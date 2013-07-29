//########################################################################
//########################################################################
//########################################################################
//########################################################################
// This is to make some control plots looseing LT cuts and isolation
//########################################################################
//########################################################################
//########################################################################
//########################################################################
#include "tr_Tree.h"

int main(int argc, char** argv) {
    std::string chanelType = *(argv + 1);
    std::string givenTauIso = *(argv + 2);
    float float_LepIso;
    float float_LTCut;
    if (argc > 1) {
        float_LepIso = atof(argv[3]); // alternative strtod
        float_LTCut = atof(argv[4]); // alternative strtod
    }
    std::string out = *(argv + 5);
    std::string input = *(argv + 6);

    //PRINTING THE OUTPUT name
    cout << "\n\n\n OUTPUT NAME IS:    " << out << endl;
    TFile *fout = TFile::Open(out.c_str(), "RECREATE");

    using namespace std;

    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    //
    TFile *f_Double = new TFile(input.c_str());
    TTree *Run_Tree = (TTree*) f_Double->Get("RLE_tree");
    Run_Tree->AddFriend("Mass_tree");



    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(1);

    Run_Tree->SetBranchAddress("Channel", &Channel);
    Run_Tree->SetBranchAddress("Run", &Run);
    Run_Tree->SetBranchAddress("Lumi", &Lumi);
    Run_Tree->SetBranchAddress("Event", &Event);
    Run_Tree->SetBranchAddress("IMass", &IMass);
    Run_Tree->SetBranchAddress("ZMass", &ZMass);
    Run_Tree->SetBranchAddress("HMass", &HMass);
    Run_Tree->SetBranchAddress("met", &met);
    Run_Tree->SetBranchAddress("pfmet", &pfmet);
    Run_Tree->SetBranchAddress("metPhi", &metPhi);
    Run_Tree->SetBranchAddress("pfmetPhi", &pfmetPhi);
    Run_Tree->SetBranchAddress("covMet11", &covMet11);
    Run_Tree->SetBranchAddress("covMet12", &covMet12);
    Run_Tree->SetBranchAddress("covMet21", &covMet21);
    Run_Tree->SetBranchAddress("covMet22", &covMet22);
    Run_Tree->SetBranchAddress("pfcovMet11", &pfcovMet11);
    Run_Tree->SetBranchAddress("pfcovMet12", &pfcovMet12);
    Run_Tree->SetBranchAddress("pfcovMet21", &pfcovMet21);
    Run_Tree->SetBranchAddress("pfcovMet22", &pfcovMet22);
    Run_Tree->SetBranchAddress("num_PV", &num_PV);
    Run_Tree->SetBranchAddress("num_bjet", &num_bjet);
    Run_Tree->SetBranchAddress("num_goodjet", &num_goodjet);
    Run_Tree->SetBranchAddress("eff_Correction", &eff_Correction);
    Run_Tree->SetBranchAddress("pu_Weight", &pu_Weight);

    Run_Tree->SetBranchAddress("mu_Size", &mu_Size);
    Run_Tree->SetBranchAddress("BareMuon_Size", &BareMuon_Size);
    Run_Tree->SetBranchAddress("electron_Size", &electron_Size);
    Run_Tree->SetBranchAddress("BareElectron_Size", &BareElectron_Size);
    Run_Tree->SetBranchAddress("tau_Size", &tau_Size);
    Run_Tree->SetBranchAddress("BareTau_Size", &BareTau_Size);
    Run_Tree->SetBranchAddress("mu_partTight_Size", &mu_partTight_Size);
    Run_Tree->SetBranchAddress("ele_partTight_Size", &ele_partTight_Size);

    Run_Tree->SetBranchAddress("l1M", &l1M);
    Run_Tree->SetBranchAddress("l1E", &l1E);
    Run_Tree->SetBranchAddress("l1Px", &l1Px);
    Run_Tree->SetBranchAddress("l1Py", &l1Py);
    Run_Tree->SetBranchAddress("l1Pz", &l1Pz);
    Run_Tree->SetBranchAddress("l1Pt", &l1Pt);
    Run_Tree->SetBranchAddress("l1Eta", &l1Eta);
    Run_Tree->SetBranchAddress("l1Phi", &l1Phi);
    Run_Tree->SetBranchAddress("l1Charge", &l1Charge);
    Run_Tree->SetBranchAddress("l1_muId", &l1_muId);
    Run_Tree->SetBranchAddress("l1_muIso", &l1_muIso);
    Run_Tree->SetBranchAddress("l1_eleId", &l1_eleId);
    Run_Tree->SetBranchAddress("l1_eleIso", &l1_eleIso);
    Run_Tree->SetBranchAddress("l1_eleMVANonTrg", &l1_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l1_eleNumHit", &l1_eleNumHit);

    Run_Tree->SetBranchAddress("l2M", &l2M);
    Run_Tree->SetBranchAddress("l2E", &l2E);
    Run_Tree->SetBranchAddress("l2Px", &l2Px);
    Run_Tree->SetBranchAddress("l2Py", &l2Py);
    Run_Tree->SetBranchAddress("l2Pz", &l2Pz);
    Run_Tree->SetBranchAddress("l2Pt", &l2Pt);
    Run_Tree->SetBranchAddress("l2Eta", &l2Eta);
    Run_Tree->SetBranchAddress("l2Phi", &l2Phi);
    Run_Tree->SetBranchAddress("l2Charge", &l2Charge);
    Run_Tree->SetBranchAddress("l2_muId", &l2_muId);
    Run_Tree->SetBranchAddress("l2_muIso", &l2_muIso);
    Run_Tree->SetBranchAddress("l2_eleId", &l2_eleId);
    Run_Tree->SetBranchAddress("l2_eleIso", &l2_eleIso);
    Run_Tree->SetBranchAddress("l2_eleMVANonTrg", &l2_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l2_eleNumHit", &l2_eleNumHit);

    Run_Tree->SetBranchAddress("l3M", &l3M);
    Run_Tree->SetBranchAddress("l3E", &l3E);
    Run_Tree->SetBranchAddress("l3Px", &l3Px);
    Run_Tree->SetBranchAddress("l3Py", &l3Py);
    Run_Tree->SetBranchAddress("l3Pz", &l3Pz);
    Run_Tree->SetBranchAddress("l3Pt", &l3Pt);
    Run_Tree->SetBranchAddress("l3Eta", &l3Eta);
    Run_Tree->SetBranchAddress("l3Phi", &l3Phi);
    Run_Tree->SetBranchAddress("l3Charge", &l3Charge);
    Run_Tree->SetBranchAddress("l3_CloseJetPt", &l3_CloseJetPt);
    Run_Tree->SetBranchAddress("l3_CloseJetEta", &l3_CloseJetEta);
    Run_Tree->SetBranchAddress("l3_CloseJetPhi", &l3_CloseJetPhi);
    Run_Tree->SetBranchAddress("l3_muId_Loose", &l3_muId_Loose);
    Run_Tree->SetBranchAddress("l3_muId_Tight", &l3_muId_Tight);
    Run_Tree->SetBranchAddress("l3_muIso", &l3_muIso);
    Run_Tree->SetBranchAddress("l3_eleId_Loose", &l3_eleId_Loose);
    Run_Tree->SetBranchAddress("l3_eleId_Tight", &l3_eleId_Tight);
    Run_Tree->SetBranchAddress("l3_eleIso", &l3_eleIso);
    Run_Tree->SetBranchAddress("l3_eleMVANonTrg", &l3_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l3_eleNumHit", &l3_eleNumHit);
    Run_Tree->SetBranchAddress("l3_tauIsoVL", &l3_tauIsoVL);
    Run_Tree->SetBranchAddress("l3_tauIso3HitL", &l3_tauIso3HitL);
    Run_Tree->SetBranchAddress("l3_tauIso3HitM", &l3_tauIso3HitM);
    Run_Tree->SetBranchAddress("l3_tauIso3HitT", &l3_tauIso3HitT);
    Run_Tree->SetBranchAddress("l3_tauIsoL", &l3_tauIsoL);
    Run_Tree->SetBranchAddress("l3_tauIsoM", &l3_tauIsoM);
    Run_Tree->SetBranchAddress("l3_tauIsoT", &l3_tauIsoT);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2L", &l3_tauIsoMVA2L);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2M", &l3_tauIsoMVA2M);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2T", &l3_tauIsoMVA2T);
    Run_Tree->SetBranchAddress("l3_tauIsoMVA2raw", &l3_tauIsoMVA2raw);
    Run_Tree->SetBranchAddress("l3_tauRejMuL", &l3_tauRejMuL);
    Run_Tree->SetBranchAddress("l3_tauRejMu2L", &l3_tauRejMu2L);
    Run_Tree->SetBranchAddress("l3_tauRejMuM", &l3_tauRejMuM);
    Run_Tree->SetBranchAddress("l3_tauRejMu2M", &l3_tauRejMu2M);
    Run_Tree->SetBranchAddress("l3_tauRejMuT", &l3_tauRejMuT);
    Run_Tree->SetBranchAddress("l3_tauRejMu2T", &l3_tauRejMu2T);
    Run_Tree->SetBranchAddress("l3_tauRejEleL", &l3_tauRejEleL);
    Run_Tree->SetBranchAddress("l3_tauRejEleM", &l3_tauRejEleM);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA", &l3_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3L", &l3_tauRejEleMVA3L);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3M", &l3_tauRejEleMVA3M);
    Run_Tree->SetBranchAddress("l3_tauRejEleMVA3T", &l3_tauRejEleMVA3T);
    Run_Tree->SetBranchAddress("l3_RefJetPt", &l3_RefJetPt);
    Run_Tree->SetBranchAddress("l3_RefJetEta", &l3_RefJetEta);
    Run_Tree->SetBranchAddress("l3_RefJetPhi", &l3_RefJetPhi);


    Run_Tree->SetBranchAddress("l4M", &l4M);
    Run_Tree->SetBranchAddress("l4E", &l4E);
    Run_Tree->SetBranchAddress("l4Px", &l4Px);
    Run_Tree->SetBranchAddress("l4Py", &l4Py);
    Run_Tree->SetBranchAddress("l4Pz", &l4Pz);
    Run_Tree->SetBranchAddress("l4Pt", &l4Pt);
    Run_Tree->SetBranchAddress("l4Eta", &l4Eta);
    Run_Tree->SetBranchAddress("l4Phi", &l4Phi);
    Run_Tree->SetBranchAddress("l4Charge", &l4Charge);
    Run_Tree->SetBranchAddress("l4_muId_Loose", &l4_muId_Loose);
    Run_Tree->SetBranchAddress("l4_muId_Tight", &l4_muId_Tight);
    Run_Tree->SetBranchAddress("l4_muIso", &l4_muIso);
    Run_Tree->SetBranchAddress("l4_eleId_Loose", &l4_eleId_Loose);
    Run_Tree->SetBranchAddress("l4_eleId_Tight", &l4_eleId_Tight);
    Run_Tree->SetBranchAddress("l4_eleIso", &l4_eleIso);
    Run_Tree->SetBranchAddress("l4_eleMVANonTrg", &l4_eleMVANonTrg);
    Run_Tree->SetBranchAddress("l4_eleNumHit", &l4_eleNumHit);
    Run_Tree->SetBranchAddress("l4_CloseJetPt", &l4_CloseJetPt);
    Run_Tree->SetBranchAddress("l4_CloseJetEta", &l4_CloseJetEta);
    Run_Tree->SetBranchAddress("l4_CloseJetPhi", &l4_CloseJetPhi);
    Run_Tree->SetBranchAddress("l4_tauIsoVL", &l4_tauIsoVL);
    Run_Tree->SetBranchAddress("l4_tauIso3HitL", &l4_tauIso3HitL);
    Run_Tree->SetBranchAddress("l4_tauIso3HitM", &l4_tauIso3HitM);
    Run_Tree->SetBranchAddress("l4_tauIso3HitT", &l4_tauIso3HitT);
    Run_Tree->SetBranchAddress("l4_tauIsoL", &l4_tauIsoL);
    Run_Tree->SetBranchAddress("l4_tauIsoM", &l4_tauIsoM);
    Run_Tree->SetBranchAddress("l4_tauIsoT", &l4_tauIsoT);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2L", &l4_tauIsoMVA2L);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2M", &l4_tauIsoMVA2M);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2T", &l4_tauIsoMVA2T);
    Run_Tree->SetBranchAddress("l4_tauIsoMVA2raw", &l4_tauIsoMVA2raw);
    Run_Tree->SetBranchAddress("l4_tauRejMuL", &l4_tauRejMuL);
    Run_Tree->SetBranchAddress("l4_tauRejMu2L", &l4_tauRejMu2L);
    Run_Tree->SetBranchAddress("l4_tauRejMuM", &l4_tauRejMuM);
    Run_Tree->SetBranchAddress("l4_tauRejMu2M", &l4_tauRejMu2M);
    Run_Tree->SetBranchAddress("l4_tauRejMuT", &l4_tauRejMuT);
    Run_Tree->SetBranchAddress("l4_tauRejMu2T", &l4_tauRejMu2T);
    Run_Tree->SetBranchAddress("l4_tauRejEleL", &l4_tauRejEleL);
    Run_Tree->SetBranchAddress("l4_tauRejEleM", &l4_tauRejEleM);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA", &l4_tauRejEleMVA);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3L", &l4_tauRejEleMVA3L);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3M", &l4_tauRejEleMVA3M);
    Run_Tree->SetBranchAddress("l4_tauRejEleMVA3T", &l4_tauRejEleMVA3T);
    Run_Tree->SetBranchAddress("l4_RefJetPt", &l4_RefJetPt);
    Run_Tree->SetBranchAddress("l4_RefJetEta", &l4_RefJetEta);
    Run_Tree->SetBranchAddress("l4_RefJetPhi", &l4_RefJetPhi);
    //SVMass from another Tree
    Run_Tree->SetBranchAddress("SVMass", &SVMass);
    Run_Tree->SetBranchAddress("SVMassUnc", &SVMassUnc);
    Run_Tree->SetBranchAddress("SVMassUp", &SVMassUp);
    Run_Tree->SetBranchAddress("SVMassUncUp", &SVMassUncUp);
    Run_Tree->SetBranchAddress("SVMassDown", &SVMassDown);
    Run_Tree->SetBranchAddress("SVMassUncDown", &SVMassUncDown);


    //New BG_Tree
    TTree * BG_Tree = new TTree("BG_Tree", "BG_Tree");
    //    To force a memory-resident Tree
    BG_Tree->SetDirectory(0);

    BG_Tree->Branch("Channel_", &Channel_, "Channel_/I");
    BG_Tree->Branch("subChannel_", &subChannel_, "subChannel_/I");

    BG_Tree->Branch("HMass_", &HMass_, "HMass_/F");
    BG_Tree->Branch("SVMass_", &SVMass_, "SVMass_/F");

    BG_Tree->Branch("l3Pt_", &l3Pt_, "l3Pt_/F");
    BG_Tree->Branch("l3Eta_", &l3Eta_, "l3Eta_/F");
    BG_Tree->Branch("l3_CloseJetPt_", &l3_CloseJetPt_, "l3_CloseJetPt_/F");
    BG_Tree->Branch("l3_CloseJetEta_", &l3_CloseJetEta_, "l3_CloseJetEta_/F");
    BG_Tree->Branch("l4Pt_", &l4Pt_, "l4Pt_/F");
    BG_Tree->Branch("l4Eta_", &l4Eta_, "l4Eta_/F");
    BG_Tree->Branch("l4_CloseJetPt_", &l4_CloseJetPt_, "l4_CloseJetPt_/F");
    BG_Tree->Branch("l4_CloseJetEta_", &l4_CloseJetEta_, "l4_CloseJetEta_/F");




    //###############################################################################################
    //Just each categori should be filled once
    int Event_Double[8][9];
    memset(Event_Double, 0, sizeof (Event_Double[0][0]) * 8 * 9);
    int Ev_double_tau = 0; //need to be checked gloat instead of integer!!!!!!!!
    int Ev_double_ele = 0;
    int Ev_double_mu = 0;
    int Ev_double_Ltau = 0;
    //###############################################################################################

    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        //###############################################################################################
        // Default values
        //###############################################################################################
        bool charge_Type = ((l3Charge * l4Charge > 0) ? true : false); //This for OS
        bool SS = l3Charge * l4Charge > 0;
        bool OS = l3Charge * l4Charge < 0;
        float VisibleMass = HMass;
        float scaleUp = 1.03;
        float scaleDown = 0.97;
        float CutOnTauPt = 15;
        int pt_Bin = 400;
        int iso_Bin = 100;
        //###############################################################################################
        float LT = l3Pt + l4Pt;
        float Isolation_tau1 = l3_tauIsoMVA2raw;
        float Isolation_tau2 = l4_tauIsoMVA2raw;
        float Isolation_ele1 = l3_eleIso;
        float Isolation_ele2 = l4_eleIso;
        float Isolation_mu1 = l3_muIso;
        float Isolation_mu2 = l4_muIso;

        //###############################################################################################
        //###########################        Optimum    #################################################
        //###############################################################################################
        bool tau3_IsoB = l3_tauIsoMVA2raw > 0.6;
        bool tau4_IsoB = l4_tauIsoMVA2raw > 0.6;
        bool tau4_Iso_ltau = l4_tauIsoMVA2raw > 0.6;
        float optimum_Lt_TT = 0;
        float optimum_Lt_MT = 0;
        float optimum_Lt_ET = 0;
        float optimum_Lt_EM = 0;
        float optimum_MT_Isolation = 1;
        float optimum_ET_Isolation = 1;
        float optimum_EM_Isolation = 1;
        //#################################        Loose Cut for Shape      #############################
        float value_looserTauIso = 0.6;
        float value_looserLepIso = 1.0;
        //###############################################################################################
        //###############################################################################################

        if (givenTauIso.compare("3HitL") == 0) {
            tau3_IsoB = l3_tauIso3HitL;
            tau4_IsoB = l4_tauIso3HitL;
        }
        if (givenTauIso.compare("3HitM") == 0) {
            tau3_IsoB = l3_tauIso3HitM;
            tau4_IsoB = l4_tauIso3HitM;
        }
        if (givenTauIso.compare("3HitT") == 0) {
            tau3_IsoB = l3_tauIso3HitT;
            tau4_IsoB = l4_tauIso3HitT;
        }
        if (givenTauIso.compare("MVAL") == 0) {
            tau3_IsoB = l3_tauIsoMVA2L;
            tau4_IsoB = l4_tauIsoMVA2L;
        }
        if (givenTauIso.compare("MVAM") == 0) {
            tau3_IsoB = l3_tauIsoMVA2M;
            tau4_IsoB = l4_tauIsoMVA2M;
        }
        if (givenTauIso.compare("MVAT") == 0) {
            tau3_IsoB = l3_tauIsoMVA2T;
            tau4_IsoB = l4_tauIsoMVA2T;
        }
        //####################################################        LT cuts
        bool LTcut_tt = ((chanelType.compare("TT") == 0) ? l3Pt + l4Pt > float_LTCut : (l3Pt + l4Pt > optimum_Lt_TT));
        bool LTcut_mt = ((chanelType.compare("MT") == 0) ? l3Pt + l4Pt > float_LTCut : (l3Pt + l4Pt > optimum_Lt_MT));
        bool LTcut_et = ((chanelType.compare("ET") == 0) ? l3Pt + l4Pt > float_LTCut : (l3Pt + l4Pt > optimum_Lt_ET));
        bool LTcut_em = ((chanelType.compare("EM") == 0) ? l3Pt + l4Pt > float_LTCut : (l3Pt + l4Pt > optimum_Lt_EM));
        //####################################################        Lepton Isolation cuts
        float TightMu = ((chanelType.compare("MT") == 0) ? float_LepIso : optimum_MT_Isolation);
        float TightEle = ((chanelType.compare("ET") == 0) ? float_LepIso : optimum_ET_Isolation);
        float looseLep = ((chanelType.compare("EM") == 0) ? float_LepIso : optimum_EM_Isolation);

        //####################################################
        // MMTT FakeRateation
        //####################################################

        if ((Channel == 91) && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL) {

            //4 Categories
            if (LTcut_tt && charge_Type && !tau3_IsoB && !tau4_IsoB && (Event != Event_Double[1][1])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][1] = Event;
            }
            if (LTcut_tt && charge_Type && tau3_IsoB && !tau4_IsoB && (Event != Event_Double[2][1])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][1] = Event;
            }
            if (LTcut_tt && charge_Type && !tau3_IsoB && tau4_IsoB && (Event != Event_Double[3][1])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][1] = Event;
            }
            if (LTcut_tt && charge_Type && tau3_IsoB && tau4_IsoB && (Event != Event_Double[0][1])) {
                plotFill("VisibleMass_tt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmtt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_tt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmtt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_mmtt_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_mmtt_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_mmtt_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_mmtt_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_mmtt_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_mmtt_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_mmtt_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][1] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_tt && SS && l3_tauIsoMVA2raw > value_looserTauIso && l4_tauIsoMVA2raw > value_looserTauIso) {
                plotFill("VisibleMass_Shape_mmtt", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_mmtt", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_mmtt", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_mmtt", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_mmtt", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_mmtt", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_mmtt", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_mmtt", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_mmtt", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
            }
        }

        //####################################################
        //  Fake Rate Application (MMET)
        //####################################################

        if (Channel == 92 && l4Pt > CutOnTauPt && mu_Size == 2 && l4_tauRejEleMVA3T && l4_tauRejMu2L) {



            if (LTcut_et && charge_Type && !tau4_IsoB && (!l3_eleId_Tight || !(l3_eleIso < TightEle)) && (Event != Event_Double[1][2])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][2] = Event;
            }
            if (LTcut_et && charge_Type && !tau4_IsoB && (l3_eleId_Tight && l3_eleIso < TightEle) && (Event != Event_Double[2][2])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][2] = Event;
            }
            if (LTcut_et && charge_Type && tau4_IsoB && (!l3_eleId_Tight || !(l3_eleIso < TightEle)) && (Event != Event_Double[3][2])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][2] = Event;
            }
            if (LTcut_et && charge_Type && tau4_IsoB && (l3_eleId_Tight && (l3_eleIso < TightEle)) && (Event != Event_Double[0][2])) {
//            if (LTcut_et && charge_Type && tau4_IsoB && (l3_eleId_Tight && (l3_eleIso < TightEle)) && (Event != Event_Double[0][2]) && electron_Size == 1) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmet_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_lt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmet_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_mmet_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_mmet_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_mmet_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_mmet_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_mmet_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_mmet_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_mmet_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][2] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_et && SS && l4_tauIsoMVA2raw > value_looserTauIso && ((l3_eleIso < value_looserLepIso)) && (Event != Event_Double[4][2])) {
                plotFill("VisibleMass_Shape_mmet", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_mmet", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_mmet", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_mmet", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_mmet", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_mmet", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_mmet", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_mmet", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_mmet", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                Event_Double[4][2] = Event;
            }

        }
        //####################################################
        //  Fake Rate Application (MMMT)
        //####################################################

        if (Channel == 93 && l4Pt > CutOnTauPt && electron_Size == 0 && l4_tauRejEleL && l4_tauRejMu2T) {

            if (LTcut_mt && charge_Type && !tau4_IsoB && (!l3_muId_Tight || !(l3_muIso < TightMu)) && (Event != Event_Double[1][3])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][3] = Event;
            }
            if (LTcut_mt && charge_Type && !tau4_IsoB && (l3_muId_Tight && l3_muIso < TightMu) && (Event != Event_Double[2][3])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][3] = Event;
            }
            if (LTcut_mt && charge_Type && tau4_IsoB && (!l3_muId_Tight || !(l3_muIso < TightMu)) && (Event != Event_Double[3][3])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][3] = Event;
            }
            if (LTcut_mt && charge_Type && tau4_IsoB && (l3_muId_Tight && (l3_muIso < TightMu)) && (Event != Event_Double[0][3])) {
//            if (LTcut_mt && charge_Type && tau4_IsoB && (l3_muId_Tight && (l3_muIso < TightMu)) && (Event != Event_Double[0][3]) && mu_Size == 3) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmmt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_lt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmmt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_mmmt_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_mmmt_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_mmmt_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_mmmt_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_mmmt_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_mmmt_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_mmmt_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][3] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_mt && SS && l4_tauIsoMVA2raw > value_looserTauIso && ((l3_muIso < value_looserLepIso)) && (Event != Event_Double[4][3])) {
                plotFill("VisibleMass_Shape_mmmt", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_mmmt", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_mmmt", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_mmmt", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_mmmt", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_mmmt", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_mmmt", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_mmmt", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_mmmt", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                Event_Double[4][3] = Event;
            }

        }

        //####################################################
        //  Fake Rate Application (mmme)
        //####################################################
        if (Channel == 94) {

            if (LTcut_em && charge_Type && (!l4_eleId_Loose || !(l4_eleIso < looseLep)) && (!l3_muId_Loose || !(l3_muIso < looseLep)) && (Event != Event_Double[1][4])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][4] = Event;
            }
            if (LTcut_em && charge_Type && (!l4_eleId_Loose || !(l4_eleIso < looseLep)) && (l3_muId_Loose && l3_muIso < looseLep) && (Event != Event_Double[2][4])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][4] = Event;
            }
            if (LTcut_em && charge_Type && (l4_eleId_Loose && (l4_eleIso < looseLep)) && (!l3_muId_Loose || !(l3_muIso < looseLep)) && (Event != Event_Double[3][4])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][4] = Event;
            }
            if (LTcut_em && charge_Type && (l4_eleId_Loose && l4_eleIso < looseLep) && (l3_muId_Loose && l3_muIso < looseLep) && (Event != Event_Double[0][4]) ) {
//            if (LTcut_em && charge_Type && (l4_eleId_Loose && l4_eleIso < looseLep) && (l3_muId_Loose && l3_muIso < looseLep) && (Event != Event_Double[0][4]) && mu_Size == 3 && electron_Size == 1) {
                plotFill("VisibleMass_ll_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmme_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_ll_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmme_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_mmme_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_mmme_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_mmme_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_mmme_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_mmme_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_mmme_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_mmme_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmme_pp_Up", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmme_pp_Up", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_mmme_pp_Down", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_mmme_pp_Down", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][4] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_em && SS && ((l4_eleIso < value_looserLepIso)) && ((l3_muIso < value_looserLepIso)) && (Event != Event_Double[4][4])) {
                plotFill("VisibleMass_Shape_mmme", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_mmme", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_mmme", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_mmme", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_mmme", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_mmme", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_mmme", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_mmme", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_mmme", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                Event_Double[4][4] = Event;
            }
        }
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        // EETT FakeRateation
        //####################################################
        //####################################################
        //####################################################
        //####################################################

        if ((Channel == 95) && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL) {


            //4 Categories
            if (LTcut_tt && charge_Type && !tau3_IsoB && !tau4_IsoB && (Event != Event_Double[1][5])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][5] = Event;
            }
            if (LTcut_tt && charge_Type && tau3_IsoB && !tau4_IsoB && (Event != Event_Double[2][5])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][5] = Event;
            }
            if (LTcut_tt && charge_Type && !tau3_IsoB && tau4_IsoB && (Event != Event_Double[3][5])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][5] = Event;
            }
            if (LTcut_tt && charge_Type && tau3_IsoB && tau4_IsoB && (Event != Event_Double[0][5])) {
                plotFill("VisibleMass_tt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_eett_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_tt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eett_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_eett_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_eett_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_eett_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_eett_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_eett_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_eett_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_eett_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][5] = Event;
            }
            //Shape of Reducible BG

            if (LTcut_tt && SS && l3_tauIsoMVA2raw > value_looserTauIso && l4_tauIsoMVA2raw > value_looserTauIso) {
                plotFill("VisibleMass_Shape_eett", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_eett", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_eett", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_eett", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_eett", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_eett", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_eett", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_eett", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_eett", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
            }
        }
        //####################################################
        //  Fake Rate Application (EEMT)
        //####################################################

        if (Channel == 96 && l4Pt > CutOnTauPt && electron_Size == 2 && l4_tauRejEleL && l4_tauRejMu2T) {

            if (LTcut_mt && charge_Type && !tau4_IsoB && (!l3_muId_Tight || !(l3_muIso < TightMu)) && (Event != Event_Double[1][6])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][6] = Event;
            }
            if (LTcut_mt && charge_Type && !tau4_IsoB && (l3_muId_Tight && l3_muIso < TightMu) && (Event != Event_Double[2][6])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][6] = Event;
            }
            if (LTcut_mt && charge_Type && tau4_IsoB && (!l3_muId_Tight || !(l3_muIso < TightMu)) && (Event != Event_Double[3][6])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][6] = Event;
            }
//            if (LTcut_mt && charge_Type && tau4_IsoB && (l3_muId_Tight && (l3_muIso < TightMu)) && (Event != Event_Double[0][6]) && mu_Size == 1) {
            if (LTcut_mt && charge_Type && tau4_IsoB && (l3_muId_Tight && (l3_muIso < TightMu)) && (Event != Event_Double[0][6])) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_eemt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_lt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eemt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_eemt_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_eemt_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_eemt_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_eemt_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_eemt_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_eemt_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_eemt_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][6] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_mt && SS && l4_tauIsoMVA2raw > value_looserTauIso && ((l3_muIso < value_looserLepIso)) && (Event != Event_Double[4][6])) {
                plotFill("VisibleMass_Shape_eemt", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_eemt", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_eemt", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_eemt", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_eemt", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_eemt", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_eemt", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_eemt", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_eemt", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                Event_Double[4][6] = Event;
            }
        }

        //####################################################
        //  Fake Rate Application (EEET)
        //####################################################

        if (Channel == 97 && l4Pt > CutOnTauPt && mu_Size == 0 && l4_tauRejEleMVA3T && l4_tauRejMu2L) {

            if (LTcut_et && charge_Type && !tau4_IsoB && (!l3_eleId_Tight || !(l3_eleIso < TightEle)) && (Event != Event_Double[1][7])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][7] = Event;
            }
            if (LTcut_et && charge_Type && !tau4_IsoB && (l3_eleId_Tight && l3_eleIso < TightEle) && (Event != Event_Double[2][7])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][7] = Event;
            }
            if (LTcut_et && charge_Type && tau4_IsoB && (!l3_eleId_Tight || !(l3_eleIso < TightEle)) && (Event != Event_Double[3][7])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][7] = Event;
            }
            if (LTcut_et && charge_Type && tau4_IsoB && (l3_eleId_Tight && (l3_eleIso < TightEle)) && (Event != Event_Double[0][7])) {
//            if (LTcut_et && charge_Type && tau4_IsoB && (l3_eleId_Tight && (l3_eleIso < TightEle)) && (Event != Event_Double[0][7]) && electron_Size == 3) {
                plotFill("VisibleMass_lt_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_eeet_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_lt_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eeet_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_eeet_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_eeet_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_eeet_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_eeet_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_eeet_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_eeet_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_eeet_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][7] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_et && SS && l4_tauIsoMVA2raw > value_looserTauIso && ((l3_eleIso < value_looserLepIso)) && (Event != Event_Double[4][7])) {
                plotFill("VisibleMass_Shape_eeet", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_eeet", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_eeet", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_eeet", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_eeet", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_eeet", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_eeet", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_eeet", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_eeet", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                                Event_Double[4][7] = Event;
            }
        }
        //####################################################
        //  Fake Rate Application (eeem)
        //####################################################
        if (Channel == 98) {


            if (LTcut_em && charge_Type && (!l3_eleId_Loose || !(l3_eleIso < looseLep)) && (!l4_muId_Loose || !(l4_muIso < looseLep)) && (Event != Event_Double[1][8])) {
                fillTreeN(BG_Tree, Channel, 0, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[1][8] = Event;
            }
            if (LTcut_em && charge_Type && (l3_eleId_Loose && (l3_eleIso < looseLep)) && (!l4_muId_Loose || !(l4_muIso < looseLep)) && (Event != Event_Double[2][8])) {
                fillTreeN(BG_Tree, Channel, 1, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[2][8] = Event;
            }
            if (LTcut_em && charge_Type && (!l3_eleId_Loose || !(l3_eleIso < looseLep)) && (l4_muId_Loose && l4_muIso < looseLep) && (Event != Event_Double[3][8])) {
                fillTreeN(BG_Tree, Channel, 2, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[3][8] = Event;
            }
            if (LTcut_em && charge_Type && (l3_eleId_Loose && l3_eleIso < looseLep) && (l4_muId_Loose && l4_muIso < looseLep) && (Event != Event_Double[0][8]) ) {
//            if (LTcut_em && charge_Type && (l3_eleId_Loose && l3_eleIso < looseLep) && (l4_muId_Loose && l4_muIso < looseLep) && (Event != Event_Double[0][8]) && electron_Size == 3 && mu_Size == 1) {
                plotFill("VisibleMass_ll_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_eeem_pp", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_ll_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eeem_pp", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_eeem_pp", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_eeem_pp", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_eeem_pp", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_eeem_pp", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_eeem_pp", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_eeem_pp", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_eeem_pp", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //Just for consistency
                plotFill("VisibleMass_eeem_pp_Up", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eeem_pp_Up", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("VisibleMass_eeem_pp_Down", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_eeem_pp_Down", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                fillTreeN(BG_Tree, Channel, 3, VisibleMass, SVMass, l3Pt, l3Eta, l3_CloseJetPt, l3_CloseJetEta, l4Pt, l4Eta, l4_CloseJetPt, l4_CloseJetEta);
                Event_Double[0][8] = Event;
            }
            //Shape of Reducible BG
            if (LTcut_em && SS && ((l4_muIso < value_looserLepIso)) && ((l3_eleIso < value_looserLepIso)) && (Event != Event_Double[4][8])) {
                plotFill("VisibleMass_Shape_eeem", VisibleMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("SVMass_Shape_eeem", SVMass, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("LT_Shape_eeem", LT, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
                plotFill("Isolation_tau1_Shape_eeem", Isolation_tau1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_tau2_Shape_eeem", Isolation_tau2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele1_Shape_eeem", Isolation_ele1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_ele2_Shape_eeem", Isolation_ele2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu1_Shape_eeem", Isolation_mu1, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                plotFill("Isolation_mu2_Shape_eeem", Isolation_mu2, iso_Bin, 0, 1, pu_Weight * eff_Correction);
                //                Event_Double[4][8] = Event;
            }
        }
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        //####################################################
        // Tau Fake Rate Measurement
        //####################################################
        bool FR_Estimation = true;

        //        if ((Channel == 91 || Channel == 95) && SS && LTcut_tt && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL && Event != Ev_double_tau) {
        if ((Channel == 91 || Channel == 95) && SS && l3Pt > CutOnTauPt && l4Pt > CutOnTauPt && l3_tauRejMu2L && l3_tauRejEleL && l4_tauRejMu2L && l4_tauRejEleL && Event != Ev_double_tau) {

            Ev_double_tau = Event;


            plotFill("deta_CloseJet_RefJet", l3_RefJetEta - l3_CloseJetEta, 400, -.2, .2);
            plotFill("deta_CloseJet_RefJet", l4_RefJetEta - l4_CloseJetEta, 400, -.2, .2);
            plotFill("dphi_CloseJet_RefJet", l3_RefJetPhi - l3_CloseJetPhi, 400, -.2, .2);
            plotFill("dphi_CloseJet_RefJet", l4_RefJetPhi - l4_CloseJetPhi, 400, -.2, .2);
            plotFill("dR_CloseJet_RefJet", dR(l3_RefJetEta, l3_RefJetPhi, l3_CloseJetEta, l3_CloseJetPhi), 400, -.2, .2);
            plotFill("dR_CloseJet_RefJet", dR(l4_RefJetEta, l4_RefJetPhi, l4_CloseJetEta, l4_CloseJetPhi), 400, -.2, .2);


            //#########################
            // Tau Fake Rate in Just 1 eta bin
            //#########################
            //Total FR in terms of CutOnTauPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            //Total FR in terms of RefJetPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_RefJet", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_RefJet", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            //Total FR in terms of JetPt
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoM) plotFill("FakeRate_TT_Tau_Pt_After_Medium_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoT) plotFill("FakeRate_TT_Tau_Pt_After_Tight_Jet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);


            //#########################
            // Tau Fake Rate in 2 eta bin
            //#########################
            //Barrel Fake rate
            if (FR_Estimation && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_B", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_B", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //EndCap Fake rate
            if (FR_Estimation && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_E", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_E", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            //Barrel Fake rate
            if (FR_Estimation && l3_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_B", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_B", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_B", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4_RefJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_B", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //EndCap Fake rate
            if (FR_Estimation && l3_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_E", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_RefJet_E", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_E", l3_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4_RefJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_RefJet_E", l4_RefJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            //Barrel Fake rate
            if (FR_Estimation && l3_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_B", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4_CloseJetEta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //EndCap Fake rate
            if (FR_Estimation && l3_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && l4_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_Before_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau3_IsoB && l3_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_E", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (FR_Estimation && tau4_IsoB && l4_CloseJetEta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Loose_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);


            //            if (FR_Estimation && l3_tauIsoM && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoM && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_B", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoT && l3Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoT && l4Eta < 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_B", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoM && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoM && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Medium_E", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l3_tauIsoT && l3Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            //            if (FR_Estimation && l4_tauIsoT && l4Eta > 1.4) plotFill("FakeRate_TT_Tau_Pt_After_Tight_E", l4Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

        }

        //#########################
        // Tau Fake Rate VS eta
        //#########################
        //fake Rate v.s eta

        //Tau Fake Rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before", l3Eta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before", l4Eta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose", l3Eta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose", l4Eta, 250, -2.5, 2.5);

        //RefJet Fake rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_RefJet", l3_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_RefJet", l4_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_RefJet", l3_RefJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_RefJet", l4_RefJetEta, 250, -2.5, 2.5);

        //CloseJet Fake rate
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_CloseJet", l3_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation) plotFill("FakeRate_TT_Tau_Eta_Before_CloseJet", l4_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau3_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_CloseJet", l3_CloseJetEta, 250, -2.5, 2.5);
        if (FR_Estimation && tau4_IsoB) plotFill("FakeRate_TT_Tau_Eta_After_Loose_CloseJet", l4_CloseJetEta, 250, -2.5, 2.5);
        //####################################################
        //  tauFR in Ltau Final State
        //####################################################
        bool lepTauFR_denum = SS && l4Pt > CutOnTauPt && (((Channel == 92 || Channel == 97) && (l4_tauRejEleMVA3T && l4_tauRejMu2L)) || ((Channel == 93 || Channel == 96) && l4_tauRejEleL && l4_tauRejMu2T));
        if (lepTauFR_denum && Event != Ev_double_Ltau) {

            Ev_double_Ltau = Event;
            if (lepTauFR_denum) plotFill("FakeRate_LT_Tau_Pt_Before_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (lepTauFR_denum && tau4_Iso_ltau) plotFill("FakeRate_LT_Tau_Pt_After_Loose_CloseJet", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            if (lepTauFR_denum && l4_CloseJetEta < 1.4) plotFill("FakeRate_LT_Tau_Pt_Before_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (lepTauFR_denum && tau4_Iso_ltau && l4_CloseJetEta < 1.4) plotFill("FakeRate_LT_Tau_Pt_After_Loose_CloseJet_B", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

            if (lepTauFR_denum && l4_CloseJetEta > 1.4) plotFill("FakeRate_LT_Tau_Pt_Before_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (lepTauFR_denum && tau4_Iso_ltau && l4_CloseJetEta > 1.4) plotFill("FakeRate_LT_Tau_Pt_After_Loose_CloseJet_E", l4_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);

        }
        //####################################################
        //####################################################
        //####################################################
        // Ele Mu  Fake Rate Measurements
        //####################################################
        //5 GeV Tau
        bool eleFR_denum_0 = ((Channel == 92 && electron_Size < 2) || (Channel == 97 && electron_Size < 4)) && SS && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5 && l4_tauRejEleMVA3T && l4_tauRejMu2L;
        if (eleFR_denum_0 && Event != Ev_double_ele) {
            Ev_double_ele = Event;
            if (eleFR_denum_0) plotFill("4objFR_Ele_Denum_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (eleFR_denum_0) plotFill("4objFR_Ele_Denum_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (eleFR_denum_0 && l3_eleId_Loose && l3_eleIso < looseLep) plotFill("4objFR_Ele_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (eleFR_denum_0 && l3_eleId_Tight && l3_eleIso < TightEle) plotFill("4objFR_Ele_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (eleFR_denum_0 && l3_eleId_Loose && l3_eleIso < looseLep) plotFill("4objFR_Ele_NumLoose_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (eleFR_denum_0 && l3_eleId_Tight && l3_eleIso < TightEle) plotFill("4objFR_Ele_NumTight_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        }
        bool muFR_denum_0 = ((Channel == 93 && mu_Size < 4) || (Channel == 96 && mu_Size < 2)) && SS && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5 && l4_tauRejEleL && l4_tauRejMu2T;
        if (muFR_denum_0 && Event != Ev_double_mu) {
            Ev_double_mu = Event;
            if (muFR_denum_0) plotFill("4objFR_Mu_Denum_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (muFR_denum_0) plotFill("4objFR_Mu_Denum_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (muFR_denum_0 && l3_muId_Loose && l3_muIso < looseLep) plotFill("4objFR_Mu_NumLoose_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (muFR_denum_0 && l3_muId_Tight && l3_muIso < TightMu) plotFill("4objFR_Mu_NumTight_0", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (muFR_denum_0 && l3_muId_Loose && l3_muIso < looseLep) plotFill("4objFR_Mu_NumLoose_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
            if (muFR_denum_0 && l3_muId_Tight && l3_muIso < TightMu) plotFill("4objFR_Mu_NumTight_0_Jet", l3_CloseJetPt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        }
        //
        //
        //        //##################################################
        //        //5 GeV Tau
        //        bool eleFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        //        if (eleFR_denum_5) plotFill("4objFR_Ele_Denum_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (eleFR_denum_5 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //
        //        bool muFR_denum_5 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 5;
        //        if (muFR_denum_5) plotFill("4objFR_Mu_Denum_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (muFR_denum_5 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (muFR_denum_5 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_5", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //
        //        //##################################################
        //        //10 GeV Tau
        //        bool eleFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        //        if (eleFR_denum_10) plotFill("4objFR_Ele_Denum_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (eleFR_denum_10 && l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //
        //        bool muFR_denum_10 = TMath::Abs(ZMass - 91.2) < dMZ_Diff && ((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 10;
        //        if (muFR_denum_10) plotFill("4objFR_Mu_Denum_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (muFR_denum_10 && l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        if (muFR_denum_10 && l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_10", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //


        //        if (((Channel == 92 && BareElectron_Size < 2) || (Channel == 97 && BareElectron_Size < 4)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 20) {
        //            plotFill("4objFR_Ele_Denum_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //            if (l3_eleId && l3_eleIso < 0.30) plotFill("4objFR_Ele_NumLoose_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //            if (l3_eleId && l3_eleIso < 0.10) plotFill("4objFR_Ele_NumTight_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //
        //        if (((Channel == 93 && BareMuon_Size < 4) || (Channel == 96 && BareMuon_Size < 2)) && (l3Charge * l4Charge > 0) && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && l4Pt > 20) {
        //            plotFill("4objFR_Mu_Denum_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //            if (l3_muId && l3_muIso < 0.30) plotFill("4objFR_Mu_NumLoose_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //            if (l3_muId && l3_muIso < 0.15) plotFill("4objFR_Mu_NumTight_justTmass", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }



        //################
        // 3-onj fake rate
        //################
        //        bool Mu_denum = (Channel == 101 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi));
        //        //        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi));
        //        bool Mu_denum = (Channel == 101 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);
        //        bool Ele_denum = (Channel == 105 && WZ_Rej_B(l3Pt, l3Px, l3Py, met, metPhi) && TMath::Abs(ZMass - 91.2) < dMZ_Diff);
        //
        //        if (Mu_denum) {
        //            plotFill("3objFR_Mu_Denum", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Mu_denum && l3_muId && l3_muIso < tightMu) {
        //            plotFill("3objFR_Mu_NumTight", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Mu_denum && l3_muId && l3_muIso < looseMu) {
        //            plotFill("3objFR_Mu_NumLoose", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Ele_denum) {
        //            plotFill("3objFR_Ele_Denum", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Ele_denum && l3_eleId && l3_eleIso < tightEle) {
        //            plotFill("3objFR_Ele_NumTight", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Ele_denum && l3_eleId && l3_eleIso < looseEle) {
        //            plotFill("3objFR_Ele_NumLoose", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //
        //        //####################################################
        //        if (Mu_denum && l3_muId) {
        //            plotFill("3objFR_Mu_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Mu_denum && l3_muIso < looseMu) {
        //            plotFill("3objFR_Mu_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Ele_denum && l3_eleId) {
        //            plotFill("3objFR_Ele_Denum_Id", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //        if (Ele_denum && l3_eleIso < looseEle) {
        //            plotFill("3objFR_Ele_Denum_Iso", l3Pt, pt_Bin, 0, pt_Bin, pu_Weight * eff_Correction);
        //        }
        //
        //
        //





    }


    fout->cd();
    BG_Tree->Write();

    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();

    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();

    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();

    fout->Close();

}

