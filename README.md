* How to setup(Do not "git clone" this code first. Follow below lines.


##----start----##


export SCRAM_ARCH=slc7_amd64_gcc700

source /cvmfs/cms.cern.ch/cmsset_default.sh

scram p CMSSW CMSSW_10_6_25

cd CMSSW_10_6_25/src

eval \`scram runtime -sh\`

git clone git@github.com:soarnsoar/GEN_Analyzer.git

eval `scram runtime -sh` ## compile "JHanalyzer" plugin

cd $CMSSW_BASE/src/GEN_Analyzer/JHanalyzer/python

cmsRun run_JHanalyzer.py ## this line will run "$CMSSW_BASE/src/GEN_Analyzer/JHanalyzer/plugin/JHanalyzer.cc"
##and show  event records!

##---end----#
* Location of test EDM file in tamsa server
/data6/Users/jhchoi_public/input_GEN/mc/RunIISummer20UL18GEN/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/GEN/106X_upgrade2018_realistic_v4-v2/1D1D6DF6-0B62-7F47-81BC-7FAE415CEB69.root


* command to show the structure of a EDM file
edmDumpEventContent *.root
