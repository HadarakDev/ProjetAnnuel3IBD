#Parametre individuel MERCI DE METTRE UN GIT IGNORE SUR CE FICHIER

#Chemin DLL
#pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Debug/ML_Library.dll"

#pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Debug/ML_Library.dll"
pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

#tatane

#pathDatasetTrain = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/dataset/minusLotte/"
#pathDatasetPredict = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/dataset/minusLotte/"

#nico

pathDatasetTrain = "C:/Users/nico_/Documents/ConvertedImages/SplittedMinus/train/"
pathDatasetPredict = "C:/Users/nico_/Documents/ConvertedImages/SplittedMinus/test/"

pathSaveWeights = "C:/Users/nico_/Documents/ConvertedImages/"

# pathDatasetTrain = "C:/Users/nico_/Documents/ConvertedImages/ResizedLotte/"
# pathDatasetPredict = "C:/Users/nico_/Documents/ConvertedImages/ResizedLotte/"
#information dataset
# pathDataset = "D:/Cours/3IBD/projetAnnuel/projet/tmp/train/"
component  = 1
# sizeImage = 490 * 357
#sizeImage = 100 * 50
imageW = 100
imageH = 50  
numberImageTrain = 400
numberImagePredict = 40
inputCountPerSample = (imageW * imageH * component)

finalSaveWeights = pathSaveWeights + "weights_" + str(inputCountPerSample) + "_" + str(imageW) + "_" + str(imageH) + "_" + str(numberImageTrain) + ".csv"
weights = pathSaveWeights + "weights_5000_100_50_400.csv"