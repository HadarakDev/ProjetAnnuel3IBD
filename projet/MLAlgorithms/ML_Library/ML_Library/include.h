#ifndef INCLUDE_H_
#define INCLUDE_H_


//C++ LIB
#include <iostream>
#include <fstream>
#include <time.h>
#include <exception>
#include <typeinfo>
#include <iomanip>
#include <stdexcept>

//OpenCV 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace cv;

#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT 
#endif

//SUPEREXPORT double predictLinearRegression(Eigen::MatrixXd*, Eigen::MatrixXd*);
// matrixUtils.cpp
Eigen::MatrixXd convertArrayToMatrix(int SampleCount, int inputCountPerSample, double *Array);
void convertMatrixToSimpleArray(Eigen::MatrixXd matrix, double *arr);
//bool matrixMultiplicationPossible(Eigen::MatrixXd matrixA, Eigen::MatrixXd matrixB);

// imageUtils.cpp
void getPixelsFromImage(string imagePath, int component, Eigen::MatrixXd *datasetX,
	unsigned int imageIdx, unsigned int sizeImageW, unsigned int sizeImageH);



#endif // !"INCLUDE_H"