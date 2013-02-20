

#ifndef _DELTA_H
#define	_DELTA_H


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

using namespace std;

inline double deltaPhi(myobject const& a, myobject const& b) {
    double result = a.phi - b.phi;
    while (result > M_PI) result -= 2 * M_PI;
    while (result <= -M_PI) result += 2 * M_PI;
    return fabs(result);
}

inline double deltaR2(myobject const& a, myobject const& b) {
    double deta = a.eta - b.eta;
    double dphi = deltaPhi(a, b);
    return deta * deta + dphi*dphi;
}
//inline double deltaR2(double eta1, double phi1, double eta2, double phi2) {
//    double deta = eta1 - eta2;
//    double dphi = deltaPhi(phi1, phi2);
//    return deta * deta + dphi*dphi;
//}

inline double deltaR(myobject const& a, myobject const& b) {
    return sqrt(deltaR2(a, b));
}
//inline double deltaR(double eta1, double phi1, double eta2, double phi2) {
//    return sqrt(deltaR2(eta1, phi1, eta2, phi2));
//}

double delta(myevent *m, myobject * tau) {
    vector<myobject> jet;
    jet = m->RecPFJetsAK5;
    double minDis = 1000;
    double mydeltaR;
    for (vector<myobject>::iterator itjet = jet.begin(); itjet != jet.end(); itjet++) {
        if (itjet->pt > 20) {
            mydeltaR = deltaR(*tau, *itjet);
            if (mydeltaR > 0.1)
                if (mydeltaR < minDis) minDis = mydeltaR;
        }
    }

    return minDis;
}

//struct  InvarMass_2{
//    double InvarMass_2 ()(myobject const& a, myobject const& b) const {
//        return (a.pt + b.pt);
//    }
//};

//struct  InvarMass_2{

double InvarMass_2(myobject const& a, myobject const& b) {
    return sqrt(pow(a.E + b.E, 2) - pow(a.px + b.px, 2) - pow(a.py + b.py, 2) - pow(a.pz + b.pz, 2));
}

double TMass(myobject const& a, myobject const& b) {
    return sqrt(pow(a.et + b.et, 2) - pow(a.px + b.px, 2) - pow(a.py + b.py, 2));
}

double TMass_2(myobject const& a, myobject const& b) {
    return sqrt(pow(a.et + b.et, 2) - pow(a.px + b.px, 2) - pow(a.py + b.py, 2));
}

double InvarMass_4(myobject const& a, myobject const& b, myobject const& c, myobject const& d) {
    return sqrt(pow(a.E + b.E + c.E + d.E, 2) - pow(a.px + b.px + c.px + d.px, 2) - pow(a.py + b.py + c.py + d.py, 2) - pow(a.pz + b.pz + c.pz + d.pz, 2));
    //        return (pow(a.pt+b.pt+c.pt+d.pt,2)-pow(a.px+b.px+c.px+d.px,2)-pow(a.py+b.py+c.py+d.py,2)-pow(a.pz+b.pz+c.pz+d.pz,2));
}
//};

double TMass(double et1, double et2, double px1, double px2, double py1, double py2) {
    return sqrt(pow(et1 + et2, 2) - pow(px1 + px2, 2) - pow(py1 + py2, 2));

}

double InvarMass(double et1, double et2, double px1, double px2, double py1, double py2, double pz1, double pz2) {
    return sqrt(pow(et1 + et2, 2) - pow(px1 + px2, 2) - pow(py1 + py2, 2) - pow(pz1 + pz2, 2));
}

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

double Find_Closet_Jet(myobject const& a, myevent *m) {
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

int bjet_Multiplicity(myevent *m) {
    vector<myobject> mu_ = GoodMuon(m);
    vector<myobject> ele_ = GoodElectron(m);
    vector<myobject> tau_ = GoodTau(m); // Loose HPS
    vector<myobject> jet = GoodJet(m);

    //    jet = m->RecPFJetsAK5;
    int num_bj = 0;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
    for (int k = 0; k < jet.size(); k++) {
        //if (jet[k].pt > 20 && fabs(jet[k].eta) < 2.4 && jet[k].bDiscriminatiors_CSV > 0.679) {
        if (jet[k].pt > 20 && fabs(jet[k].eta) < 2.4 && jet[k].bDiscriminatiors_CSV > 0.898) {
            bool Nooverlap = true;

            for (int p = 0; p < mu_.size(); p++) {
                if (deltaR(jet[k], mu_[p]) < 0.4)
                    Nooverlap = false;
            }
            for (int q = 0; q < ele_.size(); q++) {
                if (deltaR(jet[k], ele_[q]) < 0.4)
                    Nooverlap = false;
            }
            /*
            for (int r = 0; r < tau_.size(); r++) {
                       if (deltaR(jet[k], tau_[r]) < 0.4)
                           Nooverlap = false;
                   }
             */
            if (Nooverlap) num_bj++;
        }

    }

    return num_bj;
}

double getSumPtCut(std::string channel, myobject const& a, myobject const& b, myobject const& c, myobject const& d) {

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



#endif	/* _JETVETO_H */

