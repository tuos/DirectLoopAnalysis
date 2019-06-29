import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/user/t/tuos/work/private/cumulant/loops/CMSSW_9_4_6_patch1/src/PythiaCumulant/PythiaCumulant/test/F2D718DA-3361-E811-B68C-0CC47ABB5178.root'
    )
)

process.demo = cms.EDAnalyzer('PythiaCumulant',
  src = cms.untracked.InputTag("generator"),
  #src = cms.untracked.InputTag("generatorSmeared"),
  genParticleSrc = cms.untracked.InputTag("genParticles")
)


process.p = cms.Path(process.demo)
