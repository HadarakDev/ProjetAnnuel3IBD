#include "include.h"
#include <exception>
#include <typeinfo>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace Eigen;

extern "C" {

	// Initialisation random weight [-1,1]
	SUPEREXPORT double* create_linear_model(int inputCountPerSample)
	{
		srand(time(NULL));

		auto arrayWeight = new double[inputCountPerSample];
		
		for (int i = 0 ; i < inputCountPerSample ; i++){
			arrayWeight[i] = (rand() / (double)RAND_MAX) * (1.0 - (-1.0)) - 1.0;
		}

		return arrayWeight;
	}
		
	SUPEREXPORT double fit_regression(
		double *arrayWeight,
		Eigen::MatrixXd *X,
		Eigen::MatrixXd *Y,
		int SampleCount,
		int inputCountPerSample
	)
	{
		try {
			Eigen::MatrixXd Xtranspose(inputCountPerSample, SampleCount);

			Eigen::MatrixXd W(inputCountPerSample, 1);

			Xtranspose = (*X).transpose();

			Eigen::MatrixXd pinv = (*X).completeOrthogonalDecomposition().pseudoInverse();
			W = pinv * (*Y);
			//cout << "raw = " << W.rows() << endl;
			//cout << "col = " << W.cols() << endl;
			//cout << W << endl;
			convertMatrixToSimpleArray(W, arrayWeight);
		}
		catch (const std::exception & ex)
		{ 
			std::cout<< "Error occurred: " << ex.what() << std::endl;
			return (0);
		}
		return 0.42;
	}

	SUPEREXPORT double predict_regression(
		double* arrayWeight,
		Eigen::MatrixXd *X,
		int inputCountPerSample
	)
	{
		cout << "DEBUT NAISSANCE" << endl;
		double ret= 0.0;
		//Eigen::MatrixXd X = convertArrayToMatrix(inputCountPerSample, 1, XToPredict);
		Eigen::MatrixXd W = convertArrayToMatrix( 1, inputCountPerSample, arrayWeight);
		Eigen::MatrixXd R(1, 1);
		cout << "DEBUT AFFICHAGE" << endl;
		//cout << (*X).cols() << endl;
		//cout << (*X).rows() << endl;
		//cout << (*X) << endl;


		cout << "DEBUT CALCUL" << endl;

		R = W * (*X); 

		cout << "DEBUT DE LA FAIM" << endl;

		return (double)R(0, 0);
	}


	SUPEREXPORT void delete_linear_model(double* arrayWeight)
	{
		delete[] arrayWeight;
	}


}