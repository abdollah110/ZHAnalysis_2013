/* 
 * File:   zh_Tree.h
 * Author: abdollah
 *
 * Created on February 6, 2013, 1:56 PM
 */

#ifndef TR_TREE_H
#define	TR_TREE_H

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>

//needed to make the executable
#include "makeHisto.h"
//#include "../interface/zh_Auxiliary.h"
#include "myHelper.h"



int Channel = 0;
int Run = 0;
int Lumi = 0;
int Event = 0;
float IMass = 0;
float ZMass = 0;
float HMass = 0;
float met, metPhi, pfmet, pfmetPhi;
float l1M, l1Px, l1Py, l1Pz, l1E, l1Pt, l1Phi, l1Eta, l1Charge, l1_muIso, l1_eleIso, l1_eleMVANonTrg, l1_eleNumHit = -10;
float l2M, l2Px, l2Py, l2Pz, l2E, l2Pt, l2Phi, l2Eta, l2Charge, l2_muIso, l2_eleIso, l2_eleMVANonTrg, l2_eleNumHit = -10;
float l3M, l3Px, l3Py, l3Pz, l3E, l3Pt, l3Phi, l3Eta, l3Charge, l3_muIso, l3_eleIso, l3_eleMVANonTrg, l3_eleNumHit, l3_tauIsoMVA2raw = -10;
float l4M, l4Px, l4Py, l4Pz, l4E, l4Pt, l4Phi, l4Eta, l4Charge, l4_muIso, l4_eleIso, l4_eleMVANonTrg, l4_eleNumHit, l4_tauIsoMVA2raw = -10;
bool l1_muId, l1_eleId, l2_muId, l2_eleId, l3_muId_Loose, l3_muId_Tight, l3_eleId_Loose, l3_eleId_Tight, l4_muId_Loose, l4_eleId_Loose, l4_muId_Tight, l4_eleId_Tight;
bool l3_tauIsoL, l3_tauIsoM, l3_tauIsoT, l3_tauRejMuL, l3_tauRejMuM, l3_tauRejMuT, l3_tauRejEleL, l3_tauRejEleM, l3_tauRejEleMVA;
bool l3_tauIso3HitL, l3_tauIso3HitM, l3_tauIso3HitT, l3_tauRejMu2L, l3_tauRejMu2M, l3_tauRejMu2T, l3_tauRejEleMVA3L, l3_tauRejEleMVA3M, l3_tauRejEleMVA3T;
bool l3_tauIsoVL, l3_tauIsoMVA2L, l3_tauIsoMVA2M, l3_tauIsoMVA2T;
bool l4_tauIsoL, l4_tauIsoM, l4_tauIsoT, l4_tauRejMuL, l4_tauRejMuM, l4_tauRejMuT, l4_tauRejEleL, l4_tauRejEleM, l4_tauRejEleMVA;
bool l4_tauIso3HitL, l4_tauIso3HitM, l4_tauIso3HitT, l4_tauRejMu2L, l4_tauRejMu2M, l4_tauRejMu2T, l4_tauRejEleMVA3L, l4_tauRejEleMVA3M, l4_tauRejEleMVA3T;
bool l4_tauIsoVL, l4_tauIsoMVA2L, l4_tauIsoMVA2M, l4_tauIsoMVA2T;
float l3_RefJetPt, l3_RefJetEta, l3_RefJetPhi = -10;
float l4_RefJetPt, l4_RefJetEta, l4_RefJetPhi = -10;
float covMet11, covMet12, covMet21, covMet22;
float pfcovMet11, pfcovMet12, pfcovMet21, pfcovMet22;
float eff_Correction, pu_Weight;
int num_PV, num_bjet, num_goodjet;
int mu_Size, BareMuon_Size, electron_Size, BareElectron_Size, tau_Size, BareTau_Size;
int mu_partTight_Size, ele_partTight_Size;
float l3_CloseJetPt, l4_CloseJetPt;
float l3_CloseJetEta, l4_CloseJetEta;
float l3_CloseJetPhi, l4_CloseJetPhi;
double SVMass, SVMassUnc;
double SVMassUp, SVMassUncUp;
double SVMassDown, SVMassUncDown;

//New BG_Tree
int Channel_;
int subChannel_;
float HMass_;
float SVMass_;
float l3Pt_;
float l3Eta_;
float l3_CloseJetPt_;
float l3_CloseJetEta_;
float l4Pt_;
float l4Eta_;
float l4_CloseJetPt_;
float l4_CloseJetEta_;

void fillTreeN(TTree* BG_Tree, int Channel, int subChannel, float HMass, double SVMass, float l3Pt, float l3Eta, float l3_CloseJetPt, float l3_CloseJetEta, float l4Pt, float l4Eta, float l4_CloseJetPt, float l4_CloseJetEta) {

    Channel_ = Channel- 90;
    subChannel_ = subChannel;
    HMass_ = HMass;
    SVMass_ = SVMass;
    l3Pt_ = l3Pt;
    l3Eta_ = l3Eta;
    l3_CloseJetPt_ = l3_CloseJetPt;
    l3_CloseJetEta_ = l3_CloseJetEta;
    l4Pt_ = l4Pt;
    l4Eta_ = l4Eta;
    l4_CloseJetPt_ = l4_CloseJetPt;
    l4_CloseJetEta_ = l4_CloseJetEta;

    BG_Tree->Fill();
}


#endif	/* TR_TREE_H */

