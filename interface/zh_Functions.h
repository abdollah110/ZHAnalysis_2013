

#ifndef _ZH_FUNCTION_H
#define	_ZH_FUNCTION_H


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
#include "Leptons_PreSelection.h"
#include <TLorentzVector.h>
#include "zh_Auxiliary.h"

using namespace std;

bool OverLapWithTaus(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    bool Over = (deltaR(a, c) > 0.3 && deltaR(a, d) > 0.3 && deltaR(b, c) > 0.3 && deltaR(b, d) > 0.3 && deltaR(a, b) > 0.3 && deltaR(c, d) > 0.3);
    bool dZ_expo = (fabs(a.z_expo - b.z_expo) < 0.1 && fabs(a.z_expo - c.z_expo) < 0.1 && fabs(a.z_expo - d.z_expo) < 0.1);
    //    bool dz  =( (fabs(a.z - b.z)< 0.2) && (fabs(a.z - c.z) < 0.2)  && (fabs(a.z - d.z) < 0.2 ));
    //    return (Over && dZ_expo && dz );
    return (Over && dZ_expo);
    //    return Over ;

}

bool OverLap(myobject const& a, myobject const& b, myobject const& c) {
    bool Over = (deltaR(a, c) > 0.1 && deltaR(b, c) > 0.1 && deltaR(a, b) > 0.1);
    bool dZ_expo = (fabs(a.z_expo - b.z_expo) < 0.1 && fabs(a.z_expo - c.z_expo) < 0.1);
    return (Over && dZ_expo);
}

double HZ_deltaR(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    TLorentzVector LorentzV_i, LorentzV_j, LorentzV_k, LorentzV_l, LorentzV_Z, LorentzV_H;
    LorentzV_i.SetPtEtaPhiE(a.pt, a.eta, a.phi, a.E);
    LorentzV_j.SetPtEtaPhiE(b.pt, b.eta, b.phi, b.E);
    LorentzV_k.SetPtEtaPhiE(c.pt, c.eta, c.phi, c.E);
    LorentzV_l.SetPtEtaPhiE(d.pt, d.eta, d.phi, d.E);
    LorentzV_Z = LorentzV_i + LorentzV_j;
    LorentzV_H = LorentzV_k + LorentzV_l;
    return LorentzV_Z.DeltaR(LorentzV_H);
}

double HZ_deltaPhi(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    TLorentzVector LorentzV_i, LorentzV_j, LorentzV_k, LorentzV_l, LorentzV_Z, LorentzV_H;
    LorentzV_i.SetPtEtaPhiE(a.pt, a.eta, a.phi, a.E);
    LorentzV_j.SetPtEtaPhiE(b.pt, b.eta, b.phi, b.E);
    LorentzV_k.SetPtEtaPhiE(c.pt, c.eta, c.phi, c.E);
    LorentzV_l.SetPtEtaPhiE(d.pt, d.eta, d.phi, d.E);
    LorentzV_Z = LorentzV_i + LorentzV_j;
    LorentzV_H = LorentzV_k + LorentzV_l;
    return fabs(LorentzV_Z.DeltaPhi(LorentzV_H));
}

double Z_Pt(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    TLorentzVector LorentzV_i, LorentzV_j, LorentzV_k, LorentzV_l, LorentzV_Z, LorentzV_H;
    LorentzV_i.SetPtEtaPhiE(a.pt, a.eta, a.phi, a.E);
    LorentzV_j.SetPtEtaPhiE(b.pt, b.eta, b.phi, b.E);
    LorentzV_Z = LorentzV_i + LorentzV_j;
    return LorentzV_Z.Pt();
}

double H_Pt(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    TLorentzVector LorentzV_i, LorentzV_j, LorentzV_k, LorentzV_l, LorentzV_Z, LorentzV_H;
    LorentzV_k.SetPtEtaPhiE(c.pt, c.eta, c.phi, c.E);
    LorentzV_l.SetPtEtaPhiE(d.pt, d.eta, d.phi, d.E);
    LorentzV_H = LorentzV_k + LorentzV_l;
    return LorentzV_H.Pt();
}

float Find_Closet_Jet(myobject const& a, myevent *m) {
    vector<myobject> Jet = GoodJet(m);
    double fake_Pt = a.pt;
    double Refer_R = 100;


    for (int i = 0; i < Jet.size(); i++) {
        if (deltaR(a, Jet[i]) < Refer_R) {
            Refer_R = deltaR(a, Jet[i]);
            if (Refer_R < 0.5 && Jet[i].pt >= a.pt)
                fake_Pt = Jet[i].pt;
        }
    }
    return fake_Pt;
}

bool WZ_Rej(myevent *m, myobject const& a) {
    vector<myobject> Met = m->RecPFMet;
    bool met = Met.front().pt < 20;
    bool tmass = TMass(a, Met.front()) < 30;

    if (met && tmass)
        return true;
    else
        return false;


}

double jet_HT(myevent *m) {
    vector<myobject> jet;
    jet = m->RecPFJetsAK5;
    double ht_jet = 0;
    //    for (int k = 0; k < jet.size(); k++) {
    //        if (jet[k].pt > 10 && jet[k].eta < 3.0) {
    //            ht_jet = ht_jet + jet[k].pt;
    //        }
    //    }
    return ht_jet;
}

float getSumPtCut(std::string channel, myobject const& a, myobject const& b, myobject const& c, myobject const& d) {

    // return 1;



    if (channel == "mmtt" || channel == "eett") {
        return (c.pt + d.pt > 60);
    }
    if (channel == "mmmt" || channel == "mmet" || channel == "eemt" || channel == "eeet") {
        return (c.pt + d.pt > 45);
    }
    if (channel == "eeem" || channel == "mmme") {
        return (c.pt + d.pt > 30);
    }

}



#endif	/*ZH_FUNCTION_H*/
