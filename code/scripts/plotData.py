# -*- coding: utf-8 -*-

from scitools.std import random, plot, figure, linspace, zeros, array
import os, re

n = 6;

programPath = os.path.expanduser("~") + "/NetBeansProjects/matrixCourse/dist/Debug/GNU-Linux-x86"
programName = "matrixcourse"
tag = str(random.random())[2:]
outname = "output_" + tag + ".txt"

os.system("%s/%s %d > ../output/%s" % (programPath, programName, n, outname))

inFile = open("../output/" + outname, 'r')
infile = inFile.read()
inFile.close()


methods = ["QR", "HessenbergQR", "shiftedQR", "Francis"]

timeP = "Iterations completed after\s*(\d+\.?\d*e?-?\d*)\s*seconds"
times = [float(x) for x in re.findall(timeP, infile)]

iterP = "Iterations completed after\s*\d+\.?\d*e?-?\d*\s*seconds, with\s*(\d+)\s*iterations."
iters = [int(x) for x in re.findall(iterP, infile)]

errorP = "Approximate eigenvalues with error (\d+e-\d+)"
errors = [float(x) for x in re.findall(errorP, infile)]

eigvals = zeros([len(methods), n, 2])
cond = []
armaEig = zeros([n, 2])

p = re.compile("^cond:(.+)$", re.MULTILINE)
p_eig = re.compile("^\s*([\+\-]?\d+\.?\d*)\s+([\+\-]?\d+\.?\d*)\s*$", re.MULTILINE)
p_eigA = re.compile("^\s*\(([\+\-]?\d+\.?\d*e[\+\-]?\d+)\,\s*([\+\-]?\d+\.?\d*e[\+\-]?\d+)\)\s*$", re.MULTILINE)

i = 0
for methodDump in infile.split("Eigenvalues by arma::eig_gen():")[0:-1]:
    cond.append([float(x) for x in p.findall(methodDump)])
    eigvals[i][:] = array(p_eig.findall(methodDump))
    i+=1

    if (i==2):
        armaEig[:,:] = array(p_eigA.findall(methodDump))
      


maxL = 0
for c in cond:
    if (len(c)) > maxL:
        maxL = len(c)

COND = zeros([maxL, len(methods)])
for i in range(len(methods)):
    COND[0:len(cond[i]), i] = cond[i]
    COND[len(cond[i]):, i] = cond[i][-1]



condPlotStyles=["k--","k:","k-.", "k-*"]    
plotStyles=["k+", "k.", "kx", "k*"]


armaEig.sort()

figure(1)
plot(linspace(1, n, n), armaEig[:,0], "k^", hold="on")
plot(linspace(1, n, n), armaEig[:,1], "k^", hold="on", legend="arma::eig_gen()")

for i in range(len(methods)):
#    print i, len(eigvals), len(plotStyles), len(iters), len(methods)
    eigvals[i].sort()
    figure(1)
    plot(linspace(1, n, n), eigvals[i][:,0], plotStyles[i], hold="on")
    plot(linspace(1, n, n), eigvals[i][:,1], plotStyles[i], hold="on", legend="%s (%d)" % (methods[i], iters[i]) , title="Plot of eigenvalues. Error=" + str(errors[0]), xlabel="#", ylabel="eigenvalue", hardcopy="../output/" + tag + "EIGVALS.png")
    
    figure(2)
    plot(COND[:, i], condPlotStyles[i],hold="on", legend="%s (%.2E s)" % (methods[i], times[i]), title="Convergance plot.", xlabel="iteration", ylabel="prod(diag(A))", hardcopy="../output/" + tag + "CONVERGANCE.png")
    

raw_input()