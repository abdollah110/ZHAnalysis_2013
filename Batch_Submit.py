#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollah"
__date__ = "$Feb 23, 2010 5:15:54 PM$"

import os

    ########################################################################################
Run_Over = {
    1:("/pnfs/iihe/cms/store/user/jez/FILTER2/ZHttNtuples/42X/Data", "data11", "Ele", "05:00:00"),
    2:("/pnfs/iihe/cms/store/user/jez/FILTER2/ZHttNtuples/42X/Data", "data11", "Mu", "05:00:00"),
    3:("/pnfs/iihe/cms/store/user/jez/FILTER2/ZHttNtuples/53X/Data", "data12", "Ele", "05:00:00"),
    4:("/pnfs/iihe/cms/store/user/jez/FILTER2/ZHttNtuples/53X/Data", "data12", "Mu", "05:00:00"),
    5:("/pnfs/iihe/cms/store/user/jez/ZHttNtuples/42X/MC", "mc11", "Tot", "05:00:00"),
    6:("/pnfs/iihe/cms/store/user/abdollah/ZHttNtuples/53X/MC", "mc12", "Tot", "03:00:00"),
    7:("/pnfs/iihe/cms/store/user/jez/ZHttNtuples/53X/MC", "mc12", "Tot", "05:00:00"),
}

    ########################################################################################
def make_submit_form(order, pnfn, data_year, lepton_type, timing):
    location = "/localgrid/abdollah/CMSSW_4_2_8/src/WORK_DIR/Post_HCP/An5_NewVersion"
#    location = os.getcwd()
    Sample = os.popen(("ls " + pnfn + " | sort | grep " + lepton_type))
    if lepton_type == "Tot":
        Sample = os.popen(("ls " + pnfn + " | sort "))
    #output name, one for submitting jobs, one for hadding root files
    name_submitFile = "Submit_" + data_year + "_" + lepton_type + "_" + order + ".sh"
    name_haddFile = "Hadd_" + data_year + "_" + lepton_type + "_" + order + ".sh"
    submit_File = open(name_submitFile, 'w')
    Hadd_File = open(name_haddFile, 'w')

    #Make loop over the files in the given directories
    for files in Sample.readlines():
        f = os.popen("ls " + pnfn + "/" + files[0:-1] + " | sort")
        dir = "dcap://maite.iihe.ac.be" + pnfn + "/" + files[0:-1] + "/"
        name_out = "__" + data_year + "_" + files[0:-1] + ".sh"
        outFile = open(name_out, 'w')
        command1 = "source $VO_CMS_SW_DIR/cmsset_default.sh " + "\n"
        command1 = command1 + "cd " + location + "\n"
        command1 = command1 + "eval `scram runtime -sh` " + "\n\n"
        command1 = command1 + "mkdir    Out_" + files[0:-1] + "\n"
        outFile.write(command1)
        #Make loop over the rootfiles in the given file
        for i in f.readlines():
            command2 = "\n" + "./ZH_Analysis.exe " + data_year + " " + lepton_type + " "  + files[0:-1] + i[0:-1] + " " + dir + "/" + i[0:-1]
            command2 = command2 + " \n" + " mv  " + data_year + "_" + lepton_type + "_" + files[0:-1] + i[0:-1] + "\t" + "Out_" + files[0:-1]
            command2 = command2 + " \n\n\n"
            outFile.write(command2)

        #Writing on out Files
        command3 = "qsub -q localgrid@cream02 -o " + files[0:-1] + ".stdout -e " + files[0:-1] + ".stderr -l walltime=" + timing + "  " + name_out + "\n"
        command4 = "hadd -f ROOT/" + data_year + "/" + files[0:-1] + ".root\t" + "Out_" + files[0:-1] + "/*.root" + "\n"
        submit_File.write(command3)
        Hadd_File.write(command4)

    outFile.close()
    submit_File.close()
    Hadd_File.close()
    ########################################################################################
if __name__ == "__main__":
    for i in Run_Over:
        R1, R2, R3, R4 = Run_Over[i]
        make_submit_form(str(i), R1, R2, R3, R4)

    rm TotalSubmit.sh; ls Submit_* | xargs -n 1 -I {} echo 'sh {}' >> TotalSubmit.sh 
    rm TotalHadd.sh;   ls Hadd_* | xargs -n 1 -I {} echo 'sh {}' >> TotalHadd.sh
    