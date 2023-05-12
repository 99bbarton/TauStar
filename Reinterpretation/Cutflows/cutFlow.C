#include "histProducerWrapper.c"
#include <TFile.h>
#include <TCut.h>
#include <TTree.h>
#include <iostream>
#include <TH1D.h>
#include <iomanip>


//Return cuts used for the specified channel and year. idx is used to specify how many cuts to include (inclusive to all lower indices).
//Modified from https://github.com/fojensen/nanoAOD-tools/blob/TauTauGamma/analysis/cutflow.c
TCut returnCuts(const TString channel, const int year, const int idx, const bool isSig=false)
{
   const int ncuts = 10;
   TCut cuts[ncuts];
   if (channel=="ETau") {
      cuts[0] = "1>0";
      cuts[1] = "nE==1 && nMu==0";
      cuts[2] = "ETau_HavePair>0 && ETau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && Tau_decayMode[ETau_TauIdx]!=5 && Tau_decayMode[ETau_TauIdx]!=6 && Tau_decayMode[ETau_TauIdx]!=7 && Electron_mvaFall17V2Iso_WP90[ETau_EIdx] && (32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx])";
      if (year==2015||year==2016) {
         const TCut patha = "HLT_Ele27_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0)";
         const TCut pathb = "HLT_Photon175 && (ETau_EHasTrigObj>=10)";
         const TCut triggerpath = patha||pathb;
         cuts[3] = triggerpath && TCut("Electron_pt[ETau_EIdx]>=29.");
      } else if (year==2017) {
         const TCut patha = "HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0)";
         const TCut pathb = "HLT_Photon200 && (ETau_EHasTrigObj>=10)";
         const TCut triggerpath = patha||pathb;
         cuts[3] = triggerpath && TCut("Electron_pt[ETau_EIdx]>=34.");
      } else if (year==2018) {
         const TCut patha = "HLT_Ele32_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0)";
         const TCut pathb = "HLT_Photon200 && (ETau_EHasTrigObj>=10)";
         const TCut triggerpath = patha||pathb;
         cuts[3] = triggerpath && TCut("Electron_pt[ETau_EIdx]>=34.");
      }
      cuts[4] = "ETau_Mass>=100.";
      cuts[5] = "ZEE_HavePair==0 && ZMuMu_HavePair==0";
      cuts[6] = "Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_ETau==1 && JetMask_bT==1)==0";
      cuts[7] = "ETau_HaveTriplet>0 && !Photon_pixelSeed[ETau_PhotonIdx] && Photon_pt[ETau_PhotonIdx]>=20.";
      cuts[8] = "Photon_pt[ETau_PhotonIdx]>=100.";
      cuts[9] = "Tau_genPartFlav[ETau_TauIdx]==5||Tau_genPartFlav[ETau_TauIdx]==1||Tau_genPartFlav[ETau_TauIdx]==2||Tau_genPartFlav[ETau_TauIdx]==3||Tau_genPartFlav[ETau_TauIdx]==4";
   }
   if (channel=="MuTau") {
      cuts[0] = "1>0";
      cuts[1] = "nE==0 && nMu==1";
      cuts[2] = "MuTau_HavePair && MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4 && Tau_decayMode[MuTau_TauIdx]!=5 && Tau_decayMode[MuTau_TauIdx]!=6 && Tau_decayMode[MuTau_TauIdx]!=7";
      if (year==2015||year==2016) {
         cuts[3] = "(MuTau_t2016_0[1] || MuTau_t2016_1[1]) && Muon_pt[MuTau_MuIdx]>=26.";
      } else if (year==2017) {
         cuts[3] = "MuTau_t2017[1] && Muon_pt[MuTau_MuIdx]>=29";
      } else if (year==2018) {
         cuts[3] = "MuTau_t2018[1] && Muon_pt[MuTau_MuIdx]>=26.";
      } 
      cuts[4] = "MuTau_Mass>=100.";
      cuts[5] = "ZEE_HavePair==0 && ZMuMu_HavePair==0";
      cuts[6] = "Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_MuTau==1 && JetMask_bT==1)==0";
      cuts[7] = "MuTau_HaveTriplet>0 && Photon_electronVeto[MuTau_PhotonIdx] && Photon_pt[MuTau_PhotonIdx]>=20."; 
      cuts[8] = "Photon_pt[MuTau_PhotonIdx]>=100.";
      cuts[9] = "Tau_genPartFlav[MuTau_TauIdx]==5||Tau_genPartFlav[MuTau_TauIdx]==1||Tau_genPartFlav[MuTau_TauIdx]==2||Tau_genPartFlav[MuTau_TauIdx]==3||Tau_genPartFlav[MuTau_TauIdx]==4";
   }
   if (channel=="TauTau") {
      cuts[0] = "1>0";
      cuts[1] = "nE==0 && nMu==0";
      cuts[2] = "TauTau_HavePair>0 && TauTau_qq==-1 && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && Tau_decayMode[TauTau_Tau0Idx]!=5 && Tau_decayMode[TauTau_Tau0Idx]!=6 && Tau_decayMode[TauTau_Tau0Idx]!=7 && Tau_decayMode[TauTau_Tau1Idx]!=5 && Tau_decayMode[TauTau_Tau1Idx]!=6 && Tau_decayMode[TauTau_Tau1Idx]!=7"; 
      cuts[3] = "Tau_pt[TauTau_Tau0Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1 && Tau_pt[TauTau_Tau1Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1";
      if (year==2015||year==2016) {
         cuts[3] = cuts[3] && TCut("TauTau_t2016_0[0] || TauTau_t2016_1[0]");
      }
      if (year==2017) {
         cuts[3] = cuts[3] && TCut("TauTau_t2017_0[0] || TauTau_t2017_1[0] || TauTau_t2017_2[0]");
      }
      if (year==2018) {
         cuts[3] = cuts[3] && TCut("TauTau_t2018_0[0] || TauTau_t2018_1[0] || TauTau_t2018_2[0] || TauTau_t2018_3[0]");
      }
      cuts[4] = "TauTau_Mass>=100.";
      cuts[5] = "ZEE_HavePair==0 && ZMuMu_HavePair==0";
      cuts[6] = "Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_TauTau==1 && JetMask_bT==1)>-1";
      cuts[7] = "TauTau_HaveTriplet>0 && Photon_electronVeto[TauTau_PhotonIdx] && Photon_pt[TauTau_PhotonIdx]>=20.";
      cuts[8] = "Photon_pt[TauTau_PhotonIdx]>=75.";
      cuts[9] = "(Tau_genPartFlav[TauTau_Tau0Idx]==5||Tau_genPartFlav[TauTau_Tau0Idx]==1||Tau_genPartFlav[TauTau_Tau0Idx]==2||Tau_genPartFlav[TauTau_Tau0Idx]==3||Tau_genPartFlav[TauTau_Tau0Idx]==4)&&(Tau_genPartFlav[TauTau_Tau1Idx]==5||Tau_genPartFlav[TauTau_Tau1Idx]==1||Tau_genPartFlav[TauTau_Tau1Idx]==2||Tau_genPartFlav[TauTau_Tau1Idx]==3||Tau_genPartFlav[TauTau_Tau1Idx]==4)";
   }

   if (isSig) {
      const TCut cut_Flag16   = "Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter";
      const TCut cut_Flag1718 = "Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter";
      if (year==2015 || year==2016) {
         cuts[0] = cut_Flag16;
      } else {
         cuts[0] = cut_Flag1718;
      }
   }

   TCut theCut = cuts[0];
   for (int i = 1; i <= idx; ++i) theCut = theCut && cuts[i];
   //std::cout << theCut << std::endl;
   return theCut;
}

/*
   Output the necessary signal cutflow information needed to build the cutflow table for HEPData submission
   Writes the full cutflow of each signal mass, for each year, and for each of the three signal channels to stdout
   NB: The correct path to the latest signal samples must be specified in the sprintf line below
   Based off code in https://github.com/fojensen/nanoAOD-tools/blob/TauTauGamma/analysis/cutflow.c
*/
void cutFlow_HEPData()
{
   cout << "\n\nProducing signal process cut flow..." << endl;

   const int nMasses = 17;
   TString masses[nMasses] = {"175", "250", "375", "500", "625", "750", "1000", "1250", "1500", "1750", "2000", "2500", "3000", "3500", "4000", "4500", "5000"};

   TString channels[3] = {"ETau", "MuTau", "TauTau"};

   const int nCuts = 9;
   double counts[nCuts], countsErr[nCuts];

   char infile[100];

   //Write a header line. This line is used as the column labels by pandas when read in by makeSubmission.py
   printf("year,mass,channel,numLeps,numLepsErr,havePair,havePairErr,trigger,triggerErr,m_vis,m_visErr,Zveto,ZvetoErr,bVeto,bVetoErr,gamma20GeV,gamma20GeVErr,gamma100GeV,gamma100GeVErr,tauGenMatch,tauGenMatchErr");

   //Write out cutflow information for each year, tau* mass, and channel
   for (int year = 2015; year <=2018; year++)
      {
      for (int massN = 0; massN < nMasses; massN++)
      {  
         //TODO Ensure this line is up to date with the latest signal MC processing
         sprintf(infile, "root://cmseos.fnal.gov//store/user/bbarton/PDFWeights/ExcitedTau_29032023/Taustar_m%s_%d.root", masses[massN].Data(), year);
         TFile *file = TFile::Open(infile);
         TTree * tree = (TTree*) file->Get("Events");

         for (int chN = 0; chN < 3; chN++)
            {
               printf("\n%d,%s,%s", year, masses[massN].Data(), channels[chN].Data());

               for (int cutN = 0; cutN < nCuts; cutN++)
               {
                  char numCuts[5000];
                  TCut theCut = returnCuts(channels[chN], year, cutN, true);
                  TString theWeights;
                  if (cutN <= 1)                      theWeights = makeMCWeight(channels[chN], false, false, true); //makeMCWeight defined in histProducerWrapper.C
                  else if (cutN >=2 && cutN <= 6)     theWeights = makeMCWeight(channels[chN], true, false, true);
                  else                                theWeights = makeMCWeight(channels[chN], true, true, true);
                  sprintf(numCuts, "(%s) * (%s)", theWeights.Data(), TString(theCut).Data());

                  TH1D hist("hist", "", 1, 0.5, 1.5);
                  double count, countErr;
                  tree->Project("+hist", "1.", numCuts);
                  count = hist.IntegralAndError(1, 1, countErr);

                  printf(",%4.2lf,%4.2lf", count, countErr);
               }
            }
         file->Close();
      }
      }

}
