//


void plotSingleElTrigEff(bool isMC=true)
{
  
  TFile* file = new TFile("../Data/singleElTrig.root");
  TH1F* h_num = (TH1F*) file->Get("plots/h_ptnum");
  TH1F* h_denom = (TH1F*) file->Get("plots/h_ptdenom");
  TString title;
  if (isMC)
    title = "Single-Electron Trigger Efficiency in MC W-Jets";
  else
    title = "Single-Electron Trigger Efficiency in Data";
  TH1F* h_trigEff = new TH1F("trigEff", title, 10, 0, 100);
  h_trigEff->Divide(h_num, h_denom);
  h_trigEff->SetXTitle("Reconstructed El pT [GeV]");
  h_trigEff->SetYTitle("(# Triggered / Total) Single-El Events");

  gStyle->SetOptStat(0);
  TCanvas* canv = new TCanvas("canv", "El Trig Eff Plots", 600, 600);
  canv->cd();
  h_trigEff->Draw("p*");
  canv->SaveAs("Plots/singleElTrigEff.png");
  
}
