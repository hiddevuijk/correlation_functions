import numpy as np
import matplotlib.pyplot as plt
from sys import exit


x = np.loadtxt("x.dat")
v = np.loadtxt("v.dat")

plt.plot(x)
plt.show()
