#include "histProducerWrapper.c"
#include <TFile.h>
#include <TCut.h>
#include <TTree.h>
#include <iostream>
#include <TH1D.h>
#include <iomanip>

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
         cuts[3] = "(HLT_IsoMu24||HLT_IsoTkMu24) && Muon_pt[MuTau_MuIdx]>=26. && MuTau_MuHasTrigObj>0";
      } else if (year==2017) {
         cuts[3] = "HLT_IsoMu27 && Muon_pt[MuTau_MuIdx]>=29. && MuTau_MuHasTrigObj>0";
      } else if (year==2018) {
         cuts[3] = "HLT_IsoMu24 && Muon_pt[MuTau_MuIdx]>=26. && MuTau_MuHasTrigObj>0";
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
         cuts[3] = cuts[3] && TCut("Trigger_diTau2016");
      }
      if (year==2017) {
         cuts[3] = cuts[3] && TCut("Trigger_diTau2017");
      }
      if (year==2018) {
         cuts[3] = cuts[3] && TCut("Trigger_diTau2018");
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

void cutFlow_HEPData()
{
  cout << "\n\nProducing signal process cut flow..." << endl;

  const int nMasses = 17;
  TString masses[nMasses] = {"175", "250", "375", "500", "625", "750", "1000", "1250", "1500", "1750", "2000", "2500", "3000", "3500", "4000", "4500", "5000"};

  TString channels[3] = {"ETau", "MuTau", "TauTau"};

  const int nCuts = 10;
  double counts[nCuts], countsErr[nCuts];

  char infile[100];

  printf("year\tmass\tchannel\tnPassCut0, nErrPassCut0, ... nPassCutN, nErrPassCutN");

  for (int year = 2015; year <=2018; year++)
    {
      for (int massN = 0; massN < nMasses; massN++)
	{  
         
	  sprintf(infile, "root://cmseos.fnal.gov//store/user/bbarton/PDFWeights/ExcitedTau_20112022/Taustar_m%s_%d.root", masses[massN].Data(), year);
	  TFile *file = TFile::Open(infile);
	  TTree * tree = (TTree*) file->Get("Events");

	  for (int chN = 0; chN < 3; chN++)
	    {
	      printf("\n%d\t%s\t%s", year, masses[massN].Data(), channels[chN].Data());

	      for (int cutN = 0; cutN < nCuts; cutN++)
		{
		  char numCuts[5000];
		  TCut theCut = returnCuts(channels[chN], year, cutN, true);
		  TString theWeights;
		  if (cutN <= 1)                      theWeights = makeMCWeight(channels[chN], false, false, true);
		  else if (cutN >=2 && cutN <= 6)     theWeights = makeMCWeight(channels[chN], true, false, true);
		  else                                theWeights = makeMCWeight(channels[chN], true, true, true);
		  sprintf(numCuts, "(%s) * (%s)", theWeights.Data(), TString(theCut).Data());

		  TH1D hist("hist", "", 1, 0.5, 1.5);
		  double count, countErr;
		  tree->Project("+hist", "1.", numCuts);
		  count = hist.IntegralAndError(1, 1, countErr);

		  printf("\t%4.2lf\t%4.2lf", count, countErr);
		}
	    }
	  file->Close();
	}
    }

}