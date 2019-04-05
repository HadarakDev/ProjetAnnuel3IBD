#ifndef INCLUDE_H_
#define INCLUDE_H_


//C++ LIB
#include <iostream>
#include <fstream>


//OpenCV 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace cv;



// matrixUtils.cpp
Eigen::MatrixXd convertArrayToMatrix(int SampleCount, int inputCountPerSample, double *Array);
//bool matrixMultiplicationPossible(Eigen::MatrixXd matrixA, Eigen::MatrixXd matrixB);

// imageUtils.cpp
//int *getPixelsFromImage(string imagePath, int component);

#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT 
#endif

#endif // !"INCLUDE_H"