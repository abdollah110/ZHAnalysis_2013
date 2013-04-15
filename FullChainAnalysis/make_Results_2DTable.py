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
#ROOT.gROOT.ProcessLine('.x rootlogon.C')
HiggsMass = "H_VisibleMass_"
OriginRootDir = '../NewResults/'
SubRootDir = 'outRoot/'
luminosity = 19242
def XSection(mX):
    if mX == 110: return  [.00471, .00206]
    if mX == 115:  return [.00392, .00336]
    if mX == 120:  return [.00319, .00479]
    if mX == 125:  return [.00251, .00640]
    if mX == 130:  return [.00191, .00789]
    if mX == 135:  return [.00139, .00917]
    if mX == 140:  return [.00097, .0101]
    if mX == 145:  return [.00064, .0142]
    if mX == 'ZZ4L': return 0.130
    if mX == 'Data': return 1
    if mX == 'WZ3L': return 1.057
    if mX == 'TT2L2Nu2B': return 23.64

if __name__ == "__main__":

    myOut = TFile('FullResults.root', 'RECREATE')
    FullResults  = TH2F('FullResults', 'FullResults', 10, 0, 10, 22, 0, 22)
    channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
    signal = ['zhtt', 'zhww']
#    mass = [110, 115, 120, 125, 130, 135, 140, 145]
    mass = [110, 115, 120, 125, 130,135,140,145]
    BackGround = ['ZZ4L', 'Data']
    lenghtSig = len(signal) * len(mass)
    
    for chl in range(len(channel)):
        print "starting channel", channel[chl]
        ###################################### Filling Signal ZH and WH ########
        for sig in range(len(signal)):
            print "starting signal", signal[sig]
            for m in range(len(mass)):#    for m in range(110, 145, 5):
                myfile = TFile(OriginRootDir + str(signal[sig]) + str(mass[m]) + '.root')
                Histo = myfile.Get(str(channel[chl]))  # to get Total number of events
                myfileSub = TFile(SubRootDir + str(signal[sig]) + str(mass[m]) + '.root')
                HistoSub = myfileSub.Get(HiggsMass+str(channel[chl]))
                value = 0
                if (HistoSub): value = HistoSub.Integral() * luminosity * XSection(mass[m])[sig] / Histo.GetBinContent(1)
                value = round(value, 4)
                FullResults.SetBinContent(chl + 1, sig * len(mass) + m + 1, value)
                FullResults.Fill(9, sig * len(mass) + m, value)
                FullResults.GetYaxis().SetBinLabel(sig * len(mass) + m + 1, str(signal[sig]) + str(mass[m]))
        #######################################  Filling Reducible BG ##########
        print "starting reducible"
        myfile = TFile('Reducible.root')
        Histo = myfile.Get('histo_Reducible')
        value = Histo.GetBinContent(chl + 1)
        value = round(value, 4)
        FullResults.SetBinContent(chl + 1, lenghtSig  + 2, value)
        FullResults.Fill(9, lenghtSig + 1, value)
        FullResults.GetYaxis().SetBinLabel(lenghtSig  + 2, 'Reducible')
        #######################################   Filling BG and Data  #########
        for bg in range (len(BackGround)):
            print "starting BG", BackGround[bg]
            myfile = TFile(OriginRootDir + str(BackGround[bg]) + '.root')
            Histo = myfile.Get(str(channel[chl])) # to get Total number of events
            myfileSub = TFile(SubRootDir + str(BackGround[bg]) + '.root')
            HistoSubB = myfileSub.Get(HiggsMass+str(channel[chl]))
            value = HistoSubB.Integral() * luminosity * XSection(BackGround[bg]) / Histo.GetBinContent(1)
            value = round(value, 4)
            if BackGround[bg] == 'Data':
                value = HistoSubB.Integral()
            FullResults.SetBinContent(chl + 1, lenghtSig + bg + 3, value)
            FullResults.Fill(9, lenghtSig + bg + 2, value)
            FullResults.GetYaxis().SetBinLabel(lenghtSig  + bg + 3, str(BackGround[bg]))
        ########################################################################
        FullResults.GetXaxis().SetBinLabel(chl + 1, channel[chl])
    myOut.Write()
    myCanvas = TCanvas()
    gStyle.SetOptStat(0)
    FullResults.Draw('text')
    myCanvas.SaveAs("tableAll.pdf")
    