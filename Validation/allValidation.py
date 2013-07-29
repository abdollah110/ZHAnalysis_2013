./Make.sh Val1_FullHisto.cc
rm valid_Mega.root
rm FitValues_FR.root
rm log.txt
#./Val1_FullHisto.exe valid_Mega.root VeryNewData_AllInfoJet.root
./Val1_FullHisto.exe valid_Mega.root ../ROOTFiles_V3/Results/Data_8TeV.root 
#./Val1_FullHisto.exe valid_Mega.root veryNewDYJets.root

root .x -q Val2_FRMeasure.cc > log.txt
root .x -q Val3_BGestimation.cc




