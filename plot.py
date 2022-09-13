import numpy as np
import scipy.integrate as integrate
import matplotlib.pyplot as plt
from sys import exit


dt = 5e-2
crr = np.loadtxt("crr.dat")
cvr = np.loadtxt("cvr.dat")
cvv = np.loadtxt("cvv.dat")
t = np.loadtxt("t.dat") * dt
N = t.shape[0]

def msd(t):
  v2 = 1
  A = 2 * t
  A += v2 * (1 - np.exp(-t))**2
  A -= 3 + np.exp(-2*t) - 4 * np.exp(-t)
  return A

y = msd(t)
plt.plot(t[1:],y[1:]/(2 * t[1:]))

plt.scatter(t[1:], crr[1:]/(2 * t[1:]), color="blue", label="crr/(2 t)")
plt.scatter(t, cvv, color="black", label="cvv")
plt.scatter(t, cvr, color="red", label="cvr")


n = 22 
Dvv = integrate.simps(cvv[:n], t[:n])
print(Dvv)


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


plt.xlim([dt/2, t[-1]*2.0])
plt.xscale('log')
#plt.yscale('log')

plt.legend()
plt.show()
