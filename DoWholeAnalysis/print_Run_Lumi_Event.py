#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="abdollahmohammadi"
__date__ ="$Nov 26, 2013 3:14:19 PM$"

import ROOT
from ROOT import Double
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TLatex
from ROOT import TLegend
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import TTree
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gStyle
from ROOT import gSystem
import numpy as n
import os

rootInput=ROOT.TFile.Open("outRoot_V3_Debug7TeV/Data_7TeV.root", "READ")
firstTr = rootInput.Get("BG_Tree")

for entry in xrange(firstTr.GetEntries()):
    firstTr.GetEntry(entry)
#            if (entry % 20000 == 0): print "Entry is : ", entry
#        print "Hi"
#        if firstTr.subChannel_ == 3:
#        print firstTr.GetEntries()
    
#    if (firstTr.subChannel_ == 3):
    if (firstTr.Lumi_ == 40):
            print "Channel= ", firstTr.Channel_ , "  Run= ", firstTr.Run_, "  Lumi=", firstTr.Lumi_, "  Event= ", firstTr.Event_, "  L3Pt= ", firstTr.l3Pt_, " L4Pt=", firstTr.l4Pt_,  "  SVMass=", firstTr.SVMass_
