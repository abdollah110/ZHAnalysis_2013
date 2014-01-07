#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import math
import ROOT
from ROOT import Double
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gSystem

gROOT.Reset()
import os
ROOT.gROOT.SetBatch(True)
#ROOT.gROOT.ProcessLine('.x rootlogon.C')

n_bin = 15
low_bin = 0
high_bin = 300
reb_ = high_bin / n_bin
DIR_ROOT = 'outRoot_V3/'
channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
signal = ['zhtt','zhww']
signalname = ['ZH_htt','ZH_hww']
mass = [110, 115, 120, 125, 130, 135, 140, 145]
#BackGround = ['ZZ4L', 'GGToZZ2L2L']
#BackGroundname = ['ZZ', 'GGToZZ2L2L']
BackGround = ['ZZ4L','Data', 'GGToZZ2L2L']
BackGroundname = ['ZZ','data_obs', 'GGToZZ2L2L']
lenghtSig = len(signal) * len(mass)


def _Return_Value_Signal(bb,signal, mass, channel,histoName,PostFix,CoMEnergy ):
    myfile = TFile(DIR_ROOT + str(signal) + str(mass) +CoMEnergy+ '.root')
    Histo =  myfile.Get(histoName + str(channel)+"_pp"+ PostFix)
    binCont = 0
    binErr = 0
    if Histo:
        Histo.Rebin(reb_)
        binCont = Histo.GetBinContent(bb)
        binErr = Histo.GetBinError(bb)
    myfile.Close()
    return binCont , binErr

def _Return_Value_BG(bb,backG, channel,histoName,PostFix,CoMEnergy ):
    myfile = TFile(DIR_ROOT + str(backG)  +CoMEnergy+ '.root')
    Histo =  myfile.Get(histoName + str(channel)+"_pp"+ PostFix)
    binCont = 0
    binErr = 0
    if Histo:
        Histo.Rebin(reb_)
        binCont = Histo.GetBinContent(bb)
        binErr = Histo.GetBinError(bb)
    myfile.Close()
    return binCont , binErr
def _add_Value_Histogram_Signal(myOut,MMM,binNumberX,binNumberY,signalname_,signal_, mass_, channel_, histoName,CoMEnergy, PostFix,Table_Hist):
    MMM.cd()
    NewHist =TH1F(str(signalname_) + str(mass_),"",n_bin,low_bin,high_bin)
    for bb in range(0,n_bin):
        NewHist.SetBinContent(bb,_Return_Value_Signal(bb,signal_, mass_, channel_, histoName, PostFix,CoMEnergy)[0])
        NewHist.SetBinError(bb,_Return_Value_Signal(bb,signal_, mass_, channel_,histoName, PostFix,CoMEnergy)[1])

    normal = Table_Hist.GetBinContent(binNumberX,binNumberY)
    if NewHist.Integral(): NewHist.Scale(normal/NewHist.Integral())
    myOut.Write()
    
def _add_Value_Histogram_BG(MMM,binNumberX,binNumberY,BackGroundname_,BackGround_, channel_, histoName,CoMEnergy, PostFix,Table_Hist):
    MMM.cd()
    NewHist =TH1F(str(BackGroundname_) ,"",n_bin,low_bin,high_bin)
    for bb in range(0,n_bin):
        NewHist.SetBinContent(bb,_Return_Value_BG(bb,BackGround_,  channel_, histoName, PostFix,CoMEnergy)[0])
        NewHist.SetBinError(bb,_Return_Value_BG(bb,BackGround_,  channel_,histoName, PostFix,CoMEnergy)[1])

    normal = Table_Hist.GetBinContent(binNumberX,binNumberY)
    if NewHist.Integral(): NewHist.Scale(normal/NewHist.Integral())


def MakeTheHistogram(histoName,CoMEnergy):
    myOut = TFile("TotalRootForLimit_"+histoName+CoMEnergy+".root" , 'RECREATE')
    Table_File = TFile("Yield"+CoMEnergy+""+".root")
    Table_Hist = Table_File.Get('FullResults')
    #ScaleUp
    Table_File_Up = TFile("Yield"+CoMEnergy+"_Up"+".root")
    Table_Hist_Up = Table_File_Up.Get('FullResults')
    #ScaleDown
    Table_File_Down = TFile("Yield"+CoMEnergy+"_Down"+".root")
    Table_Hist_Down = Table_File_Down.Get('FullResults')


    for chl in range(len(channel)):
        print channel[chl]
        MMM= myOut.mkdir(str(channel[chl])+'_zh')
        MMM.cd()
        ###################################### Filling Signal ZH and WH ########
        for sig in range(len(signal)):
            for m in range(len(mass)):#    for m in range(110, 145, 5):
                ################################################
                binNumberX = chl + 1
                binNumberY = sig * len(mass) + m + 1
                _add_Value_Histogram_Signal(myOut,MMM,binNumberX,binNumberY,signalname[sig],signal[sig], mass[m], channel[chl], histoName,CoMEnergy, "",Table_Hist)
                _add_Value_Histogram_Signal(myOut,MMM,binNumberX,binNumberY,signalname[sig],signal[sig], mass[m], channel[chl], histoName,CoMEnergy, "_Up",Table_Hist_Up)
                _add_Value_Histogram_Signal(myOut,MMM,binNumberX,binNumberY,signalname[sig],signal[sig], mass[m], channel[chl], histoName,CoMEnergy, "_Down",Table_Hist_Down)
#                myOut.Write()

        ###################################### Filling Reducible ########
#        MMM.cd()
#        NewHist =TH1F('Zjets',"",n_bin,low_bin,high_bin)
#        myfile = TFile(DIR_ROOT + 'Data'+CoMEnergy+'.root')
#        Histo =  myfile.Get("VisibleMass_Shape_"+ channel[chl])
#        Histo.Rebin(reb_)
#        for bb in range(0,n_bin):
#            NewHist.SetBinContent(bb,Histo.GetBinContent(bb))
#            NewHist.SetBinError(bb,Histo.GetBinError(bb))
#        normal = Table_Hist.GetBinContent(chl + 1, lenghtSig  + 2)
#        NewHist.Scale(normal/NewHist.Integral())
#        myOut.Write()
        ###################################### Filling ZZ and Data ########
        for bg in range (len(BackGround)):
            #  Norm   #####################################
            binNumberX = chl + 1
            binNumberY = lenghtSig + bg + 3
#            _add_Value_Histogram_BG(MMM,binNumberX,binNumberY,BackGroundname[bg],BackGround[bg],  channel[chl], histoName,CoMEnergy, "",Table_Hist)
#            _add_Value_Histogram_BG(MMM,binNumberX,binNumberY,BackGroundname[bg],BackGround[bg],  channel[chl], histoName,CoMEnergy, "_Up",Table_Hist_Up)
#            _add_Value_Histogram_BG(MMM,binNumberX,binNumberY,BackGroundname[bg],BackGround[bg],  channel[chl], histoName,CoMEnergy, "_Down",Table_Hist_Down)
#            myOut.Write()

            
if __name__ == "__main__":
    MakeTheHistogram("SVMass_","_8TeV")
#    MakeTheHistogram("VisibleMass_","_8TeV")
#    MakeTheHistogram("SVMass_","_7TeV")
#    MakeTheHistogram("VisibleMass_","_7TeV")
            