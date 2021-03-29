//Produce L-plots and projection plots of combined collinear mass for Tau -> e + gamma
//Based on fojenson/nanoAOD-tools/analysis/makeDataPlot.c and tpwelton/ExcitedTau/PlotsCOde/SignalMass.c

#include <TCut.h>
#include <TFile.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <iostream>


int extractData()
{
  
  //Extract data from ROOT files
  TFile* file_m250 = TFile::Open("../Data/Taustar_m250.root");
  TFile* file_m5000 = TFile::Open("../Data/Taustar_m5000.root");
  
  TTree* tree_m250_raw = file_m250->Get("Events");
  TTree* tree_m5000_raw = file_m5000->Get("Events");

  //Make and apply tau -> e + gamma selection cuts /////////////////////////////////// WHAT CUTS? /////////////////
  //Tau Cuts
  TCut tauCuts = "true";
  
  //Electron Cuts
  TCut eleCuts = "true";

  //Gamma Cuts
  TCut gammaCuts = "true";
  
  //Overall
  TCut allCuts = tauCuts && eleCuts && gammaCuts;

  TTree* tree_m250_cut = (TTree*) tree_m250_raw->CopyTree(allCuts);
  TTree* tree_m5000_cut = (TTree*) tree_m5000_raw->CopyTree(allCuts);
  

  //Calc collinear mass
  int nEvents_m250 = tree_m250_cut->GetEntries();
  double minCollMass_m250[nEvents_m250];
  double maxCollMass_m250[nEvents_m250];
  calcCollinearMass(tree_m250_cut, minCollMass_m250, maxCollMass_m250);
  int nEvents_m5000 = tree_m250_cut->GetEntries();
  double minCollMass_m5000[nEvents_m5000];
  double maxCollMass_m5000[nEvents_m5000];
  calcCollinearMass(tree_m5000_cut, minCollMass_m5000, maxCollMass_m5000);


  //Fill the graphs and set graphing params
  
  TGraph* g_m250 = new TGraph(nEvents_m250, minCollMass_m250, maxCollMass_m250);
  TGraph* g_m5000 = new TGraph(nEvents_m5000, minCollMass_5000, maxCollMass_5000);
  TString axislabels = ";min mass(#tau_{h}, #gamma) [GeV/c^2];max mass(#tau_{h}, #gamma) [GeV/c^2]");
  g_m250->SetTitle(axislabels);
  g_m5000->SetTitle(axislabels);
  g_m250->SetMarkerColor(2);
  g_m5000->SetMarkerColor(4);
  g_m250->SetMarkerStyle(7);
  g_m5000->SetMarkerStyle(7);
  g_m250->SetFillColor(2);
  g_m5000->SetFillColor(4);

  TCanvas *canv = new TCanvas("canv", "Collinear Mass L-Plots", 800, 800);
  g_m250->Draw("AP");
  g_m250->SetMinimum(0.);
  g_m250->SetMaximum(2000.);
  g_m250->GetXaxis()->SetRangeUser(0., 2000.);
  g_m250->Draw("AP");
  canv->Update();

  g_m5000->Draw("P, SAME");

  TLegend * l = new TLegend(0.6, 0.2, 0.85, 0.5);
  l->SetBorderSize(0);
  l->SetHeader("#tau* mass");
  l->AddEntry(g_m250, "250 GeV/c^2", "F");
  l->AddEntry(g_m5000, "5000 GeV/c^2", "F");
  l->Draw();
  
  
  
}


//TODO ////////////////////////////////////////////////
void calcCollinearMass(TTree *cutTree, double minCollMass[], double maxCollMass[]);
{

}








