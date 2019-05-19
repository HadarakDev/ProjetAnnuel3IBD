#include "include.h"
#include <stdlib.h> 

using namespace Eigen;

extern "C" {
	SUPEREXPORT double predictPMCRegression(
		t_pmc* W,
		Eigen::VectorXd* X
	)
	{
		return (predictPMC(W, X, 1));
	}

	SUPEREXPORT double predictPMCClassification(
		t_pmc* W,
		Eigen::VectorXd* X
	)
	{
		return (predictPMC(W, X, 0));
	}

	SUPEREXPORT double fitPMCRegression(
		t_pmc* W,
		Eigen::MatrixXd* X,
		Eigen::MatrixXd* Y,
		int SampleCount,
		int inputCountPerSample,
		double alpha, // Learning Rate
		int epochs, // Nombre d'itération
		int display // interval affichage
	)
	{
		cout << "START" << endl;
		inputCountPerSample = inputCountPerSample + 1;
		double predictOutput;
		double expectedOutput;
		Eigen::MatrixXd tmpMatrixX(1, inputCountPerSample);
		Eigen::VectorXd tmpVectorX(inputCountPerSample);

		try {
			for (int i = 0; i < epochs; i++)
			{
				if (epochs % display == 0)
					cout << "current epochs  : " << i << " on " << epochs << endl;
				for (int k = 0; k < SampleCount; k++)
				{
					tmpMatrixX = (*X).block(k, 0, 1, inputCountPerSample);
					tmpVectorX = (Map<VectorXd>(tmpMatrixX.data(), tmpMatrixX.cols()));
					cout << tmpVectorX << endl;
					predictOutput = predictPMCRegression(W, &tmpVectorX);
					cout << "predict = " << predictOutput << endl;
					expectedOutput = (*Y)(k, 0);
					cout << "expected =" << expectedOutput << endl;

					
					(*W).layers[(*W).nbLayer - 1].neurones[0].sigma = predictOutput - expectedOutput;

					cout << "nbLayer " << (*W).nbLayer << endl;
					for (int l = (*W).nbLayer - 2; l >= 0; l--)
					{	
						cout << "parcours layer :  " << l <<  endl;
						//calcul sigma

						for (unsigned int i = 0; i < (*W).layers[l].nbNeurone; i++)
						{
							cout << "   parcours neurone :  " << i << endl;
							double total = 0;
							for (unsigned int j = 0; j < (*W).layers[l + 1].nbNeurone; j++)
							{
								cout << "      parcours somme :  " << j << endl;
								total += (*W->layers[l + 1].neurones[j].weights)(i + 1) * (*W).layers[l + 1].neurones[j].sigma;
							}

							double sigmaBefore = (1 - pow((*W).layers[l].neurones[i].result, 2)) * total;
							(*W).layers[l].neurones[i].sigma = sigmaBefore;
						}			
					}
					cout << "debut correction poids" << endl;
					// correction des poids
					for (unsigned int l = 0; l < (*W).nbLayer - 1;l++)
					{
						cout << "layer: " << l << endl;
						for (int idxNeurone = 0; idxNeurone < (*W).layers[l].nbNeurone - 1; idxNeurone++)
						{
							cout << "nb neurone " << (*W).layers[l].nbNeurone << endl;
							cout << "   neurone: " << idxNeurone << endl;
							for (unsigned int idxWeights = 0; idxWeights < (*W).layers[l].neurones[idxNeurone].weights->size() - 1; idxWeights++)
							{
								cout << "      weights: " << idxWeights << endl;
								(*W->layers[l].neurones[idxNeurone].weights)(idxWeights) -= alpha * (*W).layers[l].neurones[idxNeurone].result * (*W).layers[l].neurones[idxNeurone].sigma;
							}
						}
					}
				}
			}
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
			return (0);
		}
	}

	SUPEREXPORT void *createPMCModel(int *structure, int nbLayer, int inputCountPerSample)
	{

		srand(time(NULL));
		try
		{	
			t_pmc *pmc = NULL;
			if ((pmc = (t_pmc*)malloc(sizeof(t_pmc) * 1)) == NULL)
				return (NULL); // if == null throws exception
			pmc->nbLayer = nbLayer;
			if ((pmc->layers = (t_layer*)malloc(sizeof(t_layer) * nbLayer)) == NULL)
				return (NULL); // if == null throws exception
			for (int idxLayer = 0; idxLayer < nbLayer; idxLayer++)
			{
				if ((pmc->layers[idxLayer].neurones = (t_neurone*)malloc(sizeof(t_neurone) * structure[idxLayer])) == NULL)
					return (NULL);
				pmc->layers[idxLayer].nbNeurone = structure[idxLayer];
				for (int idxNeurone = 0; idxNeurone < structure[idxLayer]; idxNeurone++)
				{
					int nbWeights;
					if (idxLayer == 0)
						nbWeights = inputCountPerSample;
					else
						nbWeights = structure[idxLayer - 1];
					nbWeights++; // ajout du biais

					pmc->layers[idxLayer].neurones[idxNeurone].weights = new Eigen::VectorXd(nbWeights);
					for (int idxWeights = 0; idxWeights < nbWeights; idxWeights++)
					{
						//(*pmc->layers[idxLayer].neurones[idxNeurone].weights)(idxWeights) = (rand() / (double)RAND_MAX) * (1.0 - (-1.0)) - 1.0;
						(*pmc->layers[idxLayer].neurones[idxNeurone].weights)(idxWeights) = 1;
					}
				}
			}
			return (pmc);
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
		}
	}
}

void calculateNeuroneOutput(t_neurone *neurone, Eigen::VectorXd *input, unsigned int isLinear)
{
	Eigen::VectorXd tmp(input->size());

	tmp = (*input).transpose() * (*neurone->weights);
	if (isLinear == 1)
		(*neurone).result = tmp.sum();
	else
		(*neurone).result = tanh(tmp.sum());
}

Eigen::VectorXd *getLayerOuptut(t_layer* layer)
{
	Eigen::VectorXd* layerResult = new Eigen::VectorXd((layer->nbNeurone + 1));
	(*layerResult)(0) = 1;
	for (int idxNeurone = 1; idxNeurone < layer->nbNeurone + 1; idxNeurone++)
	{
		(*layerResult)(idxNeurone) = (*layer).neurones[idxNeurone - 1].result;
	}
	return (layerResult);
}

double predictPMC(
	t_pmc* W,
	Eigen::VectorXd* X,
	unsigned int isLinear
)
{
	Eigen::VectorXd* tmpLayerResult;
	try {

		for (unsigned int idxNeurone = 0; idxNeurone < (*W).layers[0].nbNeurone; idxNeurone++)
		{
			cout << "JE PLANTE APRES" << endl;
			cout << (*X) << endl;
			calculateNeuroneOutput(&(*W).layers[0].neurones[idxNeurone], X, 0);
			cout << "JE PLANTE AVANT" << endl;
			cout << (*W).layers[0].neurones[idxNeurone].result << endl;
		}
		tmpLayerResult = getLayerOuptut(&(*W).layers[0]);
		cout << (*tmpLayerResult) << endl;
		for (unsigned int idxLayer = 1; idxLayer < W->nbLayer; idxLayer++)
		{
			for (unsigned int idxNeurone = 0; idxNeurone < (*W).layers[idxLayer].nbNeurone; idxNeurone++)
			{
				if (idxLayer == (*W).nbLayer - 1)
					calculateNeuroneOutput(&(*W).layers[idxLayer].neurones[idxNeurone], tmpLayerResult, isLinear);
				else
					calculateNeuroneOutput(&(*W).layers[idxLayer].neurones[idxNeurone], tmpLayerResult, 0);
				cout << (*W).layers[idxLayer].neurones[idxNeurone].result << endl;

			}
			tmpLayerResult = getLayerOuptut(&(*W).layers[idxLayer]);
			cout << (*tmpLayerResult) << endl;
		}
		cout << ((*W).layers[(*W).nbLayer - 1].neurones[0].result) << endl;
		return ((*W).layers[(*W).nbLayer - 1].neurones[0].result);
	}
	catch (const std::exception & ex)
	{
		std::cout << "Error occurred: " << ex.what() << std::endl;
		return (-1);
	}
	catch (const runtime_error & error)
	{
		std::cout << "Error occurred: " << error.what() << std::endl;
		return (-2);
	}
}