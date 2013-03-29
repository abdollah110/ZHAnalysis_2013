#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollah"
__date__ = "$Feb 23, 2010 5:15:54 PM$"

import os
import shutil
if __name__ == "__main__":

    location = os.getcwd()

    OutLocation = "OutSubmit"
    if os.path.exists(OutLocation):
        shutil.rmtree(OutLocation)
    if not os.path.exists(OutLocation):
        os.makedirs(OutLocation)

    OutRoot = "OutRoot"
    submit_File = open("Prepare_JobsSubmission.sh", 'w')
    TextSamples = open("textSamples.txt", "r")
    FinalState = ['mmtt','mmet','mmmt','mmme','eett','eemt','eeet','eeem','mmtt_tot','mmet_tot','mmmt_tot','mmme_tot','eett_tot','eemt_tot','eeet_tot','eeem_tot']
    ChannelNumber = [1,2,3,4,5,6,7,8,91,92,93,94,95,96,97,98]
    for Sample in TextSamples.readlines():


       
#        RootLocation =  "Results/" + Sample    # For M Machines
        RootLocation = "/afs/cern.ch/work/a/abdollah/SVFIT_ROOT/Results/"+ Sample   # for lxplus

        Tag = Sample[:-6]
        for chanl in range(len(FinalState)):
            name_out = OutLocation + "/" + "submit" + Tag +"_" +FinalState[chanl] +".sh"
            outFile = open(name_out, 'w')
            command1 = ""
#            command1 = "source $VO_CMS_SW_DIR/cmsset_default.sh " + "\n"  # Just for M Machines
            command1 = command1 + "cd " + location + "\n"
            command1 = command1 + "eval `scram runtime -sh` " + "\n\n"
            command1 = command1 + "nsvfitStandalone " +  str(ChannelNumber[chanl]) + " "+ Tag+FinalState[chanl] + ".root"
            command1 = command1 +  " "+ RootLocation + "\n"
            command1 = command1 +  "mv " + Tag+FinalState[chanl] + ".root   " + OutRoot
            outFile.write(command1)
            outFile.close()
#            command2 = "qsub -q localgrid@cream02 -o " + Tag + ".stdout -e "  + Tag + ".stderr  " + name_out + "\n"  # for Ma mchines
            command2 = "bsub  -q 2nd -J  " + Tag + " < " + name_out + "\n"  # for lxplus
            submit_File.write(command2)
    submit_File.close()
