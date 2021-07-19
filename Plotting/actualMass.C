//Macro to plot masses of and examine reconstructed taustars in ElGamma Channel



#include <TCut.h>
#include <TFile.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <iostream>

using namespace std;

TCut getCuts(bool forEl, bool useGenMatch);
void makePlots(TString path, TString mass, bool useGenMatch);
void plotMasses(TTree* tree, TString mass, bool useGenMatch);
void plotDRs(TTree *tree, TString mass);
void getCounts(TTree* tree);
void drPlot2D(TTree* tree, TString mass);

TCut getCuts(bool forEl, bool useGenMatch)
{
  //Define cuts
  //TCut baseCuts = "ElTau_Trigger&&ElTau_HaveTriplet";
  TCut baseCuts = "ElTau_HaveTriplet";
  TCut elDRMatch = "ElTau_DRGenMatch==1";
  TCut tauDRMatch = "ElTau_DRGenMatch==5";
  TCut elGenMatch = "ElTau_ElGenTauStar>0";
  TCut tauGenMatch = "ElTau_TauGenTauStar>0";

  TCut cuts = baseCuts;
  if (forEl)
    {
      if (useGenMatch)
	cuts = cuts + elGenMatch;
      else
	cuts = cuts + elDRMatch;
    }
  else
    {
      if (useGenMatch)
	cuts = cuts + tauGenMatch;
      else
	cuts = cuts + tauDRMatch;
    }

  return cuts;
}

void makePlots(TString path, TString mass, bool useGenMatch)
{
   //Extract data from ROOT files
  TFile* file = TFile::Open(path);
  
  TTree* tree = (TTree*) file->Get("Events");

  getCounts(tree);
  plotMasses(tree, mass, useGenMatch);
  //plotDRs(tree, mass);
  //drPlot2D(tree, mass);
}

void plotMasses(TTree* tree, TString mass, bool useGenMatch)
{
  //gStyle->SetOptStat(0);
  TCanvas *massCanv = new TCanvas("massCanv", "Mass Plots", 600, 600);

  //TCut elCuts = getCuts(true, useGenMatch);
  TCut elCuts = TCut("ElTau_HaveTriplet") + TCut("abs(ElTau_ElCollMass-"+mass+")<=abs(ElTau_TauCollMass-"+mass+")");
  //TCut tauCuts = getCuts(false, useGenMatch);
  TCut tauCuts = TCut("ElTau_HaveTriplet") + TCut("abs(ElTau_TauCollMass-"+mass+")<=abs(ElTau_ElCollMass-"+mass+")");
  
  TString title = "Mass of Reconstructed #tau*";
  /*if (useGenMatch)
    title += " : MC Gen Matching";
  else
    title += " : DR Gen Matching";
  */

  TH1F *massHist_el = new TH1F("massHist_el", title + ": m=" + mass , 101, -1000.5, 1000.5);
  massHist_el->SetXTitle("Reconstructed mass - nominal mass");
  massHist_el->SetLineColor(2);
  massHist_el->Sumw2();
  //massHist_el->SetFillColor(2);
  TH1F *massHist_tau = new TH1F("massHist_tau", title + ": m=" + mass, 101, -1000.5, 1000.5);
  massHist_tau->SetXTitle("Reconstructed mass - nominal mass");
  massHist_tau->SetLineColor(4);
  massHist_tau->Sumw2();
  //massHist_tau->SetFillColor(4);
 
  tree->Draw("ElTau_ElCollMass-"+ mass +">>+massHist_el", elCuts);
  tree->Draw("ElTau_TauCollMass-"+ mass +">>+massHist_tau", tauCuts);

  /*THStack* stack = new THStack("hists","Mass of Reconstructed #tau* : m="+mass);
  stack->Add(massHist_tau);
  stack->Add(massHist_el);
  stack->Draw();
  stack->GetXaxis()->SetTitle("Reconstructed mass - nominal mass [GeV]");
  */
  
  TH1F *massHist_sum  = new TH1F("massHist", title + ": m=" + mass, 101, -1000.5, 1000.5);
  massHist_sum->SetXTitle("Reconstructed mass - nominal mass [GeV]");
  massHist_sum->Add(massHist_el);
  massHist_sum->Add(massHist_tau);
  massHist_sum->SetLineColor(1);
  
  massHist_sum->Draw("hist");
  massHist_sum->Fit("gaus", "", "same");
     
  //massHist_el->Draw("hist same");
  //massHist_tau->Draw("hist same");
			      /*
  TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->AddEntry(massHist_el, "El coll mass", "F");
  legend->AddEntry(massHist_tau, "Tau coll mass", "F");
  legend->AddEntry(massHist_sum, "Collinear mass", "F");
  legend->Draw();*/
  massCanv->Update();

  if (useGenMatch)
    massCanv->SaveAs("Plots/recoMass_genMatch_m"+mass+".png");
  else
    massCanv->SaveAs("Plots/recoMass_drMatch_m"+mass+".png");
    
}

void plotDRs(TTree *tree, TString mass)
{
  TCanvas *drCanv = new TCanvas("drCanv", "DR Plots", 800, 500);
  drCanv->Divide(2,2);
  
  TCut elCuts = getCuts(true, false);
  TCut tauCuts = getCuts(false, false);

  TH1F *drHist_el = new TH1F("drHist_el", "#DeltaR of Matched Reco Particles: m="+mass, 125, 0, 2.5);
  drHist_el->SetXTitle("#DeltaR");
  drHist_el->SetLineColor(2);
  TH1F *drHist_tau = new TH1F("drHist_tau","#DeltaR of Matched Reco Particles: m="+mass, 125, 0, 2.5);
  drHist_tau->SetXTitle("#DeltaR");
  drHist_tau->SetLineColor(4);
 
  tree->Draw("ElTau_ElGammaTauStarDR>>+drHist_el", elCuts);
  tree->Draw("ElTau_TauGammaTauStarDR>>+drHist_tau", tauCuts);

  //THStack* stack = new THStack("drHists","");
  //stack->Add(drHist_el);
  //stack->Add(drHist_tau);

  
  drCanv->cd(1);
  //drCanv->SetLogy(true);
  //stack->Draw();
  drHist_tau->Draw("hist");
  drCanv->cd(2);
  //drCanv->SetLogy(true);
  drHist_el->Draw("hist same");

  TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->AddEntry(drHist_el, "#DeltaR matched el+#gamma", "L");
  legend->AddEntry(drHist_tau, "#DeltaR matched #tau+#gamma", "L");
  legend->Draw();
  // drCanv->Update();

  drCanv->SaveAs("Plots/deltaRs_m"+mass+".png");
}


void drPlot2D(TTree* tree, TString mass)
{
  TCanvas *drCanv2D = new TCanvas("drCanv2D", "DR 2D Plot", 800, 500);
  
  TCut baseCuts = "ElTau_HaveTriplet";
  TCut elCuts = getCuts(true, true);
  TCut elMatches = baseCuts + "ElTau_ElGenTauStar";

  // TMultiGraph *mg = new TMultiGraph();

  drCanv2D->cd();
  TGraph *graph_match;
  tree->Draw("ElTau_TauGammaTauStarDR:ElTau_ElGammaTauStarDR", baseCuts);
  graph_match = (TGraph*) gPad->GetPrimitive("Graph");
  graph_match->SetTitle("#DeltaR;#DeltaR(Reco El, #tau*);#DeltaR(Reco #tau_h, #tau*)");
  graph_match->SetMarkerColor(4);
  graph_match->SetMarkerStyle(8);
  graph_match->SetMarkerSize(0.5);
  //mg->Add(graph_match);
  /*
  TGraph *graph_misMatch;
  tree->Draw("ElTau_ElGammaTauStarDR:ElTau_TauGammaTauStarDR", elCuts, "same");
  graph_misMatch = (TGraph*) gPad->GetPrimitive("Graph");
  graph_misMatch->SetTitle("#DeltaR o;#DeltaR(Reco El, #tau*);#DeltaR(Reco #tau_h, #tau*)");
  graph_misMatch->SetMarkerColor(4);
  graph_misMatch->SetMarkerStyle(8);
  graph_misMatch->SetMarkerSize(0.5);
  mg->Add(graph_misMatch);

  
  drCanv2D->cd();
  mg->SetTitle("#DeltaR;#DeltaR(Reco El, #tau*);#DeltaR(Reco #tau_h, #tau*)");
  mg->Draw("PA");*/
  graph_match->Draw("P");
  //graph_misMatch->Draw("same P");
  drCanv2D->Update();
  drCanv2D->SaveAs("Plots/drPlot2D_m" + mass + ".png");
  
  //TGraph *graph_base;
  //tree->Draw("ElTau_ElTauStarDR:ElTau_TauTauStarDR", baseCuts);
  //graph_base = (TGraph*) gPad->GetPrimitive("Graph");
}

void getCounts(TTree* tree)
{
  TCut elCutsMC = getCuts(true, true);
  TCut elCutsDR = getCuts(true, false);
  TCut tauCutsMC = getCuts(false, true);
  TCut tauCutsDR = getCuts(false, false);

  cout << "Using MC Gen Matching:" << endl;
  cout << "Electrons matching to gen tau stars (before cuts): " << tree->GetEntries("ElTau_ElGenTauStar>0") << endl;
  cout << "Electrons matching to gen tau stars (after cuts): " << tree->GetEntries(elCutsMC) << endl;
  cout << "Taus matching to gen tau stars (before cuts): " << tree->GetEntries("ElTau_TauGenTauStar>0") << endl;
  cout << "Taus matching to gen tau stars (after cuts): " << tree->GetEntries(tauCutsMC) << endl;
  
  cout << "\nUsing DR Gen Matching:" << endl;
  cout << "Electrons matching to gen tau stars: " << tree->GetEntries(elCutsDR) << endl;
  cout << "Taus matching to gen tau stars: " << tree->GetEntries(tauCutsDR) << endl;

  cout << "\nMismatches:" << endl;
  cout << "DR incorrectly matched electrons to tau*s: " << tree->GetEntries(elCutsDR+"ElTau_TauGenTauStar>0") << endl;
  cout << "DR incorrectly matched taus to tau*s: " << tree->GetEntries(tauCutsDR+"ElTau_ElGenTauStar>0") << endl;
  cout << "Reco'd particles didn't match to tau*: " << tree->GetEntries("ElTau_TauGenTauStar<=0 && ElTau_ElGenTauStar<=0")<< "\n" << endl;
}
