	

#include "include.h"
#include <Eigen/Dense>

extern "C" {
	SUPEREXPORT void* getDatasetY(char* str, unsigned int numberImage)
	{
		size_t pos = 0;
		std::string token;
		std::string s = str;

		unsigned int imageIdx = 0;
		Eigen::MatrixXd* retMatrix = new Eigen::MatrixXd(numberImage, 1);
		while ((pos = s.find(",")) != std::string::npos) {
			token = s.substr(0, pos);

			size_t start = token.find_last_of("/") + 1;
			string filename = token.erase(0, start);

			size_t delim = filename.find("_");
			string age = filename.substr(0, delim);

			(*retMatrix)(imageIdx) = std::stoi(age);
			s.erase(0, pos + 1);
			imageIdx++;
		}
		if (s.length() != 0)
		{
			size_t start = s.find_last_of("/") + 1;
			string filename = s.erase(0, start);

			size_t delim = filename.find("_");
			string age = filename.substr(0, delim);

			(*retMatrix)(imageIdx) = std::stoi(age);
		}
		return retMatrix;
	}

	SUPEREXPORT void* getDatasetX(char* str, unsigned int sizeImageW, unsigned int sizeImageH, unsigned int numberImage, unsigned int component)
	{
		size_t pos = 0;
		std::string token;
		std::string s = str;
		unsigned int imageIdx = 0;
		unsigned int inputCountPerSample = (sizeImageW * sizeImageH * component) + 1;
		Eigen::MatrixXd* retMatrix = new Eigen::MatrixXd(numberImage, inputCountPerSample);
		while ((pos = s.find(",")) != std::string::npos) {
			token = s.substr(0, pos);

			(*retMatrix)(imageIdx, 0) = 1;
			getPixelsFromImage(token, component, retMatrix, imageIdx, sizeImageW, sizeImageH);

			s.erase(0, pos + 1);
			imageIdx++;
		}
		if (s.length() != 0)
		{
			(*retMatrix)(imageIdx, 0) = 1;
			getPixelsFromImage(s, component, retMatrix, imageIdx, sizeImageW, sizeImageH);
		}
		return retMatrix;
	}
	SUPEREXPORT void saveWeightsInCSV(char* path, Eigen::MatrixXd * W)
	{
		ofstream fd;

		fd.open(path);

		for (int x = 0; x < (*W).rows(); x++)
		{
			for (int y = 0; y < (*W).cols(); y++)
			{
				fd << (*W)(x, y);
				fd << ";";
			}
		}
		fd.close();
	}

	SUPEREXPORT void* loadWeightsWithCSV(char* path, unsigned int inputCountPerSample)
	{
		Eigen::MatrixXd* W = new Eigen::MatrixXd(inputCountPerSample + 1, 1);
		double x;
		size_t pos = 0;
		std::string token;
		unsigned int i = 0;

		// get input count per sample (on filename)
		std::ifstream fd(path);

		if (!fd) {
			cout << "Unable to open file";
			exit(1);
		}
		std::string line = "";
		getline(fd, line);
		while ((pos = line.find(";")) != std::string::npos) {
			token = line.substr(0, pos);
			x = stod(token);
			(*W)(i, 0) = x;
			line.erase(0, pos + 1);
			i++;
		}
		return (W);
	}
}

Eigen::MatrixXd convertArrayToMatrix(int SampleCount, int inputCountPerSample, double *Array)
{
	inputCountPerSample = inputCountPerSample + 1;
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

void convertMatrixToSimpleArray(Eigen::MatrixXd W, double *arr) {
	int col = W.cols();
	int row = W.rows();
	int j = 0;
	
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < col; y++)
		{
			arr[j] = W(x, y);
			j++;

		}
	}
}
//bool matrixMultiplicationPossible(Eigen::MatrixXd matrixA, Eigen::MatrixXd matrixB)
//{
//	if (matrixA.rows() == matrixB.cols())
//		return (true);
//	return (false);
//}