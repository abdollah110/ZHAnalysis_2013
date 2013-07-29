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

void makeBlind2() {

    TFile * PPP = new TFile("PPP.root","RECREATE");
    TH1F * plot_DataBBB = new TH1F("BDT","",100, -.8,.8);
    TFile *rootFileData = new TFile("postMVAData.root");

    // ********************   Data
    TH1F * myData = (TH1F*) rootFileData->Get("BDT");
    cout <<" nn   "<< myData->GetNbinsX();
    for (int y = 0; y < myData->GetNbinsX(); y++) {
        if (y < 45) {
            plot_DataBBB->SetBinContent(y, myData->GetBinContent(y));
        } else {
            plot_DataBBB->SetBinContent(y, 0);
        }
    }
    plot_DataBBB->Draw();
    PPP->Write();
    
}
