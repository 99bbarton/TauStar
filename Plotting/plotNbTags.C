//Plot the number of b-tagged events for each wp for TTbar samples

void plotNbTags()
{
  gStyle->SetOptStat(0); 

  const int N_FILES = 2;

  TFile* files[N_FILES];
  TString labels[N_FILES];
  files[0] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TTTo2L2Nu_2018.root");
  labels[0] = "TTTo2L2Nu";
  files[1] = TFile::Open("root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TTToSemiLeptonic_2018.root");
  labels[1] = "TTToSemiLeptonic";  

  TCanvas *canv = new TCanvas("canv", "Number of b-Tagged Events", 700, 600);

  THStack *hs_loose = new THStack("hs_loose", "Loose WP");
  THStack *hs_med = new THStack("hs_med", "Medium WP");
  THStack *hs_tight = new THStack("hs_tight", "Tight WP");

  TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);

  for (int i = 0; i < N_FILES; i++)
    {
      TTree *tree = (TTree*) files[i]->Get("Events");
  
      TH1F* hL = new TH1F("hL","Loose WP",10, -0.5, 10.5);
      tree->Draw("ElTrig_bTagsL>>+hL");     
      TH1F* hM = new TH1F("hM","Medium WP",10, -0.5, 10.5);
      tree->Draw("ElTrig_bTagsM>>+hM");
      TH1F* hT = new TH1F("hT","Tight WP",10, -0.5, 10.5);
      tree->Draw("ElTrig_bTagsT>>+hT");
      
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

   //canv->Divide(3,1);
  
   //canv->cd(1);
   hs_loose->Draw();
   leg->Draw();
   
   /*canv->cd(2);
   hs_med->Draw();
  
   canv->cd(3);
   hs_tight->Draw();*/

   canv->SaveAs("../Plots/nBTags.png");

}

