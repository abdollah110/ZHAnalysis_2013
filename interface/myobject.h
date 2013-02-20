#ifndef __MYOBJECT_HH__
#define __MYOBJECT_HH__
#include "TROOT.h"
#include "TObject.h"
using namespace std;
#include <vector>

class myobject : public TObject {
public:

    myobject() {
        ;
    }

    ~myobject() {
        ;
    }

    //General



    float pt, eta, px, py, phi, charge, E, et, pz, z, mass, dz_Ver_match, Energy, mt, jetMass, eta_SC;
    float mod_pt, mod_eta, mod_phi, mod_charge, mod_z;
    float Gmod_pt, Gmod_eta, Gmod_phi, Gmod_charge, Gmod_z;
    float pfIsoAll, pfIsoCharged, pfIsoNeutral, pfIsoGamma, pfIsoPU, pfIsoPULow, Id_mvaTrg, Id_mvaNonTrg;
    float pfIsoAll_NoPFId, pfIsoCharged_NoPFId, pfIsoNeutral_NoPFId, pfIsoGamma_NoPFId, pfIsoPU_NoPFId;
    float z_expo;
    double position_Rho, position_rho;

    int pdgId, status, mod_pdgId, mod_status, Gmod_pdgId, Gmod_status, tracksSize;
    //Muon
    float dB, d0, emfraction;
    float DepositR03Ecal;
    float DepositR03Hcal;
    float DepositR03TrackerOfficial;
    float alpha;
    bool GlobalMuonPromptTight;
    bool TMOneStationLoose;
    bool TM2DCompatibilityLoose;
    bool isGlobalMuon, isTrackerMuon, isStandAloneMuon, isPFMuon;
    int numberOfValidMuonHits, numberOfHits, numMatchStation;
    int numLostHitEle, numValidHitEle, numHitEleInner, numLostHitEleInner;
    int normalizedChi2_innTrk, numberOfValidMuonHits_innTrk, numberOfHits_innTrk;
    float normalizedChi2;
    int trkLayerMeasure, intrkLayerMeasure, intrkLayerpixel;
    double dxy_in, dZ_in;


    //Vertex Mettopology Trigger
    bool isFake, isValid;
    float ndof;
    unsigned int Num_Vertex;
    bool jetId_loose, jetId_tight;


    //Electron
    float HoverE, deltaPhiSuperClusterTrackAtVtx, deltaEtaSuperClusterTrackAtVtx, sigmaIetaIeta, sigmaEtaEta;
    float ecalIso, hcalIso, caloIso, trackIso, hcalOverEcal, SIP;

    //For jet and taus
    float bDiscriminatiors_CSV, bDiscriminatiors_JP, bDiscriminatiors_TCHPT;
    float jetPt, jetEta, jetPhi;
    float leadChargedParticlePt, leadTrackD0;
    bool puJetIdLoose, puJetIdMedium, puJetIdTight;
    //    float leadChargedParticlePt, leadNeutralParticlePt, leadParticlePt, leadTrackD0;
    float mva_e_pi, mva_pi_mu, mva_e_mu, hcalEnergy, ecalEnergy, trackRefPt;
    int numChargedParticlesSignalCone, numNeutralHadronsSignalCone, numPhotonsSignalCone, numParticlesSignalCone;
    int numChargedParticlesIsoCone, numNeutralHadronsIsoCone, numPhotonsIsoCone, numParticlesIsoCone;
    float ptSumChargedParticlesIsoCone, ptSumPhotonsIsoCone;
    float discriminationByDecayModeFinding;
    float discriminationByVeryLooseIsolation;
    float discriminationByLooseIsolation;
    float discriminationByMediumIsolation;
    float discriminationByTightIsolation;
    float discriminationByElectronLoose;
    float discriminationByElectronMedium;
    float discriminationByElectronTight;
    float discriminationByElectronMVA;
    float discriminationByMuonLoose;
    float discriminationByMuonMedium;
    float discriminationByMuonTight;
    float byVLooseCombinedIsolationDeltaBetaCorr;
    float byLooseCombinedIsolationDeltaBetaCorr;
    float byMediumCombinedIsolationDeltaBetaCorr;
    float byTightCombinedIsolationDeltaBetaCorr;


    float byIsolationMVAraw;
    float byLooseIsolationMVA;
    float byMediumIsolationMVA;
    float byTightIsolationMVA;
    float againstElectronTightMVA2;

    float CicVeryLoose;
    float CicLoose;
    float CicMedium;
    float CicTight;
    float CicSuperTight;

    //    trigger matching
    bool hasTrgObject_loose;
    float TrgObjectEta_loose;
    float TrgObjectPt_loose;
    float TrgObjectPhi_loose;

    bool hasTrgObject_medium;
    float TrgObjectEta_medium;
    float TrgObjectPt_medium;
    float TrgObjectPhi_medium;


    ClassDef(myobject, 1)
};
#endif
