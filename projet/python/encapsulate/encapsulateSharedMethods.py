from ctypes import *
import matplotlib.pyplot as plt

def plot_dataset_old(X, Y):
    plt.plot(X[Y > 0, 0], X[Y > 0, 1], 'bx')
    plt.plot(X[Y < 0, 0], X[Y < 0, 1], 'rx')

def plot_dataset(X, Y):
    plt.plot(X[:, 0], X[:, 1], 'bx')

def matrixToArray(matrix):
    ret = []
    for el in matrix:
        ret.extend(el)
    return ret

# Python Function to get coordinates
def get(i, l):
    return [z[i] for z in l]


# Get matrix X from imagesPath
def getDatasetX(myDll, imagesPath, imageW, imageH, numberImage, component):
    imagePathUTF = imagesPath.encode('utf-8')
    myDll.getDatasetX.argtypes = [c_char_p, c_uint, c_uint, c_uint, c_uint]
    myDll.getDatasetX.restype = c_void_p
    pMatrixX = myDll.getDatasetX( imagePathUTF, imageW, imageH, numberImage, component )
    return pMatrixX

# Get matrix Y from imagesPath
def getDatasetY(myDll, imagesPath, numberImage):
    imagePathUTF = imagesPath.encode('utf-8')
    myDll.getDatasetY.restype = c_void_p
    myDll.getDatasetY.argtypes = [c_char_p, c_uint]
    pMatrixY = myDll.getDatasetY(imagePathUTF, numberImage)
    return pMatrixY

# Get both matrix X & Y from imagesPath
def prepareDataset(myDll, imagesPath, imageW, imageH, numberImage, component):	
    imagePathUTF = imagesPath.encode('utf-8')
    myDll.getDatasetX.argtypes = [c_char_p, c_uint, c_uint, c_uint, c_uint]
    myDll.getDatasetX.restype = c_void_p
    pMatrixX = myDll.getDatasetX( imagePathUTF, imageW, imageH, numberImage, component )

    myDll.getDatasetY.restype = c_void_p
    myDll.getDatasetY.argtypes = [c_char_p, c_uint]
    pMatrixY = myDll.getDatasetY( imagePathUTF, numberImage )
    return pMatrixX, pMatrixY

# Load point into matrix
def loadTestCase(myDll, X, row, col, bias):
    myDll.loadTestCase.restype = c_void_p
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
    pMatrixX = myDll.loadTestCase( (c_double * len(X))(*X), row,  col, bias )
    return pMatrixX

# Dataset to Vector ( double * => vectorXd)
def datasetToVector(myDll, dataset, bias):
    size = len(dataset)
    arr = (c_double * size)(*dataset)
    c_double_p = POINTER(c_double)
    myDll.datasetToVector.argtypes = [ c_double_p, c_uint, c_uint ]
    myDll.datasetToVector.restype = c_void_p
    vector = myDll.datasetToVector( arr, size, bias )
    return vector