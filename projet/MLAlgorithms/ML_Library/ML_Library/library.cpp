#include "include.h"


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
		double* XTrain,
		double* YTrain,
		int SampleCount,
		int inputCountPerSample
	)
	{
		Eigen::MatrixXd X = convertArrayToMatrix(SampleCount, inputCountPerSample, XTrain);
		Eigen::MatrixXd Y = convertArrayToMatrix(SampleCount, 1, YTrain);
		Eigen::MatrixXd Xtranspose(inputCountPerSample, SampleCount);
		Eigen::MatrixXd W(++inputCountPerSample, 1);
		Xtranspose = X.transpose();
		
		W = ((Xtranspose * X).inverse() * Xtranspose) * Y;

		convertMatrixToSimpleArray(W, arrayWeight);
		return 0.42;
	}

	SUPEREXPORT double predict_regression(
		double* arrayWeight,
		double* XToPredict,
		int inputCountPerSample
	)
	{
		double ret= 0.0;
		Eigen::MatrixXd X = convertArrayToMatrix(inputCountPerSample, 1, XToPredict);
		Eigen::MatrixXd W = convertArrayToMatrix( 1, inputCountPerSample, arrayWeight);
		Eigen::MatrixXd R(1, 1);

		R = W * X; 

		return (double)R(0, 0);
	}


	SUPEREXPORT void delete_linear_model(double* arrayWeight)
	{
		delete[] arrayWeight;
	}


}