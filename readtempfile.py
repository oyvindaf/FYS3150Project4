import sys
import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.font_manager
from itertools import groupby
from collections import Counter

def readfile(file):
     # opens

    temperature = []
    E_list = []
    C_v = []
    M_list = []
    M_abs_list = []
    ksi_list = []

    o = open(file)
    for line in o:
        line = line.split()

        temperature.append(float(line[0]))
        E_list.append(float(line[1]))
        C_v.append(float(line[2]))
        M_abs_list.append(float(line[3]))
        ksi_list.append(float(line[4]))
    o.close()
    return temperature, E_list, C_v, M_abs_list, ksi_list

temperature, E_list, C_v, M_abs_list, ksi_list = readfile(sys.argv[1])

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)

plt.plot(temperature, E_list)
plt.xlabel("Temperature")
plt.ylabel("Energy")
plt.title("Plot of energy versus temperature")
plt.grid()
plt.tight_layout()
plt.savefig('plots/E_T.pdf')
plt.close()

plt.plot(temperature, M_abs_list)
plt.xlabel("Temperature")
plt.ylabel("$ \langle |M| \rangle $")
plt.title("Plot of absolute magnetization versus temperature")
plt.grid()
plt.tight_layout()
plt.savefig('plots/abs(M)_T.pdf')
plt.close()

plt.plot(temperature, C_v)
plt.xlabel("Temperature")
plt.ylabel("$C_v$")
plt.title("Plot of heat capacity versus temperature")
plt.grid()
plt.tight_layout()
plt.savefig('plots/Cv_T.pdf')
plt.close()

plt.plot(temperature, ksi_list)
plt.xlabel("Temperature")
plt.ylabel(r'$ \xi $')
plt.title("Plot of magnetic susceptibility versus temperature")
plt.grid()
plt.tight_layout()
plt.savefig('plots/ksi_T.pdf')
plt.close()
