#python mlfit_and_copy.py LIMITS/std/sm/cmb/125
python produce_macros.py  -c "et tt mt em" --sm-categories-et "0" --sm-categories-tt "0"  --sm-categories-mt "0" --sm-categories-em "0" -p "7TeV 8TeV" 
python produce_macros_2.py  -c "et tt mt em" --sm-categories-et "0" --sm-categories-tt "0"  --sm-categories-mt "0" --sm-categories-em "0" -p "7TeV 8TeV"
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
hadd -f combined_7TeV.root *_zh_unscaled_7TeV_.root
hadd -f combined_8TeV.root *_zh_unscaled_8TeV_.root
hadd -f combined_78TeV.root *_zh_unscaled_*TeV_.root
hadd -f llem_7TeV.root eeem_zh_unscaled_7TeV_.root mmme_zh_unscaled_7TeV_.root
hadd -f llet_7TeV.root eeet_zh_unscaled_7TeV_.root mmet_zh_unscaled_7TeV_.root
hadd -f lltt_7TeV.root eett_zh_unscaled_7TeV_.root mmtt_zh_unscaled_7TeV_.root
hadd -f llmt_7TeV.root eemt_zh_unscaled_7TeV_.root mmmt_zh_unscaled_7TeV_.root
hadd -f llem_8TeV.root eeem_zh_unscaled_8TeV_.root mmme_zh_unscaled_8TeV_.root
hadd -f llet_8TeV.root eeet_zh_unscaled_8TeV_.root mmet_zh_unscaled_8TeV_.root
hadd -f lltt_8TeV.root eett_zh_unscaled_8TeV_.root mmtt_zh_unscaled_8TeV_.root
hadd -f llmt_8TeV.root eemt_zh_unscaled_8TeV_.root mmmt_zh_unscaled_8TeV_.root
hadd -f llem_78TeV.root eeem_zh_unscaled_7TeV_.root mmme_zh_unscaled_7TeV_.root eeem_zh_unscaled_8TeV_.root mmme_zh_unscaled_8TeV_.root
hadd -f llet_78TeV.root eeet_zh_unscaled_7TeV_.root mmet_zh_unscaled_7TeV_.root eeet_zh_unscaled_8TeV_.root mmet_zh_unscaled_8TeV_.root
hadd -f lltt_78TeV.root eett_zh_unscaled_7TeV_.root mmtt_zh_unscaled_7TeV_.root eett_zh_unscaled_8TeV_.root mmtt_zh_unscaled_8TeV_.root
hadd -f llmt_78TeV.root eemt_zh_unscaled_7TeV_.root mmmt_zh_unscaled_7TeV_.root eemt_zh_unscaled_8TeV_.root mmmt_zh_unscaled_8TeV_.root

mv *unscaled*.* Prefit/.
mv *TeV.root Prefit/.

root -b -q 'draw_prefit.C+("Prefit/llem_7TeV.root","em",7)'
root -b -q 'draw_prefit.C+("Prefit/llem_8TeV.root","em",8)'
root -b -q 'draw_prefit.C+("Prefit/llem_78TeV.root","em",78)'
root -b -q 'draw_prefit.C+("Prefit/llmt_7TeV.root","mt",7)'
root -b -q 'draw_prefit.C+("Prefit/llmt_8TeV.root","mt",8)'
root -b -q 'draw_prefit.C+("Prefit/llmt_78TeV.root","mt",78)'
root -b -q 'draw_prefit.C+("Prefit/llet_7TeV.root","et",7)'
root -b -q 'draw_prefit.C+("Prefit/llet_8TeV.root","et",8)'
root -b -q 'draw_prefit.C+("Prefit/llet_78TeV.root","et",78)'
root -b -q 'draw_prefit.C+("Prefit/lltt_7TeV.root","tt",7)'
root -b -q 'draw_prefit.C+("Prefit/lltt_8TeV.root","tt",8)'
root -b -q 'draw_prefit.C+("Prefit/lltt_78TeV.root","tt",78)'
root -b -q 'draw_prefit.C+("Prefit/combined_7TeV.root","cmb",7)'
root -b -q 'draw_prefit.C+("Prefit/combined_8TeV.root","cmb",8)'
root -b -q 'draw_prefit.C+("Prefit/combined_78TeV.root","cmb",78)'

mv *unscaled*.* Prefit/.
rrm -rf *.d *.so


