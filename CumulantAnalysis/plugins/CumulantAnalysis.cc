// -*- C++ -*-
//
// Package:    PythiaCumulant/CumulantAnalysis
// Class:      CumulantAnalysis
//
/**\class CumulantAnalysis CumulantAnalysis.cc PythiaCumulant/CumulantAnalysis/plugins/CumulantAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Mon, 21 Oct 2019 17:58:24 GMT
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
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

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

     const int nMultBin = 16;
     int multMin[nMultBin] = { 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 61, 71, 81,  91, 101, 121};
     int multMax[nMultBin] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150};

     Int_t nTrk;
     Float_t corr_evtEntries;
     Float_t corr_evtCosPhi13;
     Float_t corr_evtCosPhi1234;
     Float_t corr_evtCosSC2323;
     Float_t corr_evtCosSC3;
     Float_t corr_evtCosSC2424;
     Float_t corr_evtCosSC4;
     Float_t corr_evtEntries3;
     Float_t corr_evtCosAC224;
     Float_t corr_evtCosAC235;


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class CumulantAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit CumulantAnalysis(const edm::ParameterSet&);
      ~CumulantAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      //edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
  edm::EDGetTokenT<edm::HepMCProduct> src_;
  edm::EDGetTokenT<reco::GenParticleCollection> genParticleSrc_;
  edm::ESHandle < ParticleDataTable > pdt;
  edm::Service<TFileService> fs;

  TTree *anaTree;
  TH1D* hCorrelator2[nMultBin];
  TH1D* hCorrelator4[nMultBin];
  TH1D* hCorrelatorSC2323[nMultBin];
  TH1D* hCorrelatorSC3[nMultBin];
  TH1D* hCorrelatorSC2424[nMultBin];
  TH1D* hCorrelatorSC4[nMultBin];
  TH1D* hCorrelatorAC224[nMultBin];
  TH1D* hCorrelatorAC235[nMultBin];
     TH1D *evtCosPhi13;
     TH1D *evtCosPhi1234;
     TH1D *evtCosSC2323;
     TH1D *evtCosSC3;
     TH1D *evtCosSC2424;
     TH1D *evtCosSC4;
     TH1D *evtCosAC224;
     TH1D *evtCosAC235;

     double etaGap_;

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
CumulantAnalysis::CumulantAnalysis(const edm::ParameterSet& iConfig) :
  //tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
  src_(consumes<edm::HepMCProduct>(iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generator")))),
  //src_(consumes<edm::HepMCProduct>(iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generatorSmeared")))),
  genParticleSrc_(consumes<reco::GenParticleCollection>(iConfig.getUntrackedParameter<edm::InputTag>("genParticleSrc",edm::InputTag("hiGenParticles")))),
  etaGap_(iConfig.getParameter<double>("etaGap"))
{
   //now do what ever initialization is needed


}


CumulantAnalysis::~CumulantAnalysis()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
CumulantAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace HepMC;
/*
    Handle<TrackCollection> tracks;
    iEvent.getByToken(tracksToken_, tracks);
    for(TrackCollection::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
      // int charge = itTrack->charge();
    }
*/

    int ntrk = 0;
    //float pPt[160]={0};
    float pEta[160]={0};
    float pPhi[160]={0};
    //hCorrelator2->Reset();
    //hCorrelator4->Reset();

    evtCosPhi13->Reset(); evtCosPhi1234->Reset();
    evtCosSC2323->Reset(); evtCosSC3->Reset();
    evtCosSC2424->Reset(); evtCosSC4->Reset();
    evtCosAC224->Reset(); evtCosAC235->Reset();

    edm::Handle<reco::GenParticleCollection> parts;
    iEvent.getByToken(genParticleSrc_,parts);
    for(UInt_t i = 0; i < parts->size(); ++i){
      const reco::GenParticle& p = (*parts)[i];
      if (p.status()!=1) continue;
      if (p.pt()<0.3) continue;
      if (fabs(p.eta())>2.4) continue;
      if (p.charge()==0) continue;
      //cout<<"particles: "<<p.pdgId()<<"  "<<p.pt()<<"  "<<p.eta()<<"  "<<p.phi()<<"  "<<p.charge()<<"  "<<p.status()<<endl;
      //pPt[ntrk] = p.pt();
      pEta[ntrk] = p.eta();
      pPhi[ntrk] = p.phi();
      ntrk++;
      //if(ntrk>150) break;
      if(ntrk>150) return;
    }


    nTrk = ntrk;
    for(int i1=0; i1<nTrk; i1++){
      //ptV[i1] = pPt[i1];
      ///etaV[i1] = pEta[i1];
      ///phiV[i1] = pPhi[i1];

      for(int i2 =0; i2<nTrk; i2++){
        if( fabs(pEta[i1] - pEta[i2])<etaGap_ ) continue;
        //hCorrelator2->Fill( cos(2*(pPhi[i1] - pPhi[i2])) ); 
        for(int i3 =0; i3<nTrk; i3++){
          if( fabs(pEta[i1] - pEta[i3])<etaGap_ || fabs(pEta[i2] - pEta[i3])<etaGap_ ) continue;
            evtCosAC224->Fill(cos(2*pPhi[i1]+2*pPhi[i2]-4*pPhi[i3]));
            evtCosAC235->Fill(cos(2*pPhi[i1]+3*pPhi[i2]-5*pPhi[i3]));
          for(int i4 =0; i4<nTrk; i4++){
            if( fabs(pEta[i1] - pEta[i4])<etaGap_ || fabs(pEta[i2] - pEta[i4])<etaGap_ || fabs(pEta[i3] - pEta[i4])<etaGap_ ) continue;
            //hCorrelator4->Fill( cos(2*(pPhi[i1] + pPhi[i2] - pPhi[i3] - pPhi[i4])) );
                 evtCosPhi13->Fill(cos(2*(pPhi[i1]-pPhi[i3])));
                 evtCosPhi1234->Fill(cos(2*(pPhi[i1]+pPhi[i2]-pPhi[i3]-pPhi[i4])));
                 evtCosSC2323->Fill(cos(2*pPhi[i1]+3*pPhi[i2]-2*pPhi[i3]-3*pPhi[i4]));
                 evtCosSC3->Fill(cos(3*(pPhi[i1]-pPhi[i3])));
                 evtCosSC2424->Fill(cos(2*pPhi[i1]+4*pPhi[i2]-2*pPhi[i3]-4*pPhi[i4]));
                 evtCosSC4->Fill(cos(4*(pPhi[i1]-pPhi[i3])));

          }
        }
      }

    }
    //cout<<"nTrk = "<<nTrk<<"  "<<correlator2<<"  "<<correlator4<<endl;
    for(int i=0; i<nMultBin; i++){
      if(nTrk>=multMin[i] && nTrk<=multMax[i]){
        if(evtCosPhi13->GetEntries()>0){
          hCorrelator2[i]->Fill(evtCosPhi13->GetMean(), evtCosPhi13->GetEntries());
          hCorrelator4[i]->Fill(evtCosPhi1234->GetMean(), evtCosPhi1234->GetEntries());
          hCorrelatorSC2323[i]->Fill(evtCosSC2323->GetMean(), evtCosSC2323->GetEntries());
          hCorrelatorSC3[i]->Fill(evtCosSC3->GetMean(), evtCosSC3->GetEntries());
          hCorrelatorSC2424[i]->Fill(evtCosSC2424->GetMean(), evtCosSC2424->GetEntries());
          hCorrelatorSC4[i]->Fill(evtCosSC4->GetMean(), evtCosSC4->GetEntries());
        }
        if(evtCosAC224->GetEntries()>0){
          hCorrelatorAC224[i]->Fill(evtCosAC224->GetMean(), evtCosAC224->GetEntries());
          hCorrelatorAC235[i]->Fill(evtCosAC235->GetMean(), evtCosAC235->GetEntries());
        }

      }
    }


    corr_evtEntries = evtCosPhi1234->GetEntries();
    corr_evtCosPhi13 = evtCosPhi13->GetMean();
    corr_evtCosPhi1234 = evtCosPhi1234->GetMean();
    corr_evtCosSC2323 = evtCosSC2323->GetMean();
    corr_evtCosSC3 = evtCosSC3->GetMean();
    corr_evtCosSC2424 = evtCosSC2424->GetMean();
    corr_evtCosSC4 = evtCosSC4->GetMean();
    corr_evtEntries3 = evtCosAC224->GetEntries();
    corr_evtCosAC224 = evtCosAC224->GetMean();
    corr_evtCosAC235 = evtCosAC235->GetMean();

    if(corr_evtEntries>0 || corr_evtEntries3>0){
      anaTree->Fill();
    }

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
CumulantAnalysis::beginJob()
{
   anaTree = fs->make<TTree>("anaTree","event tree");
   anaTree->Branch("nTrk",&nTrk,"nTrk/I");
   anaTree->Branch("corr_evtEntries",&corr_evtEntries,"corr_evtEntries/F");
   anaTree->Branch("corr_evtCosPhi13",&corr_evtCosPhi13,"corr_evtCosPhi13/F");
   anaTree->Branch("corr_evtCosPhi1234",&corr_evtCosPhi1234,"corr_evtCosPhi1234/F");
   anaTree->Branch("corr_evtCosSC2323",&corr_evtCosSC2323,"corr_evtCosSC2323/F");
   anaTree->Branch("corr_evtCosSC3",&corr_evtCosSC3,"corr_evtCosSC3/F");
   anaTree->Branch("corr_evtCosSC2424",&corr_evtCosSC2424,"corr_evtCosSC2424/F");
   anaTree->Branch("corr_evtCosSC4",&corr_evtCosSC4,"corr_evtCosSC4/F");
   anaTree->Branch("corr_evtEntries3",&corr_evtEntries3,"corr_evtEntries3/F");
   anaTree->Branch("corr_evtCosAC224",&corr_evtCosAC224,"corr_evtCosAC224/F");
   anaTree->Branch("corr_evtCosAC235",&corr_evtCosAC235,"corr_evtCosAC235/F");

   //anaTree->Branch("pt",&ptV,"pt[nTrk]/F");  
   //anaTree->Branch("eta",&etaV,"eta[nTrk]/F");  
   //anaTree->Branch("phi",&phiV,"phi[nTrk]/F");  
   for(int i=0; i<nMultBin; i++){
     hCorrelator2[i] = fs->make<TH1D>(Form("hCorrelator2_%d", i),"",110,-1.1,1.1);
     hCorrelator4[i] = fs->make<TH1D>(Form("hCorrelator4_%d", i),"",110,-1.1,1.1);
     hCorrelatorSC2323[i] = fs->make<TH1D>(Form("hCorrelatorSC2323_%d", i),"",110,-1.1,1.1);
     hCorrelatorSC3[i] = fs->make<TH1D>(Form("hCorrelatorSC3_%d", i),"",110,-1.1,1.1);
     hCorrelatorSC2424[i] = fs->make<TH1D>(Form("hCorrelatorSC2424_%d", i),"",110,-1.1,1.1);
     hCorrelatorSC4[i] = fs->make<TH1D>(Form("hCorrelatorSC4_%d", i),"",110,-1.1,1.1);
     hCorrelatorAC224[i] = fs->make<TH1D>(Form("hCorrelatorAC224_%d", i),"",110,-1.1,1.1);
     hCorrelatorAC235[i] = fs->make<TH1D>(Form("hCorrelatorAC235_%d", i),"",110,-1.1,1.1);
   }
   evtCosPhi13 = fs->make<TH1D>("evtCosPhi13", "evtCosPhi13", 22,-1.1,1.1);
   evtCosPhi1234 = fs->make<TH1D>("evtCosPhi1234", "evtCosPhi1234", 22,-1.1,1.1);
   evtCosSC2323 = fs->make<TH1D>("evtCosSC2323", "evtCosSC2323", 22,-1.1,1.1);
   evtCosSC3 = fs->make<TH1D>("evtCosSC3", "evtCosSC3", 22,-1.1,1.1);
   evtCosSC2424 = fs->make<TH1D>("evtCosSC2424", "evtCosSC2424", 22,-1.1,1.1);
   evtCosSC4 = fs->make<TH1D>("evtCosSC4", "evtCosSC4", 22,-1.1,1.1);
   evtCosAC224 = fs->make<TH1D>("evtCosAC224", "evtCosAC224", 22,-1.1,1.1);
   evtCosAC235 = fs->make<TH1D>("evtCosAC235", "evtCosAC235", 22,-1.1,1.1);

}

// ------------ method called once each job just after ending the event loop  ------------
void
CumulantAnalysis::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CumulantAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CumulantAnalysis);
