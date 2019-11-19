import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.font_manager

def readfile(file):

    temperature = []
    E_list = []
    C_v = []
    M_abs_list = []
    ksi_list = []
    i = 0
    o = open(file)
    for line in o:
        # print (i)
        # i+=1
        # if i == 61:
        #     break
        line = line.split()
        temperature.append(float(line[0]))
        E_list.append(float(line[1]))
        C_v.append(float(line[2]))
        M_abs_list.append(float(line[3]))
        ksi_list.append(float(line[4]))
    o.close()
    return np.array(temperature), np.array(E_list), np.array(C_v), np.array(M_abs_list), np.array(ksi_list)


temperature1, E_list1, C_v1, M_abs_list1, ksi_list1 = readfile(sys.argv[1])
temperature2, E_list2, C_v2, M_abs_list2, ksi_list2 = readfile(sys.argv[2])
temperature3, E_list3, C_v3, M_abs_list3, ksi_list3 = readfile(sys.argv[3])
temperature4, E_list4, C_v4, M_abs_list4, ksi_list4 = readfile(sys.argv[4])

plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern', size=15)


plt.plot(temperature1, C_v1, 'b', label = 'L = 40')
plt.plot(temperature2, C_v2,'g', label = 'L = 60')
plt.plot(temperature3, C_v3, 'k', label = 'L = 80')
plt.plot(temperature4, C_v4, 'r', label = 'L = 100')
plt.title("Plot of specific heat capacity versus temperature")
plt.xlabel("Temperature")
plt.ylabel("$C_v$")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("4F_Cv.pdf")
plt.close()

plt.plot(temperature1, E_list1, 'b', label = 'L = 40')
plt.plot(temperature2, E_list2,'g', label = 'L = 60')
plt.plot(temperature3, E_list3, 'k', label = 'L = 80')
plt.plot(temperature4, E_list4, 'r', label = 'L = 100')
plt.title("Plot of mean energy versus temperature")
plt.xlabel("Temperature")
plt.ylabel("Mean energy")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("4F_E.pdf")
plt.close()

plt.plot(temperature1, M_abs_list1, 'b', label = 'L = 40')
plt.plot(temperature1, M_abs_list2,'g', label = 'L = 60')
plt.plot(temperature1, M_abs_list3, 'k', label = 'L = 80')
plt.plot(temperature1, M_abs_list4, 'r', label = 'L = 100')
plt.title("Plot of mean absolute magnetization versus temperature")
plt.xlabel("Temperature")
plt.ylabel("Mean absolute magnetization")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("4F_M.pdf")
plt.close()

plt.plot(temperature1, ksi_list1, 'b', label = 'L = 40')
plt.plot(temperature1, ksi_list2,'g', label = 'L = 60')
plt.plot(temperature1, ksi_list3, 'k', label = 'L = 80')
plt.plot(temperature1, ksi_list4, 'r', label = 'L = 100')
plt.title("Plot of susceptibility versus temperature")
plt.xlabel("Temperature")
plt.ylabel("Susceptibility")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("4F_xi.pdf")
plt.close()
