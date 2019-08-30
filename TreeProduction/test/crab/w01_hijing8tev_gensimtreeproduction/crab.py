from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'w01_hijing8tev_gensimtreeproduction'
config.General.workArea = 'project_w01_hijing8tev_gensimtreeproduction'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'

config.Data.inputDataset = '/HIJING_pPb_8160_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'FileBased'
config.Data.splitting = 'Automatic'
#config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/tuos/loops/cumulants/hijing/w01_hijing8tev_gensimtreeproduction'
config.Data.publication = False
config.Data.outputDatasetTag = 'w01_hijing8tev_gensimtreeproduction'

config.Site.storageSite = 'T2_US_Vanderbilt'
