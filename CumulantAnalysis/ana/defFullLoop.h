
     long nEvt;

     Int_t nParticle;
     Float_t phi[1000];
     Float_t pt[1000];
     Float_t eta[1000];

     const int nMultBin = 16;
     int multMin[nMultBin] = { 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 61, 71, 81,  91, 101, 121};
     int multMax[nMultBin] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150};

     Int_t nTrk;
     Float_t corr_evtEntries;
     Float_t corr_evtCosPhi1;
     Float_t corr_evtSinPhi1;
     Float_t corr_evtCosPhi12;
     Float_t corr_evtCosPhi13;
     Float_t corr_evtSinPhi12;
     Float_t corr_evtSinPhi13;
     Float_t corr_evtCosPhi123;
     Float_t corr_evtCosPhi134;
     Float_t corr_evtSinPhi123;
     Float_t corr_evtSinPhi134;
     Float_t corr_evtCosPhi1234;


     TH1D *allnTrkhist[nMultBin];
     TH1D *allCos1Cos234[nMultBin];
     TH1D *allCos2Cos134[nMultBin];
     TH1D *allCos3Cos124[nMultBin];
     TH1D *allCos4Cos123[nMultBin];
     TH1D *allSin1Sin234[nMultBin];
     TH1D *allSin2Sin134[nMultBin];
     TH1D *allSin3Sin124[nMultBin];
     TH1D *allSin4Sin123[nMultBin];
     TH1D *allCos12Cos34[nMultBin];
     TH1D *allCos13Cos24[nMultBin];
     TH1D *allCos14Cos23[nMultBin];
     TH1D *allSin12Sin34[nMultBin];
     TH1D *allSin13Sin24[nMultBin];
     TH1D *allSin14Sin23[nMultBin];
     TH1D *allCos1Cos2Cos34[nMultBin];
     TH1D *allCos1Sin2Sin34[nMultBin];
     TH1D *allSin1Cos2Sin34[nMultBin];
     TH1D *allSin1Sin2Cos34[nMultBin];
     TH1D *allCos1Cos3Cos24[nMultBin];
     TH1D *allCos1Sin3Sin24[nMultBin];
     TH1D *allSin1Cos3Sin24[nMultBin];
     TH1D *allSin1Sin3Cos24[nMultBin];
     TH1D *allCos1Cos4Cos23[nMultBin];
     TH1D *allCos1Sin4Sin23[nMultBin];
     TH1D *allSin1Cos4Sin23[nMultBin];
     TH1D *allSin1Sin4Cos23[nMultBin];
     TH1D *allCos2Cos3Cos14[nMultBin];
     TH1D *allCos2Sin3Sin14[nMultBin];
     TH1D *allSin2Cos3Sin14[nMultBin];
     TH1D *allSin2Sin3Cos14[nMultBin];
     TH1D *allCos2Cos4Cos13[nMultBin];
     TH1D *allCos2Sin4Sin13[nMultBin];
     TH1D *allSin2Cos4Sin13[nMultBin];
     TH1D *allSin2Sin4Cos13[nMultBin];
     TH1D *allCos3Cos4Cos12[nMultBin];
     TH1D *allCos3Sin4Sin12[nMultBin];
     TH1D *allSin3Cos4Sin12[nMultBin];
     TH1D *allSin3Sin4Cos12[nMultBin];
     TH1D *allCos1Cos2Cos3Cos4[nMultBin];
     TH1D *allCos1Cos2Sin3Sin4[nMultBin];
     TH1D *allCos1Sin2Cos3Sin4[nMultBin];
     TH1D *allCos1Sin2Sin3Cos4[nMultBin];
     TH1D *allSin1Cos2Cos3Sin4[nMultBin];
     TH1D *allSin1Cos2Sin3Cos4[nMultBin];
     TH1D *allSin1Sin2Cos3Cos4[nMultBin];
     TH1D *allSin1Sin2Sin3Sin4[nMultBin];
     TH1D *allCos1234[nMultBin];

     //2p
     TH1D *allCos1Cos3[nMultBin];
     TH1D *allSin1Sin3[nMultBin];
     TH1D *allCos13[nMultBin];

     TH1D *allc24[nMultBin];
     TH1D *allc24_pre[nMultBin];
     TH1D *allv24[nMultBin];
     TH1D *allv24_pre[nMultBin];

     TH1D *allCos1[nMultBin];
     TH1D *allCos134[nMultBin];
     TH1D *allSin1[nMultBin];
     TH1D *allSin134[nMultBin];
     TH1D *allCos12[nMultBin];
     TH1D *allSin12[nMultBin];

     double finalTerm01[nMultBin]; 
     double finalTerm02[nMultBin];
     double finalTerm03[nMultBin]; 
     double finalTerm04[nMultBin]; 
     double finalAll[nMultBin];

     TH1D* hCorrelator2[nMultBin];
     TH1D* hCorrelator4[nMultBin];
     TH1D* hCorrelatorSC2323[nMultBin];
     TH1D* hCorrelatorSC3[nMultBin];
     TH1D* hCorrelatorSC2424[nMultBin];
     TH1D* hCorrelatorSC4[nMultBin];
     TH1D* hCorrelatorAC224[nMultBin];
     TH1D* hCorrelatorAC235[nMultBin];


