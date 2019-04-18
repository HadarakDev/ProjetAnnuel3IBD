#include "include.h"

extern "C" {

	SUPEREXPORT double fit_regression_gd(
		double* arrayWeight,
		double* XTrain,
		double* YTrain,
		int sampleCount,
		int inputCountPerSample
	)
	{
		int nb_epoch = 30;
		double lr = 1.05;

		Eigen::MatrixXd X = convertArrayToMatrix(sampleCount, inputCountPerSample, XTrain);
		Eigen::MatrixXd Y = convertArrayToMatrix(sampleCount, 1, YTrain);
		Eigen::MatrixXd W = convertArrayToMatrix(++inputCountPerSample, 1, arrayWeight);
		Eigen::MatrixXd mat(0, 0);
		/*
		for (int epo = 0; epo < nb_epoch; epo++) {
			for (int sample = 0; sample < sampleCount; sample++) {
				for (int weight = 0; weight < inputCountPerSample; weight++) {
					mat = 
				}
			}
		}
		*/
		//découper en sous matrice
		std::cout << X << std::endl;
		std::cout << "--" << std::endl;
		std::cout << X.block<1, inputCountPerSample>(0,0) << std::endl;

			return 0.42;
	}

}