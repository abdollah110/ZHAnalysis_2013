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
import os

  ###########   Parameters  ##########
FitType = ["SV_"] #Two types of the limit
#FitType = ["Visible_","SV_"] #Two types of the limit
limitDir = "limitDir/"
#limitDir = "final_LimitRoot_NewSystematics/"
#limitDir = "limitDir/"
    

def DoMakeHistoFRomLimitTree(Channel, FirstIsoCut, SecondIsoCut, LTCut):
    print "\n\n*********************" , Channel
    for cut0 in FitType:
        outPutFile = TFile("OutFile_" +str(cut0)+Channel+".root", "RECREATE")
        outHist = ["YY","XX","YY","XX","XX"]
        for cut1 in range(len(FirstIsoCut)):
            for cut2 in range(len(SecondIsoCut)):
                outHist[cut2] = TH1F(str(SecondIsoCut[cut2]), "", 10,0,10)
                for cut3 in range(len(LTCut)):
                    name=  str(cut0) + Channel + "_" + str(FirstIsoCut[cut1]) + "_" + str(SecondIsoCut[cut2]) + "_" + str(LTCut[cut3])
                    if (Channel == "TT"): name=  str(cut0) + Channel + "_" + str(SecondIsoCut[cut2]) + "_" + str(FirstIsoCut[cut1]) + "_" + str(LTCut[cut3])
                    nameRoot = name + ".root"
                    nameCard = name + ".txt"
                    MainName = limitDir + "higgsCombine" + name + ".Asymptotic.mH125.root"
                    inputFile = ROOT.TFile.Open(MainName, "READ")
                    inputTree = inputFile.Get('limit')

                    for i in xrange(inputTree.GetEntries()):
                        inputTree.GetEntry(i)
                        if (inputTree.quantileExpected == 0.5):
                            print MainName, inputTree.limit
                            outHist[cut2].SetBinContent(cut3+1,inputTree.limit)

                outPutFile.cd()
                outHist[cut2].Write()

                
def DoCompareLimitPlots(Channel, tauIsolation, leptonIsolation, LTCut,lowY, highY):
    print "\n\n*********************" , Channel
    for cut0 in FitType:
        Hist = ['hist0', 'hist1', 'hist2', 'hist3']

        canvas = TCanvas()
        gStyle.SetOptStat(0)
        gStyle.SetOptStat(0);
        gStyle.SetOptTitle(0);
        canvas.SetFillColor(0)
        canvas.SetGridx()
        canvas.SetGridy()

        HistBG = TH1F("BG", "", 10, 0, 10)
        HistBG.GetXaxis().SetRangeUser(0, 4)
        HistBG.GetXaxis().SetLabelSize(.05)
        HistBG.GetXaxis().SetTitle("LT(=Pt_{l1} + Pt_{l2}) [GeV]")
        HistBG.GetXaxis().SetTitleOffset(1.4)
        HistBG.GetYaxis().SetRangeUser(lowY, highY)
        HistBG.GetYaxis().SetTitle("Expected Limit")
        for i in range(len(LTCut)):
            HistBG.GetXaxis().SetBinLabel(i + 1, str(LTCut[i]))
        HistBG.Draw()

        InFile = ROOT.TFile.Open("OutFile_" +cut0+Channel+".root", "READ")
        for j in range(len(leptonIsolation)):
            Hist[j] = InFile.Get(str(leptonIsolation[j]))
            Hist[j].SetMarkerStyle(20)
            Hist[j].SetMarkerSize(1.3)
            Hist[j].SetLineWidth(2)
            Hist[j].SetLineColor(j + 6)
            Hist[j].Draw("Plsame")

        l = TLegend(0.70, 0.70, 0.9, 0.9, "", "brNDC")
        l.SetBorderSize(0)
        l.SetFillColor(0)
        l.SetTextSize(.03)
        for k in range(len(leptonIsolation)):
            lgnd = "Isolation < " + str(leptonIsolation[k])
            l.AddEntry(Hist[k], lgnd, "lpf")
        l.Draw()

        #Text in Histogram
        t = TLatex()
        t.SetNDC()
        t.SetTextFont(62)
        t.SetTextAlign(12)
        t.SetTextSize(0.035)
        t.DrawLatex(0.1, .92, "CMS Preliminary 2012")
        t.DrawLatex(0.35, .92, "#sqrt{s} = 8 TeV, L = 19.8 fb^{-1}")
        t.SetTextColor(2)
        t.DrawLatex(0.65, .92, " LL"+Channel)
        t.DrawLatex(0.75, .92, cut0+"Mass")


        canvas.SaveAs("finalCompare_"+cut0 + Channel + "_NewSystematic.pdf")



if __name__ == "__main__":


    lowY = 11
    highY = 19
    tauIsolation = ["3HitL", "3HitM", "MVAL", "MVAM"]
    leptonIsolation = [0.3]
    LTCut = [60, 65,70,75, 80]
#    LTCut = [60, 65,70,75, 80, 85]
    DoMakeHistoFRomLimitTree("TT",leptonIsolation, tauIsolation,  LTCut)
    DoCompareLimitPlots("TT", leptonIsolation,tauIsolation,  LTCut, lowY, highY)


#    lowY = 8.1
#    highY = 8.5
    lowY = 8
    highY = 10
    tauIsolation = ["3HitL"]
    leptonIsolation = [   0.20, 0.25, 0.30, 0.35]
#    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [ 35,40,45, 50,55]
    DoMakeHistoFRomLimitTree("MT", tauIsolation, leptonIsolation, LTCut)
    DoCompareLimitPlots("MT", tauIsolation, leptonIsolation, LTCut, lowY, highY)



    lowY = 12
    highY = 16
    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30, 0.35]
    LTCut = [25,30, 35,40,45]
#    LTCut = [ 35,40,45, 50, 55]
    DoMakeHistoFRomLimitTree("ET", tauIsolation, leptonIsolation, LTCut)
    DoCompareLimitPlots("ET", tauIsolation, leptonIsolation, LTCut, lowY, highY)


    lowY = 5
    highY = 7
    tauIsolation = ["3HitL"]
    leptonIsolation = [ 0.20, 0.25, 0.30,0.35]
    LTCut = [20,25, 30,35, 40]
    DoMakeHistoFRomLimitTree("EM", tauIsolation, leptonIsolation, LTCut)
    DoCompareLimitPlots("EM", tauIsolation, leptonIsolation, LTCut, lowY, highY)
