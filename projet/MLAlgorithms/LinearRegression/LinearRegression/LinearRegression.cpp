// LinearRegression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;



int *getArrayFromImage(string imagePath)
{
	Mat image;
	image = imread(imagePath, 3);
	int i = 0;
	unsigned int imageSize = image.cols * image.rows;
	int *pixelArray = new int[imageSize * 3]; // a changer pour gray

	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			unsigned char *p = image.ptr(x, y); // order B G R 
			pixelArray[i] = p[2];
			pixelArray[i + 1] = p[1];
			pixelArray[i + 2] = p[0];
			i = i + 3;
		}
	}
	for (int k = 0; k < imageSize * 3; k = k + 3)
	{
		std::cout << "RED : " << pixelArray[k];
		std::cout << ", GREEN : " << pixelArray[k + 1] ;
		std::cout << ", BLUE " << pixelArray[k + 2] << endl;;
		
	}
	return (pixelArray);
}
int main()
{
	getArrayFromImage("C://Users//nico_//Documents//ConvertedImages//CroppedLotte//0_1_0_0_0.jpg");
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
