#include "include.h"
#include <exception>
#include <typeinfo>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace Eigen;

extern "C" {

	// Initialisation random weight [-1,1]
	SUPEREXPORT void* create_linear_model(int inputCountPerSample)
	{
		srand(time(NULL));

		Eigen::MatrixXd *W = new Eigen::MatrixXd(inputCountPerSample, 1);

		for (int i = 0; i < inputCountPerSample; i++) {
			(*W)(i, 0) = (rand() / (double)RAND_MAX) * (1.0 - (-1.0)) - 1.0;
		}
		cout << (*W)(0, 0) << endl;
		return W;
	}

	SUPEREXPORT double fit_regression(
		Eigen::MatrixXd*  W,
		Eigen::MatrixXd * X,
		Eigen::MatrixXd * Y,
		int SampleCount,
		int inputCountPerSample
	)
	{
		try {
			cout << "AA" << endl;
			Eigen::MatrixXd Xtranspose(inputCountPerSample, SampleCount);

			Xtranspose = (*X).transpose();

			Eigen::MatrixXd pinv = (*X).completeOrthogonalDecomposition().pseudoInverse();
			(*W) = pinv * (*Y);
		}
		catch (const std::exception & ex)
		{
			std::cout << "Error occurred: " << ex.what() << std::endl;
			return (0);
		}
		return 0.42;
	}

	SUPEREXPORT double predict_regression(
		Eigen::MatrixXd* W,
		Eigen::MatrixXd * X,
		int inputCountPerSample
	)
	{
		try {
			double ret = 0.0;
			Eigen::MatrixXd R(1, 1);

			R =  (*X) * (*W);
			return (double)R(0, 0);
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

	SUPEREXPORT void delete_tmp_predict(Eigen::MatrixXd* pMatrixX, Eigen::MatrixXd* pMatrixY)
	{
		delete pMatrixX;
		delete pMatrixY;
	}

	SUPEREXPORT void delete_linear_model(double* arrayWeight, Eigen::MatrixXd *pMatrixX, Eigen::MatrixXd *pMatrixY)
	{
		delete[] arrayWeight;
		delete pMatrixX;
		delete pMatrixY;
	}
}