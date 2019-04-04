#if _WIN32
#define SUPEREXPORT __declspec(dllexport)
#else
#define SUPEREXPORT 
#endif

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
//#include <dirent.h>

using namespace std;
using namespace cv;

extern "C" {
	SUPEREXPORT int *getPixelsFromImage(string imagePath, int component, int *requiredSize)
	{
		Mat image;
		image = imread(imagePath, component);
		int i = 0;
		//if (image.rows != requiredSize[0] || image.cols != requiredSize[1])
			//return (NULL); // wrong size
		int fullSize = requiredSize[0] * requiredSize[1] * component;
		int *pixelArray = new int[requiredSize[0] * requiredSize[1] * component];

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
		return (pixelArray);
	}
}
//
//void displayPixelArray(int *pixelArray, int imageSize, int component)
//{
//	for (int k = 0; k < imageSize; k = k + component)
//	{
//		if (component == 1)
//			std::cout << "COLOR : " << pixelArray[k] << endl;
//		else
//		{
//			std::cout << "BLUE: " << pixelArray[k];
//			std::cout << ", GREEN : " << pixelArray[k + 1];
//			std::cout << ", RED " << pixelArray[k + 2] << endl;
//		}
//	}
//}
//
//
//vector<string> getDirectoryImagesPath(string folderPath)
//{
//	vector<string> imagesPathList;
//	struct dirent *dirent;
//	DIR *dir;
//
//	char folderPathChar[folderPath.size() + 1];
//	strcpy(folderPathChar, folderPath.c_str());
//
//	dir = opendir(folderPathChar);
//	while ((dirent = readdir(dir))) {
//		string path = string(dirent->d_name);
//		size_t tmp = path.find_last_of(".") + 1;
//		string ext = path.substr(tmp, path.length());
//		if (ext.compare("jpg") == 0 || ext.compare("png") == 0 || ext.compare("jpeg") == 0)
//		{
//			imagesPathList.push_back(folderPath + "/" + path);
//		}
//	}
//	closedir(dir);
//	return imagesPathList;
//}
//
//int *getReferenceImageSize(string imagePath, int component)
//{
//	Mat image;
//
//	image = imread(imagePath, component);
//	int *imageSize = new int[2];
//	imageSize[0] = image.rows; // height
//	imageSize[1] = image.cols; // width
//	std::cout << "Height " << imageSize[0] << "Width " << imageSize[1] << std::endl;
//	return imageSize;
//}
//
//void savePixelsInCSV(string path, int *pixelArray, int *imageSize, int component)
//{
//	ofstream fd;
//	cout << "aa";
//
//	size_t start = path.find_last_of("/") + 1;
//	size_t end = path.find_last_of(".");
//	string csvPath = path.substr(start, end - start) + ".csv";
//	//cout << csvPath << endl;
//	fd.open("/home/hadarak/LotteCSV/" + csvPath);
//
//	int size = imageSize[0] * imageSize[1] * component;
//
//	for (int i = 0; i < size - 1; i++)
//	{
//		fd << pixelArray[i];
//		fd << ";";
//	}
//	fd.close();
//}
//
//int main(int ac, char **av)
//{
//	// arg: train / nom dossier
//	// arg: predict / nom image
//	//open dossier
//	//read files (images)
//
//
//	int component = 3;
//	if (ac < 2)
//		return (-1);
//
//	string folderPath = av[1];
//
//	vector<string> imagesPath = getDirectoryImagesPath(folderPath);
//	int * imageSize = getReferenceImageSize(imagesPath[0], component);
//	//std::cout << "Height " << imageSize[0] << "Width "  << imageSize[1] << std::endl;
//	for (int i = 0; i < imagesPath.size(); i++)
//	{
//		int *pixelArray;
//		if ((pixelArray = getPixelsFromImage(imagesPath[i], component, imageSize)) != NULL)
//			savePixelsInCSV(imagesPath[i], pixelArray, imageSize, component);
//		delete pixelArray;
//	}
//
//	std::cout << "Hello World!\n";
//}

// nom de dossier => parcours chaque image (getArrayFromImage) => getWeights/ bice => 
