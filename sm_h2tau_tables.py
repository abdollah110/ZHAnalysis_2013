'''

Build TeX tables of various process yields for the SM H2Tau analysis.

Yields + uncertainties are taken from the data card.  Requires a single .txt
card with all channels.  You can build it in the correct format with:

    combine_cards_with_names.sh MY-LIMIT/cmb/125/*txt > sm_megacard.txt

where MY-LIMIT is the output directory of setup-htt.py

And then create the tables with

    python mssm_h2tau_tables.py

which will create

    em_yields_table.tex
    et_yields_table.tex
    mm_yields_table.tex
    mt_yields_table.tex

Author: Jan Steggemann, based on template by Evan K. Friis
'''

import math
from HiggsAnalysis.HiggsToTauTau.DataCard import DataCard
from HiggsAnalysis.HiggsToTauTau.sigfigs import sigfigs
from sobWeightedCombine import SOBPlotter
import ROOT

dc = DataCard('sm_megacard.txt')

def quad(*xs):
    return math.sqrt(sum(x*x for x in xs))

def render(x):
    ''' Render x (an uncertainties object) with correct sig figs '''
    if isinstance(x, int):
        return '%i' % x
    else:
        #return r'$%s \pm %s$' % (int(x.nominal_value), int(x.std_dev()))
        # Never round greater than unity.  Always include at least 1 sig digit.
        return r'$%s \pm %s$' % (sigfigs(x.nominal_value, x.std_dev(), 1, max_sig_fig=0))

def render_values(table):
    # Convert all objects to strings
    output = {}
    for field in table.keys():
        output[field] = render(table[field])
    return output

def add_up_backgrounds(table, uncs, bkgs, cats, tag=''):
    ''' Add up the total bkg contribution '''
    for category in cats:
        result = sum(table[category + x] for x in bkgs if category + x in table)
        table[category + 'Total' + tag] = result
        sumUnc = math.sqrt(sum(uncs[category + x]**2 for x in bkgs if category + x in uncs))
        uncs[category + 'Total' + tag] = sumUnc

def tfileGet(tfile, histName):
    hist = tfile.Get(histName)
    if not hist:
        msg = 'Object {histName} not found in {tfile}'.format(histName=histName, tfile=tfile)
        raise RuntimeError(msg)
    return hist


def getSOverSplusB(fileName):
    inFile = ROOT.TFile(fileName)

    signal = tfileGet(inFile, 'ggH')

    if fileName.find('emu') != -1:
        sumBG = tfileGet(inFile, 'ggH_hww')
    else:
        sumBG = tfileGet(inFile, 'Ztt')

    return SOBPlotter.getSoB(signal, sumBG)

def getStdDeviationDC(names):
    fileName, dirName = names

    inFile = ROOT.TFile(fileName)
    tdir = inFile.Get(dirName)

    signal = tfileGet(tdir, 'ggH125')
    VH = tfileGet(tdir, 'VH125')
    qqH = tfileGet(tdir, 'qqH125')

    signal.Add(VH)
    signal.Add(qqH)

    results = signal.Fit('gaus', 'SQ', '', 90., 150.)
    mean  = results.GetParams()[1]
    width = results.GetParams()[2]

    # print 'DC: Integral', signal.Integral()

    return signal.GetRMS(), width

def getStdDeviation(fileName):
    inFile = ROOT.TFile(fileName)

    signal = tfileGet(inFile, 'ggH')
    if fileName.find('emu') != -1:
        sumBG = tfileGet(inFile, 'ggH_hww')
    else:
        sumBG = tfileGet(inFile, 'Ztt')
    signal.Add(sumBG, -1.)

    results = signal.Fit('gaus', 'SQ', '', 90., 150.)
    mean  = results.GetParams()[1]
    width = results.GetParams()[2]

    # print 'PF: Integral', signal.Integral()

    return signal.GetRMS(), width

SIGNAL_STRENGTH = 1.0
print 'INFO: Taking combined signal strength of', SIGNAL_STRENGTH

tables = {}
uncs = {}
sOverSplusBs = {}
sigmas = {}
widths = {}

###### MT Channel

tableProcs = ['ggH', 'VH', 'qqH', 'Total', 'TotalSig', 'obs']

channels = ['mt', 'et', 'tt', 'em', 'ee', 'mm']

channelToPostfit = {
    'mt':'muTau',
    'et':'eleTau',
    'tt':'tauTau',
    'em':'emu',
    'ee':'ee', 
    'mm':'mm',
}

channelToTex = {
    'mt':'$\mu\Pgth$',
    'et':'$\Pe\Pgth$',
    'tt':'$\Pgth\Pgth$',
    'em':'$\Pe\mu$',
    'ee':'$\Pe\Pe$', 
    'mm':'$\mu\mu$',
}

# FIXME: Can read this in from the limits.config file
catDict = {}
for com in ['7', '8']:
    for ch in ['mt', 'et']:
        catDict['htt_{ch}_0_{com}TeV'.format(ch=ch, com=com)] = '0jet_low'
        catDict['htt_{ch}_1_{com}TeV'.format(ch=ch, com=com)] = '0jet_medium'
        catDict['htt_{ch}_2_{com}TeV'.format(ch=ch, com=com)] = '0jet_high'
        catDict['htt_{ch}_3_{com}TeV'.format(ch=ch, com=com)] = '1jet_medium'
        catDict['htt_{ch}_4_{com}TeV'.format(ch=ch, com=com)] = '1jet_high_lowhiggs'
        catDict['htt_{ch}_5_{com}TeV'.format(ch=ch, com=com)] = '1jet_high_mediumhiggs'
        catDict['htt_{ch}_6_{com}TeV'.format(ch=ch, com=com)] = 'vbf_loose'
        if com == '7':
            catDict['htt_{ch}_6_{com}TeV'.format(ch=ch, com=com)] = 'vbf'
        catDict['htt_{ch}_7_{com}TeV'.format(ch=ch, com=com)] = 'vbf_tight'
    for ch in ['em', 'ee', 'mm']:
        catDict['htt_{ch}_0_{com}TeV'.format(ch=ch, com=com)] = '0jet_low'
        catDict['htt_{ch}_1_{com}TeV'.format(ch=ch, com=com)] = '0jet_high'
        catDict['htt_{ch}_2_{com}TeV'.format(ch=ch, com=com)] = '1jet_low'
        catDict['htt_{ch}_3_{com}TeV'.format(ch=ch, com=com)] = '1jet_high'
        catDict['htt_{ch}_4_{com}TeV'.format(ch=ch, com=com)] = 'vbf'
    catDict['htt_em_4_{com}TeV'.format(ch=ch, com=com)] = 'vbf_loose'
    catDict['htt_em_5_{com}TeV'.format(ch=ch, com=com)] = 'vbf_tight'
    for ch in ['tt']:
        catDict['htt_{ch}_0_{com}TeV'.format(ch=ch, com=com)] = '1jet_high_mediumhiggs'
        catDict['htt_{ch}_1_{com}TeV'.format(ch=ch, com=com)] = '1jet_high_highhiggs'
        catDict['htt_{ch}_2_{com}TeV'.format(ch=ch, com=com)] = 'vbf'

POSTFITDIR = 'postfit/'
def catToFileDC(dc, cat, channel):
    name = dc.card.shapeMap[cat]['*'][0]
    dirName = channelToPostfit[channel] + '_' + catDict[cat]
    return name, dirName

def catToFile(cat, channel):
    com = '8' if '8TeV' in cat else '7'
    scale = 'LOG' if channel in ['ee', 'mm'] else 'LIN'
    name = '{dir}{chan}_{cat}_postfit_{com}TeV_{lin_log}.root'.format(dir=POSTFITDIR, chan=channelToPostfit[channel], cat=catDict[cat], com=com, lin_log=scale)
    # print name, channel, channelToPostfit[channel], cat, catDict[cat]
    return name

catNames = {}
for ch in channels:
    catNames[ch] = {}
    catNames[ch]['vbf_loose'] = 'loose VBF tag'
    catNames[ch]['vbf_tight'] = 'tight VBF tag'
    catNames[ch]['vbf'] = 'VBF tag'
    if ch in ['et', 'mt']:
        catNames[ch]['0jet_medium'] = '0-jet low $\pt(\Pgth)$'
        catNames[ch]['0jet_high'] = '0-jet high $\pt(\Pgth)$'
        catNames[ch]['1jet_medium'] = '1-jet low $\pt(\Pgth)$'
        catNames[ch]['1jet_high_lowhiggs'] = '1-jet high $\pt(\Pgth)$'
        catNames[ch]['1jet_high_mediumhiggs'] = '1-jet high $\pt(\Pgth)$ boost'
    if ch in ['ee']:
        catNames[ch]['0jet_low'] = '0-jet low $\pt(\Pe)$'
        catNames[ch]['0jet_high'] = '0-jet high $\pt(\Pe)$'
        catNames[ch]['1jet_low'] = '1-jet low $\pt(\Pe)$'
        catNames[ch]['1jet_high'] = '1-jet high $\pt(\Pe)$'
        catNames[ch]['vbf'] = '2-jet'
    if ch in ['mm']:
        catNames[ch]['0jet_low'] = '0-jet low $\pt(\mu)$'
        catNames[ch]['0jet_high'] = '0-jet high $\pt(\mu)$'
        catNames[ch]['1jet_low'] = '1-jet low $\pt(\mu)$'
        catNames[ch]['1jet_high'] = '1-jet high $\pt(\mu)$'
        catNames[ch]['vbf'] = '2-jet'
    if ch in ['em']:
        catNames[ch]['0jet_low'] = '0-jet low $\pt(\mu)$'
        catNames[ch]['0jet_high'] = '0-jet high $\pt(\mu)$'
        catNames[ch]['1jet_low'] = '1-jet low $\pt(\mu)$'
        catNames[ch]['1jet_high'] = '1-jet high $\pt(\mu)$'
    if ch in ['tt']:
        catNames[ch]['1jet_high_mediumhiggs'] = '1-jet boost'
        catNames[ch]['1jet_high_highhiggs'] = '1-jet large boost'



# bgsamples = ['ZTT', 'ZL', 'QCD', 'Wjets', 'ZJ', 'TT', 'VV']

backgrounds = dc.card.list_of_backgrounds()
signals = dc.card.list_of_signals()
procs = dc.card.list_of_procs()
allbins = dc.card.bins 
bins = {}


POSTFIT = True

for channel in channels:

    bins[channel] = [bin for bin in allbins if '_'+channel in bin]
    chBgs = []

    tables[channel] = {}
    uncs[channel] = {}
    sOverSplusBs[channel] = {}
    sigmas[channel] = {}
    widths[channel] = {}

    for cat in bins[channel]:
        for proc in procs:
            try:
                tables[channel][cat+proc] = dc.get_rate(cat, proc).nominal_value
                uncs[channel][cat+proc] = dc.get_rate(cat, proc).std_dev()
            except KeyError:
                pass
            else:
                if proc in backgrounds:
                    chBgs.append(proc)
        if not POSTFIT and channel not in ['ee', 'mm']:
            sOverSplusBs[channel][cat] = getSOverSplusB(catToFile(cat, channel))
            sigma, width = getStdDeviation(catToFile(cat, channel))
            # sigma, width = getStdDeviationDC(catToFileDC(dc, cat, channel))
            sigmas[channel][cat] = sigma
            widths[channel][cat] = width
        tables[channel][cat+'obs'] = dc.get_obs(cat)

    chBgs = set(chBgs)

    # RESCALE LOOP
    if POSTFIT:
        for cat in bins[channel]:
            if channel not in ['ee', 'mm']:
                sOverSplusBs[channel][cat] = getSOverSplusB(catToFile(cat, channel))
                sigma, width = getStdDeviation(catToFile(cat, channel))
                # sigma, width = getStdDeviationDC(catToFileDC(dc, cat, channel))
                sigmas[channel][cat] = sigma
                widths[channel][cat] = width
            scaleName = cat.replace('htt', 'scales')
            scales = __import__(scaleName).scales
            for proc in procs:
                if cat+proc in tables[channel]:
                    if proc in scales:
                        tables[channel][cat+proc] *= scales[proc][0]
                        uncs[channel][cat+proc] = scales[proc][1] * tables[channel][cat+proc]
                        if proc in signals:
                            tables[channel][cat+proc] *= SIGNAL_STRENGTH
                            uncs[channel][cat+proc] *= SIGNAL_STRENGTH
                    else:
                        print 'WARNING', proc, 'not in', scales, 'for channel', channel
                # else:
                    # print 'WARNING', proc, 'not in mt tables'

    add_up_backgrounds(tables[channel], uncs[channel], chBgs, bins[channel])
    add_up_backgrounds(tables[channel], uncs[channel], signals, bins[channel], tag='Sig')

    # dc.print_systematics(mt_0jet_bins, 'QCD'),


header = r''' Category & \multicolumn{{3}}{{r}} SM Higgs ($m_\mathrm{{H}} = 125$\unit{{GeV}}) & \\
{channel_period} & ggH & VH & qqH & Sum Signal & Data & Sum BG & $S/(S+B)_{{68\%}}$ \\
\hline
'''
footer = r'''\hline
'''

# et_mt_line = r'''
# {category:30} & ${ggH:5.1f} \pm {ggH_err:5.1f}$ & ${VH:5.1f} \pm {VH_err:5.1f}$ & ${qqH:5.1f} \pm {qqH_err:5.1f}$ & ${TotalSig:8.0f} \pm {TotalSig_err:7.0f}$& ${Total:8.0f} \pm {Total_err:7.0f}$ & ${obs:7}$ & ${sOverSB:5.2f}$ \\
# '''

et_mt_line = r'''
{category:30} & ${ggH:5.1f}$ & ${qqH:5.1f}$ & ${VH:5.1f}$ & ${TotalSig:8.1f} \pm {TotalSig_err:7.1f} PHANTOM1$  & ${Total:8.0f} \pm {Total_err:7.0f} PHANTOM2 $ & ${obs:7}$ & ${sOverSB:5.2f}$ & {sigma:5.1f}  \\
'''
et_mt_line = r'''
{category:30} & ${ggH:5.1f}$ & ${qqH:5.1f}$ & ${VH:5.1f}$ & ${TotalSig:8.1f} \pm {TotalSig_err:7.1f} PHANTOM1$  & ${Total:8.0f} \pm {Total_err:7.0f} PHANTOM2 $ & ${obs:7}$ & ${sOverSB}$ & {sigma:5.1f}  \\
'''

ee_mm_line = r'''
{category:30} & ${ggH:5.1f}$ & ${qqH:5.1f}$ & ${VH:5.1f}$ & ${TotalSig:8.1f} \pm {TotalSig_err:7.1f} PHANTOM1$  & ${Total:8.0f} \pm {Total_err:7.0f} PHANTOM2 $ & ${obs:7}$ & n/a & n/a  \\
'''

ee_mm_line = r'''
{category:30} & ${ggH:5.1f}$ & ${qqH:5.1f}$ & ${VH:5.1f}$  & ${TotalSig:8.1f} \pm {TotalSig_err:7.1f} PHANTOM1$  & ${Total:8.0f} \pm {Total_err:7.0f} PHANTOM2 $ & ${obs:7}$  \\
'''

channel_line = r'''
{channel} & & & & & & & & \\
'''

channel_line_ee_mm = r'''
{channel} & & & & & &  \\
'''

# print sOverSplusBs
# print catDict
# print sigmas
# print widths

with open('cmb_yields_table.tex', 'w') as file:
    file.write(header.format(channel_period=channel))
    for channel in channels:
        if channel in ['ee', 'mm']:
            file.write(channel_line_ee_mm.format(channel=channelToTex[channel]))
        else:
            file.write(channel_line.format(channel=channelToTex[channel]))
        line = et_mt_line
        if channel in ['ee', 'mm']:
            line = ee_mm_line

        for cat in bins[channel]:
            yields = {}
            for p in tableProcs:
                # print tables['mt'][cat+p]
                if p == 'obs':
                    yields[p] = tables[channel][cat+p]
                else:    
                    yields[p] = tables[channel][cat+p]
                    yields[p+'_err'] = uncs[channel][cat+p]

                    if p == 'TotalSig':
                        nPhantoms1 = 4 - len(str(round(yields[p+'_err'], 1)))
                    elif p == 'Total':
                        nPhantoms2 = 4 - len(str(int(round(yields[p+'_err']))))

            if '7TeV' in cat:
                # yields['category'] = channelToTex[channel] + ' ' + catNames[channel][catDict[cat]] + ' 7\,TeV'
                if 'VBF' in catNames[channel][catDict[cat]]:
                    yields['category'] = catNames[channel][catDict[cat]] + ' 7\,\TeV'
                else:
                    yields['category'] = '\multirow{{2}}{{*}}{{{catName}}} \ 7\,\TeV'.format(catName=catNames[channel][catDict[cat]])
            else:
                # yields['category'] = channelToTex[channel] + ' ' + catNames[channel][catDict[cat]] + ' 8\,TeV'
                if 'VBF' in catNames[channel][catDict[cat]] or channel == 'tt':
                    yields['category'] = catNames[channel][catDict[cat]] + ' 8\,\TeV'
                else:
                    yields['category'] = '\phantom{{{catName}}} \ 8\,\TeV'.format(catName=catNames[channel][catDict[cat]])
            ssb = 0.
            if channel not in ['ee', 'mm']:
                yields['sOverSB'] = sigfigs(sOverSplusBs[channel][cat], sOverSplusBs[channel][cat], min_sig_fig=-3)[0]
                yields['sigma'] = sigmas[channel][cat]
                yields['width'] = widths[channel][cat]
                ssb = sOverSplusBs[channel][cat]
            # yields['obs'] = '0'

            file.write(line.format(**yields).replace('PHANTOM1', '\phantom{{{}}}'.format(nPhantoms1*'0')).replace('PHANTOM2', '\phantom{{{}}}'.format(nPhantoms2*'0')).replace('0.0$', '-$').replace('0.00$', str(int(round(1000*ssb)))+'$\qquad\\textperthousand'))
        file.write(footer)
    file.write(footer)


