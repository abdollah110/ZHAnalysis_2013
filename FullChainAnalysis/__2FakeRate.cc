#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
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

Double_t fitFunc_tau(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
}

Double_t fitFunc_emu(Double_t *x, Double_t *par) {
    return par[0] + par[1] * x[0] + par[2] *0;
}

void M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    cout << "############################################################" << endl;
    double ConstFR = Numerator->Integral(11, 200)*1.0 / Denumerator->Integral(11, 200);
    cout << num.c_str() << " = " << Numerator->Integral(11, 200) << "/" << Denumerator->Integral(11, 200) << "  =  " << ConstFR << endl;
    cout << "############################################################" << endl;
    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(10);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(10);

    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);


    const int nPar = 3; // number of parameters in the fit

    TF1 * theFit = (type.compare("tau") == 0 ? new TF1("theFit", fitFunc_tau, fMin, fMax, nPar) : new TF1("theFit", fitFunc_emu, fMin, fMax, nPar));

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, 0);

    TGraph_FR->Fit("theFit", "R0");

    //############
    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
    TGraph_FR->GetYaxis()->SetRangeUser(0, .2);
    TGraph_FR->GetXaxis()->SetRangeUser(0, 80);
    TGraph_FR->Draw("PAE");
    theFit->Draw("SAME");
    std::string outNaming = "results/__fit" + num + ".png";
    canvas->SaveAs(outNaming.c_str());
    //############

    Double_t TauLegParameters[nPar];
    theFit->GetParameters(TauLegParameters);

    for (int i = 0; i < nPar; i++) {
        hist2D_lep->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
        hist2D_lep->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
    }
    hist2D_lep->SetBinContent(WP, 7, ConstFR); // This for contact fake rate

    //    if (type.compare("tau") == 0) {
    //        for (int i = 0; i < nPar; i++) {
    //            hist2D_lep->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
    //            hist2D_lep->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
    //        }
    //    }
    //    else
    //        hist2D_lep->SetBinContent(WP, 1, Num_rebin->GetEntries()*1.0 / Denum_rebin->GetEntries());

}

void __2FakeRate(){

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 10, 0, 10, 10, 0, 10);
    TH2F * Fit_Value_emu = new TH2F("Fit_Value_emu", "Fit_Value_emu", 10, 0, 10, 10, 0, 10);

    //Tau Fake Rate
    Double_t fMin = 10;
    Double_t fMax = 80;
    M_FR(1, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Loose", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
    M_FR(2, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_LT", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
    M_FR(3, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_TT", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
//    M_FR(2, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Medium", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
//    M_FR(3, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Tight", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
    M_FR(4, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Loose_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
    M_FR(5, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Medium_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
    M_FR(6, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Tight_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
    M_FR(7, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Loose_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
    M_FR(8, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Medium_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
    M_FR(9, "tau", "outRoot/Data.root", "FakeRate_TT_Tau_Pt_After_Tight_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);

    //E-Mu Fake Rate
    fMin = 10;
    fMax = 50;
    M_FR(1, "emu", "outRoot/Data.root", "4objFR_Ele_NumLoose_0", "4objFR_Ele_Denum_0", Fit_Value_emu, fMin, fMax);
    M_FR(2, "emu", "outRoot/Data.root", "4objFR_Ele_NumTight_0", "4objFR_Ele_Denum_0", Fit_Value_emu, fMin, fMax);
    M_FR(3, "emu", "outRoot/Data.root", "4objFR_Mu_NumLoose_0", "4objFR_Mu_Denum_0", Fit_Value_emu, fMin, fMax);
    M_FR(4, "emu", "outRoot/Data.root", "4objFR_Mu_NumTight_0", "4objFR_Mu_Denum_0", Fit_Value_emu, fMin, fMax);


    FR_File->Write();
    FR_File->Close();
}
