//Look at signal selection for W->e+nu events


#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>


using namespace std;

const int NUM_FILES = 12;

void plot_mT(TFile* files[], TString labels[]);
void plot_cosDeltaPhi(TFile* files[], TString labels[]);
void plot_MET_Et(TFile* files[], TString labels[]);


void makePlots()
{
  TFile* files[NUM_FILES];
  TString labels[NUM_FILES]; 

  //WJets to L + nu
  files[0] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/WJetsToLNu.root");
  labels[0] = "WJetsToLNu";
  //Drell-Yan to 2 leptons
  files[1] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/DYJetsToLL.root");
  labels[1] = "DYJetsToLL";
  files[2] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/DYJetsToLLM10.root");
  labels[2] = "DYJetsToLLM10";
  //Single top:  top + W channel
  files[3] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/ST_tW_antitop.root");
  labels[3] = "ST_tW_antitop";
  files[4] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/ST_tW_top.root");
  labels[4] = "ST_tW_top";
  //t-tbar
  files[5] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/TTTo2L2Nu.root");
  labels[5] = "TTto2L2Nu";
  files[6] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/TTToSemiLeptonic.root");
  labels[6] = "TTtoSemiLep";
  //WW, ZZ, WZ
  files[7] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/WW.root");
  labels[7] = "WW";
  files[8] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/WZ.root");
  labels[8] = "WZ";
  files[9] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/ZZ.root");
  labels[9] = "ZZ";
  //ST t-channel
  files[10] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/ST_t_channel_antitop.root");
  labels[10] = "ST_tChannel_antitop";
  files[11] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/ST_t_channel_top.root");
  labels[11] = "ST_tChannel_top";
    

  plot_mT(files, labels);
  plot_cosDeltaPhi(files, labels);
  plot_MET_Et(files, labels);
}


void plot_mT(TFile* files[], TString labels[])
{
  TCanvas *canv_mT_all = new TCanvas("canv_mT_all", "All mT Plots", 1200, 1200);
  canv_mT_all->Divide(4,3);
  TCanvas *canv_mT = new TCanvas("canv_mT", "mT Plot", 600, 600);

  
  for (int i = 0; i < NUM_FILES; i++)
    {
      TH1F* h_mT = (TH1F*) files[i]->Get("plots/h_mt");
      h_mT->SetXTitle("mT [GeV]");
      h_mT->SetTitle(labels[i]);

      gStyle->SetOptStat(0);
      canv_mT_all->cd(i+1);
      h_mT->Draw("hist");
      gStyle->SetOptStat(1);
      canv_mT->cd();
      h_mT->Draw("hist");
      canv_mT->SaveAs("../Plots/TrigEffSigSel/MT/"+labels[i]+".png");
    }

  canv_mT_all->SaveAs("../Plots/TrigEffSigSel/MT/all.png");
}


void plot_cosDeltaPhi(TFile* files[], TString labels[])
{
  TCanvas *canv_cosDPhi_all = new TCanvas("canv_cosDPhi_all", "All cos(#Delta#phi) Plots", 1200, 1200);
  canv_cosDPhi_all->Divide(4,3);
  TCanvas *canv_cosDPhi = new TCanvas("canv_cosDPhi", "cos(#Delta#phi) Plot", 600, 600);

  
  for (int i = 0; i < NUM_FILES; i++)
    {
      TH1F* h_cosDPhi = (TH1F*) files[i]->Get("plots/h_cosdphi");
      h_cosDPhi->SetXTitle("cos(#Delta#phi)");
      h_cosDPhi->SetTitle(labels[i]);

      gStyle->SetOptStat(0);
      canv_cosDPhi_all->cd(i+1);
      h_cosDPhi->Draw("hist");
      gStyle->SetOptStat(1);
      canv_cosDPhi->cd();
      h_cosDPhi->Draw("hist");
      canv_cosDPhi->SaveAs("../Plots/TrigEffSigSel/CosDPhi/"+labels[i]+".png");
    }

  canv_cosDPhi_all->SaveAs("../Plots/TrigEffSigSel/CosDPhi/all.png");
}


void plot_MET_Et(TFile* files[], TString labels[])
{
  TCanvas *canv_MET_all = new TCanvas("canv_MET_all", "All MET_Et Plots", 1200, 1200);
  canv_MET_all->Divide(4,3);
  TCanvas *canv_MET = new TCanvas("canv_MET", "MET_Et Plot", 600, 600);


  for (int i = 0; i < NUM_FILES; i++)
    {
      TH1F* h_MET = (TH1F*) files[i]->Get("plots/h_metEt");
      h_MET->SetXTitle("MET_Et [GeV]");
      h_MET->SetTitle(labels[i]);

      gStyle->SetOptStat(0);
      canv_MET_all->cd(i+1);
      h_MET->Draw("hist");
      gStyle->SetOptStat(1);
      canv_MET->cd();
      h_MET->Draw("hist");
      canv_MET->SaveAs("../Plots/TrigEffSigSel/MET_Et/"+labels[i]+".png");
    }

  canv_MET_all->SaveAs("../Plots/TrigEffSigSel/MET_Et/all.png");
}
