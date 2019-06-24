from ctypes import *
import numpy as np
import matplotlib.pyplot as plt
from numpy.ctypeslib import ndpointer
from encapsulateSharedMethods import *

def displayPMCResult2D(myDll, pPMC, X1, X2, lenResult):
    classA = []
    classB = []

    # Predict points to test if Model is working 
    for x1 in X1:
        for x2 in X2: 
            predictX = np.array([x1, x2])
            datasetTmp = datasetToVector(myDll, predictX, 1)
            value = predictPMCClassification(myDll, pPMC, datasetTmp, 1, lenResult)
            if value[0] > 0:
                classA.append(tuple([x1, x2]))
            else:
                classB.append(tuple([x1, x2]))

    # Display points for each class
    plt.scatter(
        get(0, classA),
        get(1, classA),
        color="#bbdefb"
    )
    plt.scatter(
        get(0, classB),
        get(1, classB),
        color="#ffcdd2"
    )

# Create & Allocate PMC Model using structure (example : [2, 3, 1])
def createPMCModel(myDll, pmcStruct):
    arrStruct = (c_int * len(pmcStruct))(*pmcStruct)
    myDll.createPMCModel.argtypes = [ POINTER(ARRAY(c_int, len(pmcStruct))), c_uint ]
    myDll.createPMCModel.restype = c_void_p
    pPMC = myDll.createPMCModel( arrStruct, len(pmcStruct) )
    return pPMC

# Fit PMC with regression version
def fitPMCRegression(myDll, pPMC, pMatrixX, pMatrixY, row, alpha, epochs, display):
    myDll.fitPMCRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_double, c_int, c_int ]
    myDll.fitPMCRegression.restype = c_double								
    error = myDll.fitPMCRegression( pPMC, pMatrixX, pMatrixY, row, alpha, epochs, display )
    return error

# Fit PMC with classification version
def fitPMCClassification(myDll, pPMC, pMatrixX, pMatrixY, row, alpha, epochs, display ):
    myDll.fitPMCClassification.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_double, c_int, c_int ]
    myDll.fitPMCClassification.restype = c_double								
    error = myDll.fitPMCClassification( pPMC, pMatrixX, pMatrixY, row, alpha, epochs, display ) 
    return error

# Predict PMC with classification
def predictPMCClassification(myDll, pPMC, datasetVector, needResult, lenResult):
    myDll.predictPMCClassification.argtypes = [ c_void_p, c_void_p, c_int ]
    myDll.predictPMCClassification.restype = ndpointer(dtype=c_double, shape=(lenResult,))
    result = myDll.predictPMCClassification( pPMC, datasetVector, needResult )
    return result

# Predict PMC with regression
def predictPMCRegression(myDll, pPMC, datasetVector, needResult, lenResult):
    myDll.predictPMCRegression.argtypes = [ c_void_p, c_void_p, c_int]
    myDll.predictPMCRegression.restype = ndpointer(dtype=c_double, shape=(lenResult,))
    result = myDll.predictPMCRegression( pPMC, datasetVector, needResult )
    return result

# Delete / free PMC Model
def deletePMCModel(myDll, pPMC):
    myDll.deletePMCModel.argtypes = [ c_void_p ]
    myDll.deletePMCModel( pPMC )

# Load Weights PMC With CSV
def loadPMCWithCSV(myDll, pathPMC):
    myDll.loadPMCWithCSV.restype = [c_void_p ]
    myDll.loadPMCWithCSV.argtypes = [ c_char_p ]
    pPMC = myDll.loadPMCWithCSV( pathPMC.encode('utf-8') )
    return pPMC

def savePMCInCSV(myDll, pathSavePMC, pPMC):
    myDll.savePMCInCSV.argtypes = [ c_char_p, c_void_p ]
    myDll.savePMCInCSV( pathSavePMC.encode('utf-8'), pPMC )