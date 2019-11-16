import sys
import matplotlib.pyplot as plt
from collections import Counter



def readfile(file, skip = 10):
    o = open(file) # opens

    Cycle_list = []
    E_list = []
    M_list = []
    Accepted_list = []


    for line in o:
        line = line.split()

        Cycle_list.append(float(line[0]))
        E_list.append(float(line[1]))
        M_list.append(float(line[2]))
        Accepted_list.append(float(line[3]))

    return Cycle_list, E_list, M_list, Accepted_list






Cycle_list, E_list, M_list, Accepted_list = readfile("testing.txt")

print(Counter(E_list))

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.subplot(211)
plt.plot(Cycle_list, E_list, label = 'E / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Energy')
plt.title('Plot of energy versus cycles for L = 2')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing1.pdf')
plt.close()

plt.subplot(212)
plt.plot(Cycle_list, M_list, label = 'M / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Magnetization')
plt.title('Plot of magnetization versus cycles for L = 2')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing2.pdf')
plt.close()

plt.plot(Cycle_list, Accepted_list, label = 'Accepted / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Energy')
plt.title('Plot of energy versus cycles for L = 2')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing3.pdf')
plt.close()
