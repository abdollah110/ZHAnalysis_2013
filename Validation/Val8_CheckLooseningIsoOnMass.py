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
from ROOT import TLatex
from ROOT import TLegend
from ROOT import TNtuple
from ROOT import TProfile
from ROOT import gBenchmark
from ROOT import gROOT
from ROOT import gRandom
from ROOT import gStyle
from ROOT import gSystem
from ROOT import TAxis

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
    hist_Data = _file_input.Get("VisibleMass_Shape_lltt")

    hist_Data.GetYaxis().SetTitle("a.u.");
    hist_Data.GetYaxis().SetLabelSize(.03);
    hist_Data.GetXaxis().SetLimits(0, 300)
    hist_Data.GetXaxis().SetTitle("#tau#tau mass [GeV]");
    hist_Data.SetMinimum(0);
    hist_Data.SetMaximum(0.4);

    hist_Data.Rebin(reB)
    hist_Data.SetLineColor(0)
    hist_Data.Draw()

    testFiles = ['SVMass_Shape_lltt_00','SVMass_Shape_lltt_04', 'SVMass_Shape_lltt_05','SVMass_Shape_lltt_06','SVMass_Shape_lltt_07', 'SVMass_Shape_lltt_08']
#    testFiles = ['OS_H_SVMass_Shape_lltt_07','SS_H_SVMass_Shape_lltt_07']
#    testFiles = ['OS_H_VisibleMass_Shape_lltt_07','SS_H_VisibleMass_Shape_lltt_07']
#    testFiles = ['OS_H_VisibleMass_Shape_lltt_07','OS_H_VisibleMass_Shape_lltt_00']
    outHist = [0] * 6
    outFile = [0] * 6
    outName = [0] * 6
    outEst = [0] * 6
    for i in range(len(testFiles)):
        outHist[i] = _file_input.Get(testFiles[i])
        print outHist[i].GetName() , outHist[i].Integral()
        outHist[i].Rebin(reB)
#        outHist[i].SetMinimum(0)
#        outHist[i].SetMaximum(0.6)
#        outHist[i].GetXaxis().SetRangeUser(0, 300);
        outHist[i].SetLineColor(i+1)
        outHist[i].SetLineWidth(2)
        outHist[i].DrawNormalized("same")
        outName[i]=testFiles[i]
        
#        hist_BGNormalization = outFile[i].Get("histo_Reducible")
#        outHist[i] = XXX.Clone()
#
#        BGNormalization = int(hist_BGNormalization.GetBinContent(2)+hist_BGNormalization.GetBinContent(7))
#        BGNormalization += int(hist_BGNormalization.GetBinContent(3)+hist_BGNormalization.GetBinContent(6))
#        outHist[i].Scale(BGNormalization / outHist[i].Integral())
#        print i, outHist[i].GetName(), outHist[i].Integral()
#        outHist[i].SetLineColor(i + 2)
#        outHist[i].SetLineWidth( 2)
#        outHist[i].Draw("same")
#        outName[i]=testFiles[i][:-5]
#        outEst[i]=BGNormalization


   
#
#    l = TLegend(0.40, 0.70, 0.7, 0.9, "", "brNDC")
#    l.SetBorderSize(0)
#    l.SetFillColor(0)
#    l.SetTextSize(.03)
##    l.AddEntry(hist_Data, "Data", "p")
##    l.AddEntry(outHist[i], "BG Est.(one  tau Iso Reverted)", "lpf")
##    l.AddEntry(hist_Estimation_ff, "BG Est.(both tau Iso Reverted)", "lpf")
#    l.Draw()
#
    #Text in Histogram
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary 2012")
    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.0 fb^{-1}")
    t.DrawLatex(0.5, .60, "Data, SS, 10 GeV Tau ")
    for i in range(len(testFiles)):
        t.SetTextColor(i + 1)
        t.DrawLatex(0.5, .52-((i + 1) / 20.), outName[i] )



    canvas.SaveAs("Compare_Charge.pdf")
