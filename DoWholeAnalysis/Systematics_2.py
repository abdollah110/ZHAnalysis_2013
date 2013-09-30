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

channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]

def MakeTheHistogram(histoName,CoMEnergy):
    Table_File = TFile("Yield"+CoMEnergy+""+".root")
    Table_Hist = Table_File.Get('FullResults')

    for chl in range(len(channel)):
#        print "--------------------------------------------------------------------"
        norm = Table_Hist.GetBinContent(chl + 1, 1)
        tauUp = Table_Hist.GetBinContent(chl + 1, 2)
        tauDown = Table_Hist.GetBinContent(chl + 1, 3)
        lepUp = Table_Hist.GetBinContent(chl + 1, 4)
        lepDown = Table_Hist.GetBinContent(chl + 1, 5)
#        print channel[chl], "  Tau Systematic: Up= ", math.ceil((tauUp-norm)/norm *100)  ,"%"
#        print channel[chl], "  EMU Systematic: Up= ", math.ceil((lepUp-norm)/norm *100)  ,"%"
        print channel[chl], "  Tau Systematic: = +", math.ceil((tauUp-norm)/norm *100)  ,"%", "", math.ceil((tauDown-norm)/norm *100) , "%"
        print channel[chl], "  EMU Systematic: = +", math.ceil((lepUp-norm)/norm *100)  ,"%", "", math.ceil((lepDown-norm)/norm *100) , "%"
#        print channel[chl], "  Tau Systematic: Up= ", math.ceil((tauUp-norm)/norm *100)  ,"%","   Down= ", math.ceil((tauDown-norm)/norm *100) , "%"
#        print channel[chl], "  EMU Systematic: Up= ", math.ceil((lepUp-norm)/norm *100)  ,"%", "  Down= ", math.ceil((lepDown-norm)/norm *100) , "%"
            
if __name__ == "__main__":
    MakeTheHistogram("SVMass_","_8TeV")
            