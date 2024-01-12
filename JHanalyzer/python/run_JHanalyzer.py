import FWCore.ParameterSet.Config as cms

process = cms.Process("geninfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

        
process.source = cms.Source("PoolSource",
                                    # replace 'myfile.root' with the source file you want to use                                                                      
           fileNames = cms.untracked.vstring(
#'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16DR80Premix/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/AODSIM/PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/000D1CCB-D4B2-E611-8783-0025905B85DC.root' #2016
"file:///data6/Users/jhchoi_public/input_GEN/mc/RunIISummer20UL18GEN/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/GEN/106X_upgrade2018_realistic_v4-v2/1D1D6DF6-0B62-7F47-81BC-7FAE415CEB69.root"
      )
)
       
process.geninfo = cms.EDAnalyzer('JHanalyzer',
                                 genSrc = cms.InputTag("genParticles")
                                #prunedGenParticles
                             )


process.p = cms.Path(process.geninfo)
