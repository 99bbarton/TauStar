//Calculate the trigger+id efficiency for electrons, photons, and tauhs as a function of eta and pt


#include <TString>
#include <TFile>
#include <TH2F>
#include <TCanvas>
#include <TTree>
#include <TCut>

using namespace std;

//Assign files to a TChain for easy access
void getTreesMCasChain(TChain* chain, TString year)
{
    TString mcNames[17] = {"DYJetsToLLM10", "DYJetsToLL_M50", "ST_s_channel", "ST_tW_antitop", "ST_tW_top_2018", "ST_t_channel_antitop", "ST_t_channel_top", "TTGamma_Dilept", "TTGamma_SingleLept", "TTTo2L2Nu", "TTToSemiLeptonic", "WGToLNuG", "WJetsToLNu", "WW", "WZ", "ZGToLLG", "ZZ" };
    TString baseDir = "root://cmsxrootd.fnal.gov//store/user/fjensen/excitedTau_17022023/";
    
    char filepath[100];

    for (int fN = 0; fN < N_FILES; fN++)
    {   
        sprintf(filepath, "%s/%s_%s.root", baseDir.Data(), mcNames.Data(), year.Data());
        chain->Add(filepath);
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
            incEffsStr += "+" 
        incEffsStr += "Reco"
    }
    if (incID) 
    {
        if (incEffsStr != "") 
            incEffsStr += "+" 
        incEffsStr += "ID"
    }
    if (incTrig) 
    {
        if (incEffsStr != "") 
            incEffsStr += "+" 
        incEffsStr += "Trig"
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

    TH2F* h_elEff_reco = TH2F("h_elEff_rec_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_phoEff_reco = TH2F("h_phoEff_reco_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_muEff_reco = TH2F("h_muEff_reco_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
    //TH2F* h_tauEff_reco = TH2F("h_tauEff_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_elEff_den = TH2F("h_elEff_den_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_phoEff_den = TH2F("h_phoEff_den_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
    TH2F* h_muEff_den = TH2F("h_muEff_den_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
    //TH2F* h_tauEff_den = TH2F("h_tauEff_den_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", nEtaBins, etaBins, 20, 0, 2000);

    TChain* chain = new TChain("Events", "MC Background Files");
    getTreesMCasChain(chain, years[yrN]);
    
    int nGenParts;
    int* genPartRecoStatus;
    float* genPartEtas;
    float* genPartPts;
    chain->SetBranchAddress("nGenPart", &nGenParts);
    chain->SetBranchAddress("Eff_recoPartsStatus", &genPartRecoStatus);
    chain->SetBranchAddress("GenPart_eta", &genPartEtas);
    chain->SetBranchAddress("GenPart_pt", &genPartPts);

    //Fill the appropriate numerator and denominator histograms with eta/pt of matched and non-matched relevant gen particles
    for (int eN = 0; eN < chain->GetEntries(); eN++)
    {
        chain->GetEntry(eN);
        for (int gpN = 0; gpN < nGenParts; gpN++)
        {
            //Electrons
            if (genPartRecoStatus[gpN] == 11)
            {
                h_elEff->Fill(genPartEtas[gpN], genPartPts[gpN]);
                h_elEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -11)
            {
                h_elEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
            //Muons
            else if (genPartRecoStatus[gpN] == 13)
            {
                h_muEff->Fill(genPartEtas[gpN], genPartPts[gpN]);
                h_muEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -13)
            {
                h_muEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
            //Photons
            else if (genPartRecoStatus[gpN] == 22)
            {
                h_PhoEff->Fill(genPartEtas[gpN], genPartPts[gpN]);
                h_PhoEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
            else if (genPartRecoStatus[gpN] == -22)
            {
                h_PhoEff_den->Fill(genPartEtas[gpN], genPartPts[gpN]);
            }  
        }
    }

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
}


//Calculate the efficiencies chosen by the inc* parameters for each object in the analysis and save them to plots and a root file
void calcObjEffs(TString outFilename, bool incReco=true, bool incID=true, bool incTrig=true)
{
    const int N_YEARS = 4;
    TString years[N_YEARS] = {"2015", "2016", "2017", "2018"};
    TCanvas* elCanv = TCanvas("elCanv", 1200, 800);
    TCanvas* muCanv = TCanvas("muCanv", 1200, 800);
    //TCanvas* tauCanv = TCanvas("tauCanv", 1200, 800);
    TCanvas* phoCanv = TCanvas("phoCanv", 1200, 800);
    if (N_YEARS % 2 == 0)
    {
        elCanv->Divide(2, N_YEARS/2);
        muCanv->Divide(2, N_YEARS/2);
        //tauCanv->Divide(2, N_YEARS/2);
        phoCanv->Divide(2, N_YEARS/2);
    }
    else
    {
        elCanv->Divide(2, N_YEARS/2 + 1);
        muCanv->Divide(2, N_YEARS/2 + 1);
        //tauCanv->Divide(2, N_YEARS/2 + 1);
        phoCanv->Divide(2, N_YEARS/2 + 1);
    }

    TFile* outfile = new TFile(outfileName, "RECREATE");

    int nEtaBins = 5;
    double etaBins[nEtaBins + 1] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};

    TString effsStr = buildEffsStr(incReco, incID, incTrig);    

    for (int yrN = 0; yrN < N_YEARS; yrN++)
    {
        TH2F* h_elEff = TH2F("h_elEff_" + year, "Electron " + effsStr + " Efficiency;El eta;El pt", nEtaBins, etaBins, 20, 0, 2000);
        TH2F* h_phoEff = TH2F("h_phoEff_" + year, "Photon " + effsStr + " Efficiency;Pho eta;Pho pt", nEtaBins, etaBins, 20, 0, 2000);
        TH2F* h_muEff = TH2F("h_muEff_" + year, "Muon " + effsStr + " Efficiency;Mu eta;Mu pt", nEtaBins, etaBins, 20, 0, 2000);
        //TH2F* h_tauEff = TH2F("h_tauEff_" + year, "Tau_h " + effsStr + " Efficiency;Tau eta;Tau pt", nEtaBins, etaBins, 20, 0, 2000);

        if (incReco)
            incRecoEffs( h_elEff, h_muEff, h_tauEff, h_phoEff, year, effsStr, nEtaBins, etaBins);   
        
        //Now plot
        elCanv->cd(yrN);
        h_elEff->Draw("COLZ TEXT");
        muCanv->cd(yrN);
        h_muEff->Draw("COLZ TEXT");
        phoCanv->cd(yrN);
        h_phoEff->Draw("COLZ TEXT");
        //tauCanv->cd(yrN);
        //h_tauEff->Draw("COLZ TEXT");

        //Write the histograms to the output root file
        h_elEff->Write();
        h_muEff->Write();
        h_phoEff->Write();
        //h_tauEff->Write();

        //Clear out the histograms in preparation for the next year
        h_elEff->Clear();
        h_muEff->Clear();
        h_phoEff->Clear();
        //h_tauEff->Clear();
    }

    //Save the output plots
    TString outPath = "./"
    TString outStr = effStr.ReplaceAll('+', '-') + "_" + year + ".png";
    elCanv->SaveAs(outPath + "elEff_" + outStr);
    muCanv->SaveAs(outPath + "muEff_" + outStr);
    phoCanv->SaveAs(outPath + "phoEff_" + outStr);
    tauCanv->SaveAs(outPath + "tauEff_" + outStr);   

    outfile->Close();
}