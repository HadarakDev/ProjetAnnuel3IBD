from ctypes import *
# from numpy.ctypeslib import ndpointer
import os
from data import *
from utils import *
import time
from params import *
import random
import numpy as np

if __name__ == "__main__":

    # X = np.array([ [1, 1], [2, 2], [3, 1] ])
    #     Y = np.array([ 2, 3, 2.5 ])
    K = [4, 4]
    X = [1, 1, 2, 2, 3, 1]
    Y = [2, 3, 2.5]

    myDll = CDLL(pathDLL)
    struct = [2, 1]
    arr_struct= (c_int * len(struct))(*struct)


    
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
    myDll.loadTestCase.restype = c_void_p

    pMatrixX = myDll.loadTestCase((c_double * len(X))(*X), 3, 2, 1)
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(Y))), c_uint, c_uint, c_uint]
    pMatrixY = myDll.loadTestCase((c_double * len(Y))(*Y), 3, 1, 0)

    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, 2)), c_uint, c_uint]
    myDll.createPMCModel.restype = c_void_p

    W = myDll.createPMCModel(arr_struct, len(struct), 2)

    myDll.fitPMCRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int, c_double, c_int, c_int ]
    myDll.fitPMCRegression.restype = c_double								
    error = myDll.fitPMCRegression( W, pMatrixX, pMatrixY, 3, 2, 0.1, 100000, 10)

    c_double_p = POINTER(c_double)
    myDll.datasetToVector.argtypes = [c_double_p, c_uint, c_uint]
    myDll.datasetToVector.restype = c_void_p
    arr_K = (c_double * len(K))(*K)
    datasetX = myDll.datasetToVector(arr_K, len(K), 1)

    myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    myDll.predictPMCRegression.restype = c_double
    print(myDll.predictPMCRegression(W, datasetX))







 
