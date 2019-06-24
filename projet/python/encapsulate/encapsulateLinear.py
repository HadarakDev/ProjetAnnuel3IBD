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
    predictResponse = myDll.predictLinearClassification( ArrayWeight, pMatrixX )
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
def deleteDatasetMatrix(pMatrixX, pMatrixY):
    myDll.deleteDatasetMatrix.argtypes = [ c_void_p, c_void_p ]
    myDll.deleteDatasetMatrix( pMatrixX, pMatrixY )

# Deallocate lienar weight matrix
def deleteLinearModel(pArrayWeight):
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