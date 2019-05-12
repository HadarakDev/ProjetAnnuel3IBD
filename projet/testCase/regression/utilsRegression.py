import matplotlib.pyplot as plt
import numpy as np
from ctypes import *

def readFileWeight(path):
	with open(path, "r") as f:
		lines = f.readline()
		weight = lines.split(";")
	return tuple(weight)

def linearRegression(Xnp,Ynp, filename):
	X = Xnp.tolist()
	Y = Ynp.tolist()
	
	pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"
	#pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

	myDll = CDLL(pathDLL)

	myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
	myDll.loadTestCase.restype = c_void_p

	pMatrixX = myDll.loadTestCase((c_double * len(X))(*X), len(X),  len(X[0]), 1)
	myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(Y))), c_uint, c_uint, c_uint]
	pMatrixY = myDll.loadTestCase((c_double * len(Y))(*Y), len(Y), 1, 0)

	myDll.createLinearModel.argtypes = [c_int32]
	myDll.createLinearModel.restype = c_void_p
	pArrayWeight = myDll.createLinearModel(len(X[0])

	myDll.fitLinearRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int ]
	myDll.fitLinearRegression.restype = c_double								
	error = myDll.fitLinearRegression	( pArrayWeight, pMatrixX, pMatrixY, len(X), len(X[0]) )
	
	pathSaveWeights = "C:/Users/nico_/Documents/ConvertedImages/" + filename

	myDll.saveWeightsInCSV.argtypes = [c_char_p, c_void_p]
	myDll.saveWeightsInCSV(pathSaveWeights.encode('utf-8'), pArrayWeight)

	return readFileWeight(pathSaveWeights)
