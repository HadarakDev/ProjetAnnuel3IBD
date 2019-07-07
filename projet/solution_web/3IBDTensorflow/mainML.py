from utilsImage import *
from frameworkPredict import *
import numpy as np

def getTableResult(pathImg, crop=False):

    results = []
    # Get pixels images
    predictX = np.array(resize_and_get_pixels_from_image(pathImg)).reshape(1, width * height * color)

    # Normalise pixels
    predictX = predictX / (255 * 40000)
    print(predictX)

    # model Lineare
    myResult = "NA"
    frameworkResult = int(getLinearResultFromFramework(predictX, crop) * 255 * 40000)
    results.append({"nom": "Modele lineaire", "implement": myResult, "framework": frameworkResult})

    # model PMC
    myResult = "NA"
    frameworkResult = int(getPMCResultFromFramework(predictX, crop) * 255 * 40000)
    results.append({"nom": "PMC", "implement": myResult, "framework": frameworkResult})

    results.append({"nom": "RBF", "implement": "NA", "framework": "NA"})
    results.append({"nom": "SVR", "implement": "NA", "framework": "NA"})

    return results

def getMLResults(pathImg, pathImgCrop, modele=None):

    results = {"models": None, "modelsHead": None}
    results["models"] = getTableResult(pathImgCrop)
    results["modelsHead"] = getTableResult(pathImgCrop, crop=True)


    print(results)


    return results