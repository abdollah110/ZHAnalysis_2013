

#ifndef _ELECTRINID_H
#define	_ELECTRINID_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "myevent.h"
#include "LinkDef.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include "myobject.h"



double EAMuon(double eta) {
    double EffectiveArea = 0.0;
    if (fabs(eta) >= 0.0 && fabs(eta) < 1.0) EffectiveArea = 0.132;
    if (fabs(eta) >= 1.0 && fabs(eta) < 1.5) EffectiveArea = 0.120;
    if (fabs(eta) >= 1.5 && fabs(eta) < 2.0) EffectiveArea = 0.114;
    if (fabs(eta) >= 2.0 && fabs(eta) < 2.2) EffectiveArea = 0.139;
    if (fabs(eta) >= 2.2 && fabs(eta) < 2.3) EffectiveArea = 0.168;
    if (fabs(eta) >= 2.3) EffectiveArea = 0.189;
    return EffectiveArea;
}

double EAElectron(double eta) {
    float EffectiveArea = 0.;
    if (fabs(eta) >= 0.0 && fabs(eta) < 1.0) EffectiveArea = 0.18;
    if (fabs(eta) >= 1.0 && fabs(eta) < 1.479) EffectiveArea = 0.20;
    if (fabs(eta) >= 1.479 && fabs(eta) < 2.0) EffectiveArea = 0.15;
    if (fabs(eta) >= 2.0 && fabs(eta) < 2.2) EffectiveArea = 0.19;
    if (fabs(eta) >= 2.2 && fabs(eta) < 2.3) EffectiveArea = 0.21;
    if (fabs(eta) >= 2.3 && fabs(eta) < 2.4) EffectiveArea = 0.22;
    if (fabs(eta) >= 2.4) EffectiveArea = 0.29;
    return EffectiveArea;
}


//Muon PF Isolation

double Iso_Mu_dBeta(myobject const& a) {


    double MuIsoTrk = a.pfIsoCharged;
    double MuIsoEcal = a.pfIsoGamma;
    double MuIsoHcal = a.pfIsoNeutral;
    double MuIsoPU = a.pfIsoPU;

    double relIso = (MuIsoTrk) / a.pt;
    if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
        relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (a.pt);

    return relIso;

}

//Electron PF Isolation

double Iso_Ele_dBeta(myobject const& a) {



    double EleIsoTrk = a.pfIsoCharged;
    double EleIsoEcal = a.pfIsoGamma;
    double EleIsoHcal = a.pfIsoNeutral;
    double EleIsoPU = a.pfIsoPU;

    double relIso = (EleIsoTrk) / a.pt;
    if (EleIsoEcal + EleIsoHcal - 0.5 * EleIsoPU > 0)
        relIso = (EleIsoTrk + EleIsoEcal + EleIsoHcal - 0.5 * EleIsoPU) / (a.pt);

    return relIso;
}

//Electron PF Isolation

double Iso_Ele_Rho(myevent *m, myobject const& a) {



    //    double EleIsoTrk = a.pfIsoCharged;
    double EleIsoTrk = a.pfIsoAll;
    double EleIsoEcal = a.pfIsoGamma;
    double EleIsoHcal = a.pfIsoNeutral;
    double corr = m->RhoCorr * EAElectron(a.eta_SC);

    double relIso = (EleIsoTrk) / a.pt;
    if (EleIsoEcal + EleIsoHcal - corr > 0)
        relIso = (EleIsoTrk + EleIsoEcal + EleIsoHcal - corr) / (a.pt);

    return relIso;
}

double Iso_Mu_Rho(myevent *m, myobject const& a) {


    //    double MuIsoTrk = a.pfIsoCharged;
    double MuIsoTrk = a.pfIsoAll;
    double MuIsoEcal = a.pfIsoGamma;
    double MuIsoHcal = a.pfIsoNeutral;
    double corr = m->RhoCorr * EAMuon(a.eta);

    double relIso = (MuIsoTrk) / a.pt;
    if (MuIsoEcal + MuIsoHcal - corr > 0)
        relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - corr) / (a.pt);

    return relIso;

}

bool Id_Mu(myobject const& a) {

    bool muPF = a.isPFMuon;
    bool muGlobal = a.isGlobalMuon;
    bool muTracker = a.isTrackerMuon;
    double MuChi2 = a.normalizedChi2;
    int MuValHit = a.numberOfValidMuonHits;
    int numMatchStat = a.numMatchStation;
    double dZ_in = a.dZ_in;
    int intrkLayerpixel_ = a.intrkLayerpixel;
    int trkLayerMeasure_ = a.trkLayerMeasure;

    if (muPF && (muGlobal && muTracker) && MuChi2 < 10 && MuValHit > 0 && numMatchStat > 1 && a.dB < 0.2 && dZ_in < 0.5 && intrkLayerpixel_ > 0 && trkLayerMeasure_ > 5)
        return true;
    else
        return false;

}

//https://twiki.cern.ch/twiki/bin/view/Main/HVVElectronId2012/
//bool EleMVANonTrigId(float pt, float eta, double value){

bool EleMVANonTrigId(myobject const& a) {
    bool passingId = false;
    double pt = a.pt;
    double eta = a.eta;
    double value = a.Id_mvaNonTrg;

    if (pt > 5. && pt < 10. && fabs(eta) < 0.8 && value > 0.47)
        passingId = true;
    if (pt > 5. && pt < 10. && fabs(eta) >= 0.8 && fabs(eta) < 1.479 && value > 0.004)
        passingId = true;
    if (pt > 5. && pt < 10. && fabs(eta) >= 1.479 && value > 0.295)
        passingId = true;

    if (pt > 10. && fabs(eta) < 0.8 && value > 0.5)
        passingId = true;
    if (pt > 10. && fabs(eta) >= 0.8 && fabs(eta) < 1.479 && value > 0.12)
        passingId = true;
    if (pt > 10. && fabs(eta) >= 1.479 && value > 0.6)
        passingId = true;
    //  if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
    bool numHit = a.numHitEleInner < 2;
    return numHit && passingId;
}


#endif
