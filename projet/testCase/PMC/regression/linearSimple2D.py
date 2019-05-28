# Linear Model : OK
# MLP (1, 1)   : OK

from utilsRegression import *
import matplotlib.pyplot as plt
import numpy as np


pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"
#pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

myDll = CDLL(pathDLL)

#parametre
alpha = 0.1
epochs = 10000
display = 100

#datas des points a tester
X = np.array([ [1], [2] ])
Y = np.array([ 2, 3])

#recuperer les poids
pArrayWeight = pmcRegression(myDll, X, Y, alpha, epochs, display, [1, 1])

#affichage des points
X1 = np.linspace(0, 4, 60)
for x1 in X1:
   
	predictX = np.array([x1])
	value = predict(myDll, myDll.predictPMCRegression, predictX, pArrayWeight)        
	plt.scatter(x1, value, color='#bbdefb')
      

plt.scatter(X, Y, color='red')
plt.show()
plt.clf()
