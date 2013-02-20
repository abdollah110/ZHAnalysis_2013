/*
 * File:   LooseMuon.h
 * Author: abdollah
 *
 * Created on February 11, 2011, 4:13 PM
 */

#ifndef _GOODLEPTONS_H
#define	_GOODLEPTONS_H


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
#include "Leptons_IdIso.h"
#include "zh_Auxiliary.h"



using namespace std;

struct myobject_grt {

    bool operator ()(myobject const& a, myobject const& b) const {
        return (a.pt > b.pt);
    }
};

struct myobject_sort_Phi {

    bool operator ()(myobject const& a, myobject const& b) const {
        return (a.phi > b.phi);
    }
};




//******************************************************************************************
//**********************   MUON   **********************************************************
//******************************************************************************************

vector<myobject> GoodMuon(myevent *m) {

    vector<myobject> looseMuon;
    looseMuon.clear();
    vector<myobject> muon = m->PreSelectedMuons;
    for (int i = 0; i < muon.size(); i++) {
        double muPt = muon[i].pt;
        double muEta = muon[i].eta;
        if (muPt > 10 && fabs(muEta) < 2.4 && Id_Mu(muon[i]) && Iso_Mu_dBeta(muon[i]) < 0.40)
            looseMuon.push_back(muon[i]);
    }
    sort(looseMuon.begin(), looseMuon.end(), myobject_grt());
    return looseMuon;
}

vector<myobject> NoIdIsoMuon(myevent *m) {

    vector<myobject> bareMuon;
    bareMuon.clear();
    vector<myobject> muon = m->PreSelectedMuons;
    for (int i = 0; i < muon.size(); i++) {
        double muPt = muon[i].pt;
        double muEta = muon[i].eta;
        bool muGlobal =  muon[i].isGlobalMuon;
        bool muTracker = muon[i].isTrackerMuon;
        if (muPt > 10 && fabs(muEta) < 2.4 && (muGlobal || muTracker))
            bareMuon.push_back(muon[i]);
    }
    sort(bareMuon.begin(), bareMuon.end(), myobject_grt());
    return bareMuon;
}
//******************************************************************************************
//***********************   Electron   *****************************************************
//******************************************************************************************

vector<myobject> GoodElectron(myevent *m) {

    vector<myobject> goodElectron;
    goodElectron.clear();
    vector<myobject> electron = m->PreSelectedElectrons;
    for (int i = 0; i < electron.size(); i++) {
        double elePt = electron[i].pt;
        double eleEta = electron[i].eta;
        if (elePt > 10 && fabs(eleEta) < 2.5 && EleMVANonTrigId(electron[i]) && Iso_Ele_dBeta(electron[i]) < 0.40)
            goodElectron.push_back(electron[i]);
    }
    sort(goodElectron.begin(), goodElectron.end(), myobject_grt());
    return goodElectron;
}

vector<myobject> NoIdIsoElectron(myevent *m) {

    vector<myobject> bareElectron;
    bareElectron.clear();
    vector<myobject> electron = m->PreSelectedElectrons;
    for (int i = 0; i < electron.size(); i++) {
        double elePt = electron[i].pt;
        double eleEta = electron[i].eta;
        if (elePt > 10 && fabs(eleEta) < 2.5)
            bareElectron.push_back(electron[i]);
    }
    sort(bareElectron.begin(), bareElectron.end(), myobject_grt());
    return bareElectron;
}
//******************************************************************************************
//*********************   TAU   ************************************************************
//******************************************************************************************

vector<myobject> GoodTau(myevent *m) {

    vector<myobject> goodHPSTau;
    vector<myobject> tau = m->PreSelectedHPSTaus;
    for (int i = 0; i < tau.size(); i++) {

        double tauPt = tau[i].pt;
        double tauEta = tau[i].eta;

        if (tauPt > 20 && fabs(tauEta) < 2.3 &&
                tau[i].discriminationByDecayModeFinding && tau[i].byLooseCombinedIsolationDeltaBetaCorr &&
                tau[i].discriminationByElectronLoose && tau[i].discriminationByMuonLoose)
            goodHPSTau.push_back(tau[i]);
    }

    sort(goodHPSTau.begin(), goodHPSTau.end(), myobject_grt());
    return goodHPSTau;
}

vector<myobject> NoIsoTau(myevent *m) {

    vector<myobject> goodHPSTau;
    vector<myobject> tau = m->PreSelectedHPSTaus;
    for (int i = 0; i < tau.size(); i++) {
        double tauPt = tau[i].pt;
        double tauEta = tau[i].eta;
        if (tauPt > 0 && fabs(tauEta) < 2.3 &&
                tau[i].discriminationByDecayModeFinding &&
                tau[i].discriminationByElectronLoose && tau[i].discriminationByMuonLoose)
            goodHPSTau.push_back(tau[i]);
    }
    sort(goodHPSTau.begin(), goodHPSTau.end(), myobject_grt());
    return goodHPSTau;
}

//******************************************************************************************
//******************************************************************************************
//******************************************************************************************
vector<myobject> GoodJet(myevent *m) {

    vector<myobject> goodJet;
    vector<myobject> Jet = m->RecPFJetsAK5;
    for (int i = 0; i < Jet.size(); i++) {
        double JetPt = Jet[i].pt;
        double JetEta = Jet[i].eta;
        if (JetPt > 10 && fabs(JetEta) < 5.0 )
            goodJet.push_back(Jet[i]);
    }
    sort(goodJet.begin(), goodJet.end(), myobject_grt());
    return goodJet;
}




#endif	/* _GOODMUON_H */

