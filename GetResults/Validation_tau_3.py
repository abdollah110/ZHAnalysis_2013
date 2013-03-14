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
from ROOT import gSystem
from ROOT import gStyle

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
#    file_BGNormalization = TFile("Estim_tt_ptDep.root", "OPEN")
    file_BGNormalization = TFile("Estim_tt_ptEtaDep.root", "OPEN")

    hist_BGNormalization = file_BGNormalization.Get("histo_Reducible")

#    BGNormalization = int(hist_BGNormalization.Integral())
    BGNormalization = 73

    _file_input = TFile("valid_tt.root", "OPEN")
    hist_Data = _file_input.Get("VisibleMass_pp")
    hist_Estimation_fp = _file_input.Get("VisibleMass_fp")
    hist_Estimation_ff = _file_input.Get("VisibleMass_ff")
#    hist_Estimation3 = _file_input.Get("VisibleMass_fp")

    hist_Data.GetYaxis().SetTitle("# of Events");
    hist_Data.GetXaxis().SetTitle("di-#tau visible mass [GeV]");
    hist_Data.Rebin(reB)
    hist_Data.SetMarkerStyle(20)
    hist_Data.SetMarkerSize(1.3)
    hist_Data.Draw("pe")
    DataNormalization = int(hist_Data.Integral())
    print "Data integral=  " , DataNormalization

    hist_Estimation_fp.Rebin(reB)
    hist_Estimation_fp.Scale(BGNormalization / hist_Estimation_fp.Integral())
    print hist_Estimation_fp.Integral()
    hist_Estimation_fp.SetLineColor(3)
    hist_Estimation_fp.SetLineWidth(3)
    hist_Estimation_fp.SetFillStyle(3010)
    hist_Estimation_fp.Draw('same')

    hist_Estimation_ff.Rebin(reB)
    hist_Estimation_ff.Scale(BGNormalization/hist_Estimation_ff.Integral())
    hist_Estimation_ff.SetLineColor(2)
    hist_Estimation_ff.SetLineWidth(3)
#    hist_Estimation_ff.SetFillStyle(3010)
    hist_Estimation_ff.Draw("same")
#
#    hist_Estimation3.Rebin(reB)
#    hist_Estimation3.Scale(BGNormalization/hist_Estimation3.Integral())
#    hist_Estimation3.SetLineColor(4)
##    hist_Estimation3.SetFillStyle(3010)
#    hist_Estimation3.Draw("same")

   

    l = TLegend(0.40, 0.70, 0.7, 0.9, "", "brNDC")
    l.SetBorderSize(0)
    l.SetFillColor(0)
    l.SetTextSize(.03)
    l.AddEntry(hist_Data, "Data", "p")
    l.AddEntry(hist_Estimation_fp, "BG Est.(one  tau Iso Reverted)", "lpf")
    l.AddEntry(hist_Estimation_ff, "BG Est.(both tau Iso Reverted)", "lpf")
    l.Draw()

    #Text in Histogram
    t = TLatex()
    t.SetNDC()
    t.SetTextFont(62)
    t.SetTextAlign(12)
    t.SetTextSize(0.025)
    t.DrawLatex(0.1, .92, "CMS Preliminary 2012")
    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.0 fb^{-1}")
    t.DrawLatex(0.5, .52, "Data = " + str(DataNormalization) + ",   Estimation = " + str(BGNormalization) )
    t.DrawLatex(0.5, .45, "#tau_{PT} > 15 GeV ")



    canvas.SaveAs("tau_validation_15_pt_eta_chang_Medium.pdf")
