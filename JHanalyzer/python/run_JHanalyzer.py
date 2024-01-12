import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

        
process.source = cms.Source("PoolSource",
                                    # replace 'myfile.root' with the source file you want to use                                                                      
           fileNames = cms.untracked.vstring(
#            'file:/cms/ldap_home/jhchoi/miniAOD_copy/output/50plus/042C33E6-93CC-E511-B7D6-0CC47A4D7662.root'
# 'root://cms-xrd-global.cern.ch//store/mc/RunIISummer15GS/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/10000/000F8BDD-A77B-E511-B3D4-002590D9D8BE.root'
#'root://cms-xrd-global.cern.ch//store/mc/RunIISummer15GS/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00598ACE-D496-E511-888F-0CC47A4C8EE8.root' 
 
#'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16DR80Premix/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/AODSIM/PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/000D1CCB-D4B2-E611-8783-0025905B85DC.root' #2016

#'file:/cms/ldap_home/jhchoi/miniAOD_copy/output_GEN/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/0008638B-A0D5-E611-9297-E0071B740D80.root'

#'root://cluster142.knu.ac.kr//store/mc/RunIISummer15GS/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00598ACE-D496-E511-888F-0CC47A4C8EE8.root'

#'root://cms-xrd-global.cern.ch//store/mc/RunIISummer15GS/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00598ACE-D496-E511-888F-0CC47A4C8EE8.root'
#'srm://cluster142.knu.ac.kr:8443/srm/managerv2?SFN=/pnfs/knu.ac.kr/data/cms/store/mc/RunIISummer15GS/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/00598ACE-D496-E511-888F-0CC47A4C8EE8.root'

#'root://cluster142.knu.ac.kr//store/mc/RunIISummer15GS/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/00000/FEBFC3DC-FA96-E511-A479-0CC47A78A4B8.root' ####50plus knu gensim
#'root://cluster142.knu.ac.kr//store/mc/RunIISummer15GS/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/10000/000F8BDD-A77B-E511-B3D4-002590D9D8BE.root' ####10to50 knu gensim
#'/store/mc/RunIISummer15GS/DYJetsToLL_M-200to400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1_ext2-v1/80000/00C96872-EBD3-E511-9418-24BE05C46B11.root'

#"file:/home/jhchoi/mcm_filter_test/HIG-RunIIFall18wmLHEGS-01691_inLHE.root"
#'root://cms-xrd-global.cern.ch/'
"file:///data6/Users/jhchoi/GEN/input_GEN/mc/RunIISummer20UL18GEN/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/GEN/106X_upgrade2018_realistic_v4-v2/1D1D6DF6-0B62-7F47-81BC-7FAE415CEB69.root"
#'root://cms-xrd-global.cern.ch//QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16GENAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/GEN'
      )
)
       
process.demo = cms.EDAnalyzer('JHanalyzer',
                              
                              genSrc = cms.InputTag("genParticles")
#prunedGenParticles
)


process.p = cms.Path(process.demo)
