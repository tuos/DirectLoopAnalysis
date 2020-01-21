from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'PYTHIA8_gap08v4_OCT13TeV500M'
config.General.workArea = 'project_PYTHIA8_gap08v4_OCT13TeV500M'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/MinBias/tuos-PYTHIA8_OCT13TeV200M_v1-b760962cb2794e34f66b7129f2502618/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
#config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/loops/cumulants/pythia/PYTHIA8_gap08v4_OCT13TeV500M'
config.Data.publication = False
config.Data.outputDatasetTag = 'PYTHIA8_gap08v4_OCT13TeV500M'

config.Site.storageSite = 'T2_US_Vanderbilt'
