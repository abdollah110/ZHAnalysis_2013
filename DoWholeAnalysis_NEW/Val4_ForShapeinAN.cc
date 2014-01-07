#include <TLatex.h>
#include <TGraph.h>

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

void M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax) {
    cout << "############################################################" << endl;
    cout << "\n\n   It is Precossing -->  " << num << "  over  " << denum << endl;
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    double ConstFR = Numerator->Integral(11, 400)*1.0 / Denumerator->Integral(11, 400);
    cout << "---------------------------------------------------------------" << endl;
    cout << "...   " << WP << "  ....  " << num.c_str() << " = " << Numerator->Integral(11, 400) << "/" << Denumerator->Integral(11, 400) << "  =  " << ConstFR << endl;
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
    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
    canvas->SetLogy();
    canvas->SetTitle("");
    TGraph_FR->GetYaxis()->SetRangeUser(.001, 5);
    TGraph_FR->GetYaxis()->SetTitle("Fake Rate");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 150);
    TGraph_FR->GetXaxis()->SetTitle("Jet Pt [GeV]");
//        TGraph_FR->GetName();
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    theFit->Draw("SAME");
    std::string outNaming = "results/__fit" + num + ".png";

    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(62);
    t.SetTextAlign(12);
    t.SetTextSize(0.045);
    t.DrawLatex(0.1, .92, "CMS Preliminary 2012");
    t.DrawLatex(0.5, .92, "#sqrt{s} = 8 TeV, L = 19.8 fb^{-1}");
    std::string lepName;
    //    cout << "++++++++++++++++++++++++++  "<<num.find("Mu") << num << endl;
    if (num.find("Mu") < 20) lepName = "Mu Loose Fake Rate";
    if (num.find("Ele") < 20) lepName = "Electron Loose Fake Rate";
    if (num.find("Tau") < 40) lepName = "Tau 3HitLoose Fake Rate";
    if (num.find("Jet_B") < 140) lepName = "Tau 3HitLoose Fake Rate (Barrel)";
    if (num.find("Jet_E") < 140) lepName = "Tau 3HitLoose Fake Rate (EndCap)";
    t.DrawLatex(0.4, .75, lepName.c_str());
//    t.DrawLatex(0.5, .80, num.c_str());
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

void Val4_ForShapeinAN() {

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);
    TH2F * Fit_Value_emu = new TH2F("Fit_Value_emu", "Fit_Value_emu", 20, 0, 20, 20, 0, 20);

    Double_t fMin = 10;
    //    Double_t fMax = 90;
    Double_t fMax = 300;

    //#########################
    //Tau Fake Rate
//    M_FR(1, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
//    //    M_FR(2, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
//    //    M_FR(3, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight", "FakeRate_TT_Tau_Pt_Before", Fit_Value_tau, fMin, fMax);
//    M_FR(4, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
//    //    M_FR(5, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
//    //    M_FR(6, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
//    M_FR(7, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    //    M_FR(8, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    //    M_FR(9, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    M_FR(10, "Line2Par", "valid_Mega.root", "FakeRate_TT_Tau_Eta_After_Loose", "FakeRate_TT_Tau_Eta_Before", Fit_Value_tau, fMin, fMax);

    //#########################
    //CloseJet Fake Rate
    M_FR(11, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_CloseJet", "FakeRate_TT_Tau_Pt_Before_CloseJet", Fit_Value_tau, fMin, fMax);
    //    M_FR(12, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_Jet", "FakeRate_TT_Tau_Pt_Before_Jet", Fit_Value_tau, fMin, fMax);
    //    M_FR(13, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_Jet", "FakeRate_TT_Tau_Pt_Before_Jet", Fit_Value_tau, fMin, fMax);
    M_FR(14, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_CloseJet_B", "FakeRate_TT_Tau_Pt_Before_CloseJet_B", Fit_Value_tau, fMin, fMax);
    //    M_FR(15, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
    //    M_FR(16, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
    M_FR(17, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_CloseJet_E", "FakeRate_TT_Tau_Pt_Before_CloseJet_E", Fit_Value_tau, fMin, fMax);
    //    M_FR(18, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
    //    M_FR(19, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    M_FR(20, "Line2Par", "valid_Mega.root", "FakeRate_TT_Tau_Eta_After_Loose_CloseJet", "FakeRate_TT_Tau_Eta_Before_CloseJet", Fit_Value_tau, fMin, fMax);

//    //#########################
//    //RefJet Fake Rate
//    M_FR(21, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_RefJet", "FakeRate_TT_Tau_Pt_Before_RefJet", Fit_Value_tau, fMin, fMax);
//    //    M_FR(22, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_RefJet", "FakeRate_TT_Tau_Pt_Before_RefJet", Fit_Value_tau, fMin, fMax);
//    //    M_FR(23, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_RefJet", "FakeRate_TT_Tau_Pt_Before_RefJet", Fit_Value_tau, fMin, fMax);
//    M_FR(24, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_RefJet_B", "FakeRate_TT_Tau_Pt_Before_RefJet_B", Fit_Value_tau, fMin, fMax);
//    //    M_FR(25, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
//    //    M_FR(26, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_B", "FakeRate_TT_Tau_Pt_Before_B", Fit_Value_tau, fMin, fMax);
//    M_FR(27, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Loose_RefJet_E", "FakeRate_TT_Tau_Pt_Before_RefJet_E", Fit_Value_tau, fMin, fMax);
//    //    M_FR(28, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Medium_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    //    M_FR(29, "Exp3Par", "valid_Mega.root", "FakeRate_TT_Tau_Pt_After_Tight_E", "FakeRate_TT_Tau_Pt_Before_E", Fit_Value_tau, fMin, fMax);
//    M_FR(30, "Line2Par", "valid_Mega.root", "FakeRate_TT_Tau_Eta_After_Loose_RefJet", "FakeRate_TT_Tau_Eta_Before_RefJet", Fit_Value_tau, fMin, fMax);

    //E-Mu Fake Rate
    fMin = 10;
    //    fMax = 90;
    fMax = 200;
//    M_FR(1, "Line2Par", "valid_Mega.root", "4objFR_Ele_NumLoose_0", "4objFR_Ele_Denum_0", Fit_Value_emu, fMin, fMax);
//    M_FR(2, "Line2Par", "valid_Mega.root", "4objFR_Ele_NumTight_0", "4objFR_Ele_Denum_0", Fit_Value_emu, fMin, fMax);
//    M_FR(3, "Line2Par", "valid_Mega.root", "4objFR_Mu_NumLoose_0", "4objFR_Mu_Denum_0", Fit_Value_emu, fMin, fMax);
//    M_FR(4, "Line2Par", "valid_Mega.root", "4objFR_Mu_NumTight_0", "4objFR_Mu_Denum_0", Fit_Value_emu, fMin, fMax);
    M_FR(5, "Exp3Par", "valid_Mega.root", "4objFR_Ele_NumLoose_0_Jet", "4objFR_Ele_Denum_0_Jet", Fit_Value_emu, fMin, fMax);
//    M_FR(6, "Exp3Par", "valid_Mega.root", "4objFR_Ele_NumTight_0_Jet", "4objFR_Ele_Denum_0_Jet", Fit_Value_emu, fMin, fMax);
    M_FR(7, "Exp3Par", "valid_Mega.root", "4objFR_Mu_NumLoose_0_Jet", "4objFR_Mu_Denum_0_Jet", Fit_Value_emu, fMin, fMax);
//    M_FR(8, "Exp3Par", "valid_Mega.root", "4objFR_Mu_NumTight_0_Jet", "4objFR_Mu_Denum_0_Jet", Fit_Value_emu, fMin, fMax);


    FR_File->Write();
    FR_File->Close();
}

