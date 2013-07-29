/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "/Users/abdollahmohammadi/Downloads/root/tmva/test/TMVAGui.C"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#endif

using namespace TMVA;

void SimpleTMVAClassificationApplication(TString myMethodList = "BDT") {
#ifdef __CINT__
    gROOT->ProcessLine(".O0"); // turn off optimization in CINT
#endif

    //---------------------------------------------------------------

    // This loads the library
    TMVA::Tools::Instance();


    std::cout << std::endl;
    std::cout << "==> Start TMVAClassificationApplication" << std::endl;

    // Select methods (don't look at this code - not of interest)


    // --------------------------------------------------------------------------------------------------

    // --- Create the Reader object

    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

    // Create a set of variables and declare them to the reader
    // - the variable names MUST corresponds in name and type to those given in the weight file(s) used

    Float_t N3_Pt, N4_Pt, N_MET;
    Float_t N3_IsoT, N4_IsoT;
    reader->AddVariable("N3_Pt", &N3_Pt);
    reader->AddVariable("N4_Pt", &N4_Pt);
    reader->AddVariable("N3_IsoT", &N3_IsoT);
    reader->AddVariable("N4_IsoT", &N4_IsoT);
    reader->AddVariable("N_MET", &N_MET);


    // Spectator variables declared in the training have to be added to the reader, too
    //    Float_t spec1, spec2;
    //    reader->AddSpectator("spec1 := var1*2", &spec1);
    //    reader->AddSpectator("spec2 := var1*3", &spec2);

    Float_t Category_cat1, Category_cat2, Category_cat3;
    //    if (Use["Category"]) {
    //        // Add artificial spectators for distinguishing categories
    //        reader->AddSpectator("Category_cat1 := var3<=0", &Category_cat1);
    //        reader->AddSpectator("Category_cat2 := (var3>0)&&(var4<0)", &Category_cat2);
    //        reader->AddSpectator("Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3);
    //    }

    // --- Book the MVA methods

    TString dir = "weights/";
    TString prefix = "TMVAClassification";

    // Book method(s)
    TString methodName = TString("BDT") + TString(" method");
    TString weightfile = dir + prefix + TString("_") + TString("BDT") + TString(".weights.xml");
    reader->BookMVA(methodName, weightfile);

    // Book output histograms
    UInt_t nbin = 100;
    //


    TH1F * histBdt = new TH1F("MVA_BDT", "MVA_BDT", nbin, -0.8, 0.8);



    // Prepare input tree (this must be replaced by your data source)
    // in this example, there is a toy tree with signal and one with background events
    // we'll later on use only the "signal" events for the test in this example.
    //
    TFile * input(0);
    TString fname = "./mvaZH.root";
    input = TFile::Open(fname); // check if file in local directory exists

    std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

    // --- Event loop

    // Prepare the event tree
    // - here the variable names have to corresponds to your tree
    // - you can use the same variables as above which is slightly faster,
    //   but of course you can use different ones and copy the values inside the event loop
    //
    std::cout << "--- Select signal sample" << std::endl;
    TTree* theTree = (TTree*) input->Get("MVATree");
    Float_t userVar1, userVar2;
    //    theTree->SetBranchAddress("var1", &userVar1);
    //    theTree->SetBranchAddress("var2", &userVar2);
    //    theTree->SetBranchAddress("var3", &var3);
    //    theTree->SetBranchAddress("var4", &var4);

    theTree->SetBranchAddress("N3_Pt", &N3_Pt);
    theTree->SetBranchAddress("N4_Pt", &N4_Pt);
    theTree->SetBranchAddress("N3_IsoT", &N3_IsoT);
    theTree->SetBranchAddress("N4_IsoT", &N4_IsoT);
    theTree->SetBranchAddress("N_MET", &N_MET);



    std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
    TStopwatch sw;
    sw.Start();
    for (Long64_t ievt = 0; ievt < theTree->GetEntries(); ievt++) {

        if (ievt % 1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

        theTree->GetEntry(ievt);


        // --- Return the MVA outputs and fill into histograms


//        cout<<reader->EvaluateMVA("BDT method")<<"\t";
        histBdt ->Fill(reader->EvaluateMVA("BDT method"));


    }

    // Get elapsed time
    sw.Stop();
    std::cout << "--- End of event loop: ";
    sw.Print();



    // --- Write histograms

    TFile *target = new TFile("TMVApp.root", "RECREATE");


    histBdt ->Write();

    target->Close();

    std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;

    delete reader;

    std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
}
