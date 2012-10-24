# -*- coding: utf-8 -*-

from scitools.std import random, plot, figure, linspace, zeros
import os, re

programPath = os.path.expanduser("~") + "/NetBeansProjects/matrixCourse/dist/Debug/GNU-Linux-x86"
programName = "matrixcourse"
tag = str(random.random())[2:]
outname = "output_" + tag + ".txt"

os.system("%s/%s > ../output/%s" % (programPath, programName, outname))

inFile = open("../output/" + outname, 'r')
infile = "".join(inFile.readlines())
inFile.close()
#print infile

methods = ["QR", "HessenbergQR", "shiftedQR"]

timeP = "Iterations completed after\s*(\d+\.?\d*)\s*seconds"
times = [float(x) for x in re.findall(timeP, infile)]

iterP = "Iterations completed after\s*\d+\.?\d*\s*seconds, with\s*(\d+)\s*iterations."
iters = [int(x) for x in re.findall(iterP, infile)]

errorP = "Approximate eigenvalues with error (\d+e-\d+)"
errors = [float(x) for x in re.findall(errorP, infile)]

eigvals = [[],[],[]]
cond = [[],[],[]]
armaEig = []

lineIsEigVal = False
getArmaVal = True
isArmaVal = False
i = -1
j = 0;
for line in infile.split("\n"):
   
    if not line.strip():
        lineIsEigVal = False
        isArmaVal = False
        if len(armaEig) != 0:
            getArmaVal = False
   
    if isArmaVal and getArmaVal:
        armaEig.append(float(line))
       
    if lineIsEigVal:
        eigvals[i].append(float(line))
    
    if line.startswith("Approximate eigenvalues"):
        lineIsEigVal = True
        i+=1;
    
    if line.startswith("Eigenvalues by arma::eig_gen():"):
        isArmaVal = True
    
    if line.startswith("cond:"):
        cond[j].append(float(line.split(":")[1]))
    elif line.startswith("Iterations completed"):
        j += 1

maxL = 0
for c in cond:
    if (len(c)) > maxL:
        maxL = len(c)

COND = zeros([maxL, len(methods)])
for i in range(len(methods)):
    COND[0:len(cond[i]), i] = cond[i]
    COND[len(cond[i]):, i] = cond[i][-1]

condPlotStyles=["k--","k:","k-."]    
plotStyles=["k+", "k.", "kx"]
n = len(armaEig)

armaEig.sort()
figure(1)
plot(linspace(1, n, n), armaEig, "k^", hold="on", legend="arma::eig_gen()")

for i in range(len(methods)):
    eigvals[i].sort()
    figure(1)
    plot(linspace(1, n, n), eigvals[i], plotStyles[i], hold="on", legend="%s (%d)" % (methods[i], iters[i]) , title="Plot of eigenvalues. Error=" + str(errors[0]), xlabel="#", ylabel="eigenvalue", hardcopy="../output/" + tag + "EIGVALS.png")
    figure(2)
    plot(COND[:, i], condPlotStyles[i],hold="on", legend="%s (%.2E s)" % (methods[i], times[i]), title="Convergance plot.", xlabel="iteration", ylabel="prod(diag(A))", hardcopy="../output/" + tag + "CONVERGANCE.png")
    

raw_input()