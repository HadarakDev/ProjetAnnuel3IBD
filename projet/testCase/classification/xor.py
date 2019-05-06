# Linear Model    : KO
# MLP (2, 2, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np

#recupérer les poids
w1 = 2		#biais
w2 = -2

#datas des points a tester
X = np.array([[1, 0], [0, 1], [0, 0], [1, 1]])
Y = np.array([1, 1, -1, -1])

#droite à tracer
x = np.linspace(-0.5, 1.5, 100)
y = 1 * w1 + x * w2

plt.fill_between(x, 10, y, color="#bbdefb")
plt.fill_between(x, -10, y, color="#ffcdd2")
plt.scatter(X[0:2, 0], X[0:2, 1], color='blue')
plt.scatter(X[2:4,0], X[2:4,1], color='red')
plt.plot(x,y, color="green")
plt.show()
plt.clf()
