// The code to do teh ZH totautau Analysis
// to make it excutable run: ./Make.sh ZH_Analysis.cc

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"


//needed to make the executable
#include "interface/myevent.h"
#include "interface/LinkDef.h"
#include "interface/myobject.h"

// needed header files
#include "interface/makeHisto.h"
#include "interface/zh_Auxiliary.h"
#include "interface/Leptons_PreSelection.h"
#include "interface/zh_Corrector.h"
#include "interface/zh_Trigger.h"
#include "interface/zh_Tree.h"
#include "interface/Leptons_IdIso.h"
#include "interface/LumiReweightingStandAlone.h"

int main(int argc, char** argv) {

    using namespace std;
    //define myevent class
    myevent *m = new myevent;
    //define 1D and 2D histogram
    myMap1 = new map<string, TH1F*>();
    myMap2 = new map<string, TH2F*>();

    cout << "\n######################### Analysis is initializing ####################################### " << endl;

    //#################################################################################################
    //################# First Argument, Data or MC, which type of data or MC    #######################
    //#################################################################################################

    string status_sample = *(argv + 1);
    cout << "*** First Argument, Data or MC, which type of data or MC ***" << endl;
    cout << status_sample.c_str() << endl;

    bool mc12 = (status_sample.compare("mc12") == 0 ? true : false);
    bool mc11 = (status_sample.compare("mc11") == 0 ? true : false);
    bool data12 = (status_sample.compare("data12") == 0 ? true : false);
    bool data11 = (status_sample.compare("data11") == 0 ? true : false);
    if (!(mc12 || mc11 || data12 || data11))
        cout << "xxxxx Error, please slecet between: mc12 || mc11 || data12 || data11 " << endl;

    //#################################################################################################
    //############## Second Argument, Run over just di-ele, just di-mu (for data) or total (for MC) ###
    //#################################################################################################

    string status_type = *(argv + 2);
    cout << "**** Second Argument, Run over just di-ele, just di-mu (for data) or total (for MC) ***" << endl;
    cout << status_type.c_str() << endl;
    bool is_tot = (status_type.compare("Tot") == 0 ? true : false);
    bool is_ele = (status_type.compare("Ele") == 0 ? true : false);
    bool is_mu = (status_type.compare("Mu") == 0 ? true : false);
    if (!(is_tot || is_ele || is_mu))
        cout << "xxxxx Error, please slecet between: Tot || Ele || Mu " << endl;

    //#################################################################################################
    //############## Third anad Forth Argument,   OutPut Name/ Input Files                         ########################
    //#################################################################################################

    string out = *(argv + 3);

    std::vector<string> fileNames;
    for (int f = 4; f < argc; f++) {
        fileNames.push_back(*(argv + f));
        // printing the input NAME
        cout << "\n INPUT NAME IS:   " << fileNames[f - 4] << "\t";
    }
    //#################################################################################################
    //############## defining an out_file name need on the given argument  information  ###############
    //#################################################################################################

    string outname = status_sample + "_" + status_type + "_" + out;
    //PRINTING THE OUTPUT name
    cout << "\n\n\n OUTPUT NAME IS:    " << outname << endl;
    TFile *fout = TFile::Open(outname.c_str(), "RECREATE");


    //#################################################################################################
    //############## initializing the PU correction                                    ###############
    //#################################################################################################

    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("root/Summer12_PU.root", "root/dataPileUpHistogram_True_2012.root", "mcPU", "pileup");
    reweight::LumiReWeighting* LumiWeights_11;
    LumiWeights_11 = new reweight::LumiReWeighting("root/Fall11_PU_observed.root", "root/dataPileUpHistogram_Observed_2011.root", "mcPU", "pileup");

    //#################################################################################################
    //############## defining Tree Branches Filled via fillTree function                ###############
    //#################################################################################################

    TTree *Run_Tree = new TTree("RLE_tree", "RLE_tree");
    //    To force a memory-resident Tree
    Run_Tree->SetDirectory(0);

    Run_Tree->Branch("Channel", &Channel, "Channel/I");
    Run_Tree->Branch("Run", &Run, "Run/I");
    Run_Tree->Branch("Lumi", &Lumi, "Lumi/I");
    Run_Tree->Branch("Event", &Event, "Event/I");
    Run_Tree->Branch("IMass", &IMass, "IMass/F");
    Run_Tree->Branch("ZMass", &ZMass, "ZMass/F");
    Run_Tree->Branch("HMass", &HMass, "HMass/F");
    Run_Tree->Branch("met", &met, "met/F");
    Run_Tree->Branch("metPhi", &metPhi, "metPhi/F");
    Run_Tree->Branch("covMet11", &covMet11, "covMet11/F");
    Run_Tree->Branch("covMet12", &covMet12, "covMet12/F");
    Run_Tree->Branch("covMet21", &covMet21, "covMet21/F");
    Run_Tree->Branch("covMet22", &covMet22, "covMet22/F");
    Run_Tree->Branch("num_PV", &num_PV, "num_PV/I");
    Run_Tree->Branch("num_bjet", &num_bjet, "num_bjet/I");
    Run_Tree->Branch("eff_Correction", &eff_Correction, "eff_Correction/F");
    Run_Tree->Branch("pu_Weight", &pu_Weight, "pu_Weight/F");

    Run_Tree->Branch("l1M", &l1M, "l1M/F");
    Run_Tree->Branch("l1E", &l1E, "l1E/F");
    Run_Tree->Branch("l1Px", &l1Px, "l1Px/F");
    Run_Tree->Branch("l1Py", &l1Py, "l1Py/F");
    Run_Tree->Branch("l1Pz", &l1Pz, "l1Pz/F");
    Run_Tree->Branch("l1Pt", &l1Pt, "l1Pt/F");
    Run_Tree->Branch("l1Eta", &l1Eta, "l1Eta/F");
    Run_Tree->Branch("l1Phi", &l1Phi, "l1Phi/F");
    Run_Tree->Branch("l1Charge", &l1Charge, "l1Charge/F");
    Run_Tree->Branch("l1_muId", &l1_muId, "l1_muId/F");
    Run_Tree->Branch("l1_muIso", &l1_muIso, "l1_muIso/F");
    Run_Tree->Branch("l1_eleId", &l1_eleId, "l1_eleId/F");
    Run_Tree->Branch("l1_eleIso", &l1_eleIso, "l1_eleIso/F");
    Run_Tree->Branch("l1_eleMVANonTrg", &l1_eleMVANonTrg, "l1_eleMVANonTrg/F");
    Run_Tree->Branch("l1_eleNumHit", &l1_eleNumHit, "l1_eleNumHit/F");

    Run_Tree->Branch("l2M", &l2M, "l2M/F");
    Run_Tree->Branch("l2E", &l2E, "l2E/F");
    Run_Tree->Branch("l2Px", &l2Px, "l2Px/F");
    Run_Tree->Branch("l2Py", &l2Py, "l2Py/F");
    Run_Tree->Branch("l2Pz", &l2Pz, "l2Pz/F");
    Run_Tree->Branch("l2Pt", &l2Pt, "l2Pt/F");
    Run_Tree->Branch("l2Eta", &l2Eta, "l2Eta/F");
    Run_Tree->Branch("l2Phi", &l2Phi, "l2Phi/F");
    Run_Tree->Branch("l2Charge", &l2Charge, "l2Charge/F");
    Run_Tree->Branch("l2_muId", &l2_muId, "l2_muId/F");
    Run_Tree->Branch("l2_muIso", &l2_muIso, "l2_muIso/F");
    Run_Tree->Branch("l2_eleId", &l2_eleId, "l2_eleId/F");
    Run_Tree->Branch("l2_eleIso", &l2_eleIso, "l2_eleIso/F");
    Run_Tree->Branch("l2_eleMVANonTrg", &l2_eleMVANonTrg, "l2_eleMVANonTrg/F");
    Run_Tree->Branch("l2_eleNumHit", &l2_eleNumHit, "l2_eleNumHit/F");

    Run_Tree->Branch("l3M", &l3M, "l3M/F");
    Run_Tree->Branch("l3E", &l3E, "l3E/F");
    Run_Tree->Branch("l3Px", &l3Px, "l3Px/F");
    Run_Tree->Branch("l3Py", &l3Py, "l3Py/F");
    Run_Tree->Branch("l3Pz", &l3Pz, "l3Pz/F");
    Run_Tree->Branch("l3Pt", &l3Pt, "l3Pt/F");
    Run_Tree->Branch("l3Eta", &l3Eta, "l3Eta/F");
    Run_Tree->Branch("l3Phi", &l3Phi, "l3Phi/F");
    Run_Tree->Branch("l3Charge", &l3Charge, "l3Charge/F");
    Run_Tree->Branch("l3_muId", &l3_muId, "l3_muId/F");
    Run_Tree->Branch("l3_muIso", &l3_muIso, "l3_muIso/F");
    Run_Tree->Branch("l3_eleId", &l3_eleId, "l3_eleId/F");
    Run_Tree->Branch("l3_eleIso", &l3_eleIso, "l3_eleIso/F");
    Run_Tree->Branch("l3_eleMVANonTrg", &l3_eleMVANonTrg, "l3_eleMVANonTrg/F");
    Run_Tree->Branch("l3_eleNumHit", &l3_eleNumHit, "l3_eleNumHit/F");
    Run_Tree->Branch("l3_tauIsoL", &l3_tauIsoL, "l3_tauIsoL/F");
    Run_Tree->Branch("l3_tauIsoM", &l3_tauIsoM, "l3_tauIsoM/F");
    Run_Tree->Branch("l3_tauIsoT", &l3_tauIsoT, "l3_tauIsoT/F");
    Run_Tree->Branch("l3_tauRejMuL", &l3_tauRejMuL, "l3_tauRejMuL/F");
    Run_Tree->Branch("l3_tauRejMuM", &l3_tauRejMuM, "l3_tauRejMuM/F");
    Run_Tree->Branch("l3_tauRejMuT", &l3_tauRejMuT, "l3_tauRejMuT/F");
    Run_Tree->Branch("l3_tauRejEleL", &l3_tauRejEleL, "l3_tauRejEleL/F");
    Run_Tree->Branch("l3_tauRejEleM", &l3_tauRejEleM, "l3_tauRejEleM/F");
    Run_Tree->Branch("l3_tauRejEleMVA", &l3_tauRejEleMVA, "l3_tauRejEleMVA/F");

    Run_Tree->Branch("l4M", &l4M, "l4M/F");
    Run_Tree->Branch("l4E", &l4E, "l4E/F");
    Run_Tree->Branch("l4Px", &l4Px, "l4Px/F");
    Run_Tree->Branch("l4Py", &l4Py, "l4Py/F");
    Run_Tree->Branch("l4Pz", &l4Pz, "l4Pz/F");
    Run_Tree->Branch("l4Pt", &l4Pt, "l4Pt/F");
    Run_Tree->Branch("l4Eta", &l4Eta, "l4Eta/F");
    Run_Tree->Branch("l4Phi", &l4Phi, "l4Phi/F");
    Run_Tree->Branch("l4Charge", &l4Charge, "l4Charge/F");
    Run_Tree->Branch("l4_muId", &l4_muId, "l4_muId/F");
    Run_Tree->Branch("l4_muIso", &l4_muIso, "l4_muIso/F");
    Run_Tree->Branch("l4_eleId", &l4_eleId, "l4_eleId/F");
    Run_Tree->Branch("l4_eleIso", &l4_eleIso, "l4_eleIso/F");
    Run_Tree->Branch("l4_eleMVANonTrg", &l4_eleMVANonTrg, "l4_eleMVANonTrg/F");
    Run_Tree->Branch("l4_eleNumHit", &l4_eleNumHit, "l4_eleNumHit/F");
    Run_Tree->Branch("l4_tauIsoL", &l4_tauIsoL, "l4_tauIsoL/F");
    Run_Tree->Branch("l4_tauIsoM", &l4_tauIsoM, "l4_tauIsoM/F");
    Run_Tree->Branch("l4_tauIsoT", &l4_tauIsoT, "l4_tauIsoT/F");
    Run_Tree->Branch("l4_tauRejMuL", &l4_tauRejMuL, "l4_tauRejMuL/F");
    Run_Tree->Branch("l4_tauRejMuM", &l4_tauRejMuM, "l4_tauRejMuM/F");
    Run_Tree->Branch("l4_tauRejMuT", &l4_tauRejMuT, "l4_tauRejMuT/F");
    Run_Tree->Branch("l4_tauRejEleL", &l4_tauRejEleL, "l4_tauRejEleL/F");
    Run_Tree->Branch("l4_tauRejEleM", &l4_tauRejEleM, "l4_tauRejEleM/F");
    Run_Tree->Branch("l4_tauRejEleMVA", &l4_tauRejEleMVA, "l4_tauRejEleMVA/F");

    //#################################################################################################
    //###################      Starting the analysis, making loop over files    #######################
    //#################################################################################################

    //running over the
    for (int k = 0; k < fileNames.size(); k++) {

        TChain *rootTree = new TChain("t");
        rootTree->Add(fileNames[k].c_str());
        int nev = int(rootTree->GetEntries());
        TBranch* branch = rootTree->GetBranch("myevent");
        branch->SetAddress(&m);
        cout << "number of entries is : " << nev << endl;


        // running over the root files
        for (int i = 0; i < nev; i++) {
            rootTree->GetEvent(i);
            if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nev);
            fflush(stdout);


            //*********************************************************************************************
            //****************************    Object definitions    ***************************************
            //*********************************************************************************************
            vector<myobject> mu_ = GoodMuon(m);
            vector<myobject> BareMuon = NoIdIsoMuon(m);

            vector<myobject> electron_PreSel = GoodElectron(m);
            vector<myobject> BareElectron_PreSel = NoIdIsoElectron(m);

            vector<myobject> tau_PreSel = GoodTau(m);
            vector<myobject> BareTau_PreSel = NoIsoTau(m);
            //Number of B-jets
            int num_Bjet = bjet_Multiplicity(m);
            //*********************************************************************************************
            //****************************    PileUp re weighting    ***************************************
            //*********************************************************************************************

            int num_PU = 1;
            float PU_Weight = 1;

            if (mc12) {
                num_PU = m->PUInfo_true;
                PU_Weight = LumiWeights_12->weight(num_PU);
            }
            if (mc11) {
                num_PU = m->PUInfo;
                PU_Weight = LumiWeights_11->weight(num_PU);
            }
            //*********************************************************************************************
            //****************************    Trigger      ************************************************
            //*********************************************************************************************
            bool Trigger;
            if (mc12) Trigger = Trg_MC_12(m);
            if (mc11) Trigger = Trg_MC_11(m);
            if (data12) Trigger = Trg_Data_12(m);
            if (data11) Trigger = Trg_Data_11(m);
            //*********************************************************************************************
            //*********************************************************************************************
            //*******************    Default Values     ***************************************************
            //*********************************************************************************************
            double nominalM_Z = 91.2;

            double HighPt_Lep = 20;
            double tight_Iso_Mu = 0.15;
            double loose_Iso_Mu = 0.30;
            double tight_Iso_Ele = 0.10;
            double loose_Iso_Ele = 0.30;
            double z_lowMass = 60;
            double z_highMass = 120;

            double bin_size = 300;
            double bin_max = 300;
            bool fill_tree[40];
            for (int u = 0; u < 10; u++) {
                fill_tree[u] = true;
            }
            double Cor_eff = 1;
            double fake_pt = 0;
            int MyChannel;


            //*********************************************************************************************
            //****************************    Removing OverLaps  I ***************************************
            //*********************************************************************************************
            //remove overlap Muon and electron
            vector<myobject> electron_;
            electron_.clear();
            for (int a = 0; a < electron_PreSel.size(); a++) {
                bool Keep_obj = true;
                for (int b = 0; b < mu_.size(); b++) {
                    if (deltaR(electron_PreSel[a], mu_[b]) < 0.1)
                        Keep_obj = false;
                }
                if (Keep_obj == true)
                    electron_.push_back(electron_PreSel[a]);
            }
            //remove overlap Muon, Electron and Tau
            vector<myobject> tau_;
            tau_.clear();
            for (int a = 0; a < tau_PreSel.size(); a++) {
                bool Keep_obj = true;
                for (int b = 0; b < electron_.size(); b++) {
                    if (deltaR(tau_PreSel[a], electron_[b]) < 0.1)
                        Keep_obj = false;
                }
                for (int c = 0; c < mu_.size(); c++) {
                    if (deltaR(tau_PreSel[a], mu_[c]) < 0.1)
                        Keep_obj = false;
                }
                if (Keep_obj == true)
                    tau_.push_back(tau_PreSel[a]);
            }

            //*********************************************************************************************
            //****************************    Removing OverLaps  II ***************************************
            //*********************************************************************************************
            vector<myobject> BareElectron;
            BareElectron.clear();
            for (int a = 0; a < BareElectron_PreSel.size(); a++) {
                bool Keep_obj = true;
                for (int b = 0; b < BareMuon.size(); b++) {
                    if (Id_Mu(BareMuon[b]) && deltaR(BareElectron_PreSel[a], BareMuon[b]) < 0.1)
                        Keep_obj = false;
                }
                if (Keep_obj == true)
                    BareElectron.push_back(BareElectron_PreSel[a]);
            }



            vector<myobject> BareTau;
            BareTau.clear();
            for (int a = 0; a < BareTau_PreSel.size(); a++) {
                bool Keep_obj = true;
                for (int b = 0; b < BareElectron.size(); b++) {
                    if (EleMVANonTrigId(BareElectron[b]) && deltaR(BareTau_PreSel[a], BareElectron[b]) < 0.1)
                        Keep_obj = false;
                }
                for (int c = 0; c < BareMuon.size(); c++) {
                    if (Id_Mu(BareMuon[c]) && deltaR(BareTau_PreSel[a], BareMuon[c]) < 0.1)
                        Keep_obj = false;
                }
                if (Keep_obj == true)
                    BareTau.push_back(BareTau_PreSel[a]);
            }

            //*********************************************************************************************
            //*********************************************************************************************

            vector<myobject> mu_Debug;
            vector<myobject> mu_Debug_loose;
            mu_Debug.clear();
            mu_Debug_loose.clear();
            for (int b = 0; b < mu_.size(); b++) {
                if (Iso_Mu_dBeta(mu_[b]) > tight_Iso_Mu && Iso_Mu_dBeta(mu_[b]) < 0.40)
                    mu_Debug.push_back(mu_[b]);
                if (Iso_Mu_dBeta(mu_[b]) > loose_Iso_Mu && Iso_Mu_dBeta(mu_[b]) < 0.40)
                    mu_Debug_loose.push_back(mu_[b]);
            }
            vector<myobject> electron_Debug;
            vector<myobject> electron_Debug_loose;
            electron_Debug.clear();
            electron_Debug_loose.clear();
            for (int a = 0; a < electron_PreSel.size(); a++) {
                bool Keep_obj = true;
                for (int b = 0; b < mu_.size(); b++) {
                    if (deltaR(electron_PreSel[a], mu_[b]) < 0.1)
                        Keep_obj = false;
                }
                if (Keep_obj == true && Iso_Ele_dBeta(electron_PreSel[a]) > tight_Iso_Ele && Iso_Ele_dBeta(electron_PreSel[a]) < 0.40)
                    electron_Debug.push_back(electron_PreSel[a]);
                if (Keep_obj == true && Iso_Ele_dBeta(electron_PreSel[a]) > loose_Iso_Ele && Iso_Ele_dBeta(electron_PreSel[a]) < 0.40)
                    electron_Debug_loose.push_back(electron_PreSel[a]);
            }


            //#################################################################################################
            //#################################################################################################
            //###############    2l2ta Analysis       #########################################################
            //#################################################################################################
            //#################################################################################################
            if (is_mu || is_tot) {

                int mmtt = -1;
                plotFill("mmtt", ++mmtt, 20, 0., 20.);
                if (mu_.size() == 2 && electron_.size() == 0 && Trigger) {
                    plotFill("mmtt", ++mmtt, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < mu_.size(); i++) {
                        for (int j = i + 1; j < mu_.size(); j++) {
                            for (int k = 0; k < tau_.size(); k++) {
                                for (int l = k + 1; l < tau_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(mu_[i], mu_[j]);
                                    double Higgs_Mass = InvarMass_2(tau_[k], tau_[l]);

                                    bool first_l_HighPt = mu_[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = mu_[i].charge * mu_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(mu_[i], mu_[j], tau_[k], tau_[l]);
                                    bool Di_mu_Iso = Iso_Mu_dBeta(mu_[i]) < loose_Iso_Mu && Iso_Mu_dBeta(mu_[j]) < loose_Iso_Mu;
                                    bool mu_Rejection = tau_[k].discriminationByMuonMedium && tau_[l].discriminationByMuonMedium;
                                    bool ele_Rejection = tau_[k].discriminationByElectronMedium && tau_[l].discriminationByElectronMedium;
                                    bool tau_tightIso_1 = tau_[k].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_tightIso_2 = tau_[l].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_looseIso_1 = tau_[k].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool tau_looseIso_2 = tau_[l].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool H_Charge_b = tau_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("mmtt", mu_[i], mu_[j], tau_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("mmtt", status_sample.c_str(), mu_[i], mu_[j], tau_[k], tau_[l]);

                                    if (bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_mu_Iso && mu_Rejection && ele_Rejection) {
                                        //For Validation
                                        if (!H_Charge_b && tau_looseIso_1 && tau_looseIso_2) {
                                            plotFill("Higgs_Mass_mmtt_Validation", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        }//End of Validation
                                        if (SumPtCut && H_Charge_b && tau_tightIso_1 && tau_tightIso_2) {

                                            //Filling the tree
                                            MyChannel = 1;
                                            if (fill_tree[MyChannel]) {
                                                fill_tree[MyChannel] = false;
                                                plotFill("Zboson_Mass_mmtt", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                                plotFill("Higgs_Mass_mmtt", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                                plotFill("mmtt", ++mmtt, 20, 0., 20., PU_Weight * Cor_eff);
                                                plotFill("mmtt", ++mmtt, 20, 0., 20., PU_Weight);
                                                plotFill("mmtt", ++mmtt, 20, 0., 20., Cor_eff);
                                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 1, mu_[i], mu_[j], tau_[k], tau_[l]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################

                int mmet = -1;
                plotFill("mmet", ++mmet, 20, 0., 20.);
                if (mu_.size() == 2 && electron_.size() == 1 && Trigger) {
                    plotFill("mmet", ++mmet, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < mu_.size(); i++) {
                        for (int j = i + 1; j < mu_.size(); j++) {
                            for (int k = 0; k < electron_.size(); k++) {
                                for (int l = 0; l < tau_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(mu_[i], mu_[j]);
                                    double Higgs_Mass = InvarMass_2(electron_[k], tau_[l]);

                                    bool first_l_HighPt = mu_[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = mu_[i].charge * mu_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(mu_[i], mu_[j], electron_[k], tau_[l]);
                                    bool Di_mu_Iso = Iso_Mu_dBeta(mu_[i]) < loose_Iso_Mu && Iso_Mu_dBeta(mu_[j]) < loose_Iso_Mu;
                                    bool ele_Iso = Iso_Ele_dBeta(electron_[k]) < tight_Iso_Ele && electron_[k].numHitEleInner < 1;
                                    bool tau_Iso = tau_[l].byMediumCombinedIsolationDeltaBetaCorr && tau_[l].discriminationByElectronMVA;
                                    bool H_Charge_b = electron_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("mmet", mu_[i], mu_[j], electron_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("mmet", status_sample.c_str(), mu_[i], mu_[j], electron_[k], tau_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_mu_Iso && ele_Iso && tau_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 2;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("mmet", ++mmet, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("mmet", ++mmet, 20, 0., 20., PU_Weight);
                                            plotFill("mmet", ++mmet, 20, 0., 20., Cor_eff);
                                            plotFill("Zboson_Mass_mmet", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_mmet", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 2, mu_[i], mu_[j], electron_[k], tau_[l]);

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################
                int mmmt = -1;
                plotFill("mmmt", ++mmmt, 20, 0., 20.);
                if (mu_.size() == 3 && electron_.size() == 0 && Trigger) {
                    plotFill("mmmt", ++mmmt, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < mu_.size(); i++) {
                        for (int j = i + 1; j < mu_.size(); j++) {
                            for (int k = j + 1; k < mu_.size(); k++) {

                                double mass_ij = (mu_[i].charge * mu_[j].charge < 0 ? fabs(InvarMass_2(mu_[i], mu_[j]) - nominalM_Z) : 1000);
                                double mass_ik = (mu_[i].charge * mu_[k].charge < 0 ? fabs(InvarMass_2(mu_[i], mu_[k]) - nominalM_Z) : 1000);
                                double mass_jk = (mu_[j].charge * mu_[k].charge < 0 ? fabs(InvarMass_2(mu_[j], mu_[k]) - nominalM_Z) : 1000);

                                if (mass_ik < mass_ij && mass_ik < mass_jk) swap(mu_[j], mu_[k]);
                                if (mass_jk < mass_ij && mass_jk < mass_ik) swap(mu_[i], mu_[k]);

                                for (int l = 0; l < tau_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(mu_[i], mu_[j]);
                                    double Higgs_Mass = InvarMass_2(mu_[k], tau_[l]);

                                    bool first_l_HighPt = mu_[i].pt > HighPt_Lep || mu_[j].pt > HighPt_Lep;
                                    bool Z_Charge_b = mu_[i].charge * mu_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(mu_[i], mu_[j], mu_[k], tau_[l]);
                                    bool Di_mu_Iso = Iso_Mu_dBeta(mu_[i]) < loose_Iso_Mu && Iso_Mu_dBeta(mu_[j]) < loose_Iso_Mu;
                                    bool mu_Iso = Iso_Mu_dBeta(mu_[k]) < tight_Iso_Mu;
                                    bool tau_Iso = tau_[l].byMediumCombinedIsolationDeltaBetaCorr && tau_[l].discriminationByMuonTight;
                                    bool H_Charge_b = mu_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("mmmt", mu_[i], mu_[j], mu_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("mmmt", status_sample.c_str(), mu_[i], mu_[j], mu_[k], tau_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_mu_Iso && mu_Iso && tau_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 3;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("Zboson_Mass_mmmt", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_mmmt", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("mmmt", ++mmmt, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("mmmt", ++mmmt, 20, 0., 20., PU_Weight);
                                            plotFill("mmmt", ++mmmt, 20, 0., 20., Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 3, mu_[i], mu_[j], mu_[k], tau_[l]);

                                        }
                                    }
                                }
                                mu_ = GoodMuon(m);
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################

                int mmme = -1;
                plotFill("mmme", ++mmme, 20, 0., 20.);
                if (mu_.size() == 3 && electron_.size() == 1 && Trigger) {
                    plotFill("mmme", ++mmme, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < mu_.size(); i++) {
                        for (int j = i + 1; j < mu_.size(); j++) {
                            for (int k = j + 1; k < mu_.size(); k++) {

                                double mass_ij = (mu_[i].charge * mu_[j].charge < 0 ? fabs(InvarMass_2(mu_[i], mu_[j]) - nominalM_Z) : 1000);
                                double mass_ik = (mu_[i].charge * mu_[k].charge < 0 ? fabs(InvarMass_2(mu_[i], mu_[k]) - nominalM_Z) : 1000);
                                double mass_jk = (mu_[j].charge * mu_[k].charge < 0 ? fabs(InvarMass_2(mu_[j], mu_[k]) - nominalM_Z) : 1000);

                                if (mass_ik < mass_ij && mass_ik < mass_jk) swap(mu_[j], mu_[k]);
                                if (mass_jk < mass_ij && mass_jk < mass_ik) swap(mu_[i], mu_[k]);

                                for (int l = 0; l < electron_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(mu_[i], mu_[j]);
                                    double Higgs_Mass = InvarMass_2(mu_[k], electron_[l]);

                                    bool first_l_HighPt = mu_[i].pt > HighPt_Lep || mu_[j].pt > HighPt_Lep;
                                    bool Z_Charge_b = mu_[i].charge * mu_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass< z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(mu_[i], mu_[j], mu_[k], electron_[l]);
                                    bool Di_mu_Iso = Iso_Mu_dBeta(mu_[i]) < loose_Iso_Mu && Iso_Mu_dBeta(mu_[j]) < loose_Iso_Mu;
                                    bool mu_Iso = Iso_Mu_dBeta(mu_[k]) < loose_Iso_Mu;
                                    bool electron_Iso = Iso_Ele_dBeta(electron_[l]) < loose_Iso_Ele;
                                    bool H_Charge_b = mu_[k].charge * electron_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("mmme", mu_[i], mu_[j], mu_[k], electron_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("mmme", status_sample.c_str(), mu_[i], mu_[j], mu_[k], electron_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_mu_Iso && mu_Iso && electron_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 4;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("Zboson_Mass_mmme", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_mmme", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("mmme", ++mmme, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("mmme", ++mmme, 20, 0., 20., PU_Weight);
                                            plotFill("mmme", ++mmme, 20, 0., 20., Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 4, mu_[i], mu_[j], mu_[k], electron_[l]);
                                        }
                                    }
                                }
                                mu_ = GoodMuon(m);
                            }
                        }
                    }
                }

            }//end of only Muon
            //#################################################################################################
            //#################################################################################################
            //**********************  Double Electron ********************************
            //************************************************************************
            //************************************************************************
            if (is_ele || is_tot) {

                int eett = -1;
                plotFill("eett", ++eett, 20, 0., 20.);
                if (electron_.size() == 2 && mu_.size() == 0 && Trigger) {
                    plotFill("eett", ++eett, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < electron_.size(); i++) {
                        for (int j = i + 1; j < electron_.size(); j++) {
                            for (int k = 0; k < tau_.size(); k++) {
                                for (int l = 0; l < k; l++) {

                                    double Zboson_Mass = InvarMass_2(electron_[i], electron_[j]);
                                    double Higgs_Mass = InvarMass_2(tau_[k], tau_[l]);

                                    bool first_l_HighPt = electron_[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = electron_[i].charge * electron_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(electron_[i], electron_[j], tau_[k], tau_[l]);
                                    bool Di_Ele_Iso = Iso_Ele_dBeta(electron_[i]) < loose_Iso_Ele && Iso_Ele_dBeta(electron_[j]) < loose_Iso_Ele;
                                    bool mu_Rejection = tau_[k].discriminationByMuonMedium && tau_[l].discriminationByMuonMedium;
                                    bool ele_Rejection = tau_[k].discriminationByElectronMedium && tau_[l].discriminationByElectronMedium;
                                    bool tau_tightIso_1 = tau_[k].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_tightIso_2 = tau_[l].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_looseIso_1 = tau_[k].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool tau_looseIso_2 = tau_[l].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool H_Charge_b = tau_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("eett", electron_[i], electron_[j], tau_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("eett", status_sample.c_str(), electron_[i], electron_[j], tau_[k], tau_[l]);

                                    if (bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_Ele_Iso && ele_Rejection && mu_Rejection) {
                                        if (!H_Charge_b && tau_looseIso_1 && tau_looseIso_2) {
                                            plotFill("Higgs_Mass_eett_Validation", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        }
                                        if (SumPtCut && H_Charge_b && tau_tightIso_1 && tau_tightIso_2) {

                                            //Filling the tree
                                            MyChannel = 5;
                                            if (fill_tree[MyChannel]) {
                                                fill_tree[MyChannel] = false;
                                                plotFill("eett", ++eett, 20, 0., 20., PU_Weight * Cor_eff);
                                                plotFill("eett", ++eett, 20, 0., 20., PU_Weight);
                                                plotFill("eett", ++eett, 20, 0., 20., Cor_eff);
                                                plotFill("Zboson_Mass_eett", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                                plotFill("Higgs_Mass_eett", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 5, electron_[i], electron_[j], tau_[k], tau_[l]);

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################
                int eemt = -1;
                plotFill("eemt", ++eemt, 20, 0., 20.);
                if (electron_.size() == 2 && mu_.size() == 1 && Trigger) {
                    plotFill("eemt", ++eemt, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < electron_.size(); i++) {
                        for (int j = i + 1; j < electron_.size(); j++) {
                            for (int k = 0; k < mu_.size(); k++) {
                                for (int l = 0; l < tau_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(electron_[i], electron_[j]);
                                    double Higgs_Mass = InvarMass_2(mu_[k], tau_[l]);

                                    bool first_l_HighPt = electron_[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = electron_[i].charge * electron_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(electron_[i], electron_[j], mu_[k], tau_[l]);
                                    bool Di_Ele_Iso = Iso_Ele_dBeta(electron_[i]) < loose_Iso_Ele && Iso_Ele_dBeta(electron_[j]) < loose_Iso_Ele;
                                    bool mu_Iso = Iso_Mu_dBeta(mu_[k]) < tight_Iso_Mu;
                                    bool tau_Iso = tau_[l].byMediumCombinedIsolationDeltaBetaCorr && tau_[l].discriminationByMuonTight;
                                    bool H_Charge_b = mu_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("eemt", electron_[i], electron_[j], mu_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("eemt", status_sample.c_str(), electron_[i], electron_[j], mu_[k], tau_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_Ele_Iso && mu_Iso && tau_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 6;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("Zboson_Mass_eemt", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_eemt", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("eemt", ++eemt, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("eemt", ++eemt, 20, 0., 20., PU_Weight);
                                            plotFill("eemt", ++eemt, 20, 0., 20., Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 6, electron_[i], electron_[j], mu_[k], tau_[l]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################
                int eeet = -1;
                plotFill("eeet", ++eeet, 20, 0., 20.);
                if (electron_.size() == 3 && mu_.size() == 0 && Trigger) {
                    plotFill("eeet", ++eeet, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < electron_.size(); i++) {
                        for (int j = i + 1; j < electron_.size(); j++) {
                            for (int k = j + 1; k < electron_.size(); k++) {

                                double mass_ij = (electron_[i].charge * electron_[j].charge < 0 ? fabs(InvarMass_2(electron_[i], electron_[j]) - nominalM_Z) : 1000);
                                double mass_ik = (electron_[i].charge * electron_[k].charge < 0 ? fabs(InvarMass_2(electron_[i], electron_[k]) - nominalM_Z) : 1000);
                                double mass_jk = (electron_[j].charge * electron_[k].charge < 0 ? fabs(InvarMass_2(electron_[j], electron_[k]) - nominalM_Z) : 1000);

                                if (mass_ik < mass_ij && mass_ik < mass_jk) swap(electron_[j], electron_[k]);
                                if (mass_jk < mass_ij && mass_jk < mass_ik) swap(electron_[i], electron_[k]);

                                for (int l = 0; l < tau_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(electron_[i], electron_[j]);
                                    double Higgs_Mass = InvarMass_2(electron_[k], tau_[l]);

                                    bool first_l_HighPt = electron_[i].pt > HighPt_Lep || electron_[j].pt > HighPt_Lep;
                                    bool Z_Charge_b = electron_[i].charge * electron_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(electron_[i], electron_[j], electron_[k], tau_[l]);
                                    bool Di_Ele_Iso = Iso_Ele_dBeta(electron_[i]) < loose_Iso_Ele && Iso_Ele_dBeta(electron_[j]) < loose_Iso_Ele;
                                    bool electron_Iso = Iso_Ele_dBeta(electron_[k]) < tight_Iso_Ele && electron_[k].numHitEleInner < 1;
                                    bool tau_Iso = tau_[l].byMediumCombinedIsolationDeltaBetaCorr && tau_[l].discriminationByElectronMVA;
                                    bool H_Charge_b = electron_[k].charge * tau_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("eeet", electron_[i], electron_[j], electron_[k], tau_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("eeet", status_sample.c_str(), electron_[i], electron_[j], electron_[k], tau_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_Ele_Iso && electron_Iso && tau_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 7;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("Zboson_Mass_eeet", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_eeet", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("eeet", ++eeet, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("eeet", ++eeet, 20, 0., 20., PU_Weight);
                                            plotFill("eeet", ++eeet, 20, 0., 20., Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 7, electron_[i], electron_[j], electron_[k], tau_[l]);
                                        }
                                    }
                                }
                                electron_ = GoodElectron(m);
                            }
                        }
                    }
                }
                //#################################################################################################
                //#################################################################################################
                int eeem = -1;
                plotFill("eeem", ++eeem, 20, 0., 20.);
                if (electron_.size() == 3 && mu_.size() == 1 && Trigger) {
                    plotFill("eeem", ++eeem, 20, 0., 20., PU_Weight);

                    for (int i = 0; i < electron_.size(); i++) {
                        for (int j = i + 1; j < electron_.size(); j++) {
                            for (int k = j + 1; k < electron_.size(); k++) {

                                double mass_ij = (electron_[i].charge * electron_[j].charge < 0 ? fabs(InvarMass_2(electron_[i], electron_[j]) - nominalM_Z) : 1000);
                                double mass_ik = (electron_[i].charge * electron_[k].charge < 0 ? fabs(InvarMass_2(electron_[i], electron_[k]) - nominalM_Z) : 1000);
                                double mass_jk = (electron_[j].charge * electron_[k].charge < 0 ? fabs(InvarMass_2(electron_[j], electron_[k]) - nominalM_Z) : 1000);
                                if (mass_ik < mass_ij && mass_ik < mass_jk) swap(electron_[j], electron_[k]);
                                if (mass_jk < mass_ij && mass_jk < mass_ik) swap(electron_[i], electron_[k]);

                                for (int l = 0; l < mu_.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(electron_[i], electron_[j]);
                                    double Higgs_Mass = InvarMass_2(electron_[k], mu_[l]);

                                    bool first_l_HighPt = electron_[i].pt > HighPt_Lep || electron_[j].pt > HighPt_Lep;
                                    bool Z_Charge_b = electron_[i].charge * electron_[j].charge < 0;
                                    bool Z_Mass_b = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(electron_[i], electron_[j], electron_[k], mu_[l]);
                                    bool Di_Ele_Iso = Iso_Ele_dBeta(electron_[i]) < loose_Iso_Ele && Iso_Ele_dBeta(electron_[j]) < loose_Iso_Ele;
                                    bool electron_Iso = Iso_Ele_dBeta(electron_[k]) < loose_Iso_Ele;
                                    bool mu_Iso = Iso_Mu_dBeta(mu_[l]) < loose_Iso_Mu;
                                    bool H_Charge_b = electron_[k].charge * mu_[l].charge < 0;
                                    bool SumPtCut = getSumPtCut("eeem", electron_[i], electron_[j], electron_[k], mu_[l]);
                                    bool bjet_num = num_Bjet < 1;
                                    Cor_eff = getCorrFactor("eeem", status_sample.c_str(), electron_[i], electron_[j], electron_[k], mu_[l]);

                                    if (SumPtCut && bjet_num && first_l_HighPt && Z_Charge_b && Z_Mass_b && Overlap_Dz && Di_Ele_Iso && electron_Iso && mu_Iso && H_Charge_b) {

                                        //Filling the tree
                                        MyChannel = 8;
                                        if (fill_tree[MyChannel]) {
                                            fill_tree[MyChannel] = false;
                                            plotFill("eeem", ++eeem, 20, 0., 20., PU_Weight * Cor_eff);
                                            plotFill("eeem", ++eeem, 20, 0., 20., PU_Weight);
                                            plotFill("eeem", ++eeem, 20, 0., 20., Cor_eff);
                                            plotFill("Zboson_Mass_eeem", Zboson_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            plotFill("Higgs_Mass_eeem", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 8, electron_[i], electron_[j], electron_[k], mu_[l]);
                                        }
                                    }
                                }
                                electron_ = GoodElectron(m);
                            }
                        }
                    }
                }

            }//end of Only Electron
            //#################################################################################################
            //#################################################################################################
            //#################################################################################################
            //#########################        Fake Rate Estimation        ##########################################
            //#################################################################################################
            //*****************************************************************************************
            //*****************************************************************************************
            //*****************************************************************************************
            //*****************************************************************************************
            if (is_mu || is_tot) {


                // ABCD mmtt
                bool Fill_Once_ff = true;
                bool Fill_Once_fp = true;
                bool Fill_Once_pf = true;
                bool fill_once_Estimate = true;
                bool Fill_Once_ff_v = true;
                bool Fill_Once_fp_v = true;
                bool Fill_Once_pf_v = true;
                bool Fill_Once_pp_v = true;

                if (BareTau.size() > 1 && BareMuon.size() > 1 && Trigger) {
                    for (int i = 0; i < BareMuon.size(); i++) {
                        for (int j = i + 1; j < BareMuon.size(); j++) {
                            for (int k = 0; k < BareTau.size(); k++) {
                                for (int l = k + 1; l < BareTau.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(BareMuon[i], BareMuon[j]);
                                    double Higgs_Mass = InvarMass_2(BareTau[k], BareTau[l]);

                                    bool first_l_HighPt = BareMuon[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = BareMuon[i].charge * BareMuon[j].charge < 0;
                                    bool mu_Iso_1 = Iso_Mu_dBeta(BareMuon[i]) < loose_Iso_Mu;
                                    bool mu_Iso_2 = Iso_Mu_dBeta(BareMuon[j]) < loose_Iso_Mu;
                                    bool mu_Id_1 = Id_Mu(BareMuon[i]);
                                    bool mu_Id_2 = Id_Mu(BareMuon[j]);
                                    bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                    bool mu_Rejection = BareTau[k].discriminationByMuonMedium && BareTau[l].discriminationByMuonMedium;
                                    bool ele_Rejection = BareTau[k].discriminationByElectronMedium && BareTau[l].discriminationByElectronMedium;
                                    bool tau_Iso_Tight_1 = BareTau[k].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Tight_2 = BareTau[l].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Medium_1 = BareTau[k].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Medium_2 = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Loose_1 = BareTau[k].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Loose_2 = BareTau[l].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool H_Charge_b = BareTau[k].charge * BareTau[l].charge < 0;
                                    bool No_extra_lepton = mu_.size() == 2 && electron_.size() == 0;
                                    bool bjet_num = num_Bjet < 1;
                                    bool SumPtCut = getSumPtCut("mmtt", BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                    Cor_eff = getCorrFactor("mmtt", status_sample.c_str(), BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);

                                    bool preSelection = bjet_num && No_extra_lepton && Overlap_Dz && first_l_HighPt && Z_Charge_b && mu_Iso_1 && mu_Iso_2 && mu_Id_1 && mu_Id_2 && Leading_Z_Mass && mu_Rejection && ele_Rejection;
                                    bool FR_Application = SumPtCut && BareTau[k].pt > 20 && BareTau[l].pt > 20 && H_Charge_b;
                                    bool FR_Validation = BareTau[k].pt > 20 && BareTau[l].pt > 20 && !H_Charge_b;
                                    bool FR_Estimation_SS = fill_once_Estimate && !H_Charge_b && BareTau[k].pt > 10 && BareTau[l].pt > 10;

                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************

                                    if (preSelection && BareTau[k].pt > 10 && BareTau[l].pt > 10) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 91, BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        if (Fill_Once_ff && !tau_Iso_Tight_1 && !tau_Iso_Tight_2) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_MMTT_apply_ff", BareTau[k].pt, BareTau[l].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 11, BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                        }
                                        if (Fill_Once_fp && !tau_Iso_Tight_1 && tau_Iso_Tight_2) {
                                            Fill_Once_fp = false;
                                            plotFill("FakeRate_MMTT_apply_fp", BareTau[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 21, BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                        }
                                        if (Fill_Once_pf && tau_Iso_Tight_1 && !tau_Iso_Tight_2) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_MMTT_apply_pf", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 31, BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_mmtt_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 41, BareMuon[i], BareMuon[j], BareTau[k], BareTau[l]);
                                    }//end fake rate application

                                    //*********************************************************************************
                                    ////************************ Fake rate  validation ************************
                                    //*********************************************************************************
                                    if (preSelection && FR_Validation) {
                                        plotFill("Higgs_Mass_mmtt_ABCD_Validation", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);

                                        //Fake Rate Application Validation
                                        if (Fill_Once_ff_v && !tau_Iso_Loose_1 && !tau_Iso_Loose_2) {
                                            Fill_Once_ff_v = false;
                                            plotFill("Validation_FakeRate_MMTT_apply_ff", BareTau[k].pt, BareTau[l].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                        }
                                        if (Fill_Once_fp_v && !tau_Iso_Loose_1 && tau_Iso_Loose_2) {
                                            Fill_Once_fp_v = false;
                                            plotFill("ValidationFakeRate_MMTT_apply_fp", BareTau[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                        }
                                        if (Fill_Once_pf_v && tau_Iso_Loose_1 && !tau_Iso_Loose_2) {
                                            Fill_Once_pf_v = false;
                                            plotFill("ValidationFakeRate_MMTT_apply_pf", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                        }
                                        if (Fill_Once_pp_v && tau_Iso_Loose_1 && tau_Iso_Loose_2) {
                                            Fill_Once_pp_v = false;
                                            plotFill("ValidationFakeRate_MMTT_apply_pp", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                        }
                                    }//end of validation

                                    //*********
                                }
                            }
                        }
                    }
                }
                //****************************************************************
                //mmet ABCD
                Fill_Once_ff = true;
                Fill_Once_fp = true;
                Fill_Once_pf = true;

                if (BareTau.size() > 0 && BareElectron.size() > 0 && BareMuon.size() > 1 && Trigger) {
                    for (int i = 0; i < BareMuon.size(); i++) {
                        for (int j = i + 1; j < BareMuon.size(); j++) {
                            for (int k = 0; k < BareElectron.size(); k++) {
                                for (int l = 0; l < BareTau.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(BareMuon[i], BareMuon[j]);
                                    double Higgs_Mass = InvarMass_2(BareElectron[k], BareTau[l]);

                                    bool first_l_HighPt = BareMuon[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = BareMuon[i].charge * BareMuon[j].charge < 0;
                                    bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                    bool mu_Iso_1 = Iso_Mu_dBeta(BareMuon[i]) < loose_Iso_Mu;
                                    bool mu_Iso_2 = Iso_Mu_dBeta(BareMuon[j]) < loose_Iso_Mu;
                                    bool mu_Id_1 = Id_Mu(BareMuon[i]);
                                    bool mu_Id_2 = Id_Mu(BareMuon[j]);
                                    bool tau_Isol = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool electron_Isol_Tight = Iso_Ele_dBeta(BareElectron[k]) < tight_Iso_Ele;
                                    bool electron_Isol_Loose = Iso_Ele_dBeta(BareElectron[k]) < loose_Iso_Ele;
                                    bool electron_Id = EleMVANonTrigId(BareElectron[k]);
                                    bool H_Charge_b = BareElectron[k].charge * BareTau[l].charge < 0;
                                    bool ele_Rejection = BareTau[l].discriminationByElectronMVA;
                                    bool ele_numHit = BareElectron[k].numHitEleInner < 1;
                                    bool No_extra_lepton = mu_.size() == 2;
                                    bool bjet_num = num_Bjet < 1;
                                    bool SumPtCut = getSumPtCut("mmet", BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                    Cor_eff = getCorrFactor("mmet", status_sample.c_str(), BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                    fake_pt = Find_Closet_Jet(BareElectron[k], m);

                                    bool preSelection = Overlap_Dz && ele_Rejection && ele_numHit && bjet_num && first_l_HighPt && mu_Iso_1 && mu_Iso_2 && mu_Id_1 && mu_Id_2 && Z_Charge_b && Leading_Z_Mass;
                                    bool FR_Application = SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
                                    bool FR_Estimation_tau0 = BareTau[l].pt > 0 && !H_Charge_b;
                                    bool FR_Estimation_tau10 = BareTau[l].pt > 10 && !H_Charge_b;


                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************
                                    if (preSelection) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 92, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {
                                        //                                            if (Fill_Once_ff && !tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 0 || (electron_.size() == 1 && electron_Debug.size() == 1)) && tau_.size() == 0) {
                                        if (Fill_Once_ff && !tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 0 || (electron_.size() == 1 && electron_Debug.size() == 1))) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_MMET_apply_ff", BareTau[l].pt, BareElectron[k].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMET_apply_ff_Jet", BareTau[l].pt, fake_pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 12, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_fp && !tau_Isol && electron_Isol_Tight && electron_Id && electron_.size() == 1 && tau_.size() == 0) {
                                        if (Fill_Once_fp && !tau_Isol && electron_Isol_Tight && electron_Id && electron_.size() == 1) {
                                            Fill_Once_fp = false;
                                            plotFill("SizeTau_MMET", BareTau.size(), 10, 0, 10);
                                            plotFill("FakeRate_MMET_apply_fp", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 22, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_pf && tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 0 || (electron_.size() == 1 && electron_Debug.size() == 1)) && tau_.size() == 1) {
                                        if (Fill_Once_pf && tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 0 || (electron_.size() == 1 && electron_Debug.size() == 1))) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_MMET_apply_pf", BareElectron[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMET_apply_pf_Jet", fake_pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 32, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_mmet_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 42, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                    }//end of fake apply
                                    //*********************************************************************************
                                    //***************************Fake Rate Estimation ***************************
                                    //*********************************************************************************
                                    if (preSelection && FR_Estimation_tau0) {

                                        //Denumerator
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2) {
                                            plotFill("FakeRate_ET_Electron_Pt_Before_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Pt_Before_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Pt_Before_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 52, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }
                                        //numerator Tight
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2 && electron_Id && electron_Isol_Tight) {
                                            plotFill("FakeRate_ET_Electron_Tight_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Tight_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Tight_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 62, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }
                                        //numerator Loose
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2 && electron_Id && electron_Isol_Loose) {
                                            plotFill("FakeRate_ET_Electron_Loose_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Loose_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Loose_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 72, BareMuon[i], BareMuon[j], BareElectron[k], BareTau[l]);
                                        }

                                    }//end of fake estimate //tau Pt > 0
                                    if (preSelection && FR_Estimation_tau10) {
                                        //tau fake rate
                                        plotFill("FakeRate_MMET_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        plotFill("FakeRate_ET_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        if (tau_Isol) {
                                            plotFill("FakeRate_MMET_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                        }

                                        //electron fake rate
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2) {
                                            plotFill("FakeRate_ET_Electron_Pt_Before_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Pt_Before_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Pt_Before_10_Jet", fake_pt, 200, 0, 200);
                                        }

                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2 && electron_Id && electron_Isol_Tight) {
                                            plotFill("FakeRate_ET_Electron_Tight_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Tight_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Tight_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 2 && electron_Id && electron_Isol_Loose) {
                                            plotFill("FakeRate_ET_Electron_Loose_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMET_Electron_Loose_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Loose_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                    }//end of fake estimate //tau Pt > 10
                                    //******
                                }
                            }
                        }
                    }
                }
                //*************************************************************
                //mmmt ABCD

                if (BareMuon.size() > 1 && Trigger) {
                    double Refer_Mass = 1000;
                    double Mass_LeadingZ;
                    int p, q;
                    bool Selected_Lead_Z = false;
                    for (int i = 0; i < BareMuon.size(); i++) {
                        for (int j = i + 1; j < BareMuon.size(); j++) {

                            double Zboson_Mass = InvarMass_2(BareMuon[i], BareMuon[j]);
                            double Zboson_Mass_diff = fabs(Zboson_Mass - nominalM_Z);

                            bool mu_Iso_1 = Iso_Mu_dBeta(BareMuon[i]) < loose_Iso_Mu;
                            bool mu_Iso_2 = Iso_Mu_dBeta(BareMuon[j]) < loose_Iso_Mu;
                            bool mu_Id_1 = Id_Mu(BareMuon[i]);
                            bool mu_Id_2 = Id_Mu(BareMuon[j]);
                            bool first_l_HighPt = BareMuon[i].pt > 20;
                            bool Z_Charge_b = BareMuon[i].charge * BareMuon[j].charge < 0;
                            bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                            bool bjet_num = num_Bjet < 1;
                            if (bjet_num && first_l_HighPt && Z_Charge_b && Leading_Z_Mass && mu_Iso_1 && mu_Iso_2 && mu_Id_1 && mu_Id_2) {
                                if (Zboson_Mass_diff < Refer_Mass) {
                                    Refer_Mass = Zboson_Mass_diff;
                                    p = i;
                                    q = j;
                                    Mass_LeadingZ = Zboson_Mass;
                                    Selected_Lead_Z = true;

                                }
                            }
                        }
                    }
                    if (Selected_Lead_Z) {

                        //*****************////////////************////////////

                        Fill_Once_ff = true;
                        Fill_Once_fp = true;
                        Fill_Once_pf = true;

                        if (BareTau.size() > 0 && BareMuon.size() > 2) {
                            for (int k = 0; k < BareMuon.size(); k++) {
                                for (int l = 0; l < BareTau.size(); l++) {


                                    double Higgs_Mass = InvarMass_2(BareMuon[k], BareTau[l]);

                                    bool Overlap_Dz = OverLapWithTaus(BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                    bool tau_Isol = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool Muon_Isol_Tight = Iso_Mu_dBeta(BareMuon[k]) < tight_Iso_Mu;
                                    bool Muon_Isol_Loose = Iso_Mu_dBeta(BareMuon[k]) < loose_Iso_Mu;
                                    bool Muon_Id = Id_Mu(BareMuon[k]);
                                    bool H_Charge_b = BareTau[l].charge * BareMuon[k].charge < 0;
                                    bool tau_Mu_Veto = BareTau[l].discriminationByMuonTight;
                                    bool No_extra_lepton = electron_.size() == 0;
                                    bool SumPtCut = getSumPtCut("mmmt", BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                    Cor_eff = getCorrFactor("mmmt", status_sample.c_str(), BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                    fake_pt = Find_Closet_Jet(BareMuon[k], m);

                                    bool preSelection = Overlap_Dz && tau_Mu_Veto;
                                    bool FR_Application = SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
                                    bool FR_Estimation_tau0 = BareTau[l].pt > 0 && !H_Charge_b;
                                    bool FR_Estimation_tau10 = BareTau[l].pt > 10 && !H_Charge_b;

                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************

                                    if (preSelection) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 93, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        //                                            if (Fill_Once_ff && !tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 && mu_Debug.size() == 1)) && tau_.size() == 0) {
                                        if (Fill_Once_ff && !tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 && mu_Debug.size() == 1))) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_MMMT_apply_ff", BareTau[l].pt, BareMuon[k].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMMT_apply_ff_Jet", BareTau[l].pt, fake_pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 13, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_fp && !tau_Isol && Muon_Isol_Tight && Muon_Id && mu_.size() == 3 && tau_.size() == 0) {
                                        if (Fill_Once_fp && !tau_Isol && Muon_Isol_Tight && Muon_Id && mu_.size() == 3) {
                                            Fill_Once_fp = false;
                                            plotFill("FakeRate_MMMT_apply_fp", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 23, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_pf && tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 && mu_Debug.size() == 1)) && tau_.size() == 1) {
                                        if (Fill_Once_pf && tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 && mu_Debug.size() == 1))) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_MMMT_apply_pf", BareMuon[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMMT_apply_pf_Jet", fake_pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 33, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_mmmt_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 43, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                    }//end of fake apply

                                    //*********************************************************************************
                                    //***************************Fake Rate Estimation ***************************
                                    //*********************************************************************************
                                    //Fake Rate Estimation tau Pt > 0
                                    if (preSelection && FR_Estimation_tau0) {

                                        //Denumerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4) {
                                            plotFill("FakeRate_MT_Muon_Pt_Before_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Pt_Before_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Pt_Before_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 53, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);

                                        }
                                        //Numerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4 && Muon_Id && Muon_Isol_Tight) {
                                            plotFill("FakeRate_MT_Muon_Tight_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Tight_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Tight_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 63, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                        }
                                        //Numerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4 && Muon_Id && Muon_Isol_Loose) {
                                            plotFill("FakeRate_MT_Muon_Loose_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Loose_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Loose_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 73, BareMuon[p], BareMuon[q], BareMuon[k], BareTau[l]);
                                        }
                                    }//tau Pt > 0

                                    //Fake Rate Estimation tau Pt > 10
                                    if (preSelection && FR_Estimation_tau10) {
                                        //tau fake rate
                                        plotFill("FakeRate_MMMT_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        plotFill("FakeRate_MT_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        if (tau_Isol) {
                                            plotFill("FakeRate_MMMT_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                        }

                                        //Denumerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4) {
                                            plotFill("FakeRate_MT_Muon_Pt_Before_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Pt_Before_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Pt_Before_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4 && Muon_Id && Muon_Isol_Tight) {
                                            plotFill("FakeRate_MT_Muon_Tight_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Tight_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Tight_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 4 && Muon_Id && Muon_Isol_Loose) {
                                            plotFill("FakeRate_MT_Muon_Loose_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MMMT_Muon_Loose_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Loose_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                    }//tau Pt > 10
                                    //****
                                }
                            }
                        }
                        //*********************************************
                        //mmme
                        Fill_Once_ff = true;
                        Fill_Once_fp = true;
                        Fill_Once_pf = true;

                        if (BareElectron.size() > 0 && BareMuon.size() > 2) {

                            for (int k = 0; k < BareMuon.size(); k++) {
                                for (int l = 0; l < BareElectron.size(); l++) {

                                    double Higgs_Mass = InvarMass_2(BareMuon[k], BareElectron[l]);

                                    bool Overlap_Dz = OverLapWithTaus(BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                    bool muon_Isol_Loose = Iso_Mu_dBeta(BareMuon[k]) < loose_Iso_Mu;
                                    bool electron_Isol_Loose = Iso_Ele_dBeta(BareElectron[l]) < loose_Iso_Ele;
                                    bool muon_Id = Id_Mu(BareMuon[k]);
                                    bool electron_Id = EleMVANonTrigId(BareElectron[l]);
                                    bool H_Charge_b = BareElectron[l].charge * BareMuon[k].charge < 0;
                                    bool No_extra_lepton = tau_.size() < 10; //strange cut
                                    Cor_eff = getCorrFactor("mmme", status_sample.c_str(), BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                    bool SumPtCut = getSumPtCut("mmme", BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                    double fake_pt_mu = Find_Closet_Jet(BareMuon[k], m);
                                    double fake_pt_ele = Find_Closet_Jet(BareElectron[l], m);

                                    bool preSelection = true;
                                    bool FR_Application = SumPtCut && No_extra_lepton && Overlap_Dz && H_Charge_b;
                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************

                                    if (preSelection) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 94, BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                    }
                                    if (preSelection && FR_Application) {


                                        //Fake Rate Application
                                        if (Fill_Once_ff && (!electron_Isol_Loose || !electron_Id) && (!muon_Isol_Loose || !muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 - mu_Debug_loose.size() == 2)) && (electron_.size() == 0 || (electron_.size() - electron_Debug_loose.size() == 0))) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_MMME_apply_ff", BareElectron[l].pt, BareMuon[k].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMME_apply_ff_Jet", fake_pt_ele, fake_pt_mu, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 14, BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                        }
                                        if (Fill_Once_fp && (!electron_Isol_Loose || !electron_Id) && (muon_Isol_Loose && muon_Id) && mu_.size() == 3 && (electron_.size() == 0 || (electron_.size() == 1 && electron_Debug_loose.size() == 1))) {
                                            Fill_Once_fp = false;
                                            plotFill("FakeRate_MMME_apply_fp", BareElectron[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMME_apply_fp_Jet", fake_pt_ele, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 24, BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                        }
                                        if (Fill_Once_pf && (electron_Isol_Loose && electron_Id) && (!muon_Isol_Loose || !muon_Id) && (mu_.size() == 2 || (mu_.size() == 3 && mu_Debug_loose.size() == 1)) && electron_.size() == 1) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_MMME_apply_pf", BareMuon[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_MMME_apply_pf_Jet", fake_pt_mu, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 34, BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                        }
                                        plotFill("Higgs_Mass_mmme_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 44, BareMuon[p], BareMuon[q], BareMuon[k], BareElectron[l]);
                                    }//end of fake apply
                                }
                            }
                        }
                    } //finosh good leading muon
                }// Finish muon trg and 2 good muon



            }// finish Only Muon


            //####################### Double Electron


            if (is_ele || is_tot) {


                bool Fill_Once_ff = true;
                bool Fill_Once_fp = true;
                bool Fill_Once_pf = true;
                bool Fill_Once_ff_v = true;
                bool Fill_Once_fp_v = true;
                bool Fill_Once_pf_v = true;
                bool fill_once_Estimate = true;

                // ABCD eett
                if (BareTau.size() > 1 && BareElectron.size() > 1 && Trigger) {
                    for (int i = 0; i < BareElectron.size(); i++) {
                        for (int j = i + 1; j < BareElectron.size(); j++) {
                            for (int k = 0; k < BareTau.size(); k++) {
                                for (int l = k + 1; l < BareTau.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(BareElectron[i], BareElectron[j]);
                                    double Higgs_Mass = InvarMass_2(BareTau[k], BareTau[l]);

                                    bool first_l_HighPt = BareElectron[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = BareElectron[i].charge * BareElectron[j].charge < 0;
                                    bool ele_Iso_1 = Iso_Ele_dBeta(BareElectron[i]) < loose_Iso_Ele;
                                    bool ele_Iso_2 = Iso_Ele_dBeta(BareElectron[j]) < loose_Iso_Ele;
                                    bool ele_Id_1 = EleMVANonTrigId(BareElectron[i]);
                                    bool ele_Id_2 = EleMVANonTrigId(BareElectron[j]);
                                    bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                    bool mu_Rejection = BareTau[k].discriminationByMuonMedium && BareTau[l].discriminationByMuonMedium;
                                    bool ele_Rejection = BareTau[k].discriminationByElectronMedium && BareTau[l].discriminationByElectronMedium;
                                    bool tau_Iso_Tight_1 = BareTau[k].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Tight_2 = BareTau[l].byTightCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Medium_1 = BareTau[k].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Medium_2 = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Loose_1 = BareTau[k].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool tau_Iso_Loose_2 = BareTau[l].byLooseCombinedIsolationDeltaBetaCorr;
                                    bool H_Charge_b = BareTau[k].charge * BareTau[l].charge < 0;
                                    bool bjet_num = num_Bjet < 1;
                                    bool No_extra_lepton = electron_.size() == 2 && mu_.size() == 0;
                                    Cor_eff = getCorrFactor("eett", status_sample.c_str(), BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                    bool SumPtCut = getSumPtCut("eett", BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);

                                    bool preSelection = No_extra_lepton && Overlap_Dz && bjet_num && first_l_HighPt && Z_Charge_b && ele_Iso_1 && ele_Iso_2 && ele_Id_1 && ele_Id_2 && Leading_Z_Mass && mu_Rejection && ele_Rejection;
                                    bool FR_Application = SumPtCut && BareTau[k].pt > 20 && BareTau[l].pt > 20 && H_Charge_b;
                                    bool FR_Validation = BareTau[k].pt > 20 && BareTau[l].pt > 20 && !H_Charge_b;
                                    bool FR_Estimation_SS = fill_once_Estimate && !H_Charge_b && BareTau[k].pt > 10 && BareTau[l].pt > 10;



                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************
                                    if (preSelection && BareTau[k].pt > 10 && BareTau[l].pt > 10) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 95, BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        //                                            if (Fill_Once_ff && !tau_Iso_Tight_1 && !tau_Iso_Tight_2 && tau_.size() == 0) {
                                        if (Fill_Once_ff && !tau_Iso_Tight_1 && !tau_Iso_Tight_2) {
                                            plotFill("FakeRate_EETT_apply_ff", BareTau[k].pt, BareTau[l].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_ff = false;
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 15, BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_fp && !tau_Iso_Tight_1 && tau_Iso_Tight_2 && tau_.size() == 1) {
                                        if (Fill_Once_fp && !tau_Iso_Tight_1 && tau_Iso_Tight_2) {
                                            plotFill("FakeRate_EETT_apply_fp", BareTau[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_fp = false;
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 25, BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_pf && tau_Iso_Tight_1 && !tau_Iso_Tight_2 && tau_.size() == 1) {
                                        if (Fill_Once_pf && tau_Iso_Tight_1 && !tau_Iso_Tight_2) {
                                            plotFill("FakeRate_EETT_apply_pf", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_pf = false;
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 35, BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_eett_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 45, BareElectron[i], BareElectron[j], BareTau[k], BareTau[l]);
                                    }
                                    //*********************************************************************************
                                    //***************************Fake Rate Application Validation ***************************
                                    //*********************************************************************************
                                    if (preSelection && FR_Validation) {
                                        plotFill("Higgs_Mass_eett_ABCD_Validation", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);

                                        //Fake Rate Application Validation
                                        //                                            if (!tau_Iso_Loose_1 && !tau_Iso_Loose_2 && tau_.size() == 0) {
                                        if (Fill_Once_ff_v && !tau_Iso_Loose_1 && !tau_Iso_Loose_2) {
                                            plotFill("Validation_FakeRate_EETT_apply_ff", BareTau[k].pt, BareTau[l].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_ff_v = false;
                                        }
                                        //                                            if (!tau_Iso_Loose_1 && tau_Iso_Loose_2 && tau_.size() == 1) {
                                        if (Fill_Once_fp_v && !tau_Iso_Loose_1 && tau_Iso_Loose_2) {
                                            plotFill("ValidationFakeRate_EETT_apply_fp", BareTau[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_fp_v = false;
                                        }
                                        //                                            if (tau_Iso_Loose_1 && !tau_Iso_Loose_2 && tau_.size() == 1) {
                                        if (Fill_Once_pf_v && tau_Iso_Loose_1 && !tau_Iso_Loose_2) {
                                            plotFill("ValidationFakeRate_EETT_apply_pf", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            Fill_Once_pf_v = false;
                                        }//end of validation
                                    }//end fake rate application
                                    //*****
                                }
                            }
                        }
                    }
                }
                //****************************************************
                //eemt ABCD
                Fill_Once_ff = true;
                Fill_Once_fp = true;
                Fill_Once_pf = true;

                if (BareTau.size() > 0 && BareMuon.size() > 0 && BareElectron.size() > 1 && Trigger) {
                    for (int i = 0; i < BareElectron.size(); i++) {
                        for (int j = i + 1; j < BareElectron.size(); j++) {
                            for (int k = 0; k < BareMuon.size(); k++) {
                                for (int l = 0; l < BareTau.size(); l++) {

                                    double Zboson_Mass = InvarMass_2(BareElectron[i], BareElectron[j]);
                                    double Higgs_Mass = InvarMass_2(BareMuon[k], BareTau[l]);

                                    bool first_l_HighPt = BareElectron[i].pt > HighPt_Lep;
                                    bool Z_Charge_b = BareElectron[i].charge * BareElectron[j].charge < 0;
                                    bool ele_Iso_1 = Iso_Ele_dBeta(BareElectron[i]) < loose_Iso_Ele;
                                    bool ele_Iso_2 = Iso_Ele_dBeta(BareElectron[j]) < loose_Iso_Ele;
                                    bool ele_Id_1 = EleMVANonTrigId(BareElectron[i]);
                                    bool ele_Id_2 = EleMVANonTrigId(BareElectron[j]);
                                    bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                                    bool Overlap_Dz = OverLapWithTaus(BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                    bool tau_Isol = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool Muon_Isol_Tight = Iso_Mu_dBeta(BareMuon[k]) < tight_Iso_Mu;
                                    bool Muon_Isol_Loose = Iso_Mu_dBeta(BareMuon[k]) < loose_Iso_Mu;
                                    bool Muon_Id = Id_Mu(BareMuon[k]);
                                    bool H_Charge_b = BareTau[l].charge * BareMuon[k].charge < 0;
                                    bool tau_Mu_Veto = BareTau[l].discriminationByMuonTight;
                                    bool No_extra_lepton = electron_.size() == 2;
                                    bool bjet_num = num_Bjet < 1;
                                    bool SumPtCut = getSumPtCut("eemt", BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                    Cor_eff = getCorrFactor("eemt", status_sample.c_str(), BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                    fake_pt = Find_Closet_Jet(BareMuon[k], m);

                                    bool preSelection = bjet_num && Overlap_Dz && tau_Mu_Veto && ele_Iso_1 && ele_Iso_2 && ele_Id_1 && ele_Id_2 && first_l_HighPt && Z_Charge_b && Leading_Z_Mass;
                                    bool FR_Application = SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
                                    //                                            bool FR_Validation =
                                    bool FR_Estimation_tau0 = BareTau[l].pt > 0 && !H_Charge_b;
                                    bool FR_Estimation_tau10 = BareTau[l].pt > 10 && !H_Charge_b;

                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************
                                    if (preSelection) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 96, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        //                                                if (Fill_Once_ff && !tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 0 || (mu_.size() == 1 && mu_Debug.size() == 1)) && tau_.size() == 0) {
                                        if (Fill_Once_ff && !tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 0 || (mu_.size() == 1 && mu_Debug.size() == 1))) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_EEMT_apply_ff", BareTau[l].pt, BareMuon[k].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEMT_apply_ff_Jet", BareTau[l].pt, fake_pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 16, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                        //                                                if (Fill_Once_fp && !tau_Isol && (Muon_Isol_Tight && Muon_Id) && mu_.size() == 1 && tau_.size() == 0) {
                                        if (Fill_Once_fp && !tau_Isol && (Muon_Isol_Tight && Muon_Id) && mu_.size() == 1) {
                                            Fill_Once_fp = false;
                                            plotFill("FakeRate_EEMT_apply_fp", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 26, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                        //                                                if (Fill_Once_pf && tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 0 || (mu_.size() == 1 && mu_Debug.size() == 1)) && tau_.size() == 1) {
                                        if (Fill_Once_pf && tau_Isol && (!Muon_Isol_Tight || !Muon_Id) && (mu_.size() == 0 || (mu_.size() == 1 && mu_Debug.size() == 1))) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_EEMT_apply_pf", BareMuon[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEMT_apply_pf_Jet", fake_pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 36, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_eemt_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 46, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                    }//end of fake apply
                                    //*********************************************************************************
                                    //***************************Fake Rate Estimation ***************************
                                    //*********************************************************************************
                                    if (preSelection && FR_Estimation_tau0) {
                                        //Fake rate tau Pt > 10 GeV
                                        //Denumerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2) {
                                            plotFill("FakeRate_MT_Muon_Pt_Before_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Pt_Before_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Pt_Before_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 56, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                        //Numerator Tight
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2 && Muon_Id && Muon_Isol_Tight) {
                                            plotFill("FakeRate_MT_Muon_Tight_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Tight_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Tight_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 66, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                        //Numerator Loose
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2 && Muon_Id && Muon_Isol_Loose) {
                                            plotFill("FakeRate_MT_Muon_Loose_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Loose_After_0", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Loose_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 76, BareElectron[i], BareElectron[j], BareMuon[k], BareTau[l]);
                                        }
                                    }// tau pt > 0
                                    //Fake rate tau Pt > 10 GeV
                                    if (preSelection && FR_Estimation_tau10) {
                                        plotFill("FakeRate_EEMT_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        plotFill("FakeRate_MT_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        if (tau_Isol) {
                                            plotFill("FakeRate_EEMT_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                        }
                                        //Denumerator
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2) {
                                            plotFill("FakeRate_MT_Muon_Pt_Before_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Pt_Before_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Pt_Before_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator Tight
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2 && Muon_Id && Muon_Isol_Tight) {
                                            plotFill("FakeRate_MT_Muon_Tight_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Tight_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Tight_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator Loose
                                        if (WZ_Rej(m, BareMuon[k]) && BareMuon.size() < 2 && Muon_Id && Muon_Isol_Loose) {
                                            plotFill("FakeRate_MT_Muon_Loose_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEMT_Muon_Loose_After_10", BareMuon[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_MT_Muon_Loose_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                    }// tau pt > 10
                                    //*****
                                }
                            }
                        }
                    }
                }

                //****************************************************




                if (BareElectron.size() > 1 && Trigger) {
                    double Refer_Mass = 1000;
                    double Mass_LeadingZ;
                    int p, q;
                    bool Selected_Lead_Z = false;
                    for (int i = 0; i < BareElectron.size(); i++) {
                        for (int j = i + 1; j < BareElectron.size(); j++) {

                            double Zboson_Mass = InvarMass_2(BareElectron[i], BareElectron[j]);
                            double Zboson_Mass_diff = fabs(Zboson_Mass - nominalM_Z);

                            bool ele_Iso_1 = Iso_Ele_dBeta(BareElectron[i]) < loose_Iso_Ele;
                            bool ele_Iso_2 = Iso_Ele_dBeta(BareElectron[j]) < loose_Iso_Ele;
                            bool ele_Id_1 = EleMVANonTrigId(BareElectron[i]);
                            bool ele_Id_2 = EleMVANonTrigId(BareElectron[j]);
                            bool first_l_HighPt = BareElectron[i].pt > 20;
                            bool Z_Charge_b = BareElectron[i].charge * BareElectron[j].charge < 0;
                            bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                            bool bjet_num = num_Bjet < 1;
                            if (bjet_num && first_l_HighPt && Z_Charge_b && Leading_Z_Mass && ele_Iso_1 && ele_Iso_2 && ele_Id_1 && ele_Id_2) {
                                if (Zboson_Mass_diff < Refer_Mass) {
                                    Refer_Mass = Zboson_Mass_diff;
                                    p = i;
                                    q = j;
                                    Mass_LeadingZ = Zboson_Mass;
                                    Selected_Lead_Z = true;
                                }
                            }
                        }
                    }

                    if (Selected_Lead_Z) {


                        //****///*****************///

                        //eeet ABCD
                        Fill_Once_ff = true;
                        Fill_Once_fp = true;
                        Fill_Once_pf = true;

                        if (BareTau.size() > 0 && BareElectron.size() > 2) {

                            for (int k = 0; k < BareElectron.size(); k++) {
                                for (int l = 0; l < BareTau.size(); l++) {

                                    double Higgs_Mass = InvarMass_2(BareElectron[k], BareTau[l]);

                                    bool Overlap_Dz = OverLapWithTaus(BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                    bool electron_Isol_Tight = Iso_Ele_dBeta(BareElectron[k]) < tight_Iso_Ele;
                                    bool electron_Isol_Loose = Iso_Ele_dBeta(BareElectron[k]) < loose_Iso_Ele;
                                    bool electron_Id = EleMVANonTrigId(BareElectron[k]);
                                    bool tau_Isol = BareTau[l].byMediumCombinedIsolationDeltaBetaCorr;
                                    bool H_Charge_b = BareTau[l].charge * BareElectron[k].charge < 0;
                                    bool ele_Rejection = BareTau[l].discriminationByElectronMVA;
                                    bool ele_numHit = BareElectron[k].numHitEleInner < 1;
                                    bool No_extra_lepton = mu_.size() == 0;
                                    bool SumPtCut = getSumPtCut("eeet", BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                    Cor_eff = getCorrFactor("eeet", status_sample.c_str(), BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                    fake_pt = Find_Closet_Jet(BareElectron[k], m);

                                    bool preSelection = Overlap_Dz && ele_numHit && ele_Rejection;
                                    bool FR_Application = SumPtCut && No_extra_lepton && BareTau[l].pt > 20 && H_Charge_b;
                                    //                                            bool FR_Validation =
                                    bool FR_Estimation_tau0 = BareTau[l].pt > 0 && !H_Charge_b;
                                    bool FR_Estimation_tau10 = BareTau[l].pt > 10 && !H_Charge_b;

                                    //*********************************************************************************
                                    //***************************Fake Rate Application ***************************
                                    //*********************************************************************************
                                    if (preSelection) {
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 97, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        //                                            if (Fill_Once_ff && !tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 2 || (electron_.size() == 3 && electron_Debug.size() == 1)) && tau_.size() == 0) {
                                        if (Fill_Once_ff && !tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 2 || (electron_.size() == 3 && electron_Debug.size() == 1))) {
                                            Fill_Once_ff = false;
                                            plotFill("FakeRate_EEET_apply_ff", BareTau[l].pt, BareElectron[k].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEET_apply_ff_Jet", BareTau[l].pt, fake_pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 17, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_fp && !tau_Isol && (electron_Isol_Tight && electron_Id) && electron_.size() == 3 && tau_.size() == 0) {
                                        if (Fill_Once_fp && !tau_Isol && (electron_Isol_Tight && electron_Id) && electron_.size() == 3) {
                                            Fill_Once_fp = false;
                                            plotFill("FakeRate_EEET_apply_fp", BareTau[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 27, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                        //                                            if (Fill_Once_pf && tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 2 || (electron_.size() == 3 && electron_Debug.size() == 1)) && tau_.size() == 1) {
                                        if (Fill_Once_pf && tau_Isol && (!electron_Isol_Tight || !electron_Id) && (electron_.size() == 2 || (electron_.size() == 3 && electron_Debug.size() == 1))) {
                                            Fill_Once_pf = false;
                                            plotFill("FakeRate_EEET_apply_pf", BareElectron[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEET_apply_pf_Jet", fake_pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 37, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                        plotFill("Higgs_Mass_eeet_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 47, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                    }//end of fake apply

                                    //*********************************************************************************
                                    //***************************Fake Rate Estimation ***************************
                                    //*********************************************************************************
                                    //tau fake rate
                                    if (preSelection && FR_Estimation_tau0) {

                                        //Denumerator
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4) {
                                            plotFill("FakeRate_ET_Electron_Pt_Before_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Pt_Before_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Pt_Before_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 57, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                        //Numerator Tight
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4 && electron_Id && electron_Isol_Tight) {
                                            plotFill("FakeRate_ET_Electron_Tight_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Tight_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Tight_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 67, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                        //Numerator Loose
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4 && electron_Id && electron_Isol_Loose) {
                                            plotFill("FakeRate_ET_Electron_Loose_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Loose_After_0", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Loose_After_0_Jet", fake_pt, 200, 0, 200);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 77, BareElectron[p], BareElectron[q], BareElectron[k], BareTau[l]);
                                        }
                                    }// tau Pt > 0

                                    //Fake Rate Estimation
                                    if (preSelection && FR_Estimation_tau10) {
                                        //tau fake rate
                                        plotFill("FakeRate_EEET_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        plotFill("FakeRate_ET_Tau_Pt_Before_10", BareTau[l].pt, 200, 0, 200);
                                        if (tau_Isol) {
                                            plotFill("FakeRate_EEET_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Tau_Pt_After_10", BareTau[l].pt, 200, 0, 200);
                                        }

                                        ////Denumerator
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4) {
                                            plotFill("FakeRate_ET_Electron_Pt_Before_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Pt_Before_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Pt_Before_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator Tight
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4 && electron_Id && electron_Isol_Tight) {
                                            plotFill("FakeRate_ET_Electron_Tight_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Tight_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Tight_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                        //Numerator Loose
                                        if (WZ_Rej(m, BareElectron[k]) && BareElectron.size() < 4 && electron_Id && electron_Isol_Loose) {
                                            plotFill("FakeRate_ET_Electron_Loose_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_EEET_Electron_Loose_After_10", BareElectron[k].pt, 200, 0, 200);
                                            plotFill("FakeRate_ET_Electron_Loose_After_10_Jet", fake_pt, 200, 0, 200);
                                        }
                                    }// tau Pt >1 0
                                }
                            }
                        }
                        //**********************************

                        //**********************************************
                        //eeem
                        Fill_Once_ff = true;
                        Fill_Once_fp = true;
                        Fill_Once_pf = true;

                        if (BareMuon.size() > 0 && BareElectron.size() > 2) {


                            for (int k = 0; k < BareElectron.size(); k++) {
                                for (int l = 0; l < BareMuon.size(); l++) {

                                    double Higgs_Mass = InvarMass_2(BareMuon[l], BareElectron[k]);


                                    bool Overlap_Dz = OverLapWithTaus(BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                    bool muon_Isol_Loose = Iso_Mu_dBeta(BareMuon[l]) < loose_Iso_Mu;
                                    bool electron_Isol_Loose = Iso_Ele_dBeta(BareElectron[k]) < loose_Iso_Ele;
                                    bool muon_Id = Id_Mu(BareMuon[l]);
                                    bool electron_Id = EleMVANonTrigId(BareElectron[k]);
                                    bool H_Charge_b = BareElectron[k].charge * BareMuon[l].charge < 0;
                                    bool No_extra_lepton = tau_.size() < 10; //strange cut
                                    Cor_eff = getCorrFactor("eeem", status_sample.c_str(), BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                    bool SumPtCut = getSumPtCut("eeem", BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                    double fake_pt_mu = Find_Closet_Jet(BareMuon[l], m);
                                    double fake_pt_ele = Find_Closet_Jet(BareElectron[k], m);

                                    bool preSelection = true;
                                    bool FR_Application = SumPtCut && No_extra_lepton && Overlap_Dz && H_Charge_b;
                                    //*********************************************************************************
                                    //***************************Fake Rate Estimation ***************************
                                    //*********************************************************************************
                                    if (preSelection) {

                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 98, BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                    }
                                    if (preSelection && FR_Application) {

                                        //Fake Rate Application
                                        if (Fill_Once_ff && (!electron_Isol_Loose || !electron_Id) && (!muon_Isol_Loose || !muon_Id) && (electron_.size() == 2 || electron_.size() - electron_Debug_loose.size() == 2) && (mu_.size() == 0 || mu_.size() - mu_Debug_loose.size() == 0)) {
                                            Fill_Once_ff = false;
                                            plotFill("SizeEleMu_EEEM", BareElectron.size(), BareMuon.size(), 10, 0, 10, 10, 0, 10);
                                            plotFill("FakeRate_EEEM_apply_ff", BareElectron[k].pt, BareMuon[l].pt, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEEM_apply_ff_Jet", fake_pt_ele, fake_pt_mu, 200, 0, 200, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 18, BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                        }
                                        if (Fill_Once_fp && (!electron_Isol_Loose || !electron_Id) && (muon_Isol_Loose && muon_Id) && (electron_.size() == 2 || electron_.size() - electron_Debug_loose.size() == 2) && mu_.size() == 1) {
                                            Fill_Once_fp = false;
                                            plotFill("SizeEle_EEEM", BareElectron.size(), 10, 0, 10);
                                            plotFill("FakeRate_EEEM_apply_fp", BareElectron[k].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEEM_apply_fp_Jet", fake_pt_ele, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 28, BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                        }
                                        if (Fill_Once_pf && (electron_Isol_Loose && electron_Id) && (!muon_Isol_Loose || !muon_Id) && electron_.size() == 3 && (mu_.size() == 0 || mu_.size() - mu_Debug_loose.size() == 0)) {
                                            Fill_Once_pf = false;
                                            plotFill("SizeMu_EEEM", BareMuon.size(), 10, 0, 10);
                                            plotFill("FakeRate_EEEM_apply_pf", BareMuon[l].pt, 200, 0, 200, PU_Weight * Cor_eff);
                                            plotFill("FakeRate_EEEM_apply_pf_Jet", fake_pt_mu, 200, 0, 200, PU_Weight * Cor_eff);
                                            fillTree(Run_Tree, m, PU_Weight, Cor_eff, 38, BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                        }
                                        plotFill("Higgs_Mass_eeem_ABCD", Higgs_Mass, bin_size, 0, bin_max, PU_Weight * Cor_eff);
                                        fillTree(Run_Tree, m, PU_Weight, Cor_eff, 48, BareElectron[p], BareElectron[q], BareElectron[k], BareMuon[l]);
                                    }//end of fake apply
                                }
                            }
                        }//eeem
                    } //selected first Z
                }//more than 1 good electron
            }//only Electron



            //********************************************************
            //********************************************************
            //********************************************************
            //********************************************************
            //********************************************************
            //********************************************************
            //********************************************************
            //********************************************************
            //************

            if ((is_mu || is_tot) && BareMuon.size() > 1 && Trigger) {
                double Refer_Mass = 1000;
                double Mass_LeadingZ;
                int p, q;
                bool Selected_Lead_Z = false;
                for (int i = 0; i < BareMuon.size(); i++) {
                    for (int j = i + 1; j < BareMuon.size(); j++) {

                        double Zboson_Mass = InvarMass_2(BareMuon[i], BareMuon[j]);
                        double Zboson_Mass_diff = fabs(Zboson_Mass - nominalM_Z);

                        bool mu_Iso_1 = Iso_Mu_dBeta(BareMuon[i]) < loose_Iso_Mu;
                        bool mu_Iso_2 = Iso_Mu_dBeta(BareMuon[j]) < loose_Iso_Mu;
                        bool mu_Id_1 = Id_Mu(BareMuon[i]);
                        bool mu_Id_2 = Id_Mu(BareMuon[j]);
                        bool first_l_HighPt = BareMuon[i].pt > 20;
                        bool Z_Charge_b = BareMuon[i].charge * BareMuon[j].charge < 0;
                        bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                        bool bjet_num = num_Bjet < 1;
                        if (bjet_num && first_l_HighPt && Z_Charge_b && Leading_Z_Mass && mu_Iso_1 && mu_Iso_2 && mu_Id_1 && mu_Id_2) {
                            if (Zboson_Mass_diff < Refer_Mass) {
                                Refer_Mass = Zboson_Mass_diff;
                                p = i;
                                q = j;
                                Mass_LeadingZ = Zboson_Mass;
                                Selected_Lead_Z = true;

                            }
                        }
                    }
                }
                if (Selected_Lead_Z) {



                    //  Di-Muon Mass Plots
                    Cor_eff = getCorrFactor("mm", status_sample.c_str(), BareMuon[p], BareMuon[q], BareMuon[p], BareMuon[q]);
                    plotFill("MM_Mass_PUCor", Mass_LeadingZ, bin_size, 0., bin_max, PU_Weight * Cor_eff);
                    plotFill("MM_Mass_PU", Mass_LeadingZ, bin_size, 0., bin_max, PU_Weight);
                    plotFill("MM_Mass_Cor", Mass_LeadingZ, bin_size, 0., bin_max, Cor_eff);
                    plotFill("MM_Mass_", Mass_LeadingZ, bin_size, 0., bin_max);

                    //*****************////////////************////////////
                    //Muon Fakerate Measurement
                    //                        if (BareMuon.size() > 0) {
                    if (BareMuon.size() == 3 && p < 3 && q < 3 && fabs(Mass_LeadingZ - nominalM_Z) < 10) {
                        for (int y = 0; y < BareMuon.size(); y++) {
                            if (WZ_Rej(m, BareMuon[y]) && OverLap(BareMuon[q], BareMuon[p], BareMuon[y])) {
                                plotFill("FakeRate_Muon_Before", BareMuon[y].pt, 200, 0, 200);
                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 101, BareMuon[p], BareMuon[q], BareMuon[y], BareMuon[y]);
                                if (Iso_Mu_dBeta(BareMuon[y]) < tight_Iso_Mu && Id_Mu(BareMuon[y])) {
                                    plotFill("FakeRate_Muon_Tight_After", BareMuon[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 102, BareMuon[p], BareMuon[q], BareMuon[y], BareMuon[y]);
                                }
                                if (Iso_Mu_dBeta(BareMuon[y]) < loose_Iso_Mu && Id_Mu(BareMuon[y])) {
                                    plotFill("FakeRate_Muon_Loose_After", BareMuon[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 103, BareMuon[p], BareMuon[q], BareMuon[y], BareMuon[y]);
                                }

                                fake_pt = Find_Closet_Jet(BareMuon[y], m);
                                plotFill("FakeRate_Muon_Before_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Mu_dBeta(BareMuon[y]) < tight_Iso_Mu && Id_Mu(BareMuon[y]))
                                    plotFill("FakeRate_Muon_Tight_After_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Mu_dBeta(BareMuon[y]) < loose_Iso_Mu && Id_Mu(BareMuon[y]))
                                    plotFill("FakeRate_Muon_Loose_After_Jet", fake_pt, 200, 0, 200);
                            }
                        }
                    }
                    //Electron Fakerate Measurement
                    //                        if (BareElectron.size() > 0) {
                    if (BareElectron.size() == 1 && fabs(Mass_LeadingZ - nominalM_Z) < 10) {
                        for (int y = 0; y < BareElectron.size(); y++) {
                            if (WZ_Rej(m, BareElectron[y]) && OverLap(BareMuon[q], BareMuon[p], BareElectron[y])) {
                                plotFill("FakeRate_Electron_Before", BareElectron[y].pt, 200, 0, 200);
                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 104, BareMuon[p], BareMuon[q], BareElectron[y], BareElectron[y]);
                                if (Iso_Ele_dBeta(BareElectron[y]) < tight_Iso_Ele && EleMVANonTrigId(BareElectron[y])) {
                                    plotFill("FakeRate_Electron_Tight_After", BareElectron[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 105, BareMuon[p], BareMuon[q], BareElectron[y], BareElectron[y]);
                                }
                                if (Iso_Ele_dBeta(BareElectron[y]) < loose_Iso_Ele && EleMVANonTrigId(BareElectron[y])) {
                                    plotFill("FakeRate_Electron_Loose_After", BareElectron[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 106, BareMuon[p], BareMuon[q], BareElectron[y], BareElectron[y]);
                                }

                                fake_pt = Find_Closet_Jet(BareElectron[y], m);
                                plotFill("FakeRate_Electron_Before_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Ele_dBeta(BareElectron[y]) < tight_Iso_Ele && EleMVANonTrigId(BareElectron[y]))
                                    plotFill("FakeRate_Electron_Tight_After_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Ele_dBeta(BareElectron[y]) < loose_Iso_Ele && EleMVANonTrigId(BareElectron[y]))
                                    plotFill("FakeRate_Electron_Loose_After_Jet", fake_pt, 200, 0, 200);
                            }
                        }
                    }
                }//good Z
            }
            //*************
            //*************
            //*************


            if ((is_ele || is_tot) && BareElectron.size() > 1 && Trigger) {
                double Refer_Mass = 1000;
                double Mass_LeadingZ;
                int p, q;
                bool Selected_Lead_Z = false;
                for (int i = 0; i < BareElectron.size(); i++) {
                    for (int j = i + 1; j < BareElectron.size(); j++) {

                        double Zboson_Mass = InvarMass_2(BareElectron[i], BareElectron[j]);
                        double Zboson_Mass_diff = fabs(Zboson_Mass - nominalM_Z);

                        bool ele_Iso_1 = Iso_Ele_dBeta(BareElectron[i]) < loose_Iso_Ele;
                        bool ele_Iso_2 = Iso_Ele_dBeta(BareElectron[j]) < loose_Iso_Ele;
                        bool ele_Id_1 = EleMVANonTrigId(BareElectron[i]);
                        bool ele_Id_2 = EleMVANonTrigId(BareElectron[j]);
                        bool first_l_HighPt = BareElectron[i].pt > 20;
                        bool Z_Charge_b = BareElectron[i].charge * BareElectron[j].charge < 0;
                        bool Leading_Z_Mass = Zboson_Mass > z_lowMass && Zboson_Mass < z_highMass;
                        bool bjet_num = num_Bjet < 1;
                        if (bjet_num && first_l_HighPt && Z_Charge_b && Leading_Z_Mass && ele_Iso_1 && ele_Iso_2 && ele_Id_1 && ele_Id_2) {
                            if (Zboson_Mass_diff < Refer_Mass) {
                                Refer_Mass = Zboson_Mass_diff;
                                p = i;
                                q = j;
                                Mass_LeadingZ = Zboson_Mass;
                                Selected_Lead_Z = true;
                            }
                        }
                    }
                }



                if (Selected_Lead_Z) {


                    //  Di-Muon Mass Plots
                    Cor_eff = getCorrFactor("ee", status_sample.c_str(), BareElectron[p], BareElectron[q], BareElectron[p], BareElectron[q]);
                    plotFill("EE_Mass_PUCor", Mass_LeadingZ, bin_size, 0., bin_max, PU_Weight * Cor_eff);
                    plotFill("EE_Mass_PU", Mass_LeadingZ, bin_size, 0., bin_max, PU_Weight);
                    plotFill("EE_Mass_Cor", Mass_LeadingZ, bin_size, 0., bin_max, Cor_eff);
                    plotFill("EE_Mass_", Mass_LeadingZ, bin_size, 0., bin_max);

                    //****///*****************///
                    //Muon Fakerate Measurement
                    //                        if (BareMuon.size() > 0) {
                    if (BareMuon.size() == 1 && fabs(Mass_LeadingZ - nominalM_Z) < 10) {
                        for (int y = 0; y < BareMuon.size(); y++) {
                            if (WZ_Rej(m, BareMuon[y]) && OverLap(BareElectron[q], BareElectron[p], BareMuon[y])) {
                                plotFill("FakeRate_Muon_Before", BareMuon[y].pt, 200, 0, 200);
                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 101, BareElectron[p], BareElectron[q], BareMuon[y], BareMuon[y]);

                                if (Iso_Mu_dBeta(BareMuon[y]) < tight_Iso_Mu && Id_Mu(BareMuon[y])) {
                                    plotFill("FakeRate_Muon_Tight_After", BareMuon[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 102, BareElectron[p], BareElectron[q], BareMuon[y], BareMuon[y]);
                                }
                                if (Iso_Mu_dBeta(BareMuon[y]) < loose_Iso_Mu && Id_Mu(BareMuon[y])) {
                                    plotFill("FakeRate_Muon_Loose_After", BareMuon[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 103, BareElectron[p], BareElectron[q], BareMuon[y], BareMuon[y]);
                                }


                                double fake_pt = Find_Closet_Jet(BareMuon[y], m);
                                plotFill("FakeRate_Muon_Before_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Mu_dBeta(BareMuon[y]) < tight_Iso_Mu && Id_Mu(BareMuon[y]))
                                    plotFill("FakeRate_Muon_Tight_After_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Mu_dBeta(BareMuon[y]) < loose_Iso_Mu && Id_Mu(BareMuon[y]))
                                    plotFill("FakeRate_Muon_Loose_After_Jet", fake_pt, 200, 0, 200);

                            }
                        }
                    }
                    //Electron Fakerate Measurement
                    //                        if (BareElectron.size() > 0) {
                    if (BareElectron.size() == 3 && p < 3 && q < 3 && fabs(Mass_LeadingZ - nominalM_Z) < 10) {
                        for (int y = 0; y < BareElectron.size(); y++) {
                            if (WZ_Rej(m, BareElectron[y]) && OverLap(BareElectron[q], BareElectron[p], BareElectron[y])) {
                                plotFill("FakeRate_Electron_Before", BareElectron[y].pt, 200, 0, 200);
                                fillTree(Run_Tree, m, PU_Weight, Cor_eff, 104, BareElectron[p], BareElectron[q], BareElectron[y], BareElectron[y]);
                                if (Iso_Ele_dBeta(BareElectron[y]) < tight_Iso_Ele && EleMVANonTrigId(BareElectron[y])) {
                                    plotFill("FakeRate_Electron_Tight_After", BareElectron[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 105, BareElectron[p], BareElectron[q], BareElectron[y], BareElectron[y]);
                                }
                                if (Iso_Ele_dBeta(BareElectron[y]) < loose_Iso_Ele && EleMVANonTrigId(BareElectron[y])) {
                                    plotFill("FakeRate_Electron_Loose_After", BareElectron[y].pt, 200, 0, 200);
                                    fillTree(Run_Tree, m, PU_Weight, Cor_eff, 106, BareElectron[p], BareElectron[q], BareElectron[y], BareElectron[y]);
                                }


                                double fake_pt = Find_Closet_Jet(BareElectron[y], m);
                                plotFill("FakeRate_Electron_Before_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Ele_dBeta(BareElectron[y]) < tight_Iso_Ele && EleMVANonTrigId(BareElectron[y]))
                                    plotFill("FakeRate_Electron_Tight_After_Jet", fake_pt, 200, 0, 200);
                                if (Iso_Ele_dBeta(BareElectron[y]) < loose_Iso_Ele && EleMVANonTrigId(BareElectron[y]))
                                    plotFill("FakeRate_Electron_Loose_After_Jet", fake_pt, 200, 0, 200);

                            }
                        }
                    }
                }
            }




        }//loop over events


        delete rootTree;
    }
    delete m;


    fout->cd();

    Run_Tree->Write();

    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();

    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();

    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();



    fout->Close();
    return 0;
}
