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
OriginRootDir = '../ROOTFiles_V3/Results/'
SubRootDir = 'outRoot_V3/'

def luminosity(CoMEnergy):
    if CoMEnergy == '_8TeV': return  19765 #19242
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

#Histogram = "SVMass_"
Histogram = "VisibleMass_"
channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
signal = ['zhtt', 'zhww']
#mass = [ 125]
mass = [110, 115, 120, 125, 130,135,140,145]
#BackGround = ['ZZ4L',  'GGToZZ2L2L']
#BackGround = ['ZZ4L', 'Data', 'GGToZZ2L2L', 'TTZJets']
#BackGround = ['ZZ4L', 'Data', 'GGToZZ2L2L','TTZJets','WZJets3L','WZ3L','TT2L2Nu']
#BackGround = ['ZZ4L',  'GGToZZ2L2L','Data','TTZJets','TT2L2Nu','WZJets3L','TTJets_FullLep','DYJets']
BackGround = ['ZZ4L',  'Data','TTZJets','TTJets_FullLep','WZJets3L','DYJets']
lenghtSig = len(signal) * len(mass)
low_bin = 0
high_bin = 300

def make2DTable(PostFix,CoMEnergy):
    myOut = TFile("Yield"+CoMEnergy+PostFix+".root", 'RECREATE')
    FullResults  = TH2F('FullResults', 'FullResults', 10, 0, 10, 30, 0, 30)
    FullError  = TH2F('FullError', 'FullError', 10, 0, 10, 30, 0, 30)
    
    for chl in range(len(channel)):
        print "starting channel", channel[chl]
        ###################################### Filling Signal ZH and WH ########
        for sig in range(len(signal)):
            for m in range(len(mass)):#    for m in range(110, 145, 5):
                myfile = TFile(OriginRootDir + str(signal[sig]) + str(mass[m]) +CoMEnergy+ '.root')
                Histo = myfile.Get(str(channel[chl]))  # to get Total number of events
                myfileSub = TFile(SubRootDir + str(signal[sig]) + str(mass[m]) +CoMEnergy+ '.root')
                HistoSub = myfileSub.Get(Histogram+str(channel[chl])+"_pp"+PostFix )
                value = 0
                if (HistoSub): value = HistoSub.Integral(low_bin,high_bin) * luminosity(CoMEnergy) * XSection(mass[m], CoMEnergy)[sig] / Histo.GetBinContent(1)
                value = round(value, 3)
                FullResults.SetBinContent(chl + 1, sig * len(mass) + m + 1, value)
                FullResults.Fill(9, sig * len(mass) + m, value)
                FullResults.GetYaxis().SetBinLabel(sig * len(mass) + m + 1, str(signal[sig]) + str(mass[m]))
                ## Do the samw for error
                valueEr = 0
                if (HistoSub): valueEr = math.sqrt(HistoSub.Integral(low_bin,high_bin)) * luminosity(CoMEnergy) * XSection(mass[m], CoMEnergy)[sig] / Histo.GetBinContent(1)
                valueEr = round(valueEr, 3)
                FullError.SetBinContent(chl + 1, sig * len(mass) + m + 1, valueEr)
                FullError.Fill(9, sig * len(mass) + m, valueEr)
                FullError.GetYaxis().SetBinLabel(sig * len(mass) + m + 1, str(signal[sig]) + str(mass[m]))
        #######################################  Filling Reducible BG ##########
        myfile = TFile('Reducible'+CoMEnergy+'.root')
        Histo = myfile.Get('histo_Reducible')
        value = Histo.GetBinContent(chl + 1)
        value = round(value, 3)
        FullResults.SetBinContent(chl + 1, lenghtSig  + 2, value)
        FullResults.Fill(9, lenghtSig + 1, value)
        FullResults.GetYaxis().SetBinLabel(lenghtSig  + 2, 'Reducible')
        #Error
        HistoEr = myfile.Get('histo_ReducibleEr')
        valueEr = HistoEr.GetBinContent(chl + 1)
        valueEr = round(valueEr, 4)
        FullError.SetBinContent(chl + 1, lenghtSig  + 2, valueEr)
        FullError.Fill(9, lenghtSig + 1, valueEr)
        FullError.GetYaxis().SetBinLabel(lenghtSig  + 2, 'ReducibleEr')
        #######################################   Filling BG and Data  #########
        for bg in range (len(BackGround)):
            myfile = TFile(OriginRootDir + str(BackGround[bg]) + CoMEnergy+'.root')
            Histo = myfile.Get(str(channel[chl])) # to get Total number of events
            myfileSub = TFile(SubRootDir + str(BackGround[bg]) + CoMEnergy+'.root')
            HistoSubB = myfileSub.Get(Histogram+str(channel[chl])+"_pp"+PostFix)
            value = 0
            if (HistoSubB): value = HistoSubB.Integral(low_bin,high_bin) * luminosity(CoMEnergy) * XSection(BackGround[bg], CoMEnergy) / Histo.GetBinContent(1)
            value = round(value, 3)
            if BackGround[bg] == 'Data':
                if (HistoSubB): value = HistoSubB.Integral(low_bin,high_bin) # as some data pomits are above 300
            FullResults.SetBinContent(chl + 1, lenghtSig + bg + 3, value)
            FullResults.Fill(9, lenghtSig + bg + 2, value)
            FullResults.GetYaxis().SetBinLabel(lenghtSig  + bg + 3, str(BackGround[bg]))
            ## Do Error
            valueEr = 0
            if (HistoSubB): valueEr = math.sqrt(HistoSubB.Integral(low_bin,high_bin)) * luminosity(CoMEnergy) * XSection(BackGround[bg], CoMEnergy) / Histo.GetBinContent(1)
            valueEr = round(valueEr, 3)
            FullError.SetBinContent(chl + 1, lenghtSig + bg + 3, valueEr)
            FullError.Fill(9, lenghtSig + bg + 2, valueEr)
            FullError.GetYaxis().SetBinLabel(lenghtSig  + bg + 3, str(BackGround[bg]))
        ########################################################################
        FullResults.GetXaxis().SetBinLabel(chl + 1, channel[chl])
        FullError.GetXaxis().SetBinLabel(chl + 1, channel[chl])
    myOut.Write()
    myCanvas = TCanvas()
    gStyle.SetOptStat(0)
    FullResults.Draw('text')
    myCanvas.SaveAs("tableAll"+PostFix+CoMEnergy+".pdf")
    myCanvasEr = TCanvas()
    gStyle.SetOptStat(0)
    FullError.Draw('text')
    myCanvasEr.SaveAs("ErrorAll"+PostFix+CoMEnergy+".pdf")


if __name__ == "__main__":
    make2DTable("", "_8TeV")
#    make2DTable("_Up", "_8TeV")
#    make2DTable("_Down", "_8TeV")
#    make2DTable("", "_7TeV")
#    make2DTable("_Up", "_7TeV")
#    make2DTable("_Down", "_7TeV")
    