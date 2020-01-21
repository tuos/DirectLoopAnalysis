#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
using namespace std; 

#include "./defFullLoop.h"


void cumulantAnalysis(){

    TFile *infile = new TFile("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_gap08v4_OCT13TeV500M/MinBias/PYTHIA8_gap08v4_OCT13TeV500M/191029_161602/output_cumulantanalysis_pythia13tev_gap08merged.root");
    for(int i=0; i<nMultBin; i++){
      hCorrelator2[i] = (TH1D*)infile->Get(Form("demo/hCorrelator2_%d", i));
      hCorrelator4[i] = (TH1D*)infile->Get(Form("demo/hCorrelator4_%d", i));
      hCorrelatorSC2323[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorSC2323_%d", i));
      hCorrelatorSC3[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorSC3_%d", i));
      hCorrelatorSC2424[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorSC2424_%d", i));
      hCorrelatorSC4[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorSC4_%d", i));
      hCorrelatorAC224[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorAC224_%d", i));
      hCorrelatorAC235[i] = (TH1D*)infile->Get(Form("demo/hCorrelatorAC235_%d", i));
      cout<<i<<"   "<<hCorrelator2[i]->GetMean()<<" "<<hCorrelator2[i]->GetMeanError()<<"      "<<hCorrelator4[i]->GetMean()<<" "<<hCorrelator4[i]->GetMeanError()<<"      "<<hCorrelator4[i]->GetMean() - 2*hCorrelator2[i]->GetMean()*hCorrelator2[i]->GetMean()<<endl;
    }
cout<<endl<<"hCorrelatorSC2323"<<endl;
    for(int i=0; i<nMultBin; i++){
      cout<<i<<"   "<<hCorrelatorSC2323[i]->GetMean()<<" "<<hCorrelatorSC2323[i]->GetMeanError()<<"      "<<hCorrelatorSC3[i]->GetMean()<<" "<<hCorrelatorSC3[i]->GetMeanError()<<"      "<<hCorrelatorSC2323[i]->GetMean() - 1*hCorrelator2[i]->GetMean()*hCorrelatorSC3[i]->GetMean()<<endl;
    }
cout<<endl<<"hCorrelatorSC2424"<<endl;
    for(int i=0; i<nMultBin; i++){
      cout<<i<<"   "<<hCorrelatorSC2424[i]->GetMean()<<" "<<hCorrelatorSC2424[i]->GetMeanError()<<"      "<<hCorrelatorSC4[i]->GetMean()<<" "<<hCorrelatorSC4[i]->GetMeanError()<<"      "<<hCorrelatorSC2424[i]->GetMean() - 1*hCorrelator2[i]->GetMean()*hCorrelatorSC4[i]->GetMean()<<endl;
    }
cout<<endl<<"hCorrelatorAC224 and hCorrelatorAC235"<<endl;
    for(int i=0; i<nMultBin; i++){
      cout<<i<<"   "<<hCorrelatorAC224[i]->GetMean()<<" "<<hCorrelatorAC224[i]->GetMeanError()<<"      "<<hCorrelatorAC235[i]->GetMean()<<" "<<hCorrelatorAC235[i]->GetMeanError()<<endl;
    }


    infile->Close();

}


