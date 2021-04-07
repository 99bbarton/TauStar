//Produce L-plots and projection plots of combined collinear mass for Tau -> e + gamma

#include <TCut.h>
#include <TFile.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <iostream>


int extractData(TTree* tree, double minMasses[], double maxMasses[], int nEvents)
{
  float minCollMass = 0;
  float maxCollMass = 0;
  tree->SetBranchAddress("ElTau_MinCollMass", &minCollMass);
  tree->SetBranchAddress("ElTau_MaxCollMass", &maxCollMass);

  int j = 0;
  for (int i = 0; i < nEvents; i++)
    {
      tree->GetEntry(i);
      
      if (minCollMass > 0 && maxCollMass > 0)
	{
	  minMasses[j] = minCollMass;
	  maxMasses[j] = maxCollMass;
	  j++;
	}
    }

  return j;
}


void makeProfilePlots(const double min250[], const double max250[], int n250, const double min5000[], const double max5000[], int n5000)
{
  TCanvas *canv2 = new TCanvas("canv2", "Profiles Hists", 1200, 600);
  canv2->Divide(2, 2);

  TH1F *h_min250 = new TH1F("min250", "Min Coll Mass #tau* m=250 GeV/c^2", 30, 0, 600);
  TH1F *h_max250 = new TH1F("max250", "Max Coll Mass #tau* m=250 GeV/c^2", 150, 0, 3000);
  TH1F *h_min5000 = new TH1F("min5000", "Min Coll Mass #tau* m=5000 GeV/c^2", 110, 0, 5500);
  TH1F *h_max5000 = new TH1F("max5000", "Max Coll Mass #tau* m=5000 GeV/c^2", 150, 3500, 6500);

  h_min250->FillN(n250, min250, NULL);
  h_max250->FillN(n250, max250, NULL);
  h_min5000->FillN(n5000, min5000, NULL);
  h_max5000->FillN(n5000, max5000, NULL);

  h_min250->SetLineColor(2);
  h_max250->SetLineColor(2);
  h_min5000->SetLineColor(4);
  h_max5000->SetLineColor(4);

  h_min250->SetXTitle("Coll mass [20 GeV/c^2 per bin]");
  h_max250->SetXTitle("Coll mass [20 GeV/c^2 per bin]");
  h_min5000->SetXTitle("Coll mass [20 GeV/c^2 per bin]");
  h_max5000->SetXTitle("Coll mass [20 GeV/c^2 per bin]");
  
  canv2->cd(1);
  h_min250->Draw();
  canv2->cd(2);
  h_min5000->Draw();
  canv2->cd(3);
  h_max250->Draw();
  canv2->cd(4);
  h_max5000->Draw();
  canv2->Update();

  canv2->SaveAs("Plots/elTau_collMassProfiles_m250m5000.png");
  
}


void makePlots()
{
  
  //Extract data from ROOT files
  TFile* file_m250 = TFile::Open("../Data/m250.root");
  TFile* file_m5000 = TFile::Open("../Data/m5000.root");
  
  TTree* tree_m250 = (TTree*) file_m250->Get("Events");
  TTree* tree_m5000 = (TTree*) file_m5000->Get("Events");

  int nEvents_m250 = tree_m250->GetEntries();
  int nEvents_m5000 = tree_m5000->GetEntries();

  double minMasses_m250[nEvents_m250];
  double maxMasses_m250[nEvents_m250];
  double minMasses_m5000[nEvents_m250];
  double maxMasses_m5000[nEvents_m250];

  int nGood_m250 = extractData(tree_m250, minMasses_m250, maxMasses_m250, nEvents_m250);
  int nGood_m5000 = extractData(tree_m5000, minMasses_m5000, maxMasses_m5000, nEvents_m5000);
  
  TGraph* g_m250 = new TGraph(nGood_m250, minMasses_m250, maxMasses_m250);
  TGraph* g_m5000 = new TGraph(nGood_m5000, minMasses_m5000, maxMasses_m5000);
  TString axislabels = ";min collMass(#tau_{h}#gamma) [GeV/c^2];max mass(#tau_{h}#gamma) [GeV/c^2]";


  g_m250->SetTitle("#tau* mass = 250 [GeV/c^2]" + axislabels);
  g_m5000->SetTitle("#tau* mass = 250 [GeV/c^2]" + axislabels);
  g_m250->SetMarkerColor(2);
  g_m5000->SetMarkerColor(4);
  g_m250->SetMarkerStyle(7);
  g_m5000->SetMarkerStyle(7);
  g_m250->SetFillColor(2);
  g_m5000->SetFillColor(4);

  TCanvas *canv = new TCanvas("canv", "Collinear Mass L-Plots", 1200, 600);
  canv->Divide(2);
  canv->cd(1);
  g_m250->Draw("AP");
  g_m250->SetMinimum(0.);
  g_m250->SetMaximum(3000.);
  g_m250->GetXaxis()->SetRangeUser(0., 500.);
  g_m250->Draw("AP");
  canv->Update();

  canv->cd(2);
  g_m5000->Draw("AP");
  g_m5000->SetMinimum(3000.);
  g_m5000->SetMaximum(8000.);
  g_m5000->GetXaxis()->SetRangeUser(0., 6000.);
  g_m5000->Draw("AP");

  canv->Update();
  /*
  TLegend * l = new TLegend(0.6, 0.2, 0.85, 0.5);
  l->SetBorderSize(0);
  l->SetHeader("#tau* mass");
  l->AddEntry(g_m250, "250 GeV/c^2", "F");
  l->AddEntry(g_m5000, "5000 GeV/c^2", "F");
  l->Draw();
  */
  canv->SaveAs("Plots/elTau_collMassLPlots_m250m5000.png");

  
  makeProfilePlots(minMasses_m250, maxMasses_m250, nGood_m250, minMasses_m5000, maxMasses_m5000, nGood_m5000);

}







