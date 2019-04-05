#include "include.h"


extern "C" {

	// Initialisation random weight [-1,1]
	SUPEREXPORT double* create_linear_model(int inputCountPerSample)
	{
		std::cout << inputCountPerSample << endl;
		auto arrayWeight = new double[inputCountPerSample + 1];
		
		for (int i = 0 ; i < inputCountPerSample + 1 ; i++){
			//arrayWeight[i] = (rand() / (double)RAND_MAX) * (1.0 - -1.0) + -1.0;
			arrayWeight[i] = 0.42;
		}
		return arrayWeight;
	}
		
	SUPEREXPORT void fit_regression(
		double* arrayWeight,
		double* XTrain,
		int SampleCount,
		int inputCountPerSample,
		double* YTrain
	)
	{

		std::cout << " arrayWeight = " << arrayWeight[0] << " Xtrain = " << XTrain[0] << " Sample Count = " << SampleCount << " inputCount = "
			<< inputCountPerSample << " Ytrain = " << YTrain[0] << endl;
		// TODO : entrainement (correction des W, cf slides !)
		auto a = convertArrayToMatrix(SampleCount, inputCountPerSample, XTrain);
		std::cout << a << std::endl;
	}

	SUPEREXPORT double predict_regression(
		double* W,
		double* XToPredict,
		int inputCountPerSample
	)
	{
		// TODO : Inférence (CF Slides !)
		return 0.42;
	}


	SUPEREXPORT void delete_linear_model(double* W)
	{
		delete[] W;
	}


}