#!/usr/bin/env python
import os
import sys

def system(command):
    """ Version that dies immediately on a command failure """
    result = os.system(command)



#DiSign= ["OS"]
#Plots= ["SVMass"]
DiSign= ["OS","SS"]
Plots= ["SVMass","VisibleMass","LT"]
#Plots= ["SVMass","VisibleMass","LT","Isolation_tau1","Isolation_tau2","Isolation_ele1","Isolation_ele2","Isolation_mu1","Isolation_mu2"]
finalstate= ["tt","et","mt","em","cmb"]
finalstateGrand= ["lltt","llet","llmt","llem","combined"]
year= [7,8,78]

for sign in DiSign:
    for plot in Plots:
        system("cp -v _%s_%s/*.root  root/" % (plot,sign))
        system("sh step2_runAllChannels.sh")
        system("rm -rf Prefit_%s_%s" % (plot,sign))
        system("mkdir -p Prefit_%s_%s" % (plot,sign))
        for ii in range(len(finalstate)):
            for time in year:
                system("""root -b -q 'draw_prefit.C+("Prefit/%s_%dTeV.root","%s",%d, "%s [GeV]", "%s")'""" % (finalstateGrand[ii],time,finalstate[ii],time,plot,sign ))
        system("mv *scaled*.* Prefit_%s_%s/." % (plot,sign))
        system("cp Prefit/* Prefit_%s_%s/." % (plot,sign))
        system("rm -rf  *.d *.so")




