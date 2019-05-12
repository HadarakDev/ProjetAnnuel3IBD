# Linear Model : KO
# MLP (1, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np
from utilsRegression import *

#datas des points a tester
X = np.array([ [1], [2], [3] ])
Y = np.array([ 2, 3, 2.5])

w1, w2 = linearRegression(X,Y, "nonLinearSimple2D.csv")

#droite à tracer
x = np.linspace(0, 4, 100)
y = 1 * w1 + x * w2

#affichage
plt.plot(x, y, color="green")
plt.scatter(X, Y, color='blue')
plt.show()
plt.clf()
