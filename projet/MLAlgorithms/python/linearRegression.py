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

	imagesPath = os.listdir(pathDataset)
	
	selectedImages = random.sample(imagesPath, numberImage)
	pMatrixX, pMatrixY = prepareDataset(selectedImages, myDll, numberImage)
	
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
											numberImage,
											inputCountPerSample
									)

	
	#faire une prediction
	
	for i in range(0, 50):
		print ("----Prediction---")
		toPredictImage = random.sample(imagesPath, 1)
		predictResponse = predict(myDll, myDll.predict_regression, toPredictImage, pArrayWeight)
		print("response : %s , image %s \n" % (predictResponse, toPredictImage))
	print("--- %s seconds ---" % (time.time() - start_time))
	
	#predictResponse = predictAverage(myDll, myDll.predict_regression, pathDataset, pArrayWeight, 10)
	#print("res moyen %s" % predictResponse )

	myDll.delete_linear_model.argtypes = [ c_void_p, c_void_p, c_void_p ]
	myDll.delete_linear_model( pArrayWeight, pMatrixX, pMatrixY)

