//Calculate the signal to background ratios in the signal bin for each mass point and background sources
//Must be run on LPC in order to access files

/*
Background files:
/eos/uscms/store/user/fojensen/cmsdas_12052021/DYJetsToEEMuMu_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/DYJetsToTauTau_2018.root

/eos/uscms/store/user/fojensen/cmsdas_12052021/ST_tW_antitop_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/ST_tW_top_2018.root

/eos/uscms/store/user/fojensen/cmsdas_12052021/TTTo2L2Nu_bVeto_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/TTToSemiLeptonic_bVeto_2018.root

/eos/uscms/store/user/fojensen/cmsdas_12052021/WW_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/WZ_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/ZZ_2018.root

Signal Files:
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m1000_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m1250_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m1500_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m1750_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m175_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m2000_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m2500_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m250_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m3000_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m3500_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m375_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m4000_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m4500_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m5000_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m500_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m625_2018.root
/eos/uscms/store/user/fojensen/cmsdas_12052021/Taustar_m750_2018.root
*/


void makeGraphs()
{
  int numFiles = 9;
  int maxWidth = 98; //Percentage - Make sure to adjust the length of the bkgd array below as well
  int numMasses = 10;
  int masses[10] = {250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000};

  TFile* files[numFiles];
  //Drell-Yan to 2 leptons
  files[0] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/DYJetsToEEMuMu_2018.root");
  files[1] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/DYJetsToTauTau_2018.root");
  //Single top:  top + W channel
  files[2] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/ST_tW_antitop_2018.root");
  files[3] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/ST_tW_top_2018.root");
  //t-tbar with b veto
  files[4] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/TTTo2L2Nu_bVeto_2018.root");
  files[5] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/TTToSemiLeptonic_bVeto_2018.root");
  //WW, ZZ, WZ
  files[6] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/WW_2018.root");
  files[7] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/WZ_2018.root");
  files[8] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_12052021/ZZ_2018.root");
  
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

	  //tree->Scan("ElTau_ECollMass",baseCuts);

	  tree->Draw("ElTau_ECollMass-"+massStr+">>+elHist", elCuts);
	  tree->Draw("ElTau_TauCollMass-"+massStr+">>+tauHist", tauCuts);
	  combHist->Add(elHist, tauHist);
	  
	  //std::cout << "elHist: " << elHist->GetEntries() << endl;		
	  //std::cout << "tauHist: " << tauHist->GetEntries() << endl;
		  
	  for (int k = 0; k < maxWidth; k++)
	    {
	      float halfWidth = fracHalfWidths[k] * masses[i];
	      int lowBin = combHist->FindBin(mass - halfWidth);
	      int highBin = combHist->FindBin(mass + halfWidth);
	      bkdgCounts[k] += combHist->Integral(lowBin, highBin);
//	      std::cout << "(halfWidth, integral): (" << halfWidth << ", " << bkdgCounts[k] << ")" << endl; 	
	    }
	  
	  delete(tree);
	  delete(combHist);
	  delete(elHist);
	  delete(tauHist);
	}

      TGraph* graph = new TGraph(maxWidth, fracHalfWidths, bkdgCounts);
      graph->Draw("AL");
      graph->SetTitle("Background Events as Function of Signal Bin Width;Signal Bin Fractional Half Width[GeV];Num Bkgd Events");
      /*if (i == 10)
	graph->SetLineColor(46);
      else
	graph->SetLineColor(i+1);
      canv->Update();
      canv->SaveAs("graph"+massStr+".png");*/
      graphs->Add(graph, "AL");
      leg->AddEntry(graph, massStr, "L");
    }
  graphs->Draw("A PLC");
  graphs->SetTitle("Background Events in Signal Bin;Signal Bin Fractional Half Width[GeV];Num Bkgd Events");
  leg->SetHeader("#tau* Mass Hypothesis");
  leg->Draw("same");
  canv->Update();
  canv->SaveAs("~/nobackup/TauStar/Plots/bkgdWidthCurves.png");
   
}
