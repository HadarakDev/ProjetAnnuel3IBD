# Linear Model    : KO
# MLP (2, 4, 1)   : OK

import matplotlib.pyplot as plt
import numpy as np


#recupérer les poids
w1 = 0		#biais
w2 = 0

#datas des points a tester
X = np.random.random((500, 2)) * 2.0 - 1.0
Y = np.array([1 if abs(p[0]) <= 0.3 or abs(p[1]) <= 0.3 else -1 for p in X])

#droite à tracer
x = np.linspace(-1.5, 1.5, 100)
y = 1 * w1 + x * w2

#affichage
plt.fill_between(x, 3, y, color="#bbdefb")
plt.fill_between(x, -3, y, color="#ffcdd2")
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]] == 1, enumerate(X)))))[:,1], color='blue')
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]] == -1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]] == -1, enumerate(X)))))[:,1], color='red')
plt.plot(x,y, color="green")
plt.show()
plt.clf()
