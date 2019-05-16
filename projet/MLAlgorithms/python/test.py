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

    myDll = CDLL(pathDLL)

    # X = np.array([ [1], [2] ])
    
    # tmp = X.tolist()
    # tmpX, lenX = matrixToArray(tmp)
    
    # c_double_p = POINTER(c_double)
    # myDll.loadWeightsWithCSV.argtypes = [c_double_p, c_uint, c_uint]
    # myDll.loadWeightsWithCSV.restype = c_void_p

    # myDll.loadWeightsWithCSV(tmpX, X.shape[0], X.shape[1])
    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, 3)), c_uint, c_uint]
    myDll.createPMCModel.restype = c_void_p
    l = [2,2,2]
    arr = (c_int * len(l))(*l)
    myDll.createPMCModel(arr, 3, 12)
