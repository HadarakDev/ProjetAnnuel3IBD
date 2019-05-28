from ctypes import *
# from numpy.ctypeslib import ndpointer
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

    # X = np.array([ [1, 1], [2, 2], [3, 1] ])
    #     Y = np.array([ 2, 3, 2.5 ])
    K = [4]
    X = [1, 2]
    Y = [2, 3]
    Xnp = np.array([ [1], [2] ])
    Ynp = np.array([ 2, 3])

    # X = [ 1, 2, 3, 4 , 5 , 6 ]
    # Y = [ -1, 1, -1, 1, -1, 1]
    # Xnp = np.array([ [1], [2], [3], [4] , [5] , [6]  ])
    # Ynp = np.array([  [-1], [1], [-1], [1], [-1], [1]])
    
    # Xnp = np.random.random((500, 2)) * 2.0 - 1.0
    # Ynp = np.array([1 if abs(p[0]) <= 0.3 or abs(p[1]) <= 0.3 else -1 for p in X])
    # X = Xnp.tolist()
    # Y = Ynp.tolist()
    myDll = CDLL(pathDLL)
    
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
    myDll.loadTestCase.restype = c_void_p

    pMatrixX = myDll.loadTestCase((c_double * len(X))(*X), 2, 1, 1)
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(Y))), c_uint, c_uint, c_uint]
    pMatrixY = myDll.loadTestCase((c_double * len(Y))(*Y), 2, 1, 0)

    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, len(pmcStruct))), c_uint, c_uint]
    myDll.createPMCModel.restype = c_void_p

    W = myDll.createPMCModel(arrStruct, len(pmcStruct), 1)

    myDll.fitPMCRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int, c_double, c_int, c_int ]
    myDll.fitPMCRegression.restype = c_double								
    error = myDll.fitPMCRegression( W, pMatrixX, pMatrixY, 2, 1, 0.1, 1000, 10)

    myDll.datasetToVector.argtypes = [c_double_p, c_uint, c_uint]
    myDll.datasetToVector.restype = c_void_p

    # arr_K = (c_double * len(K))(*K)
    # datasetX = myDll.datasetToVector(arr_K, len(K), 1)
    # myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    # myDll.predictPMCRegression.restype = c_double
    # print(myDll.predictPMCRegression(W, datasetX))
    print(W)

    allResults = []
    colors = []
    ret = []
    myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    myDll.predictPMCRegression.restype = ndpointer(dtype=c_double, shape=(pmcStruct[-1],))
    for x1 in range(0,300):
        x1 *= 0.01 
        tmpArray = [x1]
        arr_tmp = (c_double * 1)(*tmpArray)
        datasetTmp = myDll.datasetToVector(arr_tmp, len(tmpArray), 1)
        ret = myDll.predictPMCRegression(W, datasetTmp)
        tmpArray.append(ret[0])
        allResults.append(tmpArray)
        plt.scatter(x1, ret[0], color="green")
    res = np.array([allResults])


myDll.deletePMC.argtypes = [ c_void_p ]
myDll.deletePMC(W)
plt.scatter(Xnp, Ynp, color='blue')
plt.show()
plt.clf()




    # for i in res:
    #    res[2] = (res[2]  - maxNb) / (maxNb - minNb)
    # print(res)
    # print(maxNb)
    # print(minNb)

    # myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    # myDll.predictPMCRegression.restype = c_double
    # print(myDll.predictPMCRegression(W, datasetX))

	







 
