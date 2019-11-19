import numpy as np
import matplotlib.pyplot as plt
import scipy.stats
T = np.array([2.31,2.3,2.285,2.28])
T_L = [T[0]/40, T[1]/60, T[2]/80, T[3]/100]


slope,intercept,_,_,_ = scipy.stats.linregress(T_L,T)

def approximate_func(x, a = slope, b = intercept):
    return a*x + b

x = np.linspace(-0.025,0.075,1000)
func = approximate_func(x)


plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.scatter(T_L,T)
plt.plot(x,func)
plt.grid()
plt.xlabel('$ T/L $')
plt.ylabel('$T$')
plt.title('Best fit line')
plt.tight_layout()
plt.savefig('regplot.pdf')
