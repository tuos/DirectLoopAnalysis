from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'v01_pythia_gensim'
config.General.workArea = 'project_v01_pythia_gensim'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'

config.Data.inputDataset = '/MinBias_TuneCUETP8M1_2017_5p02TeV-pythia8/RunIIpp5Spring18GS-94X_mc2017_realistic_v10For2017G_v3-v2/GEN-SIM'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'FileBased'
config.Data.splitting = 'Automatic'
#config.Data.unitsPerJob = 2
config.Data.outLFNDirBase = '/store/user/tuos/loops/cumulants/pythia/v01_pythia_gensim'
config.Data.publication = False
config.Data.outputDatasetTag = 'v01_pythia_gensim'

config.Site.storageSite = 'T2_US_Vanderbilt'
