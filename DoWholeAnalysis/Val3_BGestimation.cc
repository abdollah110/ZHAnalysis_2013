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

//#include "tr_Tree.h"

void PrintResults(TH2F* Chnl_estimate, TH2F* Chnl_event, std::string name) {
    TFile * MegaFile = new TFile("valid_Mega.root");
    TH1D * arrayPP[8];
    char * array[8] = {"mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"};
    char *arrayMass[8] = {"SVMass_mmtt_pp", "SVMass_mmet_pp", "SVMass_mmmt_pp", "SVMass_mmme_pp", "SVMass_eett_pp", "SVMass_eemt_pp", "SVMass_eeet_pp", "SVMass_eeem_pp"};
    for (int q = 0; q < 8; q++) {
        arrayPP[q] = (TH1D*) MegaFile->Get(arrayMass[q]);
    }

    TFile * OutFile = new TFile(name.c_str(), "RECREATE");
    OutFile->cd();
    TH1F * histo_Reducible = new TH1F("histo_Reducible", "histo_Reducible", 10, 0, 10);
    TH1F * histo_ReducibleEr = new TH1F("histo_ReducibleEr", "histo_ReducibleEr", 10, 0, 10);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    cout << "\n\n" << "\\begin{table}[htbp]" << endl;
    cout << "\\centering" << endl;
    cout << "\\caption{ events}" << endl;
    cout << "\\label{table:events}" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c| }" << endl;
//    cout << "\\begin{tabular}{|c|c|c|c|c|c| }" << endl;
    cout << "\\hline" << endl;
    cout << " channel & Cat0 & Cat1 & Cat2 &  1+2-0 " << " \\\\" << endl;
//    cout << " channel & Cat0 & Cat1 & Cat2 &  1+2-0 & Selected" << " \\\\" << endl;
    cout << "\\hline" << endl;


    float Total_Est = 0;
    float Total_Obs = 0;
    for (int j = 1; j <= 8; j++) {
        cout << array[j - 1] << "&";

        float Est_cat0 = Chnl_estimate->GetBinContent(2, j + 1);
        float Est_cat1 = Chnl_estimate->GetBinContent(3, j + 1);
        float Est_cat2 = Chnl_estimate->GetBinContent(4, j + 1);

        int Num_cat0 = Chnl_event->GetBinContent(2, j + 1);
        int Num_cat1 = Chnl_event->GetBinContent(3, j + 1);
        int Num_cat2 = Chnl_event->GetBinContent(4, j + 1);

        float Er_cat0 = 1. / sqrt(Num_cat0) * Est_cat0;
        float Er_cat1 = 1. / sqrt(Num_cat1) * Est_cat1;
        float Er_cat2 = 1. / sqrt(Num_cat2) * Est_cat2;

        float cen_val = Est_cat1 + Est_cat2 - Est_cat0;
        float cen_Er = Er_cat0 + Er_cat1 + Er_cat2;

        cout << Est_cat0 << "(" << Num_cat0 << ")" << "&";
        cout << Est_cat1 << "(" << Num_cat1 << ")" << "&";
        cout << Est_cat2 << "(" << Num_cat2 << ")" << "&";
        cout << cen_val << "$\\pm$" << cen_Er ;

        float obs = 0;
        //        if (arrayPP[j - 1]) obs = arrayPP[j - 1]->Integral();
        cout <<  " \\\\ " << endl;
//        cout << "&"<<int(obs) << " \\\\ " << endl;
        Total_Est += cen_val;
        Total_Obs += obs;
        histo_Reducible->SetBinContent(j, cen_val);
        histo_ReducibleEr->SetBinContent(j, cen_Er);
    }
    cout << "\\hline" << "\n\\end{tabular}" << "\n\\end{table}" << "\n\n\n";
    cout << "Total Reducible BG =  " << Total_Est << endl;
    //    cout << "Total Reducible BG =  " << Total_Est << "    with:    "<< Total_Obs<<endl;

    OutFile->Write();
    OutFile->Close();
}

std::vector<float> * Get_FitParameter(std::string firstLeg) {
    //ToGet Fake Rate values
    TFile *fr_file = new TFile("FitValues_FR.root");
    TH2F * Fit_Value_tau = (TH2F*) fr_file->Get("Fit_Value_tau");
    TH2F * Fit_Value_emu = (TH2F*) fr_file->Get("Fit_Value_emu");

    std::vector<float> * leg1 = new std::vector<float>(3);
    leg1->clear();

    //first leg
    if (firstLeg == "tauTight")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(3, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(2, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(1, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(13, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(12, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(11, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_RefJet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(23, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_RefJet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(22, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_RefJet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(21, 2 * (i - 1) + 1));
    //ele Mu
    if (firstLeg == "eleLoose")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(1, 2 * (i - 1) + 1));
    if (firstLeg == "eleLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(5, 2 * (i - 1) + 1));
    if (firstLeg == "muLoose")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(3, 2 * (i - 1) + 1));
    if (firstLeg == "muLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(7, 2 * (i - 1) + 1));
    if (firstLeg == "eleTight")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(2, 2 * (i - 1) + 1));
    if (firstLeg == "eleTight_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(6, 2 * (i - 1) + 1));
    if (firstLeg == "muTight")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(4, 2 * (i - 1) + 1));
    if (firstLeg == "muTight_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(8, 2 * (i - 1) + 1));

    //ele Mu 3 Object
    if (firstLeg == "3obj_eleLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(9, 2 * (i - 1) + 1));
    if (firstLeg == "3obj_muLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(11, 2 * (i - 1) + 1));
    if (firstLeg == "3obj_eleTight_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(10, 2 * (i - 1) + 1));
    if (firstLeg == "3obj_muTight_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_emu->GetBinContent(12, 2 * (i - 1) + 1));

    //apply the Eta dependecy
    if (firstLeg == "tauLoose_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(4, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(5, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(6, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(7, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(8, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(9, 2 * (i - 1) + 1));

    //apply the Eta dependecy for Ltau CloseJet
    if (firstLeg == "tauLoose_ltau_Jet")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(31, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_ltau_Jet_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(34, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_ltau_Jet_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(37, 2 * (i - 1) + 1));

    //apply the Eta dependecy CloseJet
    if (firstLeg == "tauLoose_Jet_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(14, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_Jet_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(17, 2 * (i - 1) + 1));

    //apply the Eta dependecy RefJet
    if (firstLeg == "RefJetLoose_B")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(24, 2 * (i - 1) + 1));
    if (firstLeg == "RefJetLoose_E")
        for (int i = 1; i <= 3; i++) leg1->push_back(Fit_Value_tau->GetBinContent(27, 2 * (i - 1) + 1));
    //    cout<<(*leg1)[0]<<endl;
    return leg1;

}

Double_t fitFunction(float x, bool isPtDependent, std::vector<float> * FitPar) {


    if (isPtDependent) {
        float fValue = ((*FitPar)[0] + (*FitPar)[1] * (TMath::Exp((*FitPar)[2] * x)))*1.0;
        if (fValue > 0.95 && fValue < 1.0) fValue = 0.975;
        if (fValue > 1.0 && fValue < 1.05) fValue = 1.025;
        return fValue;
    } else {
        float fValue = (*FitPar)[0] + (*FitPar)[1] * x;
        if (fValue > 0.95 && fValue < 1.0) fValue = 0.975;
        if (fValue > 1.0 && fValue < 1.05) fValue = 1.025;
        return fValue;
    }
}

Double_t fitFunction(Double_t x, bool isPtDependent, Double_t par0, Double_t par1, Double_t par2) {
    if (isPtDependent)
        return (par0 + par1 * (TMath::Exp(par2 * x)));
    else
        return par0 + par1 * x;
}

void Estim_BG(int trChannel, std::string etaType, std::string frType1, std::string kindFR1, int fitType1, std::string frType2, std::string kindFR2, int fitType2, TH2F * Chnl_estimate, TH2F* Chnl_event) {



    std::vector<float> * FitPar1 = new std::vector<float>(3);
    FitPar1->clear();
    FitPar1 = (Get_FitParameter(frType1));
    std::vector<float> * FitPar2 = new std::vector<float>(3);
    FitPar2->clear();
    FitPar2 = (Get_FitParameter(frType2));

    //#######################################################
    TFile * MegaFile = new TFile("valid_Mega.root");
    TTree * BG_Tree_ = (TTree*) MegaFile->Get("BG_Tree");
    float _l3pt, l3Eta_;
    float _l4pt, l4Eta_;
    int myChannel;
    int mysubChannel;
    BG_Tree_->SetBranchAddress(kindFR1.c_str(), &_l3pt);
    BG_Tree_->SetBranchAddress(kindFR2.c_str(), &_l4pt);
    BG_Tree_->SetBranchAddress("Channel_", &myChannel);
    BG_Tree_->SetBranchAddress("subChannel_", &mysubChannel);
    BG_Tree_->SetBranchAddress("l3Eta_", &l3Eta_);
    BG_Tree_->SetBranchAddress("l4Eta_", &l4Eta_);
    //#######################################################



    Int_t nentries_wtn = (Int_t) BG_Tree_->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        BG_Tree_->GetEntry(i);
        if (i % 50000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        bool check_eta = false;
        if (etaType.compare("BB") == 0) check_eta = ((TMath::Abs(l3Eta_) < 1.4 && TMath::Abs(l4Eta_) < 1.4) ? true : false);
        if (etaType.compare("BE") == 0) check_eta = ((TMath::Abs(l3Eta_) < 1.4 && TMath::Abs(l4Eta_) > 1.4) ? true : false);
        if (etaType.compare("EB") == 0) check_eta = ((TMath::Abs(l3Eta_) > 1.4 && TMath::Abs(l4Eta_) < 1.4) ? true : false);
        if (etaType.compare("EE") == 0) check_eta = ((TMath::Abs(l3Eta_) > 1.4 && TMath::Abs(l4Eta_) > 1.4) ? true : false);
        if (etaType.compare("B") == 0) check_eta = ((TMath::Abs(l4Eta_) < 1.4) ? true : false);
        if (etaType.compare("E") == 0) check_eta = ((TMath::Abs(l4Eta_) > 1.4) ? true : false);
        if (etaType.compare("NoEta") == 0) check_eta = true;

        //#######################################################
        if (myChannel == trChannel && check_eta) {
            //        Do Category 0
            if (mysubChannel == 0) {
                double FrateX = fitFunction(_l3pt, fitType1, FitPar1);
                double FrateY = fitFunction(_l4pt, fitType2, FitPar2);
                double Frate = ((FrateX * FrateY) / ((1 - FrateX) * (1 - FrateY)));
                Chnl_estimate->Fill(1, myChannel, Frate);
                Chnl_event->Fill(1, myChannel, 1);
            }
            //        Do Category 1
            if (mysubChannel == 1) {
                double FrateX = .1;
                double FrateX = fitFunction(_l4pt, fitType2, FitPar2);
                double Frate = (FrateX) / (1 - FrateX);
                Chnl_estimate->Fill(2, myChannel, Frate);
                Chnl_event->Fill(2, myChannel, 1);
            }
            //        Do Category 2
            if (mysubChannel == 2) {

                double FrateX = .1;
                double FrateX = fitFunction(_l3pt, fitType1, FitPar1);
                double Frate = (FrateX) / (1 - FrateX);
                Chnl_estimate->Fill(3, myChannel, Frate);
                Chnl_event->Fill(3, myChannel, 1);
            }
        }
    }


}

void Val3_BGestimation() {
    TH2F* Chnl_estimate = new TH2F("Chnl_estimate", "Chnl_estimate", 10, 0, 10, 10, 0, 10);
    TH2F* Chnl_event = new TH2F("Chnl_event", "Chnl_event", 10, 0, 10, 10, 0, 10);

    bool FRvsJetandEta = 0;
    bool FRvsJetandEta_dedicatedTauFR_LTau = 1;
    bool FRvsJetandEta_dedicatedTauFR_LTau_3ObjFR = 0;
    bool FRvsJet = 0;
    bool FRvsLepton = 0;

    if (FRvsJetandEta) {
        Estim_BG(1, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "B", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "E", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "B", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "E", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "B", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "E", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "B", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "E", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(4, "NoEta", "muLoose_Jet", "l3_CloseJetPt_", 1, "eleLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(8, "NoEta", "eleLoose_Jet", "l3_CloseJetPt_", 1, "muLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
    }

    if (FRvsJetandEta_dedicatedTauFR_LTau) {
        Estim_BG(1, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "B", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "E", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "B", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "E", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "B", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "E", "muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "B", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "E", "eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(4, "NoEta", "muLoose_Jet", "l3_CloseJetPt_", 1, "eleLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(8, "NoEta", "eleLoose_Jet", "l3_CloseJetPt_", 1, "muLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
    }
    if (FRvsJetandEta_dedicatedTauFR_LTau_3ObjFR) {
        Estim_BG(1, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(1, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BB", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "BE", "tauLoose_Jet_B", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EB", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "EE", "tauLoose_Jet_E", "l3_CloseJetPt_", 1, "tauLoose_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "B", "3obj_eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "E", "3obj_eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "B", "3obj_muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "E", "3obj_muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "B", "3obj_muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "E", "3obj_muTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "B", "3obj_eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_B", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "E", "3obj_eleTight_Jet", "l3_CloseJetPt_", 1, "tauLoose_ltau_Jet_E", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(4, "NoEta", "3obj_muLoose_Jet", "l3_CloseJetPt_", 1, "3obj_eleLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(8, "NoEta", "3obj_eleLoose_Jet", "l3_CloseJetPt_", 1, "3obj_muLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
    }

    if (FRvsJet) {
        Estim_BG(1, "NoEta", "tauLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "NoEta", "eleLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "NoEta", "muLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(5, "NoEta", "tauLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(4, "NoEta", "muLoose_Jet", "l3_CloseJetPt_", 1, "eleLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "NoEta", "muLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "NoEta", "eleLoose_Jet", "l3_CloseJetPt_", 1, "tauLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(8, "NoEta", "eleLoose_Jet", "l3_CloseJetPt_", 1, "muLoose_Jet", "l4_CloseJetPt_", 1, Chnl_estimate, Chnl_event);
    }

    if (FRvsLepton) {
        Estim_BG(1, "NoEta", "tauLoose", "l3Pt_", 1, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(2, "NoEta", "eleLoose", "l3Pt_", 0, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(3, "NoEta", "muLoose", "l3Pt_", 0, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(4, "NoEta", "muLoose", "l3Pt_", 0, "eleLoose", "l4Pt_", 0, Chnl_estimate, Chnl_event);
        Estim_BG(5, "NoEta", "tauLoose", "l3Pt_", 1, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(6, "NoEta", "muLoose", "l3Pt_", 0, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(7, "NoEta", "eleLoose", "l3Pt_", 0, "tauLoose", "l4Pt_", 1, Chnl_estimate, Chnl_event);
        Estim_BG(8, "NoEta", "eleLoose", "l3Pt_", 0, "muLoose", "l4Pt_", 0, Chnl_estimate, Chnl_event);
    }

    PrintResults(Chnl_estimate, Chnl_event, "Reducible.root");
}



