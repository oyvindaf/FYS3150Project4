import sys
import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.font_manager
from itertools import groupby
from collections import Counter



def readfile(file, skip = 0):
    o = open(file) # opens

    Cycle_list = []
    E_list = []
    M_list = []
    Accepted_list = []

    for i in range(skip):
        o.readline()

    for line in o:
        line = line.split()

        Cycle_list.append(float(line[0]))
        E_list.append(float(line[1]))
        M_list.append(float(line[2]))
        Accepted_list.append(float(line[3]))

    return np.array(Cycle_list), np.array(E_list), np.array(M_list), np.array(Accepted_list)






Cycle_list, E_list, M_list, Accepted_list = readfile( sys.argv[1] )

new_E_list = E_list[1000:]

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.hist(new_E_list, density = True)
plt.xlabel('Energy')
plt.ylabel('P(E)')
plt.title('Probability distribution of energy states')
plt.tight_layout()
plt.savefig('testingtesting.pdf')
plt.close()

plt.plot(new_E_list)
plt.xlabel('Energy')
plt.ylabel('P(E)')
plt.title('Probability distribution of energy states')
plt.tight_layout()
plt.savefig('testingtesting2.pdf')
plt.close()

plt.subplot(211)
plt.semilogx(Cycle_list, E_list, label = 'E / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Energy')
plt.title('Plot of energy versus cycles for L = 20')
plt.legend()
plt.tight_layout()

plt.subplot(212)
plt.semilogx(Cycle_list, M_list, label = 'M / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Magnetization')
plt.title('Plot of magnetization versus cycles for L = 20')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing1.pdf')
plt.close()

plt.semilogx(Cycle_list, Accepted_list, label = 'Accepted / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Acceptance')
plt.title('Plot of accepted states versus cycles for L = 20')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing2.pdf')
plt.close()
