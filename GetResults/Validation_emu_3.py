#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollahmohammadi"
__date__ = "$Mar 8, 2013 3:00:22 PM$"

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

if __name__ == "__main__":

    myCanvs = TCanvas('canvas')
    myCanvs.cd()

    reB = 10
    file_BGNormalization = TFile("Reducible_valid_lt.root", "OPEN")
    hist_BGNormalization = file_BGNormalization.Get("histo_Reducible")
    BGNormalization = hist_BGNormalization.Integral()
#    BGNormalization = 72.43

    _file_input = TFile("valid_lt.root", "OPEN")
    hist_Data = _file_input.Get("VisibleMass_pp")
    hist_Estimation1 = _file_input.Get("VisibleMass_ff")
#    hist_Estimation2 = _file_input.Get("VisibleMass_ff")
#    hist_Estimation3 = _file_input.Get("VisibleMass_fp")

    hist_Data.Rebin(reB)
    print hist_Data.Integral()
    hist_Data.Draw("pe")

    hist_Estimation1.Rebin(reB)
    hist_Estimation1.Scale(BGNormalization/hist_Estimation1.Integral())
    print hist_Estimation1.Integral()
    hist_Estimation1.SetLineColor(3)
    hist_Estimation1.SetFillStyle(3010)
    hist_Estimation1.Draw('same')

#    hist_Estimation2.Rebin(reB)
#    hist_Estimation2.Scale(BGNormalization/hist_Estimation2.Integral())
#    hist_Estimation2.SetLineColor(2)
##    hist_Estimation2.SetFillStyle(3010)
#    hist_Estimation2.Draw("same")
#
#    hist_Estimation3.Rebin(reB)
#    hist_Estimation3.Scale(BGNormalization/hist_Estimation3.Integral())
#    hist_Estimation3.SetLineColor(4)
##    hist_Estimation3.SetFillStyle(3010)
#    hist_Estimation3.Draw("same")


    myCanvs.SaveAs("hist.root")
    myCanvs.SaveAs("hist.pdf")
