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
from ROOT import gStyle
from ROOT import gSystem

gROOT.Reset()
import os
ROOT.gROOT.SetBatch(True)

channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
syst = ["norm", "tauUp","tauDown","lepUp","lepDown"]

def make2DTable(PostFix,CoMEnergy):
    myOut = TFile("Yield"+CoMEnergy+PostFix+".root", 'RECREATE')
    FullResults  = TH2F('FullResults', 'FullResults', 10, 0, 10, 22, 0, 22)
    
    for chl in range(len(channel)):
        print "starting channel", channel[chl]
        for ivale in range(len(syst)):
            myfile = TFile('Reducible_'+syst[ivale]+'.root')
            Histo = myfile.Get('histo_Reducible')
            value = Histo.GetBinContent(chl + 1)
            value = round(value, 4)
            FullResults.SetBinContent(chl + 1, ivale+1, value)
            FullResults.Fill(9, ivale, value)
            FullResults.GetYaxis().SetBinLabel(ivale+1, syst[ivale])
        FullResults.GetXaxis().SetBinLabel(chl + 1, channel[chl])
    myOut.Write()
    myCanvas = TCanvas()
    gStyle.SetOptStat(0)
    FullResults.Draw('text')
    myCanvas.SaveAs("tableAll"+PostFix+CoMEnergy+".pdf")


if __name__ == "__main__":
    make2DTable("", "_8TeV")
    