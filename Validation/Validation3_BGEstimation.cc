#include <TGraph.h>

#include "TRandom.h"
#include "iostream.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

Double_t fitFunction(Double_t x, Double_t par0, Double_t par1, Double_t par2, bool isPtDependent) {
    if (isPtDependent)
        return par0 + par1 * (TMath::Exp(par2 * x));
    else
        return par0 + par1 * x;
}

void PrintResults(TH2F* Chnl_estimate, TH2F* Chnl_event) {
    TFile * MegaFile = new TFile("valid_Mega.root");
    TH1D * arrayPP[8];
    char * array[8] = {"mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"};
    char *arrayMass[8] = {"VisibleMass_mmtt_pp", "VisibleMass_mmet_pp", "VisibleMass_mmmt_pp", "VisibleMass_mmme_pp", "VisibleMass_eett_pp", "VisibleMass_eemt_pp", "VisibleMass_eeet_pp", "VisibleMass_eeem_pp"};
    for (int q = 0; q < 8; q++) {
        arrayPP[q] = (TH1D*) MegaFile->Get(arrayMass[q]);
    }

    TFile * OutFile = new TFile("Reducible_validation.root", "RECREATE");
    OutFile->cd();
    TH1F * histo_Reducible = new TH1F("histo_Reducible", "histo_Reducible", 10, 0, 10);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    cout << "\n\n" << "\\begin{table}[htbp]" << endl;
    cout << "\\centering" << endl;
    cout << "\\caption{ events}" << endl;
    cout << "\\label{table:events}" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c|c|c| }" << endl;
    cout << "\\hline" << endl;
    cout << "FR type & channel & Cat0 & Cat1 & Cat2 &  1+2-0 & Selected" << " \\\\" << endl;
    cout << "\\hline" << endl;


    float Total_Est = 0;
    for (int j = 1; j <= 8; j++) {
        cout << "LeptonFR" << "&" << array[j - 1] << "&";
        double cen_val = 0;
        for (int i = 1; i <= 3; i++) {
            cout << Chnl_estimate->GetBinContent(i + 1, j + 1) << "(" << int(Chnl_event->GetBinContent(i + 1, j + 1)) << ")" << "&";
        }
        cen_val = Chnl_estimate->GetBinContent(3, j + 1) + Chnl_estimate->GetBinContent(4, j + 1) - Chnl_estimate->GetBinContent(2, j + 1);

        cout << cen_val << "&";
        cout << int(arrayPP[j - 1]->Integral()) << " \\\\ " << endl;
        Total_Est += cen_val;
        histo_Reducible->SetBinContent(j, cen_val);
    }
    cout << "\\hline" << "\n\\end{tabular}" << "\n\\end{table}" << "\n\n\n";
    cout << "Total Reducible BG =  " << Total_Est << endl;

    OutFile->Write();
    OutFile->Close();
}

void Measure(int num, std::vector<float> p, bool p_ptDep, std::vector<float> q, bool q_ptDep, TH2F * Chnl_estimate, TH2F* Chnl_event, std::string ff, std::string fp, std::string pf) {
    cout << ff << " " << fp << "  " << pf << endl;
    TFile * MegaFile = new TFile("valid_Mega.root");
    TH2D *Hist2_FF = (TH2D*) MegaFile->Get(ff.c_str());
    TH1D *Hist2_FP = (TH1D*) MegaFile->Get(fp.c_str());
    TH1D *Hist2_PF = (TH1D*) MegaFile->Get(pf.c_str());

    for (int i = 10; i < Hist2_FF->GetNbinsX(); i++) {
        for (int j = 10; j < Hist2_FF->GetNbinsY(); j++) {
            double Value = Hist2_FF->GetBinContent(i + 1, j + 1);
            double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
            double FrateY = fitFunction(0.5 + j, q[0], q[1], q[2], q_ptDep);
            double Frate = (Value * (FrateX * FrateY) / ((1 - FrateX) * (1 - FrateY)));
            Chnl_estimate->Fill(1, num, Frate);
            Chnl_event->Fill(1, num, Value);
        }
    }
    for (int i = 10; i < Hist2_FP->GetNbinsX(); i++) {
        double Value = Hist2_FP->GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
        double Frate = Value * (FrateX) / (1 - FrateX);
        Chnl_estimate->Fill(2, num, Frate);
        Chnl_event->Fill(2, num, Value);
    }
    for (int i = 10; i < Hist2_PF->GetNbinsX(); i++) {
        double Value = Hist2_PF->GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, q[0], q[1], q[2], q_ptDep);
        double Frate = Value * (FrateX) / (1 - FrateX);
        Chnl_estimate->Fill(3, num, Frate);
        Chnl_event->Fill(3, num, Value);
    }
}

void Get_FitParameter(int num, std::string firstLeg, bool is_ptDep1, std::string secondLeg, bool is_ptDep2, TH2F * Chnl_estimate, TH2F* Chnl_event, std::string ff, std::string fp, std::string pf) {
    TFile *fr_file = new TFile("FitValues_FR.root");
    TH2F * Fit_Value_tau = (TH2F*) fr_file->Get("Fit_Value_tau");
    TH2F * Fit_Value_emu = (TH2F*) fr_file->Get("Fit_Value_emu");

    std::vector<float> leg1;
    std::vector<float> leg2;
    leg1.clear();
    leg2.clear();

    //first leg
    if (firstLeg == "tauTight")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(3, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(2, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(1, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_Jet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(13, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_Jet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(12, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(11, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_RefJet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(23, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_RefJet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(22, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_RefJet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(21, 2 * (i - 1) + 1));
    //ele Mu
    if (firstLeg == "eleLoose")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_emu->GetBinContent(1, 2 * (i - 1) + 1));
    if (firstLeg == "eleLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_emu->GetBinContent(5, 2 * (i - 1) + 1));
    if (firstLeg == "muLoose")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_emu->GetBinContent(3, 2 * (i - 1) + 1));
    if (firstLeg == "muLoose_Jet")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_emu->GetBinContent(7, 2 * (i - 1) + 1));
    //second leg
    if (secondLeg == "tauTight")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(3, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(2, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(1, 2 * (i - 1) + 1));
    if (secondLeg == "tauTight_Jet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(13, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium_Jet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(12, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_Jet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(11, 2 * (i - 1) + 1));
    if (secondLeg == "tauTight_RefJet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(23, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium_RefJet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(22, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_RefJet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(21, 2 * (i - 1) + 1));
    //ele Mu
    if (secondLeg == "eleLoose")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(1, 2 * (i - 1) + 1));
    if (secondLeg == "eleLoose_Jet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(5, 2 * (i - 1) + 1));
    if (secondLeg == "eleTight")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(2, 2 * (i - 1) + 1));
    if (secondLeg == "muLoose")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(3, 2 * (i - 1) + 1));
    if (secondLeg == "muLoose_Jet")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(7, 2 * (i - 1) + 1));
    if (secondLeg == "muTight")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_emu->GetBinContent(4, 2 * (i - 1) + 1));


    //apply the Eta dependecy
    if (firstLeg == "tauLoose_B")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(4, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_B")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(5, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_B")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(6, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_E")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(7, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium_E")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(8, 2 * (i - 1) + 1));
    if (firstLeg == "tauTight_E")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(9, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_B")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(4, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium_B")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(5, 2 * (i - 1) + 1));
    if (secondLeg == "tauTight_B")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(6, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_E")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(7, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium_E")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(8, 2 * (i - 1) + 1));
    if (secondLeg == "tauTight_E")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(9, 2 * (i - 1) + 1));

    //apply Const fakeRate for tau
    if (firstLeg == "tauLoose_const") {
        leg1.push_back(Fit_Value_tau->GetBinContent(1, 7));
        leg1.push_back(0);
        leg1.push_back(0);
    }
    if (firstLeg == "tauMedium_const") {
        leg1.push_back(Fit_Value_tau->GetBinContent(2, 7));
        leg1.push_back(0);
        leg1.push_back(0);
    }
    if (firstLeg == "tauTight_const") {
        leg1.push_back(Fit_Value_tau->GetBinContent(3, 7));
        leg1.push_back(0);
        leg1.push_back(0);
    }
    if (secondLeg == "tauLoose_const") {
        leg2.push_back(Fit_Value_tau->GetBinContent(1, 7));
        leg2.push_back(0);
        leg2.push_back(0);
    }
    if (secondLeg == "tauMedium_const") {
        leg2.push_back(Fit_Value_tau->GetBinContent(2, 7));
        leg2.push_back(0);
        leg2.push_back(0);
    }
    if (secondLeg == "tauTight_const") {
        leg2.push_back(Fit_Value_tau->GetBinContent(3, 7));
        leg2.push_back(0);
        leg2.push_back(0);
    }
    //    //BarrelEndCap constant
    //    if (firstLeg == "tauLoose_B") {
    //        leg1.push_back(Fit_Value_tau->GetBinContent(1, 7));
    //        leg1.push_back(0);
    //        leg1.push_back(0);
    //    }
    //    if (secondLeg == "tauLoose_B") {
    //        leg2.push_back(Fit_Value_tau->GetBinContent(1, 7));
    //        leg2.push_back(0);
    //        leg2.push_back(0);
    //    }
    //    if (firstLeg == "tauLoose_E") {
    //        leg1.push_back(Fit_Value_tau->GetBinContent(1, 7));
    //        leg1.push_back(0);
    //        leg1.push_back(0);
    //    }
    //    if (secondLeg == "tauLoose_E") {
    //        leg2.push_back(Fit_Value_tau->GetBinContent(1, 7));
    //        leg2.push_back(0);
    //        leg2.push_back(0);
    //    }

    Measure(num, leg1, is_ptDep1, leg2, is_ptDep2, Chnl_estimate, Chnl_event, ff, fp, pf);
}

void Validation3_BGEstimation() {
    TH2F* Chnl_estimate = new TH2F("Chnl_estimate", "Chnl_estimate", 10, 0, 10, 10, 0, 10);
    TH2F* Chnl_event = new TH2F("Chnl_event", "Chnl_event", 10, 0, 10, 10, 0, 10);

    //        Get_FitParameter(1, "tauMedium_const", 1, "tauMedium_const", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
    //        Get_FitParameter(5, "tauMedium_const", 1, "tauMedium_const", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff", "FakeRate_EETT_apply_fp", "FakeRate_EETT_apply_pf");


    //        Get_FitParameter(1, "tauMedium", 1, "tauMedium", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
    //        Get_FitParameter(5, "tauMedium", 1, "tauMedium", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff", "FakeRate_EETT_apply_fp", "FakeRate_EETT_apply_pf");

        Get_FitParameter(1, "tauLoose", 1, "tauLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
        Get_FitParameter(5, "tauLoose", 1, "tauLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff", "FakeRate_EETT_apply_fp", "FakeRate_EETT_apply_pf");
//    Get_FitParameter(1, "tauLoose_Jet", 1, "tauLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_Jet", "FakeRate_MMTT_apply_fp_Jet", "FakeRate_MMTT_apply_pf_Jet");
//    Get_FitParameter(5, "tauLoose_Jet", 1, "tauLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_Jet", "FakeRate_EETT_apply_fp_Jet", "FakeRate_EETT_apply_pf_Jet");
    //        Get_FitParameter(1, "tauLoose_RefJet", 1, "tauLoose_RefJet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet", "FakeRate_MMTT_apply_fp_RefJet", "FakeRate_MMTT_apply_pf_RefJet");
    //        Get_FitParameter(5, "tauLoose_RefJet", 1, "tauLoose_RefJet", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet", "FakeRate_EETT_apply_fp_RefJet", "FakeRate_EETT_apply_pf_RefJet");

    //    Get_FitParameter(1, "tauMedium", 1, "tauMedium", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
    //    Get_FitParameter(5, "tauMedium", 1, "tauMedium", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff", "FakeRate_EETT_apply_fp", "FakeRate_EETT_apply_pf");

    //        Get_FitParameter(1, "tauMedium_B", 1, "tauMedium_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_BB", "FakeRate_MMTT_apply_fp_BB", "FakeRate_MMTT_apply_pf_BB");
    //        Get_FitParameter(1, "tauMedium_B", 1, "tauMedium_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_BE", "FakeRate_MMTT_apply_fp_BE", "FakeRate_MMTT_apply_pf_BE");
    //        Get_FitParameter(1, "tauMedium_E", 1, "tauMedium_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_EB", "FakeRate_MMTT_apply_fp_EB", "FakeRate_MMTT_apply_pf_EB");
    //        Get_FitParameter(1, "tauMedium_E", 1, "tauMedium_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_EE", "FakeRate_MMTT_apply_fp_EE", "FakeRate_MMTT_apply_pf_EE");
    //        Get_FitParameter(5, "tauMedium_B", 1, "tauMedium_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_BB", "FakeRate_EETT_apply_fp_BB", "FakeRate_EETT_apply_pf_BB");
    //        Get_FitParameter(5, "tauMedium_B", 1, "tauMedium_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_BE", "FakeRate_EETT_apply_fp_BE", "FakeRate_EETT_apply_pf_BE");
    //        Get_FitParameter(5, "tauMedium_E", 1, "tauMedium_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_EB", "FakeRate_EETT_apply_fp_EB", "FakeRate_EETT_apply_pf_EB");
    //        Get_FitParameter(5, "tauMedium_E", 1, "tauMedium_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_EE", "FakeRate_EETT_apply_fp_EE", "FakeRate_EETT_apply_pf_EE");


    //########## ltau validation
//    Get_FitParameter(2, "tauLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_Jet", "FakeRate_MMET_apply_fp_Jet", "FakeRate_MMET_apply_pf_Jet");
//    Get_FitParameter(3, "tauLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_Jet", "FakeRate_MMMT_apply_fp_Jet", "FakeRate_MMMT_apply_pf_Jet");
//    Get_FitParameter(4, "eleLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff_Jet", "FakeRate_MMME_apply_fp_Jet", "FakeRate_MMME_apply_pf_Jet");
//    Get_FitParameter(6, "tauLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_Jet", "FakeRate_EEMT_apply_fp_Jet", "FakeRate_EEMT_apply_pf_Jet");
//    Get_FitParameter(7, "tauLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_Jet", "FakeRate_EEET_apply_fp_Jet", "FakeRate_EEET_apply_pf_Jet");
//    Get_FitParameter(8, "muLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff_Jet", "FakeRate_EEEM_apply_fp_Jet", "FakeRate_EEEM_apply_pf_Jet");
            Get_FitParameter(2, "tauLoose", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff", "FakeRate_MMET_apply_fp", "FakeRate_MMET_apply_pf");
            Get_FitParameter(3, "tauLoose", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff", "FakeRate_MMMT_apply_fp", "FakeRate_MMMT_apply_pf");
            Get_FitParameter(4, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff", "FakeRate_MMME_apply_fp", "FakeRate_MMME_apply_pf");
            Get_FitParameter(6, "tauLoose", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff", "FakeRate_EEMT_apply_fp", "FakeRate_EEMT_apply_pf");
            Get_FitParameter(7, "tauLoose", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff", "FakeRate_EEET_apply_fp", "FakeRate_EEET_apply_pf");
            Get_FitParameter(8, "muLoose", 0, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff", "FakeRate_EEEM_apply_fp", "FakeRate_EEEM_apply_pf");
    //        Get_FitParameter(2, "tauLoose_B", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_B", "FakeRate_MMET_apply_fp_B", "FakeRate_MMET_apply_pf_B");
    //        Get_FitParameter(2, "tauLoose_E", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_E", "FakeRate_MMET_apply_fp_E", "FakeRate_MMET_apply_pf_E");
    //        Get_FitParameter(3, "tauLoose_B", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_B", "FakeRate_MMMT_apply_fp_B", "FakeRate_MMMT_apply_pf_B");
    //        Get_FitParameter(3, "tauLoose_E", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_E", "FakeRate_MMMT_apply_fp_E", "FakeRate_MMMT_apply_pf_E");
    //        Get_FitParameter(6, "tauLoose_B", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_B", "FakeRate_EEMT_apply_fp_B", "FakeRate_EEMT_apply_pf_B");
    //        Get_FitParameter(6, "tauLoose_E", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_E", "FakeRate_EEMT_apply_fp_E", "FakeRate_EEMT_apply_pf_E");
    //        Get_FitParameter(7, "tauLoose_B", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_B", "FakeRate_EEET_apply_fp_B", "FakeRate_EEET_apply_pf_B");
    //        Get_FitParameter(7, "tauLoose_E", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_E", "FakeRate_EEET_apply_fp_E", "FakeRate_EEET_apply_pf_E");





    PrintResults(Chnl_estimate, Chnl_event);
}

