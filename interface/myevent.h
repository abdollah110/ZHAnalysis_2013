#ifndef __MYEVENT_HH__
#define __MYEVENT_HH__
#include <vector>
#include <map>
#include <utility>
#include "myobject.h"
#include "TObject.h"

using namespace std;
class myevent : public TObject {
public:

    myevent() {
        ;
    }

    ~myevent() {
        ;
    }

    vector<myobject> RecPFJetsAK5;
    vector<myobject> RecPFJetsAK5_Up_SubTotal;
    vector<myobject> RecPFJetsAK5_Down_SubTotal;
    vector<myobject> RecPFJetsAK5_Up_Total;
    vector<myobject> RecPFJetsAK5_Down_Total;
    vector<myobject> RecGenParticle;
    vector<myobject> RecGenMet;
    vector<myobject> RecGenJet;
    vector<myobject> PreSelectedElectrons;
    vector<myobject> PreSelectedMuons;
    vector<myobject> PreSelectedHPSTaus;
    vector<myobject> RecPFMet;
    vector<myobject> RectcMet;
    vector<myobject> Vertex;

    map<string, int> HLT;

    unsigned int runNumber;
    unsigned int eventNumber;
    unsigned int lumiNumber;
    unsigned int HLT_DiElectron;
    unsigned int HLT_DiMuon;
    int PUInfo;
    int PUInfo_true;
    int PUInfo_Bunch0;
    double RhoCorr;
    double RhoCenNeutral;
    double RhoCenCharged;
    double RhoCenNeutralTight;
    double Rho;

    // MET significance matrix                                                                                                                                                                                                    
    float MET_sigMatrix_00;
    float MET_sigMatrix_01;
    float MET_sigMatrix_10;
    float MET_sigMatrix_11;


private:

    ClassDef(myevent, 1)
};
#endif
