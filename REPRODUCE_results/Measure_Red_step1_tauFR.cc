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

Double_t fitFunction(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
}

void fake_Fit(int WP, TGraphAsymmErrors * TGraph_FR, TH2F * Fit_Value_tau) {

    const int nPar = 3; // number of parameters in the fit
    Double_t fitRangeMin = 15,
            fitRangeMax = 80;

    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, -0.095);

    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
    canvas->SetFillColor(0);

    canvas->cd(1);

    TGraph_FR->SetMarkerColor(3);
    TGraph_FR->SetMarkerSize(1.4);
    TGraph_FR->SetMarkerStyle(20);
    TGraph_FR->GetXaxis()->SetTitle("#tau Pt [GeV]");
    TGraph_FR->GetXaxis()->SetTitleOffset(1);
    TGraph_FR->GetXaxis()->SetTitleSize(0.05);
    TGraph_FR->GetYaxis()->SetTitle("Fake Rate");
    TGraph_FR->GetYaxis()->SetRangeUser(0, 0.1);
    TGraph_FR->GetXaxis()->SetRangeUser(0, 100);
    TGraph_FR->GetYaxis()->SetTitleOffset(1.3);
    TGraph_FR->GetYaxis()->SetTitleSize(0.05);
    TGraph_FR->Draw("PAE");

    TGraph_FR->Fit("theFit", "R0");
    theFit->SetRange(10, 100);
    theFit->SetLineColor(kRed);
    theFit->SetLineWidth(2);
    theFit->Draw("SAME");
    theFit->Write();


    canvas->SaveAs("Fake_fit.png");
    canvas->SaveAs("Fake_fit.pdf");


    Double_t TauLegParameters[nPar];
    theFit->GetParameters(TauLegParameters);
    for (int i = 0; i < nPar; i++) {
        Fit_Value_tau->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
        Fit_Value_tau->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
    }
}

void M_FR(int WP, std::string files, std::string num, std::string denum, TH2F * Fit_Value_tau) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(5);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(5);
    cout << num.c_str() << " = " << Num_rebin->GetEntries() << "/" << Denum_rebin->GetEntries() << "  =  " << Num_rebin->GetEntries()*1.0 / Denum_rebin->GetEntries() << endl;

    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);

//    TGraph_FR->Draw("P");
//    TGraph_FR->SetName("Fake_R_12AB");
//    TGraph_FR->Write();

    fake_Fit(WP, TGraph_FR, Fit_Value_tau);

}

void Measure_Red_step1_tauFR() {

    TFile *FR_File = new TFile("FR_Tau.root", "RECREATE");
    FR_File->cd();
    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 10, 0, 10, 6, 0, 6);
    M_FR(1, "Mega.root", "FakeRate_TT_Tau_Pt_After_Loose", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau);
    M_FR(2, "Mega.root", "FakeRate_TT_Tau_Pt_After_Medium", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau);
    M_FR(3, "Mega.root", "FakeRate_TT_Tau_Pt_After_Tight", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau);
    FR_File->Write();
    FR_File->Close();
}

