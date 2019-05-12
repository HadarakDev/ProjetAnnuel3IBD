# Linear Model x3 : OK
# MLP (2, 3)      : OK

import matplotlib.pyplot as plt
import numpy as np
from utilsClassification import *
from ctypes import *

pathDLL = "C:/Users/nico_/Documents/GitHub/ProjetAnnuel3IBD/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"
#pathDLL = "D:/CloudStation/Cours/3IBD/projetAnnuel/projet/MLAlgorithms/ML_Library/x64/Release/ML_Library.dll"

myDll = CDLL(pathDLL)
#recupérer les poids


#datas des points a tester
X = np.random.random((500, 2)) * 2.0 - 1.0
Y = np.array([[1, 0, 0] if -p[0] - p[1] - 0.5 > 0 and p[1] < 0 and p[0] - p[1] - 0.5 < 0 else 
              [0, 1, 0] if -p[0] - p[1] - 0.5 < 0 and p[1] > 0 and p[0] - p[1] - 0.5 < 0 else 
              [0, 0, 1] if -p[0] - p[1] - 0.5 < 0 and p[1] < 0 and p[0] - p[1] - 0.5 > 0 else 
              [0, 0, 0]for p in X])

#droite à tracer
x = np.linspace(-1.5, 1.5, 100)
y = 1 * w1 + x * w2

#affichage
plt.fill_between(x, 3, y, color="#ffcdd2")
plt.fill_between(x, -3, y, color="#bbdefb")
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:,1], color='blue')
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:,1], color='red')
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:,1], color='green')
plt.plot(x,y, color="green")
plt.show()
plt.clf()
