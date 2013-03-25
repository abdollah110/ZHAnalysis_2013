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

    submit_File = open("Prepare_JobsSubmission.sh", 'w')
    TextSamples = open("textSamples.txt", "r")
    for Sample in TextSamples.readlines():


       
#        RootLocation = location + "/Results/"   # For M Machines
        RootLocation = "/afs/cern.ch/work/a/abdollah/SVFIT_ROOT/Results/"  # for lxplus

        Tag = Sample[:-6]
        name_out = OutLocation + "/" + "submit" + Tag + ".sh"
        outFile = open(name_out, 'w')
        command1 = ""
#        command1 = "source $VO_CMS_SW_DIR/cmsset_default.sh " + "\n"  # Just for M Machines
        command1 = command1 + "cd " + location + "\n"
        command1 = command1 + "eval `scram runtime -sh` " + "\n\n"
        command1 = command1 + "nsvfitStandalone  " + RootLocation + Sample
        outFile.write(command1)
        outFile.close()
#        command2 = "qsub -q localgrid@cream02 -o " + Tag + ".stdout -e "  + Tag + ".stderr  " + name_out + "\n"  # for Ma mchines
        command2 = "bsub  -q 1nd -J  " + Tag + " < " + name_out + "\n"  # for lxplus
        submit_File.write(command2)
    submit_File.close()
