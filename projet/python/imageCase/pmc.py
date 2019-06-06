from ctypes import *
import os
from data import *
from utils import *
import time
from params import *
import random
import numpy as np
import matplotlib.pyplot as plt
from numpy.ctypeslib import ndpointer

if __name__ == "__main__":

    myDll = CDLL(pathDLL)

    imagesName = os.listdir(pathDatasetTrain)
    selectedImages = random.sample(imagesName, numberImageTrain)
    selectedImages = convertListToString(selectedImages, pathDatasetTrain)
    pMatrixX, pMatrixY = prepareDataset(selectedImages, myDll, numberImageTrain)

    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, len(pmcStruct))), c_uint, c_uint]
    myDll.createPMCModel.restype = c_void_p

    W = myDll.createPMCModel(arrStruct, len(pmcStruct), inputCountPerSample)

    myDll.fitPMCRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int, c_double, c_int, c_int ]
    myDll.fitPMCRegression.restype = c_double								
    error = myDll.fitPMCRegression( W, pMatrixX, pMatrixY, sampleCount, inputCountPerSample, 0.1, 100, 1000)

    imagesName = os.listdir(pathDatasetPredict)	
    selectedImages = random.sample(imagesName, numberImagePredict)
    selectedImages = [pathDatasetPredict + el for el in selectedImages ]

    print ("----Prediction---")
    predictResponse = predictPMCAverage(myDll, myDll.predictPMCRegression, selectedImages , pArrayWeight)
    print("Moyenne erreurs² : %s" % predictResponse )
    print("Moyenne erreurs : %s" % predictResponse**0.5 )

    myDll.deletePMC.argtypes = [ c_void_p ]
    myDll.deletePMC(W)


	







 
