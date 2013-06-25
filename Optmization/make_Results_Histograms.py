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
DIR_ROOT = 'outRoot/'


def SET(bb,signal, mass, channel,HiggsMass ):
    myfile = TFile(DIR_ROOT + str(signal) + str(mass) + '.root')
    Histo =  myfile.Get(HiggsMass + str(channel)+"_pp")
    binCont = 0
    binErr = 0
    if Histo:
        Histo.Rebin(reb_)
        binCont = Histo.GetBinContent(bb)
        binErr = Histo.GetBinError(bb)
    myfile.Close()
    return binCont , binErr

#if __name__ == "__main__":
def MakeTheHistogram(fileOutName, histoName):
    myOut = TFile(fileOutName, 'RECREATE')
#    myOut = TFile('TotalRootForLimit.root', 'RECREATE')
    HiggsMass = histoName
    Table_File = TFile('FullResults.root')
    Table_Hist = Table_File.Get('FullResults')
    channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
    signal = ['zhtt','zhww']
    signalname = ['ZH_htt','ZH_hww']
    mass = [110, 115, 120, 125, 130, 135, 140, 145]
    BackGround = ['ZZ4L','Data']
    BackGroundname = ['ZZ','data_obs']
    lenghtSig = len(signal) * len(mass)

    for chl in range(len(channel)):
        print channel[chl]
        MMM= myOut.mkdir(str(channel[chl])+'_zh')
        MMM.cd()
        ###################################### Filling Signal ZH and WH ########
        for sig in range(len(signal)):
            for m in range(len(mass)):#    for m in range(110, 145, 5):
                MMM.cd()
                normal = Table_Hist.GetBinContent(chl + 1, sig * len(mass) + m + 1)
                NewHist =TH1F(str(signalname[sig]) + str(mass[m]),"",n_bin,low_bin,high_bin)
                for bb in range(0,n_bin):
                    NewHist.SetBinContent(bb,SET(bb,signal[sig], mass[m], channel[chl], HiggsMass)[0])
                    NewHist.SetBinError(bb,SET(bb,signal[sig], mass[m], channel[chl],HiggsMass)[1])

                if NewHist.Integral(): NewHist.Scale(normal/NewHist.Integral())
                myOut.Write()
        ###################################### Filling Reducible ########
        MMM.cd()
        normal = Table_Hist.GetBinContent(chl + 1, lenghtSig  + 2)
        NewHist =TH1F('Zjets',"",n_bin,low_bin,high_bin)
        myfile = TFile(DIR_ROOT + 'Data.root')
        Histo =  myfile.Get("VisibleMass_Shape_"+ channel[chl])
        Histo.Rebin(reb_)
        for bb in range(0,n_bin):
            NewHist.SetBinContent(bb,Histo.GetBinContent(bb))
            NewHist.SetBinError(bb,Histo.GetBinError(bb))
        NewHist.Scale(normal/NewHist.Integral())
        myOut.Write()
        ###################################### Filling ZZ and Data ########
        for bg in range (len(BackGround)):
            MMM.cd()
            normal = Table_Hist.GetBinContent(chl + 1, lenghtSig + bg + 3)
            NewHist =TH1F(BackGroundname[bg],"",n_bin,low_bin,high_bin)
            myfile = TFile(DIR_ROOT + str(BackGround[bg]) + '.root')
            Histo = myfile.Get(HiggsMass + str(channel[chl])+"_pp")
            Histo.Rebin(reb_)
            for bb in range(0,n_bin):
                NewHist.SetBinContent(bb,Histo.GetBinContent(bb))
                NewHist.SetBinError(bb,Histo.GetBinError(bb))
            myfile.Close()
            NewHist.Scale(normal/NewHist.Integral())
            myOut.Write()
if __name__ == "__main__":
    MakeTheHistogram("TotalRootForLimit_SV.root", "SVMass_")
    MakeTheHistogram("TotalRootForLimit_Visible.root", "VisibleMass_")
            