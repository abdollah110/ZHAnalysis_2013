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

void TotalPlot() {

    TFile *rootFileZH = new TFile("llltMVAZH.root");
    TFile *rootFileZZ = new TFile("llltMVAZZ.root");
    TFile *rootFileData = new TFile("llltMVAData.root");

    //    TFile *rootFileRed = new TFile("llltMVARed.root");
    TFile *rootFileRed = new TFile("DYSS.root");
    //        TFile *rootFileRed = new TFile("DYRedSS.root");


    const int Total_Chnl = 1;
    bool blind = false;

    int ZH125_Color = TColor::GetColor("#1C1C76");
    int ZJets_Color = TColor::GetColor("#FFCCFF");
    int ZZ_Color = TColor::GetColor("#990000");
    int Zero_Color = TColor::GetColor("#000000");


    TCanvas * MyC = new TCanvas("c1", "c12", 1);
    MyC->SetTitle("");
    MyC->SetLogy();
    MyC->SetFrameLineWidth(2);

    THStack * hs_ZZ = new THStack("hs_ZZ", "200");


    int rebin_ = 2;
    //###########################
    //    float maxBin = 200;
    //    float minBin = 0;
    //    TH1F * BG = new TH1F("BG", "", maxBin / rebin_, minBin, maxBin);
    //    std::string array_channel[] = {"mva_N_MET"};
    //    BG->GetXaxis()->SetTitle("MVAMet [GeV]");
    //    std::string namepng = "__Hist_MET_N.png";
    //    std::string namepdf = "__Hist_MET_N.pdf";
    //###########################
    //        float maxBin = 200;
    //        float minBin = 0;
    //        TH1F * BG = new TH1F("BG", "", maxBin/rebin_, minBin, maxBin);
    //        std::string array_channel[] = {"mva_N_LT"};
    //        BG->GetXaxis()->SetTitle("LT [GeV]");
    //        std::string namepng = "__Hist_LT.png";
    //        std::string namepdf = "__Hist_LT.pdf";
    //    //###########################
    //    float maxBin = 1.;
    //    float minBin = -1.;
    //    TH1F * BG = new TH1F("BG", "", 40, minBin, maxBin);
    //    std::string array_channel[] = {"mva_N_IsoTot"};
    //    BG->GetXaxis()->SetTitle("(MVAIao1 + MVAIso2)/2");
    //    std::string namepng = "__Hist_Iso_N.png";
    //    std::string namepdf = "__Hist_Iso_N.pdf";
    //    //###########################
    //    float maxBin = 1;
    //    float minBin = -1;
    //    int binSpace = 200 / rebin_;
    //        float maxBin = 200;
    //        float minBin = 0;
    //        int binSpace = 200/rebin_;
    float maxBin = 0.8;
    float minBin = -0.8;
    int binSpace = 100 / rebin_;
    TH1F * BG = new TH1F("BG", "", binSpace, minBin, maxBin);
    //    std::string array_channel[] = {"mva_N_LT"};
    std::string array_channel[] = {"BDT"};
    BG->GetXaxis()->SetTitle("BDT");
    //        BG->GetXaxis()->SetRangeUser(0, 1);
    std::string namepng = "__Hist_BDT_N.png";
    std::string namepdf = "__Hist_BDT_N.pdf";

    //Y axix
    BG->GetYaxis()->SetTitle("Events/5 GeV");
    BG->GetYaxis()->SetTitleSize(0.05);
    BG->GetYaxis()->SetTitleOffset(1.0);
    //X axis
    BG->GetXaxis()->SetTitleSize(0.05);
    BG->GetXaxis()->SetTitleOffset(1.0);
    BG->GetXaxis()->SetLabelSize(0.04);

    BG->SetStats(0);
    BG->SetTitle("");
    BG->Draw();

    // ********************   Signal ZHTT and ZHWW
    TH1F * plot_Signal = new TH1F("hi33", "Hi", binSpace, minBin, maxBin);
    for (int k = 0; k < Total_Chnl; k++) {
        std::string chnl = array_channel[k];
        TH1F * myZH = (TH1F*) rootFileZH->Get(chnl.c_str());
        myZH->Rebin(rebin_);
        plot_Signal->Add(myZH);
    }
    plot_Signal->SetFillStyle(0);
    plot_Signal->SetFillColor(0);
    plot_Signal->SetLineStyle(2);
    plot_Signal->SetLineWidth(2);
    plot_Signal->SetLineColor(ZH125_Color);
    plot_Signal->Scale(19240 * 0.00251 / 100000);
    hs_ZZ->Add(plot_Signal);
    cout << "signal= " << plot_Signal->Integral() << endl;


    // ********************   Backgrounds ZZ
    TH1F * plot_ZZ = new TH1F("hi", "Hi", binSpace, minBin, maxBin);
    for (int k = 0; k < Total_Chnl; k++) {
        std::string chnl = array_channel[k];
        TH1F * myZZ = (TH1F*) rootFileZZ->Get(chnl.c_str());
        myZZ->Rebin(rebin_);
        plot_ZZ->Add(myZZ);
    }
    plot_ZZ->SetFillStyle(1001);
    plot_ZZ->SetFillColor(ZZ_Color);
    plot_ZZ->SetLineColor(Zero_Color);
    plot_ZZ->Scale(19240 * 0.130 / 4989540);
    hs_ZZ->Add(plot_ZZ);
    cout << "Total_Chnl= " << Total_Chnl << "\n";
    cout << "ZZ= " << plot_ZZ->Integral() << endl;


    // ********************   Backgrounds  Zjets
    TH1F * plot_Zjets = new TH1F("hii", "Hii", binSpace, minBin, maxBin);
    for (int k = 0; k < Total_Chnl; k++) {
        std::string chnl = array_channel[k];
        TH1F * myZjet = (TH1F*) rootFileRed->Get(chnl.c_str());
        myZjet->Rebin(rebin_);
        plot_Zjets->Add(myZjet);
    }
    plot_Zjets->SetFillStyle(1001);
    plot_Zjets->SetFillColor(ZJets_Color);
    plot_Zjets->SetLineColor(Zero_Color);
    plot_Zjets->Scale(3527.4 / plot_Zjets->Integral());
    hs_ZZ->Add(plot_Zjets);
    cout << "Zjets= " << plot_Zjets->Integral() << endl;



    // ********************   Data
    TH1F * plot_Data = new TH1F("hi2", "Hi2", binSpace, minBin, maxBin);
    for (int k = 0; k < Total_Chnl; k++) {
        std::string chnl = array_channel[k];
        TH1F * myData = (TH1F*) rootFileData->Get(chnl.c_str());
        myData->Rebin(rebin_);
        plot_Data->Add(myData);
        cout << "NewData= " << myData->Integral() << endl;
    }
    plot_Data->SetMarkerStyle(20);
    plot_Data->SetMarkerSize(1.1);
    plot_Data->SetLineWidth(2);
    cout << "Data= " << plot_Data->Integral() << endl;

    hs_ZZ->Draw("histsame");
    if (!blind)
        plot_Data->Draw("E1Psame");


    //  *******************
    double max_y = plot_Data->GetBinContent(plot_Data->GetMaximumBin())*2;
    BG->GetYaxis()->SetRangeUser(0.01, max_y);

    TLegend *l = new TLegend(0.7123824, 0.6959826, 0.9004702, 0.8990228, NULL, "brNDC");
    l->SetFillColor(0);
    l->SetBorderSize(0);
    l->SetLineWidth(15);
    l->SetTextSize(.03);
    l->AddEntry(plot_Data, "Observed ", "p");
    l->AddEntry(plot_Signal, "m_{H} = 125 GeV", "f");
    l->AddEntry(plot_Zjets, "Non Prompt ", "f");
    l->AddEntry(plot_ZZ, "ZZ", "f");
    l->Draw();
    TLatex * tex = new TLatex(10, max_y * 1.02, "CMS Preliminary");
    tex->SetTextSize(0.03);
    tex->Draw();
    //tex = new TLatex(80, max_y*1.02, "#sqrt{s}= 7, 8 TeV, L = 24 fb ^{-1}");
    tex = new TLatex(80, max_y * 1.02, " 8 TeV, L = 19 fb ^{-1}");
    tex->SetTextSize(0.03);
    tex->Draw();
    tex = new TLatex(170, max_y * 1.02, "ZH#rightarrow ll#tau#tau");
    tex->SetTextSize(0.03);
    tex->Draw();


    MyC->Modified();
    MyC->cd();
    MyC->SetSelected(MyC);

    //    MyC->SaveAs(namepng.c_str());
    MyC->SaveAs(namepdf.c_str());
}
