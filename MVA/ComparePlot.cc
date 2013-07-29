#include <THStack.h>
#include <string>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH1F.h"
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

void ComparePlot() {

    //    TFile *rootFile = new TFile("2012RootFiles.root");
    TFile *rootFileZH = new TFile("DYSS.root");
    TFile *rootFileZZ = new TFile("DYSS.root");
    //    TFile *rootFileRed = new TFile("preMVARed.root");
    //    TFile *rootFileData = new TFile("preMVAData.root");
    TFile *rootFileRed = new TFile("DYOS.root");
    TFile *rootFileData = new TFile("DataSS.root");
    //    TFile *rootFileData = new TFile("DYRed.root");
    const int Total_Chnl = 1;
    bool blind = false;

    int ZH125_Color = TColor::GetColor("#1C1C76");
    int ZJets_Color = TColor::GetColor("#FFCCFF");
    int ZZ_Color = TColor::GetColor("#990000");
    int Zero_Color = TColor::GetColor("#000000");


    TCanvas * MyC = new TCanvas("c1", "c12", 1);
    MyC->SetTitle("");
    MyC->SetFrameLineWidth(2);

    int rebin_ = 4;
    //###########################
    //    float maxBin = 200;
    //    float minBin = 0;
    //        TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
    //    std::string array_channel[] = {"mva_N_MET"};
    //    BG->GetXaxis()->SetTitle("MVAMet [GeV]");
    //    std::string namepng = "__Hist_MET_N.png";
    //    std::string namepdf = "__Hist_MET_N.pdf";
    //    BG->GetXaxis()->SetTitle("MVAMet [GeV]");
    //###########################
//    float maxBin = 200;
//    float minBin = 0;
//    float binSpace = maxBin / rebin_;
//    TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
//    std::string array_channel[] = {"mva_N_LT"};
//    BG->GetYaxis()->SetRangeUser(0, 0.2);
//    BG->GetXaxis()->SetRangeUser(0, 150);
//    BG->GetXaxis()->SetTitle("LT [GeV]");
//    std::string namepng = "__Hist_LT.png";
//    std::string namepdf = "__Hist_LT.pdf";
//    BG->GetXaxis()->SetTitle("LT [GeV]");
    //###########################
//    float maxBin = 1;
//    float minBin = -1;
//    float binSpace = 200 / rebin_;
//    TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
//    std::string array_channel[] = {"mva_N_IsoTau2"};
//    BG->GetYaxis()->SetRangeUser(0, 0.2);
//    BG->GetXaxis()->SetRangeUser(0, 1);
//    BG->GetXaxis()->SetTitle("LT [GeV]");
//    std::string namepng = "__Hist_Isotau2.png";
//    std::string namepdf = "__Hist_Isotau2.pdf";
//    BG->GetXaxis()->SetTitle("Isotau2 [GeV]");
    //    //###########################
    //    float maxBin = 1.;
    //    float minBin = -1.;
    //        TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
    //    std::string array_channel[] = {"mva_N_IsoTot"};
    //    BG->GetXaxis()->SetTitle("(MVAIao1 + MVAIso2)/2");
    //    std::string namepng = "__Hist_Iso_N.png";
    //    std::string namepdf = "__Hist_Iso_N.pdf";
    //    BG->GetXaxis()->SetTitle("MVAMet [GeV]");
    //    //###########################
        float maxBin = 1;
        float minBin = -1;
        int binSpace = 100 / rebin_;
        std::string array_channel[] = {"BDT"};
        TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
        BG->GetXaxis()->SetRangeUser(-1, 1);
        BG->GetYaxis()->SetRangeUser(0, .2);
        std::string namepng = "__Hist_BDT.png";
        std::string namepdf = "__Hist_BDT.pdf";
        BG->GetXaxis()->SetTitle("BDT ");

    BG->GetYaxis()->SetTitle("Normalized to Unity");
    BG->GetYaxis()->SetTitleSize(0.05);
    BG->GetYaxis()->SetTitleOffset(1.0);
    BG->GetXaxis()->SetTitleSize(0.05);
    BG->GetXaxis()->SetTitleOffset(1.0);
    BG->GetXaxis()->SetLabelSize(0.04);

    BG->SetStats(0);
    BG->SetTitle("");
    BG->Draw();

    // ********************   Backgrounds  Zjets
    TH1F * plot_Zjets = new TH1F("hi33", "Hi", binSpace, minBin, maxBin);
    std::string chnl = array_channel[0];
    TH1F * myZjet = (TH1F*) rootFileRed->Get(chnl.c_str());
    myZjet->Rebin(rebin_);
    myZjet->SetFillStyle(1001);
    myZjet->SetFillColor(ZJets_Color);
    myZjet->SetLineColor(Zero_Color);
    cout << "Zjets= " << plot_Zjets->Integral() << endl;
    myZjet->DrawNormalized("same");

    // ********************   Backgrounds ZZ
    TH1F * plot_ZZ = new TH1F("hi22", "Hi", binSpace, minBin, maxBin);
    std::string chnl = array_channel[0];
    TH1F * myZZ = (TH1F*) rootFileZZ->Get(chnl.c_str());
    myZZ->Rebin(rebin_);
    //    myZZ->SetFillStyle(3008);
    //    myZZ->SetFillColor(ZZ_Color);
    myZZ->SetLineColor(Zero_Color);
    myZZ->SetLineWidth(3);
    cout << "ZZ= " << plot_ZZ->Integral() << endl;
    myZZ->DrawNormalized("same");

    // ********************   Signal ZHTT and ZHWW
    TH1F * plot_Signal = new TH1F("hi11", "Hi", binSpace, minBin, maxBin);
    std::string chnl = array_channel[0];
    TH1F * myZH = (TH1F*) rootFileZH->Get(chnl.c_str());
    myZH->Rebin(rebin_);
    myZH->SetFillStyle(3031);
    myZH->SetFillColor(0);
    //    myZH->SetLineStyle(2);
    myZH->SetLineWidth(3);
    myZH->SetLineColor(ZH125_Color);
    cout << "signal= " << plot_Signal->Integral() << endl;
    //    myZH->DrawNormalized("same");

    // ********************   Data
    TH1F * plot_Data = new TH1F("hi2", "Hi2", binSpace, minBin, maxBin);
    std::string chnl = array_channel[0];
    TH1F * myData = (TH1F*) rootFileData->Get(chnl.c_str());
    myData->Rebin(rebin_);
    myData->SetLineWidth(3);
    myData->SetLineColor(2);
    cout << "Data= " << plot_Data->Integral() << endl;
    myData->DrawNormalized("same");


    TLegend *l = new TLegend(0.5123824, 0.6959826, 0.7004702, 0.8990228, NULL, "brNDC");
    l->SetFillColor(0);
    l->SetBorderSize(0);
    l->SetLineWidth(15);
    l->SetTextSize(.03);
    l->AddEntry(myData, "SS Data", "f");
    //    l->AddEntry(myZH, "m_{H} = 125 GeV", "f");
    l->AddEntry(myZjet, "DY OS ", "f");
    l->AddEntry(myZZ, "DY SS", "f");
    l->Draw();
    TLatex * tex = new TLatex(10, .5 * 1.02, "CMS Preliminary");
    tex->SetTextSize(0.03);
    //    tex->Draw();
    //tex = new TLatex(80, max_y*1.02, "#sqrt{s}= 7, 8 TeV, L = 24 fb ^{-1}");
    tex = new TLatex(80, .4 * 1.02, " 8 TeV, L = 19 fb ^{-1}");
    tex->SetTextSize(0.03);
    //    tex->Draw();
    tex = new TLatex(170, .4 * 1.02, "ZH#rightarrow ll#tau#tau");
    tex->SetTextSize(0.03);
    //    tex->Draw();


    MyC->Modified();
    MyC->cd();
    MyC->SetSelected(MyC);

    MyC->SaveAs(namepng.c_str());
    MyC->SaveAs(namepdf.c_str());
}
