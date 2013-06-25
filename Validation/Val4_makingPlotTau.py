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
    hist_Data = _file_input.Get("H_SVMass_lltt_pp")
    XXX = _file_input.Get("H_SVMass_Shape_lltt_07")
    XXX.Rebin(reB)

    hist_Data.GetYaxis().SetTitle("# of Events");
    hist_Data.GetXaxis().SetTitle("di-#tau  mass [GeV]");
    hist_Data.GetYaxis().SetLabelSize(.03);
    hist_Data.GetXaxis().SetLimits(0, 300)
    hist_Data.Rebin(reB)
    hist_Data.SetMarkerStyle(20)
    hist_Data.SetMarkerSize(1.3)
    hist_Data.Draw("pe")
    DataNormalization = int(hist_Data.Integral())
    print "Data integral=  ", DataNormalization

# Using OLDVal3____.py
#    testFiles = ['tauFR_pt.root']
    testFiles = [ 'tauCloseJet_pt.root','tauCloseJet_ptEta.root']
#    testFiles = ['tauFR_pt.root', 'tauCloseJet_pt.root', 'tauRefJet_pt.root','tauFR_ptEta.root', 'tauCloseJet_ptEta.root', 'tauRefJet_ptEta.root']
#    testFiles = ['tauFRx0.8.root', 'tauFRx0.9.root', 'tauFRx1.0.root','tauFRx1.1.root', 'tauFRx1.2.root']
    outHist = [0] * 6
    outFile = [0] * 6
    outName = [0] * 6
    outEst = [0] * 6
    for i in range(len(testFiles)):
        outFile[i] = TFile(testFiles[i], "OPEN")
        hist_BGNormalization = outFile[i].Get("histo_Reducible")
        outHist[i] = XXX.Clone()

        BGNormalization = int(hist_BGNormalization.GetBinContent(1)+hist_BGNormalization.GetBinContent(5))
        outHist[i].Scale(BGNormalization / outHist[i].Integral())
        print i, outHist[i].GetName(), outHist[i].Integral()
        clr =  i+1
        if i==4: clr = 7
        outHist[i].SetLineColor(clr)
        outHist[i].SetLineWidth( 2)
        outHist[i].GetXaxis().SetLimits(0, 300)
        outHist[i].Draw("same")
        outName[i]=testFiles[i][:-5]
        outEst[i]=BGNormalization


   

    l = TLegend(0.40, 0.70, 0.7, 0.9, "", "brNDC")
    l.SetBorderSize(0)
    l.SetFillColor(0)
    l.SetTextSize(.03)
#    l.AddEntry(hist_Data, "Data", "p")
#    l.AddEntry(outHist[i], "BG Est.(one  tau Iso Reverted)", "lpf")
#    l.AddEntry(hist_Estimation_ff, "BG Est.(both tau Iso Reverted)", "lpf")
    l.Draw()

    #Text in Histogram
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary 2012")
    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.0 fb^{-1}")
    t.DrawLatex(0.5, .60, "Data, SS, 10 GeV Tau LooseIso")
    t.DrawLatex(0.5, .52, "Data = " + str(DataNormalization) )
    for i in range(len(testFiles)):
        clr =  i+1
        if i==4: clr = 7
        t.SetTextColor(clr)
        t.DrawLatex(0.5, .52-((i+1)/20.),  outName[i] +" = " + str(outEst[i]) )



    canvas.SaveAs("Compare_tauFR2.pdf")
    canvas.SaveAs("Compare_tauFR2.eps")
    canvas.SaveAs("Compare_tauFR2.png")
