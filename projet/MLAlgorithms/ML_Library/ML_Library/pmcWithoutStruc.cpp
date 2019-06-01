#include "include.h"
#include <stdlib.h> 

using namespace Eigen;

extern "C" {
	SUPEREXPORT void* createPMCModel(int* structure, int nbLayer)
	{
		t_pmcData* PMC;
		try
		{
			srand(time(NULL));
			PMC = new t_pmcData[1];
			PMC->W = new double** [nbLayer];
			PMC->structure = new int[nbLayer];

			PMC->structure = structure;
			PMC->lenStructure = nbLayer;
			for (int l = 1; l < nbLayer; l++)
			{
				PMC->W[l] = new double* [structure[l] + 1.0]; // neurones ajout biais

				for (int j = 1; j < structure[l] + 1; j++)
				{
					PMC->W[l][j] = new double[structure[l - 1] + 1.0]; // poids
					for (int i = 0; i < structure[l - 1] + 1; i++)
					{
						PMC->W[l][j][i] = (rand() / (double)RAND_MAX) * (1.0 - (-1.0)) - 1.0;
					}
				}
			}
			allocate(PMC);
			return PMC;
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
			return NULL;
		}
	}

	SUPEREXPORT double* predictPMC(t_pmcData * PMC, Eigen::VectorXd * X)
	{
		addInputsInPMC(PMC, X);
		for (int l = 1; l < PMC->lenStructure; l++)
		{
			for (int j = 1; j < PMC->structure[l] + 1; j++)
			{
				double tmpTotal = 0;
				for (int i = 0; i < PMC->structure[l - 1] + 1; i++)
				{
					tmpTotal += PMC->W[l][j][i] * PMC->output[l - 1][i];
				}
				if (l == PMC->lenStructure - 1)
					PMC->output[l][j] = tmpTotal;
				else
					PMC->output[l][j] = tanh(tmpTotal);

			}
		}
		double *ret = new double(PMC->structure[PMC->lenStructure - 1]);
		
		for (int i = 1; i < PMC->structure[PMC->lenStructure - 1] + 1; i++)
		{
			ret[i - 1] = PMC->output[PMC->lenStructure - 1][i];
		}
		return (ret);
	}

	SUPEREXPORT double fitPMC(t_pmcData* PMC, Eigen::MatrixXd* X, Eigen::MatrixXd* Y, int SampleCount, double alpha, int epochs, int display)
	{
		double* predictOutput;
		double* expectedOutput;
		int inputCountPerSample = PMC->structure[0] + 1;
		Eigen::MatrixXd tmpMatrixX(1, inputCountPerSample);
		Eigen::VectorXd tmpVectorX(inputCountPerSample);
		Eigen::VectorXd expectedOutputVector((*Y).cols());

		try {

			if ((*Y).cols() != PMC->structure[PMC->lenStructure - 1])
				throw std::exception("erreur Y n'est pas de la meme taille que les neurones");
			

			for (int i = 0; i < epochs; i++)
			{
				if (i % display == 0)
					cout << "current epochs  : " << i << " on " << epochs << endl;
				for (int k = 0; k < SampleCount; k++)
				{
					//cout << "A" << endl;
					//random ligne du dataset
					tmpMatrixX = (*X).block(k, 0, 1, inputCountPerSample);
					tmpVectorX = (Map<VectorXd>(tmpMatrixX.data(), tmpMatrixX.cols()));
					//cout << "B" << endl;
					predictOutput = predictPMC(PMC, &tmpVectorX);
					//cout << "C" << endl;;
					expectedOutputVector = (*Y).block(k, 0, 1, (*Y).cols());
					for (int n = 1; n < PMC->structure[PMC->lenStructure - 1] + 1; n++)
					{
						//cout << "E" << endl;

						PMC->sigma[PMC->lenStructure - 1][n] = predictOutput[n - 1] - expectedOutputVector[n - 1];
					}

					//update sigmas
					//cout << "F" << endl;
					for (int l = PMC->lenStructure - 1; l > 1; l--)
					{
						//PMC->sigma[l - 1] = new double[PMC->structure[l - 1] + 1];
						//cout << "l " << l << endl;
						for (int j = 1; j < PMC->structure[l] + 1; j++)
						{
							//cout << "j " << j << endl;
							double res = 0;
							for (int i = 0; i < PMC->structure[l - 1] + 1; i++)
							{
								//cout << "i " << i << endl;
								res += PMC->W[l][j][i] * PMC->sigma[l][i];
							}
							double newSigma = (1 - pow(PMC->output[l - 1][j], 2)) * res;
							PMC->sigma[l - 1][j] = newSigma;
						}
					}
					// update poids
					for (int l = 1; l < PMC->lenStructure; l++)
					{
						for (int j = 1; j < PMC->structure[l] + 1; j++)
						{
							for (int i = 0; i < PMC->structure[l - 1] + 1; i++)
							{
								PMC->W[l][j][i] -= alpha * PMC->output[l - 1][i] * PMC->sigma[l][j];
							}
						}
					}
				}
			}
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
			return (-1);
		}
	}
}

void addInputsInPMC(t_pmcData* PMC, Eigen::VectorXd* input)
{
	for (int i = 0; i < input->size(); i++)
	{
		PMC->output[0][i] = (*input)(i);
	}
}

void displayOutput(t_pmcData* PMC)
{
	cout << "OUTPUTS :" << endl;
	for (int l = 0; l < PMC->lenStructure; l++)
	{
		cout << "layer " << l << endl;
		for (int j = 0; j < PMC->structure[l] + 1; j++)
		{
			cout << std::setprecision(9) << PMC->output[l][j] << endl;
		}
	}
}

void displaySigmas(t_pmcData* PMC)
{
	cout << "SIGMAS :" << endl;
	for (int l = 1; l < PMC->lenStructure; l++)
	{
		cout << "layer " << l << endl;
		for (int j = 1; j < PMC->structure[l] + 1; j++)
		{
			cout << std::setprecision(9) << PMC->sigma[l][j] << endl;
		}
	}
}

void displayPmcModel(t_pmcData* PMC)
{
	cout << "STRUCT :" << endl;
	for (int k = 0; k < PMC->lenStructure; k++)
	{
		cout << PMC->structure[k] << ", ";
	}
	cout << endl;
	cout << "PMC :" << endl;
	for (int l = 1; l < PMC->lenStructure; l++)
	{
		cout << "layer " << l << endl;
		for (int j = 1; j < PMC->structure[l] + 1; j++)
		{
			cout << "	neurones " << j << endl;
			for (int i = 0; i < PMC->structure[l - 1] + 1; i++)
			{
				cout << "		weights " << PMC->W[l][j][i] << endl;
			}
		}
	}
}

//  [2, 3 , 1]
void allocate(t_pmcData* PMC)
{
	PMC->output = new double *[PMC->lenStructure];
	PMC->sigma = new double *[PMC->lenStructure];
	for (int l = 0; l < PMC->lenStructure; l++)
	{	
		PMC->output[l] = new double[PMC->structure[l] + 1];
		PMC->output[l][0] = 1;
		// sigma ne commence que à l >= 1
		if (l >= 1)
			PMC->sigma[l] = new double[PMC->structure[l] + 1];
	}
}
