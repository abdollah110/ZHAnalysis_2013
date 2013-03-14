#include "TGraph.h"
#include "TGraphErrors.h"
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <ostream>
#include <time.h>
#include <TF1.h>
#include <TPad.h>
#include <TGraphAsymmErrors.h>
#include <TPave.h>
#include <TCanvas.h>
#include <TAttAxis.h>
#include <TLatex.h>
#include <TAxis.h>
#include "TMath.h"

void myStyle_Graph(TGraph * TGraph_FR, int color) {


    TGraph_FR->SetMarkerColor(color);
    TGraph_FR->SetMarkerSize(1.4);
    TGraph_FR->SetMarkerStyle(20 + color);
    TGraph_FR->SetTitle("");
    TGraph_FR->GetXaxis()->SetTitle("#tau Pt [GeV]");
    TGraph_FR->GetXaxis()->SetTitleOffset(1);
    TGraph_FR->GetXaxis()->SetTitleSize(0.045);
    TGraph_FR->GetXaxis()->SetLabelSize(0.04);
    TGraph_FR->GetYaxis()->SetLabelSize(0.03);
    TGraph_FR->GetYaxis()->SetTitle("Fake Rate");
    TGraph_FR->GetYaxis()->SetRangeUser(0, 0.101);
    TGraph_FR->GetXaxis()->SetRangeUser(0, 90);
    TGraph_FR->GetYaxis()->SetTitleOffset(1.0);
    TGraph_FR->GetYaxis()->SetTitleSize(0.045);
}

void myStyle_Fit(TF1* theFit, int color) {
    theFit->SetRange(10, 100);
    theFit->SetLineColor(color);
    theFit->SetLineWidth(2);
}

Double_t fitFunction(Double_t *x, Double_t *par) {
    //    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
    return par[0] + par[1] * x[0];
}

TF1* fake_Fit(TGraphAsymmErrors * TGraph_FR, int color) {

    const int nPar = 3; // number of parameters in the fit
    Double_t fitRangeMin = 10,
            fitRangeMax = 80;

    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, -0.095);

    TGraph_FR->Fit("theFit", "R0");
    myStyle_Fit(theFit, color);
    return theFit;


}

TGraphAsymmErrors* M_FR(std::string files, std::string num, std::string denum, int color) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    int reb_ = 5;
    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(reb_);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(reb_);
    cout << num.c_str() << " = " << Num_rebin->GetEntries() << "/" << Denum_rebin->GetEntries() << "  =  " << Num_rebin->GetEntries()*1.0 / Denum_rebin->GetEntries() << endl;

    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);

    myStyle_Graph(TGraph_FR, color);
    return TGraph_FR;
}

void emu_FRPlots() {

    //Tau FR
    //    TGraphAsymmErrors * loose = M_FR("Mega.root", "FakeRate_TT_Tau_Pt_After_Tight", "FakeRate_TT_Tau_Pt_Before", 2);
    //    TF1 * loose_Fit = fake_Fit(loose, 2);
    //    TGraphAsymmErrors * medium = M_FR("Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_B", "FakeRate_TT_Tau_Pt_Before_B", 3);
    //    TF1 * medium_Fit = fake_Fit(medium, 3);
    //    TGraphAsymmErrors * tight = M_FR("Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_E", "FakeRate_TT_Tau_Pt_Before_E", 4);
    //    TF1 * tight_Fit = fake_Fit(tight, 4);


    //    TGraphAsymmErrors * tight = M_FR("Mega3.root", "FakeRate_TT_Tau_Rand_Loose", "FakeRate_TT_Tau_Rand", 4);
    //    TF1 * tight_Fit = fake_Fit(tight, 4);

    //Electron FR
        TGraphAsymmErrors * loose = M_FR("valid_emu.root", "FakeRate_Electron_Loose_After", "FakeRate_Electron_Before", 2);
        TF1 * loose_Fit = fake_Fit(loose, 2);
        TGraphAsymmErrors * medium = M_FR("valid_emu.root", "FakeRate_ET_Electron_Loose_After_0", "FakeRate_ET_Electron_Pt_Before_0", 3);
        TF1 * medium_Fit = fake_Fit(medium, 3);
//    TGraphAsymmErrors * loose = M_FR("valid_emu.root", "FakeRate_Muon_Loose_After", "FakeRate_Muon_Before", 2);
//    TF1 * loose_Fit = fake_Fit(loose, 2);
//    TGraphAsymmErrors * medium = M_FR("valid_emu.root", "FakeRate_MT_Muon_Loose_After_0", "FakeRate_MT_Muon_Pt_Before_0", 3);
//    TF1 * medium_Fit = fake_Fit(medium, 3);
    //
    //    //Muon FR
    //    TGraphAsymmErrors * loose = M_FR("Mega.root", "FakeRate_MT_Muon_Loose_After_0", "FakeRate_MT_Muon_Pt_Before_0", 2);
    //    TGraphAsymmErrors * medium = M_FR("Mega.root", "FakeRate_MT_Muon_Tight_After_0", "FakeRate_MT_Muon_Pt_Before_0", 3);


    TCanvas* canvas = new TCanvas("canvas", "", 600, 600);
    canvas->SetFillColor(0);
    canvas->SetTitle("0");
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);


    canvas->cd(1);
    loose->GetYaxis()->SetRangeUser(0,.2);
    loose->Draw("PAE");
    loose_Fit->Draw("SAME");
    medium->Draw("PSAME");
    medium_Fit->Draw("SAME");
    //    tight->Draw("PSAME");
    //    tight_Fit->Draw("SAME");

    TLegend *l = new TLegend(0.40, 0.60, 0.7, 0.8, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
    l->AddEntry(loose, "Tau Loose FR", "lpf");
    l->AddEntry(medium, "Tau Loose FR (|#eta_{#tau}| < 1.4)", "lpf");
    //    l->AddEntry(tight, "Tau Loose FR (|#eta_{#tau}| > 1.4)", "lpf");
    //    l->Draw();

    TLatex *text = new TLatex();
    text->SetTextSize(0.04);
    text->DrawLatex(1, 0.103, "CMS Preliminary 2012,");
    text->DrawLatex(50, 0.103, "L = 19 fb^{-1}");


    canvas->SaveAs("mue_fakerate.pdf");


}
