./Make.sh Val0_FullTre.cc
rm valid_MegaNew.root
rm FitValues_FR.root
rm log.txt
#./Val1_FullHisto.exe valid_Mega.root VeryNewData_AllInfoJet.root
./Val0_FullTre.exe valid_MegaNew.root ../ROOTFiles/Results/Data.root
#./Val1_FullHisto.exe valid_Mega.root veryNewDYJets.root

root .x -q Val2_FRMeasure.cc > log.txt
root .x -q Val03_BGestimation.cc




