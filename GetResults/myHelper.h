/* 
 * File:   myHelper.h
 * Author: abdollahmohammadi
 *
 * Created on March 3, 2013, 11:59 AM
 */

#ifndef MYHELPER_H
#define	MYHELPER_H

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
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>
#include "../interface/zh_Auxiliary.h"

bool WZ_Rej_B(float pt3lep, float px3lep, float py3lep, float met, float metPhi) {
    bool b_met = met < 20;
    bool b_tmass = sqrt(pow(pt3lep + met, 2) - pow(px3lep + met*cos(metPhi), 2) - pow(py3lep + met*sin(metPhi), 2)) < 30;
//    if (b_met && b_tmass)
    if (b_tmass )
        return true;
    else
        return false;
}

#endif	/* MYHELPER_H */

