from ctypes import *
from numpy.ctypeslib import ndpointer
import os
from data import *
from utils import *
from params import *

if __name__ == "__main__":
    myDll = CDLL(pathDLL)
    # imagesPath = os.listdir(pathDataset)
    # print(imagesPath)
    tmpImages = ["0_1_0_0_0.jpg", "0_1_0_0_29.jpg", "0_1_0_0_83.jpg"]

    paths = convertListToString(tmpImages)
    print(paths)
    # imagesPathFinal = matrixToArray(imagesPath)
    param = paths.encode('utf-8')
    myDll.getDatasetX.argtypes = [ c_char_p , c_uint, c_uint ]
      #myDll.getDatasetX.restype = [ ]
    myDll.getDatasetX(param, sizeImage, 3)
