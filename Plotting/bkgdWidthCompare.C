//Calculate the signal to background ratios in the signal bin for each mass point and background sources
//Must be run on LPC in order to access files


void makeGraphs()
{
  int numFiles = 11;
  int maxWidth = 98; //Percentage - Make sure to adjust the length of the bkgd array below as well
  int numMasses = 10;
  int masses[10] = {250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000};

  TFile* files[numFiles];
  //Drell-Yan to 2 leptons
  files[0] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/DYJetsToLL_2018.root");
  files[1] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/DYJetsToLLM10_2018.root");
  //Single top:  top + W channel
  files[2] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/ST_tW_antitop_2018.root");
  files[3] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/ST_tW_top_2018.root");
  //t-tbar
  files[4] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/TTTo2L2Nu_2018.root");
  files[5] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/TTToSemiLeptonic_2018.root");
  //WW, ZZ, WZ
  files[6] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/WW_2018.root");
  files[7] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/WZ_2018.root");
  files[8] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/ZZ_2018.root");
  //ST t-channel
  files[9] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/ST_t_channel_antitop_2018.root");
  files[10] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/ST_t_channel_top_2018.root");

  float lumi2018 = 59830;
  TString lumiStr = TString(std::to_string(lumi2018));
  float fracHalfWidths[maxWidth];
  for (int w = 0; w < maxWidth; w++)
    fracHalfWidths[w] = ((w+1.0) / 100.0) / 2.0;
  
  TCanvas *canv = new TCanvas("canv", "Background Events", 600, 600);
  TLegend *leg = new TLegend(0.2, 0.6, 0.4, 0.8);
  TMultiGraph *graphs = new TMultiGraph();
  gStyle->SetPalette(kRainBow);
  TCut baseCuts = TCut("ElTau_HaveTriplet");

  for (int i = 0; i < numMasses; i++)
    {
      int mass = masses[i];
      std::cout << "Processing Backgrounds for tau* mass = " << mass << endl;
      float bkdgCounts[98] = {0}; //Needs to be the same as maxWidth
      TString massStr = TString(std::to_string(mass));
      TCut elCuts = baseCuts + TCut("abs(ElTau_ECollMass-"+ massStr +")<=abs(ElTau_TauCollMass-" + massStr + ")");
      TCut tauCuts = baseCuts + TCut("abs(ElTau_TauCollMass-"+ massStr +")<=abs(ElTau_ECollMass-" + massStr + ")");
    
      for (int j = 0; j < numFiles; j++)
	{
	  TTree* tree  = (TTree*) files[j]->Get("Events");
	  TH1F* elHist = new TH1F("elHist", "El+#gamma Coll Mass, #tau* mass=" + massStr, 301, -2000, 1000);
	  TH1F* tauHist = new TH1F("tauHist", "#tau+#gamma Coll Mass, #tau* mass=" + massStr,301, -2000, 1000);
	  TH1F* combHist = new TH1F("combHist", "Coll Mass, #tau* mass="+massStr, 301,-2000, 1000);

	  tree->Draw("(ElTau_ECollMass-"+massStr+")*xsWeight*"+lumiStr+">>+elHist", elCuts);
	  tree->Draw("(ElTau_TauCollMass-"+massStr+")*xsWeight*"+lumiStr+">>+tauHist", tauCuts);
	  combHist->Add(elHist, tauHist);
			  
	  for (int k = 0; k < maxWidth; k++)
	    {
	      float halfWidth = fracHalfWidths[k] * masses[i];
	      int lowBin = combHist->FindBin(mass - halfWidth);
	      int highBin = combHist->FindBin(mass + halfWidth);
	      bkdgCounts[k] += combHist->Integral(lowBin, highBin); 	
	    }
	  
	  delete(tree);
	  delete(combHist);
	  delete(elHist);
	  delete(tauHist);
	}
	
     
      TGraph* graph = new TGraph(maxWidth, fracHalfWidths, bkdgCounts);
      graph->Draw("AL");
      graph->SetTitle("Background Events as Function of Signal Bin Width;Signal Bin Fractional Half Width[GeV];Num Bkgd Events");
      graphs->Add(graph, "AL");
      leg->AddEntry(graph, massStr, "L");
    }
  graphs->Draw("A PLC");
  graphs->SetTitle("Background Events in Signal Bin;Signal Bin Fractional Half Width;Num Bkgd Events");
  leg->SetHeader("#tau* Mass Hypothesis");
  leg->Draw("same");
  canv->Update();
  canv->SaveAs("~/nobackup/TauStar/Plots/bkgdWidthCurves.png");
   

}
