#include "include.h"
#include "pmc.h"
#include <stdlib.h> 

using namespace Eigen;

extern "C" {

	// Initialisation random weight [-1,1]
	SUPEREXPORT void *createPMCModel(int *structure, int nbLayer, int inputCountPerSample)
	{

		srand(time(NULL));
		try
		{
			t_layer* pmcLayers = NULL;
			if ((pmcLayers = (t_layer*)malloc(sizeof(t_layer) * nbLayer)) == NULL)
				return (NULL); // if == null throws exception
			for (int idxLayer = 0; idxLayer < nbLayer; idxLayer++)
			{
				if ((pmcLayers[idxLayer].neurones = (t_neurone*)malloc(sizeof(t_neurone) * structure[idxLayer])) == NULL)
					return (NULL);

				for (int idxNeurone = 0; idxNeurone < structure[idxLayer]; idxNeurone++)
				{
					int nbWeights;
					if (idxLayer == 0)
						nbWeights = inputCountPerSample;
					else
						nbWeights = structure[idxLayer - 1];
					nbWeights++; // ajout du biais

					pmcLayers[idxLayer].neurones[idxNeurone].weights = new Eigen::VectorXd(nbWeights);
					for (int idxWeights = 0; idxWeights < nbWeights; idxWeights++)
					{
						pmcLayers[idxLayer].neurones[idxNeurone].weights(idxWeights) = (rand() / (double)RAND_MAX) * (1.0 - (-1.0)) - 1.0;
					}
				}
			}
			cout << pmcLayers[2].neurones[1].weights[2] << endl;
			return (pmcLayers);
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
		}
	}
}