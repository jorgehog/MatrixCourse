# -*- coding: utf-8 -*-

from scitools.std import *
import os, re

n =20;
eps=0.001
nm = n*100

programPath = os.path.expanduser("~") + "/NetBeansProjects/matrixCourse/dist/Debug/GNU-Linux-x86"
programName = "matrixcourse"
tag = str(random.random())[2:]
outname = "output_" + tag + ".txt"

print "TAG: ", tag, "\n"

os.system("%s/%s %d %g %d > ../output/%s" % (programPath, programName, n,eps, nm, outname))

inFile = open("../output/" + outname, 'r')
infile = inFile.read()
inFile.close()

methods = ["QR", "HessenbergQR", "shiftedQR", "Francis"]

timeP = "Iterations completed after\s*(\d+\.?\d*e?-?\d*)\s*seconds|Iterations aborted after\s*(\d+\.?\d*e?-?\d*)\s*seconds, with\s*\d+\s*iterations."

times = []
for t in re.findall(timeP, infile):
    if t[0]:
        times.append(float(t[0]))
    elif t[1]:
        times.append(float(t[1]))
    else:
        print "error"
        times.append(0)

iterP = "Iterations completed after\s*\d+\.?\d*e?-?\d*\s*seconds, with\s*(\d+)\s*iterations.|Iterations (aborted) after\s*\d+\.?\d*e?-?\d*\s*seconds, with\s*\d+\s*iterations."

itersRaw = re.findall(iterP, infile)
iters = []
c = 0
for it in itersRaw:
    if it[0]:
        iters.append(it[0])
    elif it[1] == 'aborted':
        iters.append('N/A')
        c+=1
    else:
        print "error"
        iters.append('0')


errorP = "Approximate eigenvalues with error (\d+\.?\d*e?-?\d*)"
errors = [float(x) for x in re.findall(errorP, infile)]
if c == len(methods):
    errors = [0]

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

doCond = True
        
if doCond:
    COND = zeros([maxL, len(methods)])
    CONDSTOP = zeros([len(methods)])
    for i in range(len(methods)):
        CONDSTOP[i] = len(cond[i])
        COND[0:len(cond[i]), i] = cond[i]
        COND[len(cond[i]):, i] = cond[i][-1]

plotStyles=["b","r","g", "c"]    
eigPlotStyle = "x"

#Sorting
armaEig.sort(axis=0)
for subset in eigvals:
    subset.sort(axis=0)


titleEig = "Plot of eigenvalues z. Error=%g." % errors[0]
hcEig = "../output/" + tag + "EIGVALS.png"

#min_x = eigvals[:][:,0].min()*(1.1*(eigvals[:][:,0].min() < 0) + 0.9*(eigvals[:][:,0].min() > 0))
#maxEig = eigvals.max()*(1.1*(eigvals.max() > 0) + 0.9*(eigvals.max() < 0))
#axisEig = [0, n+1,  minEig, maxEig]

for i in range(len(methods)):
    figure(1)
    
    plot(eigvals[i][:,0],eigvals[i][:,1], 
         plotStyles[i] + eigPlotStyle, 
         hold="on", 
         legend="%s (%s)" % (methods[i], iters[i]))
    
    if doCond:
        figure(2)

        accu = add.accumulate(COND[:, i])/add.accumulate(ones(COND[:, i].shape))
        plot(accu, 
             plotStyles[i],
             hold="on", 
             legend="%s (%.2E s)" % (methods[i], times[i]))
        
        figure(5)
        
        plot(COND[:, i], plotStyles[i], hold="on", 
             title="Convergance plot lower values", 
             legend="%s (%.2E s)" % (methods[i], times[i]),
             xlabel="iteration", ylabel="Condition", 
             hardcopy="../output/" + tag + "CONVERGANCE0.png")

figure(1)
plot(armaEig[:,0], armaEig[:,1], "r*", hold="on", 
     legend="arma::eig_gen()",
#     axis=axisEig,
     title=titleEig, 
     xlabel="Re(z)", ylabel="Im(z)", 
     hardcopy=hcEig)       
        
figure(2)
plot(CONDSTOP, zeros(len(methods)), "ks",
     title="Convergance plot lower values (trailing averages)", 
     legend="Point of convergance",
     xlabel="iteration", ylabel="Average condition", 
     hardcopy="../output/" + tag + "CONVERGANCE1.png")

raw_input()