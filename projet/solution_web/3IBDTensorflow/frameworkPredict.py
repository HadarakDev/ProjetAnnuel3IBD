import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.models import load_model
import h5py
from utilsImage import *


def getLinearResultFromFramework(predictX, crop):

    if crop:
        model = load_model(crop_linear_model_framework_to_load)
    else:
        model = load_model(linear_model_framework_to_load)

    return model.predict(predictX)[0][0]

def getPMCResultFromFramework(predictX, crop):

    if crop:
        model = load_model(crop_PMC_model_framework_to_load)
    else:
        model = load_model(PMC_model_framework_to_load)
    return model.predict(predictX)[0][0]