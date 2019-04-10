

//#include "include.h"
#include <Eigen/Dense>

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