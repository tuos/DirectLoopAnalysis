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

TH2D *histcorr2corr4All = new TH2D("histcorr2corr4All", "histcorr2corr4All", 200,-1,1, 200,-1,1);

double err_vn2(double cn2, double err_cn2){
  return (1.0/2 * pow(cn2, -1.0/2) * err_cn2);
}
// Need GetCorrelationFactor() or GetCovariance() 
double err_cn4(double cn2, double err_corr2, double err_corr4){
  //double err_sqr = err_corr4*err_corr4 + (4*cn2)*(4*cn2)*err_corr2*err_corr2 - 8*cn2*(err_corr2*err_corr4*0.6); //pho=0.6
  double err_sqr = err_corr4*err_corr4 + (4*cn2)*(4*cn2)*err_corr2*err_corr2 - 8*cn2*(err_corr2*err_corr4*0.6 * 0.0); //assume no corr
  //double err_sqr = err_corr4*err_corr4 + (4*cn2)*(4*cn2)*err_corr2*err_corr2 - 8*cn2*histcorr2corr4All->GetCovariance(); 
  //cout<<"\n err_sqr:"<<err_sqr<<" get cov: "<<histcorr2corr4All->GetCovariance()<<"  get factor: "<<histcorr2corr4All->GetCorrelationFactor()<<endl;
  if (err_sqr>0) { return pow(err_sqr, 1.0/2); }
  else return 0.0;
}
double err_vn4(double cn4, double err_cn4){
  if(cn4<0) { return (1.0/4 * pow(-cn4, -3.0/4) *err_cn4); }
  else return 0.0;
}

void cumulantAnalysis(){

     long nEvt, nEvtProcess; 

     Int_t nParticle, iParticle;
     Float_t phi[20000];
     Float_t pt[20000];
     Float_t eta[20000];

     TH1D *histPhiAll = new TH1D("histPhiAll", "histPhiAll", 160,-1,7);
     TH1D *histPhi2All = new TH1D("histPhi2All", "histPhi2All", 160,-1,7);
     TH1D *histPhi3All = new TH1D("histPhi3All", "histPhi3All", 160,-1,7);
     TH1D *histPhi4All = new TH1D("histPhi4All", "histPhi4All", 160,-1,7);

     TH1D *histcorr2Evt = new TH1D("histcorr2Evt", "histcorr2Evt", 200,-1,1);
     TH1D *histcorr4Evt = new TH1D("histcorr4Evt", "histcorr4Evt", 200,-1,1);
     TH1D *histcos1Evt = new TH1D("histcos1Evt", "histcos1Evt", 200,-1,1);
     TH1D *histsin1Evt = new TH1D("histsin1Evt", "histsin1Evt", 200,-1,1);
     TH1D *histcos2Evt = new TH1D("histcos2Evt", "histcos2Evt", 200,-1,1);
     TH1D *histsin2Evt = new TH1D("histsin2Evt", "histsin2Evt", 200,-1,1);
     TH1D *histcos3Evt = new TH1D("histcos3Evt", "histcos3Evt", 200,-1,1);
     TH1D *histsin3Evt = new TH1D("histsin3Evt", "histsin3Evt", 200,-1,1);


     TH1D *histcorr2All = new TH1D("histcorr2All", "histcorr2All", 200,-1,1);
     TH1D *histcorr4All = new TH1D("histcorr4All", "histcorr4All", 200,-1,1);
     TH1D *histcos1All = new TH1D("histcos1All", "histcos1All", 200,-1,1);
     TH1D *histsin1All = new TH1D("histsin1All", "histsin1All", 200,-1,1);
     TH1D *histcos2All = new TH1D("histcos2All", "histcos2All", 200,-1,1);
     TH1D *histsin2All = new TH1D("histsin2All", "histsin2All", 200,-1,1);
     TH1D *histcos3All = new TH1D("histcos3All", "histcos3All", 200,-1,1);
     TH1D *histsin3All = new TH1D("histsin3All", "histsin3All", 200,-1,1);

     //TH2D *histcorr2corr4All = new TH2D("histcorr2corr4All", "histcorr2corr4All", 200,-1,1, 200,-1,1);

     double gapsize = 0.2; // the max gap is 1.6 with the default mehtod.
     TChain t1("t1");
     t1.Add("/hd0/ShengquanTuo/analysis/cumulants/toy/data/steg_m100_prod.root/tree");
     t1.SetBranchAddress("n", &nParticle);
     t1.SetBranchAddress("ptg", &pt);
     t1.SetBranchAddress("etag", &eta);
     t1.SetBranchAddress("phig", &phi);

     nEvt=t1.GetEntries();
     //nEvtProcess=2000;
     //for(long ne=0; ne<nEvt; ne++)
     //for(long ne=1800; ne<2000; ne++)
     //for(long ne=200; ne<300; ne++)
     //for(long ne=100; ne<200; ne++)
     for(long ne=0; ne<100; ne++)
     {
       if(ne%1==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1.GetEntry(ne);


       histcorr2Evt->Reset();
       histcorr4Evt->Reset();
       histcos1Evt->Reset();
       histsin1Evt->Reset();
       histcos2Evt->Reset();
       histsin2Evt->Reset();
       histcos3Evt->Reset();
       histsin3Evt->Reset();

       histPhi4All->Reset();


        for(iParticle=0; iParticle<nParticle; iParticle++){

           histcos1Evt->Fill( cos(2*phi[iParticle]) );
           histsin1Evt->Fill( sin(2*phi[iParticle]) );
           histPhiAll->Fill(phi[iParticle]);

           for(int j =0; j<nParticle; j++){

             if( fabs(eta[iParticle] - eta[j])<gapsize ) continue;
             histcorr2Evt->Fill( cos(2*(phi[iParticle] - phi[j])) );
             histcos2Evt->Fill( cos(2*(phi[iParticle] + phi[j])) );
             histsin2Evt->Fill( sin(2*(phi[iParticle] + phi[j])) );
             histPhi2All->Fill(phi[j]);
             histcorr2All->Fill( cos(2*(phi[iParticle] - phi[j])) );

             for(int k =0; k<nParticle; k++){

               if( fabs(eta[iParticle] - eta[k])<gapsize || fabs(eta[j] - eta[k])<gapsize ) continue;
               histcos3Evt->Fill( cos(2*(phi[iParticle] - phi[j] - phi[k])) );
               histsin3Evt->Fill( sin(2*(phi[iParticle] - phi[j] - phi[k])) );
               histPhi3All->Fill(phi[k]);

               for(int t =0; t<nParticle; t++){
                 if( fabs(eta[iParticle] - eta[t])<gapsize || fabs(eta[j] - eta[t])<gapsize || fabs(eta[k] - eta[t])<gapsize ) continue;
                 histcorr4Evt->Fill( cos(2*(phi[iParticle] + phi[j] - phi[k] - phi[t])) );
                 histPhi4All->Fill(phi[t]);
                 histcorr4All->Fill( cos(2*(phi[iParticle] + phi[j] - phi[k] - phi[t])) );

                 //cout<<"particle eta: "<<eta[iParticle]<<"  "<<eta[j]<<"  "<<eta[k]<<"  "<<eta[t]<<endl;

               }
             }
           } 

        }
        //histcorr2All->Fill(histcorr2Evt->GetMean());
        //histcorr4All->Fill(histcorr4Evt->GetMean());
        histcos1All->Fill(histcos1Evt->GetMean());
        histsin1All->Fill(histsin1Evt->GetMean());
        histcos2All->Fill(histcos2Evt->GetMean());
        histsin2All->Fill(histsin2Evt->GetMean());
        histcos3All->Fill(histcos3Evt->GetMean());
        histsin3All->Fill(histsin3Evt->GetMean());

        histcorr2corr4All->Fill( histcorr2Evt->GetMean(), histcorr4Evt->GetMean() );

      }


double c22corrected = histcorr2All->GetMean() - (histcos1All->GetMean()*histcos1All->GetMean() + histsin1All->GetMean()*histsin1All->GetMean());

double c24corrected = histcorr4All->GetMean() - 2*histcorr2All->GetMean()*histcorr2All->GetMean() - 4*histcos1All->GetMean()*histcos3All->GetMean() + 4*histsin1All->GetMean()*histsin3All->GetMean() - histcos2All->GetMean()*histcos2All->GetMean() - histsin2All->GetMean()*histsin2All->GetMean() + 4*histcos2All->GetMean()*(histcos1All->GetMean()*histcos1All->GetMean() - histsin1All->GetMean()*histsin1All->GetMean()) + 8*histsin2All->GetMean()*histsin1All->GetMean()*histcos1All->GetMean() + 8*histcorr2All->GetMean()*(histcos1All->GetMean()*histcos1All->GetMean()+histsin1All->GetMean()*histsin1All->GetMean()) - 6*(histcos1All->GetMean()*histcos1All->GetMean()+histsin1All->GetMean()*histsin1All->GetMean())*(histcos1All->GetMean()*histcos1All->GetMean()+histsin1All->GetMean()*histsin1All->GetMean());


ofstream outf;
outf.open("text_output.txt");
outf<<nParticle<<" ; cumulants:   "<<histcorr2All->GetMean()<<"   "<<histcorr4All->GetMean()<<"     "<<histcorr4All->GetMean() - 2*histcorr2All->GetMean()*histcorr2All->GetMean()<<endl;
outf<<nParticle<<" ; v22= "<<sqrt(histcorr2All->GetMean())<<" ; v24= "<<pow(-1*histcorr4All->GetMean() + 2*histcorr2All->GetMean()*histcorr2All->GetMean(), 0.25)<<endl;
outf<<endl<<"===== corrected for non-uniform ====="<<endl;
outf<<nParticle<<" ; v22= "<<sqrt(c22corrected)<<" ; v24= "<<pow(-1*c24corrected, 0.25)<<endl;


cout<<nParticle<<" ; cumulants:   "<<histcorr2All->GetMean()<<"   "<<histcorr4All->GetMean()<<"     "<<histcorr4All->GetMean() - 2*histcorr2All->GetMean()*histcorr2All->GetMean()<<endl;
double c24_pre = histcorr4All->GetMean() - 2*histcorr2All->GetMean()*histcorr2All->GetMean();
cout<<nParticle<<"  v22= "<<sqrt(histcorr2All->GetMean())<<" +/- "<<err_vn2(histcorr2All->GetMean(), histcorr2All->GetMeanError())<<" ; v24= "<<pow(-1*histcorr4All->GetMean() + 2*histcorr2All->GetMean()*histcorr2All->GetMean(), 0.25)<<" +/- "<<err_vn4(c24_pre, err_cn4(histcorr2All->GetMean(), histcorr2All->GetMeanError(), histcorr4All->GetMeanError()))<<endl;
//cout<<"Entries for 2p:"<<histcorr2All->GetEntries()<<",  Entries for 4p:"<<histcorr4All->GetEntries()<<endl;

cout<<"===== out new ====="<<endl;
cout<<nParticle<<"  v22= "<<sqrt(c22corrected)<<endl;
cout<<nParticle<<"  v24= "<<pow(-1*c24corrected, 0.25)<<endl;
if(c24corrected>0) cout<<"c24corrected = "<<c24corrected<<"  v24 = "<<pow(1*c24corrected, 0.25)<<endl;


  TFile *outFile = new TFile("out_dist_cumulant.root","recreate");
  //outFile->cd();

  histcorr2All->Write();
  histcorr4All->Write();
  histcos1All->Write();
  histsin1All->Write();
  histcos2All->Write();
  histsin2All->Write();
  histcos3All->Write();
  histsin3All->Write();

  histPhiAll->Write();
  histPhi2All->Write();
  histPhi3All->Write();
  histPhi4All->Write();

  histcorr2corr4All->Write();

  outFile->Write();
  outFile->Close();

}



