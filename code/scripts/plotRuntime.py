# -*- coding: utf-8 -*-

from scitools.std import array, plot

infile = open("../output/TEST2.txt", 'r')

n = []
t = [[],[],[]]
i = [[],[],[]]

for line in infile:
    if line.startswith("n="):
        n.append(int(line.split("=")[1]))
    else:
        tmp = line.split(":")
        j = int(tmp[0])
        t[j].append(float(tmp[2]))
        i[j].append(int(tmp[3]))
        

t0 = array(t[0])#/array(i[0])
t1 = array(t[1])#/array(i[1])
t2 = array(t[2])#/array(i[2])

T = array([t0, t1, t2])
styles = ["k--","k:","k-."]
methods = ["QR", "HessenbergQR", "shiftedQR"]

for i in range(1, len(T)):
    plot(n, T[i,:], styles[i], hold="on",legend=methods[i], title="Comparison of runtime pr. iteration. n = matrix dim.", ylabel="n", xlabel="runtime/iteration [s]")
    
raw_input()
