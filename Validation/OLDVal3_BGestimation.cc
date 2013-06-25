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
        return (par0 + par1 * (TMath::Exp(par2 * x)));
    else
        return par0 + par1 * x;
}

void PrintResults(TH2F* Chnl_estimate, TH2F* Chnl_event, std::string name) {
    TFile * MegaFile = new TFile("valid_Mega.root");
    TH1D * arrayPP[8];
    char * array[8] = {"mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"};
    char *arrayMass[8] = {"VisibleMass_mmtt_pp", "VisibleMass_mmet_pp", "VisibleMass_mmmt_pp", "VisibleMass_mmme_pp", "VisibleMass_eett_pp", "VisibleMass_eemt_pp", "VisibleMass_eeet_pp", "VisibleMass_eeem_pp"};
    for (int q = 0; q < 8; q++) {
        arrayPP[q] = (TH1D*) MegaFile->Get(arrayMass[q]);
    }

    TFile * OutFile = new TFile(name.c_str(), "RECREATE");
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
    float Total_Obs = 0;
    for (int j = 1; j <= 8; j++) {
        cout << "LeptonFR" << "&" << array[j - 1] << "&";
        double cen_val = 0;
        for (int i = 1; i <= 3; i++) {
            cout << Chnl_estimate->GetBinContent(i + 1, j + 1) << "(" << int(Chnl_event->GetBinContent(i + 1, j + 1)) << ")" << "&";
        }
        cen_val = Chnl_estimate->GetBinContent(3, j + 1) + Chnl_estimate->GetBinContent(4, j + 1) - Chnl_estimate->GetBinContent(2, j + 1);

        cout << cen_val << "&";
        float obs = arrayPP[j - 1]->Integral();
        cout << int(obs) << " \\\\ " << endl;
        Total_Est += cen_val;
        Total_Obs += obs;
        histo_Reducible->SetBinContent(j, cen_val);
    }
    cout << "\\hline" << "\n\\end{tabular}" << "\n\\end{table}" << "\n\n\n";
    cout << "Total Reducible BG =  " << Total_Est << endl;
    //    cout << "Total Reducible BG =  " << Total_Est << "    with:    "<< Total_Obs<<endl;

    OutFile->Write();
    OutFile->Close();
}

void Measure(int num, std::vector<float> p, bool p_ptDep, std::vector<float> q, bool q_ptDep, TH2F * Chnl_estimate, TH2F* Chnl_event, std::string ff, std::string fp, std::string pf) {
    float startCut = 10;
    TFile * MegaFile = new TFile("valid_Mega.root");
    TH2D *Hist2_FF = (TH2D*) MegaFile->Get(ff.c_str());
    TH1D *Hist2_FP = (TH1D*) MegaFile->Get(fp.c_str());
    TH1D *Hist2_PF = (TH1D*) MegaFile->Get(pf.c_str());
    cout << ff << " " << Hist2_FF->Integral() << "\t" << fp << " " << Hist2_FP->Integral() << "\t" << pf << " " << Hist2_PF->Integral() << "\n";
    for (int i = startCut; i < Hist2_FF->GetNbinsX(); i++) {
        for (int j = startCut; j < Hist2_FF->GetNbinsY(); j++) {
            double Value = Hist2_FF->GetBinContent(i + 1, j + 1);
            double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
            double FrateY = fitFunction(0.5 + j, q[0], q[1], q[2], q_ptDep);
            if (FrateX > 0.95 && FrateX < 1.0) FrateX = 0.975; // This is to prohibit the denumerator NOT to blow up
            if (FrateX > 1.0 && FrateX < 1.05) FrateX = 1.025; // This is to prohibit the denumerator NOT to blow up
            if (FrateY > 0.95 && FrateY < 1.0) FrateY = 0.975; // This is to prohibit the denumerator NOT to blow up
            if (FrateY > 1.0 && FrateY < 1.05) FrateY = 1.025; // This is to prohibit the denumerator NOT to blow up
            //            if (FrateX > .99 || FrateY > .99) cout << i <<"  FrateX=  " << FrateX  <<"     FrateY=  " << FrateY << endl;
            double Frate = (Value * (FrateX * FrateY) / ((1 - FrateX) * (1 - FrateY)));
            Chnl_estimate->Fill(1, num, Frate);
            Chnl_event->Fill(1, num, Value);
            if (FrateY > 2) cout << FrateY << "\t";
            if (FrateX > 2) cout << FrateX << "\t";
        }
    }
    for (int i = startCut; i < Hist2_FP->GetNbinsX(); i++) {
        double Value = Hist2_FP->GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
        if (FrateX > 0.95 && FrateX < 1.0) FrateX = 0.975; // This is to prohibit the denumerator NOT to blow up
        if (FrateX > 1.0 && FrateX < 1.05) FrateX = 1.025; // This is to prohibit the denumerator NOT to blow up
        double Frate = Value * (FrateX) / (1 - FrateX);
        Chnl_estimate->Fill(2, num, Frate);
        Chnl_event->Fill(2, num, Value);
    }
    for (int i = startCut; i < Hist2_PF->GetNbinsX(); i++) {
        double Value = Hist2_PF->GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, q[0], q[1], q[2], q_ptDep);
        if (FrateX > 0.95 && FrateX < 1.0) FrateX = 0.975; // This is to prohibit the denumerator NOT to blow up
        if (FrateX > 1.0 && FrateX < 1.05) FrateX = 1.025; // This is to prohibit the denumerator NOT to blow up
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

    //apply the Eta dependecy CloseJet
    if (firstLeg == "tauLoose_Jet_B")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(14, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose_Jet_E")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(17, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_Jet_B")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(14, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose_Jet_E")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(17, 2 * (i - 1) + 1));
    //apply the Eta dependecy RefJet
    if (firstLeg == "RefJetLoose_B")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(24, 2 * (i - 1) + 1));
    if (firstLeg == "RefJetLoose_E")
        for (int i = 1; i <= 3; i++) leg1.push_back(Fit_Value_tau->GetBinContent(27, 2 * (i - 1) + 1));
    if (secondLeg == "RefJetLoose_B")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(24, 2 * (i - 1) + 1));
    if (secondLeg == "RefJetLoose_E")
        for (int i = 1; i <= 3; i++) leg2.push_back(Fit_Value_tau->GetBinContent(27, 2 * (i - 1) + 1));

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

void OLDVal3_BGestimation() {
    TH2F* Chnl_estimate = new TH2F("Chnl_estimate", "Chnl_estimate", 10, 0, 10, 10, 0, 10);
    TH2F* Chnl_event = new TH2F("Chnl_event", "Chnl_event", 10, 0, 10, 10, 0, 10);

    //MMTT & EETT
    bool tauFR_pt = 0;
    bool tauCloseJet_pt = 0;
    bool tauRefJet_pt = 0;
    bool tauFR_ptEta = 0;
    bool tauCloseJet_ptEta = 0;
    bool tauRefJet_ptEta = 0;
    std::string name;

    if (tauFR_pt) {
        Get_FitParameter(1, "tauLoose", 1, "tauLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
        Get_FitParameter(5, "tauLoose", 1, "tauLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff", "FakeRate_EETT_apply_fp", "FakeRate_EETT_apply_pf");
        name = "tauFR_pt.root";
    }
    if (tauCloseJet_pt) {
        Get_FitParameter(1, "tauLoose_Jet", 1, "tauLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_Jet", "FakeRate_MMTT_apply_fp_Jet", "FakeRate_MMTT_apply_pf_Jet");
        Get_FitParameter(5, "tauLoose_Jet", 1, "tauLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_Jet", "FakeRate_EETT_apply_fp_Jet", "FakeRate_EETT_apply_pf_Jet");
        name = "tauCloseJet_pt.root";
    }
    if (tauRefJet_pt) {
        Get_FitParameter(1, "tauLoose_RefJet", 1, "tauLoose_RefJet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet", "FakeRate_MMTT_apply_fp_RefJet", "FakeRate_MMTT_apply_pf_RefJet");
        Get_FitParameter(5, "tauLoose_RefJet", 1, "tauLoose_RefJet", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet", "FakeRate_EETT_apply_fp_RefJet", "FakeRate_EETT_apply_pf_RefJet");
        name = "tauRefJet_pt.root";
    }
    if (tauFR_ptEta) {
        Get_FitParameter(1, "tauLoose_B", 1, "tauLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_BB", "FakeRate_MMTT_apply_fp_BB", "FakeRate_MMTT_apply_pf_BB");
        Get_FitParameter(1, "tauLoose_B", 1, "tauLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_BE", "FakeRate_MMTT_apply_fp_BE", "FakeRate_MMTT_apply_pf_BE");
        Get_FitParameter(1, "tauLoose_E", 1, "tauLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_EB", "FakeRate_MMTT_apply_fp_EB", "FakeRate_MMTT_apply_pf_EB");
        Get_FitParameter(1, "tauLoose_E", 1, "tauLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_EE", "FakeRate_MMTT_apply_fp_EE", "FakeRate_MMTT_apply_pf_EE");
        Get_FitParameter(5, "tauLoose_B", 1, "tauLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_BB", "FakeRate_EETT_apply_fp_BB", "FakeRate_EETT_apply_pf_BB");
        Get_FitParameter(5, "tauLoose_B", 1, "tauLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_BE", "FakeRate_EETT_apply_fp_BE", "FakeRate_EETT_apply_pf_BE");
        Get_FitParameter(5, "tauLoose_E", 1, "tauLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_EB", "FakeRate_EETT_apply_fp_EB", "FakeRate_EETT_apply_pf_EB");
        Get_FitParameter(5, "tauLoose_E", 1, "tauLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_EE", "FakeRate_EETT_apply_fp_EE", "FakeRate_EETT_apply_pf_EE");
        name = "tauFR_ptEta.root";
    }
    if (tauCloseJet_ptEta) {
        Get_FitParameter(1, "tauLoose_Jet_B", 1, "tauLoose_Jet_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_CloseJet_BB", "FakeRate_MMTT_apply_fp_CloseJet_BB", "FakeRate_MMTT_apply_pf_CloseJet_BB");
        Get_FitParameter(1, "tauLoose_Jet_B", 1, "tauLoose_Jet_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_CloseJet_BE", "FakeRate_MMTT_apply_fp_CloseJet_BE", "FakeRate_MMTT_apply_pf_CloseJet_BE");
        Get_FitParameter(1, "tauLoose_Jet_E", 1, "tauLoose_Jet_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_CloseJet_EB", "FakeRate_MMTT_apply_fp_CloseJet_EB", "FakeRate_MMTT_apply_pf_CloseJet_EB");
        Get_FitParameter(1, "tauLoose_Jet_E", 1, "tauLoose_Jet_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_CloseJet_EE", "FakeRate_MMTT_apply_fp_CloseJet_EE", "FakeRate_MMTT_apply_pf_CloseJet_EE");
        Get_FitParameter(5, "tauLoose_Jet_B", 1, "tauLoose_Jet_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_CloseJet_BB", "FakeRate_EETT_apply_fp_CloseJet_BB", "FakeRate_EETT_apply_pf_CloseJet_BB");
        Get_FitParameter(5, "tauLoose_Jet_B", 1, "tauLoose_Jet_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_CloseJet_BE", "FakeRate_EETT_apply_fp_CloseJet_BE", "FakeRate_EETT_apply_pf_CloseJet_BE");
        Get_FitParameter(5, "tauLoose_Jet_E", 1, "tauLoose_Jet_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_CloseJet_EB", "FakeRate_EETT_apply_fp_CloseJet_EB", "FakeRate_EETT_apply_pf_CloseJet_EB");
        Get_FitParameter(5, "tauLoose_Jet_E", 1, "tauLoose_Jet_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_CloseJet_EE", "FakeRate_EETT_apply_fp_CloseJet_EE", "FakeRate_EETT_apply_pf_CloseJet_EE");
        name = "tauCloseJet_ptEta.root";
    }
    if (tauRefJet_ptEta) {
        Get_FitParameter(1, "RefJetLoose_B", 1, "RefJetLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet_BB", "FakeRate_MMTT_apply_fp_RefJet_BB", "FakeRate_MMTT_apply_pf_RefJet_BB");
        Get_FitParameter(1, "RefJetLoose_B", 1, "RefJetLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet_BE", "FakeRate_MMTT_apply_fp_RefJet_BE", "FakeRate_MMTT_apply_pf_RefJet_BE");
        Get_FitParameter(1, "RefJetLoose_E", 1, "RefJetLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet_EB", "FakeRate_MMTT_apply_fp_RefJet_EB", "FakeRate_MMTT_apply_pf_RefJet_EB");
        Get_FitParameter(1, "RefJetLoose_E", 1, "RefJetLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff_RefJet_EE", "FakeRate_MMTT_apply_fp_RefJet_EE", "FakeRate_MMTT_apply_pf_RefJet_EE");
        Get_FitParameter(5, "RefJetLoose_B", 1, "RefJetLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet_BB", "FakeRate_EETT_apply_fp_RefJet_BB", "FakeRate_EETT_apply_pf_RefJet_BB");
        Get_FitParameter(5, "RefJetLoose_B", 1, "RefJetLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet_BE", "FakeRate_EETT_apply_fp_RefJet_BE", "FakeRate_EETT_apply_pf_RefJet_BE");
        Get_FitParameter(5, "RefJetLoose_E", 1, "RefJetLoose_B", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet_EB", "FakeRate_EETT_apply_fp_RefJet_EB", "FakeRate_EETT_apply_pf_RefJet_EB");
        Get_FitParameter(5, "RefJetLoose_E", 1, "RefJetLoose_E", 1, Chnl_estimate, Chnl_event, "FakeRate_EETT_apply_ff_RefJet_EE", "FakeRate_EETT_apply_fp_RefJet_EE", "FakeRate_EETT_apply_pf_RefJet_EE");
        name = "tauRefJet_ptEta.root";
    }

    //########## ltau validation

    bool tauPtlepPt = 0;
    bool tauJetlepPt = 0;
    bool tauJetlepJet = 0;
    bool tauJetlepJetETA = 1;

    if (tauPtlepPt) {
        Get_FitParameter(2, "tauLoose", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff", "FakeRate_MMET_apply_fp", "FakeRate_MMET_apply_pf");
        Get_FitParameter(3, "tauLoose", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff", "FakeRate_MMMT_apply_fp", "FakeRate_MMMT_apply_pf");
        Get_FitParameter(4, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff", "FakeRate_MMME_apply_fp", "FakeRate_MMME_apply_pf");
        Get_FitParameter(6, "tauLoose", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff", "FakeRate_EEMT_apply_fp", "FakeRate_EEMT_apply_pf");
        Get_FitParameter(7, "tauLoose", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff", "FakeRate_EEET_apply_fp", "FakeRate_EEET_apply_pf");
        Get_FitParameter(8, "muLoose", 0, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff", "FakeRate_EEEM_apply_fp", "FakeRate_EEEM_apply_pf");
        name = "tauPtlepPt.root";
    }
    if (tauJetlepPt) {
        Get_FitParameter(2, "tauLoose_Jet", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_JetTau", "FakeRate_MMET_apply_fp_JetTau", "FakeRate_MMET_apply_pf_JetTau");
        Get_FitParameter(3, "tauLoose_Jet", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_JetTau", "FakeRate_MMMT_apply_fp_JetTau", "FakeRate_MMMT_apply_pf_JetTau");
        //        Get_FitParameter(4, "eleLoose", 1, "muLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff_JetTau", "FakeRate_MMME_apply_fp_JetTau", "FakeRate_MMME_apply_pf_JetTau");
        Get_FitParameter(6, "tauLoose_Jet", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_JetTau", "FakeRate_EEMT_apply_fp_JetTau", "FakeRate_EEMT_apply_pf_JetTau");
        Get_FitParameter(7, "tauLoose_Jet", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_JetTau", "FakeRate_EEET_apply_fp_JetTau", "FakeRate_EEET_apply_pf_JetTau");
        //        Get_FitParameter(8, "muLoose", 1, "eleLoose", 1, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff_JetTau", "FakeRate_EEEM_apply_fp_JetTau", "FakeRate_EEEM_apply_pf_JetTau");
        name = "tauJetlepPt.root";
    }
    if (tauJetlepJet) {
        Get_FitParameter(2, "tauLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_Jet", "FakeRate_MMET_apply_fp_Jet", "FakeRate_MMET_apply_pf_Jet");
        Get_FitParameter(3, "tauLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_Jet", "FakeRate_MMMT_apply_fp_Jet", "FakeRate_MMMT_apply_pf_Jet");
        Get_FitParameter(4, "eleLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff_Jet", "FakeRate_MMME_apply_fp_Jet", "FakeRate_MMME_apply_pf_Jet");
        Get_FitParameter(6, "tauLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_Jet", "FakeRate_EEMT_apply_fp_Jet", "FakeRate_EEMT_apply_pf_Jet");
        Get_FitParameter(7, "tauLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_Jet", "FakeRate_EEET_apply_fp_Jet", "FakeRate_EEET_apply_pf_Jet");
        Get_FitParameter(8, "muLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff_Jet", "FakeRate_EEEM_apply_fp_Jet", "FakeRate_EEEM_apply_pf_Jet");
        name = "tauJetlepJet.root";
    }
    if (tauJetlepJetETA) {
        Get_FitParameter(2, "tauLoose_Jet_B", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_B", "FakeRate_MMET_apply_fp_B", "FakeRate_MMET_apply_pf_B");
        Get_FitParameter(2, "tauLoose_Jet_E", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_E", "FakeRate_MMET_apply_fp_E", "FakeRate_MMET_apply_pf_E");
        Get_FitParameter(3, "tauLoose_Jet_B", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_B", "FakeRate_MMMT_apply_fp_B", "FakeRate_MMMT_apply_pf_B");
        Get_FitParameter(3, "tauLoose_Jet_E", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_E", "FakeRate_MMMT_apply_fp_E", "FakeRate_MMMT_apply_pf_E");
        Get_FitParameter(4, "eleLoose_Jet", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_MMME_apply_ff_Jet", "FakeRate_MMME_apply_fp_Jet", "FakeRate_MMME_apply_pf_Jet");
        Get_FitParameter(6, "tauLoose_Jet_B", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_B", "FakeRate_EEMT_apply_fp_B", "FakeRate_EEMT_apply_pf_B");
        Get_FitParameter(6, "tauLoose_Jet_E", 1, "muLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_E", "FakeRate_EEMT_apply_fp_E", "FakeRate_EEMT_apply_pf_E");
        Get_FitParameter(7, "tauLoose_Jet_B", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_B", "FakeRate_EEET_apply_fp_B", "FakeRate_EEET_apply_pf_B");
        Get_FitParameter(7, "tauLoose_Jet_E", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_E", "FakeRate_EEET_apply_fp_E", "FakeRate_EEET_apply_pf_E");
        Get_FitParameter(8, "muLoose_Jet", 1, "eleLoose_Jet", 1, Chnl_estimate, Chnl_event, "FakeRate_EEEM_apply_ff_Jet", "FakeRate_EEEM_apply_fp_Jet", "FakeRate_EEEM_apply_pf_Jet");
        name = "tauJetlepJetWta.root";
    }

    //        Get_FitParameter(2, "tauLoose_B", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_B", "FakeRate_MMET_apply_fp_B", "FakeRate_MMET_apply_pf_B");
    //        Get_FitParameter(2, "tauLoose_E", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff_E", "FakeRate_MMET_apply_fp_E", "FakeRate_MMET_apply_pf_E");
    //        Get_FitParameter(3, "tauLoose_B", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_B", "FakeRate_MMMT_apply_fp_B", "FakeRate_MMMT_apply_pf_B");
    //        Get_FitParameter(3, "tauLoose_E", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_MMMT_apply_ff_E", "FakeRate_MMMT_apply_fp_E", "FakeRate_MMMT_apply_pf_E");
    //        Get_FitParameter(6, "tauLoose_B", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_B", "FakeRate_EEMT_apply_fp_B", "FakeRate_EEMT_apply_pf_B");
    //        Get_FitParameter(6, "tauLoose_E", 1, "muLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEMT_apply_ff_E", "FakeRate_EEMT_apply_fp_E", "FakeRate_EEMT_apply_pf_E");
    //        Get_FitParameter(7, "tauLoose_B", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_B", "FakeRate_EEET_apply_fp_B", "FakeRate_EEET_apply_pf_B");
    //        Get_FitParameter(7, "tauLoose_E", 1, "eleLoose", 0, Chnl_estimate, Chnl_event, "FakeRate_EEET_apply_ff_E", "FakeRate_EEET_apply_fp_E", "FakeRate_EEET_apply_pf_E");





    PrintResults(Chnl_estimate, Chnl_event, name);
}

