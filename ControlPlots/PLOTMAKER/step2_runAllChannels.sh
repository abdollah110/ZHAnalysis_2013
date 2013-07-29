rm -rf Prefit
mkdir -p Prefit
root -l -q htt_tt_0_7TeV.C++
root -l -q htt_tt_1_7TeV.C++
root -l -q htt_et_0_7TeV.C++
root -l -q htt_et_1_7TeV.C++
root -l -q htt_mt_0_7TeV.C++
root -l -q htt_mt_1_7TeV.C++
root -l -q htt_em_0_7TeV.C++
root -l -q htt_em_1_7TeV.C++
root -l -q htt_tt_0_8TeV.C++
root -l -q htt_tt_1_8TeV.C++
root -l -q htt_et_0_8TeV.C++
root -l -q htt_et_1_8TeV.C++
root -l -q htt_mt_0_8TeV.C++
root -l -q htt_mt_1_8TeV.C++
root -l -q htt_em_0_8TeV.C++
root -l -q htt_em_1_8TeV.C++
hadd -f combined_7TeV.root *_zh_rescaled_7TeV_.root
hadd -f combined_8TeV.root *_zh_rescaled_8TeV_.root
hadd -f combined_78TeV.root *_zh_rescaled_*TeV_.root
hadd -f llem_7TeV.root eeem_zh_rescaled_7TeV_.root mmme_zh_rescaled_7TeV_.root
hadd -f llet_7TeV.root eeet_zh_rescaled_7TeV_.root mmet_zh_rescaled_7TeV_.root
hadd -f lltt_7TeV.root eett_zh_rescaled_7TeV_.root mmtt_zh_rescaled_7TeV_.root
hadd -f llmt_7TeV.root eemt_zh_rescaled_7TeV_.root mmmt_zh_rescaled_7TeV_.root
hadd -f llem_8TeV.root eeem_zh_rescaled_8TeV_.root mmme_zh_rescaled_8TeV_.root
hadd -f llet_8TeV.root eeet_zh_rescaled_8TeV_.root mmet_zh_rescaled_8TeV_.root
hadd -f lltt_8TeV.root eett_zh_rescaled_8TeV_.root mmtt_zh_rescaled_8TeV_.root
hadd -f llmt_8TeV.root eemt_zh_rescaled_8TeV_.root mmmt_zh_rescaled_8TeV_.root
hadd -f llem_78TeV.root eeem_zh_rescaled_7TeV_.root mmme_zh_rescaled_7TeV_.root eeem_zh_rescaled_8TeV_.root mmme_zh_rescaled_8TeV_.root
hadd -f llet_78TeV.root eeet_zh_rescaled_7TeV_.root mmet_zh_rescaled_7TeV_.root eeet_zh_rescaled_8TeV_.root mmet_zh_rescaled_8TeV_.root
hadd -f lltt_78TeV.root eett_zh_rescaled_7TeV_.root mmtt_zh_rescaled_7TeV_.root eett_zh_rescaled_8TeV_.root mmtt_zh_rescaled_8TeV_.root
hadd -f llmt_78TeV.root eemt_zh_rescaled_7TeV_.root mmmt_zh_rescaled_7TeV_.root eemt_zh_rescaled_8TeV_.root mmmt_zh_rescaled_8TeV_.root

mv *scaled*.* Prefit/.
mv *TeV.root Prefit/.