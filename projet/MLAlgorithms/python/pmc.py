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

if __name__ == "__main__":

    # X = np.array([ [1, 1], [2, 2], [3, 1] ])
    #     Y = np.array([ 2, 3, 2.5 ])
    K = [4]
    # X = [1, 1, 2, 2, 3, 1]
    # Y = [2, 3, 2.5]
    X = [ 6, 2 ]
    Y = [ 2, 3 ]
    Xnp = np.array([ [1], [2] ])
    Ynp = np.array([ 2, 3])

    myDll = CDLL(pathDLL)
    struct = [2, 1]
    arr_struct= (c_int * len(struct))(*struct)


    
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(X))), c_uint, c_uint, c_uint]
    myDll.loadTestCase.restype = c_void_p

    pMatrixX = myDll.loadTestCase((c_double * len(X))(*X), 2, 1, 1)
    myDll.loadTestCase.argtypes = [POINTER(ARRAY(c_double, len(Y))), c_uint, c_uint, c_uint]
    pMatrixY = myDll.loadTestCase((c_double * len(Y))(*Y), 2, 1, 0)

    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, 2)), c_uint, c_uint]
    myDll.createPMCModel.restype = c_void_p

    W = myDll.createPMCModel(arr_struct, len(struct), 1)

    myDll.fitPMCRegression.argtypes = [ c_void_p, c_void_p, c_void_p, c_int, c_int, c_double, c_int, c_int ]
    myDll.fitPMCRegression.restype = c_double								
    error = myDll.fitPMCRegression( W, pMatrixX, pMatrixY, 2, 1, 0.2, 3, 10)

    # c_double_p = POINTER(c_double)
    # myDll.datasetToVector.argtypes = [c_double_p, c_uint, c_uint]
    # myDll.datasetToVector.restype = c_void_p
    # arr_K = (c_double * len(K))(*K)
    # datasetX = myDll.datasetToVector(arr_K, len(K), 1)
    # myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    # myDll.predictPMCRegression.restype = c_double
    # print(myDll.predictPMCRegression(W, datasetX))


    allResults = []
    colors = []
    print("ICI")
    myDll.predictPMCRegression.argtypes = [c_void_p, c_void_p ]
    myDll.predictPMCRegression.restype = c_double
    for x1 in range(0, 300):
        x1 *= 0.01 
        tmpArray = [x1]
        arr_tmp = (c_double * len(tmpArray))(*tmpArray)
        datasetTmp = myDll.datasetToVector(arr_tmp, len(tmpArray), 1)
        ret = myDll.predictPMCRegression(W, datasetTmp)
        #tmpArray.append(ret)
        #allResults.append(tmpArray)
        #print( "x:%s, y:%s" % (x1,ret) )
        plt.scatter(x1, ret, color="green")

        #if maxNb is None or ret > maxNb:
         #   maxNb = ret
        #if minNb is None or ret < minNb:
         #   minNb = ret

    res = np.array([allResults])



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

	







 
