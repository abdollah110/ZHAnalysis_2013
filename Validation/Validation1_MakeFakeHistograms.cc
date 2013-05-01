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
    TFile *f_Double = new TFile(input.c_str(), "UPDATE");
    TTree *Run_Tree = (TTree*) f_Double->Get("RLE_tree");

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(1);
    int pt_Bin = 200;

    int Channel = 0;
    int Run = 0;
    int Lumi = 0;
    int Event = 1000;
    float IMass = 0;
    float ZMass = 0;
    float HMass = 0;
    float met, metPhi;
    float l1M, l1Px, l1Py, l1Pz, l1E, l1Pt, l1Phi, l1Eta, l1_muId, l1_muIso, l1_eleId, l1_eleIso, l1_eleMVANonTrg, l1_eleNumHit;
    float l2M, l2Px, l2Py, l2Pz, l2E, l2Pt, l2Phi, l2Eta, l2_muId, l2_muIso, l2_eleId, l2_eleIso, l2_eleMVANonTrg, l2_eleNumHit;
    float l3M, l3Px, l3Py, l3Pz, l3E, l3Pt, l3Phi, l3Eta, l3_muId, l3_muIso, l3_eleId, l3_eleIso, l3_eleMVANonTrg, l3_eleNumHit, l3_tauIsoL, l3_tauIsoM, l3_tauIsoT, l3_tauRejMuL, l3_tauRejMuM, l3_tauRejMuT, l3_tauRejEleL, l3_tauRejEleM, l3_tauRejEleMVA;
    float l4M, l4Px, l4Py, l4Pz, l4E, l4Pt, l4Phi, l4Eta, l4_muId, l4_muIso, l4_eleId, l4_eleIso, l4_eleMVANonTrg, l4_eleNumHit, l4_tauIsoL, l4_tauIsoM, l4_tauIsoT, l4_tauRejMuL, l4_tauRejMuM, l4_tauRejMuT, l4_tauRejEleL, l4_tauRejEleM, l4_tauRejEleMVA;
    float covMet11;
    float covMet12;
    float covMet21;
    float covMet22;
    float eff_Correction, pu_Weight;
    int num_PV, num_bjet;
    float l3Charge, l4Charge;
    int mu_Size, BareMuon_Size, electron_Size, BareElectron_Size, tau_Size, BareTau_Size;
    int mu_partTight_Size, mu_partLoose_Size, ele_partTight_Size, ele_partLoose_Size;

    Run_Tree->SetBranchAddress("Channel", &Channel);
    Run_Tree->SetBranchAddress("Run", &Run);
    Run_Tree->SetBranchAddress("Lumi", &Lumi);
    Run_Tree->SetBranchAddress("Event", &Event);
    Run_Tree->SetBranchAddress("IMass", &IMass);
    Run_Tree->SetBranchAddress("ZMass", &ZMass);
    Run_Tree->SetBranchAddress("HMass", &HMass);
    Run_Tree->SetBranchAddress("met", &met);
    Run_Tree->SetBranchAddress("num_PV", &num_PV);
    Run_Tree->SetBranchAddress("metPhi", &metPhi);

    Run_Tree->SetBranchAddress("l1Eta", &l1Eta);
    Run_Tree->SetBranchAddress("l1Phi", &l1Phi);
    Run_Tree->SetBranchAddress("l2Eta", &l2Eta);
    Run_Tree->SetBranchAddress("l2Phi", &l2Phi);

    Run_Tree->SetBranchAddress("BareElectron_Size", &BareElectron_Size);
    Run_Tree->SetBranchAddress("BareMuon_Size", &BareMuon_Size);
    Run_Tree->SetBranchAddress("electron_Size", &electron_Size);
    Run_Tree->SetBranchAddress("mu_Size", &mu_Size);
    Run_Tree->SetBranchAddress("mu_partTight_Size", &mu_partTight_Size);
    Run_Tree->SetBranchAddress("ele_partTight_Size", &ele_partTight_Size);


    Run_Tree->SetBranchAddress("l3Pt", &l3Pt);
    Run_Tree->SetBranchAddress("l3Px", &l3Px);
    Run_Tree->SetBranchAddress("l3Py", &l3Py);
    Run_Tree->SetBranchAddress("l3Eta", &l3Eta);
    Run_Tree->SetBranchAddress("l3Phi", &l3Phi);
    Run_Tree->SetBranchAddress("l3_tauIsoL", &l3_tauIsoL);
    Run_Tree->SetBranchAddress("l3_tauIsoM", &l3_tauIsoM);
    Run_Tree->SetBranchAddress("l3_tauIsoT", &l3_tauIsoT);
    Run_Tree->SetBranchAddress("l3_tauRejMuL", &l3_tauRejMuL);
    Run_Tree->SetBranchAddress("l3_tauRejMuM", &l3_tauRejMuM);
    Run_Tree->SetBranchAddress("l3_tauRejMuT", &l3_tauRejMuT);
    Run_Tree->SetBranchAddress("l3_tauRejEleL", &l3_tauRejEleL);
    Run_Tree->SetBranchAddress("l3_tauRejEleM", &l3_tauRejEleM);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA", &l3_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA", &l3_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l3_eleIso", &l3_eleIso);
    Run_Tree->SetBranchAddress("l3_eleId", &l3_eleId);
    Run_Tree->SetBranchAddress("l3_muIso", &l3_muIso);
    Run_Tree->SetBranchAddress("l3_muId", &l3_muId);
    Run_Tree->SetBranchAddress("l3Charge", &l3Charge);

    Run_Tree->SetBranchAddress("l4Pt", &l4Pt);
    Run_Tree->SetBranchAddress("l4Px", &l4Py);
    Run_Tree->SetBranchAddress("l4Px", &l4Py);
    Run_Tree->SetBranchAddress("l4Eta", &l4Eta);
    Run_Tree->SetBranchAddress("l4Phi", &l4Phi);
    Run_Tree->SetBranchAddress("l4_tauIsoL", &l4_tauIsoL);
    Run_Tree->SetBranchAddress("l4_tauIsoM", &l4_tauIsoM);
    Run_Tree->SetBranchAddress("l4_tauIsoT", &l4_tauIsoT);
    Run_Tree->SetBranchAddress("l4_tauRejMuL", &l4_tauRejMuL);
    Run_Tree->SetBranchAddress("l4_tauRejMuM", &l4_tauRejMuM);
    Run_Tree->SetBranchAddress("l4_tauRejMuT", &l4_tauRejMuT);
    Run_Tree->SetBranchAddress("l4_tauRejEleL", &l4_tauRejEleL);
    Run_Tree->SetBranchAddress("l4_tauRejEleM", &l4_tauRejEleM);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA", &l4_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l4_eleIso", &l4_eleIso);
    Run_Tree->SetBranchAddress("l4_eleId", &l4_eleId);
    Run_Tree->SetBranchAddress("l4_muIso", &l4_muIso);
    Run_Tree->SetBranchAddress("l4_muId", &l4_muId);
    Run_Tree->SetBranchAddress("l4Charge", &l4Charge);


    int Event_Double[5][9];
    memset(Event_Double, 0, sizeof (Event_Double[0][0]) * 5 * 9);
    float Ev_doubleff = 0;
    float Ev_doublefp = 0;
    float Ev_doublepf = 0;
    float Ev_double = 0;

    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        //###############################################################################################
        //values
        float tauPtCut = 15;
        bool charge_Type = ((l3Charge * l4Charge < 0) ? true : false);
        //###############################################################################################
        float looseEle = 0.3;
        float looseMu = 0.3;
        float tightEle = 0.10;
        float tightMu = 0.15;
        float tauPt = 10;
        float value_Eta = 1.4;
        float VisibleMass = InvarMass_F(l3Pt, l4Pt, l3Px, l4Px, l3Py, l4Py, l3Pz, l4Pz);
        float TMass_l_Met = TMass_F(l3Pt, l4Px, l3Py, met, metPhi);



        //        cout<< "         after Randomizaton= "<<  l3E<<"  " <<l4E<<"  " <<l3Px<<"  " <<l4Px<<"  " <<l3Py<<"  " <<l4Py<<"  "<< l3Pz<<"  " <<l4Pz<<"  "<<"\n";
        //####################################################
        // MMTT FakeRateation
        //####################################################

        if ((Channel == 91) && charge_Type && l3Pt > tauPtCut && l4Pt > tauPtCut) {

            if (l3Phi > l4Phi) {

                float xpt3 = l3Pt;
                l3Pt = l4Pt;
                l4Pt = xpt3;

                float xEta3 = l3Eta;
                l3Eta = l4Eta;
                l4Eta = xEta3;

                float x_tauIsoL3 = l3_tauIsoL;
                l3_tauIsoL = l4_tauIsoL;
                l4_tauIsoL = x_tauIsoL3;

                float x_tauIsoM3 = l3_tauIsoM;
                l3_tauIsoM = l4_tauIsoM;
                l4_tauIsoM = x_tauIsoM3;

                float x_tauIsoT3 = l3_tauIsoT;
                l3_tauIsoT = l4_tauIsoT;
                l4_tauIsoT = x_tauIsoT3;
            }


            if (l3_tauIsoL && l4_tauIsoL && (Event != Event_Double[0][1])) {
                plotFill("VisibleMass_MMTT_tt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][1] = Event;
            }
            if (!l3_tauIsoL  && !l4_tauIsoL  && (Event != Event_Double[1][1])) {
                plotFill("FakeRate_MMTT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][1] = Event;
                //eta dependency
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (!l3_tauIsoL  && l4_tauIsoL  && (Event != Event_Double[2][1])) {
                plotFill("FakeRate_MMTT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][1] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL  && !l4_tauIsoL  && (Event != Event_Double[3][1])) {
                plotFill("FakeRate_MMTT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][1] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
            }

        }


        //####################################################
        //  Fake Rate Application (MMET)
        //####################################################

        if (Channel == 92 && (l3Charge * l4Charge > 0) && l4Pt > tauPt && mu_Size == 2) {



            if (l4_tauIsoL && (l3_eleId && (l3_eleIso < looseEle)) && (Event != Event_Double[0][2])) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ele_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ele_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[0][2] = Event;
            }
            if (!l4_tauIsoL && (!l3_eleId || !(l3_eleIso < looseEle)) && (Event != Event_Double[1][2])) {

                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_ff_B", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_ff_E", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][2] = Event;
            }
            if (!l4_tauIsoL && (l3_eleId && l3_eleIso < looseEle) && (Event != Event_Double[2][2])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_fp_B", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_fp_E", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][2] = Event;
            }
            if (l4_tauIsoL && (!l3_eleId || !(l3_eleIso < looseEle)) && (Event != Event_Double[3][2])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMET_apply_pf_B", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMET_apply_pf_E", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][2] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (MMMT)
        //####################################################

        if (Channel == 93 && (l3Charge * l4Charge > 0) && l4Pt > tauPt && electron_Size == 0) {

            if (l4_tauIsoL && (l3_muId && (l3_muIso < looseMu)) && (Event != Event_Double[0][3])) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_mu_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_mu_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[0][3] = Event;
            }
            if (!l4_tauIsoL && (!l3_muId || !(l3_muIso < looseMu)) && (Event != Event_Double[1][3])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_ff_B", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_ff_E", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][3] = Event;
            }
            if (!l4_tauIsoL && (l3_muId && l3_muIso < looseMu) && (Event != Event_Double[2][3])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_fp_B", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_fp_E", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][3] = Event;
            }
            if (l4_tauIsoL && (!l3_muId || !(l3_muIso < looseMu)) && (Event != Event_Double[3][3])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMMT_apply_pf_B", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMMT_apply_pf_E", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][3] = Event;
            }

        }

        //####################################################
        // EETT FakeRateation
        //####################################################

        if ((Channel == 95) && charge_Type && l3Pt > tauPtCut && l4Pt > tauPtCut) {

            if (l3Phi > l4Phi) {

                float xpt3 = l3Pt;
                l3Pt = l4Pt;
                l4Pt = xpt3;

                float xEta3 = l3Eta;
                l3Eta = l4Eta;
                l4Eta = xEta3;

                float x_tauIsoL3 = l3_tauIsoL;
                l3_tauIsoL = l4_tauIsoL;
                l4_tauIsoL = x_tauIsoL3;

                float x_tauIsoM3 = l3_tauIsoM;
                l3_tauIsoM = l4_tauIsoM;
                l4_tauIsoM = x_tauIsoM3;

                float x_tauIsoT3 = l3_tauIsoT;
                l3_tauIsoT = l4_tauIsoT;
                l4_tauIsoT = x_tauIsoT3;
            }


            if (l3_tauIsoL && l4_tauIsoL && (Event != Event_Double[0][5])) {
                plotFill("VisibleMass_EETT_tt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][5] = Event;
            }
            if (!l3_tauIsoL  && !l4_tauIsoL  && (Event != Event_Double[1][5])) {
                plotFill("FakeRate_EETT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][5] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (!l3_tauIsoL  && l4_tauIsoL  && (Event != Event_Double[2][5])) {
                plotFill("FakeRate_EETT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][5] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL && !l4_tauIsoL  && (Event != Event_Double[3][5])) {
                plotFill("FakeRate_EETT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_tt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][5] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
            }

        }
        //####################################################
        //  Fake Rate Application (EEMT)
        //####################################################

        if (Channel == 96 && (l3Charge * l4Charge > 0) && l4Pt > tauPt && electron_Size == 2) {

            if (l4_tauIsoL && (l3_muId && l3_muIso < looseMu) && (Event != Event_Double[0][6])) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_mu_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_mu_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[0][6] = Event;
            }
            if (!l4_tauIsoL && (!l3_muId || !(l3_muIso < looseMu)) && (Event != Event_Double[1][6])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_ff_B", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_ff_E", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][6] = Event;
            }
            if (!l4_tauIsoL && (l3_muId && l3_muIso < looseMu) && (Event != Event_Double[2][6])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_fp_B", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_fp_E", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][6] = Event;
            }
            if (l4_tauIsoL && (!l3_muId || !(l3_muIso < looseMu)) && (Event != Event_Double[3][6])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEMT_apply_pf_B", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEMT_apply_pf_E", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][6] = Event;
            }
        }
        //####################################################
        //  Fake Rate Application (EEET)
        //####################################################

        if (Channel == 97 && (l3Charge * l4Charge > 0) && l4Pt > tauPt && mu_Size == 0) {

            if (l4_tauIsoL && (l3_eleId && (l3_eleIso < looseEle)) && (Event != Event_Double[0][7])) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ele_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ele_pp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[0][7] = Event;
            }
            if (!l4_tauIsoL && (!l3_eleId || !(l3_eleIso < looseEle)) && (Event != Event_Double[1][7])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_ff_B", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_ff_E", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_ff", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[1][7] = Event;
            }
            if (!l4_tauIsoL && (l3_eleId && l3_eleIso < looseEle) && (Event != Event_Double[2][7])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_fp_B", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_fp_E", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_fp", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[2][7] = Event;
            }
            if (l4_tauIsoL && (!l3_eleId || !(l3_eleIso < looseEle)) && (Event != Event_Double[3][7])) {
                if (TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EEET_apply_pf_B", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EEET_apply_pf_E", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_lt_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                plotFill("TMass_l_Met_pf", TMass_l_Met, pt_Bin, 0, pt_Bin);
                Event_Double[3][7] = Event;
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
        //  Fake Rate Application (MMME)
        //####################################################

        if (Channel == 94 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 30) && NewOverLap(l1Eta, l1Phi, l2Eta, l2Phi, l3Eta, l3Phi, l4Eta, l4Phi)) {

            if ((!l4_eleId || !(l4_eleIso < 0.30)) && (!l3_muId || !(l3_muIso < 0.30)) && (Event != Event_Double[1][4]) && ((mu_Size - mu_partLoose_Size == 2)) && ((electron_Size - ele_partLoose_Size == 0))) {
                plotFill("FakeRate_MMME_apply_ff", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][4] = Event;
            }
            if ((!l4_eleId || !(l4_eleIso < 0.30)) && (l3_muId && l3_muIso < 0.30) && (Event != Event_Double[2][4]) && mu_Size == 3 && ((electron_Size - ele_partLoose_Size == 0))) {
                plotFill("FakeRate_MMME_apply_fp", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][4] = Event;
            }
            if ((l4_eleId && (l4_eleIso < 0.30)) && (!l3_muId || !(l3_muIso < 0.30)) && (Event != Event_Double[3][4]) && electron_Size == 1 && ((mu_Size - mu_partLoose_Size == 2))) {
                plotFill("FakeRate_MMME_apply_pf", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][4] = Event;
            }

        }
        //####################################################
        //  Fake Rate Application (EEEM)
        //####################################################

        if (Channel == 98 && (l3Charge * l4Charge < 0) && (l3Pt + l4Pt > 30) && NewOverLap(l1Eta, l1Phi, l2Eta, l2Phi, l3Eta, l3Phi, l4Eta, l4Phi)) {

            //            if ((!l3_eleId || !(l3_eleIso < 0.30)) && (!l4_muId || !(l4_muIso < 0.30)) && (Event != Event_Double[1][8]) && (mu_Size == 0 || (mu_Size - mu_partLoose_Size == 0)) && (electron_Size == 2 || (electron_Size - ele_partLoose_Size == 2))) {
            if ((!l3_eleId || !(l3_eleIso < 0.30)) && (!l4_muId || !(l4_muIso < 0.30)) && (Event != Event_Double[1][8]) && ((mu_Size - mu_partLoose_Size == 0)) && ((electron_Size - ele_partLoose_Size == 2))) {
                plotFill("FakeRate_EEEM_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                Event_Double[1][8] = Event;
            }
            if ((!l3_eleId || !(l3_eleIso < 0.30)) && (l4_muId && l4_muIso < 0.30) && (Event != Event_Double[2][8]) && mu_Size == 1 && ((electron_Size - ele_partLoose_Size == 2))) {
                plotFill("FakeRate_EEEM_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                Event_Double[2][8] = Event;
            }
            if ((l3_eleId && (l3_eleIso < 0.30)) && (!l4_muId || !(l4_muIso < 0.30)) && (Event != Event_Double[3][8]) && electron_Size == 3 && ((mu_Size - mu_partLoose_Size == 0))) {
                plotFill("FakeRate_EEEM_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                Event_Double[3][8] = Event;
            }

        }

        if (Channel == 12) plotFill("MMET_FF_12", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 22) plotFill("MMET_FP_22", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 32) plotFill("MMET_PF_32", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 13) plotFill("MMMT_FF_13", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 23) plotFill("MMMT_FP_23", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 33) plotFill("MMMT_PF_33", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 14) plotFill("MMME_FF_14", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 24) plotFill("MMME_FP_24", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 34) plotFill("MMME_PF_34", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 16) plotFill("EEMT_FF_16", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 26) plotFill("EEMT_FP_26", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 36) plotFill("EEMT_PF_36", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 17) plotFill("EEET_FF_17", l4Pt, l3Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 27) plotFill("EEET_FP_27", l4Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 37) plotFill("EEET_PF_37", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 18) plotFill("EEEM_FF_18", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
        if (Channel == 28) plotFill("EEEM_FP_28", l3Pt, pt_Bin, 0, pt_Bin);
        if (Channel == 38) plotFill("EEEM_PF_38", l4Pt, pt_Bin, 0, pt_Bin);




        //####################################################
        // Tau Fake Rate Measurement
        //####################################################
        bool FR_Estimation = true;

        if ((Channel == 91 || Channel == 95) && (l3Charge * l4Charge > 0) && Event != Ev_double) {

            Ev_double = Event;

            //Total FR
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoL) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoL) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l4Pt, pt_Bin, 0, pt_Bin);

            //Barrel Fake rate
            if (FR_Estimation && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoL && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoL && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoM && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoM && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoT && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoT && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l4Pt, pt_Bin, 0, pt_Bin);

            //EndCap Fake rate
            if (FR_Estimation && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoL && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoL && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoM && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoM && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l4Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l3_tauIsoT && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l3Pt, pt_Bin, 0, pt_Bin);
            if (FR_Estimation && l4_tauIsoT && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l4Pt, pt_Bin, 0, pt_Bin);

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
