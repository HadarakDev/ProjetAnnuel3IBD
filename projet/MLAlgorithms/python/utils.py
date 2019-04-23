from ctypes import *
from params import *
import os
import random

def printRes(tab):
	for el in tab:
		print (el)

def truncate(n, size):
	return float(str(n)[:size+2])

def matrixToArray(matrix):
	ret = []
	for el in matrix:
		ret.extend(el)
	return ret, len(ret)

def convertListToString(list):
	ret = ""
	for el in list:
		ret += pathDataset + el
		ret += ','
	return ret

def prepareDataset(imagePaths, myDll, numberImage):	
	paths = convertListToString(imagePaths)
	#paths = [x.replace("\\", "/") for x in paths]
	param = paths.encode('utf-8')
	
	myDll.getDatasetX.argtypes = [c_char_p, c_uint, c_uint, c_uint]
	myDll.getDatasetX.restype = c_void_p
	pMatrixX = myDll.getDatasetX(param, sizeImage, numberImage, component)

	myDll.getDatasetY.restype = c_void_p
	myDll.getDatasetY.argtypes = [c_char_p, c_uint]
	pMatrixY = myDll.getDatasetY(param, numberImage)

	return pMatrixX, pMatrixY

#tester
def predict(myDll, function, path, pArrayWeight):
	pMatrixXPredict, pMatrixYPredict = prepareDataset(path, myDll, 1)
	function.argtypes = [
							c_void_p,
							c_void_p,
							c_int
						]
	function.restype = c_double
	predictResponse = function (
							pArrayWeight,
							pMatrixXPredict,
							inputCountPerSample
						)
	myDll.delete_tmp_predict.argtypes =  [ c_void_p, c_void_p ]
	myDll.delete_tmp_predict ( pMatrixXPredict, pMatrixYPredict )

	return predictResponse

def	predictAverage(myDll, function, path, pArrayWeight, nbImage):

	print("test")
	res = 0
	imagesPath = os.listdir(path)
	selectedImages = random.sample(imagesPath, 1)

	for image in selectedImages:
		res += predict(myDll, function, image, pArrayWeight)
	return res / len(selectedImages)
	



