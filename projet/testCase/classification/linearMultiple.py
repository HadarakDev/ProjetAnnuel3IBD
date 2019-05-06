# Linear Model : OK
# MLP (2, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np

#recupérer les poids
w1 = 5.75		#biais
w2 = -2

#datas des points a tester
X = np.concatenate([np.random.random((50,2)) * 0.9 + np.array([1, 1]), np.random.random((50,2)) * 0.9 + np.array([2, 2])])
Y = np.concatenate([np.ones((50, 2)), np.ones((50, 2)) * -1.0])

#droite à tracer
x = np.linspace(0, 4, 100)
y = 1 * w1 + x * w2

plt.fill_between(x, 10, y, color="#bbdefb")
plt.fill_between(x, -10, y, color="#ffcdd2")
plt.scatter(X[0:50, 0], X[0:50, 1], color='red')
plt.scatter(X[50:100,0], X[50:100,1], color='blue')
plt.plot(x,y, color="green")
plt.show()
plt.clf()
