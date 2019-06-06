from ctypes import *
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
    X = [ 6, 2 ]
    Y = [ 2, 1 ]

    myDll = CDLL(pathDLL)
    myDll.createPMCModel.argtypes = [POINTER(ARRAY(c_int, lenPMC)), c_uint]
    myDll.createPMCModel.restype = c_void_p

    W = myDll.createPMCModel(pmcArray, lenPMC)

    # myDll.displayPmcModel.argtypes = [c_void_p]
    # myDll.displayPmcModel(W)
    myDll.datasetToVector.argtypes = [c_double_p, c_uint, c_uint]
    myDll.datasetToVector.restype = c_void_p
    arr_tmp = (c_double * 2)(*X)
    datasetTmp = myDll.datasetToVector(arr_tmp, len(X), 1)


    myDll.predictPMC.argtypes = [ c_void_p, c_void_p]
    myDll.predictPMC.restype = ndpointer(dtype=c_double, shape=(pmcStruct[-1],))
    value = myDll.predictPMC(W, datasetTmp)
