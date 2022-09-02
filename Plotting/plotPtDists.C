//Plotting functions to plot pT distributions in signal MC and MC backgrounds

TCut loadCuts(const TString channel, const int year, TCut cuts4[4], TCut cuts8[8], const bool applyTrigger=true, const int mass=0);
void getBkgdTrees(TTree **treesArr, TString labels[], TString year);
void plotSigMC(TString mass, TString year);
void plotBkgdMC(TString year);
TString getPath(TString whatPath);
void plotAll();
TString makeMCWeight(const TString channel, const bool havePair=true, const bool haveTriplet=true);

const int N_BKGD_FILES = 14;


//Return a file system path corresponding to whatPath
TString getPath(TString whatPath)
{
  if (whatPath == "input")
    return "root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_09082022/";
  else if (whatPath == "output")
    return "../Plots/PhoPtDists/";
  else
    {
      cout << "WARNING: Path specifier is unrecognized" << endl;
      exit(1);
    }
}

//Make signal and background plots for all taustar mass hypothesis and years
void plotAll(bool doSig = true, bool doBkgd = true)
{
   const int NUM_MASSES = 17;
   const int NUM_YEARS = 4;
   TString masses[NUM_MASSES] = {"175", "250", "375", "500", "625", "750", "1000", "1250", "1500", "1750", "2000", "2500", "3000", "3500", "4000", "4500", "5000"};
   TString years[NUM_YEARS] = {"2015", "2016", "2017", "2018"};

   for (int y = 0; y < NUM_YEARS; y++)
   {
      if (doBkgd)
	plotBkgdMC(years[y]);
      if (doSig)
	{
	  for (int m = 0; m < NUM_MASSES; m++)
	    {
	      plotSigMC(masses[m], years[y]);
	    }
	}
   }
}


//Make a plot of the photon pT distribution in signal monty carlo
//@param mass : The taustar hypothesis mass of the sample
//@param year : The year to plot
//Assumes a filename of the format Taustar_m<mass>_<year>.root
void plotSigMC(TString mass, TString year)
{
   //Setup graphics
   TCanvas* sigCanv = new TCanvas("sigCanv", "MC Signal Plots", 1200, 600);
   gStyle->SetOptStat(0);

   //Get data
   TString dir = getPath("input");
   TString filename = "Taustar_m" + mass + "_" + year + ".root"; 
   TFile* file = TFile::Open(dir + filename, "READ");
   TTree* tree = (TTree*) file->Get("Events");

   //Setup histograms
   TH1F* h_pt = new TH1F("h_pt", "Signal Photons m#tau*=" + mass + "GeV;photon Pt [GeV];Events", 50, 0, 5000);
   TH1F* h_ptFrac = new TH1F("h_ptFrac", "Signal Photons m#tau*=" + mass + "GeV;photon Pt [GeV];Fraction of Total Events", 5, 0, 5000);
   
   //Cuts
   int intYear = atoi(year);
   TString channels[3] = {"ETau", "MuTau", "TauTau"};
   TCut cuts4[4]; //Dummy arrays to hold cuts for the four ABCD regions
   TCut cuts8[8]; //Sim as above
   TCut cuts[3];  //Actual cuts to be used, same order as channels
   cuts[0] = loadCuts("ETau", intYear, cuts4, cuts8);
   cuts[1] = loadCuts("MuTau", intYear, cuts4, cuts8);
   cuts[2] = loadCuts("TauTau", intYear, cuts4, cuts8);

   //Fill the histograms
   for (int i = 0; i < 3; i++)
   {
      TH1F* temp = new TH1F("temp"+channels[i], "", 50, 0, 5000);
      TH1F* tempFrac = new TH1F("tempFrac"+channels[i], "", 5, 0, 5000);

      tree->Draw("Photon_pt>>+temp"+channels[i], cuts[i]);
      tree->Draw("Photon_pt>>+tempFrac"+channels[i], cuts[i]);

      h_pt->Add(temp);
      h_ptFrac->Add(tempFrac);

      delete temp;
      delete tempFrac; 
   }

   //Scale fractional histogram so bin values are fraction of total events
   h_ptFrac->Scale(1.0 / h_ptFrac->GetEntries());

   //Make the plots
   sigCanv->Clear();
   sigCanv->Divide(2,1);
   
   sigCanv->cd(1);
   h_pt->Draw("HIST");

   sigCanv->cd(2);
   h_ptFrac->Draw("HIST");
   gPad->SetLogy();

   sigCanv->Update();
   sigCanv->SaveAs(getPath("output") + "photonPt_m" + mass + "_" + year + ".png");   
}


//Make a plot of the photon pT distribution of background monty carlo
//@param year : The year to plot
void plotBkgdMC(TString year)
{
   cout << "Plotting background MC photon pT" << endl;
   //Get data
   TTree* trees[N_BKGD_FILES];
   TString labels[N_BKGD_FILES];
   getBkgdTrees(trees, labels, year);

   //Graphics
   TCanvas* bkgdCanv = new TCanvas("bkgdCanv", "MC Background Plots", 1200, 800);
   gStyle->SetOptStat(0);
   gStyle->SetPalette(kDarkRainBow);

   //Cuts
   int intYear = atoi(year);
   TCut cuts4[4]; //Dummy arrays to hold cuts for the four ABCD regions
   TCut cuts8[8]; //Sim as above
   TCut elCuts = loadCuts("ETau", intYear, cuts4, cuts8);
   TCut muCuts = loadCuts("MuTau", intYear, cuts4, cuts8);
   TCut tauCuts = loadCuts("TauTau", intYear, cuts4, cuts8);
   TCut photonStitchCut_ZG = TCut("PhotonStitch_n>0");
   TCut photonStitchCut_DY = TCut("PhotonStitch_n==0");
   
   //MC Event weights
   TString weightStr_el = makeMCWeight("ETau");
   TString weightStr_mu = makeMCWeight("MuTau");
   TString weightStr_tau = makeMCWeight("TauTau");


   //Fill histogram stacks
   THStack* elStack = new THStack("elStack","Photon pT: e+#tau Channel;photon pT [GeV]; Events");
   THStack* muStack = new THStack("muStack","Photon pT: #mu+#tau Channel;photon pT [GeV]; Events");
   THStack* tauStack = new THStack("tauStack","Photon pT: #tau+#tau Channel;photon pT [GeV]; Events");
   int nPtBins = 6;
   float ptBins[7] = {0, 200, 400, 600, 800, 1000, 1200};
   for (int fileN = 0; fileN < N_BKGD_FILES; fileN++)
   {  
      cout << "\t..Filling hists from file " << fileN + 1 << "/" << N_BKGD_FILES << endl;
      
      TH1F* h_tempEl = new TH1F(labels[fileN]+"_el", labels[fileN], nPtBins, ptBins);
      TH1F* h_tempMu = new TH1F(labels[fileN]+"_mu", labels[fileN], nPtBins, ptBins);
      TH1F* h_tempTau = new TH1F(labels[fileN]+"_tau", labels[fileN], nPtBins, ptBins);

      if (labels[fileN] == "ZGToLLG")
	{
	  trees[fileN]->Draw("Photon_pt*" + weightStr_el + ">>+"+labels[fileN]+"_el", elCuts + photonStitchCut_ZG);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_mu + ">>+"+labels[fileN]+"_mu", muCuts + photonStitchCut_ZG);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_tau + ">>+"+labels[fileN]+"_tau", tauCuts + photonStitchCut_ZG);
	}
      else if (labels[fileN] == "DYJetsToLL" || labels[fileN] == "DYJetsToLL_M10-50")
	{
	  trees[fileN]->Draw("Photon_pt*" + weightStr_el + ">>+"+labels[fileN]+"_el", elCuts + photonStitchCut_DY);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_mu + ">>+"+labels[fileN]+"_mu", muCuts + photonStitchCut_DY);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_tau + ">>+"+labels[fileN]+"_tau", tauCuts + photonStitchCut_DY);
	}
      else
	{
	  trees[fileN]->Draw("Photon_pt*" + weightStr_el + ">>+"+labels[fileN]+"_el", elCuts);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_mu + ">>+"+labels[fileN]+"_mu", muCuts);
	  trees[fileN]->Draw("Photon_pt*" + weightStr_tau + ">>+"+labels[fileN]+"_tau", tauCuts);
	}
 
      elStack->Add((TH1F*) h_tempEl->Clone());
      muStack->Add((TH1F*) h_tempMu->Clone());
      tauStack->Add((TH1F*) h_tempTau->Clone());

      delete h_tempEl;
      delete h_tempMu;
      delete h_tempTau;
   }

   //Plot the stacks
   bkgdCanv->Clear();
   bkgdCanv->Divide(2, 2);

   bkgdCanv->cd(1);
   elStack->Draw("pfc");
   gPad->SetLogy();
   bkgdCanv->Modified();
   gPad->BuildLegend(0.7, 0.5, 0.9, 0.9);

   bkgdCanv->cd(2);
   muStack->Draw("pfc");
   gPad->SetLogy();
   bkgdCanv->Modified();
   gPad->BuildLegend(0.7, 0.5, 0.9, 0.9);

   bkgdCanv->cd(3);
   tauStack->Draw("pfc");
   gPad->SetLogy();
   bkgdCanv->Modified();
   gPad->BuildLegend(0.7, 0.5, 0.9, 0.9);

   bkgdCanv->Update();
   bkgdCanv->SaveAs(getPath("output") + "photonPt_bkgd_" + year + ".png");
}


//Get the trees and labels from all the background MC files
void getBkgdTrees(TTree **treesArr, TString labels[], TString year)
{
   TFile* files[N_BKGD_FILES];
   TTree* trees[N_BKGD_FILES];

   TString baseDir = getPath("input");
   
   files[0] = TFile::Open(baseDir + "WJetsToLNu_" + year + ".root");
   labels[0] = "WJetsToLNu"; 
   files[1] = TFile::Open(baseDir + "WW_" + year + ".root");
   labels[1] = "WW";
   files[2] = TFile::Open(baseDir + "WZ_" + year + ".root");
   labels[2] = "WZ";
   files[3] = TFile::Open(baseDir + "ZZ_" + year + ".root");
   labels[3] = "ZZ";
   files[4] = TFile::Open(baseDir + "DYJetsToLL_" + year + ".root");
   labels[4] = "DYJetsToLL";
   files[5] = TFile::Open(baseDir + "DYJetsToLLM10_" + year + ".root");
   labels[5] = "DYJetsToLL_M10-50";
   files[6] = TFile::Open(baseDir + "ST_tW_top_" + year + ".root");
   labels[6] = "ST_tW_top";
   files[7] = TFile::Open(baseDir + "ST_tW_antitop_" + year + ".root");
   labels[7] = "ST_tW_antitop";
   files[8] = TFile::Open(baseDir + "ST_t_channel_antitop_" + year + ".root");
   labels[8] = "ST_t_channel_antitop";
   files[9] = TFile::Open(baseDir + "ST_t_channel_top_" + year + ".root");
   labels[9] = "ST_t_channel_top";
   files[10] = TFile::Open(baseDir + "ST_s_channel_" + year + ".root");
   labels[10] = "ST_s_channel";
   files[11] = TFile::Open(baseDir + "TTTo2L2Nu_" + year + ".root");
   labels[11] = "TTTo2L2Nu";
   files[12] = TFile::Open(baseDir + "TTToSemiLeptonic_" + year + ".root");
   labels[12] = "TTToSemiLeptonic";
   files[13] = TFile::Open(baseDir + "ZGToLLG_" + year + ".root");
   labels[13] = "ZGToLLG";

   for (int i = 0; i < N_BKGD_FILES; i++)
   {
   treesArr[i] = (TTree*) files[i]->Get("Events");
   if (treesArr[i] == NULL) cout << "WARNING: Tree" << i << "is NULL" << endl;
   }  
}


//Cut definition function taken from Franks histProducerWrapper.C
TCut loadCuts(const TString channel, const int year, TCut cuts4[4], TCut cuts8[8], const bool applyTrigger=true, const int mass=0)
{
   std::cout << "loadCuts(): " << channel << std::endl;
   TCut baseline = "1>0"; 
   TCut regionA = "1>0";
   TCut regionB = "1>0";
   TCut regionC = "1>0";
   TCut regionD = "1>0";
   //TCut regionE = "1>0";
   //TCut regionF = "1>0";
   TCut cut_1p = "1>0";
   TCut cut_3p = "1>0";

   if (channel=="EE") {
      baseline = TCut("EE_HaveTriplet>0 && Photon_pt[EE_PhotonIdx]>=20.");
      baseline = baseline && TCut("(EE_Mass>=50. && EE_Mass<140.) || (EE_TripletMass>=50. && EE_TripletMass<140.)");
      if (year==2015||year==2016) baseline = baseline && TCut("Electron_pt[EE_E0Idx]>=29. && Electron_pt[EE_E1Idx]>=29.");
      if (year==2017)             baseline = baseline && TCut("Electron_pt[EE_E0Idx]>=34. && Electron_pt[EE_E1Idx]>=34.");
      if (year==2018)             baseline = baseline && TCut("Electron_pt[EE_E0Idx]>=34. && Electron_pt[EE_E1Idx]>=34.");
      if (applyTrigger) {
         if (year==2015||year==2016) baseline = baseline && TCut("HLT_Ele27_WPTight_Gsf||HLT_Photon175");
         if (year==2017)             baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Photon200");
         if (year==2018)             baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf||HLT_Photon200");
      }
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[EE_E0Idx] && Electron_mvaFall17V2Iso_WP90[EE_E1Idx]");
      baseline = baseline && TCut("Photon_mvaID_WP90[EE_PhotonIdx] && !Photon_pixelSeed[EE_PhotonIdx]");
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==2");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "EE_qq==-1";
      regionB = "EE_qq==-1";
      regionC = "EE_qq==+1";
      regionD = "EE_qq==+1";
   }
   if (channel=="MuMu") {
      baseline = TCut("MuMu_HaveTriplet>0 && Photon_pt[MuMu_PhotonIdx]>=20.");
      baseline = baseline && TCut("(MuMu_Mass>=50. && MuMu_Mass<140.) || (MuMu_TripletMass>=50. && MuMu_TripletMass<140.)");
      if (year==2015||year==2016) baseline = baseline && TCut("Muon_pt[MuMu_Mu0Idx]>=26. && Muon_pt[MuMu_Mu1Idx]>=26.");
      if (year==2017)             baseline = baseline && TCut("Muon_pt[MuMu_Mu0Idx]>=29. && Muon_pt[MuMu_Mu1Idx]>=29.");
      if (year==2018)             baseline = baseline && TCut("Muon_pt[MuMu_Mu0Idx]>=26. && Muon_pt[MuMu_Mu1Idx]>=26.");
      if (applyTrigger) {
         if (year==2015||year==2016) baseline = baseline && TCut("HLT_IsoMu24||HLT_IsoTkMu24");
         if (year==2017)             baseline = baseline && TCut("HLT_IsoMu27");
         if (year==2018)             baseline = baseline && TCut("HLT_IsoMu24");
      }
      baseline = baseline && TCut("Muon_pfIsoId[MuMu_Mu0Idx]>=4 && Muon_tightId[MuMu_Mu0Idx]");
      baseline = baseline && TCut("Muon_pfIsoId[MuMu_Mu1Idx]>=4 && Muon_tightId[MuMu_Mu1Idx]");
      baseline = baseline && TCut("Photon_mvaID_WP90[MuMu_PhotonIdx] && Photon_electronVeto[MuMu_PhotonIdx]");
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==2");
      regionA = "MuMu_qq==-1";
      regionB = "MuMu_qq==-1";
      regionC = "MuMu_qq==+1";
      regionD = "MuMu_qq==+1";
   }
   if (channel=="EMu") {
      baseline = TCut("EMu_HaveTriplet>0 && Photon_pt[EMu_PhotonIdx]>=20.");
      const TCut lowE = "Trigger_lowE && Muon_pt[EMu_MuIdx]>=25. && Electron_pt[EMu_EIdx]>=20.";
      const TCut lowMu = "Trigger_lowMu && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=25.";
      baseline = baseline && TCut(lowE||lowMu);
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[EMu_EIdx]");
      baseline = baseline && TCut("Photon_mvaID_WP90[EMu_PhotonIdx] && !Photon_pixelSeed[EMu_PhotonIdx]");
      baseline = baseline && TCut("Muon_pfIsoId[EMu_MuIdx]>=4 && Muon_tightId[EMu_MuIdx]");
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = TCut("EMu_qq==-1");
      regionB = TCut("EMu_qq==-1");
      regionC = TCut("EMu_qq==+1");
      regionD = TCut("EMu_qq==+1");
   }
   //if (channel=="ETau")      baseline = TCut("ETau_HaveTriplet>0 && Photon_pt[ETau_PhotonIdx]>=100.");
   //if (channel=="ETauLowPt") baseline = TCut("ETau_HaveTriplet>0 && Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<100.");
   if (channel=="ETau"||channel=="ETauLowPt") {
      baseline = TCut("ETau_HaveTriplet>0");
      /*char buffer[100];
      if (channel=="ETau") {
         sprintf(buffer, "ETau_HaveTriplet>0 && Photon_pt[ETau_PhotonIdx]>=%d.", mass);
      }
      if (channel=="ETauLowPt") {
         sprintf(buffer, "ETau_HaveTriplet>0 && Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<%d.", mass);
      }
      baseline = TCut(buffer);*/
      baseline = baseline && TCut("ETau_Mass>=100.");
      baseline = baseline && TCut("ZEE_HavePair==0 && ZMuMu_HavePair==0");
      baseline = baseline && TCut("JetETau_nBJetT==0");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ETau_EIdx]");
      if (year==2015||year==2016) {
         baseline = baseline && TCut("HLT_Ele27_WPTight_Gsf||HLT_Photon175");
         baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=29.");
      }
      if (year==2017) {
         baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Photon200");
         baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
      }
      if (year==2018) {
         baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf||HLT_Photon200");
         baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
      }
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0"); 
      baseline = baseline && TCut("Tau_decayMode[ETau_TauIdx]!=5 && Tau_decayMode[ETau_TauIdx]!=6 && Tau_decayMode[ETau_TauIdx]!=7");
      baseline = baseline && TCut("(32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]) && !Photon_pixelSeed[ETau_PhotonIdx]");
      regionA = "ETau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      //if (channel=="ETauLowPt") regionA = regionA && TCut("Photon_pt[ETau_PhotonIdx]<100.");
      regionB = "ETau_qq==-1 && (1&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      regionC = "ETau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      regionD = "ETau_qq==+1 && (1&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      if (channel=="ETau") {
         regionA = regionA && TCut("Photon_pt[ETau_PhotonIdx]>=100.");
         regionB = regionB && TCut("Photon_pt[ETau_PhotonIdx]>=100.");
         regionC = regionC && TCut("Photon_pt[ETau_PhotonIdx]>=75.");
         regionD = regionD && TCut("Photon_pt[ETau_PhotonIdx]>=75.");
      }
      if (channel=="ETauLowPt") {
        regionA = regionA && TCut("Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<75.");
        regionB = regionB && TCut("Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<75.");
        regionC = regionC && TCut("Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<75.");
        regionD = regionD && TCut("Photon_pt[ETau_PhotonIdx]>=20. && Photon_pt[ETau_PhotonIdx]<75.");
      }
      cut_1p = "ETau_nProng==1";
      cut_3p = "ETau_nProng==3";
   }
   //if (channel=="MuTau")      baseline = TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=100.");
   //if (channel=="MuTauLowPt") baseline = TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<100.");
   if (channel=="MuTau"||channel=="MuTauLowPt") {
      baseline = TCut("MuTau_HaveTriplet>0");
      /*char buffer[100];
      if (channel=="MuTau") {
         sprintf(buffer, "MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=%d.", mass);
       }
      if (channel=="MuTauLowPt") {
         sprintf(buffer, "MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<%d.", mass);
      }
      baseline = TCut(buffer);*/
      baseline = baseline && TCut("MuTau_Mass>=100.");
      baseline = baseline && TCut("ZEE_HavePair==0 && ZMuMu_HavePair==0");
      baseline = baseline && TCut("JetMuTau_nBJetT==0");
      baseline = baseline && TCut("Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year==2015||year==2016) {
         baseline = baseline && TCut("HLT_IsoMu24||HLT_IsoTkMu24");
         baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      }
      if (year==2017) {
         baseline = baseline && TCut("HLT_IsoMu27");
         baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      }
      if (year==2018) {
         baseline = baseline && TCut("HLT_IsoMu24");
         baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      }
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      baseline = baseline && TCut("Tau_decayMode[MuTau_TauIdx]!=5 && Tau_decayMode[MuTau_TauIdx]!=6 && Tau_decayMode[MuTau_TauIdx]!=7");
      regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      //if (channel=="MuTauLowPt") regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]<100.");
      regionB = "MuTau_qq==-1 && (1&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (1&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      if (channel=="MuTau") {
         regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
         regionB = regionB && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
         regionC = regionC && TCut("Photon_pt[MuTau_PhotonIdx]>=75.");
         regionD = regionD && TCut("Photon_pt[MuTau_PhotonIdx]>=75.");
      }
      if (channel=="MuTauLowPt") {
        regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<75.");
        regionB = regionB && TCut("Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<75.");
        regionC = regionC && TCut("Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<75.");
        regionD = regionD && TCut("Photon_pt[MuTau_PhotonIdx]>=20. && Photon_pt[MuTau_PhotonIdx]<75.");
      }
      cut_1p = "MuTau_nProng==1";
      cut_3p = "MuTau_nProng==3";
   }
   //if (channel=="TauTau")      baseline = TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=75.");
   //if (channel=="TauTauLowPt") baseline = TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<75.");
   if (channel=="TauTau"||channel=="TauTauLowPt") {
      baseline = TCut("TauTau_HaveTriplet>0");
      /*char buffer[100];
      if (channel=="TauTau") {
         sprintf(buffer, "TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=%d.", mass);
      }
      if (channel=="TauTauLowPt") {
         sprintf(buffer, "TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<%d.", mass);
      }
      baseline = TCut(buffer);*/
      baseline = baseline && TCut("TauTau_Mass>=100.");
      baseline = baseline && TCut("ZEE_HavePair==0 && ZMuMu_HavePair==0"); 
      baseline = baseline && TCut("Trigger_diTau");
      //if (year==2015) {
      //   baseline = baseline && TCut("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg");
      //} else if (year==2016) {
      //   baseline = baseline && TCut("HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg||HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg");
      //} else if (year==2017) {
      //   baseline = baseline && TCut("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg||HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg||HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg");
      //} else if (year==2018) {
      //   baseline = baseline && TCut("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg||HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg||HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg||HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg");
      //}
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau1Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90 && (TMath::Abs(Electron_eta+Electron_deltaEtaSC)>=1.566||TMath::Abs(Electron_eta+Electron_deltaEtaSC)<1.444))==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      baseline = baseline && TCut("Tau_decayMode[TauTau_Tau0Idx]!=5 && Tau_decayMode[TauTau_Tau0Idx]!=6 && Tau_decayMode[TauTau_Tau0Idx]!=7");
      baseline = baseline && TCut("Tau_decayMode[TauTau_Tau1Idx]!=5 && Tau_decayMode[TauTau_Tau1Idx]!=6 && Tau_decayMode[TauTau_Tau1Idx]!=7");
      const TCut tau0pass = "(16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau0fail = "(1&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau1pass = "(16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      const TCut tau1fail = "(1&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      regionA = TCut("TauTau_qq==-1") && (tau0pass&&tau1pass);
      //if (channel=="TauTauLowPt") regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]<75.");
      regionC = TCut("TauTau_qq==+1") && (tau0pass&&tau1pass);
      //regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      //regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      //regionB = TCut("TauTau_qq==-1") && (tau0fail&&tau1fail);
      //regionD = TCut("TauTau_qq==+1") && (tau0fail&&tau1fail);
      regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass)||(tau0fail&&tau1fail));
      regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass)||(tau0fail&&tau1fail));
      if (channel=="TauTau") {
         regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]>=75.");
         regionB = regionB && TCut("Photon_pt[TauTau_PhotonIdx]>=75.");
         regionC = regionC && TCut("Photon_pt[TauTau_PhotonIdx]>=60.");
         regionD = regionD && TCut("Photon_pt[TauTau_PhotonIdx]>=60.");
      }
      if (channel=="TauTauLowPt") {
        regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<60.");
        regionB = regionB && TCut("Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<60.");
        regionC = regionC && TCut("Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<60.");
        regionD = regionD && TCut("Photon_pt[TauTau_PhotonIdx]>=20. && Photon_pt[TauTau_PhotonIdx]<60.");
      }
      cut_1p = "(Tau_pt[TauTau_Tau0Idx]>=Tau_pt[TauTau_Tau1Idx] ? TauTau_Tau1nProng==1 : TauTau_Tau0nProng==1)";
      cut_3p = "(Tau_pt[TauTau_Tau0Idx]>=Tau_pt[TauTau_Tau1Idx] ? TauTau_Tau1nProng==3 : TauTau_Tau0nProng==3)";
      //baseline = baseline && TCut("JetTauTau_nBJetT==0");
   }

   //const TCut cut_Flag16   = "Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter";
   //const TCut cut_Flag1718 = "Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter";
   //if (year==2015 || year==2016) {
   //   baseline = baseline && cut_Flag16;
   //} else {
   //   baseline = baseline && cut_Flag1718;
   //}

   //if (extraCut!="1>0") {
   //std::cout << "Appending the cut: " << extraCut << std::endl;
   //baseline = baseline && TCut(extraCut);
   //}

   //cuts4
   cuts4[0] = baseline && regionA;
   cuts4[1] = baseline && regionB;
   cuts4[2] = baseline && regionC;
   cuts4[3] = baseline && regionD;
   //cuts8
   if (channel=="EE"||channel=="MuMu"||channel=="EMu") {
      cuts8[0]  = baseline && regionA;
      cuts8[1]  = baseline && regionA;
      cuts8[2]  = baseline && regionB;
      cuts8[3]  = baseline && regionB;
      cuts8[4]  = baseline && regionC;
      cuts8[5]  = baseline && regionC;
      cuts8[6]  = baseline && regionD;
      cuts8[7]  = baseline && regionD;
   } else {
      cuts8[0]  = baseline && regionA && cut_1p;
      cuts8[1]  = baseline && regionA && cut_3p;
      cuts8[2]  = baseline && regionB && cut_1p;
      cuts8[3]  = baseline && regionB && cut_3p;
      cuts8[4]  = baseline && regionC && cut_1p;
      cuts8[5]  = baseline && regionC && cut_3p;
      cuts8[6]  = baseline && regionD && cut_1p;
      cuts8[7]  = baseline && regionD && cut_3p;
   }
   return cuts4[0];
   //return cuts4[2];
}

//Function to return the event weight, taken from Frank's histProducerWrapper.c
TString makeMCWeight(const TString channel, const bool havePair=true, const bool haveTriplet=true)
//TString makeMCWeight(const TString channel, const bool doweights=true)
{
  //const bool havePair=true;
  //const bool haveTriplet=true;
  //std::cout << "makeMCWeight: " << channel << std::endl;

  TString weightTag = "lumiWeight[1] * xsWeight";
  //return weightTag;
  //if (isSignal) return weightTag;

  //weightTag += " * puWeightDown";
  weightTag += " * puWeight";
  //weightTag += " * puWeightUp";

  //weightTag += " * L1PreFiringWeight_ECAL_Dn";
  weightTag += " * L1PreFiringWeight_ECAL_Nom";
  //weightTag += " * L1PreFiringWeight_ECAL_Up";

  if (channel=="EMu" || channel=="MuMu" || channel=="MuTau" || channel=="MuTauLowPt") {
    //weightTag += " * L1PreFiringWeight_Muon_SystDn";
    weightTag += " * L1PreFiringWeight_Muon_Nom";
    //weightTag += " * L1PreFiringWeight_Muon_SystUp";
  }

  weightTag += " * (genWeight<0?-1.:+1.)";
  if (!havePair) return weightTag;

  if (channel=="EE") {
    //ereco
    weightTag += " * EE_SFE0_reco[1] * EE_SFE1_reco[1]";
    //eid
    weightTag += " * EE_SFE0_id[1] * EE_SFE1_id[1]";
    //eetrigger
    weightTag += " * EE_TriggerEff[1]";
    if (haveTriplet) {
      //photonid
      weightTag += " * EE_SFPhoton_id[1]";
      //pv
      weightTag += " * EE_SFPhoton_pv[1]";
    }
  }
  if (channel=="MuMu") {
    //mureco
    weightTag += " * MuMu_SFMu0_reco[1] * MuMu_SFMu1_reco[1]";
    //muid
    weightTag += " * MuMu_SFMu0_id[1] * MuMu_SFMu1_id[1]";
    //muiso
    weightTag += " * MuMu_SFMu0_iso[1] * MuMu_SFMu1_iso[1]";
    //mumutrigger
    weightTag += " * MuMu_TriggerEff[1]";
    if (haveTriplet) {
      //photonid
      weightTag += " * MuMu_SFPhoton_id[1]";
      //csev
      weightTag += " * MuMu_SFPhoton_csev[1]";
    }
  }
  if (channel=="EMu") {
    //ereco
    weightTag += " * EMu_SFE_reco[1]";
    //eid
    weightTag += " * EMu_SFE_id[1]";
    //mureco
    weightTag += " * EMu_SFMu_reco[1]";
    //muid
    weightTag += " * EMu_SFMu_id[1]";
    //muiso
    weightTag += " * EMu_SFMu_iso[1]";
    //emutrigger
    weightTag += " * EMu_SFEMu_trigger[1]";
    if (haveTriplet) {
      //photonid
      weightTag += " * EMu_SFPhoton_id[1]";
      //pv
      weightTag += " * EMu_SFPhoton_pv[1]";
    }
  }
  if (channel=="ETau"||channel=="ETauLowPt") {
    //antie
    weightTag += " * ETau_SFTau_e[1]";
    //antimu
    weightTag += " * ETau_SFTau_mu[1]";
    //antijet
    weightTag += " * ((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx] && Tau_pt[ETau_TauIdx]>=40.) ? ETau_SFTau_jetdm_tight[1] : 1.)";
    weightTag += " * ((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx] && Tau_pt[ETau_TauIdx]<40.)  ? ETau_SFTau_jetpt_tight[1] : 1.)";
    weightTag += " * ((!32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx] && Tau_pt[ETau_TauIdx]>=40.) ? ETau_SFTau_jetdm_vvvloose[1] : 1.)";
    weightTag += " * ((!32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx] && Tau_pt[ETau_TauIdx]<40.)  ? ETau_SFTau_jetpt_vvvloose[1] : 1.)";
    //ereco
    weightTag += " * ETau_SFE_reco[1]";
    //eid
    weightTag += " * ETau_SFE_id[1]";
    //etrigger
    weightTag += " * ETau_SFE_trigger[1]";
    //btaglight
    weightTag += " * JetETau_bTagWeight_light[1]";
    //btaglightcorr
    //weightTag += " * JetETau_bTagWeight_lightcorr[1]";
    //btagbc
    weightTag += " * JetETau_bTagWeight_bc[1]";
    //btagbccorr
    //weightTag += " * JetETau_bTagWeight_bccorr[1]";
    if (haveTriplet) {
      //photonid
      weightTag += " * ETau_SFPhoton_id[1]";
      //pv
      weightTag += " * ETau_SFPhoton_pv[1]";
    }
  }
  if (channel=="MuTau"||channel=="MuTauLowPt") {
    //antie
    weightTag += " * MuTau_SFTau_e[1]";
    //antimu
    weightTag += " * MuTau_SFTau_mu[1]";
    //antijet
    weightTag += " * ((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx] && Tau_pt[MuTau_TauIdx]>=40.) ? MuTau_SFTau_jetdm_tight[1] : 1.)";
    weightTag += " * ((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx] && Tau_pt[MuTau_TauIdx]<40.)  ? MuTau_SFTau_jetpt_tight[1] : 1.)";
    weightTag += " * ((!32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx] && Tau_pt[MuTau_TauIdx]>=40.) ? MuTau_SFTau_jetdm_vvvloose[1] : 1.)";
    weightTag += " * ((!32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx] && Tau_pt[MuTau_TauIdx]<40.)  ? MuTau_SFTau_jetpt_vvvloose[1] : 1.)";
    //mureco
    weightTag += " * MuTau_SFMu_reco[1]";
    //muid
    weightTag += " * MuTau_SFMu_id[1]";
    //muiso
    weightTag += " * MuTau_SFMu_iso[1]";
    //mutrigger
    weightTag += " * MuTau_SFMu_trigger[1]";
    //btaglight
    weightTag += " * JetMuTau_bTagWeight_light[1]";
    //btaglightcorr
    //weightTag += " * JetMuTau_bTagWeight_lightcorr[1]";
    //btagbc
    weightTag += " * JetMuTau_bTagWeight_bc[1]";
    //btagbccorr
    //weightTag += " * JetMuTau_bTagWeight_bccorr[1]";
    if (haveTriplet) {
      //photonid
      weightTag += " * MuTau_SFPhoton_id[1]";
      //csev
      weightTag += " * MuTau_SFPhoton_csev[1]";
    }
  }
  if (channel=="TauTau"||channel=="TauTauLowPt") {
    //antie
    weightTag += " * TauTau_SFTau0_e[1] * TauTau_SFTau1_e[1]";
    //antimu
    weightTag += " * TauTau_SFTau0_mu[1] * TauTau_SFTau1_mu[1]";
    //antijet
    weightTag += " * ((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) ? TauTau_SFTau0_jetdm_medium[1] : 1.)";
    weightTag += " * ((!16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) ? TauTau_SFTau0_jetdm_vvvloose[1] : 1.)";
    weightTag += " * ((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) ? TauTau_SFTau1_jetdm_medium[1] : 1.)";
    weightTag += " * ((!16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) ? TauTau_SFTau1_jetdm_vvvloose[1] : 1.)";
    //tautrigger
    weightTag += " * ((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) ? TauTau_SFTau0_trigger_medium[1] : 1.)";
    weightTag += " * ((!16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) ? TauTau_SFTau0_trigger_vvvloose[1] : 1.)";
    weightTag += " * ((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) ? TauTau_SFTau1_trigger_medium[1] : 1.)";
    weightTag += " * ((!16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) ? TauTau_SFTau1_trigger_vvvloose[1] : 1.)";
      if (haveTriplet) {
         //photonid
         weightTag += " * TauTau_SFPhoton_id[1]";
         //csev
         weightTag += " * TauTau_SFPhoton_csev[1]";
      }
   }
   return weightTag;
}
