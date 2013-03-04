/* 
 * File:   zh_Tree.h
 * Author: abdollah
 *
 * Created on February 6, 2013, 1:56 PM
 */

#ifndef ZH_TREE_H
#define	ZH_TREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "myevent.h"
#include "myobject.h"
#include "Leptons_IdIso.h"
#include "zh_Auxiliary.h"
#include "Leptons_PreSelection.h"
#include "zh_Functions.h"





unsigned int Channel = 0;
unsigned int Run = 0;
unsigned int Lumi = 0;
unsigned int Event = 0;
float IMass = 0;
float ZMass = 0;
float HMass = 0;
float met, metPhi;
float l1M, l1Px, l1Py, l1Pz, l1E, l1Pt, l1Phi, l1Eta, l1Charge, l1_muId, l1_muIso, l1_eleId, l1_eleIso, l1_eleMVANonTrg, l1_eleNumHit = -10;
float l2M, l2Px, l2Py, l2Pz, l2E, l2Pt, l2Phi, l2Eta, l2Charge, l2_muId, l2_muIso, l2_eleId, l2_eleIso, l2_eleMVANonTrg, l2_eleNumHit = -10;
float l3M, l3Px, l3Py, l3Pz, l3E, l3Pt, l3Phi, l3Eta, l3Charge, l3_muId, l3_muIso, l3_eleId, l3_eleIso, l3_eleMVANonTrg, l3_eleNumHit, l3_tauIsoL, l3_tauIsoM, l3_tauIsoT, l3_tauRejMuL, l3_tauRejMuM, l3_tauRejMuT, l3_tauRejEleL, l3_tauRejEleM, l3_tauRejEleMVA = -10;
float l4M, l4Px, l4Py, l4Pz, l4E, l4Pt, l4Phi, l4Eta, l4Charge, l4_muId, l4_muIso, l4_eleId, l4_eleIso, l4_eleMVANonTrg, l4_eleNumHit, l4_tauIsoL, l4_tauIsoM, l4_tauIsoT, l4_tauRejMuL, l4_tauRejMuM, l4_tauRejMuT, l4_tauRejEleL, l4_tauRejEleM, l4_tauRejEleMVA = -10;
float covMet11;
float covMet12;
float covMet21;
float covMet22;
float eff_Correction, pu_Weight;
int num_PV, num_bjet;
int mu_Size, BareMuon_Size, electron_Size, BareElectron_Size, tau_Size, BareTau_Size;
int mu_partTight_Size, mu_partLoose_Size, ele_partTight_Size, ele_partLoose_Size;
float l3_CloseJetPt, l4_CloseJetPt;

void fillTree(TTree * Run_Tree, myevent *m, double cor_eff, float PU_Weight, int channel, myobject obj1, myobject obj2, myobject obj3, myobject obj4) {



    vector<myobject> Met = m->RecPFMet;
    Channel = channel;
    Run = m->runNumber;
    Lumi = m->lumiNumber;
    Event = m->eventNumber;
    IMass = InvarMass_4(obj1, obj2, obj3, obj4);
    ZMass = InvarMass_2(obj1, obj2);
    HMass = InvarMass_2(obj3, obj4);
    covMet11 = m->MET_sigMatrix_00;
    covMet12 = m->MET_sigMatrix_01;
    covMet21 = m->MET_sigMatrix_10;
    covMet22 = m->MET_sigMatrix_11;
    met = Met.front().pt;
    metPhi = Met.front().phi;
    eff_Correction = cor_eff;
    //lepton size
    mu_Size = myCleanLepton(m, "mu").size();
    BareMuon_Size = myCleanBareLepton(m, "mu").size();
    electron_Size = myCleanLepton(m, "ele").size();
    BareElectron_Size = myCleanBareLepton(m, "ele").size();
    tau_Size = myCleanLepton(m, "tau").size();
    BareTau_Size = myCleanBareLepton(m, "tau").size();

    mu_partLoose_Size = LeptonSubSet(m, "mu_loose_partly").size();
    mu_partTight_Size = LeptonSubSet(m, "mu_tight_partly").size();
    ele_partLoose_Size = LeptonSubSet(m, "ele_loose_partly").size();
    ele_partTight_Size = LeptonSubSet(m, "ele_tight_partly").size();


    l1M = obj1.mass;
    l1Px = obj1.px;
    l1Py = obj1.py;
    l1Pz = obj1.pz;
    l1E = obj1.E;
    l1Pt = obj1.pt;
    l1Phi = obj1.phi;
    l1Eta = obj1.eta;
    l1_muId = Id_Mu(obj1);
    l1_muIso = Iso_Mu_dBeta(obj1);
    l1_eleId = EleMVANonTrigId(obj1);
    l1_eleIso = Iso_Ele_dBeta(obj1);
    l1_eleMVANonTrg = obj1.Id_mvaNonTrg;
    l1_eleNumHit = obj1.numHitEleInner;
    l1Charge = obj1.charge;


    l2M = obj2.mass;
    l2Px = obj2.px;
    l2Py = obj2.py;
    l2E = obj2.E;
    l2Pt = obj2.pt;
    l2Phi = obj2.phi;
    l2Pz = obj2.pz;
    l2Eta = obj2.eta;
    l2_muId = Id_Mu(obj2);
    l2_muIso = Iso_Mu_dBeta(obj2);
    l2_eleId = EleMVANonTrigId(obj2);
    l2_eleIso = Iso_Ele_dBeta(obj2);
    l2_eleMVANonTrg = obj2.Id_mvaNonTrg;
    l2_eleNumHit = obj2.numHitEleInner;
    l2Charge = obj2.charge;

    l3M = obj3.mass;
    l3Px = obj3.px;
    l3Py = obj3.py;
    l3Pz = obj3.pz;
    l3E = obj3.E;
    l3Pt = obj3.pt;
    l3Phi = obj3.phi;
    l3Eta = obj3.eta;
    l3_muId = Id_Mu(obj3);
    l3_muIso = Iso_Mu_dBeta(obj3);
    l3_eleId = EleMVANonTrigId(obj3);
    l3_eleIso = Iso_Ele_dBeta(obj3);
    l3_eleMVANonTrg = obj3.Id_mvaNonTrg;
    l3_eleNumHit = obj3.numHitEleInner;
    l3_tauIsoL = obj3.byLooseCombinedIsolationDeltaBetaCorr;
    l3_tauIsoM = obj3.byMediumCombinedIsolationDeltaBetaCorr;
    l3_tauIsoT = obj3.byTightCombinedIsolationDeltaBetaCorr;
    l3_tauRejMuL = obj3.discriminationByMuonLoose;
    l3_tauRejMuM = obj3.discriminationByMuonMedium;
    l3_tauRejMuT = obj3.discriminationByMuonTight;
    l3_tauRejEleL = obj3.discriminationByElectronLoose;
    l3_tauRejEleM = obj3.discriminationByElectronMedium;
    l3_tauRejEleMVA = obj3.discriminationByElectronMVA;
    l3Charge = obj3.charge;
    l3_CloseJetPt = ((Channel % 10 != 1 || Channel % 10 != 5 || Channel > 99) ? Find_Closet_Jet(obj3, m) : 0);

    l4M = obj4.mass;
    l4Px = obj4.px;
    l4Py = obj4.py;
    l4E = obj4.E;
    l4Pt = obj4.pt;
    l4Phi = obj4.phi;
    l4Pz = obj4.pz;
    l4Eta = obj4.eta;
    l4_muId = Id_Mu(obj4);
    l4_muIso = Iso_Mu_dBeta(obj4);
    l4_eleId = EleMVANonTrigId(obj4);
    l4_eleIso = Iso_Ele_dBeta(obj4);
    l4_eleMVANonTrg = obj4.Id_mvaNonTrg;
    l4_eleNumHit = obj4.numHitEleInner;
    l4_tauIsoL = obj4.byLooseCombinedIsolationDeltaBetaCorr;
    l4_tauIsoM = obj4.byMediumCombinedIsolationDeltaBetaCorr;
    l4_tauIsoT = obj4.byTightCombinedIsolationDeltaBetaCorr;
    l4_tauRejMuL = obj4.discriminationByMuonLoose;
    l4_tauRejMuM = obj4.discriminationByMuonMedium;
    l4_tauRejMuT = obj4.discriminationByMuonTight;
    l4_tauRejEleL = obj4.discriminationByElectronLoose;
    l4_tauRejEleM = obj4.discriminationByElectronMedium;
    l4_tauRejEleMVA = obj4.discriminationByElectronMVA;
    l4Charge = obj4.charge;
    l4_CloseJetPt = ((Channel % 10 != 1 || Channel % 10 != 5 || Channel > 99) ? Find_Closet_Jet(obj4, m) : 0);

    vector<myobject> Vertex = m->Vertex;
    num_PV = Vertex.size();
    num_bjet = bjet_Multiplicity(m);
    pu_Weight = PU_Weight;


    //    if (chanal < 40)
    Run_Tree->Fill();
}



#endif	/* ZH_TREE_H */

