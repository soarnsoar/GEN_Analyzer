import FWCore.ParameterSet.Config as cms

process = cms.Process("geninfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


flist=open("samples/UL18_QCD_MuEnriched.txt")
lines=flist.readlines()
finput=[]
for line in lines:
    finput.append(line.rstrip('\n'))
#finput=",".join(lines)
process.source = cms.Source("PoolSource",
                    
                            fileNames = cms.untracked.vstring(
                                #finput
                                #finput
                                #'root://cms-xrd-global.cern.ch///store/mc/RunIISummer20UL17RECO/QCD_Pt-20toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/GEN-SIM-RECO/PUForTRK_TRK_106X_mc2017_realistic_v6-v2/50000/143D95AF-59B5-144E-B6AB-6F627400D4F5.root'
                                #'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16DR80Premix/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/AODSIM/PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/000D1CCB-D4B2-E611-8783-0025905B85DC.root' #2016
                                #["file:///data6/Users/jhchoi_public/input_GEN/mc/RunIISummer20UL18GEN/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/GEN/106X_upgrade2018_realistic_v4-v2/1D1D6DF6-0B62-7F47-81BC-7FAE415CEB69.root"]
                                [
                                    "file:///data6/Users/jhchoi_public/input_GEN/mc/RunIISummer20UL18RECO/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/AODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/100000/24D3ED08-D4EF-2E4E-9FE1-23BD38D5D85A.root"
                                ]
                                #"root://xrootd-cms.infn.it///store/mc/RunIISummer20UL16GENAPV/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/GEN/106X_mcRun2_asymptotic_preVFP_v8-v1/250000/4E27B459-8AF4-9D45-A982-7223FD36F14D.root"
                                #"root://cmsxrootd.fnal.gov///store/mc/RunIISummer20UL16GENAPV/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/GEN/106X_mcRun2_asymptotic_preVFP_v8-v1/250000/4E27B459-8AF4-9D45-A982-7223FD36F14D.root"
                            )
)

process.geninfo = cms.EDAnalyzer('JHanalyzer_Bmeson',
                                 genSrc = cms.InputTag("genParticles")
                                #prunedGenParticles
                             )


process.p = cms.Path(process.geninfo)
