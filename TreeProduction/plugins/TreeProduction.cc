// -*- C++ -*-
//
// Package:    PythiaCumulant/TreeProduction
// Class:      TreeProduction
// 
/**\class TreeProduction TreeProduction.cc PythiaCumulant/TreeProduction/plugins/TreeProduction.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sat, 29 Jun 2019 19:01:44 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// system include files
#include <memory>
#include <iostream>
#include <string>
#include <fstream>

// root include file
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include <vector>
#include "TTree.h"
#include <TVector3.h>

using namespace std;

 Int_t nTrk;
 Float_t correlator2;
 Float_t correlator4;
 const Int_t nTrkMax = 1000;
 Float_t ptV[nTrkMax]; 
 Float_t etaV[nTrkMax]; 
 Float_t phiV[nTrkMax]; 

 float etaGap = 1.2;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeProduction : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TreeProduction(const edm::ParameterSet&);
      ~TreeProduction();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<edm::HepMCProduct> src_;
  edm::EDGetTokenT<reco::GenParticleCollection> genParticleSrc_;
  edm::ESHandle < ParticleDataTable > pdt;
  edm::Service<TFileService> fs;

  TTree *anaTree;
  TH1D* hCorrelator2;
  TH1D* hCorrelator4;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TreeProduction::TreeProduction(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");

    src_ = consumes<edm::HepMCProduct>(iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generator")));
    //src_ = consumes<edm::HepMCProduct>(iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generatorSmeared")));

    genParticleSrc_ = consumes<reco::GenParticleCollection>(iConfig.getUntrackedParameter<edm::InputTag>("genParticleSrc",edm::InputTag("hiGenParticles")));

}


TreeProduction::~TreeProduction()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeProduction::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace HepMC;

/*
    const GenEvent* evt;

    Handle<edm::HepMCProduct> mc;
    iEvent.getByToken(src_,mc);
    evt = mc->GetEvent();

    HepMC::GenEvent::particle_const_iterator begin = evt->particles_begin();
    HepMC::GenEvent::particle_const_iterator end = evt->particles_end();
    int nparticles=-1;

    for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){
      nparticles++;
      if ((*it)->momentum().perp()<0.3) continue;
      if (fabs((*it)->momentum().eta())>2.4) continue; 
      Int_t pdg_id = (*it)->pdg_id();
      Float_t eta = (*it)->momentum().eta();
      Float_t phi = (*it)->momentum().phi();
      Float_t pt = (*it)->momentum().perp();
      const ParticleData * part = pdt->particle(pdg_id );
      Int_t charge = static_cast<Int_t>(part->charge());
      if (charge==0) continue;

      Int_t status = (*it)->status(); // use sta ==1 only

      cout<<"particles: "<<pdg_id<<"  "<<pt<<"  "<<eta<<"  "<<phi<<"  "<<charge<<"  "<<status<<endl;


    }
*/

    int ntrk = 0;
    float pPt[160]={0};
    float pEta[160]={0};
    float pPhi[160]={0};
    hCorrelator2->Reset();
    hCorrelator4->Reset();

    edm::Handle<reco::GenParticleCollection> parts;
    iEvent.getByToken(genParticleSrc_,parts);
    for(UInt_t i = 0; i < parts->size(); ++i){
      const reco::GenParticle& p = (*parts)[i];
      if (p.status()!=1) continue;
      if (p.pt()<0.3) continue;
      if (fabs(p.eta())>2.4) continue;
      if (p.charge()==0) continue;
      //cout<<"particles: "<<p.pdgId()<<"  "<<p.pt()<<"  "<<p.eta()<<"  "<<p.phi()<<"  "<<p.charge()<<"  "<<p.status()<<endl;
      pPt[ntrk] = p.pt();
      pEta[ntrk] = p.eta();
      pPhi[ntrk] = p.phi();
      ntrk++;
      //if(ntrk>150) break;
      if(ntrk>150) return;
    }


    nTrk = ntrk;
    for(int iParticle=0; iParticle<nTrk; iParticle++){
      ptV[iParticle] = pPt[iParticle];
      etaV[iParticle] = pEta[iParticle];
      phiV[iParticle] = pPhi[iParticle];
      for(int j =0; j<nTrk; j++){
        if( fabs(pEta[iParticle] - pEta[j])<etaGap ) continue;
        hCorrelator2->Fill( cos(2*(pPhi[iParticle] - pPhi[j])) ); 
        for(int s =0; s<nTrk; s++){
          if( fabs(pEta[iParticle] - pEta[s])<etaGap || fabs(pEta[j] - pEta[s])<etaGap ) continue;
          for(int t =0; t<nTrk; t++){
            if( fabs(pEta[iParticle] - pEta[t])<etaGap || fabs(pEta[j] - pEta[t])<etaGap || fabs(pEta[s] - pEta[t])<etaGap ) continue;
            hCorrelator4->Fill( cos(2*(pPhi[iParticle] + pPhi[j] - pPhi[s] - pPhi[t])) );
          }
        }
      }
    }
    //cout<<"nTrk = "<<nTrk<<"  "<<correlator2<<"  "<<correlator4<<endl;

    correlator2 = hCorrelator2->GetMean();
    correlator4 = hCorrelator4->GetMean();
    
    anaTree->Fill(); 


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TreeProduction::beginJob()
{
   anaTree = fs->make<TTree>("anaTree","event tree");
   anaTree->Branch("nTrk",&nTrk,"nTrk/I");  
   anaTree->Branch("correlator2",&correlator2,"correlator2/F");  
   anaTree->Branch("correlator4",&correlator4,"correlator4/F");  
   anaTree->Branch("pt",&ptV,"pt[nTrk]/F");  
   anaTree->Branch("eta",&etaV,"eta[nTrk]/F");  
   anaTree->Branch("phi",&phiV,"phi[nTrk]/F");  

   hCorrelator2 = fs->make<TH1D>(Form("hCorrelator2"),"",100,-2,2);
   hCorrelator4 = fs->make<TH1D>(Form("hCorrelator4"),"",100,-2,2);


}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeProduction::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeProduction::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProduction);
