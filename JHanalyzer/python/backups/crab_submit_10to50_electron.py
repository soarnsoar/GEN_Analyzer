from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'crab_HLTConfig_dielectron_samewith2017_180308'
config.General.requestName = 'crab_ISR_GEN_Ntupler_10to50_electron_v2'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = ''
#config.JobType.numCores = 4
config.JobType.maxMemoryMB = 4000
# config.JobType.maxJobRuntimeMin = 2000

config.Data.inputDataset = ''
config.Data.useParent = True

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.ignoreLocality = True

#config.Site.storageSite = 'T3_KR_KISTI'
config.Site.storageSite = 'T2_KR_KNU'

#config.Data.lumiMask = '/u/user/jskim/scratch/CMSSW_9_2_13/src/work/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'
#config.Data.lumiMask = '/afs/cern.ch/user/j/jhchoi/ElectronHLT/ex180213_santi/v2/CMSSW_9_2_15/src/test/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'

#config.Data.lumiMask = '/u/user/jhchoi/ElectronHLT/test_4p0_add_doublet_to_l1io/CMSSW_9_2_13/src/HLTrigger/Configuration/test/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'
#config.Data.lumiMask = '/afs/cern.ch/user/j/jhchoi/ElectronHLT/10_0_3_sepa_seq2018_TrackExtractorPSet/v2/CMSSW_10_0_3/src/HLTrigger/Configuration/test/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'
#FirstRun = 305832
#LastRun = 305862
#config.Data.runRange = '%d-%d' % (FirstRun, LastRun)

#version = '_v20171208_'

#config.General.requestName = 'TSntuple'+version+'SingleElectron_Run2017Fv1_%d_to_%d_GoldenJSON_Menu4p0_FromL1ExtendL1Seed' % (FirstRun, LastRun)
#config.Data.inputDataset = '/SingleElectron/Run2017F-PromptReco-v1/AOD'
#config.Data.inputDataset = '/DoubleElectron/Run2017F-PromptReco-v1/AOD'
#config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16DR80Premix-PUMoriond17_plus5percentMaterial_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/AODSIM'
config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16DR80Premix-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/AODSIM'

#config.General.requestName = 'TSntuple'+version+'MET_Run2017Fv1_%d_to_%d_GoldenJSON_Menu4p0_FromL1ExtendL1Seed' % (FirstRun, LastRun)
#config.Data.inputDataset = '/MET/Run2017F-PromptReco-v1/AOD'

#config.JobType.psetName = 'HLT_IsoMu27_Mu50_MasterTable100X_loose_ntupler.py'
#config.JobType.psetName = 'HLT_IsoMu27_Mu50_MasterTable100X_separateseq2018_tightdoublet_ntupler.py'
config.JobType.psetName = 'ISR_GEN_Ntupler_electron.py'
#config.JobType.psetName = 'hlt_withid_ntupler.py'
config.Site.blacklist = ['T3_UK_London_RHUL','T3_UK_SGrid_Oxford','T3_US_Rice']
