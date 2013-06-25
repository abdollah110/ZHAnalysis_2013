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
#include "../interface/makeHisto.h"
#include "../interface/zh_Auxiliary.h"
#include "../interface/myHelper.h"

int main(int argc, char** argv) {
    string out = *(argv + 1);
    string input = *(argv + 2);

    //PRINTING THE OUTPUT name
    cout << "\n\n\n OUTPUT NAME IS:    " << out << endl;
    TFile *fout = TFile::Open(out.c_str(), "RECREATE");

    using namespace std;

    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    //
    TFile *f_Double = new TFile(input.c_str());
    TTree *Run_Tree = (TTree*) f_Double->Get("RLE_tree");
    Run_Tree->AddFriend("Mass_tree");

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(1);
    int pt_Bin = 400;


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

    Run_Tree->SetBranchAddress("Channel", &Channel);
    Run_Tree->SetBranchAddress("Run", &Run);
    Run_Tree->SetBranchAddress("Lumi", &Lumi);
    Run_Tree->SetBranchAddress("Event", &Event);
    Run_Tree->SetBranchAddress("IMass", &IMass);
    Run_Tree->SetBranchAddress("ZMass", &ZMass);
    Run_Tree->SetBranchAddress("HMass", &HMass);
    Run_Tree->SetBranchAddress("met", &met);
    Run_Tree->SetBranchAddress("pfmet", &pfmet);
    Run_Tree->SetBranchAddress("metPhi", &metPhi);
    Run_Tree->SetBranchAddress("pfmetPhi", &pfmetPhi);
    Run_Tree->SetBranchAddress("covMet11", &covMet11);
    Run_Tree->SetBranchAddress("covMet12", &covMet12);
    Run_Tree->SetBranchAddress("covMet21", &covMet21);
    Run_Tree->SetBranchAddress("covMet22", &covMet22);
    Run_Tree->SetBranchAddress("pfcovMet11", &pfcovMet11);
    Run_Tree->SetBranchAddress("pfcovMet12", &pfcovMet12);
    Run_Tree->SetBranchAddress("pfcovMet21", &pfcovMet21);
    Run_Tree->SetBranchAddress("pfcovMet22", &pfcovMet22);
    Run_Tree->SetBranchAddress("num_PV", &num_PV);
    Run_Tree->SetBranchAddress("num_bjet", &num_bjet);
    Run_Tree->SetBranchAddress("num_goodjet", &num_goodjet);
    Run_Tree->SetBranchAddress("eff_Correction", &eff_Correction);
    Run_Tree->SetBranchAddress("pu_Weight", &pu_Weight);

    Run_Tree->SetBranchAddress("mu_Size", &mu_Size);
    Run_Tree->SetBranchAddress("BareMuon_Size", &BareMuon_Size);
    Run_Tree->SetBranchAddress("electron_Size", &electron_Size);
    Run_Tree->SetBranchAddress("BareElectron_Size", &BareElectron_Size);
    Run_Tree->SetBranchAddress("tau_Size", &tau_Size);
    Run_Tree->SetBranchAddress("BareTau_Size", &BareTau_Size);
    Run_Tree->SetBranchAddress("mu_partTight_Size", &mu_partTight_Size);
    Run_Tree->SetBranchAddress("ele_partTight_Size", &ele_partTight_Size);

    Run_Tree->SetBranchAddress("l1M", &l1M);
    Run_Tree->SetBranchAddress("l1E", &l1E);
    Run_Tree->SetBranchAddress("l1Px", &l1Px);
    Run_Tree->SetBranchAddress("l1Py", &l1Py);
    Run_Tree->SetBranchAddress("l1Pz", &l1Pz);
    Run_Tree->SetBranchAddress("l1Pt", &l1Pt);
    Run_Tree->SetBranchAddress("l1Eta", &l1Eta);
    Run_Tree->SetBranchAddress("l1Phi", &l1Phi);
    Run_Tree->SetBranchAddress("l1Charge", &l1Charge);
    Run_Tree->SetBranchAddress("l1_muId", &l1_muId);
    Run_Tree->SetBranchAddress("l1_muIso", &l1_muIso);
    Run_Tree->SetBranchAddress("l1_eleId", &l1_eleId);
    Run_Tree->SetBranchAddress("l1_eleIso", &l1_eleIso);
    Run_Tree->SetBranchAddress("l1_eleMVANonTrg", &l1_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l1_eleNumHit", &l1_eleNumHit);

    Run_Tree->SetBranchAddress("l2M", &l2M);
    Run_Tree->SetBranchAddress("l2E", &l2E);
    Run_Tree->SetBranchAddress("l2Px", &l2Px);
    Run_Tree->SetBranchAddress("l2Py", &l2Py);
    Run_Tree->SetBranchAddress("l2Pz", &l2Pz);
    Run_Tree->SetBranchAddress("l2Pt", &l2Pt);
    Run_Tree->SetBranchAddress("l2Eta", &l2Eta);
    Run_Tree->SetBranchAddress("l2Phi", &l2Phi);
    Run_Tree->SetBranchAddress("l2Charge", &l2Charge);
    Run_Tree->SetBranchAddress("l2_muId", &l2_muId);
    Run_Tree->SetBranchAddress("l2_muIso", &l2_muIso);
    Run_Tree->SetBranchAddress("l2_eleId", &l2_eleId);
    Run_Tree->SetBranchAddress("l2_eleIso", &l2_eleIso);
    Run_Tree->SetBranchAddress("l2_eleMVANonTrg", &l2_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l2_eleNumHit", &l2_eleNumHit);

    Run_Tree->SetBranchAddress("l3M", &l3M);
    Run_Tree->SetBranchAddress("l3E", &l3E);
    Run_Tree->SetBranchAddress("l3Px", &l3Px);
    Run_Tree->SetBranchAddress("l3Py", &l3Py);
    Run_Tree->SetBranchAddress("l3Pz", &l3Pz);
    Run_Tree->SetBranchAddress("l3Pt", &l3Pt);
    Run_Tree->SetBranchAddress("l3Eta", &l3Eta);
    Run_Tree->SetBranchAddress("l3Phi", &l3Phi);
    Run_Tree->SetBranchAddress("l3Charge", &l3Charge);
    Run_Tree->SetBranchAddress("l3_CloseJetPt", &l3_CloseJetPt);
    Run_Tree->SetBranchAddress("l3_CloseJetEta", &l3_CloseJetEta);
    Run_Tree->SetBranchAddress("l3_CloseJetPhi", &l3_CloseJetPhi);
    Run_Tree->SetBranchAddress("l3_muId_Loose", &l3_muId_Loose);
    Run_Tree->SetBranchAddress("l3_muId_Tight", &l3_muId_Tight);
    Run_Tree->SetBranchAddress("l3_muIso", &l3_muIso);
    Run_Tree->SetBranchAddress("l3_eleId_Loose", &l3_eleId_Loose);
    Run_Tree->SetBranchAddress("l3_eleId_Tight", &l3_eleId_Tight);
    Run_Tree->SetBranchAddress("l3_eleIso", &l3_eleIso);
    Run_Tree->SetBranchAddress("l3_eleMVANonTrg", &l3_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l3_eleNumHit", &l3_eleNumHit);
    Run_Tree->SetBranchAddress("l3_tauIsoVL", &l3_tauIsoVL);
    Run_Tree->SetBranchAddress("l3_tauIso3HitL", &l3_tauIso3HitL);
    Run_Tree->SetBranchAddress("l3_tauIso3HitM", &l3_tauIso3HitM);
    Run_Tree->SetBranchAddress("l3_tauIso3HitT", &l3_tauIso3HitT);
    Run_Tree->SetBranchAddress("l3_tauIsoL", &l3_tauIsoL);
    Run_Tree->SetBranchAddress("l3_tauIsoM", &l3_tauIsoM);
    Run_Tree->SetBranchAddress("l3_tauIsoT", &l3_tauIsoT);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2L", &l3_tauIsoMVA2L);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2M", &l3_tauIsoMVA2M);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2T", &l3_tauIsoMVA2T);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2raw", &l3_tauIsoMVA2raw);
    Run_Tree->SetBranchAddress("l3_tauRejMuL", &l3_tauRejMuL);
    Run_Tree->SetBranchAddress("l3_tauRejMu2L", &l3_tauRejMu2L);
    Run_Tree->SetBranchAddress("l3_tauRejMuM", &l3_tauRejMuM);
    Run_Tree->SetBranchAddress("l3_tauRejMu2M", &l3_tauRejMu2M);
    Run_Tree->SetBranchAddress("l3_tauRejMuT", &l3_tauRejMuT);
    Run_Tree->SetBranchAddress("l3_tauRejMu2T", &l3_tauRejMu2T);
    Run_Tree->SetBranchAddress("l3_tauRejEleL", &l3_tauRejEleL);
    Run_Tree->SetBranchAddress("l3_tauRejEleM", &l3_tauRejEleM);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA", &l3_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3L", &l3_tauRejEleMVA3L);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3M", &l3_tauRejEleMVA3M);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3T", &l3_tauRejEleMVA3T);
    Run_Tree->SetBranchAddress("l3_RefJetPt", &l3_RefJetPt);
    Run_Tree->SetBranchAddress("l3_RefJetEta", &l3_RefJetEta);
    Run_Tree->SetBranchAddress("l3_RefJetPhi", &l3_RefJetPhi);


    Run_Tree->SetBranchAddress("l4M", &l4M);
    Run_Tree->SetBranchAddress("l4E", &l4E);
    Run_Tree->SetBranchAddress("l4Px", &l4Px);
    Run_Tree->SetBranchAddress("l4Py", &l4Py);
    Run_Tree->SetBranchAddress("l4Pz", &l4Pz);
    Run_Tree->SetBranchAddress("l4Pt", &l4Pt);
    Run_Tree->SetBranchAddress("l4Eta", &l4Eta);
    Run_Tree->SetBranchAddress("l4Phi", &l4Phi);
    Run_Tree->SetBranchAddress("l4Charge", &l4Charge);
    Run_Tree->SetBranchAddress("l4_muId_Loose", &l4_muId_Loose);
    Run_Tree->SetBranchAddress("l4_muId_Tight", &l4_muId_Tight);
    Run_Tree->SetBranchAddress("l4_muIso", &l4_muIso);
    Run_Tree->SetBranchAddress("l4_eleId_Loose", &l4_eleId_Loose);
    Run_Tree->SetBranchAddress("l4_eleId_Tight", &l4_eleId_Tight);
    Run_Tree->SetBranchAddress("l4_eleIso", &l4_eleIso);
    Run_Tree->SetBranchAddress("l4_eleMVANonTrg", &l4_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l4_eleNumHit", &l4_eleNumHit);
    Run_Tree->SetBranchAddress("l4_CloseJetPt", &l4_CloseJetPt);
    Run_Tree->SetBranchAddress("l4_CloseJetEta", &l4_CloseJetEta);
    Run_Tree->SetBranchAddress("l4_CloseJetPhi", &l4_CloseJetPhi);
    Run_Tree->SetBranchAddress("l4_tauIsoVL", &l4_tauIsoVL);
    Run_Tree->SetBranchAddress("l4_tauIso3HitL", &l4_tauIso3HitL);
    Run_Tree->SetBranchAddress("l4_tauIso3HitM", &l4_tauIso3HitM);
    Run_Tree->SetBranchAddress("l4_tauIso3HitT", &l4_tauIso3HitT);
    Run_Tree->SetBranchAddress("l4_tauIsoL", &l4_tauIsoL);
    Run_Tree->SetBranchAddress("l4_tauIsoM", &l4_tauIsoM);
    Run_Tree->SetBranchAddress("l4_tauIsoT", &l4_tauIsoT);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2L", &l4_tauIsoMVA2L);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2M", &l4_tauIsoMVA2M);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2T", &l4_tauIsoMVA2T);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2raw", &l4_tauIsoMVA2raw);
    Run_Tree->SetBranchAddress("l4_tauRejMuL", &l4_tauRejMuL);
    Run_Tree->SetBranchAddress("l4_tauRejMu2L", &l4_tauRejMu2L);
    Run_Tree->SetBranchAddress("l4_tauRejMuM", &l4_tauRejMuM);
    Run_Tree->SetBranchAddress("l4_tauRejMu2M", &l4_tauRejMu2M);
    Run_Tree->SetBranchAddress("l4_tauRejMuT", &l4_tauRejMuT);
    Run_Tree->SetBranchAddress("l4_tauRejMu2T", &l4_tauRejMu2T);
    Run_Tree->SetBranchAddress("l4_tauRejEleL", &l4_tauRejEleL);
    Run_Tree->SetBranchAddress("l4_tauRejEleM", &l4_tauRejEleM);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA", &l4_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3L", &l4_tauRejEleMVA3L);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3M", &l4_tauRejEleMVA3M);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3T", &l4_tauRejEleMVA3T);
    Run_Tree->SetBranchAddress("l4_RefJetPt", &l4_RefJetPt);
    Run_Tree->SetBranchAddress("l4_RefJetEta", &l4_RefJetEta);
    Run_Tree->SetBranchAddress("l4_RefJetPhi", &l4_RefJetPhi);
    //SVMass from another Tree
    Run_Tree->SetBranchAddress("SVMass", &SVMass);
    Run_Tree->SetBranchAddress("SVMassUnc", &SVMassUnc);




    //Just each categori should be filled once
    int Event_Double[6][9];
    memset(Event_Double, 0, sizeof (Event_Double[0][0]) * 6 * 9);
    int Ev_double_tau = 0; //need to be checked gloat instead of integer!!!!!!!!
    int Ev_double_ele = 0;
    int Ev_double_mu = 0;

    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        //###############################################################################################
        //values
        //###############################################################################################
        float dMZ_Diff = 10;
        float looseLep = 0.7;
        float looseEle = 0.7;
        float looseMu = 0.7;
        float tightEle = 0.10;
        float tightMu = 0.15;
        float value_Eta = 1.4;
        float VisibleMass = InvarMass_F(l3E, l4E, l3Px, l4Px, l3Py, l4Py, l3Pz, l4Pz);
        float TMass_l_Met = TMass_F(l3Pt, l4Px, l3Py, met, metPhi);

        bool charge_Type = ((l3Charge * l4Charge > 0) ? true : false); //This for OS
        bool SS = l3Charge * l4Charge > 0;
        bool OS = l3Charge * l4Charge < 0;
        float CutOnTauPt = 10;
        bool tau3_IsoB = l3_tauIsoL;
        bool tau4_IsoB = l4_tauIsoL;
        //        bool LTcut = l3_CloseJetPt + l4_CloseJetPt > 0;
        bool LTcut = l3Pt + l4Pt > 0;
        //        bool tau3_IsoB = l3_tauIsoMVA2raw > .0;
        //        bool tau4_IsoB = l4_tauIsoMVA2raw > .0;

        //####################################################
        // MMTT FakeRateation
        //####################################################

        if ((Channel == 91) && LTcut && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL) {

            if (charge_Type && tau3_IsoB && tau4_IsoB && (Event != Event_Double[0][1])) {
                plotFill("TauPtJetPt_pp", l3Pt / l3_CloseJetPt, 100, 0, 2);
                plotFill("TauPtJetPt_pp", l4Pt / l4_CloseJetPt, 100, 0, 2);
                plotFill("TauPtRefJetPt_pp", l3Pt / l3_RefJetPt, 100, 0, 2);
                plotFill("TauPtRefJetPt_pp", l4Pt / l4_RefJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_pp", l3_RefJetPt / l3_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_pp", l4_RefJetPt / l4_CloseJetPt, 100, 0, 2);
                plotFill("VisibleMass_mmtt_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lltt_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_lltt_pp", SVMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][1] = Event;
            }
            if (charge_Type && !tau3_IsoB && !tau4_IsoB && (Event != Event_Double[1][1])) {
                plotFill("TauPtJetPt_ff", l3Pt / l3_CloseJetPt, 100, 0, 2);
                plotFill("TauPtJetPt_ff", l4Pt / l4_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_ff", l3_RefJetPt / l3_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_ff", l4_RefJetPt / l4_CloseJetPt, 100, 0, 2);
                plotFill("FakeRate_MMTT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_ff_Jet", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_ff_RefJet", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][1] = Event;
                //eta dependency Tau FR
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_RefJet_BB", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_RefJet_BE", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_RefJet_EB", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_RefJet_EE", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                //eta dependency CloseREf FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_CloseJet_BB", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_CloseJet_BE", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_CloseJet_EB", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_CloseJet_EE", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (charge_Type && !tau3_IsoB && tau4_IsoB && (Event != Event_Double[2][1])) {
                plotFill("FakeRate_MMTT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_fp_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_fp_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][1] = Event;
                //eta dependency Tau FR
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_RefJet_BB", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_RefJet_BE", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_RefJet_EB", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_RefJet_EE", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                //eta dependency CloseREf FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_CloseJet_BB", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_CloseJet_BE", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_CloseJet_EB", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_CloseJet_EE", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            }
            if (charge_Type && tau3_IsoB && !tau4_IsoB && (Event != Event_Double[3][1])) {
                plotFill("FakeRate_MMTT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_pf_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_pf_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][1] = Event;
                //eta dependency Tau FR
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_RefJet_BB", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_RefJet_BE", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_RefJet_EB", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_RefJet_EE", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                //eta dependency CloseREf FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_CloseJet_BB", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_CloseJet_BE", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_CloseJet_EB", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_CloseJet_EE", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            }
            //Shape of Reducible BG
            if (SS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7 && (Event != Event_Double[4][1])) {
                plotFill("H_VisibleMass_Shape_lltt", HMass, pt_Bin, 0, pt_Bin);
                plotFill("Z_Mass_Shape_lltt", ZMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                Event_Double[4][1] = Event;
            }
            if (SS && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {
                plotFill("H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.4 && l4_tauIsoMVA2raw > 0.4) {
                plotFill("H_VisibleMass_Shape_lltt_04", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_04", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.5 && l4_tauIsoMVA2raw > 0.5) {
                plotFill("H_VisibleMass_Shape_lltt_05", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_05", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.6 && l4_tauIsoMVA2raw > 0.6) {
                plotFill("H_VisibleMass_Shape_lltt_06", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_06", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7) {
                plotFill("H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.8 && l4_tauIsoMVA2raw > 0.8) {
                plotFill("H_VisibleMass_Shape_lltt_08", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_08", SVMass, pt_Bin, 0, pt_Bin);
            }
            //            Opposite sign
            if (OS && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {
                plotFill("OS_H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("OS_H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (OS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7) {
                plotFill("OS_H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("OS_H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
            }

        }


        //####################################################
        //  Fake Rate Application (MMET)
        //####################################################

        if (Channel == 92 && charge_Type && LTcut && l4Pt > CutOnTauPt && mu_Size == 2 && l4_tauRejEleMVA3T && l4_tauRejMu2L) {



            if (tau4_IsoB && (l3_eleId_Loose && (l3_eleIso < looseEle)) && (Event != Event_Double[0][2])) {
                plotFill("VisibleMass_mmet_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ele_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ele_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_llet_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lllt_pp", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }
            if (!tau4_IsoB && (!l3_eleId_Loose || !(l3_eleIso < looseEle)) && (Event != Event_Double[1][2])) {

                plotFill("FakeRate_MMET_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_ff_JetTau", l4_CloseJetPt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_ff_JetRef", l4_RefJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);

                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_ff_B", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_ff_E", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][2] = Event;
            }
            if (!tau4_IsoB && (l3_eleId_Loose && l3_eleIso < looseEle) && (Event != Event_Double[2][2])) {
                plotFill("FakeRate_MMET_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_fp_JetTau", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_fp_Ref_Jet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_fp_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_fp_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][2] = Event;
            }
            if (tau4_IsoB && (!l3_eleId_Loose || !(l3_eleIso < looseEle)) && (Event != Event_Double[3][2])) {
                plotFill("FakeRate_MMET_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_pf_JetTau", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMET_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_pf_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_pf_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][2] = Event;
            }
            //Shape of Reducible BG
            if (SS && l4_tauIsoMVA2raw > 0.7 && (l3_eleId_Loose && (l3_eleIso < 1.0)) && (Event != Event_Double[4][2])) {
                plotFill("H_VisibleMass_Shape_llet", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_VisibleMass_Shape_lllt", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[4][2] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (MMMT)
        //####################################################

        if (Channel == 93 && charge_Type && LTcut && l4Pt > CutOnTauPt && electron_Size == 0 && l4_tauRejEleL && l4_tauRejMu2T) {

            if (tau4_IsoB && (l3_muId_Loose && (l3_muIso < looseMu)) && (Event != Event_Double[0][3])) {
                plotFill("VisibleMass_mmmt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_mu_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_mu_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_llmt_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lllt_pp", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][3] = Event;
            }
            if (!tau4_IsoB && (!l3_muId_Loose || !(l3_muIso < looseMu)) && (Event != Event_Double[1][3])) {
                plotFill("FakeRate_MMMT_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_ff_JetTau", l4_CloseJetPt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_ff_RefJet", l4_RefJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_ff_B", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_ff_E", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][3] = Event;
            }
            if (!tau4_IsoB && (l3_muId_Loose && l3_muIso < looseMu) && (Event != Event_Double[2][3])) {
                plotFill("FakeRate_MMMT_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_fp_JetTau", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_fp_Ref_Jet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_fp_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_fp_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][3] = Event;
            }
            if (tau4_IsoB && (!l3_muId_Loose || !(l3_muIso < looseMu)) && (Event != Event_Double[3][3])) {
                plotFill("FakeRate_MMMT_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_pf_JetTau", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMMT_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_pf_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_pf_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][3] = Event;
            }
            //Shape of Reducible BG
            if (SS && l4_tauIsoMVA2raw > 0.7 && (l3_muId_Loose && (l3_muIso < 1.0)) && (Event != Event_Double[4][3])) {
                plotFill("H_VisibleMass_Shape_llmt", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_VisibleMass_Shape_lllt", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[4][3] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (mmme)
        //####################################################
        if (Channel == 94 && charge_Type) {

            if ((l4_eleId_Loose && l4_eleIso < looseLep) && (l3_muId_Loose && l3_muIso < looseLep) && (Event != Event_Double[0][4])) {
                plotFill("VisibleMass_mmme_pp", HMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Z_Mass_mmme", ZMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                Event_Double[0][4] = Event;
            }
            if ((!l4_eleId_Loose || !(l4_eleIso < looseLep)) && (!l3_muId_Loose || !(l3_muIso < looseLep)) && (Event != Event_Double[1][4])) {
                plotFill("FakeRate_MMME_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_ff_RefJet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][4] = Event;
            }
            if ((!l4_eleId_Loose || !(l4_eleIso < looseLep)) && (l3_muId_Loose && l3_muIso < looseLep) && (Event != Event_Double[2][4])) {
                plotFill("FakeRate_MMME_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_fp_Ref_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                Event_Double[2][4] = Event;
            }
            if ((l4_eleId_Loose && (l4_eleIso < looseLep)) && (!l3_muId_Loose || !(l3_muIso < looseLep)) && (Event != Event_Double[3][4])) {
                plotFill("FakeRate_MMME_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMME_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                Event_Double[3][4] = Event;
            }
        }
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        // EETT FakeRateation
        //####################################################
        //####################################################
        //####################################################
        //####################################################

        if ((Channel == 95) && LTcut && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL) {
            //        if ((Channel == 95) && charge_Type &&  LTcut && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt) {


            if (charge_Type && tau3_IsoB && tau4_IsoB && (Event != Event_Double[0][5])) {
                plotFill("TauPtJetPt_pp", l3Pt / l3_CloseJetPt, 100, 0, 2);
                plotFill("TauPtJetPt_pp", l4Pt / l4_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_pp", l3_RefJetPt / l3_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_pp", l4_RefJetPt / l4_CloseJetPt, 100, 0, 2);
                plotFill("VisibleMass_eett_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lltt_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_lltt_pp", SVMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][5] = Event;
            }
            if (charge_Type && !tau3_IsoB && !tau4_IsoB && (Event != Event_Double[1][5])) {
                plotFill("TauPtJetPt_ff", l3Pt / l3_CloseJetPt, 100, 0, 2);
                plotFill("TauPtJetPt_ff", l4Pt / l4_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_ff", l3_RefJetPt / l3_CloseJetPt, 100, 0, 2);
                plotFill("Ratio_RefJet_CorrectedJet_ff", l4_RefJetPt / l4_CloseJetPt, 100, 0, 2);
                plotFill("FakeRate_EETT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_ff_Jet", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_ff_RefJet", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][5] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_RefJet_BB", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_RefJet_BE", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_RefJet_EB", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_RefJet_EE", l3_RefJetPt, l4_RefJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                //eta dependency CloseJet FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_CloseJet_BB", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_CloseJet_BE", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_CloseJet_EB", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_CloseJet_EE", l3_CloseJetPt, l4_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (charge_Type && !tau3_IsoB && tau4_IsoB && (Event != Event_Double[2][5])) {
                plotFill("FakeRate_EETT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_fp_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_fp_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][5] = Event;
                //eta dependency Tau FR
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_RefJet_BB", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_RefJet_BE", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_RefJet_EB", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_RefJet_EE", l3_RefJetPt, pt_Bin, 0, pt_Bin);
                //eta dependency CloseREf FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_CloseJet_BB", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_CloseJet_BE", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_CloseJet_EB", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_CloseJet_EE", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            }
            if (charge_Type && tau3_IsoB && !tau4_IsoB && (Event != Event_Double[3][5])) {
                plotFill("FakeRate_EETT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_pf_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_pf_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][5] = Event;
                //eta dependency Tau FR
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
                //eta dependency JetREf FR
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_RefJet_BB", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) < value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_RefJet_BE", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_RefJet_EB", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_RefJetEta) > value_Eta && TMath::Abs(l4_RefJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_RefJet_EE", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                //eta dependency CloseREf FR
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_CloseJet_BB", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) < value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_CloseJet_BE", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_CloseJet_EB", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3_CloseJetEta) > value_Eta && TMath::Abs(l4_CloseJetEta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_CloseJet_EE", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            }
            //Shape of Reducible BG
            if (SS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7 && (Event != Event_Double[4][5])) {
                plotFill("H_VisibleMass_Shape_lltt", HMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Z_Mass_Shape_lltt", ZMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                Event_Double[4][5] = Event;
            }
            if (SS && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {
                plotFill("H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.4 && l4_tauIsoMVA2raw > 0.4) {
                plotFill("H_VisibleMass_Shape_lltt_04", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_04", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.5 && l4_tauIsoMVA2raw > 0.5) {
                plotFill("H_VisibleMass_Shape_lltt_05", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_05", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.6 && l4_tauIsoMVA2raw > 0.6) {
                plotFill("H_VisibleMass_Shape_lltt_06", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_06", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7) {
                plotFill("H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
                plotFill("SS_H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (SS && l3_tauIsoMVA2raw > 0.8 && l4_tauIsoMVA2raw > 0.8) {
                plotFill("H_VisibleMass_Shape_lltt_08", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_SVMass_Shape_lltt_08", SVMass, pt_Bin, 0, pt_Bin);
            }
            //                  Opposite sign
            if (OS && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {
                plotFill("OS_H_VisibleMass_Shape_lltt_00", HMass, pt_Bin, 0, pt_Bin);
                plotFill("OS_H_SVMass_Shape_lltt_00", SVMass, pt_Bin, 0, pt_Bin);
            }
            if (OS && l3_tauIsoMVA2raw > 0.7 && l4_tauIsoMVA2raw > 0.7) {
                plotFill("OS_H_VisibleMass_Shape_lltt_07", HMass, pt_Bin, 0, pt_Bin);
                plotFill("OS_H_SVMass_Shape_lltt_07", SVMass, pt_Bin, 0, pt_Bin);
            }

        }
        //####################################################
        //  Fake Rate Application (EEMT)
        //####################################################

        if (Channel == 96 && charge_Type && LTcut && l4Pt > CutOnTauPt && electron_Size == 2 && l4_tauRejEleL && l4_tauRejMu2T) {

            if (tau4_IsoB && (l3_muId_Loose && l3_muIso < looseMu) && (Event != Event_Double[0][6])) {
                plotFill("VisibleMass_eemt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_mu_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_mu_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_llmt_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lllt_pp", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }
            if (!tau4_IsoB && (!l3_muId_Loose || !(l3_muIso < looseMu)) && (Event != Event_Double[1][6])) {
                plotFill("FakeRate_EEMT_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_ff_JetTau", l4_CloseJetPt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_ff_RefJet", l4_RefJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_ff_B", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_ff_E", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][6] = Event;
            }
            if (!tau4_IsoB && (l3_muId_Loose && l3_muIso < looseMu) && (Event != Event_Double[2][6])) {
                plotFill("FakeRate_EEMT_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_fp_JetTau", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_fp_Ref_Jet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_fp_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_fp_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][6] = Event;
            }
            if (tau4_IsoB && (!l3_muId_Loose || !(l3_muIso < looseMu)) && (Event != Event_Double[3][6])) {
                plotFill("FakeRate_EEMT_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_pf_JetTau", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEMT_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_pf_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_pf_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][6] = Event;
            }
            //Shape of Reducible BG
            if (SS && l4_tauIsoMVA2raw > 0.7 && (l3_muId_Loose && (l3_muIso < 1.0)) && (Event != Event_Double[4][6])) {
                plotFill("H_VisibleMass_Shape_llmt", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_VisibleMass_Shape_lllt", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[4][6] = Event;
            }
        }
        //####################################################
        //  Fake Rate Application (EEET)
        //####################################################

        if (Channel == 97 && charge_Type && LTcut && l4Pt > CutOnTauPt && mu_Size == 0 && l4_tauRejEleMVA3T && l4_tauRejMu2L) {

            if (tau4_IsoB && (l3_eleId_Loose && (l3_eleIso < looseEle)) && (Event != Event_Double[0][7])) {
                plotFill("VisibleMass_eeet_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ele_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ele_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_llet_pp", HMass, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lllt_pp", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][7] = Event;
            }
            if (!tau4_IsoB && (!l3_eleId_Loose || !(l3_eleIso < looseEle)) && (Event != Event_Double[1][7])) {
                plotFill("FakeRate_EEET_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_ff_JetTau", l4_CloseJetPt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_ff_RefJet", l4_RefJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_ff_B", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_ff_E", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][7] = Event;
            }
            if (!tau4_IsoB && (l3_eleId_Loose && l3_eleIso < looseEle) && (Event != Event_Double[2][7])) {
                plotFill("FakeRate_EEET_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_fp_JetTau", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_fp_Ref_Jet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_fp_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_fp_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][7] = Event;
            }
            if (tau4_IsoB && (!l3_eleId_Loose || !(l3_eleIso < looseEle)) && (Event != Event_Double[3][7])) {
                plotFill("FakeRate_EEET_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_pf_JetTau", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEET_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_pf_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_pf_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][7] = Event;
            }
            //Shape of Reducible BG
            if (SS && l4_tauIsoMVA2raw > 0.7 && (l3_eleId_Loose && (l3_eleIso < 1.0)) && (Event != Event_Double[4][7])) {
                plotFill("H_VisibleMass_Shape_llet", HMass, pt_Bin, 0, pt_Bin);
                plotFill("H_VisibleMass_Shape_lllt", HMass, pt_Bin, 0, pt_Bin);
                Event_Double[4][7] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (eeem)
        //####################################################
        if (Channel == 98 && charge_Type) {

            if ((l3_eleId_Loose && (l3_eleIso < looseLep)) && (l4_muId_Loose && l4_muIso < looseLep) && (Event != Event_Double[0][8])) {
                plotFill("VisibleMass_eeem_pp", HMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Z_Mass_eeem", ZMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                Event_Double[0][8] = Event;
            }
            if ((!l3_eleId_Loose || !(l3_eleIso < looseLep)) && (!l4_muId_Loose || !(l4_muIso < looseLep)) && (Event != Event_Double[1][8])) {
                plotFill("FakeRate_EEEM_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_ff_Jet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_ff_RefJet", l4_CloseJetPt, l3_CloseJetPt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][8] = Event;
            }
            if ((!l4_muId_Loose || !(l4_muIso < looseLep)) && (l3_eleId_Loose && (l3_eleIso < looseLep)) && (Event != Event_Double[2][8])) {
                plotFill("FakeRate_EEEM_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_fp_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_fp_Ref_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
                Event_Double[2][8] = Event;
            }
            if ((l4_muId_Loose && l4_muIso < looseLep) && (!l3_eleId_Loose || !(l3_eleIso < looseLep)) && (Event != Event_Double[3][8])) {
                plotFill("FakeRate_EEEM_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_pf_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EEEM_apply_pf_RefJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
                Event_Double[3][8] = Event;
            }
        }
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        // Tau Fake Rate Measurement
        //####################################################
        bool FR_Estimation = true;

        if ((Channel == 91 || Channel == 95) && SS && LTcut && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL && Event != Ev_double_tau) {
            //        if ((Channel == 91 || Channel == 95) && (l3Charge * l4Charge > 0) && LTcut && l3Pt > 10 && l4Pt > 10 && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL && Event != Ev_double_tau) {

            Ev_double_tau = Event;


            plotFill("deta_CloseJet_RefJet", l3_RefJetEta - l3_CloseJetEta, 400, -.2, .2);
            plotFill("deta_CloseJet_RefJet", l4_RefJetEta - l4_CloseJetEta, 400, -.2, .2);
            plotFill("dphi_CloseJet_RefJet", l3_RefJetPhi - l3_CloseJetPhi, 400, -.2, .2);
            plotFill("dphi_CloseJet_RefJet", l4_RefJetPhi - l4_CloseJetPhi, 400, -.2, .2);
            plotFill("dR_CloseJet_RefJet", dR(l3_RefJetEta, l3_RefJetPhi, l3_CloseJetEta, l3_CloseJetPhi), 400, -.2, .2);
            plotFill("dR_CloseJet_RefJet", dR(l4_RefJetEta, l4_RefJetPhi, l4_CloseJetEta, l4_CloseJetPhi), 400, -.2, .2);


            //#########################
            // Tau Fake Rate in Just 1 eta bin
            //#########################
            //Total FR in terms of CutOnTauPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l4Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l4Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l4Pt, pt_Bin, 0, pt_Bin);

            //Total FR in terms of RefJetPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin);

            //Total FR in terms of JetPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin);


            //#########################
            // Tau Fake Rate in 2 eta bin
            //#########################
            //Barrel Fake rate
            if (FR_Estimation && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l4Pt, pt_Bin, 0, pt_Bin);
            //EndCap Fake rate
            if (FR_Estimation && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l4Pt, pt_Bin, 0, pt_Bin);

            //Barrel Fake rate
            if (FR_Estimation && l3_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_B", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_B", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_B", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_B", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            //EndCap Fake rate
            if (FR_Estimation && l3_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_E", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_E", l4_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_E", l3_RefJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_E", l4_RefJetPt, pt_Bin, 0, pt_Bin);

            //Barrel Fake rate
            if (FR_Estimation && l3_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            //EndCap Fake rate
            if (FR_Estimation && l3_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau3_IsoB && l3_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && tau4_IsoB && l4_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin);


            //            if (FR_Estimation && l3_tauIsoM && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoM && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l4Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoT && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoT && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l4Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoM && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoM && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l4Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l3_tauIsoT && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l3Pt, pt_Bin, 0, pt_Bin);
            //            if (FR_Estimation && l4_tauIsoT && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l4Pt, pt_Bin, 0, pt_Bin);

        }

        //#########################
        // Tau Fake Rate VS eta
        //#########################
        //fake Rate v.s eta

        //Tau Fake Rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before", l3Eta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before", l4Eta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose", l3Eta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose", l4Eta, 250, -2.5, 2.5);

        //RefJet Fake rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_RefJet", l3_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_RefJet", l4_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_RefJet", l3_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_RefJet", l4_RefJetEta, 250, -2.5, 2.5);

        //CloseJet Fake rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_CloseJet", l3_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_CloseJet", l4_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_CloseJet", l3_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_CloseJet", l4_CloseJetEta, 250, -2.5, 2.5);
        //####################################################
        // Ele Mu  Fake Rate Measurements
        //####################################################
        //0 GeV Tau
        bool eleFR_denum_0 = ((Channel == 92 && electron_Size < 2) || (Channel == 97 && electron_Size < 4)) && SS && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5 && l4_tauRejEleMVA3T && l4_tauRejMu2L;
        if (Event != Ev_double_ele) {
            Ev_double_ele = Event;
            if (eleFR_denum_0) plotFill("4objFR_Ele_Denum_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (eleFR_denum_0) plotFill("4objFR_Ele_Denum_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (eleFR_denum_0 && l3_eleId_Loose && l3_eleIso < looseLep) plotFill("4objFR_Ele_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (eleFR_denum_0 && l3_eleId_Tight && l3_eleIso < tightEle) plotFill("4objFR_Ele_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (eleFR_denum_0 && l3_eleId_Loose && l3_eleIso < looseLep) plotFill("4objFR_Ele_NumLoose_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (eleFR_denum_0 && l3_eleId_Tight && l3_eleIso < tightEle) plotFill("4objFR_Ele_NumTight_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
        }
        bool muFR_denum_0 = ((Channel == 93 && mu_Size < 4) || (Channel == 96 && mu_Size < 2)) && SS && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5 && l4_tauRejEleL && l4_tauRejMu2T;
        if (Event != Ev_double_mu) {
            Ev_double_mu = Event;
            if (muFR_denum_0) plotFill("4objFR_Mu_Denum_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (muFR_denum_0) plotFill("4objFR_Mu_Denum_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (muFR_denum_0 && l3_muId_Loose && l3_muIso < looseLep) plotFill("4objFR_Mu_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (muFR_denum_0 && l3_muId_Tight && l3_muIso < tightMu) plotFill("4objFR_Mu_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin);
            if (muFR_denum_0 && l3_muId_Loose && l3_muIso < looseLep) plotFill("4objFR_Mu_NumLoose_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
            if (muFR_denum_0 && l3_muId_Tight && l3_muIso < tightMu) plotFill("4objFR_Mu_NumTight_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin);
        }
        //
        //
        //        //##################################################
        //        //5 GeV Tau
        //        bool eleFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        //        if (eleFR_denum_5) plotFill("4objFR_Ele_Denum_5", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin);
        //
        //        bool muFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        //        if (muFR_denum_5) plotFill("4objFR_Mu_Denum_5", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (muFR_denum_5 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (muFR_denum_5 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin);
        //
        //        //##################################################
        //        //10 GeV Tau
        //        bool eleFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        //        if (eleFR_denum_10) plotFill("4objFR_Ele_Denum_10", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin);
        //
        //        bool muFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        //        if (muFR_denum_10) plotFill("4objFR_Mu_Denum_10", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (muFR_denum_10 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (muFR_denum_10 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin);
        //


        //        if (((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 20) {
        //            plotFill("4objFR_Ele_Denum_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //        if (((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 20) {
        //            plotFill("4objFR_Mu_Denum_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_justTmass", l3Pt, pt_Bin, 0, pt_Bin);
        //        }



        //################
        // 3-onj fake rate
        //################
        //        bool Mu_denum = (Channel == 101 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi));
        //        //        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi));
        //        bool Mu_denum = (Channel == 101 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);
        //        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);
        //
        //        if (Mu_denum) {
        //            plotFill("3objFR_Mu_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Mu_denum && l3_muId && l3_muIso < tightMu) {
        //            plotFill("3objFR_Mu_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Mu_denum && l3_muId && l3_muIso < looseMu) {
        //            plotFill("3objFR_Mu_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Ele_denum) {
        //            plotFill("3objFR_Ele_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Ele_denum && l3_eleId && l3_eleIso < tightEle) {
        //            plotFill("3objFR_Ele_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Ele_denum && l3_eleId && l3_eleIso < looseEle) {
        //            plotFill("3objFR_Ele_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //        //####################################################
        //        if (Mu_denum && l3_muId) {
        //            plotFill("3objFR_Mu_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Mu_denum && l3_muIso < looseMu) {
        //            plotFill("3objFR_Mu_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Ele_denum && l3_eleId) {
        //            plotFill("3objFR_Ele_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //        if (Ele_denum && l3_eleIso < looseEle) {
        //            plotFill("3objFR_Ele_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //
        //





    }


    fout->cd();

    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();

    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();

    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();

    fout->Close();

}

