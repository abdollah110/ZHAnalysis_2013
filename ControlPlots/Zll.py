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
from ROOT import TLatex
from ROOT import TLegend
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
#ROOT.gROOT.ProcessLine('.x rootlogon.C')
DIR_ROOT = "../ROOTFiles_V3/Results/"


def luminosity(CoMEnergy):
    if CoMEnergy == '_8TeV': return  19712 #19242
    if CoMEnergy == '_7TeV': return  4982

def XSection(mX,CoMEnergy ):
    if CoMEnergy == '_8TeV':
        if mX == 110: return  [.00471, .00206]
        if mX == 115:  return [.00392, .00336]
        if mX == 120:  return [.00319, .00479]
        if mX == 125:  return [.00251, .00640]
        if mX == 130:  return [.00191, .00789]
        if mX == 135:  return [.00139, .00917]
        if mX == 140:  return [.00097, .0102] # changed 0.0101 to 0.0102
        if mX == 145:  return [.00064, .0107] # Changed from 0.0140 to 0.0107
        if mX == 'ZZ4L': return 0.130
        if mX == 'Data': return 1
        if mX == 'TT2L2Nu': return 23.64
        if mX == 'GGToZZ2L2L': return 0.01203
        if mX == 'GGToZZ4L': return 0.0048
        if mX == 'TTZJets': return 0.208
        if mX == 'WZ3L': return 0
        if mX == 'WZJets3L': return 1.057
        if mX == 'DYJets': return 3504.
        if mX == 'TTJets_FullLep': return 26.20

    if CoMEnergy == '_7TeV':
        if mX == 110: return  [0.003815, .00177]
        if mX == 115:  return [0.003173 , .00275]
        if mX == 120:  return [0.002580, .00395]
        if mX == 125:  return [0.002032, .00522]
        if mX == 130:  return [0.001538 , .00645]
        if mX == 135:  return [0.001120, .00748]
        if mX == 140:  return [0.000777, .00822]
        if mX == 145:  return [0.000509, .00873]
        if mX == 'ZZ4L': return 0.106
        if mX == 'Data': return 1
        if mX == 'WZ3L': return 1.057  # need to be change
        if mX == 'TT2L2Nu': return 17.32  # need to be change
        if mX == 'GGToZZ2L2L': return 0.00348
        if mX == 'GGToZZ4L': return 0.00174
        if mX == 'TTZJets': return 0.139
        if mX == 'WZ3L': return 0
        if mX == 'WZJets3L': return 0.868
        if mX == 'DYJets': return 3048.
        if mX == 'TTJets_FullLep': return 17.32
        
def MakeHistogram(BackGround, Plot,CoMEnergy, ):
    canvas = TCanvas()
    gStyle.SetOptStat(0)
    gStyle.SetOptStat(0);
    gStyle.SetOptTitle(0);
    canvas.SetFillColor(0)

    file_default=TFile(DIR_ROOT + 'Data'+CoMEnergy+'.root')
    histo_default= file_default.Get(Plot)
    histo_default.GetXaxis().SetRangeUser(60, 120);
#    maxvalueY = histo_default.GetMax()
    histo_default.GetYaxis().SetRangeUser(0, 1400000);
#    histo_default.Scale()
    histo_default.SetLineColor(0)
    histo_default.Draw()
    
    for eachBG in BackGround:
        file_dy=TFile(DIR_ROOT + eachBG+CoMEnergy+".root")
        histo_dy= file_dy.Get(Plot)
        Histo = file_dy.Get("TotalEventsNumber") # to get Total number of events
        value =  luminosity(CoMEnergy) * XSection(eachBG, CoMEnergy) / Histo.Integral()
        histo_dy.SetFillColor(3)
        print value
        histo_dy.Scale(value)
        histo_dy.Draw("same")

    


    file_data=TFile(DIR_ROOT + 'Data'+CoMEnergy+'.root')
    histo_data= file_data.Get(Plot)
    histo_data.SetMarkerStyle(20);
    histo_data.SetMarkerColor(1);
    histo_data.SetMarkerSize (1.01);
    histo_data.Draw("psame")



    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.3, .92, "CMS Preliminary 2012")
    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.7 fb^{-1}")
    t.DrawLatex(0.6, .72, Plot+CoMEnergy )



    canvas.SaveAs("zll_"+Plot+CoMEnergy+".pdf")


            
if __name__ == "__main__":

    BackGround=["DYJets"]
    MakeHistogram(BackGround,"Zboson_Mass_EE_PUCor","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_EE_PU","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_EE_Cor","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_EE_","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_MM_PUCor","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_MM_PU","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_MM_Cor","_8TeV")
    MakeHistogram(BackGround,"Zboson_Mass_MM_","_8TeV")


            
