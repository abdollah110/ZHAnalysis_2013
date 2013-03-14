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

void M_FR(std::string files, std::string num, std::string denum) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());


    cout << num.c_str() << " = " << Numerator->GetEntries() << "  /  " << Denumerator->GetEntries() << " division is =     " << Numerator->GetEntries()*1.0 / Denumerator->GetEntries() << endl;

}

void XCheck() {

    M_FR("Mega.root", "FakeRate_EEET_apply_pp", "FakeRate_MMET_apply_pp");
    M_FR("Mega.root", "FakeRate_EEET_apply_pp", "FakeRate_MMET_apply_pp");
    cout << endl;
    M_FR("Mega.root", "FakeRate_EEMT_apply_pp", "FakeRate_MMMT_apply_pp");
    M_FR("Mega.root", "FakeRate_EEMT_apply_pp", "FakeRate_MMMT_apply_pp");
    cout << endl;



    M_FR("Mega.root", "MMTT_FF_11", "FakeRate_MMTT_apply_ff");
    M_FR("Mega.root", "MMTT_FP_21", "FakeRate_MMTT_apply_fp");
    M_FR("Mega.root", "MMTT_PF_31", "FakeRate_MMTT_apply_pf");
    cout << endl;

    M_FR("Mega.root", "MMET_FF_12", "FakeRate_MMET_apply_ff");
    M_FR("Mega.root", "MMET_FP_22", "FakeRate_MMET_apply_fp");
    M_FR("Mega.root", "MMET_PF_32", "FakeRate_MMET_apply_pf");
    cout << endl;

    M_FR("Mega.root", "MMMT_FF_13", "FakeRate_MMMT_apply_ff");
    M_FR("Mega.root", "MMMT_FP_23", "FakeRate_MMMT_apply_fp");
    M_FR("Mega.root", "MMMT_PF_33", "FakeRate_MMMT_apply_pf");
    cout << endl;

    M_FR("Mega.root", "MMME_FF_14", "FakeRate_MMME_apply_ff");
    M_FR("Mega.root", "MMME_FP_24", "FakeRate_MMME_apply_fp");
    M_FR("Mega.root", "MMME_PF_34", "FakeRate_MMME_apply_pf");
    cout << endl;


    M_FR("Mega.root", "EETT_FF_15", "FakeRate_EETT_apply_ff");
    M_FR("Mega.root", "EETT_FP_25", "FakeRate_EETT_apply_fp");
    M_FR("Mega.root", "EETT_PF_35", "FakeRate_EETT_apply_pf");
    cout << endl;

    M_FR("Mega.root", "EEMT_FF_16", "FakeRate_EEMT_apply_ff");
    M_FR("Mega.root", "EEMT_FP_26", "FakeRate_EEMT_apply_fp");
    M_FR("Mega.root", "EEMT_PF_36", "FakeRate_EEMT_apply_pf");
    cout << endl;

    M_FR("Mega.root", "EEET_FF_17", "FakeRate_EEET_apply_ff");
    M_FR("Mega.root", "EEET_FP_27", "FakeRate_EEET_apply_fp");
    M_FR("Mega.root", "EEET_PF_37", "FakeRate_EEET_apply_pf");
    cout << endl;

    M_FR("Mega.root", "EEEM_FF_18", "FakeRate_EEEM_apply_ff");
    M_FR("Mega.root", "EEEM_FP_28", "FakeRate_EEEM_apply_fp");
    M_FR("Mega.root", "EEEM_PF_38", "FakeRate_EEEM_apply_pf");
    cout << endl;

    M_FR("Mega.root", "ET_Electron_Pt_Before_0", "FakeRate_ET_Electron_Pt_Before_0");
    M_FR("Mega.root", "ET_Electron_Loose_After_0", "FakeRate_ET_Electron_Loose_After_0");
    M_FR("Mega.root", "ET_Electron_Tight_After_0", "FakeRate_ET_Electron_Tight_After_0");
    cout << endl;

    M_FR("Mega.root", "MT_Muon_Pt_Before_0", "FakeRate_MT_Muon_Pt_Before_0");
    M_FR("Mega.root", "MT_Muon_Loose_After_0", "FakeRate_MT_Muon_Loose_After_0");
    M_FR("Mega.root", "MT_Muon_Tight_After_0", "FakeRate_MT_Muon_Tight_After_0");
    cout << endl;


}

