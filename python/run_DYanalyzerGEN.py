import FWCore.ParameterSet.Config as cms

process = cms.Process("DYGEN")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
 #       'file:myfile.root'
#        '/cms/ldap_home/jhchoi/miniAOD_copy/output/50plus/042C33E6-93CC-E511-B7D6-0CC47A4D7662.root' 
#      )


        
process.source = cms.Source("PoolSource",
                                    # replace 'myfile.root' with the source file you want to use                                                                      
           fileNames = cms.untracked.vstring(


"file:DAS_MG_EXERCISE.root"
      )
)
      

process.TFileService = cms.Service("TFileService", fileName = cms.string("histoGEN.root") )
 
process.DASana = cms.EDAnalyzer('DYanalyzerGEN',
                              
                              genSrc = cms.InputTag("genParticles")
#prunedGenParticles
)


process.p = cms.Path(process.DASana)
