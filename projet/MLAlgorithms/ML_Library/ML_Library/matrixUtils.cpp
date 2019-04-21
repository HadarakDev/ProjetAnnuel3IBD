

#include "include.h"
#include <Eigen/Dense>

extern "C" {
	SUPEREXPORT Eigen::MatrixXd *getDatasetX(char *str, unsigned int sizeImage, unsigned int numberImage)
	{
		size_t pos = 0;
		std::string token;
		std::string s = str;
		int imageIdx = 0;
		unsigned int inputCountPerSample = sizeImage + 1;
		Eigen::MatrixXd retMatrix(numberImage, sizeImage);
		while ((pos = s.find(",")) != std::string::npos) {
			token = s.substr(0, pos);
			
			retMatrix(imageIdx, 0) = 1;



			s.erase(0, pos + 1);
			imageIdx++;
		}
		

		return &retMatrix;
	}
}

Eigen::MatrixXd convertArrayToMatrix(int SampleCount, int inputCountPerSample, double *Array)
{
	Eigen::MatrixXd retMatrix(SampleCount, inputCountPerSample);
	int i = 0;
	for (int x = 0; x < SampleCount; x++)
	{
		for (int y = 0; y < inputCountPerSample; y++)
		{
			retMatrix(x, y) = Array[i];
			i++;
		}
	}
	return (retMatrix);
}

void convertMatrixToSimpleArray(Eigen::MatrixXd matrix, double *arr) {
	int col = matrix.cols();
	int row = matrix.rows();
	int j = 0;

	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < col; y++)
		{
			arr[j++] = matrix(x,y);
		}
	}
	
}
//bool matrixMultiplicationPossible(Eigen::MatrixXd matrixA, Eigen::MatrixXd matrixB)
//{
//	if (matrixA.rows() == matrixB.cols())
//		return (true);
//	return (false);
//}