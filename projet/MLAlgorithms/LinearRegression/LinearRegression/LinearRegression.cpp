// LinearRegression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <filesystem>
using namespace std;
using namespace cv;
namespace fs = std::filesystem;

void saveWeight(double *weightArray, double bice)
{
	ofstream weightFile;
	weightFile.open("example.txt");

	weightFile << bice << ";";
	//for (int i = 0; i < weightArray.)
	weightFile.close();
}

int *getArrayFromImage(string imagePath, bool isGray)
{
	Mat image;
	int component = 3;
	if (isGray == true)
		component = 1;
	image = imread(imagePath, component);
	int i = 0;
	unsigned int imageSize = image.cols * image.rows;
	int *pixelArray = new int[imageSize * component]; // a changer pour gray

	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			unsigned char *p = image.ptr(x, y); // order B G R 
			for (int c = 0; c < component; c++)
			{
				pixelArray[i++] = p[c];
			}
		}
	}
	for (int k = 0; k < imageSize * 3; k = k + component)
	{
		if (isGray == true)
			std::cout << "COLOR : " << pixelArray[k] << endl;
		else
		{
			std::cout << "BLUE: " << pixelArray[k];
			std::cout << ", GREEN : " << pixelArray[k + 1] ;
			std::cout << ", RED " << pixelArray[k + 2] << endl;
		}
	}
	return (pixelArray);
}

vector<string> getDirectoryImagesPath(string folderPath)
{
	vector<string> imagesPathList;
	for (auto& p : fs::directory_iterator(folderPath))
	{
		string ext = p.path.substr(p.path.find_last_of(".") + 1);
		if ( ext == "jpg" || ext == "png" || ext == "jpeg")
		{
			imagesPathList.push_back(p.path);
		}
	}
	return imagesPathList;
}

int *getReferenceImageSize(string imagePath)
{
	Mat image;

	image = imread(imagePath, component); // 
	int *imageSize = new int[2];
	//image = imread(imagePath, 3);
	imageSize[0] = image.rows;
	imageSize[1] = image.cols;
	return imageSize;
} 

int main()
{
	// arg: train / nom dossier
	// arg: predict / nom image
	//open dossier
	//read files (images)

	string folderPath = "C://Users//nico_//Documents//ConvertedImages//CroppedLotte//";

	vector<string> imagesPath = getDirectoryImagesPath(folderPath);
	getReferenceImageSize(imagesPath[0]);
	getArrayFromImage("C://Users//nico_//Documents//ConvertedImages//CroppedLotte//0_1_0_0_0.jpg", false);
    std::cout << "Hello World!\n"; 
}

// nom de dossier => parcours chaque image (getArrayFromImage) => getWeights/ bice => 

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
