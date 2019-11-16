import sys
import matplotlib.pyplot as plt


o = open("testing.txt") # opens

Cycle_list = []
E_list = []
M_list = []
Accepted_list = []


skip = 10
for i in range(skip):
    o.readline()

for line in o:
    o.readline()
    o.readline()
    o.readline()
    line = line.split()

    Cycle_list.append(float(line[0]))
    E_list.append(float(line[1]))
    M_list.append(float(line[2]))
    Accepted_list.append(float(line[3]))


plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.plot(Cycle_list, E_list, label = 'E / Cycles')
plt.grid()
plt.xlabel('Cycles')
plt.ylabel('Energy')
plt.title('Plot of energy versus cycles for L = 2')
plt.legend()
plt.tight_layout()
plt.savefig('plots/L2Testing1.pdf')
plt.close()

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
