#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include <map>
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>

void Val11_NewBGEStimation() {



    //#######################################################
    TFile * MegaFile = new TFile("valid_Mega.root");
    TTree * BG_Tree_ = (TTree*) MegaFile->Get("BG_Tree");
    int myChannel;
    int mysubChannel;
    BG_Tree_->SetBranchAddress("Channel_", &myChannel);
    BG_Tree_->SetBranchAddress("subChannel_", &mysubChannel);
    //#######################################################

    TFile *bgEstimation = new TFile("bgEstimation.root", "RECREATE");
    TH2F * numHitogram = new TH2F("numHitogram", "numHitogram", 20, 0, 20, 5, 0, 5);


    Int_t nentries_wtn = (Int_t) BG_Tree_->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        BG_Tree_->GetEntry(i);
        if (i % 50000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        numHitogram->Fill(myChannel, mysubChannel);

    }
    bgEstimation->cd();
    numHitogram->Write();
    bgEstimation->Close();
}



