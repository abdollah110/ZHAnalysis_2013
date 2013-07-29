#!/usr/bin/env python
import os
import sys

def system(command):
    """ Version that dies immediately on a command failure """
    result = os.system(command)



#Plots= ["SVMass","VisibleMass","LT","Isolation_tau1","Isolation_tau2","Isolation_ele1","Isolation_ele2","Isolation_mu1","Isolation_mu2"]
Plots= ["SVMass","VisibleMass","LT"]
finalstate= ["tt","et","mt","em"]
year= [7,8]
DiSign= ["OS","SS"]

for sign in DiSign:
    for plot in Plots:
        system("rm  -rf _%s_%s" % (plot,sign))
        system("mkdir -p _%s_%s" % (plot,sign))
        for state in finalstate:
            for time in year:
                system("cp -v files_%s/TotalRootForLimit_%s__%dTeV.root _%s_%s/htt_%s.input_%dTeV.root" % (sign,plot,time,plot,sign,state,time ))