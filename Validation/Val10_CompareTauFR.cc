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

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * x[0] + par[2] *0;
}

void M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, Double_t fMin, Double_t fMax, TLegend *legend_) {
    cout << "############################################################" << endl;
    cout << "\n\n It is Precossing -->  " << num << "  over  " << denum << endl;
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    double ConstFR = Numerator->Integral(11, 200)*1.0 / Denumerator->Integral(11, 200);
    cout << "---------------------------------------------------------------" << endl;
    cout << num.c_str() << " = " << Numerator->Integral(11, 200) << "/" << Denumerator->Integral(11, 200) << "  =  " << ConstFR << endl;
    cout << "---------------------------------------------------------------" << endl;
    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(5);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(5);

    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);


    const int nPar = 3; // number of parameters in the fit

    TF1 * theFit = (type.compare("Exp3Par") == 0 ? new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar) : new TF1("theFit", fitFunc_Line2Par, fMin, fMax, nPar));

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, 0);

    TGraph_FR->Fit("theFit", "R0");

    //############

    TGraph_FR->GetYaxis()->SetRangeUser(0, .1);
    TGraph_FR->GetYaxis()->SetTitle("fake rate");
    TGraph_FR->GetXaxis()->SetRangeUser(-3, 150);
    TGraph_FR->GetXaxis()->SetTitle("Jet Pt [GeV]");
    TGraph_FR->Draw("SAMEPAE");
    theFit->SetLineColor(WP);
    theFit->SetLineWidth(3.5);
    theFit->Draw("SAME");
    std::string str2 = files.substr(11, 22);
    legend_->AddEntry(theFit, str2.c_str(), "l");
    legend_->Draw();

}

void Val10_CompareTauFR() {

    TCanvas * canvas = new TCanvas("canvas", "", 800, 600);
    //    canvas = TCanvas("canvas", "", 600, 600);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    canvas->SetFillColor(0);
    canvas->SetTitle("qqqqqq");
    canvas->SetName("");
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    Double_t fMin = 10;
    Double_t fMax = 150;

    //#########################
    //Tau Fake Rate
    TFile *inputFile = new TFile("loose3Hit.root");

    TH1D *Numerator = (TH1D*) inputFile->Get("FakeRate_TT_Tau_Pt_After_Loose_CloseJet");
    TH1D *Denumerator = (TH1D*) inputFile->Get("FakeRate_TT_Tau_Pt_Before_CloseJet");

    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(5);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(5);
    cout << "***************   " << Num_rebin->Integral() << endl;
    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);
    const int nPar = 3; // number of parameters in the fit

    TF1 * theFit = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, 0);

    TGraph_FR->Fit("theFit", "R0");

    //############

    theFit->GetYaxis()->SetRangeUser(0, .1);
    theFit->GetYaxis()->SetTitle("fake rate");
    theFit->GetYaxis()->SetTitleSize(.05);
    theFit->GetXaxis()->SetRangeUser(0, 150);
    theFit->GetXaxis()->SetTitle("Jet Pt [GeV]");
    theFit->GetXaxis()->SetTitleSize(.05);
    TGraph_FR->Draw("PAE");
    theFit->SetLineColor(0);
    theFit->Draw();

    TLegend * legend_ = new TLegend(0.4, 0.6, 0.9, 0.9);
    legend_->SetFillColor(0);
    legend_->SetBorderSize(0);
    //    legend_->Draw();


    M_FR(1, "Exp3Par", "loose3Hit.root", "FakeRate_TT_Tau_Pt_After_Loose", "FakeRate_TT_Tau_Pt_Before", fMin, fMax, legend_);
    M_FR(2, "Exp3Par", "looseMVA.root", "FakeRate_TT_Tau_Pt_After_Loose", "FakeRate_TT_Tau_Pt_Before", fMin, fMax, legend_);
//    M_FR(3, "Exp3Par", "valid_Mega_25GevPt1_25GevPt2_0LT.root", "FakeRate_TT_Tau_Pt_After_Loose_CloseJet", "FakeRate_TT_Tau_Pt_Before_CloseJet", fMin, fMax, legend_);


}

