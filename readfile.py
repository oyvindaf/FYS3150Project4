import sys
import matplotlib.pyplot as plt


o = open("unordered_T1_L20.txt") # opens

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


plt.plot(Cycle_list, E_list, label = 'E / Cycles')
plt.legend()
plt.show()

plt.plot(Cycle_list, M_list, label = 'M / Cycles')
plt.legend()
plt.show()

plt.plot(Cycle_list, Accepted_list, label = 'Accepted / Cycles')
plt.legend()
plt.show()
#print(Cycle_list)
#print(E_list)
#print(M_list)
#print(Accepted_list)
