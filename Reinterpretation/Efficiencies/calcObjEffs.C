//Calculate the trigger+id efficiency for electrons, photons, and tauhs as a function of eta and pt


#include "TString.h"
#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TCut.h"
#include "TChain.h"
#include "TStyle.h"
#include <iostream>

const int N_FILES = 17; //17 if all bkgd MC


//Assign files to a TChain for easy access
void getTreesMCasChain(TChain& chain, TString year)
{
    TString mcNames[N_FILES] = {"DYJetsToLL_M10to50", "DYJetsToLL_M50", "ST_s_channel", "ST_tW_antitop", "ST_tW_top", "ST_t_channel_antitop", "ST_t_channel_top", "TTGamma_Dilept", "TTGamma_SingleLept", "TTTo2L2Nu", "TTToSemiLeptonic", "WGToLNuG", "WJetsToLNu", "WW", "WZ", "ZGToLLG", "ZZ" };
    TString baseDir = "root://cmsxrootd.fnal.gov//store/user/fjensen/excitedTau_23032023/";
    //TString mcNames[N_FILES] = {"recoEffs_sigMC_2500"};
    //TString baseDir = "../Data/";
    char filepath[100];

    for (int fN = 0; fN < N_FILES; fN++)
    {   
        sprintf(filepath, "%s%s_%s.root", baseDir.Data(), mcNames[fN].Data(), year.Data());
        chain.Add(filepath);
    }
}


//Construct a string for use in histogram titling based on which efficiencies are being considered
TString buildEffsStr(bool incReco=true, bool incID=true, bool incTrig=true)
{
    if (!incReco && !incID && !incTrig)
    {
        std::cout << "\nReco, ID, and trig efficiencies are all excluded. Exiting..." << endl;
        exit(1);
    }

    TString incEffsStr = "";
    if (incReco) 
    {
        if (incEffsStr != "") 
            incEffsStr += "+"; 
        incEffsStr += "Reco";
    }
    if (incID) 
    {
        if (incEffsStr != "") 
            incEffsStr += "+"; 
        incEffsStr += "ID";
    }
    if (incTrig) 
    {
        if (incEffsStr != "") 
            incEffsStr += "+"; 
        incEffsStr += "Trig";
    }

    return incEffsStr;
}

//Include reco efficiencies in the histograms passed to the function
//If the passed histograms are empty, adds the reco efficienicies. Otherwise, multiplies the existing values with the ones calculated here
void incRecoEffs(TH2F* h_elEff, TH2F* h_muEff, TH2F* h_tauEff, TH2F* h_phoEff, TString year, TString effsStr)
{
    /*Whether each relevant gen particle is matched can be found in the branch "Eff_recoPartsStatus"
    If the status is a positive definite value, that gen particle matched to a reco'd particle with abs(pdgID) = that value
    If the value is instead negative, that gen particle did NOT match to a reco'd particle with abs(pdgID) = abs(that value)
    Any other value means the gen particle was not of the type/status we care about */

    //Define custom binning
    double etaBins_EG[6] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};
    TString etaBinLabels_EG[5] = {"[0, 0.8)", "[0.8, 1.4442)", "[1.4442, 1.566)", "[1.566, 2.0)", "[2.0, 2.5)"};
    double etaBins_mu[5] = {0, 0.9, 1.2, 2.1, 2.4};
    TString etaBinLabels_mu[4] = {"[0, 0.9)", "[0.9, 1.2)", "[1.2, 2.1)", "[2.1, 2.4)"};
    double etaBins_tau[4] = {0, 1.46, 1.558, 2.3};
    TString etaBinLabels_tau[3] = {"[0, 1.46)", "[1.46, 1.558)", "[1.558, 2.3)"};
    double ptBins_mu[6] = {18, 50, 100, 200, 500, 1500};
    double ptBins_EG[7] = {5, 50, 100, 200, 500, 1000, 4000};
    double ptBins_tau[6] = {18, 50, 100, 200, 500, 1000};

    std::cout << "\nCalculating object reco efficiencies for " << year << "..." << endl;

    TH2F* h_elEff_reco = new TH2F("h_elEff_reco_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", 5, etaBins_EG, 6, ptBins_EG);
    TH2F* h_phoEff_reco = new TH2F("h_phoEff_reco_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", 5, etaBins_EG, 6, ptBins_EG);
    TH2F* h_muEff_reco = new TH2F("h_muEff_reco_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", 4, etaBins_mu, 5, ptBins_mu);
    TH2F* h_tauEff_reco = new TH2F("h_tauEff_reco_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* h_elEff_den = new TH2F("h_elEff_den_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", 5, etaBins_EG, 6, ptBins_EG);
    TH2F* h_phoEff_den = new TH2F("h_phoEff_den_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", 5, etaBins_EG, 6, ptBins_EG);
    TH2F* h_muEff_den = new TH2F("h_muEff_den_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", 4, etaBins_mu, 5, ptBins_mu);
    TH2F* h_tauEff_den = new TH2F("h_tauEff_den_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", 3, etaBins_tau, 5, ptBins_tau);

    TChain chain("Events", "MC Background Files");
    getTreesMCasChain(chain, year);

    int nGenParts;
    int genPartRecoStatus[500]; //Arrays must be equal or longer in length than arrays in tree branches
    float genPartEtas[500];
    float genPartPts[500];
    int nGenVisTau;
    int genVisTauRecoStatus[500];
    float genVisTauEtas[500];
    float genVisTauPts[500];

    //Only read the branches of the trees we care about for efficiency
    chain.SetBranchStatus("*", false);

    chain.SetBranchStatus("nGenPart", true);
    chain.SetBranchStatus("Eff_recoPartsStatus", true);
    chain.SetBranchStatus("GenPart_eta", true);
    chain.SetBranchStatus("GenPart_pt", true);
    chain.SetBranchStatus("nGenVisTau", true);
    chain.SetBranchStatus("Eff_recoVisTausStatus", true);
    chain.SetBranchStatus("GenVisTau_eta", true);
    chain.SetBranchStatus("GenVisTau_pt", true);

    chain.SetBranchAddress("nGenPart", &nGenParts);
    chain.SetBranchAddress("Eff_recoPartsStatus", &genPartRecoStatus);
    chain.SetBranchAddress("GenPart_eta", &genPartEtas);
    chain.SetBranchAddress("GenPart_pt", &genPartPts);
    chain.SetBranchAddress("nGenVisTau", &nGenVisTau);
    chain.SetBranchAddress("Eff_recoVisTausStatus", &genVisTauRecoStatus);
    chain.SetBranchAddress("GenVisTau_eta", &genVisTauEtas);
    chain.SetBranchAddress("GenVisTau_pt", &genVisTauPts);

    //Fill the appropriate numerator and denominator histograms with eta/pt of matched and non-matched relevant gen particles
    for (int eN = 1; eN < chain.GetEntries(); eN++)
    {
        chain.GetEntry(eN);

        for (int gpN = 0; gpN < nGenParts; gpN++)
        {   
            //Particles we don't care about - continue to avoid unecessary comparisons below
            if (abs(genPartRecoStatus[gpN]) < 11)
                continue;
            //Electrons
            if (genPartRecoStatus[gpN] == 11)
            {
                h_elEff_reco->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
                h_elEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -11)
            {
                h_elEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
            //Muons
            else if (genPartRecoStatus[gpN] == 13)
            {
                h_muEff_reco->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
                h_muEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -13)
            {
                h_muEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
            //Photons
            else if (genPartRecoStatus[gpN] == 22)
            {
                h_phoEff_reco->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
                h_phoEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -22)
            {
                h_phoEff_den->Fill(abs(genPartEtas[gpN]), genPartPts[gpN]);
            }  
        }

        //Taus match separately to genVisTaus
        if (nGenVisTau >= 1)
        {
            for (int gvtN = 0; gvtN < nGenVisTau; gvtN++)
            {
                if (genVisTauRecoStatus[gvtN] == -1) //Not a valid genVisTau for consideration
                    continue;
                else if (genVisTauRecoStatus[gvtN] == 15)
                {
                    h_tauEff_reco->Fill(genVisTauEtas[gvtN], genVisTauPts[gvtN]);
                    h_tauEff_den->Fill(genVisTauEtas[gvtN], genVisTauPts[gvtN]);
                }
                else
                {
                    h_tauEff_den->Fill(genVisTauEtas[gvtN], genVisTauPts[gvtN]);
                }
            }
        }
    }

    chain.SetBranchStatus("*", true); //Reset all branch statuses to true

    h_elEff_reco->Sumw2();
    h_elEff_den->Sumw2();
    h_muEff_reco->Sumw2();
    h_muEff_den->Sumw2();
    h_phoEff_reco->Sumw2();
    h_phoEff_den->Sumw2();
    h_tauEff_reco->Sumw2();
    h_tauEff_den->Sumw2();

    //Now calculate the efficiencies
    //Divide option allows assymmetric, non-zero errors if efficiency is one with binomial errors
    h_elEff_reco->Divide(h_elEff_reco, h_elEff_den, 1.0, 1.0, "cl=0.683 b(1,1) mode");
    h_muEff_reco->Divide(h_muEff_reco, h_muEff_den, 1.0, 1.0, "cl=0.683 b(1,1) mode");
    h_tauEff_reco->Divide(h_tauEff_reco, h_tauEff_den, 1.0, 1.0, "cl=0.683 b(1,1) mode");
    h_phoEff_reco->Divide(h_phoEff_reco, h_phoEff_den, 1.0, 1.0, "cl=0.683 b(1,1) mode");

    if (h_elEff->GetEntries() == 0) //Passed histograms are empty, therefore we can just add our new efficiencies in
    {
        h_elEff->Add(h_elEff_reco);
        h_muEff->Add(h_muEff_reco);
        h_tauEff->Add(h_tauEff_reco);
        h_phoEff->Add(h_phoEff_reco);
    }
    else //There are already efficiencies in the passed histograms, therefore total overall efficiency is multiplicative
    {
        h_elEff->Multiply(h_elEff_reco);
        h_muEff->Multiply(h_muEff_reco);
        h_tauEff->Multiply(h_tauEff_reco);
        h_phoEff->Multiply(h_phoEff_reco);
    }

    std::cout << "...Done calculating object reco efficiencies for " << year << endl;
}


//Calculate the efficiencies chosen by the inc* parameters for each object in the analysis and save them to plots and a root file
void calcRecoEffs(TString outFilename)
{
    const int N_YEARS = 4;
    TString years[N_YEARS] = {"2015", "2016", "2017", "2018"};
    //const int N_YEARS = 1;
    //TString years[N_YEARS] = {"2015"};
    
    //Set up canvases and graphics options
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("4.2f");
    TCanvas* elCanv = new TCanvas("elCanv", "Electron Efficiencies", 1200, 800);
    TCanvas* muCanv = new TCanvas("muCanv", "Muon Efficiencies", 1200, 800);
    TCanvas* tauCanv = new TCanvas("tauCanv", "Tauh Efficiencies", 1200, 800);
    TCanvas* phoCanv = new TCanvas("phoCanv", "Photon Efficiencies", 1200, 800);

    if (N_YEARS >= 2 && N_YEARS % 2 == 0)
    {
        elCanv->Divide(2, N_YEARS/2);
        muCanv->Divide(2, N_YEARS/2);
        tauCanv->Divide(2, N_YEARS/2);
        phoCanv->Divide(2, N_YEARS/2);
    }
    else if (N_YEARS >= 2)
    {
        elCanv->Divide(2, N_YEARS/2 + 1);
        muCanv->Divide(2, N_YEARS/2 + 1);
        tauCanv->Divide(2, N_YEARS/2 + 1);
        phoCanv->Divide(2, N_YEARS/2 + 1);
    }

    //Create a file to write the histograms to
    TFile* outfile = new TFile(outFilename, "RECREATE");
    TString outStr;

    double etaBins_EG[6] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};
    TString etaBinLabels_EG[5] = {"[0, 0.8)", "[0.8, 1.4442)", "[1.4442, 1.566)", "[1.566, 2.0)", "[2.0, 2.5)"};
    double etaBins_mu[5] = {0, 0.9, 1.2, 2.1, 2.4};
    TString etaBinLabels_mu[4] = {"[0, 0.9)", "[0.9, 1.2)", "[1.2, 2.1)", "[2.1, 2.4)"};
    double etaBins_tau[4] = {0, 1.46, 1.558, 2.3};
    TString etaBinLabels_tau[3] = {"[0, 1.46)", "[1.46, 1.558)", "[1.558, 2.3)"};
    double ptBins_mu[6] = {18, 50, 100, 200, 500, 1500};
    double ptBins_EG[7] = {5, 50, 100, 200, 500, 1000, 4000};
    double ptBins_tau[6] = {18, 50, 100, 200, 500, 1000};

    //Since only using this code for reco now, this is overkill but keep format for ease
    TString effsStr = buildEffsStr(true, false, false);    

    for (int yrN = 0; yrN < N_YEARS; yrN++)
    {
        TH2F* h_elEff = new TH2F("h_elEff_" + years[yrN], years[yrN] + " Electron " + effsStr + " Efficiency;El |#eta|;El pt", 5, etaBins_EG, 6, ptBins_EG);
        TH2F* h_phoEff = new TH2F("h_phoEff_" + years[yrN], years[yrN] +  " Photon " + effsStr + " Efficiency;Pho |#eta|;Pho pt", 5, etaBins_EG, 6, ptBins_EG);
        TH2F* h_muEff = new TH2F("h_muEff_" + years[yrN], years[yrN] +  " Muon " + effsStr + " Efficiency;Mu |#eta|;Mu pt", 4, etaBins_mu, 5, ptBins_mu);
        TH2F* h_tauEff = new TH2F("h_tauEff_" + years[yrN], years[yrN] +  " Tau_h " + effsStr + " Efficiency;Tau |#eta|;Tau pt", 3, etaBins_tau, 5, ptBins_tau);
	
        h_elEff->Sumw2();
        h_muEff->Sumw2();
        h_phoEff->Sumw2();
        h_tauEff->Sumw2();

        incRecoEffs( h_elEff, h_muEff, h_tauEff, h_phoEff, years[yrN], effsStr);   
        
	//Set better eta bin labels
        for (int i = 0; i < 5; i++) //6 is the largest number of eta bins
        {
            h_elEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels_EG[i]);
            h_phoEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels_EG[i]);
            if (i < 4) //Only 4 mu bins
            h_muEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels_mu[i]);
            if (i < 3) //only 3 tau eta bins
            h_tauEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels_tau[i]);
        }

        //Now plot
        elCanv->cd(yrN+1);
        h_elEff->Draw("COLZ TEXTE");
        gPad->SetLogy(1);
        gPad->Modified();
        gPad->Update();
        muCanv->cd(yrN+1);
        h_muEff->Draw("COLZ TEXTE");
        gPad->SetLogy(1);
        gPad->Modified();
        gPad->Update();
        phoCanv->cd(yrN+1);
        h_phoEff->Draw("COLZ TEXTE");
        gPad->SetLogy(1);
        gPad->Modified();
        gPad->Update();
        tauCanv->cd(yrN+1);
        h_tauEff->Draw("COLZ TEXTE");
        gPad->SetLogy(1);
        gPad->Modified();
        gPad->Update();

        
        //Write the histograms to the output root file
        h_elEff->Write();
        h_muEff->Write();
        h_phoEff->Write();
        h_tauEff->Write();	    
    }

    //Save the output plots
    TString outPath = "../Plots/ObjEffs/";
    outStr = effsStr.ReplaceAll('+', '-') + ".png";
    elCanv->SaveAs(outPath + "elEff_" + outStr);
    muCanv->SaveAs(outPath + "muEff_" + outStr);
    phoCanv->SaveAs(outPath + "phoEff_" + outStr);
    tauCanv->SaveAs(outPath + "tauEff_" + outStr);   

    outfile->Close();
}


//Calculate the tau ID efficiencies corresponding to the working points used in signal channels
//Writes TEfficiency objects for each channel to the file specified by outFilename (file will be created or updated, not overwritten)
void calcTauIDEff(TString outFilename, TString year)
{
  cout << "Calculating tau ID efficiencies..." << endl;

    //Define our eff plots
    double etaBins_tau[4] = {0, 1.46, 1.558, 2.3};
    TString etaBinLabels_tau[3] = {"[0, 1.46)", "[1.46, 1.558)", "[1.558, 2.3)"};
    double ptBins_tau[6] = {18, 50, 100, 200, 500, 1000};
    TH2F* eff_ETau = new TH2F("tauIDeff_ETau_" + year, "Tau ID Efficiency: ETau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* eff_MuTau = new TH2F("tauIDeff_MuTau_" + year, "Tau ID Efficiency: MuTau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* eff_TauTau = new TH2F("tauIDeff_TauTau_" + year, "Tau ID Efficiency: TauTau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* eff_ETauDen = new TH2F("tauIDeff_ETauDen_" + year, "Tau ID Efficiency: ETau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* eff_MuTauDen = new TH2F("tauIDeff_MuTauDen_" + year, "Tau ID Efficiency: MuTau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);
    TH2F* eff_TauTauDen = new TH2F("tauIDeff_TauTauDen_" + year, "Tau ID Efficiency: TauTau "+year+";Tau eta; Tau pT", 3, etaBins_tau, 5, ptBins_tau);

    //Define our data source
    TChain chain("Events", "MC Background Files");
    getTreesMCasChain(chain, year);
    
    //Read only branches we need
    int nTau;
    UChar_t genPartFlav[50];
    int id_vs_e[50];
    int id_vs_mu[50];
    int id_vs_jet[50];
    float pt[50];
    float eta[50];
    chain.SetBranchStatus("*", false);

    chain.SetBranchStatus("nTau", true);
    chain.SetBranchStatus("Tau_genPartFlav", true);
    chain.SetBranchStatus("Tau_idDeepTau2017v2p1VSe", true);
    chain.SetBranchStatus("Tau_idDeepTau2017v2p1VSjet", true);
    chain.SetBranchStatus("Tau_idDeepTau2017v2p1VSmu", true);
    chain.SetBranchStatus("Tau_pt", true);
    chain.SetBranchStatus("Tau_eta", true);

    chain.SetBranchAddress("nTau", &nTau);
    chain.SetBranchAddress("Tau_genPartFlav", &genPartFlav);
    chain.SetBranchAddress("Tau_idDeepTau2017v2p1VSe", &id_vs_e);
    chain.SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", &id_vs_jet);
    chain.SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", &id_vs_mu);
    chain.SetBranchAddress("Tau_pt", &pt);
    chain.SetBranchAddress("Tau_eta", &eta);


    for (int eN = 1; eN < chain.GetEntries(); eN++)
    {
        chain.GetEntry(eN);
	if (eN % 250000 == 0)
	  cout << "Processing entry " << eN << "/" << chain.GetEntries() << endl;

        //Check each tau for for ID efficiency for each channels WPs
        for (int tauN = 0; tauN < nTau; tauN++)
        {
	  if (genPartFlav[tauN] != 5)
	    continue;
	  
            //ETau: tight vs e, tight vs mu, tight vs jet
            if(pt[tauN] > 20 && abs(eta[tauN]) < 2.3 && (32 & id_vs_e[tauN]) && (8 & id_vs_mu[tauN]) && (32 & id_vs_jet[tauN]) )
	      {
		eff_ETau->Fill(abs(eta[tauN]), pt[tauN]);
		eff_ETauDen->Fill(abs(eta[tauN]), pt[tauN]);
	      }
	    else if (pt[tauN] > 20 && abs(eta[tauN]) < 2.3 )
                eff_ETauDen->Fill(abs(eta[tauN]), pt[tauN]);

            //MuTau: VVLoose vs e, tight vs mu, tight vs jet
            if(pt[tauN] > 20 && abs(eta[tauN]) < 2.3 && (2 & id_vs_e[tauN]) && (8 & id_vs_mu[tauN]) && (32 & id_vs_jet[tauN]) )
	      {
                eff_MuTau->Fill(abs(eta[tauN]), pt[tauN]);
		eff_MuTauDen->Fill(abs(eta[tauN]), pt[tauN]);
	      }
            else if (pt[tauN] > 20 && abs(eta[tauN]) < 2.3 )
                eff_MuTauDen->Fill(abs(eta[tauN]), pt[tauN]);

            //TauTau: VVLoose vs e, tight vs mu, medium vs jet
            if(pt[tauN] > 40 && abs(eta[tauN]) < 2.1 && (2 & id_vs_e[tauN]) && (8 & id_vs_mu[tauN]) && (16 & id_vs_jet[tauN]) )
	      {
                eff_TauTau->Fill(abs(eta[tauN]), pt[tauN]);
		eff_TauTauDen->Fill(abs(eta[tauN]), pt[tauN]);
	      }
            else if (pt[tauN] > 40 && abs(eta[tauN]) < 2.1) 
                eff_TauTauDen->Fill(abs(eta[tauN]), pt[tauN]);
        }
    }
    
    chain.SetBranchStatus("*", true);

    //Calculate efficiencies and uncertainties
    eff_ETau->Sumw2();
    eff_MuTau->Sumw2();
    eff_TauTau->Sumw2();
    eff_ETauDen->Sumw2();
    eff_MuTauDen->Sumw2();
    eff_TauTauDen->Sumw2();

    //Divide option allows assymmetric, non-zero errors if efficiency is one with binomial errors
    eff_ETau->Divide(eff_ETau, eff_ETauDen, 1.0, 1.0, "cl=0.683 b(1,1) mode");
    eff_MuTau->Divide(eff_MuTau, eff_MuTauDen, 1.0, 1.0, "cl=0.683 b(1,1) mode");
    eff_TauTau->Divide(eff_TauTau, eff_TauTauDen, 1.0, 1.0, "cl=0.683 b(1,1) mode");

    eff_ETau->SetMaximum(1.0); //Ensure color scale goes from 0.0-1.0
    eff_MuTau->SetMaximum(1.0);
    eff_TauTau->SetMaximum(1.0);

    //Plot our efficiencies and save to a .png and ROOT file
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("4.2f");

    TCanvas* canv = new TCanvas("tauIDcanv", year + " Tau ID Efficiencies", 1200, 600);
    canv->Divide(3,1);
    
    canv->cd(1);
    eff_ETau->Draw("COLZ TEXTE");
    gPad->Modified();
    gPad->Update();
    canv->cd(2);
    eff_MuTau->Draw("COLZ TEXTE");
    gPad->Modified();
    gPad->Update();
    canv->cd(3);
    eff_TauTau->Draw("COLZ TEXTE");
    gPad->Modified();
    gPad->Update();

    canv->SaveAs("../Plots/tauIDEffs_" + year + ".png");

    TFile* outfile = TFile::Open(outFilename, "UPDATE");
    eff_ETau->Write();
    eff_MuTau->Write();
    eff_TauTau->Write();
    outfile->Close();

    cout << "...Done calculating tau ID efficiencies" << endl;
}
