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
#include "myHelper.h"

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
    Run_Tree->SetBranchAddress("l3Pz", &l3Pz);
    Run_Tree->SetBranchAddress("l3Eta", &l3Eta);
    Run_Tree->SetBranchAddress("l3E", &l3E);
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
    Run_Tree->SetBranchAddress("l4Px", &l4Px);
    Run_Tree->SetBranchAddress("l4Py", &l4Py);
    Run_Tree->SetBranchAddress("l4Pz", &l4Pz);
    Run_Tree->SetBranchAddress("l4Eta", &l4Eta);
    Run_Tree->SetBranchAddress("l4E", &l4E);
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


    //values
    float tauPtCut = 15;
    int pt_Bin = 300;
    float value_Eta = 1.4;
    int Event_Double[4][9];
    memset(Event_Double, 0, sizeof (Event_Double[0][0]) * 3 * 8);
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    int y = 0;


    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);



        //        cout<< "before Randomizaton= "<<  InvarMass_F(l3Pt, l4Pt, l3Px, l4Px, l3Py, l4Py, l3Pz, l4Pz)<<"\t";
        //select l3 and l4 randomly
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
        //        cout<< "         after Randomizaton= "<<  l3E<<"  " <<l4E<<"  " <<l3Px<<"  " <<l4Px<<"  " <<l3Py<<"  " <<l4Py<<"  "<< l3Pz<<"  " <<l4Pz<<"  "<<"\n";
        //####################################################
        // MMTT FakeRateation
        //####################################################

        float VisibleMass = InvarMass_F(l3E, l4E, l3Px, l4Px, l3Py, l4Py, l3Pz, l4Pz);
        if ((Channel == 91) && (l3Charge * l4Charge > 0) && l3Pt > tauPtCut && l4Pt > tauPtCut) {

            if (l3_tauIsoL && l4_tauIsoL && (Event != Event_Double[0][0])) {
                plotFill("VisibleMass_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][0] = Event;
            }
            if (l3_tauIsoL < 0.5 && l4_tauIsoL < 0.5 && (Event != Event_Double[1][0])) {
                plotFill("FakeRate_MMTT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][0] = Event;
                //eta dependency
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL < 0.5 && l4_tauIsoL > 0.5 && (Event != Event_Double[2][0])) {
                plotFill("FakeRate_MMTT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][0] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL > 0.5 && l4_tauIsoL < 0.5 && (Event != Event_Double[3][0])) {
                plotFill("FakeRate_MMTT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][0] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_MMTT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_MMTT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
            }

        }
        //####################################################
        // EETT FakeRateation
        //####################################################

        if ((Channel == 95) && (l3Charge * l4Charge > 0) && l3Pt > tauPtCut && l4Pt > tauPtCut) {

            if (l3_tauIsoL && l4_tauIsoL && (Event != Event_Double[0][1])) {
                plotFill("VisibleMass_pp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[0][1] = Event;
            }
            if (l3_tauIsoL < 0.5 && l4_tauIsoL < 0.5 && (Event != Event_Double[1][1])) {
                plotFill("FakeRate_EETT_apply_ff", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_ff", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[1][1] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_BB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_BE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_ff_EB", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_ff_EE", l3Pt, l4Pt, pt_Bin, 0, pt_Bin, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL < 0.5 && l4_tauIsoL > 0.5 && (Event != Event_Double[2][1])) {
                plotFill("FakeRate_EETT_apply_fp", l3Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_fp", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[2][1] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_BB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_BE", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_fp_EB", l3Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_fp_EE", l3Pt, pt_Bin, 0, pt_Bin);
            }
            if (l3_tauIsoL > 0.5 && l4_tauIsoL < 0.5 && (Event != Event_Double[3][0])) {
                plotFill("FakeRate_EETT_apply_pf", l4Pt, pt_Bin, 0, pt_Bin);
                plotFill("VisibleMass_pf", VisibleMass, pt_Bin, 0, pt_Bin);
                Event_Double[3][0] = Event;
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_BB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) < value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_BE", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) < value_Eta) plotFill("FakeRate_EETT_apply_pf_EB", l4Pt, pt_Bin, 0, pt_Bin);
                if (TMath::Abs(l3Eta) > value_Eta && TMath::Abs(l4Eta) > value_Eta) plotFill("FakeRate_EETT_apply_pf_EE", l4Pt, pt_Bin, 0, pt_Bin);
            }

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

