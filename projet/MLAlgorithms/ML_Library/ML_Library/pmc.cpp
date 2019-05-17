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
					cout << "TEST" << endl;
					tmpVectorX = (Map<VectorXd>(tmpMatrixX.data(), tmpMatrixX.cols()));
					cout << tmpVectorX << endl;
					predictOutput = predictPMCRegression(W, &tmpVectorX);
					cout << "predict = " << predictOutput << endl;
					expectedOutput = (*Y)(k, 0);
					cout << "expected =" << expectedOutput << endl;
					double sigma = predictOutput - expectedOutput;
					
					//for (unsigned int idxWeight )
					//{
					//}
					//	= 1 - (pow((*W).layers[1].neurones[idxNeurone].result))
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
	cout << "KINDRED" << endl;
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