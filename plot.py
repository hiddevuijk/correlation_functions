import numpy as np
import matplotlib.pyplot as plt
from sys import exit


dt = 1e-2
#cvv = np.loadtxt("cvv.dat")
#cvr = np.loadtxt("cvr.dat")
crr2 = np.loadtxt("crr2.dat")[1:]
crr4 = np.loadtxt("crr4.dat")[1:]
c =  crr4 / (3 * crr2**2)
c -= 1
t = np.loadtxt("t2.dat")[1:] * dt
c = np.gradient(crr2,t) / 2.0

#t = np.linspace(0, dt * crr.shape[0], crr.shape[0])

def msd(t):
  v2 = 1
  A = 2 * t
  A += v2 * (1 - np.exp(-t))**2
  A -= 3 + np.exp(-2*t) - 4 * np.exp(-t)
  return A

y = msd(t)
#plt.plot(t,y)

#plt.scatter(t, crr, color="black")
#plt.plot(t, cvv, color="black", label="cvv")
#plt.plot(t, cvr, color="red", label="cvr")
plt.scatter(t, c, color="blue", label="crr")


#Drr1 = crr[-1] / ( 2 * t[-1])
#n = 100
#Drr2 = (crr[-1] - crr[-(1+n)]) / ( 2 *dt * n)
#Dvr1 = cvr[-1]
#N = cvr.shape[0]
#print(t[N-n])
#Dvr2 = np.sum(cvr[N-n:])/cvr[N-n:].shape[0]
#Dvv = np.sum(cvv) * dt
#
#print("Dvv=",Dvv)
#print("Dvr1=",Dvr1)
#print("Dvr2=",Dvr2)
#print("Drr1=",Drr1)
#print("Drr2=",Drr2)

#plt.axhline(0)
#plt.axhline(1)


#plt.xlim([0, t[-1]*1.1])
#plt.xscale('log')
#plt.yscale('log')

plt.legend()
plt.show()
