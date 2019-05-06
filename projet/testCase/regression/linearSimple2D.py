# Linear Model : OK
# MLP (1, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np


#recuperer les poids
w1 = 1	#biais
w2 = 1

#datas des points a tester
X = np.array([ [1], [2] ])
Y = np.array([ 2, 3])

#droite à tracer
x = np.linspace(0, 4, 100)
y = 1 * w1 + x * w2

#affichage
plt.plot(x, y, color="green")
plt.scatter(X, Y, color='blue')
plt.show()
plt.clf()
