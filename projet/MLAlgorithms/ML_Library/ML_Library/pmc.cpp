#include "include.h"
#include "pmc.h"
#include <stdlib.h> 

using namespace Eigen;

extern "C" {

	void calculateNeuroneOutput(t_neurone* neurone, Eigen::VectorXd* input);
	SUPEREXPORT double predictPMCRegression(
		t_pmc *W,
		Eigen::VectorXd *X
	)
	{
		try {
			//for (int idxLayer = 0; idxLayer < W->nbLayer; idxLayer++)
			for (int idxNeurone = 0; idxNeurone < (*W).layers[0].nbNeurone; idxNeurone++)
			{
				calculateNeuroneOutput(&(*W).layers[0].neurones[idxNeurone], X);
				cout << (*W).layers[0].neurones[idxNeurone].result << endl;
			}
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
			cout << (*pmc->layers[2].neurones[1].weights)(2) << endl;
			return (pmc);
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
		}
	}
}

void calculateNeuroneOutput(t_neurone *neurone, Eigen::VectorXd *input)
{
	Eigen::VectorXd tmp(input->size());

	cout << "AA" << endl;
	tmp = (*input) * (*neurone->weights);
	(*neurone).result = tmp.sum();
	cout << tmp.sum() << endl;


}