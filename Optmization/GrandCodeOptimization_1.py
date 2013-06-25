import math

import ROOT
from ROOT import Double
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import TTree
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gStyle
from ROOT import gSystem
from ROOT import TLegend
import os



outRootDir = outRootDir = '../ROOTFiles/Results/'
inRootDir = "outRoot/"
limitDir = "limitDir/"

signal = ['zhtt', 'zhww']
mass = [110, 115, 120, 125, 130, 135, 140, 145]
BackGround = ['ZZ4L', 'Data']

FitType = ["Visible_","SV_"] #Two types of the limit

def DoTheOptimization(Channel, tauIsolation, leptonIsolation, LTCut):
    print "\n\n*********************" , Channel
    OutFile = open("RunOpt_" + Channel + ".txt", 'w')
    firstCommand = "./Make.sh Val1_FullHisto.cc\n"
#    firstCommand = firstCommand + "rm limitDir/*.*\n\n"
    OutFile.write(firstCommand)
    for cut1 in tauIsolation:
        for cut2 in leptonIsolation:
            for cut3 in LTCut:
                outCommand = ""
                outCommand = "rm *.root\n"
                outCommand = outCommand + "rm " + inRootDir + "*.root\n"
                ###################################### Filling Signal ZH and WH ########
                for sig in signal:
                    for m in range(len(mass)):#    for m in range(110, 145, 5):
                        outCommand = outCommand + "./Val1_FullHisto.exe  " + Channel + " " + str(cut1) + " " + str(cut2) + " " + str(cut3) + " "
                        outCommand = outCommand + inRootDir + str(sig) + str(mass[m]) + ".root  " + outRootDir + str(sig) + str(mass[m]) + ".root\n"

                #######################################   Filling BG and Data  #########
                for bg in range (len(BackGround)):
                    outCommand = outCommand + "./Val1_FullHisto.exe  " + Channel  + " " + str(cut1) + " " + str(cut2) + " " + str(cut3) + " "
                    outCommand = outCommand + inRootDir + str(BackGround[bg]) + ".root  " + outRootDir + str(BackGround[bg]) + ".root\n"

                outCommand = outCommand + "cp  outRoot/Data.root valid_Mega.root \n"
                outCommand = outCommand + "root .x -q Val2_FRMeasure.cc \n"
                outCommand = outCommand + "root .x -q Val3_BGestimation.cc \n"
                outCommand = outCommand + "python make_Results_2DTable.py \n"
                outCommand = outCommand + "python make_Results_Histograms.py \n"
                outCommand = outCommand + "mv tableAll.pdf  " + limitDir + Channel + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".pdf \n"
                outCommand = outCommand + "mv TotalRootForLimit_SV.root  " + limitDir + "SV_" + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".root \n"
                outCommand = outCommand + "mv TotalRootForLimit_Visible.root  " + limitDir + "Visible_" + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".root \n\n\n"
                OutFile.write(outCommand)
                
def DoLimitMeasurement(Channel, tauIsolation, leptonIsolation, LTCut):
    print "\n\n*********************" , Channel
    for cut0 in FitType:
        OutFile = open("RunLimit_"+str(cut0) + Channel + ".txt", 'w')
        for cut1 in tauIsolation:
            for cut2 in leptonIsolation:
                for cut3 in LTCut:
                    outCommand = ""
                    name=  str(cut0) + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3)
                    nameRoot = name + ".root"
                    nameCard = name + ".txt"
                    outCommand = outCommand + "create-datacard.py -i " + limitDir + nameRoot
                    outCommand = outCommand + " -o " + limitDir + nameCard + " -c cgs-sm-8TeV-01"+Channel+".conf -u template_unc.vals -d template_unc.conf 125\n"
                    outCommand = outCommand + "combine -M Asymptotic -m 125 " + limitDir + nameCard + "  -H ProfileLikelihood -n " + name + "  -t  -1  \n"
                    OutFile.write(outCommand)

def DoLimitMeasurement_BBB(Channel, tauIsolation, leptonIsolation, LTCut):
    print "\n\n*********************" , Channel
    numChannel = ["00","01","02","03","04","05","06","07"]
    if Channel == "TT" : numChannel = ["00","04"]
    if Channel == "MT" : numChannel = ["02","05"]
    if Channel == "ET" : numChannel = ["01","06"]
    if Channel == "EM" : numChannel = ["03","07"]
    for cut0 in FitType:
        OutFile = open("RunLimit_"+str(cut0) + Channel + ".txt", 'w')
        for cut1 in tauIsolation:
            for cut2 in leptonIsolation:
                for cut3 in LTCut:
                    outCommand = ""
                    name=  str(cut0) + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3)
                    nameRoot = name + ".root"
                    nameCard = name + ".txt"

                    OriginalFiles = "setups/std/em/"
                    limFiles = "setups/std-bin-by-bin/em/"
                    BBB_Root = limFiles + "htt_em.inputs-sm-8TeV.root"
                    outCommand = outCommand + "rm "+ limitDir +nameCard +  "\n"
                    outCommand = outCommand + "cp " +limitDir + nameRoot + " setups/std/em/htt_em.inputs-sm-8TeV.root\n"

                    outCommand = outCommand + "./add_bbb_errors.py -f 'em:8TeV:"
                    for subChannel in range(len(numChannel)):
                        outCommand = outCommand + numChannel[subChannel] + ","
                    outCommand = outCommand + ":Zjets' -i setups/std -o  setups/std-bin-by-bin --normalize --threshold 0.10\n" #(this adds bin-by-bin errors to Zjets background, in the em


                    for subChannel in range(len(numChannel)):
                        outCommand = outCommand + "create-datacard.py -i  " + BBB_Root +  " -o " + "card"+str(subChannel)+".txt" + " -c " + limFiles+ "cgs-sm-8TeV-"+numChannel[subChannel]+ ".conf " + " -u " + limFiles+ "unc-sm-8TeV-"+numChannel[subChannel]+ ".vals " + " -d " + limFiles+ "unc-sm-8TeV-"+numChannel[subChannel]+ ".conf 125 \n"

                    outCommand = outCommand + "combineCards.py "
                    for subChannel in range(len(numChannel)):
                        outCommand = outCommand +  "card"+str(subChannel)+".txt "

                    outCommand = outCommand + " > " + limitDir +nameCard + "\n"

                    outCommand = outCommand + 'echo "**************************************** " \n'
                    outCommand = outCommand + 'echo "************* ' + name + ' ************* " \n'
                    outCommand = outCommand + 'echo "****************************************"  \n'
                    outCommand = outCommand + "combine -M Asymptotic -m 125 " + limitDir + nameCard + "  -H ProfileLikelihood -n " + name + "  -t  -1  \n"
                    outCommand = outCommand + "rm card0.txt card1.txt  roostats-* \n\n"
                    OutFile.write(outCommand)
                    




if __name__ == "__main__":

    

    tauIsolation = ["Total"]
    leptonIsolation = [0.3]
    LTCut = [0]
    DoTheOptimization("Total", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement("Total", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_BBB("Total", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL", "3HitM", "MVAL", "MVAM"]
    leptonIsolation = [0.3]
    LTCut = [60, 65,70,75, 80]
    DoTheOptimization("TT", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_BBB("TT", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [ 40,45, 50,55, 60]
    DoTheOptimization("MT", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_BBB("MT", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [30, 35,40,45, 50]
    DoTheOptimization("ET", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_BBB("ET", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30,0.35]
    LTCut = [20,25, 30,35, 40]
    DoTheOptimization("EM", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_BBB("EM", tauIsolation, leptonIsolation, LTCut)

#    tauIsolation = ["3HitL", "3HitM", "MVAL", "MVAM"]
#    leptonIsolation = [0.3]
#    LTCut = [50, 60, 70, 80]
#    DoTheOptimization("TT", tauIsolation, leptonIsolation, LTCut)
##    DoLimitMeasurement("TT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("TT", tauIsolation, leptonIsolation, LTCut)
#
#    tauIsolation = ["3HitL"]
#    leptonIsolation = [0.10, 0.20, 0.30, 0.40]
#    LTCut = [30, 40, 50, 60]
#    DoTheOptimization("MT", tauIsolation, leptonIsolation, LTCut)
##    DoLimitMeasurement("MT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("MT", tauIsolation, leptonIsolation, LTCut)
#
#    tauIsolation = ["3HitL"]
#    leptonIsolation = [0.10, 0.20, 0.30, 0.40]
#    LTCut = [30, 40, 50, 60]
#    DoTheOptimization("ET", tauIsolation, leptonIsolation, LTCut)
##    DoLimitMeasurement("ET", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("ET", tauIsolation, leptonIsolation, LTCut)
#
#    tauIsolation = ["3HitL"]
#    leptonIsolation = [0.10, 0.20, 0.30, 0.40]
#    LTCut = [20, 30, 40, 50]
#    DoTheOptimization("EM", tauIsolation, leptonIsolation, LTCut)
##    DoLimitMeasurement("EM", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("EM", tauIsolation, leptonIsolation, LTCut)
#    