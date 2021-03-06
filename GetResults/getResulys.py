#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "abdollahmohammadi"
__date__ = "$Mar 11, 2013 11:01:33 AM$"

    const char * arrayff[] = {, "FakeRate_MMMT_apply_ff", "FakeRate_MMME_apply_ff", "FakeRate_EETT_apply_ff", "FakeRate_EEMT_apply_ff", "FakeRate_EEET_apply_ff", "FakeRate_EEEM_apply_ff"};
    const char * arrayfp[] = {, "FakeRate_MMMT_apply_fp", "FakeRate_MMME_apply_fp", "FakeRate_EETT_apply_fp", "FakeRate_EEMT_apply_fp", "FakeRate_EEET_apply_fp", "FakeRate_EEEM_apply_fp"};
    const char * arraypf[] = {, , "FakeRate_MMMT_apply_pf", "FakeRate_MMME_apply_pf", "FakeRate_EETT_apply_pf", "FakeRate_EEMT_apply_pf", "FakeRate_EEET_apply_pf", "FakeRate_EEEM_apply_pf"};
    TH2F * Chnl_estimate = new TH2F("Chnl_estimate", "Chnl_estimate", 10, 0, 10, 10, 0, 10);
    TH2F * Chnl_event = new TH2F("Chnl_event", "Chnl_event", 10, 0, 10, 10, 0, 10);

    Get_FitParameter(1, "tauTight", 1, "tauTight", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
    Get_FitParameter(2, "tauMedium", 1, "eleTight", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff", "FakeRate_MMET_apply_fp", "FakeRate_MMET_apply_pf");
    Get_FitParameter(3, "tauMedium", 1, "muTight", 0, Chnl_estimate, Chnl_event,);
    Get_FitParameter(4, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(5, "tauTight", 1, "tauTight", 1, Chnl_estimate, Chnl_event);
    Get_FitParameter(6, "tauMedium", 1, "muTight", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(7, "tauMedium", 1, "eleTight", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(8, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event);

Channels = {
    1:{'MMTT', "tauTight", 1, "tauTight", 1},
    2:{'MMET', "tauMedium", 1, "eleTight", 0},
    3:{'MMMT', "tauMedium", 1, "muTight", 0},
    4:{'MMME', "eleLoose", 0, "muLoose", 0},
    5:{'EETT', "tauTight", 1, "tauTight", 1},
    6:{'EEMT', "tauMedium", 1, "muTight", 0},
    7:{'EEET', "tauMedium", 1, "eleTight", 0},
    8:{'EEEM', "eleLoose", 0, "muLoose", 0}
}

if __name__ == "__main__":
    print "Hello World";

    Double_t fitFunction(Double_t x, Double_t par0, Double_t par1, Double_t par2, bool isPtDependent) {
    if (isPtDependent)
        return par0 + par1 * (TMath::Exp(par2 * x));
    else
        return par0;
}

TFile * PrintResults(TH2F * Chnl_estimate, TH2F * Chnl_event) {

    TFile * OutFile = new TFile("Reducible.root", "RECREATE");
    OutFile- > cd();
    TH1F * histo_Reducible = new TH1F("histo_Reducible", "histo_Reducible", 10, 0, 10);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    cout << "\n\n" << "\\begin{table}[htbp]" << endl;
    cout << "\\centering" << endl;
    cout << "\\caption{ events}" << endl;
    cout << "\\label{table:events}" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c| }" << endl;
    cout << "\\hline" << endl;
    cout << " channel & Cat0 & Cat1 & Cat2 &  1+2-0" << " \\\\" << endl;
    cout << "\\hline" << endl;

    char * array[8] = {"mmtt", "mmet", "mmmt", "mmme", "eett", "eemt", "eeet", "eeem"};

    float Total_Est = 0;
    for (int j=1; j <= 8; j +  + ) {
        cout << array[j - 1] << "&";
        double cen_val = 0;
        for (int i=1; i <= 3; i +  + ) {
            cout << Chnl_estimate- > GetBinContent(i + 1, j + 1) << "(" << int(Chnl_event- > GetBinContent(i + 1, j + 1)) << ")" << "&";
        }
        cen_val = Chnl_estimate- > GetBinContent(3, j + 1) + Chnl_estimate- > GetBinContent(4, j + 1) - Chnl_estimate- > GetBinContent(2, j + 1);
        cout << cen_val << " \\\\ " << endl;
        Total_Est += cen_val;
        histo_Reducible- > SetBinContent(j, cen_val);
    }
    cout << "\\hline" << "\n\\end{tabular}" << "\n\\end{table}" << "\n\n\n";
    cout << "Total Reducible BG =  " << Total_Est << endl;

    OutFile- > Write();
    return OutFile;

}

void Measure(int num, std::vector < float > p, bool p_ptDep, std::vector < float > q, bool q_ptDep, TH2F * Chnl_estimate, TH2F * Chnl_event) {
    TFile * MegaFile = new TFile("Mega.root");

    TH2D * Hist2_FF = (TH2D * ) MegaFile- > Get(arrayff[num - 1]);
    TH2D * Hist2_FP = (TH2D * ) MegaFile- > Get(arrayfp[num - 1]);
    TH2D * Hist2_PF = (TH2D * ) MegaFile- > Get(arraypf[num - 1]);

    for (int i=10; i < Hist2_FF- > GetNbinsX(); i +  + ) {
        for (int j=10; j < Hist2_FF- > GetNbinsY(); j +  + ) {
            double Value = Hist2_FF- > GetBinContent(i + 1, j + 1);
            double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
            double FrateY = fitFunction(0.5 + j, q[0], q[1], q[2], q_ptDep);
            double Frate = Value * (FrateX * FrateY) / ((1 - FrateX) * (1 - FrateY));
            Chnl_estimate- > Fill(1, num, Frate);
            Chnl_event- > Fill(1, num, Value);
        }
    }
    for (int i=10; i < Hist2_FP- > GetNbinsX(); i +  + ) {
        double Value = Hist2_FP- > GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, p[0], p[1], p[2], p_ptDep);
        double Frate = Value * (FrateX) / (1 - FrateX);
        Chnl_estimate- > Fill(2, num, Frate);
        Chnl_event- > Fill(2, num, Value);
    }
    for (int i=10; i < Hist2_PF- > GetNbinsX(); i +  + ) {
        double Value = Hist2_PF- > GetBinContent(i + 1);
        double FrateX = fitFunction(0.5 + i, q[0], q[1], q[2], q_ptDep);
        double Frate = Value * (FrateX) / (1 - FrateX);
        Chnl_estimate- > Fill(3, num, Frate);
        Chnl_event- > Fill(3, num, Value);
    }

}

void Get_FitParameter(int num, std::string firstLeg, bool is_ptDep1, std::string secondLeg, bool is_ptDep2, TH2F * Chnl_estimate, TH2F * Chnl_event) {
    TFile * tau_fr = new TFile("FR_Tau.root");
    TH2F * Fit_Value_tau = (TH2F * ) tau_fr- > Get("Fit_Value_tau");
    TFile * emu_fr = new TFile("FR_EMU.root");
    TH2F * Fit_Value_emu = (TH2F * ) emu_fr- > Get("Fit_Value_emu");

    std::vector < float > leg1;
    std::vector < float > leg2;
    leg1.clear();
    leg2.clear();

    // first leg
    if (firstLeg == "tauTight")
        for (int i=1; i <= 3; i +  + ) leg1.push_back(Fit_Value_tau- > GetBinContent(3, 2 * (i - 1) + 1));
    if (firstLeg == "tauMedium")
        for (int i=1; i <= 3; i +  + ) leg1.push_back(Fit_Value_tau- > GetBinContent(2, 2 * (i - 1) + 1));
    if (firstLeg == "tauLoose")
        for (int i=1; i <= 3; i +  + ) leg1.push_back(Fit_Value_tau- > GetBinContent(1, 2 * (i - 1) + 1));
    if (firstLeg == "eleLoose")
        for (int i=1; i <= 3; i +  + ) leg1.push_back(Fit_Value_emu- > GetBinContent(1, 1));
    // second leg
    if (secondLeg == "tauTight")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_tau- > GetBinContent(3, 2 * (i - 1) + 1));
    if (secondLeg == "tauMedium")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_tau- > GetBinContent(2, 2 * (i - 1) + 1));
    if (secondLeg == "tauLoose")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_tau- > GetBinContent(1, 2 * (i - 1) + 1));
    if (secondLeg == "eleLoose")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_emu- > GetBinContent(1, 1));
    if (secondLeg == "eleTight")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_emu- > GetBinContent(2, 1));
    if (secondLeg == "muLoose")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_emu- > GetBinContent(3, 1));
    if (secondLeg == "muTight")
        for (int i=1; i <= 3; i +  + ) leg2.push_back(Fit_Value_emu- > GetBinContent(4, 1));

    Measure(num, leg1, is_ptDep1, leg2, is_ptDep2, Chnl_estimate, Chnl_event);
}

Measure_Red_step3_Total() {
    const char * arrayff[] = {, "FakeRate_MMMT_apply_ff", "FakeRate_MMME_apply_ff", "FakeRate_EETT_apply_ff", "FakeRate_EEMT_apply_ff", "FakeRate_EEET_apply_ff", "FakeRate_EEEM_apply_ff"};
    const char * arrayfp[] = {, "FakeRate_MMMT_apply_fp", "FakeRate_MMME_apply_fp", "FakeRate_EETT_apply_fp", "FakeRate_EEMT_apply_fp", "FakeRate_EEET_apply_fp", "FakeRate_EEEM_apply_fp"};
    const char * arraypf[] = {, , "FakeRate_MMMT_apply_pf", "FakeRate_MMME_apply_pf", "FakeRate_EETT_apply_pf", "FakeRate_EEMT_apply_pf", "FakeRate_EEET_apply_pf", "FakeRate_EEEM_apply_pf"};
    TH2F * Chnl_estimate = new TH2F("Chnl_estimate", "Chnl_estimate", 10, 0, 10, 10, 0, 10);
    TH2F * Chnl_event = new TH2F("Chnl_event", "Chnl_event", 10, 0, 10, 10, 0, 10);

    Get_FitParameter(1, "tauTight", 1, "tauTight", 1, Chnl_estimate, Chnl_event, "FakeRate_MMTT_apply_ff", "FakeRate_MMTT_apply_fp", "FakeRate_MMTT_apply_pf");
    Get_FitParameter(2, "tauMedium", 1, "eleTight", 0, Chnl_estimate, Chnl_event, "FakeRate_MMET_apply_ff", "FakeRate_MMET_apply_fp", "FakeRate_MMET_apply_pf");
    Get_FitParameter(3, "tauMedium", 1, "muTight", 0, Chnl_estimate, Chnl_event,);
    Get_FitParameter(4, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(5, "tauTight", 1, "tauTight", 1, Chnl_estimate, Chnl_event);
    Get_FitParameter(6, "tauMedium", 1, "muTight", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(7, "tauMedium", 1, "eleTight", 0, Chnl_estimate, Chnl_event);
    Get_FitParameter(8, "eleLoose", 0, "muLoose", 0, Chnl_estimate, Chnl_event);

    PrintResults(Chnl_estimate, Chnl_event);
}
