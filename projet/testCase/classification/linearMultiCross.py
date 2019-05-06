# Linear Model x3 : KO
# MLP (2, ?, ?, 3): OK

import matplotlib.pyplot as plt
import numpy as np


#recupérer les poids
w1 = 0		#biais
w2 = 0

#datas des points a tester
X = np.random.random((1000, 2)) * 2.0 - 1.0
Y = np.array([[1, 0, 0] if abs(p[0] % 0.5) <= 0.25 and abs(p[1] % 0.5) > 0.25 else [0, 1, 0] if abs(p[0] % 0.5) > 0.25 and abs(p[1] % 0.5) <= 0.25 else [0, 0, 1] for p in X])

#droite à tracer
x = np.linspace(-1.5, 1.5, 100)
y = 1 * w1 + x * w2

#affichage
plt.fill_between(x, 2, y, color="#bbdefb")
plt.fill_between(x, -2, y, color="#ffcdd2")
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][0] == 1, enumerate(X)))))[:,1], color='blue')
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][1] == 1, enumerate(X)))))[:,1], color='red')
plt.scatter(np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:,0], np.array(list(map(lambda elt : elt[1], filter(lambda c: Y[c[0]][2] == 1, enumerate(X)))))[:,1], color='grey')
plt.plot(x,y, color="green")
plt.show()
plt.clf()
