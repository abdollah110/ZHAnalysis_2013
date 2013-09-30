#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollahmohammadi"
__date__ = "$Mar 8, 2013 3:00:22 PM$"

import math

import ROOT
from ROOT import Double
from ROOT import TAxis
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

if __name__ == "__main__":


    canvas = TCanvas("canvas", "", 600, 600)
    gStyle.SetOptStat(0);
    gStyle.SetOptTitle(0);
    canvas.SetFillColor(0)
    canvas.SetTitle("qqqqqq")
    canvas.SetName("")
    canvas.SetBorderMode(0)
    canvas.SetBorderSize(2)
    canvas.SetFrameBorderMode(0)
    canvas.SetFrameLineWidth(2)
    canvas.SetFrameBorderMode(0)

    reB = 20
    

    _file_input = TFile("valid_Mega.root", "OPEN")
    hist_Data = _file_input.Get("SVMass_Shape_lltt_MVAIso0.2_LT30")

    hist_Data.GetYaxis().SetTitle("a.u.");
    hist_Data.GetYaxis().SetLabelSize(.03);
    hist_Data.GetXaxis().SetLimits(0, 300)
    hist_Data.GetXaxis().SetTitle("m_{#tau#tau} [GeV]");
    hist_Data.SetMinimum(0);
    hist_Data.SetMaximum(0.4);

    hist_Data.Rebin(reB)
    hist_Data.SetLineColor(0)
    hist_Data.Draw()


    testFiles = ['SVMass_Shape_lltt_MVAIso0.3_LT70', 'SVMass_Shape_lltt_MVAIso0.5_LT70', 'SVMass_Shape_lltt_MVAIso0.7_LT70']
    legName = ['MVAIso > 0.3', 'MVAIso > 0.5', 'MVAIso > 0.7']
#    testFiles = ['SVMass_Shape_lltt_MVAIso0.3_LT30','SVMass_Shape_lltt_MVAIso0.3_LT50', 'SVMass_Shape_lltt_MVAIso0.3_LT70']
#    legName = ['LT > 30', 'LT > 50', 'LT > 70']

    outHist = [0] * 6
    outFile = [0] * 6
    outName = [0] * 6
    outEst = [0] * 6
    for i in range(len(testFiles)):
        outHist[i] = _file_input.Get(testFiles[i])
        print outHist[i].GetName(), outHist[i].Integral()
        outHist[i].Rebin(reB)
        outHist[i].SetLineColor(i+1 )
        outHist[i].SetLineStyle(2*i + 1)
        outHist[i].SetLineWidth(5)
        outHist[i].DrawNormalized("same")
        outName[i] = testFiles[i]
        
    #Text in Histogram
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary 2012")
    t.DrawLatex(0.4, .92, "#sqrt{s} = 8 TeV, L = 19.7 fb^{-1}")
    t.DrawLatex(0.7, .92, "SS Data")
    t.DrawLatex(0.8, .92, "ll#tau#tau")
#    for i in range(len(testFiles)):
#        t.SetTextColor(i + 1)
#        t.DrawLatex(0.5, .87-((i + 1) / 20.), legName[i])

    legend_ =  TLegend(0.6, 0.6, 0.9, 0.9)
    legend_.SetFillColor(0)
    legend_.SetBorderSize(0)
    legend_.SetTextSize(.04)
    for i in range(len(testFiles)):
        legend_.AddEntry(outHist[i], legName[i], "l");
        legend_.Draw();

    canvas.SaveAs("ChaeckBias1.pdf")
