from ctypes import *
from numpy.ctypeslib import ndpointer
import os

if __name__ == "__main__":

	#information dataset
	#pathDataset = "C:"
	#composante = 3
	#sizeImage = 490 * 357

	#files = os.listdir(pathDataset)
	#for file in files:
	#	#executer la dll

	trainX = [0,0,1,1]
	trainY = [0,1]
	arrayWeight = [0.5, 0.4, -0.8]
	SampleCount = len(trainY)
	inputCountPerSample = len(trainX)

	myDll = CDLL("C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Debug/ML_Library.dll")
	myDll.create_linear_model.argtypes = [c_int]
	myDll.create_linear_model.restype = POINTER(c_double * 6)	
	
	#creer le modele
	#arrayWeight = myDll.create_linear_model(len(trainX[0]))
	

	#entrainement du modele
	myDll.create_linear_model.argtypes = [ POINTER(ARRAY(c_double, len(arrayWeight))),  POINTER(ARRAY(c_double, len(trainX))), c_int, c_int, POINTER(ARRAY(c_double,len(trainY))) ]
	myDll.fit_regression( (c_double*len(arrayWeight))(*arrayWeight) , (c_double*len(trainX))(*trainX), SampleCount, inputCountPerSample, (c_double*len(trainY))(*trainY))

	#double* W, double* XToPredict, int inputCountPerSample

#	for el in arrayWeight[0]:
#		print(el)
	
	#Dll.predict_regression.argtypes = [c_void_p, POINTER(ARRAY(c_double, 2)), c_int32]
    
	
	#myDll.predict_regression.restype = c_double
    #native_input = (c_double * 2)(*[0.0, 0.0])
    #rslt = myDll.predict_regression(toto, native_input, 2)
    #print(rslt)
	print("\nend")