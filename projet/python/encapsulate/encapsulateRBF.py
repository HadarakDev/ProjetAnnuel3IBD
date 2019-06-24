def createNaiveRBFModel(myDll, inputCountPerSample):
    myDll.createNaiveRBFModel.argtypes = [ c_uint ]
    myDll.createNaiveRBFModel.restype = c_void_p
    pRBF = myDll.createNaiveRBFModel( inputCountPerSample )
    return pRBF

def fitNaiveRBFRegression(myDll, pRBF, pMatrixX, pMatrixY, gamma):
    myDll.fitNaiveRBFRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_double ]							
    myDll.fitNaiveRBFRegression( pRBF, pMatrixX, pMatrixY, gamma )

def predictNaiveRBFRegression(myDll, pRBF, datasetVector):
    myDll.predictNaiveRBFRegression.argtypes = [ c_void_p, c_void_p]
    myDll.predictNaiveRBFRegression.restype = c_double
    result = myDll.predictNaiveRBFRegression( pRBF, datasetVector )
    return result

def fitNaiveRBFClassification(myDll, pRBF, pMatrixX, pMatrixY, gamma):
    myDll.fitNaiveRBFClassification.argtypes = [ c_void_p, c_void_p, c_void_p, c_double ]							
    myDll.fitNaiveRBFClassification( pRBF, pMatrixX, pMatrixY, gamma)

def predictNaiveRBFClassification(myDll, pRBF, datasetVector):
    myDll.predictNaiveRBFClassification.argtypes = [ c_void_p, c_void_p]
    myDll.predictNaiveRBFClassification.restype = c_double
    result = myDll.predictNaiveRBFClassification( pRBF, datasetVector )
    return result

def deleteNaiveRBFModel(myDll, pRBF):
    myDll.deleteNaiveRBFModel.argtypes = [ c_void_p ]
    myDll.deleteNaiveRBFModel( pRBF )

