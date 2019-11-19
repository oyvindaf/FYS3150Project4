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

def test_analytical():
    if temperature[0] == 1:
        tol = 1e-3
        E = E_list[0]; E_ana = -1.99598
        M = M_abs_list[0]; M_ana = 0.99866
        Cv = C_v[0]; Cv_ana = 0.03480
        ksi = ksi_list[0]; ksi_ana = 0.00409

        numerical = np.asarray([E, M, Cv, ksi])
        analytical = np.asarray([E_ana, M_ana, Cv_ana, ksi_ana])

        for i in range(len(numerical)):
            success = abs(numerical[i]-analytical[i]) < tol
            msg = 'numerical value: %.4f, analytical value: %.4f' % (numerical[i], analytical[i])

            assert success, msg

test_analytical()