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
//#include "../interface/zh_Auxiliary.h"
#include "myHelper.h"
#include "../interface/mvaXXX.h"

int main(int argc, char** argv) {
    string chargeOfH = *(argv + 1);
    string out = *(argv + 2);
    string input = *(argv + 3);


    //PRINTING THE OUTPUT name
    cout << "\n\n\n OUTPUT NAME IS:    " << out << endl;
    TFile *fout = TFile::Open(out.c_str(), "RECREATE");

    using namespace std;

    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    //
    TFile *f_Double = new TFile(input.c_str(), "UPDATE");
    TTree *Run_Tree = (TTree*) f_Double->Get("RLE_tree");

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(1);









    int Channel = 0;
    int Run = 0;
    int Lumi = 0;
    int Event = 0;
    float IMass = 0;
    float ZMass = 0;
    float HMass = 0;
    float met, metPhi, pfmet, pfmetPhi;
    float l1M, l1Px, l1Py, l1Pz, l1E, l1Pt, l1Phi, l1Eta, l1Charge, l1_muId, l1_muIso, l1_eleId, l1_eleIso, l1_eleMVANonTrg, l1_eleNumHit = -10;
    float l2M, l2Px, l2Py, l2Pz, l2E, l2Pt, l2Phi, l2Eta, l2Charge, l2_muId, l2_muIso, l2_eleId, l2_eleIso, l2_eleMVANonTrg, l2_eleNumHit = -10;
    float l3M, l3Px, l3Py, l3Pz, l3E, l3Pt, l3Phi, l3Eta, l3Charge, l3_muId, l3_muIso, l3_eleId, l3_eleIso, l3_eleMVANonTrg, l3_eleNumHit, l3_tauIsoMVA2raw = -10;
    float l4M, l4Px, l4Py, l4Pz, l4E, l4Pt, l4Phi, l4Eta, l4Charge, l4_muId, l4_muIso, l4_eleId, l4_eleIso, l4_eleMVANonTrg, l4_eleNumHit, l4_tauIsoMVA2raw = -10;
    bool l3_tauIsoL, l3_tauIsoM, l3_tauIsoT, l3_tauRejMuL, l3_tauRejMuM, l3_tauRejMuT, l3_tauRejEleL, l3_tauRejEleM, l3_tauRejEleMVA;
    bool l3_tauIso3HitL, l3_tauIso3HitM, l3_tauIso3HitT, l3_tauRejMu2L, l3_tauRejMu2M, l3_tauRejMu2T, l3_tauRejEleMVA3L, l3_tauRejEleMVA3M, l3_tauRejEleMVA3T;
    bool l3_tauIsoVL, l3_tauIsoMVA2L, l3_tauIsoMVA2M, l3_tauIsoMVA2T;
    bool l4_tauIsoL, l4_tauIsoM, l4_tauIsoT, l4_tauRejMuL, l4_tauRejMuM, l4_tauRejMuT, l4_tauRejEleL, l4_tauRejEleM, l4_tauRejEleMVA;
    bool l4_tauIso3HitL, l4_tauIso3HitM, l4_tauIso3HitT, l4_tauRejMu2L, l4_tauRejMu2M, l4_tauRejMu2T, l4_tauRejEleMVA3L, l4_tauRejEleMVA3M, l4_tauRejEleMVA3T;
    bool l4_tauIsoVL, l4_tauIsoMVA2L, l4_tauIsoMVA2M, l4_tauIsoMVA2T;

    float covMet11, covMet12, covMet21, covMet22;
    float pfcovMet11, pfcovMet12, pfcovMet21, pfcovMet22;
    float eff_Correction, pu_Weight;
    int num_PV, num_bjet, num_goodjet;
    int mu_Size, BareMuon_Size, electron_Size, BareElectron_Size, tau_Size, BareTau_Size;
    int mu_partTight_Size, ele_partTight_Size;
    float l3_CloseJetPt, l4_CloseJetPt;











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
    Run_Tree->SetBranchAddress("l3_muId", &l3_muId);
    Run_Tree->SetBranchAddress("l3_muIso", &l3_muIso);
    Run_Tree->SetBranchAddress("l3_eleId", &l3_eleId);
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

    Run_Tree->SetBranchAddress("l4M", &l4M);
    Run_Tree->SetBranchAddress("l4E", &l4E);
    Run_Tree->SetBranchAddress("l4Px", &l4Px);
    Run_Tree->SetBranchAddress("l4Py", &l4Py);
    Run_Tree->SetBranchAddress("l4Pz", &l4Pz);
    Run_Tree->SetBranchAddress("l4Pt", &l4Pt);
    Run_Tree->SetBranchAddress("l4Eta", &l4Eta);
    Run_Tree->SetBranchAddress("l4Phi", &l4Phi);
    Run_Tree->SetBranchAddress("l4Charge", &l4Charge);
    Run_Tree->SetBranchAddress("l4_muId", &l4_muId);
    Run_Tree->SetBranchAddress("l4_muIso", &l4_muIso);
    Run_Tree->SetBranchAddress("l4_eleId", &l4_eleId);
    Run_Tree->SetBranchAddress("l4_eleIso", &l4_eleIso);
    Run_Tree->SetBranchAddress("l4_eleMVANonTrg", &l4_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l4_eleNumHit", &l4_eleNumHit);
    Run_Tree->SetBranchAddress("l4_CloseJetPt", &l4_CloseJetPt);
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



    //######################################################
    //Booking MVA just once
    //######################################################
    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");


    reader->AddVariable("N_LT", &N_LT);
    reader->AddVariable("N_IsoTot", &N_IsoTot);
    reader->AddVariable("N_MET", &N_MET);


    TString dir = "weights/";
    TString prefix = "TMVAClassification";

    // Book method(s)
    TString methodName = TString("BDT") + TString(" method");
    TString weightfile = dir + prefix + TString("_") + TString("BDT") + TString(".weights.xml");
    reader->BookMVA(methodName, weightfile);
    //######################################################
    //TREE FOR MVA
    //######################################################

    float N_LT, N_MET;
    float N_l3_tauIsoMVA2raw, N_l4_tauIsoMVA2raw, N_IsoTot;
    float N_l3_LepId, N_l3_LepIso, N_TMass;

    //   MVA for LLTT ######################################################
    TTree * MVATree = new TTree("MVATree", "MVATree");
    //    To force a memory-resident Tree
    MVATree->SetDirectory(0);
    MVATree->Branch("N_LT", &N_LT, "N_LT/F");
    MVATree->Branch("N_MET", &N_MET, "N_MET/F");
    MVATree->Branch("N_l3_tauIsoMVA2raw", &N_l3_tauIsoMVA2raw, "N_l3_tauIsoMVA2raw/F");
    MVATree->Branch("N_l4_tauIsoMVA2raw", &N_l4_tauIsoMVA2raw, "N_l4_tauIsoMVA2raw/F");
    MVATree->Branch("N_IsoTot", &N_IsoTot, "N_IsoTot/F");

    //   MVA for LLMT ######################################################
    TTree * MVATreeLT = new TTree("MVATreeLT", "MVATreeLT");
    //    To force a memory-resident Tree
    MVATreeLT->SetDirectory(0);
    MVATreeLT->Branch("N_LT", &N_LT, "N_LT/F");
    MVATreeLT->Branch("N_MET", &N_MET, "N_MET/F");
    MVATreeLT->Branch("N_l4_tauIsoMVA2raw", &N_l4_tauIsoMVA2raw, "N_l4_tauIsoMVA2raw/F");
    MVATreeLT->Branch("N_l3_LepId", &N_l3_LepId, "N_l3_LepId/F");
    MVATreeLT->Branch("N_l3_LepIso", &N_l3_LepIso, "N_l3_LepIso/F");
    MVATreeLT->Branch("N_TMass", &N_TMass, "N_TMass/F");
    //######################################################

    //    //   MVA for LLET ######################################################
    //    TTree * MVATreeLT = new TTree("MVATreeLT", "MVATreeLT");
    //    //    To force a memory-resident Tree
    //    MVATreeLT->SetDirectory(0);
    //    MVATreeLT->Branch("N_LT", &N_LT, "N_LT/F");
    //    MVATreeLT->Branch("N_MET", &N_MET, "N_MET/F");
    //    MVATreeLT->Branch("N_l4_tauIsoMVA2raw", &N_l4_tauIsoMVA2raw, "N_l4_tauIsoMVA2raw/F");
    //    MVATreeLT->Branch("N_l3_LepId", &N_l3_LepId, "N_l3_LepId/F");
    //    MVATreeLT->Branch("N_l3_LepIso", &N_l3_LepIso, "N_l3_LepIso/F");
    //    MVATreeLT->Branch("N_TMass", &N_TMass, "N_TMass/F");
    //######################################################

    //#######################
    //Predefind Values
    //#######################
    float Val_tauPt = 15;
    int pt_Bin = 200;
    float value_Eta = 1.4;
    float tightMu = 0.15;
    float looseMu = 0.30;
    float tightEle = 0.10;
    float looseEle = 0.30;
    int Event_Double[4][9];
    memset(Event_Double, 0, sizeof (Event_Double[0][0]) * 4 * 9);
    float Ev_double = 0;

    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        //        fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        float TMass_lepMet = TMass_F(l3Pt, l4Px, l3Py, met, metPhi);

        bool l3tauIso = l3_tauIsoMVA2raw > 0;
        bool l4tauIso = l4_tauIsoMVA2raw > 0;
        float Val_Iso = 0.5;
        bool CheckHSign;
        if (chargeOfH.compare("SS") == 0) CheckHSign = l3Charge * l4Charge > 0;
        if (chargeOfH.compare("OS") == 0) CheckHSign = l3Charge * l4Charge < 0;

        //####################################################
        // Tau Fake Rate Application (MMTT)
        //####################################################
        if (Channel == 11) plotFill("MMTT_FF_11", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 21) plotFill("MMTT_FP_21", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 31) plotFill("MMTT_PF_31", l4Pt, pt_Bin, 0, pt_Bin);
        //        if ((Channel == 91) && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 60) && l3Pt > 20 && l4Pt > 20) {
        //        if ((Channel == 91) && (l3Charge * l4Charge < 0) && l3Pt > Val_tauPt && l4Pt > Val_tauPt) {
        if ((Channel == 91) && CheckHSign && l3Pt > Val_tauPt && l4Pt > Val_tauPt && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {


            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l3_tauIsoMVA2raw = l3_tauIsoMVA2raw;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_IsoTot = (l4_tauIsoMVA2raw + l3_tauIsoMVA2raw) / 2;
            MVATree->Fill();

            plotFill("mva_N_LT", N_LT, 200, 0, 200);
            plotFill("mva_N_LT_MMTT", N_LT, 200, 0, 200);
            plotFill("mva_N_MET", N_MET, 200, 0, 200);
            plotFill("mva_N_MET_MMTT", N_MET, 200, 0, 200);
            plotFill("mva_N_IsoTot", N_IsoTot, 200, -1, +1);
            plotFill("mva_N_IsoTot_MMTT", N_IsoTot, 200, -1, 1);
            plotFill("HMass", HMass, 200, 0, 200);
            plotFill("HMass_MMTT", HMass, 200, 0, 200);

            float BDT_Out = mvaXXX(reader, N_LT, N_l3_tauIsoMVA2raw,N_l4_tauIsoMVA2raw, N_MET);
            plotFill("BDT", BDT_Out, 100, -0.8, 0.8);
            if (BDT_Out > 0) {
                plotFill("BDT_Pass0", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_MMTT_BDT0", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT0", HMass, 200, 0, 200);
                plotFill("postMVALT", N_LT, 200, 0, 200);
                plotFill("postMVAMET", N_MET, 200, 0, 200);
                plotFill("postMVAIso", N_IsoTot, 200, -1, +1);
            }
            if (BDT_Out > 0.02) {
                plotFill("BDT_Pass02", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_MMTT_BDT02", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT02", HMass, 200, 0, 200);
            }
            if (BDT_Out > 0.04) {
                plotFill("BDT_Pass04", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_MMTT_BDT04", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT04", HMass, 200, 0, 200);
            }

            if (N_IsoTot > 0.8 && N_LT > 65) {
                plotFill("CutBasedA", N_MET, 200, 0, 200);
            }

            //            if (l3Phi > l4Phi) {
            //
            //                float xpt3 = l3Pt;
            //                l3Pt = l4Pt;
            //                l4Pt = xpt3;
            //
            //                float xEta3 = l3Eta;
            //                l3Eta = l4Eta;
            //                l4Eta = xEta3;
            //
            //                float x_tauIsoL3 = l3_tauIsoL;
            //                l3_tauIsoL = l4_tauIsoL;
            //                l4_tauIsoL = x_tauIsoL3;
            //
            //                float x_tauIsoM3 = l3_tauIsoM;
            //                l3_tauIsoM = l4_tauIsoM;
            //                l4_tauIsoM = x_tauIsoM3;
            //
            //                float x_tauIsoT3 = l3_tauIsoT;
            //                l3_tauIsoT = l4_tauIsoT;
            //                l4_tauIsoT = x_tauIsoT3;
            //            }


            if (!l3tauIso && !l4tauIso && (Event != Event_Double[1][1])) {
                plotFill("FakeRate_MMTT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][1] = Event;
            }
            if (!l3tauIso && l4tauIso && (Event != Event_Double[2][1])) {
                plotFill("FakeRate_MMTT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][1] = Event;
            }
            if (l3tauIso && !l4tauIso && (Event != Event_Double[3][1])) {
                plotFill("FakeRate_MMTT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][1] = Event;
            }
            if (l3tauIso && l4tauIso && (Event != Event_Double[0][1])) {
                plotFill("TMass_lepMet_tt", TMass_lepMet, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_MMTT_apply_pp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[0][1] = Event;
            }

        }


        //####################################################
        //  Fake Rate Application (MMET)
        //####################################################
        //        SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
        if (Channel == 12) plotFill("MMET_FF_12", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 22) plotFill("MMET_FP_22", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 32) plotFill("MMET_PF_32", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (Channel == 92 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 45) && l4Pt > 20 && mu_Size == 2) {
        if (Channel == 92 && CheckHSign && l4Pt > Val_tauPt && mu_Size == 2 && l4_tauIsoMVA2raw > 0 && l3_eleIso < Val_Iso) {

            //######################  MVA   ##################
            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_l3_LepId = l3_eleId;
            N_l3_LepIso = l3_eleIso;
            N_TMass = TMass_F(l3Pt, l3Px, l3Py, met, metPhi);
            MVATreeLT->Fill();



            if (!l4_tauIsoM && (!l3_eleId || !(l3_eleIso < 0.1)) && (Event != Event_Double[1][2]) && ((electron_Size - ele_partTight_Size == 0))) {
                plotFill("FakeRate_MMET_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][2] = Event;
            }
            if (!l4_tauIsoM && (l3_eleId && l3_eleIso < 0.1) && (Event != Event_Double[2][2]) && electron_Size == 1) {
                plotFill("FakeRate_MMET_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][2] = Event;
            }
            if (l4_tauIsoM && (!l3_eleId || !(l3_eleIso < 0.1)) && (Event != Event_Double[3][2]) && ((electron_Size - ele_partTight_Size == 0))) {
                plotFill("FakeRate_MMET_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][2] = Event;
            }
            if (l4_tauIsoM && (l3_eleId && (l3_eleIso < 0.1)) && (Event != Event_Double[0][2]) && ((electron_Size == 1))) {
                plotFill("TMass_lepMet", TMass_lepMet, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }

            //extra Checck
            if (!l4_tauIsoM && (!l3_eleId && !(l3_eleIso < 0.1)) && (Event != Event_Double[0][2]) && ((electron_Size - ele_partTight_Size == 0))) {
                plotFill("FakeRate_MMET_apply_ff_failIdfailId", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }
            if (!l4_tauIsoM && (l3_eleId && !(l3_eleIso < 0.1)) && (Event != Event_Double[0][2]) && ((electron_Size - ele_partTight_Size == 0))) {
                plotFill("FakeRate_MMET_apply_ff_passIdfailIso", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }
            if (!l4_tauIsoM && (!l3_eleId && (l3_eleIso < 0.1)) && (Event != Event_Double[0][2]) && ((electron_Size - ele_partTight_Size == 0))) {
                plotFill("FakeRate_MMET_apply_ff_failIdpassIso", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (MMMT)
        //####################################################
        //        SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
        if (Channel == 13) plotFill("MMMT_FF_13", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 23) plotFill("MMMT_FP_23", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 33) plotFill("MMMT_PF_33", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (Channel == 93 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 45) && l4Pt > 20 && electron_Size == 0) {
        if (Channel == 93 && CheckHSign && l4Pt > Val_tauPt && electron_Size == 0 && l4_tauIsoMVA2raw > 0 && l3_muIso < Val_Iso) {

            //######################  MVA   ##################
            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_l3_LepId = l3_muId;
            N_l3_LepIso = l3_muIso;
            N_TMass = TMass_F(l3Pt, l3Px, l3Py, met, metPhi);
            MVATreeLT->Fill();
            //######################  MVA   ##################

            if (!l4_tauIsoM && (!l3_muId || !(l3_muIso < 0.15)) && (Event != Event_Double[1][3]) && (mu_Size - mu_partTight_Size == 2)) {
                plotFill("FakeRate_MMMT_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][3] = Event;
            }
            if (!l4_tauIsoM && (l3_muId && l3_muIso < 0.15) && (Event != Event_Double[2][3]) && mu_Size == 3) {
                plotFill("FakeRate_MMMT_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][3] = Event;
            }
            if (l4_tauIsoM && (!l3_muId || !(l3_muIso < 0.15)) && (Event != Event_Double[3][3]) && (mu_Size - mu_partTight_Size == 2)) {
                plotFill("FakeRate_MMMT_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][3] = Event;
            }
            if (l4_tauIsoM && (l3_muId && (l3_muIso < 0.15)) && (Event != Event_Double[0][3]) && (mu_Size == 3)) {
                plotFill("TMass_lepMet", TMass_lepMet, pt_Bin, 0, pt_Bin);
                Event_Double[0][3] = Event;
            }

        }
        //####################################################
        //  Fake Rate Application (MMME)
        //####################################################
        //        SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
        if (Channel == 14) plotFill("MMME_FF_14", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 24) plotFill("MMME_FP_24", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 34) plotFill("MMME_PF_34", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 94 && CheckHSign && (l3Pt + l4Pt > 30) && NewOverLap(l1Eta, l1Phi, l2Eta, l2Phi, l3Eta, l3Phi, l4Eta, l4Phi)) {

            if ((!l4_eleId || !(l4_eleIso < 0.30)) && (!l3_muId || !(l3_muIso < 0.30)) && (Event != Event_Double[1][4]) && ((mu_Size == 2)) && ((electron_Size == 0))) {
                plotFill("FakeRate_MMME_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][4] = Event;
            }
            if ((!l4_eleId || !(l4_eleIso < 0.30)) && (l3_muId && l3_muIso < 0.30) && (Event != Event_Double[2][4]) && mu_Size == 3 && ((electron_Size == 0))) {
                plotFill("FakeRate_MMME_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][4] = Event;
            }
            if ((l4_eleId && (l4_eleIso < 0.30)) && (!l3_muId || !(l3_muIso < 0.30)) && (Event != Event_Double[3][4]) && electron_Size == 1 && ((mu_Size == 2))) {
                plotFill("FakeRate_MMME_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][4] = Event;
            }

        }

        //####################################################
        // Tau Fake Rate Application (EETT)
        //####################################################
        if (Channel == 15) plotFill("EETT_FF_15", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 25) plotFill("EETT_FP_25", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 35) plotFill("EETT_PF_35", l4Pt, pt_Bin, 0, pt_Bin);
        //        if ((Channel == 95) && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 60) && l3Pt > 20 && l4Pt > 20) {
        //        if ((Channel == 95) && (l3Charge * l4Charge < 0) && l3Pt > Val_tauPt && l4Pt > Val_tauPt) {
        if ((Channel == 95) && CheckHSign && l3Pt > Val_tauPt && l4Pt > Val_tauPt && l3_tauIsoMVA2raw > 0 && l4_tauIsoMVA2raw > 0) {


            plotFill("l3_tauIsoMVA2raw_H", l3_tauIsoMVA2raw, 200, -1, 1);
            plotFill("l4_tauIsoMVA2raw_H", l4_tauIsoMVA2raw, 200, -1, 1);
            if (l3_tauIsoMVA2L) plotFill("l3_tauIsoMVA2raw_H_Loose", l3_tauIsoMVA2raw, 200, -1, 1);
            if (l4_tauIsoMVA2L) plotFill("l4_tauIsoMVA2raw_H_Loose", l4_tauIsoMVA2raw, 200, -1, 1);
            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l3_tauIsoMVA2raw = l3_tauIsoMVA2raw;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_IsoTot = (l4_tauIsoMVA2raw + l3_tauIsoMVA2raw) / 2;
            MVATree->Fill();


            plotFill("mva_N_LT", N_LT, 200, 0, 200);
            plotFill("mva_N_LT_EETT", N_LT, 200, 0, 200);
            plotFill("mva_N_MET", N_MET, 200, 0, 200);
            plotFill("mva_N_MET_EETT", N_MET, 200, 0, 200);
            plotFill("mva_N_IsoTot", N_IsoTot, 200, -1, 1);
            plotFill("mva_N_IsoTot_EETT", N_IsoTot, 200, -1, 1);
            plotFill("HMass", HMass, 200, 0, 200);
            plotFill("HMass_EETT", HMass, 200, 0, 200);

            float BDT_Out = mvaXXX(reader, N_LT, N_IsoTot, N_MET);
            plotFill("BDT", BDT_Out, 100, -0.8, 0.8);
            if (BDT_Out > 0) {
                plotFill("BDT_Pass0", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_EETT_BDT0", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT0", HMass, 200, 0, 200);
                plotFill("postMVALT", N_LT, 200, 0, 200);
                plotFill("postMVAMET", N_MET, 200, 0, 200);
                plotFill("postMVAIso", N_IsoTot, 200, -1, +1);
            }
            if (BDT_Out > 0.02) {
                plotFill("BDT_Pass02", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_EETT_BDT02", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT02", HMass, 200, 0, 200);
            }
            if (BDT_Out > 0.04) {
                plotFill("BDT_Pass04", BDT_Out, 100, -0.8, 0.8);
                plotFill("HMass_EETT_BDT04", HMass, 200, 0, 200);
                plotFill("HMass_TT_BDT04", HMass, 200, 0, 200);
            }

            //apply cut
            if (N_IsoTot > 0.8 && N_LT > 65) {
                plotFill("CutBasedA", N_MET, 200, 0, 200);
            }
            //
            //            if (l3Phi > l4Phi) {
            //
            //                float xpt3 = l3Pt;
            //                l3Pt = l4Pt;
            //                l4Pt = xpt3;
            //
            //                float xEta3 = l3Eta;
            //                l3Eta = l4Eta;
            //                l4Eta = xEta3;
            //
            //                float x_tauIsoL3 = l3_tauIsoL;
            //                l3_tauIsoL = l4_tauIsoL;
            //                l4_tauIsoL = x_tauIsoL3;
            //
            //                float x_tauIsoM3 = l3_tauIsoM;
            //                l3_tauIsoM = l4_tauIsoM;
            //                l4_tauIsoM = x_tauIsoM3;
            //
            //                float x_tauIsoT3 = l3_tauIsoT;
            //                l3_tauIsoT = l4_tauIsoT;
            //                l4_tauIsoT = x_tauIsoT3;
            //            }

            plotFill("l3TauIsoTele", l3_tauIsoT, 2, 0, 2);
            plotFill("l4TauIsoTele", l4_tauIsoT, 2, 0, 2);
            if (!l3tauIso && !l4tauIso && (Event != Event_Double[1][5])) {
                plotFill("FakeRate_EETT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][5] = Event;
            }
            if (!l3tauIso && l4tauIso && (Event != Event_Double[2][5])) {
                plotFill("FakeRate_EETT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][5] = Event;
            }
            if (l3tauIso && !l4tauIso && (Event != Event_Double[3][5])) {
                plotFill("FakeRate_EETT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][5] = Event;
            }
            if (l3tauIso && l4tauIso && (Event != Event_Double[0][5])) {
                plotFill("TMass_lepMet_tt", TMass_lepMet, pt_Bin, 0, pt_Bin);
                plotFill("FakeRate_EETT_apply_pp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[0][5] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (EEMT)
        //####################################################
        //        SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
        if (Channel == 16) plotFill("EEMT_FF_16", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 26) plotFill("EEMT_FP_26", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 36) plotFill("EEMT_PF_36", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (Channel == 96 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 45) && l4Pt > 20 && electron_Size == 2) {
        if (Channel == 96 && CheckHSign && l4Pt > Val_tauPt && electron_Size == 2 && l4_tauIsoMVA2raw > 0 && l3_muIso < Val_Iso) {


            //######################  MVA   ##################
            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_l3_LepId = l3_muId;
            N_l3_LepIso = l3_muIso;
            N_TMass = TMass_F(l3Pt, l3Px, l3Py, met, metPhi);
            MVATreeLT->Fill();
            //######################  MVA   ##################

            if (!l4_tauIsoM && (!l3_muId || !(l3_muIso < 0.15)) && (Event != Event_Double[1][6]) && (mu_Size - mu_partTight_Size == 0)) {
                plotFill("FakeRate_EEMT_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][6] = Event;
            }
            if (!l4_tauIsoM && (l3_muId && l3_muIso < 0.15) && (Event != Event_Double[2][6]) && mu_Size == 1) {
                plotFill("FakeRate_EEMT_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][6] = Event;
            }
            if (l4_tauIsoM && (!l3_muId || !(l3_muIso < 0.15)) && (Event != Event_Double[3][6]) && (mu_Size - mu_partTight_Size == 0)) {
                plotFill("FakeRate_EEMT_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][6] = Event;
            }
            if (l4_tauIsoM && (l3_muId && (l3_muIso < 0.15)) && (Event != Event_Double[0][6]) && (mu_Size == 1)) {
                plotFill("TMass_lepMet", TMass_lepMet, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }

            //extraCheck

            if (!l4_tauIsoM && (!l3_muId && !(l3_muIso < 0.15)) && (Event != Event_Double[0][6]) && (mu_Size - mu_partTight_Size == 0)) {
                plotFill("FakeRate_EEMT_apply_ff_failIdfailIso", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }
            if (!l4_tauIsoM && (l3_muId && !(l3_muIso < 0.15)) && (Event != Event_Double[0][6]) && (mu_Size - mu_partTight_Size == 0)) {
                plotFill("FakeRate_EEMT_apply_ff_passIdfailIso", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }
            if (!l4_tauIsoM && (!l3_muId && (l3_muIso < 0.15)) && (Event != Event_Double[0][6]) && (mu_Size - mu_partTight_Size == 0)) {
                plotFill("FakeRate_EEMT_apply_ff_failIdpassIso", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }

        }


        //####################################################
        //  Fake Rate Application (EEET)
        //####################################################
        if (Channel == 17) plotFill("EEET_FF_17", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 27) plotFill("EEET_FP_27", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 37) plotFill("EEET_PF_37", l3Pt, pt_Bin, 0, pt_Bin);
        //        if (Channel == 97 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 45) && l4Pt > 20 && mu_Size == 0) {
        if (Channel == 97 && CheckHSign && l4Pt > Val_tauPt && mu_Size == 0 && l4_tauIsoMVA2raw > 0 && l3_eleIso < Val_Iso) {

            //######################  MVA   ##################
            N_LT = l3Pt + l4Pt;
            N_MET = met;
            N_l4_tauIsoMVA2raw = l4_tauIsoMVA2raw;
            N_l3_LepId = l3_eleId;
            N_l3_LepIso = l3_eleIso;
            N_TMass = TMass_F(l3Pt, l3Px, l3Py, met, metPhi);
            MVATreeLT->Fill();
            //######################  MVA   ##################

            if (!l4_tauIsoM && (!l3_eleId || !(l3_eleIso < 0.1)) && (Event != Event_Double[1][7]) && (electron_Size - ele_partTight_Size == 2)) {
                plotFill("FakeRate_EEET_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][7] = Event;
            }
            if (!l4_tauIsoM && (l3_eleId && l3_eleIso < 0.1) && (Event != Event_Double[2][7]) && electron_Size == 3) {
                plotFill("FakeRate_EEET_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][7] = Event;
            }
            if (l4_tauIsoM && (!l3_eleId || !(l3_eleIso < 0.1)) && (Event != Event_Double[3][7]) && (electron_Size - ele_partTight_Size == 2)) {
                plotFill("FakeRate_EEET_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][7] = Event;
            }
            if (l4_tauIsoM && (l3_eleId && (l3_eleIso < 0.1)) && (Event != Event_Double[0][7]) && (electron_Size == 3)) {
                plotFill("TMass_lepMet", TMass_lepMet, pt_Bin, 0, pt_Bin);
                Event_Double[0][7] = Event;
            }

        }





        //####################################################
        //  Fake Rate Application (EEEM)
        //####################################################
        if (Channel == 18) plotFill("EEEM_FF_18", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 28) plotFill("EEEM_FP_28", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 38) plotFill("EEEM_PF_38", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 98 && CheckHSign && (l3Pt + l4Pt > 30) && NewOverLap(l1Eta, l1Phi, l2Eta, l2Phi, l3Eta, l3Phi, l4Eta, l4Phi)) {

            if ((!l3_eleId || !(l3_eleIso < 0.30)) && (!l4_muId || !(l4_muIso < 0.30)) && (Event != Event_Double[1][8]) && (mu_Size == 0) && (electron_Size == 2)) {
                plotFill("FakeRate_EEEM_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][8] = Event;
            }
            if ((!l3_eleId || !(l3_eleIso < 0.30)) && (l4_muId && l4_muIso < 0.30) && (Event != Event_Double[2][8]) && mu_Size == 1 && (electron_Size == 2)) {
                plotFill("FakeRate_EEEM_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][8] = Event;
            }
            if ((l3_eleId && (l3_eleIso < 0.30)) && (!l4_muId || !(l4_muIso < 0.30)) && (Event != Event_Double[3][8]) && electron_Size == 3 && (mu_Size == 0)) {
                plotFill("FakeRate_EEEM_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][8] = Event;
            }

        }
        //####################################################
        // Tau Fake Rate Measurement
        //####################################################
        bool FR_Estimation = true;

        if ((Channel == 91 || Channel == 95) && (l3Charge * l4Charge > 0) && Event != Ev_double) {

            Ev_double = Event;

            //Total FR
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l4Pt, pt_Bin, 0, pt_Bin);

            //Barrel Fake rate
            if (FR_Estimation && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l4Pt, pt_Bin, 0, pt_Bin);

            //EndCap Fake rate
            if (FR_Estimation && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3tauIso && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4tauIso && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l4Pt, pt_Bin, 0, pt_Bin);

        }

        //####################################################
        // Ele Mu  Fake Rate Measurements
        //####################################################
        float dMZ_Diff = 10;
        //It has been check 92&93&96&97 are the saem as 52&53&56&67
        //        if (Channel == 52 || Channel == 57) {
        //            plotFill("4objFR_Ele_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //        if (Channel == 53 || Channel == 56) {
        //            plotFill("4objFR_Mu_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //        if (((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10) {
        //            plotFill("4objFR_Ele_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }
        //
        //        if (((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10) {
        //            plotFill("4objFR_Mu_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        //            if (l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        //        }

        //##################################################
        //0 GeV Tau
        bool eleFR_denum_0 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 0;
        if (eleFR_denum_0) plotFill("4objFR_Ele_Denum_0", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_0 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_0 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin);

        bool muFR_denum_0 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 0;
        if (muFR_denum_0) plotFill("4objFR_Mu_Denum_0", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_0 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_0 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin);


        //##################################################
        //5 GeV Tau
        bool eleFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        if (eleFR_denum_5) plotFill("4objFR_Ele_Denum_5", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin);

        bool muFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        if (muFR_denum_5) plotFill("4objFR_Mu_Denum_5", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_5 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_5 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin);

        //##################################################
        //10 GeV Tau
        bool eleFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        if (eleFR_denum_10) plotFill("4objFR_Ele_Denum_10", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin);
        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin);

        bool muFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        if (muFR_denum_10) plotFill("4objFR_Mu_Denum_10", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_10 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin);
        if (muFR_denum_10 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin);



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
        //        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi));
        bool Mu_denum = (Channel == 101 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);
        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);

        if (Mu_denum) {
            plotFill("3objFR_Mu_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Mu_denum && l3_muId && l3_muIso < tightMu) {
            plotFill("3objFR_Mu_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Mu_denum && l3_muId && l3_muIso < looseMu) {
            plotFill("3objFR_Mu_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Ele_denum) {
            plotFill("3objFR_Ele_Denum", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Ele_denum && l3_eleId && l3_eleIso < tightEle) {
            plotFill("3objFR_Ele_NumTight", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Ele_denum && l3_eleId && l3_eleIso < looseEle) {
            plotFill("3objFR_Ele_NumLoose", l3Pt, pt_Bin, 0, pt_Bin);
        }

        //####################################################
        if (Mu_denum && l3_muId) {
            plotFill("3objFR_Mu_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Mu_denum && l3_muIso < looseMu) {
            plotFill("3objFR_Mu_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Ele_denum && l3_eleId) {
            plotFill("3objFR_Ele_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin);
        }
        if (Ele_denum && l3_eleIso < looseEle) {
            plotFill("3objFR_Ele_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin);
        }







    }


    fout->cd();
    MVATree->Write();
    MVATreeLT->Write();
    //    MVATreeLT->Write();

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

