import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
 #       'file:myfile.root'
#        '/cms/ldap_home/jhchoi/miniAOD_copy/output/50plus/042C33E6-93CC-E511-B7D6-0CC47A4D7662.root' 
#      )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("ISR_GENtuple.root"),
                                   closeFileFast = cms.untracked.bool(True)
                                   )
        
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
'root://cluster142.knu.ac.kr//store/mc/RunIISummer15GS/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1-v1/10000/000F8BDD-A77B-E511-B3D4-002590D9D8BE.root' ####10to50 knu gensim
#'/store/mc/RunIISummer15GS/DYJetsToLL_M-200to400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/GEN-SIM/MCRUN2_71_V1_ext2-v1/80000/00C96872-EBD3-E511-9418-24BE05C46B11.root'
      )
)
       
process.demo = cms.EDAnalyzer('JHanalyzer_muon_status2223',
                              
                              genSrc = cms.InputTag("genParticles")
#prunedGenParticles
)


process.p = cms.Path(process.demo)
