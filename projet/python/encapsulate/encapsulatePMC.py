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
    myDll.predictPMCClassification.argtypes = [ c_void_p, c_void_p, c_int, c_int ]
    myDll.predictPMCClassification.restype = ndpointer(dtype=c_double, shape=(lenResult, 1))
    result = myDll.predictPMCClassification( pPMC, datasetVector, needResult )
    return result

# Predict PMC with regression
def predictPMCRegression(myDll, pPMC, datasetVector, needResult, lenResult):
    myDll.predictPMCRegression.argtypes = [ c_void_p, c_void_p, c_int, c_int ]
    myDll.predictPMCRegression.restype = ndpointer(dtype=c_double, shape=(lenResult, 1))
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