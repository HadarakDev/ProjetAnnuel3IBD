from ctypes import *
from numpy.ctypeslib import ndpointer
import os
from data import *
from utils import *
import time
from params import *
import random

if __name__ == "__main__":

	start_time = time.time()
	#chargemennt de la DLL
	myDll = CDLL(pathDLL)

	imagesName = os.listdir(pathDatasetTrain)
	
	selectedImages = random.sample(imagesName, numberImageTrain)
	selectedImages = convertListToString(selectedImages, pathDatasetTrain)

	pMatrixX, pMatrixY = prepareDataset(selectedImages, myDll, numberImageTrain)
	
	#changement de dimension pour le transfert
	#arrTrainX, arrTrainXSize = matrixToArray(trainX)

	myDll.create_linear_model.argtypes = [c_int32]
	myDll.create_linear_model.restype = c_void_p
	pArrayWeight = myDll.create_linear_model(inputCountPerSample)
	print ("----Train---")
	#entrainement du modèle
	myDll.fit_regression.argtypes = [ 	
										c_void_p,
										c_void_p, 
										c_void_p, 
										c_int,
										c_int 
									]
	myDll.fit_regression.restype = c_double								
	error = myDll.fit_regression	( 	
											pArrayWeight,
											pMatrixX,
											pMatrixY, 
											numberImageTrain,
											inputCountPerSample
									)

	
	#faire une prediction
	
	# for i in range(0, 50):
	# 	print ("----Prediction---")
	# 	toPredictImage = random.sample(imagesName, 1)
	# 	predictResponse = predict(myDll, myDll.predict_regression, toPredictImage, pArrayWeight)
	# 	print("response : %s , image %s \n" % (predictResponse, toPredictImage))
	# print("--- %s seconds ---" % (time.time() - start_time))
	
	imagesName = os.listdir(pathDatasetPredict)	
	selectedImages = random.sample(imagesName, numberImagePredict)
	selectedImages = [pathDatasetPredict + el for el in selectedImages ]
	print(selectedImages)

	predictResponse = predictAverage(myDll, myDll.predict_regression, selectedImages , pArrayWeight, 10)
	print("Moyenne erreurs² : %s" % predictResponse )

	myDll.delete_linear_model.argtypes = [ c_void_p, c_void_p, c_void_p ]
	myDll.delete_linear_model( pArrayWeight, pMatrixX, pMatrixY)

