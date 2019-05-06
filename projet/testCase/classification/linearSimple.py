# Linear Model : OK
# MLP (2, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np


#recuperer les poids
w1 = -3		#biais
w2 = 2.25

#datas des points a tester
X = np.array([ [1, 1], [2, 3], [3, 3] ])
Y = np.array([ 1, -1, -1 ])

#droite à tracer
x = np.linspace(0, 4, 100)
y = 1 * w1 + x * w2

#affichage
plt.plot(x, y, color="green")
plt.fill_between(x, 10, y, color="#bbdefb")
plt.fill_between(x, -10, y, color="#ffcdd2")
plt.scatter(X[0:2, 0], X[0:2, 1], color='blue')
plt.scatter(X[2:4,0], X[2:4,1], color='red')
plt.show()
plt.clf()
