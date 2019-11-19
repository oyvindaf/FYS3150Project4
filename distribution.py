import numpy as np
import matplotlib.pyplot as plt
import sys


def readfile(file, skip = 50000):
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

Cycle_list, E_list, _,_ = readfile(sys.argv[1])

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.hist(E_list, density = True, bins = 30)
plt.xlabel('Energy')
plt.ylabel('$P(E)$')
plt.title('Probability distribution of energy states, T = 1')
plt.tight_layout()
plt.savefig('4DhistT1.pdf')
plt.close()
