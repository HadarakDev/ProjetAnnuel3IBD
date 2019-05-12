import matplotlib.pyplot as plt
import numpy as np
from ctypes import *

def readFileWeight(path):
	with open(path, "r") as f:
		lines = f.readline()
		weight = lines.split(";")
	weight = [int(x) for x in weight if x ]
	return tuple(weight)

def matrixToArray(matrix):
	ret = []
	for el in matrix:
		ret.extend(el)
	return ret

def linearRegression(Xnp,Ynp, filename):
	X = matrixToArray(Xnp.tolist())
	Y = Ynp.tolist()
	

	pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"
	#pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

	myDll = CDLL(pathDLL)
	myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
	myDll.loadTestCase.restype = c_void_p

	pMatrixX = myDll.loadTestCase((c_double * len(X))(*X), Xnp.shape[0],  Xnp.shape[1], 1)
	myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(Y))), c_uint, c_uint, c_uint]
	pMatrixY = myDll.loadTestCase((c_double * len(Y))(*Y), Ynp.shape[0], 1, 0)

	myDll.createLinearModel.argtypes = [c_int32]
	myDll.createLinearModel.restype = c_void_p
	pArrayWeight = myDll.createLinearModel(Xnp.shape[1])

	myDll.fitLinearRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int ]
	myDll.fitLinearRegression.restype = c_double								
	error = myDll.fitLinearRegression	( pArrayWeight, pMatrixX, pMatrixY, Xnp.shape[0], Xnp.shape[1] )
	
	pathSaveWeights = "C:/Users/nico_/Documents/ConvertedImages/" + filename

	myDll.saveWeightsInCSV.argtypes = [c_char_p, c_void_p]
	myDll.saveWeightsInCSV(pathSaveWeights.encode('utf-8'), pArrayWeight)

	return readFileWeight(pathSaveWeights)