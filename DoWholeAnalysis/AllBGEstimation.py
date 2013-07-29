./Make.sh Val1_FullHisto.cc
rm valid_Mega.root
rm FitValues_FR.root
rm log.txt

./Val1_FullHisto.exe  Total Total 0.3 0 outRoot_V3/Data_8TeV.root  ../ROOTFiles_V3/Results/Data_8TeV.root
cp  outRoot_V3/Data_8TeV.root valid_Mega.root
root .x -q Val2_FRMeasure.cc
root .x -q Val3_BGestimation.cc 


