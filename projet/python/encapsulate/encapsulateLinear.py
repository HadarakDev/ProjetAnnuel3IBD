from ctypes import *
import numpy as np
import matplotlib.pyplot as plt
from encapsulateSharedMethods import *

def displayLinearRegResult3D(myDll, pArrayWeight, ax, maxRange):
    XX, YY, ZZ = [], [], []
    for x1 in range(0, maxRange, 10):
        for x2 in range(0, maxRange, 10):
            x1 /= 100
            x2 /= 100
            XX.append(x1)
            YY.append(x2)
            predictX = np.array([x1, x2])
            pMatrixX = loadTestCase(myDll, predictX, 1, len(predictX), 1)
            value = predictLinearRegression(myDll, pArrayWeight, pMatrixX)
            ZZ.append(value)
    ax.plot_trisurf(XX, YY, ZZ, lw=0, color='#bbdefb', alpha=0.5)

def displayLinearRegResult2D(myDll, pArrayWeight, X1, X2):
    for x1 in X1:
        predictX = np.array([x1])
        pMatrixX = loadTestCase(myDll, predictX, 1, len(predictX), 1)
        value = predictLinearRegression(myDll, pArrayWeight, pMatrixX)     
        plt.scatter(x1, value, color='#bbdefb')

def displayLinearClassifResult2DTripleClass(myDll, pArrayWeight1, pArrayWeight2, pArrayWeight3, X1, X2):
    classA = []
    classB = []
    classC = []

    for x1 in X1:
        for x2 in X2: 
            predictX = np.array([x1, x2])
            pMatrixX = loadTestCase(myDll, predictX, 1, len(predictX), 1)
            value1 = predictLinearClassification(myDll, pArrayWeight1, pMatrixX)
            value2 = predictLinearClassification(myDll, pArrayWeight2, pMatrixX)
            value3 = predictLinearClassification(myDll, pArrayWeight3, pMatrixX)
            if value1 > value2 and value1 > value3:
                classA.append(tuple([x1, x2]))
            elif value2 > value1 and value2 > value3:
                classB.append(tuple([x1, x2]))
            elif value3 > value1 and value3 > value2:
                classC.append(tuple([x1, x2]))

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
    plt.scatter(
        get(0, classC),
        get(1, classC),
        color="#c8e6c9"
    )

def displayLinearClassifResult2D(myDll, pArrayWeight, X1, X2):
    classA = []
    classB = []
    
    # Predict points to test if Model is working 
    for x1 in X1:
        for x2 in X2: 
            predictX = np.array([x1, x2]).tolist()
            pMatrixX = loadTestCase(myDll, predictX, 1, len(predictX), 1)
            value = predictLinearClassification(myDll, pArrayWeight, pMatrixX)
            if value > 0:
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

# Create Linear (weights matrix)
def createLinearModel(myDll, inputCountPerSample):
    myDll.createLinearModel.argtypes = [c_int32]
    myDll.createLinearModel.restype = c_void_p
    pArrayWeight = myDll.createLinearModel( inputCountPerSample )
    return pArrayWeight

# Fit linear classification with rosenblatt
def fitLinearClassification(myDll, pArrayWeight,pMatrixX, pMatrixY, row, col, alpha, epochs, display):
    myDll.fitLinearClassification.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int, c_double, c_int, c_int ]
    myDll.fitLinearClassification.restype = c_double								
    error = myDll.fitLinearClassification( pArrayWeight,pMatrixX, pMatrixY, row, col, alpha, epochs, display )
    return error

# Predict linear classification
def predictLinearClassification(myDll, pArrayWeight, pMatrixX):
    myDll.predictLinearClassification.argtypes = [ c_void_p, c_void_p ]
    myDll.predictLinearClassification.restype = c_double
    predictResponse = myDll.predictLinearClassification( pArrayWeight, pMatrixX )
    return predictResponse

# Fit linear regression with Moore pseudo inverse 
def fitLinearRegression(myDll, pArrayWeight, pMatrixX, pMatrixY, row, col):
    myDll.fitLinearRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int ]
    myDll.fitLinearRegression.restype = c_double								
    error = myDll.fitLinearRegression( pArrayWeight, pMatrixX, pMatrixY, row, col )
    return error  

# Predict linear regression
def predictLinearRegression(myDll, pArrayWeight, pMatrixX):
    myDll.predictLinearRegression.argtypes = [ c_void_p, c_void_p]
    myDll.predictLinearRegression.restype = c_double
    predictResponse = myDll.predictLinearRegression( pArrayWeight, pMatrixX )
    return predictResponse

# Deallocate matrix X & Y 
def deleteDatasetMatrix(myDll, pMatrixX, pMatrixY):
    myDll.deleteDatasetMatrix.argtypes = [ c_void_p, c_void_p ]
    myDll.deleteDatasetMatrix( pMatrixX, pMatrixY )

# Deallocate lienar weight matrix
def deleteLinearModel(myDll, pArrayWeight):
    myDll.deleteLinearModel.argtypes = [ c_void_p ]
    myDll.deleteLinearModel( pArrayWeight )

# Load Linear Model from CSV
def loadLinearWeightsWithCSV(pathLoad, inputCountPerSample):
    myDll.loadWeightsWithCSV.argtypes = [c_char_p, c_void_p]
    myDll.loadWeightsWithCSV.restype = c_void_p
    pArrayWeight = myDll.loadWeightsWithCSV( pathLoad.encode('utf-8'), inputCountPerSample )
    return pArrayWeight

# Save Linear Model In CSV
def saveLinearWeightsInCSV(pathSave, pArrayWeight):
    myDll.saveLinearWeightsInCSV.argtypes = [c_char_p, c_void_p]
    myDll.saveWeightsInCSV( pathSave.encode('utf-8'), pArrayWeight )