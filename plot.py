import numpy as np
import matplotlib.pyplot as plt
from sys import exit


crr = np.loadtxt("crr.dat")
t = np.linspace(0, (1e-2)*crr.shape[0], crr.shape[0])

def msd(t):
  return 2 * t - 3 + 4 * np.exp(-t) - np.exp(-2 * t)

def msd2(t):
  v2 = 1
  A = 2 * t
  A += v2 * (1 - np.exp(-t))**2
  A -= 3 + np.exp(-2*t) - 4 * np.exp(-t)
  return A

y = msd2(t)
plt.plot(t,y)

plt.scatter(t, crr, color="black")


tb = np.linspace(0.005, 0.5)
y = 1 * tb**2
#plt.plot(tb, y, ls=":")

td = np.linspace(2, 20)
y = 10 * td
#plt.plot(td, y, ls=":")

#plt.xlim([t[0], t[-1]*2])
#plt.xscale('log')
#plt.yscale('log')
plt.show()
