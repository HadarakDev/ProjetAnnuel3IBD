from ctypes import *

pathSaveWeights = "C:/Users/nico_/Documents/ConvertedImages/"

# pathDatasetTrain = "C:/Users/nico_/Documents/ConvertedImages/ResizedLotte/"
# pathDatasetPredict = "C:/Users/nico_/Documents/ConvertedImages/ResizedLotte/"
#information dataset
# pathDataset = "D:/Cours/3IBD/projetAnnuel/projet/tmp/train/"
component  = 1
imageW = 100
imageH = 50
# imageW = 490
# imageH = 357 
numberImageTrain = 400
numberImagePredict = 40
inputCountPerSample = (imageW * imageH * component)

finalSaveWeights = pathSaveWeights + "weights_" + str(inputCountPerSample) + "_" + str(imageW) + "_" + str(imageH) + "_" + str(numberImageTrain) + ".csv"
weights = pathSaveWeights + "weights_5000_100_50_400.csv"

#### EVALUATE  ####
startNumberImageTrain = 20
evaluateFactor = 2
pathLog = "C:/Users/nico_/Documents/ConvertedImages/EvaluateModels.txt"
numberImagePredictEvaluate = 1388

##### PMC ####

pmcStruct = [2,3, 2,1]
arrStruct= (c_int * len(pmcStruct))(*pmcStruct)

#### CTYPES ####
c_double_p = POINTER(c_double)

#### DLL PATHS ####
#nico
pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

#tatane
pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Debug/ML_Library.dll

#### DATASET PATHS ####

#nico
pathDatasetTrain = "C:/Users/nico_/Documents/ConvertedImages/SplittedMinus/train/"
pathDatasetPredict = "C:/Users/nico_/Documents/ConvertedImages/SplittedMinus/test/"

#tatane
#pathDatasetTrain = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/dataset/minusLotte/"
#pathDatasetPredict = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/dataset/minusLotte/"
