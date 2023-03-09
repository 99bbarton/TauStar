//Calculate the trigger+id efficiency for electrons, photons, and tauhs as a function of eta and pt


#include "TString.h"
#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TCut.h"


const int N_FILES = 3;



//Assign files to a TChain for easy access
void getTreesMCasChain(TChain& chain, TString year)
{
  //TString mcNames[N_FILES] = {"DYJetsToLL_M10to50", "DYJetsToLL_M50", "ST_s_channel", "ST_tW_antitop", "ST_tW_top", "ST_t_channel_antitop", "ST_t_channel_top", "TTGamma_Dilept", "TTGamma_SingleLept", "TTTo2L2Nu", "TTToSemiLeptonic", "WGToLNuG", "WJetsToLNu", "WW", "WZ", "ZGToLLG", "ZZ" };
  //TString baseDir = "root://cmsxrootd.fnal.gov//store/user/fjensen/excitedTau_22022023/";
  TString mcNames[N_FILES] = {"recoEffs_sigMC_500", "recoEffs_sigMC_2500", "recoEffs_sigMC_5000"};
    TString baseDir = "../Data/";
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
        cout << "\nReco, ID, and trig efficiencies are all excluded. Exiting..." << endl;
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
void incRecoEffs(TH2F* h_elEff, TH2F* h_muEff, TH2F* h_tauEff, TH2F* h_phoEff, TString year, TString effsStr, int nEtaBins, double etaBins[])
{
    /*Whether each relevant gen particle is matched can be found in the branch "Eff_recoPartsStatus"
    If the status is a positive definite value, that gen particle matched to a reco'd particle with abs(pdgID) = that value
    If the value is instead negative, that gen particle did NOT match to a reco'd particle with abs(pdgID) = abs(that value)
    Any other value means the gen particle was not of the type/status we care about */

    cout << "\nCalculating object reco efficiencies for " << year << "..." << endl;

    TH2F* h_elEff_reco = new TH2F("h_elEff_rec_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_phoEff_reco = new TH2F("h_phoEff_reco_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_muEff_reco = new TH2F("h_muEff_reco_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
    //TH2F* h_tauEff_reco = TH2F("h_tauEff_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_elEff_den = new TH2F("h_elEff_den_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_phoEff_den = new TH2F("h_phoEff_den_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_muEff_den = new TH2F("h_muEff_den_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
    //TH2F* h_tauEff_den = TH2F("h_tauEff_den_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", nEtaBins, etaBins, 20, 0, 2000);

    TChain chain("Events", "MC Background Files");
    getTreesMCasChain(chain, year);

    int nGenParts;
    int genPartRecoStatus[500]; //Arrays must be equal or longer in length than arrays in tree branches
    float genPartEtas[500];
    float genPartPts[500];

    //Only read the branches of the trees we care about for efficiency
    chain.SetBranchStatus("*", false);
    chain.SetBranchStatus("nGenPart", true);
    chain.SetBranchStatus("Eff_recoPartsStatus", true);
    chain.SetBranchStatus("GenPart_eta", true);
    chain.SetBranchStatus("GenPart_pt", true);

    chain.SetBranchAddress("nGenPart", &nGenParts);
    chain.SetBranchAddress("Eff_recoPartsStatus", &genPartRecoStatus);
    chain.SetBranchAddress("GenPart_eta", &genPartEtas);
    chain.SetBranchAddress("GenPart_pt", &genPartPts);

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
    }

    h_elEff_reco->Sumw2();
    h_elEff_den->Sumw2();
    h_muEff_reco->Sumw2();
    h_muEff_den->Sumw2();
    h_phoEff_reco->Sumw2();
    h_phoEff_den->Sumw2();
    //h_tauEff_reco->Sumw2();
    //h_tauEff_den->Sumw2();

    //Now calculated the efficiencies
    h_elEff_reco->Divide(h_elEff_den);
    h_muEff_reco->Divide(h_muEff_den);
    //h_tauEff_reco->Divide(h_tauEff_den);
    h_phoEff_reco->Divide(h_phoEff_den);

    if (h_elEff->GetEntries() == 0) //Passed histograms are empty, therefore we can just add our new efficiencies in
    {
        h_elEff->Add(h_elEff_reco);
        h_muEff->Add(h_muEff_reco);
        //h_tauEff->Add(h_tauEff_reco);
        h_phoEff->Add(h_phoEff_reco);
    }
    else //There are already efficiencies in the passed histograms, therefore total overall efficiency is multiplicative
    {
        h_elEff->Multiply(h_elEff_reco);
        h_muEff->Multiply(h_muEff_reco);
        //h_tauEff->Multiply(h_tauEff_reco);
        h_phoEff->Multiply(h_phoEff_reco);
    }

    cout << "...Done calculating object reco efficiencies for " << year << endl;
}


//Calculate the efficiencies chosen by the inc* parameters for each object in the analysis and save them to plots and a root file
void calcObjEffs(TString outFilename, bool incReco=true, bool incID=true, bool incTrig=true)
{
    //const int N_YEARS = 4;
    //TString years[N_YEARS] = {"2015", "2016", "2017", "2018"};
    const int N_YEARS = 1;
    TString years[N_YEARS] = {"2015"};
    
    //Set up canvases and graphics options
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("4.2f");
    TCanvas* elCanv = new TCanvas("elCanv", "Electron Efficiencies", 1200, 800);
    TCanvas* muCanv = new TCanvas("muCanv", "Muon Efficiencies", 1200, 800);
    //TCanvas* tauCanv = TCanvas("tauCanv", "Tauh Efficiencies", 1200, 800);
    TCanvas* phoCanv = new TCanvas("phoCanv", "Photon Efficiencies", 1200, 800);

    if (N_YEARS >= 2 && N_YEARS % 2 == 0)
    {
        elCanv->Divide(2, N_YEARS/2);
        muCanv->Divide(2, N_YEARS/2);
        //tauCanv->Divide(2, N_YEARS/2);
        phoCanv->Divide(2, N_YEARS/2);
    }
    else if (N_YEARS >= 2)
    {
        elCanv->Divide(2, N_YEARS/2 + 1);
        muCanv->Divide(2, N_YEARS/2 + 1);
        //tauCanv->Divide(2, N_YEARS/2 + 1);
        phoCanv->Divide(2, N_YEARS/2 + 1);
    }

    //Create a file to write the histograms to
    TFile* outfile = new TFile(outFilename, "RECREATE");
    TString outStr;

    const int nEtaBins = 5;
    double etaBins[nEtaBins + 1] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};
    TString etaBinLabels[nEtaBins] = {"[0, 0.8)", "[0.8, 1.4442)", "[1.4442, 1.566)", "[1.566, 2.0)", "[2.0, 2.5)"};


    TString effsStr = buildEffsStr(incReco, incID, incTrig);    

    for (int yrN = 0; yrN < N_YEARS; yrN++)
    {
        TH2F* h_elEff = new TH2F("h_elEff_" + years[yrN], years[yrN] + " Electron " + effsStr + " Efficiency;El |#eta|;El pt", nEtaBins, etaBins, 20, 0, 2000);
        TH2F* h_phoEff = new TH2F("h_phoEff_" + years[yrN], years[yrN] +  " Photon " + effsStr + " Efficiency;Pho |#eta|;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
        TH2F* h_muEff = new TH2F("h_muEff_" + years[yrN], years[yrN] +  " Muon " + effsStr + " Efficiency;Mu |#eta|;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
        TH2F* h_tauEff = new TH2F("h_tauEff_" + years[yrN], years[yrN] +  " Tau_h " + effsStr + " Efficiency;Tau |#eta|;Tau pt", nEtaBins, etaBins, 20, 0, 2000);
	
	h_elEff->Sumw2();
	h_muEff->Sumw2();
	h_phoEff->Sumw2();
        //h_tauEff->Sumw2();

        if (incReco)
            incRecoEffs( h_elEff, h_muEff, h_tauEff, h_phoEff, years[yrN], effsStr, nEtaBins, etaBins);   
        
	//Set better eta bin labels
	for (int i = 0; i < nEtaBins; i++)
	  {
	    h_elEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels[i]);
	    h_muEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels[i]);
	    h_phoEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels[i]);
	    //h_tauEff->GetXaxis()->SetBinLabel(i+1, etaBinLabels[i]);
	  }

        //Now plot
        elCanv->cd(yrN+1);
        h_elEff->Draw("COLZ TEXTE");
        gPad->Modified();
	gPad->Update();
        muCanv->cd(yrN+1);
        h_muEff->Draw("COLZ TEXTE");
        gPad->Modified();
        gPad->Update();
        phoCanv->cd(yrN+1);
        h_phoEff->Draw("COLZ TEXTE");
        gPad->Modified();
        gPad->Update();
        //tauCanv->cd(yrN);
        //h_tauEff->Draw("COLZ TEXT");
        //gPad->Modified();
        //gPad->Update();

        //Write the histograms to the output root file
        h_elEff->Write();
        h_muEff->Write();
        h_phoEff->Write();
        //h_tauEff->Write();	    
    }

    //Save the output plots
    TString outPath = "../Plots/ObjEffs/";
    outStr = effsStr.ReplaceAll('+', '-') + ".png";
    elCanv->SaveAs(outPath + "elEff_" + outStr);
    muCanv->SaveAs(outPath + "muEff_" + outStr);
    phoCanv->SaveAs(outPath + "phoEff_" + outStr);
    //tauCanv->SaveAs(outPath + "tauEff_" + outStr);   

    outfile->Close();
}
