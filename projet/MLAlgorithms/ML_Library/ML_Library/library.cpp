#include "include.h"
#include <exception>
#include <typeinfo>
#include <stdexcept>


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
			//Eigen::MatrixXd X = convertArrayToMatrix(SampleCount, inputCountPerSample, XTrain);
			//Eigen::MatrixXd Y = convertArrayToMatrix(SampleCount, 1, YTrain);
			Eigen::MatrixXd Xtranspose(inputCountPerSample, SampleCount);

			//Eigen::MatrixXd W(inputCountPerSample, 1);

			//Eigen::MatrixXd W;

			//W = ((Xtranspose * (*X)).inverse() * Xtranspose) * (*Y);
			//Xtranspose = (*X).transpose();
			
			cout << "B" << endl;
			Eigen::MatrixXd A(inputCountPerSample, inputCountPerSample);
			A = Xtranspose * (*X);
			cout << A << endl;
			cout << "LOL" << endl;
			
			//Eigen::MatrixXd B = A.inverse();
			
			////cout << "MARCHE B" << endl;	
			//Eigen::MatrixXd C = (B * Xtranspose);
			//cout << C << endl;

			//cout << "raw C= " << C.rows() << endl;
			//cout << "col C = " << C.cols() << endl;
			//cout << "raw Y = " << (*Y).rows() << endl;
			//cout << "col Y = " << (*Y).cols() << endl;
			//cout << "raw W = " << (W).rows() << endl;
			//cout << "col W = " << (W).cols() << endl;
			//auto W = C * (*Y);
			//cout << "MARCHE 4" << endl;
			//cout << "raw = " << W.rows() << endl; // 174931
			//cout << "col = " << W.cols() << endl; // 1
			//cout << inputCountPerSample << endl;
			//cout << "W00 " << W(0, 0) << endl;
			//cout << "W11 " << W(1, 1) << endl;
			//convertMatrixToSimpleArray();// , arrayWeight);
			//int j = 0;
			//for (int x = 0; x < W.rows(); x++)
			//{
			//	cout << "TEST A" << endl;
			//	for (int y = 0; y < W.cols(); y++)
			//	{
			//		//cout << "TEST B" << endl;
			//		//cout << W(x, y) << endl;
			//		//arrayWeight[j] = W(x, y);
			//		//cout << arrayWeight[j] << endl;
			//		j++;

			//	}
			//}
		}
		catch (const std::exception & ex)
		{ 
			std::cout<< "Error occurred: " << ex.what() << std::endl;
		}
		return 0.42;
	}

	SUPEREXPORT double predict_regression(
		double* arrayWeight,
		Eigen::MatrixXd *X,
		int inputCountPerSample
	)
	{
		double ret= 0.0;
		//Eigen::MatrixXd X = convertArrayToMatrix(inputCountPerSample, 1, XToPredict);
		Eigen::MatrixXd W = convertArrayToMatrix( 1, inputCountPerSample, arrayWeight);
		Eigen::MatrixXd R(1, 1);

		R = W * (*X); 

		return (double)R(0, 0);
	}


	SUPEREXPORT void delete_linear_model(double* arrayWeight)
	{
		delete[] arrayWeight;
	}


}