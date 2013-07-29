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



outRootDir = outRootDir = '../ROOTFiles_V3/Results/'
inRootDir = "outRoot_V3/"
limitDir = "limitDir/"

signal = ['zhtt', 'zhww']
mass = [110, 115, 120, 125, 130, 135, 140, 145]
BackGround = ['ZZ4L', 'Data', 'GGToZZ2L2L']

#FitType = ["Visible_","SV_"] #Two types of the limit
FitType = ["SV_"] #Two types of the limit
energy_Index = "_8TeV"
#energy_Index = ""

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
                        outCommand = outCommand + inRootDir + str(sig) + str(mass[m]) + energy_Index+ ".root  " + outRootDir + str(sig) + str(mass[m]) +energy_Index+ ".root\n"

                #######################################   Filling BG and Data  #########
                for bg in range (len(BackGround)):
                    outCommand = outCommand + "./Val1_FullHisto.exe  " + Channel  + " " + str(cut1) + " " + str(cut2) + " " + str(cut3) + " "
                    outCommand = outCommand + inRootDir + str(BackGround[bg]) +energy_Index+ ".root  " + outRootDir + str(BackGround[bg]) +energy_Index+ ".root\n"

                outCommand = outCommand + "cp  "+inRootDir+"Data"+energy_Index+".root valid_Mega.root \n"
                outCommand = outCommand + "root .x -q Val2_FRMeasure.cc \n"
                outCommand = outCommand + "root .x -q Val3_BGestimation.cc \n"
                outCommand = outCommand + "mv Reducible.root  Reducible_8TeV.root \n"
                outCommand = outCommand + "python make_Results_2DTable.py \n"
                outCommand = outCommand + "python make_Results_Histograms.py \n"
                outCommand = outCommand + "mv tableAll_8TeV.pdf  " + limitDir + Channel + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".pdf \n"
                outCommand = outCommand + "mv tableAll_Up_8TeV.pdf  " + limitDir + Channel + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + "_Up.pdf \n"
                outCommand = outCommand + "mv tableAll_Down_8TeV.pdf  " + limitDir + Channel + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + "_Down.pdf \n"
                outCommand = outCommand + "mv TotalRootForLimit_SVMass__8TeV.root  " + limitDir + "SV_" + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".root \n\n\n"
#                outCommand = outCommand + "mv TotalRootForLimit_Visible.root  " + limitDir + "Visible_" + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3) + ".root \n\n\n"
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
    if Channel == "TT" : numChannel = ["mmtt","eett"]
    if Channel == "MT" : numChannel = ["mmmt","eemt"]
    if Channel == "ET" : numChannel = ["mmet","eeet"]
    if Channel == "EM" : numChannel = ["mmme","eeem"]
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
                    
def DoLimitMeasurement_NEW_HTT(Channel, tauIsolation, leptonIsolation, LTCut):
    print "\n\n*********************" , Channel
    if Channel == "TT" : numChannel = "tt"
    if Channel == "MT" : numChannel = "mt"
    if Channel == "ET" : numChannel = "et"
    if Channel == "EM" : numChannel = "em"
    for cut0 in FitType:
        OutFile = open("RunLimit_"+str(cut0) + Channel + ".txt", 'w')
        for cut1 in tauIsolation:
            for cut2 in leptonIsolation:
                for cut3 in LTCut:
                    outCommand = ""
                    name=  str(cut0) + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3)
                    nameRoot = name + ".root"
#                    nameCard = name + ".txt"
#
#                    OriginalFiles = "setups/std/em/"
#                    limFiles = "setups/std-bin-by-bin/em/"
#                    BBB_Root = limFiles + "htt_em.inputs-sm-8TeV.root"


                    outCommand = outCommand + "rrm -rf HiggsAnalysis/HiggsToTauTau/setup/*/*.* \n"
                    outCommand = outCommand + "source copy_cgs_8TeV.sh \n"
                    outCommand = outCommand + "cp " +limitDir + nameRoot + "  HiggsAnalysis/HiggsToTauTau/setup/"+numChannel+"/htt_"+numChannel+".inputs-sm-8TeV.root\n"

                    outCommand = outCommand + "rrm -rf aux/ \n"
                    outCommand = outCommand + "rrm -rf setups/ \n"
                    outCommand = outCommand + "rrm -rf LIMITS/ \n"
                    outCommand = outCommand + "mkdir -p setups aux \n"
                    outCommand = outCommand + "cp -r HiggsAnalysis/HiggsToTauTau/setup setups/std \n"
                    
                    outCommand = outCommand + "./add_bbb_errors_1.py -f '"+numChannel+":8TeV:00:Zjets' -i setups/std -o setups/std-bin-by-bin \n"
                    outCommand = outCommand + "./add_bbb_errors_2.py -f '"+numChannel+":8TeV:00:Zjets' -i setups/std-bin-by-bin -o setups/std-bin-by-bin2 \n"
                    outCommand = outCommand + " mkdir -p aux/std/sm  \n"


                    outCommand = outCommand + "setup-datacards.py -i setups/std-bin-by-bin2 -o aux/std/sm -c '" +numChannel+"'  --sm-categories-"+numChannel+ " '0'  -p 8TeV -a sm 125-125:5 \n"
                    outCommand = outCommand + "mkdir -p LIMITS  \n"
                    outCommand = outCommand + "mkdir -p LIMITS/std  \n"

                    outCommand = outCommand + "setup-htt.py -i aux/std/sm -o LIMITS/std/sm -s chn  -p 8TeV -c '"+numChannel+"' --sm-categories-"+numChannel+" '0'  -a sm 125-125:5  \n"
                    outCommand = outCommand + 'echo "**************************************** " \n'
                    outCommand = outCommand + 'echo "************* ' + name + ' ************* " \n'
                    outCommand = outCommand + 'echo "****************************************"  \n'
                    outCommand = outCommand + "limit.py --asymptotic --expectedOnly --no-prefit LIMITS/std/sm/"+numChannel+"/125 \n"

                    outCommand = outCommand + "cp  LIMITS/std/sm/"+numChannel+"/125/higgsCombine-exp.Asymptotic.mH125.root  RESULTS/"+ "higgsCombine" + name + ".Asymptotic.mH125.root"+ "\n"
                    outCommand = outCommand + "cp  LIMITS/std/sm/"+numChannel+"/125/htt_"+numChannel+"_0_8TeV.txt  RESULTS/"+ "Datacards" + name + ".txt"+ "\n\n\n"


                    OutFile.write(outCommand)

def DoLimitMeasurement_NEW_HTT_NoBBB(Channel, tauIsolation, leptonIsolation, LTCut):
    print "\n\n*********************" , Channel
    if Channel == "TT" : numChannel = "tt"
    if Channel == "MT" : numChannel = "mt"
    if Channel == "ET" : numChannel = "et"
    if Channel == "EM" : numChannel = "em"
    for cut0 in FitType:
        OutFile = open("RunLimit_"+str(cut0) + Channel + ".txt", 'w')
        for cut1 in tauIsolation:
            for cut2 in leptonIsolation:
                for cut3 in LTCut:
                    outCommand = ""
                    name=  str(cut0) + Channel + "_" + str(cut1) + "_" + str(cut2) + "_" + str(cut3)
                    nameRoot = name + ".root"
#                    nameCard = name + ".txt"
#
#                    OriginalFiles = "setups/std/em/"
#                    limFiles = "setups/std-bin-by-bin/em/"
#                    BBB_Root = limFiles + "htt_em.inputs-sm-8TeV.root"


                    outCommand = outCommand + "rrm -rf HiggsAnalysis/HiggsToTauTau/setup/*/*.* \n"
                    outCommand = outCommand + "source copy_cgs_8TeV.sh \n"
                    outCommand = outCommand + "cp " +limitDir + nameRoot + "  HiggsAnalysis/HiggsToTauTau/setup/"+numChannel+"/htt_"+numChannel+".inputs-sm-8TeV.root\n"

                    outCommand = outCommand + " rrm -rf aux/ \n"
                    outCommand = outCommand + "rrm -rf setups/ \n"
                    outCommand = outCommand + "rrm -rf LIMITS/ \n"
                    outCommand = outCommand + "mkdir -p setups aux \n"
                    outCommand = outCommand + "cp -r HiggsAnalysis/HiggsToTauTau/setup setups/std \n"

#                    outCommand = outCommand + "./add_bbb_errors_1.py -f '"+numChannel+":8TeV:00:Zjets' -i setups/std -o setups/std-bin-by-bin \n"
#                    outCommand = outCommand + "./add_bbb_errors_2.py -f '"+numChannel+":8TeV:00:Zjets' -i setups/std-bin-by-bin -o setups/std-bin-by-bin2 \n"
                    outCommand = outCommand + " mkdir -p aux/std/sm  \n"


                    outCommand = outCommand + "setup-datacards.py -i setups/std -o aux/std/sm -c '" +numChannel+"'  --sm-categories-"+numChannel+ " '0'  -p 8TeV -a sm 125-125:5 \n"
                    outCommand = outCommand + "mkdir -p LIMITS  \n"
                    outCommand = outCommand + "mkdir -p LIMITS/std  \n"

                    outCommand = outCommand + "setup-htt.py -i aux/std/sm -o LIMITS/std/sm -s chn  -p 8TeV -c '"+numChannel+"' --sm-categories-"+numChannel+" '0'  -a sm 125-125:5  \n"
                    outCommand = outCommand + "limit.py --asymptotic --expectedOnly --no-prefit LIMITS/std/sm/"+numChannel+"/125 \n"

                    outCommand = outCommand + "cp  LIMITS/std/sm/"+numChannel+"/125/higgsCombine-exp.Asymptotic.mH125.root  RESULTS/"+ "higgsCombine" + name + ".Asymptotic.mH125.root"+ "\n"
                    outCommand = outCommand + "cp  LIMITS/std/sm/"+numChannel+"/125/htt_"+numChannel+"_0_8TeV.txt  RESULTS/"+ "Datacards" + name + ".txt"+ "\n\n\n"


#
#                    outCommand = outCommand + "./add_bbb_errors.py -f 'em:8TeV:"
#                    for subChannel in range(len(numChannel)):
#                        outCommand = outCommand + numChannel[subChannel] + ","
#                    outCommand = outCommand + ":Zjets' -i setups/std -o  setups/std-bin-by-bin --normalize --threshold 0.10\n" #(this adds bin-by-bin errors to Zjets background, in the em
#
#
#                    for subChannel in range(len(numChannel)):
#                        outCommand = outCommand + "create-datacard.py -i  " + BBB_Root +  " -o " + "card"+str(subChannel)+".txt" + " -c " + limFiles+ "cgs-sm-8TeV-"+numChannel[subChannel]+ ".conf " + " -u " + limFiles+ "unc-sm-8TeV-"+numChannel[subChannel]+ ".vals " + " -d " + limFiles+ "unc-sm-8TeV-"+numChannel[subChannel]+ ".conf 125 \n"
#
#                    outCommand = outCommand + "combineCards.py "
#                    for subChannel in range(len(numChannel)):
#                        outCommand = outCommand +  "card"+str(subChannel)+".txt "
#
#                    outCommand = outCommand + " > " + limitDir +nameCard + "\n"
#
#                    outCommand = outCommand + 'echo "**************************************** " \n'
#                    outCommand = outCommand + 'echo "************* ' + name + ' ************* " \n'
#                    outCommand = outCommand + 'echo "****************************************"  \n'
#                    outCommand = outCommand + "combine -M Asymptotic -m 125 " + limitDir + nameCard + "  -H ProfileLikelihood -n " + name + "  -t  -1  \n"
#                    outCommand = outCommand + "rm card0.txt card1.txt  roostats-* \n\n"
                    OutFile.write(outCommand)





if __name__ == "__main__":

    

#    tauIsolation = ["Total"]
#    leptonIsolation = [0.3]
#    LTCut = [0]
#    DoTheOptimization("Total", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("Total", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL", "3HitM", "MVAL", "MVAM"]
    leptonIsolation = [0.3]
    LTCut = [60, 65,70,75, 80]
    DoTheOptimization("TT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("TT", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_NEW_HTT("TT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_NEW_HTT_NoBBB("TT", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [ 35,40,45, 50,55]
    DoTheOptimization("MT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("MT", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_NEW_HTT("MT", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_NEW_HTT_NoBBB("MT", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [25,30, 35,40,45]
    DoTheOptimization("ET", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("ET", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_NEW_HTT("ET", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_NEW_HTT_NoBBB("ET", tauIsolation, leptonIsolation, LTCut)

    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30,0.35]
    LTCut = [20,25, 30,35, 40]
    DoTheOptimization("EM", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_BBB("EM", tauIsolation, leptonIsolation, LTCut)
    DoLimitMeasurement_NEW_HTT("EM", tauIsolation, leptonIsolation, LTCut)
#    DoLimitMeasurement_NEW_noBBB("EM", tauIsolation, leptonIsolation, LTCut)
