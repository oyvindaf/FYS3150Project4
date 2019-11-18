import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.font_manager

def readfile(file):
    for file in file_list:

        o = open(file) # opens

        temperature = []
        E_list = []
        C_v = []
        M_list = []
        M_abs_list = []
        ksi_list = []

        for line in o:
            line = line.split()

            temperature.append(float(line[0]))
            E_list.append(float(line[1]))
            C_v.append(float(line[2]))
            M_abs_list.append(float(line[3]))
            ksi_list.append(float(line[4]))
        o.close()
    return np.array(temperature), E_list, np.array(C_v), M_abs_list, np.array(ksi_list)

file_list = [sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4]]
temperature1, E_list, C_v, M_abs_list, ksi_list = readfile(file_list)

temperature = temperature1[:temperature.size/4]

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)



plt.plot(temperature, C_v[:C_v.size/4], 'b', label = 'L = 40')
plt.plot(temperature, C_v[C_v.size/4:C_v.size/2],'g', label = 'L = 60')
plt.plot(temperature, C_v[C_v.size/2:3*C_v.size/4], 'k', label = 'L = 80')
plt.plot(temperature, C_v[3*C_v.size/4:], 'r', label = 'L = 100')
plt.title("Plot of heat capacity versus temperature for various Lattice sizes")
plt.xlabel("Temperature")
plt.ylabel("$C_v$")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("exercise_f.pdf")
plt.close()
