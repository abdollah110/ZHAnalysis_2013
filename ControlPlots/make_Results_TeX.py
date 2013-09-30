#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.
#http://root.cern.ch/viewvc/trunk/tutorials/pyroot/hsimple.py?revision=20881&view=markup
__author__ = "abdollahmohammadi"
__date__ = "$Feb 23, 2013 10:39:33 PM$"

import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser
import math
import ROOT
import sys
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

gROOT.Reset()
import os
ROOT.gROOT.SetBatch(True)

BLIND = False
channel = ["mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"]
signal = ['zhtt','zhww']
signalname = ['ZH_htt','ZH_hww']
mass = [110, 115, 120, 125, 130, 135, 140, 145]
BackGround = ['ZZ4L',  'Data','TTZJets','TTJets_FullLep','WZJets3L','DYJets']
lenghtSig = len(signal) * len(mass)
round_sig = 2
round_BG = 1


def MakeTheHistogram(CoMEnergy,text_file):
    Table_File = TFile("Yield"+CoMEnergy+""+".root")
    Table_Hist = Table_File.Get('FullResults')
    Table_Error = Table_File.Get('FullError')
    

    text_file.write('\\begin{tabular}{|c|c|c|c|c|c|c|c|c|}\n')
    text_file.write('\\hline\n')
    text_file.write('Channel & ZHtt125 &  Reducible & ZZ4L &  Data &TTZ&TTJet&WZ&DYJet\\\\ \n')
    text_file.write('\\hline\n')
    for chl in range(len(channel)):
        text_file.write("%s" %channel[chl])
        ###################################### Filling Signal ZH and WH ########
        for sig in range(len(signal)):
            for m in range(len(mass)):#    for m in range(110, 145, 5):

                normal = round(Table_Hist.GetBinContent(chl + 1, sig * len(mass) + m + 1),round_sig)
                normalEr = round(Table_Error.GetBinContent(chl + 1, sig * len(mass) + m + 1),round_sig)
                if (mass[m] == 125 and  signal[sig] == 'zhtt'): text_file.write('& %.1f  $\pm$ %.1f ' %(normal,normalEr))
                if (mass[m] == 125 and  signal[sig] == 'zhtt'): print '& %.1f  $\pm$ %.1f ' %(normal,normalEr) ,

        ###################################### Filling Reducible ########
        normal = round(Table_Hist.GetBinContent(chl + 1, lenghtSig  + 2),round_BG)
        normalEr = round(Table_Error.GetBinContent(chl + 1, lenghtSig  + 2),round_BG)
        text_file.write('&%.0f  $\pm$ %.0f ' %(normal,normalEr))
        print '&%.0f  $\pm$ %.0f ' %(normal,normalEr) ,
        ###################################### Filling ZZ and Data ########
        for bg in range (len(BackGround)):

            if (BackGround[bg] == "Data"):
                if (BLIND):
                    text_file.write('&%1d   ' %0)
                    print '&%01d   ' %0,
                else:
                    normal = round(Table_Hist.GetBinContent(chl + 1, lenghtSig + bg + 3),round_BG)
                    text_file.write('&%1d  ' %normal)
                    print '&%1d  ' %normal,
            else:
                normal = round(Table_Hist.GetBinContent(chl + 1, lenghtSig + bg + 3),round_BG)
                normalEr = round(Table_Error.GetBinContent(chl + 1, lenghtSig + bg + 3),round_BG)
                text_file.write('&%.0f  $\pm$ %.0f ' %(normal,normalEr))
                print '&%.0f  $\pm$ %.0f ' %(normal,normalEr),

            
        print ""
        text_file.write('\\\\\n')
    text_file.write('\\hline\n')
    text_file.write('\\end{tabular}')



if __name__ == "__main__":

    text_file = open("Full8TeVTableZH.tex", "w")
    MakeTheHistogram("_8TeV",text_file)
    text_file.close()

#    text_file = open("Full7TeVTableZH.tex", "w")
#    MakeTheHistogram("_7TeV",text_file)
#    text_file.close()