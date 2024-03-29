//Plot single-electron trigger efficiency in MC and data

#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TStyle.h"
#include "TRatioPlot.h"
#include "TPad.h"
#include "TLegend.h"

using namespace std;

const int N_YEARS = 4;
const int N_MC_FILES = 12;
const int N_DATA_FILES = 4;

void getMCTrees(TTree **treesArr, TString labels[], TString runDir, TString year)
{ 
  TFile* files[N_MC_FILES];
  TTree* trees[N_MC_FILES];
  
  TString baseDir = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/";  
    
  if (runDir == "13Nov2021/" || runDir == "20Feb2022/")
   {
     files[0] = TFile::Open(baseDir + runDir + "WJetsToLNu_" + year + ".root");
     labels[0] = "WJetsToLNu_" + year; 
     files[1] = TFile::Open(baseDir + runDir + "WW_" + year + ".root");
     labels[1] = "WW_" + year;
     files[2] = TFile::Open(baseDir + runDir + "WZ_" + year + ".root");
     labels[2] = "WZ_" + year;
     files[3] = TFile::Open(baseDir + runDir + "ZZ_" + year + ".root");
     labels[3] = "ZZ_" + year;
     files[4] = TFile::Open(baseDir + runDir + "DYJetsToLL_M50_" + year + ".root");
     labels[4] = "DYJetsToLL_M50_" + year;
     files[5] = TFile::Open(baseDir + runDir + "DYJetsToLL_M10to50_" + year + ".root");
     labels[5] = "DYJetsToLL_M10-50_" + year;
     files[6] = TFile::Open(baseDir + runDir + "ST_tW_top_" + year + ".root");
     labels[6] = "ST_tW_top_" + year;
     files[7] = TFile::Open(baseDir + runDir + "ST_tW_antitop_" + year + ".root");
     labels[7] = "ST_tW_antitop_" + year;
     files[8] = TFile::Open(baseDir + runDir + "ST_t_channel_antitop_" + year + ".root");
     labels[8] = "ST_t_channel_antitop_" + year;
     files[9] = TFile::Open(baseDir + runDir + "ST_t_channel_top_" + year + ".root");
     labels[9] = "ST_t_channel_top_" + year;
     files[10] = TFile::Open(baseDir + runDir + "TTTo2L2Nu_" + year + ".root");
     labels[10] = "TTTo2L2Nu_" + year;
     files[11] = TFile::Open(baseDir + runDir + "TTToSemiLeptonic_" + year + ".root");
     labels[11] = "TTToSemiLeptonic_" + year;
   }
  else
   {
     cout << "Invalid run directory (" << runDir << ") exiting" << endl;
     exit(-1);
   }


  for (int i = 0; i < N_MC_FILES; i++)
    {
      treesArr[i] = (TTree*) files[i]->Get("Events");
      if (treesArr[i] == NULL) cout << i << endl;
    }  
}


void getDataTrees(TTree **treesArr, TString runDir, TString year)
{  
  TFile* files[N_DATA_FILES];
  TTree* trees[N_DATA_FILES];


  TString baseDir = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/"; 
  files[0] = TFile::Open(baseDir + runDir + "MET_" + year + "A.root");
  files[1] = TFile::Open(baseDir + runDir + "MET_" + year + "B.root");
  files[2] = TFile::Open(baseDir + runDir + "MET_" + year + "C.root");
  files[3] = TFile::Open(baseDir + runDir + "MET_" + year + "D.root");

  for (int i = 0; i < N_DATA_FILES; i++)
    {
      treesArr[i] = (TTree*) files[i]->Get("Events");
    }
}


void plotElTrigEff(bool ratioStyle = true, TString year="2018")
{
  TTree* mcTrees[N_MC_FILES];
  TTree* dataTrees[N_DATA_FILES];
  TString labels[N_MC_FILES];
  TString runDirMC = "20Feb2022/";
  TString runDirData = "20Feb2022/";

  getMCTrees(mcTrees, labels, runDirMC, year);
  getDataTrees(dataTrees, runDirData, year);
  
  TCanvas *canv = new TCanvas("canv", "Single El Trigger Eff Plots", 600, 600);
  TCanvas *etaCanv = new TCanvas("etaCanv", "Single El Trigger Plots in Eta", 1000, 800); 
 
  TCut baseCuts = TCut("");
  TCut metPtCut = TCut("ElTrig_metPt>250");
  TCut metFlagsCut = TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter");
  //https://indico.cern.ch/event/1042812/attachments/2288980/3891127/METHatsLPC2020.pdf Slide 20
  TCut bTagsCut = TCut("ElTrig_bTagsM==0&&ElTrig_bTagsT==0");
  TCut passHLT_Ele32_WPTight_Gsf = TCut("ElTrig_HLT_Ele32_WPTight_Gsf");
  if (runDirMC == "13Nov2021/" || runDirData == "13Nov2021" || runDirMC == "20Feb2022/" || runDirData == "20Feb2022/")
     baseCuts = baseCuts + metPtCut + metFlagsCut + bTagsCut + passHLT_Ele32_WPTight_Gsf;  
  else
    baseCuts = baseCuts + metPtCut + metFlagsCut;

  TCut trigCut = TCut("ElTrig_elTrig");
  TCut etaCuts[3];
  etaCuts[0] = "ElTrig_elEta<1.444";
  etaCuts[1] = "ElTrig_elEta>=1.566&&ElTrig_elEta<2";
  etaCuts[2] = "ElTrig_elEta>=2&&ElTrig_elEta<2.5";  
    
  int maxPt = 200;
  int nBins = 20;
  double minEtas[3] = {0, 1.566, 2};
  double maxEtas[3] = {1.444, 2, 2.5};
  //TString etas[3] = {"eta1", "eta2", "eta3"};

  TH1F *hData = new TH1F("hData", "Single-Electron Trigger Efficiency", nBins, 0, maxPt);
  TH1F *hMC = new TH1F("hMC", "Single-Electron Trigger Efficiency", nBins, 0, maxPt);
  TH1F* hMC_etas[3];
  TH1F* hData_etas[3];
  THStack* hsMC = new THStack("hsMC", "Single-Electron Trigger Efficiency");
  TH1F* hDenData = new TH1F("hDenData", "", nBins, 0, maxPt);
  TH1F* hDenData_etas[3];
  TH1F* hDenMC = new TH1F("hDenMC", "", nBins, 0, maxPt);
  TH1F* hDenMC_etas[3];
  TH1F* mcHists[N_MC_FILES];
  
  hMC_etas[0] = new TH1F("hMC_eta0", "", nBins, 0, maxPt);
  hMC_etas[1] = new TH1F("hMC_eta1", "", nBins, 0, maxPt);
  hMC_etas[2] = new TH1F("hMC_eta2", "", nBins, 0, maxPt);
  hDenMC_etas[0] = new TH1F("hDenMC_eta0", "", nBins, 0, maxPt);
  hDenMC_etas[1] = new TH1F("hDenMC_eta1", "", nBins, 0, maxPt);
  hDenMC_etas[2] = new TH1F("hDenMC_eta2", "", nBins, 0, maxPt);
  hData_etas[0] = new TH1F("hData_eta0", "Trigger Efficiency: 0 < el.eta < 1.444", nBins, 0, maxPt);
  hData_etas[1] = new TH1F("hData_eta1", "Trigger Efficiency: 1.566 < el.eta < 2.000", nBins, 0, maxPt);
  hData_etas[2] = new TH1F("hData_eta2", "Trigger Efficiency: 2.000 < el.eta < 2.500", nBins, 0, maxPt);
  hDenData_etas[0] = new TH1F("hDenData_eta0", "", nBins, 0, maxPt);
  hDenData_etas[1] = new TH1F("hDenData_eta1", "", nBins, 0, maxPt);
  hDenData_etas[2] = new TH1F("hDenData_eta2", "", nBins, 0, maxPt);

  for (int i = 0; i < N_MC_FILES; i++)
    {
      TH1F *hNum = new TH1F(labels[i], "", nBins, 0, maxPt);
      mcTrees[i]->Draw("ElTrig_elPt>>+"+labels[i], baseCuts + trigCut);
      hNum->Sumw2();

      TH1F *hDen = new TH1F("hDen", "", nBins, 0, maxPt);
      mcTrees[i]->Draw("ElTrig_elPt>>+hDen", baseCuts);
      hDen->Sumw2();

      hDenMC->Add(hDen);
      hMC->Add(hNum);
      mcHists[i] = (TH1F*) hNum->Clone();
      mcHists[i]->Divide(hDen);      

      delete hNum;
      delete hDen;

     
      for (int j = 0; j < 3; j++)
        {
	   TH1F *hNum2 = new TH1F("hNum2", "", nBins, 0, maxPt);
      	   mcTrees[i]->Draw("ElTrig_elPt>>+hNum2", baseCuts + trigCut + etaCuts[j]);
           hNum2->Sumw2();
              
           TH1F *hDen2 = new TH1F("hDen2", "", nBins, 0, maxPt);
           mcTrees[i]->Draw("ElTrig_elPt>>+hDen2", baseCuts + etaCuts[j]);
           hDen2->Sumw2();
           
           hMC_etas[j]->Add(hNum2);
           hDenMC_etas[j]->Add(hDen2);         
           
           delete hNum2;
           delete hDen2;
	}

    }

  hMC->Divide(hDenMC);

  for (int j = 0; j < 3; j++)
    {
      hMC_etas[j]->Divide(hDenMC_etas[j]);
      hMC_etas[j]->SetMarkerColor(kBlue);
      hMC_etas[j]->SetLineColor(kBlue);
    }  
 
  int col = 2;
  for (int k = 0; k < N_MC_FILES; k++)
    { 
      if (k == 8)
	col = 40;
      mcHists[k]->SetXTitle("el pt [GeV]");
      mcHists[k]->SetYTitle("Trigger Efficiency");
      mcHists[k]->SetFillColor(col);
      mcHists[k]->SetMarkerColor(col);
      mcHists[k]->SetLineColor(col);
      hsMC->Add(mcHists[k]);
      col++;
    }

  for (int j = 0; j < N_DATA_FILES; j++)
    {
      TH1F *hNum = new TH1F("hNum", "", nBins, 0, maxPt);
      dataTrees[j]->Draw("ElTrig_elPt>>+hNum", baseCuts + trigCut);
      hNum->Sumw2();

      TH1F *hDen = new TH1F("hDen", "", nBins, 0, maxPt);
      dataTrees[j]->Draw("ElTrig_elPt>>+hDen", baseCuts);
      hDen->Sumw2();

      hDenData->Add(hDen);
      hData->Add(hNum);

      delete hNum;
      delete hDen;

      for (int k = 0; k < 3; k++)
        {
           TH1F *hNum2 = new TH1F("hNum2", "", nBins, 0, maxPt);
           dataTrees[j]->Draw("ElTrig_elPt>>+hNum2", baseCuts + trigCut + etaCuts[k]);
           hNum2->Sumw2();

           TH1F *hDen2 = new TH1F("hDen2", "", nBins, 0, maxPt);
           dataTrees[j]->Draw("ElTrig_elPt>>+hDen2", baseCuts + etaCuts[k]);
           hDen2->Sumw2();
           
           hData_etas[k]->Add(hNum2);
           hDenData_etas[k]->Add(hDen2);

           delete hNum2;
           delete hDen2;
        }
    }
  hData->Divide(hDenData);
   for (int j = 0; j < 3; j++)
    {
      hData_etas[j]->Divide(hDenData_etas[j]);
      hData_etas[j]->SetMarkerColor(kRed);
      hData_etas[j]->SetLineColor(kRed);
      hData_etas[j]->SetXTitle("Electron pt [GeV]");
      hData_etas[j]->SetMaximum(1.0);
    }

  gStyle->SetOptStat(0);

  if (!ratioStyle)
   {   
      TLegend *leg = new TLegend(0.6, 0.1, 0.9, 0.45);
      for (int i = 0; i < N_MC_FILES; i++)
         {
            mcHists[i]->Draw("p* same");
            leg->AddEntry(mcHists[i], labels[i], "p");
         }      


      hData->SetMarkerColor(1);
      hData->SetLineColor(1);	
      hData->SetXTitle("el pt [GeV]");
      hData->SetTitle("Trigger Efficiency");
      hData->Draw("e same");
      
      leg->AddEntry(hData, "MET Dataset 2018", "ep");
      leg->Draw("same");
      
      canv->SaveAs("../Plots/singleElTrigEff_stack.png");
    }
  else
   {
    canv->cd();   
  
    hData->SetMarkerColor(2);
    hMC->SetMarkerColor(4);
    hData->SetLineColor(2);
    hMC->SetLineColor(4);
    hData->SetXTitle("el pt [GeV]");
    hMC->SetXTitle("el pt [GeV]");
    hData->SetYTitle("Trigger Efficiency");
    hMC->SetYTitle("Trigger Efficiency");    
    hData->SetMaximum(1.0);
    hMC->SetMaximum(1.0); 

    TRatioPlot* ratio = new TRatioPlot(hData, hMC, "divsym");
    ratio->SetH1DrawOpt("e");
    ratio->SetH2DrawOpt("e");
    ratio->Draw();
    //ratio->GetLowerPad()->GetYAxis->SetTitle("Data / MC");  

    gPad->Modified();
    gPad->Update(); // make sure it’s really (re)drawn
    TPad *pad = ratio->GetUpperPad();
    TLegend *leg = pad->BuildLegend(0.6, 0.1, 0.9, 0.35);
    leg->Clear();
    leg->AddEntry(hMC, "MC 2018", "ep");
    leg->AddEntry(hData, "Data 2018", "ep");
    pad->Modified();
    pad->Update();
    
    canv->SaveAs("../Plots/singleElTriggerEff_ratio.png");

    etaCanv->Divide(2,2);
    
    TRatioPlot* ratio_etas[3];
    TPad *pad2;
    for (int i = 0; i < 3; i++)
      {
        ratio_etas[i] = new TRatioPlot(hData_etas[i], hMC_etas[i], "divsym");
        ratio_etas[i]->SetH1DrawOpt("e");
        ratio_etas[i]->SetH2DrawOpt("e");
        etaCanv->cd(i+1);
        ratio_etas[i]->Draw();
        
        gPad->Modified();
        gPad->Update(); // make sure it’s really (re)drawn
        pad2 = ratio_etas[i]->GetUpperPad();
        leg = pad2->BuildLegend(0.5, 0.3, 0.9, 0.5);
        leg->Clear();
        leg->AddEntry(hData_etas[i], "Data 2018", "ep");
        leg->AddEntry(hMC_etas[i], "MC 2018", "ep");
        pad2->Modified();
        pad2->Update();
      }
/*
    gPad->Modified();
    gPad->Update(); // make sure it’s really (re)drawn
    TPad *pad2 = ratio_etas[0]->GetUpperPad();
    TLegend *leg2 = pad2->BuildLegend(0.5, 0.1, 0.9, 0.5);
    leg2->Clear();
    leg2->AddEntry(hMC_etas[0], "MC 0<=abs(el.eta)<1", "ep");
    leg2->AddEntry(hMC_etas[1], "MC 1<=abs(el.eta)<2", "ep");
    leg2->AddEntry(hMC_etas[2], "MC 2<=abs(el.eta)<2.5", "ep");
    leg2->AddEntry(hData_etas[0], "Data 0<=abs(el.eta)<1", "ep");
    leg2->AddEntry(hData_etas[1], "Data 1<=abs(el.eta)<2", "ep");
    leg2->AddEntry(hData_etas[2], "Data 2<=abs(el.eta)<2.5", "ep");
    pad2->Modified();
    pad2->Update();
*/
    etaCanv->SaveAs("../Plots/TrigEff/singleElTrigEff_ratioEta.png");
   }

}

  
void plotCutParameters(bool applyCuts=true)
{
  TTree* mcTrees[N_MC_FILES];
  TTree* dataTrees[N_DATA_FILES];
  TString labels[N_MC_FILES];
  TString runDirMC = "20Feb2022/";
  TString runDirData = "20Feb2022/";
  TString year = "2018";

  getMCTrees(mcTrees, labels, runDirMC, year);
  getDataTrees(dataTrees, runDirData, year);


  TCanvas *canv_elPt = new TCanvas("canv_elPt", "elPt Plot", 600, 600);
  TCanvas *canv_mt = new TCanvas("canv_mt", "mt Plot", 600, 600);
  TCanvas *canv_METpt = new TCanvas("canv_METpt", "MET.pt Plot", 600, 600);
  TCanvas *canv_bTags = new TCanvas("canv_bTags", "N b-tags Plot", 600, 600);
  TCanvas *canv_elEta = new TCanvas("canv_elEta", "elEta Plot", 600, 600);
  TCanvas *canv_nAK4 = new TCanvas("canv_nAK4", "nAK4 Plot", 600, 600);
  TCanvas *canv_metSig = new TCanvas("canv_metSig", "MET Significance", 600, 600);

  gStyle->SetOptStat(0);

  int nBins_elPt = 25;
  int nBins_mt = 15;
  int nBins_METpt = 25;
  int nBins_bTags = 100;
  int nBins_eta = 25;
  int nBins_nAK4 = 20;
  int nBins_metSig = 40;
  float min_eta = 0;
  float min_nAK4 = 0;
  float min_metSig = 0;
  float max_elPt = 200;
  float max_mt = 150;
  float max_METpt = 500;
  float max_bTags = 1;
  float max_eta = 2.5;
  float max_nAK4 = 20;
  float max_metSig = 200;

  TCut elTrig = "ElTrig_elTrig";
  TCut bTagCuts = "Jet_pt>=20&&abs(Jet_eta)<2.5&&4&Jet_jetId&&Jet_btagDeepB>=0.1208";
  TCut metPtCut = TCut("ElTrig_metPt>250");
  TCut metFlagsCut = TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter");
  //https://indico.cern.ch/event/1042812/attachments/2288980/3891127/METHatsLPC2020.pdf Slide 20
  TCut nbTagsCut = TCut("ElTrig_bTagsM==0&&ElTrig_bTagsT==0");
  TCut cuts;
  if (applyCuts)
    cuts = metPtCut + metFlagsCut + nbTagsCut;
  else
    cuts = "";

  cout << "Applying cuts= " << cuts << endl;

  //2018 luminosity
  double lumi = 59830;  

  //Add data
  TH1F *h_elPt_data = new TH1F("h_elPt_data","Electron pt", nBins_elPt, 10, max_elPt);
  TH1F *h_mt_data = new TH1F("h_mt_data", "Tranverse Mass", nBins_mt, 10, max_mt); 
  TH1F *h_METpt_data = new TH1F("h_METpt", "MET pt", nBins_METpt, 200, max_METpt);
  TH1F *h_bTag_data = new TH1F("h_bTag", "b-tagged Events", nBins_bTags, 0.12, max_bTags);  
  TH1F *h_elEta_data = new TH1F("h_elEta_data","Electron eta", nBins_eta, min_eta, max_eta);
  TH1F *h_nAK4_data = new TH1F("h_nAK4_data", "Num AK4 Jets", nBins_nAK4, min_nAK4, max_nAK4); 
  TH1F *h_metSig_data = new TH1F("h_metSig_data", "MET Significance", nBins_metSig, min_metSig, max_metSig);

  for (int i = 0; i < N_DATA_FILES; i++)
    {
      TH1F *temp_elPt = new TH1F("temp_elPt", "", nBins_elPt, 10, max_elPt);
      dataTrees[i]->Draw("ElTrig_elPt>>+temp_elPt", cuts);
      temp_elPt->Sumw2();
      h_elPt_data->Add(temp_elPt);
      delete temp_elPt;
      
      TH1F *temp_mt = new TH1F("temp_mt", "", nBins_mt, 10, max_mt);
      dataTrees[i]->Draw("ElTrig_mt>>+temp_mt", cuts);
      temp_mt->Sumw2();
      h_mt_data->Add(temp_mt);
      delete temp_mt;
      
      TH1F *temp_METpt = new TH1F("temp_METpt", "", nBins_METpt, 200, max_METpt);
      dataTrees[i]->Draw("ElTrig_metPt>>+temp_METpt", cuts);
      temp_METpt->Sumw2();
      h_METpt_data->Add(temp_METpt);
      delete temp_METpt;

      TH1F *temp_bTag = new TH1F("temp_bTag", "", nBins_bTags, 0.12 , max_bTags);
      dataTrees[i]->Draw("Jet_btagDeepB>>+temp_bTag", cuts + bTagCuts);
      temp_bTag->Sumw2();
      //temp_bTag->Scale(1.0/dataTrees[i]->GetEntries(cuts));
      h_bTag_data->Add(temp_bTag);
      delete temp_bTag;

      TH1F *temp_elEta = new TH1F("temp_elEta", "", nBins_eta, min_eta, max_eta);
      dataTrees[i]->Draw("abs(ElTrig_elEta)>>+temp_elEta", cuts);
      temp_elEta->Sumw2();
      h_elEta_data->Add(temp_elEta);
      delete temp_elEta;

      TH1F *temp_nAK4 = new TH1F("temp_nAK4", "", nBins_nAK4, min_nAK4, max_nAK4);
      dataTrees[i]->Draw("nJet>>+temp_nAK4", cuts);
      temp_nAK4->Sumw2();
      h_nAK4_data->Add(temp_nAK4);
      delete temp_nAK4;

      TH1F *temp_metSig = new TH1F("temp_metSig", "", nBins_metSig, min_metSig, max_metSig);
      dataTrees[i]->Draw("MET_significance>>+temp_metSig", cuts);
      temp_metSig->Sumw2();
      h_metSig_data->Add(temp_metSig);
      delete temp_metSig;
    }
  h_bTag_data->Scale(1.0/h_bTag_data->GetEntries());

  TLegend *leg = new TLegend(0.6, 0.5, 0.9, 0.9);
  leg->AddEntry(h_METpt_data, "Data 2018", "l");

  //Stack MC
  THStack *hs_elPt_mc = new THStack("hs_elPt_mc", "Electron pt");
  THStack *hs_mt_mc = new THStack("hs_mt_mc", "Transverse Mass");
  THStack *hs_METpt_mc = new THStack("hs_METpt_mc", "MET pt");
  THStack *hs_bTag_mc = new THStack("hs_bTag_mc", "b-tagged Events");
  THStack *hs_elEta_mc = new THStack("hs_elEta_mc", "Electron eta");
  THStack *hs_nAK4_mc = new THStack("hs_nAK4_mc", "Num AK4 Jets");
  THStack *hs_metSig_mc = new THStack("hs_metSig_mc", "MET Significance");
 
  int col = 2;
  for (int j = 0; j < N_MC_FILES; j++)
    {      
      if (j == 8)
        col = 40;
      
      float xsWeight;
      mcTrees[j]->SetBranchAddress("xsWeight", &xsWeight);
      mcTrees[j]->GetEntry(); 
     
      cout << "xsWeight for " << labels[j] << " = " << xsWeight << endl;
      cout << "xsWeight * lumi = event weight = " << xsWeight * lumi << endl;
     
      TH1F *temp_elPt = new TH1F("elPt_"+labels[j], "", nBins_elPt, 10, max_elPt);
      mcTrees[j]->Draw("ElTrig_elPt>>+elPt_"+labels[j], cuts, "hist"); 	 
      temp_elPt->Sumw2();
      temp_elPt->Scale(xsWeight*lumi);
      temp_elPt->SetLineColor(col);
      temp_elPt->SetFillColor(col);
      temp_elPt->SetXTitle("electron pt [GeV]");
      hs_elPt_mc->Add((TH1F*) temp_elPt->Clone());
      
      TH1F *temp_mt = new TH1F("temp_mt_"+labels[j], "", nBins_mt, 10, max_mt);
      mcTrees[j]->Draw("ElTrig_mt>>+temp_mt_"+labels[j], cuts, "hist");
      temp_mt->Scale(xsWeight*lumi);
      temp_mt->SetLineColor(col);
      temp_mt->SetFillColor(col);
      hs_mt_mc->Add((TH1F*) temp_mt->Clone());
      
      TH1F *temp_METpt = new TH1F("temp_METpt_"+labels[j], "", nBins_METpt, 200, max_METpt);
      mcTrees[j]->Draw("ElTrig_metPt>>+temp_METpt_"+labels[j], cuts, "hist");
      temp_METpt->Scale(lumi*xsWeight);
      temp_METpt->SetLineColor(col);
      temp_METpt->SetFillColor(col);
      hs_METpt_mc->Add((TH1F*) temp_METpt->Clone());

      TH1F *temp_bTag = new TH1F("temp_bTag_"+labels[j], "", nBins_bTags, 0.12, max_bTags);
      mcTrees[j]->Draw("Jet_btagDeepB>>+temp_bTag_"+labels[j], cuts + bTagCuts, "hist");
      //temp_bTag->Scale(xsWeight*lumi);
      if (mcTrees[j]->GetEntries(cuts)>0)
      	temp_bTag->Scale(1.0/mcTrees[j]->GetEntries(cuts));
      TH1 *cumulative = temp_bTag->GetCumulative();
      cumulative->SetLineColor(col);
      cumulative->SetFillColor(col);
      hs_bTag_mc->Add((TH1*) cumulative->Clone());
      //cout << "Average # b-tags / event for " << labels[j] << " = " << temp_bTag->Integral() << endl;

      TH1F *temp_elEta = new TH1F("elEta_"+labels[j], "", nBins_eta, min_eta, max_eta);
      mcTrees[j]->Draw("abs(ElTrig_elEta)>>+elEta_"+labels[j], cuts, "hist");
      temp_elEta->Sumw2();
      temp_elEta->Scale(xsWeight*lumi);
      temp_elEta->SetLineColor(col);
      temp_elEta->SetFillColor(col);
      temp_elEta->SetXTitle("electron eta");
      hs_elEta_mc->Add((TH1F*) temp_elEta->Clone());

      TH1F *temp_nAK4 = new TH1F("nAK4_"+labels[j], "", nBins_nAK4, min_nAK4, max_nAK4);
      mcTrees[j]->Draw("nJet>>+nAK4_"+labels[j], cuts, "hist");
      temp_nAK4->Sumw2();
      temp_nAK4->Scale(xsWeight*lumi);
      temp_nAK4->SetLineColor(col);
      temp_nAK4->SetFillColor(col);
      temp_nAK4->SetXTitle("Num AK4 Jets");
      hs_nAK4_mc->Add((TH1F*) temp_nAK4->Clone());

      TH1F *temp_metSig = new TH1F("metSig_"+labels[j], "", nBins_metSig, min_metSig, max_metSig);
      mcTrees[j]->Draw("MET_significance>>+metSig_"+labels[j], cuts, "hist");
      temp_metSig->Sumw2();
      temp_metSig->Scale(xsWeight*lumi);
      temp_metSig->SetLineColor(col);
      temp_metSig->SetFillColor(col);
      temp_metSig->SetXTitle("MET Significance");
      hs_metSig_mc->Add((TH1F*) temp_metSig->Clone());
      
      col++;

      leg->AddEntry(temp_METpt, labels[j], "f");
    }

  h_elPt_data->SetXTitle("electron pt [GeV]");
  h_elPt_data->SetLineColor(1);
  h_mt_data->SetLineColor(1);
  h_mt_data->SetXTitle("mt [Gev]");
  h_METpt_data->SetLineColor(1);
  h_METpt_data->SetXTitle("MET.pt [GeV]");
  h_bTag_data->SetXTitle("Jet_btagDeepB");
  h_bTag_data->SetYTitle("Cumulative Avg # Tags / event");
  h_bTag_data->SetLineColor(1);
  h_elEta_data->SetXTitle("electron eta");
  h_elEta_data->SetLineColor(1);
  h_nAK4_data->SetXTitle("Num AK4 Jets");
  h_nAK4_data->SetLineColor(1);
  h_metSig_data->SetXTitle("MET Significance");
  h_metSig_data->SetLineColor(1);
  
  //elPt
  canv_elPt->cd();
  hs_elPt_mc->Draw("hist");
  hs_elPt_mc->GetXaxis()->SetTitle("electron pt [GeV]");
  h_elPt_data->Draw("e same");
  leg->Draw("same");
  canv_elPt->SaveAs("../Plots/TrigEff/elPt.png");

  canv_mt->cd();
  hs_mt_mc->Draw("hist");
  hs_mt_mc->GetXaxis()->SetTitle("mt [GeV]");
  h_mt_data->Draw("e same");
  leg->Draw("same");
  canv_mt->SaveAs("../Plots/TrigEff/mt.png");

  canv_METpt->cd();
  hs_METpt_mc->Draw("hist");
  hs_METpt_mc->GetXaxis()->SetTitle("MET.pt [GeV]");
  h_METpt_data->Draw("e same");
  leg->Draw("same");
  canv_METpt->SaveAs("../Plots/TrigEff/metPt.png");
  
  canv_bTags->cd();
  hs_bTag_mc->Draw("hist");
  hs_bTag_mc->GetXaxis()->SetTitle("Jet_btagDeepB");
  hs_bTag_mc->GetYaxis()->SetTitle("Cumulative Avg # Tags / Event");
  h_bTag_data->Draw("e same");
  leg->Draw("same");
  canv_bTags->SaveAs("../Plots/TrigEff/bTag.png");

  canv_elEta->cd();
  hs_elEta_mc->Draw("hist");
  hs_elEta_mc->GetXaxis()->SetTitle("electron eta");
  h_elEta_data->Draw("e same");
  leg->Draw("same");
  canv_elEta->SaveAs("../Plots/TrigEff/elEta.png");

  canv_nAK4->cd();
  hs_nAK4_mc->Draw("hist");
  hs_nAK4_mc->GetXaxis()->SetTitle("Num AK4 Jets");
  h_nAK4_data->Draw("e same");
  leg->Draw("same");
  canv_nAK4->SaveAs("../Plots/TrigEff/nAK4.png");  

  canv_metSig->cd();
  hs_metSig_mc->Draw("hist");
  hs_metSig_mc->GetXaxis()->SetTitle("MET Significance");
  h_metSig_data->Draw("e same");
  leg->Draw("same");
  canv_metSig->SaveAs("../Plots/TrigEff/metSig.png");  

}



void plotNbTags()
{
  TTree* mcTrees[N_MC_FILES];
  TString labels[N_MC_FILES];
//  TString runDir = "13Nov2021/";
  TString runDir = "20Feb2022/";
  TString year = "2018";
  getMCTrees(mcTrees, labels, runDir, year);
  gStyle->SetOptStat(0);

  TCanvas *canv = new TCanvas("canv", "Number of b-Tagged Events", 1500, 600);

  THStack *hs_loose = new THStack("hs_loose", "Loose WP");
  THStack *hs_med = new THStack("hs_med", "Medium WP");
  THStack *hs_tight = new THStack("hs_tight", "Tight WP");

  TLegend *leg = new TLegend(0.5, 0.5, 0.9, 0.9);

  for (int i = 0; i < N_MC_FILES; i++)
    {  
      TH1F* hL = new TH1F("hL_"+labels[i],"Loose WP",7, -0.5, 6.5);
      mcTrees[i]->Draw("ElTrig_bTagsL>>+hL_"+labels[i], "ElTrig_bTagsM==0&&ElTrig_bTagsT==0");     
      TH1F* hM = new TH1F("hM_"+labels[i],"Medium WP",7, -0.5, 6.5);
      mcTrees[i]->Draw("ElTrig_bTagsM>>+hM_"+labels[i], "ElTrig_bTagsT==0");
      TH1F* hT = new TH1F("hT_"+labels[i],"Tight WP",7, -0.5, 6.5);
      mcTrees[i]->Draw("ElTrig_bTagsT>>+hT_"+labels[i]);
      
      int col = 2*(i+1);
      hL->SetLineColor(col);
      hL->SetFillColor(col);
      hM->SetLineColor(col);
      hM->SetFillColor(col);
      hT->SetLineColor(col);
      hT->SetFillColor(col);

      hL->SetXTitle("# of b-tagged events");
      hM->SetXTitle("# of b-tagged events");
      hT->SetXTitle("# of b-tagged events");
  
      hs_loose->Add((TH1F*) hL->Clone());
      hs_med->Add((TH1F*) hM->Clone());
      hs_tight->Add((TH1F*) hT->Clone());

      leg->AddEntry(hL->Clone(), labels[i], "F");   
  
      delete hL;
      delete hM;
      delete hT;
    }  

   canv->Divide(3,1);
  
   canv->cd(1);
   hs_loose->Draw();
   hs_loose->GetXaxis()->SetTitle("# of b-tagged jets/event");
   leg->Draw();
   
   canv->cd(2);
   hs_med->Draw();
   hs_med->GetXaxis()->SetTitle("# of b-tagged jets/event");
   leg->Draw();   
  
   canv->cd(3);
   hs_tight->Draw();
   hs_tight->GetXaxis()->SetTitle("# of b-tagged jets/event");
   leg->Draw();

   canv->SaveAs("../Plots/nBTags.png");

}


//Make TH2Fs of pt vs eta SFs for each year
void makeSFplots(TString year="2018", bool testSingleTrig = false)
{
  gStyle->SetOptStat(0);
  TCanvas* canv = new TCanvas("canv", "Single-El Trigger SFs", 1200, 700);
  TFile* outFile = new TFile("singleElTrigEffSF_" + year + ".root", "RECREATE");

  TTree* mcTrees[N_MC_FILES];
  TTree* dataTrees[N_DATA_FILES];
  TString labels[N_MC_FILES];
  TString runDirMC = "20Feb2022/";
  TString runDirData = "20Feb2022/";

  getMCTrees(mcTrees, labels, runDirMC, year);
  getDataTrees(dataTrees, runDirData, year);

  //Eta bins chosen to match barrel & endcap regions in agreement with:
  //https://github.com/cms-sw/cmssw/blob/e864342789fe1766666f49b97f8e3e3b9e6bfa25/PhysicsTools/NanoAOD/python/photons_cff.py#L213-L214
  const int nEtaBins = 3;
  double etaBinsLowEdges[nEtaBins+1] = {0,1.4442,1.566,2.5}; 
  const int nPtBins = 5;
  double ptBinsLowEdges[nPtBins+1] = {34,50,75,100,150,250};

  TString etaBinLabels[nEtaBins] = {"[0, 1.442)", "[1.442, 1.566)", "[1.566, 2.5)"};
  TString ptBinLabels[nPtBins] = {"[34, 50)", "[50, 75)", "[75, 100)", "[100, 150)", "[150, 250)"};

  TH2F* hSFs = new TH2F("hSFs", "Single Electron Trigger Scale Factors (Data/MC);El SC Eta;El pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
  TH2F* hData = new TH2F("hData", "Data;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
  TH2F* hMC = new TH2F("hMC", "MC;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
  TH2F* hDataDen = new TH2F("hDataDen", "Data;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
  TH2F* hMCDen = new TH2F("hMCDen", "MC;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
  TH2F* hSFerrs = new TH2F("hSFerrs", "Single El Trigger SF Uncertainties; El SC Eta; El pT", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);

  TCut baseCuts = TCut("");
  TCut metPtCut = TCut("ElTrig_metPt>250");
  TCut metFlagsCut = TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter");
  //https://indico.cern.ch/event/1042812/attachments/2288980/3891127/METHatsLPC2020.pdf Slide 20
  TCut bTagsCut = TCut("ElTrig_bTagsM==0&&ElTrig_bTagsT==0");
  if (runDirData == "13Nov2021/" || runDirMC == "13Nov2021" || runDirMC == "20Feb2022/" || runDirData == "20Feb2022/")
     baseCuts = baseCuts + metPtCut + metFlagsCut + bTagsCut;  
  else
    baseCuts = baseCuts + metPtCut + metFlagsCut;
  TCut trigCut = TCut("ElTrig_elTrig");
  TCut passHLT_Ele32_WPTight_Gsf = TCut("ElTrig_HLT_Ele32_WPTight_Gsf");
  if (testSingleTrig)
    trigCut = trigCut + passHLT_Ele32_WPTight_Gsf;

  cout << "Trigger cut is " << trigCut << endl;

  hData->Sumw2();
  hMC->Sumw2();
  hDataDen->Sumw2();
  hMCDen->Sumw2();
  hSFs->Sumw2();
  hSFerrs->Sumw2();

  for (int i = 0; i < N_DATA_FILES; i++)
  {
    TH2F* hTempNum =  new TH2F("hTempNum", "Data;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
    TH2F* hTempDen =  new TH2F("hTempDen", "Data;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
    //dataTrees[i]->Draw("ElTrig_elPt:ElTrig_elEta>>+hTempNum", baseCuts + trigCut);
    //dataTrees[i]->Draw("ElTrig_elPt:ElTrig_elEta>>+hTempDen", baseCuts);
    dataTrees[i]->Draw("ElTrig_elPt:(ElTrig_elEta+ElTrig_elDeltaEtaSC)>>+hTempNum", baseCuts + trigCut);
    dataTrees[i]->Draw("ElTrig_elPt:(ElTrig_elEta+ElTrig_elDeltaEtaSC)>>+hTempDen", baseCuts);

    hData->Add(hTempNum);
    hDataDen->Add(hTempDen);

    delete hTempNum;
    delete hTempDen;
  }
  
  for (int i = 0; i < N_MC_FILES; i++)
  {
    TH2F* hTempNum =  new TH2F("hTempNum", "MC;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
    TH2F* hTempDen =  new TH2F("hTempDen", "MC;El SC Eta;Electron pT [GeV]", nEtaBins, etaBinsLowEdges, nPtBins, ptBinsLowEdges);
    //mcTrees[i]->Draw("ElTrig_elPt:ElTrig_elEta>>+hTempNum", baseCuts + trigCut);
    //mcTrees[i]->Draw("ElTrig_elPt:ElTrig_elEta>>+hTempDen", baseCuts);
    mcTrees[i]->Draw("ElTrig_elPt:(ElTrig_elEta+ElTrig_elDeltaEtaSC)>>+hTempNum", baseCuts + trigCut);
    mcTrees[i]->Draw("ElTrig_elPt:(ElTrig_elEta+ElTrig_elDeltaEtaSC)>>+hTempDen", baseCuts);

    hMC->Add(hTempNum);
    hMCDen->Add(hTempDen);

    delete hTempNum;
    delete hTempDen;
  }

  hData->Divide(hDataDen);
  hMC->Divide(hMCDen);

  hSFs->Divide(hData, hMC);
  hSFs->Sumw2();

  //Calculate uncertainties and store in hSFerrs
  for (int i = 1; i <= hSFs->GetNbinsX(); i++)
  {
    hSFs->GetXaxis()->SetBinLabel(i, etaBinLabels[i-1]);
    hSFerrs->GetXaxis()->SetBinLabel(i, etaBinLabels[i-1]);
    for (int j = 1; j <= hSFs->GetNbinsY(); j++)
    {
      double err = hSFs->GetBinError(i, j); //Since Sumw2() has been called, err = sqrt(sum of squares of weight) for each bin
      hSFerrs->SetBinContent(i, j, err);

      hSFs->GetYaxis()->SetBinLabel(j, ptBinLabels[j-1]);
      hSFerrs->GetYaxis()->SetBinLabel(j, ptBinLabels[j-1]);
    }
  }
 
  //outFile->Write("hData");
  //outFile->Write("hMC");
  outFile->Write("hSFs");
  outFile->Write("hSFerrs");
  outFile->Close();

  canv->Divide(2,1);
  canv->cd(1);

  gStyle->SetPaintTextFormat("4.2f");

  //hSFs->LabelsOption("h","Z"); //Label bins on plot with the z (SF) value, label horizontally
  hSFs->Draw("col texte");
  canv->cd(2);
  //hSFerrs->LabelsOption("h", "Z");
  hSFerrs->Draw("col text");
  canv->SaveAs("../Plots/singleElTrigEffSFs.png");
}



void examineFiredTriggers(TString year = "2018")
{
  TTree* mcTrees[N_MC_FILES];
  TTree* dataTrees[N_DATA_FILES];
  TString labels[N_MC_FILES];
  TString runDirMC = "20Feb2022/";
  TString runDirData = "20Feb2022/";

  getMCTrees(mcTrees, labels, runDirMC, year);
  getDataTrees(dataTrees, runDirData, year);
 
  TString trigNames[7] = {"HLT_Ele25_eta2p1_WPTight_Gsf", "HLT_Ele27_WPTight_Gsf",
  "HLT_Ele32_WPTight_Gsf", "HLT_Ele32_WPTight_Gsf_L1DoubleEG", "HLT_Ele35_WPTight_Gsf",
  "HLT_Ele38_WPTight_Gsf", "HLT_Ele40_WPTight_Gsf"};
   
  TCut anyTrig = TCut("ElTrig_elTrig"); 
  
  int nAnyTrigMC = 0;
  int nAnyTrigData = 0;
  int nTimesTrigMC[7] = {0};
  int nTimesTrigData[7] = {0};

  cout << "Entering loops" << endl;
  for (int i = 0; i < N_MC_FILES; i++)
  {
    TTree* tree = mcTrees[i];
    nAnyTrigMC += tree->GetEntries(anyTrig);
    //cout << "Got tree for mc i = " << i << endl;
    for (int j = 0; j < 7; j++)
    {
      TCut thisTrigCut = TCut("ElTrig_" + trigNames[j] + ">0");
      nTimesTrigMC[j] += tree->GetEntries(anyTrig + thisTrigCut); 
    }
  }

  for (int i = 0; i < N_DATA_FILES; i++)
  {
    TTree* tree = dataTrees[i];
    nAnyTrigData += tree->GetEntries(anyTrig);
    for (int j = 0; j < 7; j++)
    {
      TCut thisTrigCut = TCut("ElTrig_" + trigNames[j] + ">0");
      nTimesTrigData[j] += tree->GetEntries(anyTrig + thisTrigCut); 
    }
  }

  cout << "\nTrigger Counting:" << endl;
  cout << "Total triggered MC events using OR of all triggers = " << nAnyTrigMC << endl;
  cout << "Total triggered MC events using OR of all triggers = " << nAnyTrigData << endl;
  cout << "Trigger |\t nData |\t nData % |\t nMC |\t nMC % |\t (nData / nMC) * (nAnyTrigMC / nAnyTrigData)" << endl;
  for (int i = 0; i < 7; i++)
  {
     cout << trigNames[i] << " |\t" << nTimesTrigData[i] << " |\t" << 100.0 * nTimesTrigData[i] / (float) nAnyTrigData << " |\t" <<
     nTimesTrigMC[i] << " |\t" << 100.0 * nTimesTrigMC[i] / (float) nAnyTrigMC << "|\t" <<
     nTimesTrigData[i] / (float) nTimesTrigMC[i] * nAnyTrigMC /(float) nAnyTrigData << endl;
  }
}
