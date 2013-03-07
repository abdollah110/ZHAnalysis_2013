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

//void fake_Fit(int WP, TGraphAsymmErrors * TGraph_FR) {

//void fake_Fit(int WP, TGraphAsymmErrors * TGraph_FR, TH2F * Fit_Value_emu) {

//    const int nPar = 3; // number of parameters in the fit
//    Double_t fitRangeMin = 15,
//            fitRangeMax = 80;
//
//    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);
//
//    theFit->SetParameter(0, 0.012);
//    theFit->SetParameter(1, 0.18);
//    theFit->SetParameter(2, -0.095);
//
//    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
//    canvas->SetFillColor(0);
//
//    canvas->cd(1);
//
//    TGraph_FR->SetMarkerColor(3);
//    TGraph_FR->SetMarkerSize(1.4);
//    TGraph_FR->SetMarkerStyle(20);
//    TGraph_FR->GetXaxis()->SetTitle("#tau Pt [GeV]");
//    TGraph_FR->GetXaxis()->SetTitleOffset(1);
//    TGraph_FR->GetXaxis()->SetTitleSize(0.05);
//    TGraph_FR->GetYaxis()->SetTitle("Fake Rate");
//    TGraph_FR->GetYaxis()->SetRangeUser(0, 0.1);
//    TGraph_FR->GetXaxis()->SetRangeUser(0, 100);
//    TGraph_FR->GetYaxis()->SetTitleOffset(1.3);
//    TGraph_FR->GetYaxis()->SetTitleSize(0.05);
//    TGraph_FR->Draw("PAE");
//
//    TGraph_FR->Fit("theFit", "R0");
//    theFit->SetRange(10, 100);
//    theFit->SetLineColor(kRed);
//    theFit->SetLineWidth(2);
//    theFit->Draw("SAME");
//
//
//    canvas->SaveAs("Fake_fit.png");
//    canvas->SaveAs("Fake_fit.pdf");
//
//
//    Double_t TauLegParameters[nPar];
//    theFit->GetParameters(TauLegParameters);
//    for (int i = 0; i < nPar; i++) {
//        Fit_Value_emu->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
//        Fit_Value_emu->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
//    }
//}



void M_FR(int WP, std::string files, std::string num, std::string denum, TH2F * Fit_Value_emu) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(5);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(5);
    cout << num.c_str() << " = " << Num_rebin->GetEntries() << "/" << Denum_rebin->GetEntries() << "  =  " << Num_rebin->GetEntries()*1.0 / Denum_rebin->GetEntries() << endl;

    //    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);

    Fit_Value_emu->SetBinContent(WP, 1, Num_rebin->GetEntries()*1.0 / Denum_rebin->GetEntries());
}

void Measure_Red_step2_emuFR() {

    TFile *FR_File = new TFile("FR_EMU.root", "RECREATE");
    FR_File->cd();
    TH2F * Fit_Value_emu = new TH2F("Fit_Value_emu", "Fit_Value_emu", 10, 0, 10, 6, 0, 6);
    M_FR(1, "Mega.root", "FakeRate_ET_Electron_Loose_After_0", "FakeRate_ET_Electron_Pt_Before_0", Fit_Value_emu);
    M_FR(2, "Mega.root", "FakeRate_ET_Electron_Tight_After_0", "FakeRate_ET_Electron_Pt_Before_0", Fit_Value_emu);
    M_FR(3, "Mega.root", "FakeRate_MT_Muon_Loose_After_0", "FakeRate_MT_Muon_Pt_Before_0", Fit_Value_emu);
    M_FR(4, "Mega.root", "FakeRate_MT_Muon_Tight_After_0", "FakeRate_MT_Muon_Pt_Before_0", Fit_Value_emu);
    FR_File->Write();
    FR_File->Close();
}

