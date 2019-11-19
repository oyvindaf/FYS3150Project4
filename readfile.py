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
Cycle_list2, E_list2, M_list2, Accepted_list2 = readfile(sys.argv[2])

# new_E_list = E_list[10000:]
# new_E_list2 = E_list2[10000:]
# new_M_list = M_list[10000:]
# new_M_list2 = M_list2[10000:]
# Cycle_list = Cycle_list[10000:]
# Cycle_list2 = Cycle_list


# energies, frequencies = np.unique(new_E_list, return_counts = True)
#
# probability = energies/np.sum(energies)

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

# plt.bar(frequencies, energies)
# plt.xlabel('Energy')
# plt.ylabel('P(E)')
# plt.title('Probability distribution of energy states')
# plt.tight_layout()
# plt.savefig('testingtesting.pdf')
# plt.close()

# plt.plot(new_E_list)
# plt.xlabel('Energy')
# plt.ylabel('P(E)')
# plt.title('Probability distribution of energy states')
# plt.tight_layout()
# plt.savefig('testingtesting2.pdf')
# plt.close()

#plt.subplot(211)
plt.semilogx(Cycle_list, E_list, label = 'Disordered')
plt.semilogx(Cycle_list2, E_list2, label = 'Ordered')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Energy')
plt.title('Energy for T = 2.4')
plt.legend()
plt.tight_layout()
plt.savefig('ferdig_resultater/2C_energyT24.pdf')
plt.close()

# plt.subplot(212)
plt.semilogx(Cycle_list, M_list, label = 'Disordered')
plt.semilogx(Cycle_list2, M_list2, label = 'Ordered')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Magnetization')
plt.title('Magnetization for T = 2.4')
plt.legend()
plt.tight_layout()
plt.savefig('ferdig_resultater/2C_magnetizationT24.pdf')
plt.close()

plt.semilogx(Cycle_list, Accepted_list, label = 'Ordered')
plt.semilogx(Cycle_list2, Accepted_list2, label = 'Disordered')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Acceptance')
plt.title('Plot of accepted states versus cycles for T = 2.4')
plt.legend()
plt.tight_layout()
plt.savefig('ferdig_resultater/2C_acceptedT24.pdf')
plt.close()
