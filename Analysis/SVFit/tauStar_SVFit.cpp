//Script to reconstruct the Z peak from tautau events using SVFit
//https://github.com/SVfit/ClassicSVfit/blob/master/


#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"

#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TMatrixD.h"

#include <iostream>

using namespace classic_svFit;

int main(int argc, char* argv[])
{
    const int N_FILES = 1;
    TString fileNames[N_FILES] = {"Taustar_m500"};
    TString baseDir = "../Data/ExcitedTau_29032023/";

    //const int N_FILES = 17;
    //TString fileNames[N_FILES] = {"DYJetsToLL_M10to50", "DYJetsToLL_M50", "ST_s_channel", "ST_tW_antitop", "ST_tW_top", "ST_t_channel_antitop", "ST_t_channel_top", "TTGamma_Dilept", "TTGamma_SingleLept", "TTTo2L2Nu", "TTToSemiLeptonic", "WGToLNuG", "WJetsToLNu", "WW", "WZ", "ZGToLLG", "ZZ" };
    //TString baseDir = "root://cmsxrootd.fnal.gov//store/user/";
    
    std::cout << "Running SVFit... " << std::endl;
    runSVFit(fileNames, N_FILES, baseDir);

    return 0;
}


void runSVFit(TString filenames[], int nFiles, TString baseDir)
{
    TString years[4] = {"2015", "2016", "2017", "2018"};

    ClassicSVfit svFitAlgo(1);//arg is verbosity level

    for (int fN = 0; fN < nFiles; fN++)
    {
        std::cout << "... over process " << fN+1 << "/" << nFiles << "..." << std::endl;
        for (int yrN = 0; yrN < 4; yrN++)
        {
            char filepath[100];
            sprintf(filepath, "%s%s_%s.root", baseDir.Data(), mcNames[fN].Data(), year.Data())
            TFile* file = TFile::Open(filepath, "UPDATE");
            TTree* tree = (TTree*) file->Get("Events");

            //Variables to readout tree
            int ETau_HavePair;
            int ETau_TauIdx;
            int ETau_EIdx;
            int MuTau_HavePair;
            int MuTau_TauIdx;
            int MuTau_MuIdx;
            int TauTau_HavePair;
            int TauTau_Tau0Idx;
            int TauTau_Tau1Idx;
            float tau_pt[50];
            float tau_eta[50];
            float tau_phi[50];
            float tau_mass[50];
            int tau_decayMode[50];
            float el_pt[50];
            float el_eta[50];
            float el_phi[50];
            float el_mass[50];
            float mu_pt[50];
            float mu_eta[50];
            float mu_phi[50];
            float mu_mass[50];
            float met_covXX;
            float met_covXY;
            float met_covYY;
            float met_sumEt;
            float met_phi;

            tree.SetBranchStatus("*", false);
            tree.SetBranchStatus("ETau_HavePair", true);
            tree.SetBranchStatus("ETau_TauIdx", true);
            tree.SetBranchStatus("ETau_EIdx", true);
            tree.SetBranchStatus("MuTau_HavePair", true);
            tree.SetBranchStatus("MuTau_TauIdx", true);
            tree.SetBranchStatus("MuTau_MuIdx", true);
            tree.SetBranchStatus("TauTau_HavePair", true);
            tree.SetBranchStatus("TauTau_Tau0Idx", true);
            tree.SetBranchStatus("TauTau_Tau1Idx", true);
            tree.SetBranchStatus("Tau_pt", true);
            tree.SetBranchStatus("Tau_eta", true);
            tree.SetBranchStatus("Tau_phi", true);
            tree.SetBranchStatus("Tau_mass", true);
            tree.SetBranchStatus("Tau_decayMode", true);
            tree.SetBranchStatus("Electron_pt", true);
            tree.SetBranchStatus("Electron_eta", true);
            tree.SetBranchStatus("Electron_phi", true);
            tree.SetBranchStatus("Electron_mass", true);
            tree.SetBranchStatus("Muon_pt", true);
            tree.SetBranchStatus("Muon_eta", true);
            tree.SetBranchStatus("Muon_phi", true);
            tree.SetBranchStatus("Muon_mass", true);
            tree.SetBranchStatus("MEX_covXX", true);
            tree.SetBranchStatus("MEX_covXY", true);
            tree.SetBranchStatus("MEX_covYY", true);
            tree.SetBranchStatus("MET_sumEt", true);
            tree.SetBranchStatus("MET_phi", true);

            tree.SetBranchAddress("ETau_HavePair", &ETau_HavePair);
            tree.SetBranchAddress("ETau_TauIdx", &ETau_TauIdx);
            tree.SetBranchAddress("ETau_EIdx", &ETau_EIdx);
            tree.SetBranchAddress("MuTau_HavePair", &MuTau_HavePair);
            tree.SetBranchAddress("MuTau_TauIdx", &MuTau_TauIdx);
            tree.SetBranchAddress("MuTau_MuIdx", &MuTau_MuIdx);
            tree.SetBranchAddress("TauTau_HavePair", &TauTau_HavePair);
            tree.SetBranchAddress("TauTau_Tau0Idx", &TauTau_Tau0Idx);
            tree.SetBranchAddress("TauTau_Tau1Idx", &TauTau_Tau1Idx);
            tree.SetBranchAddress("Tau_pt", tau_pt );
            tree.SetBranchAddress("Tau_eta", tau_eta );
            tree.SetBranchAddress("Tau_phi", tau_phi );
            tree.SetBranchAddress("Tau_mass", tau_mass );
            tree.SetBranchAddress("Tau_decayMode", tau_decayMode );
            tree.SetBranchAddress("Electron_pt", tau_pt );
            tree.SetBranchAddress("Electron_eta", tau_eta );
            tree.SetBranchAddress("Electron_phi", tau_phi );
            tree.SetBranchAddress("Electron_mass", tau_mass );
            tree.SetBranchAddress("Muon_pt", tau_pt );
            tree.SetBranchAddress("Muon_eta", tau_eta );
            tree.SetBranchAddress("Muon_phi", tau_phi );
            tree.SetBranchAddress("Muon_mass", tau_mass );
            tree.SetBranchAddress("MET_sumEt", &met_sumEt);
            tree.SetBranchAddress("MET_phi", &met_phi);

            float mass;
            float massErr;
            float transverseMass;
            float transverseMassErr;

            TBranch *b_mass = tree->Branch("SVFit_TauPairMass", &mass, "SVFit_TauPairMass/F");
            TBranch *b_massErr = tree->Branch("SVFit_TauPairMassErr", &massErr, "SVFit_TauPairMassErr/F");
            TBranch *b_transverseMass = tree->Branch("SVFit_TauPairMT", &transverseMass, "SVFit_TauPairMT/F");
            TBranch *b_transverseMassErr = tree->Branch("SVFit_TauPairMTErr", &transverseMassErr, "SVFit_TauPairMTErr/F");

            std::vector<MeasuredTauLepton> tausToFit;
            for (int eN = 0; eN < tree.GetEntries(); eN++)
            {
                tree.GetEntry(eN);

                TMatrixD covMET(2, 2);
                covMET[0][0] = met_covXX;
                covMET[1][0] = met_covXY;
                covMET[0][1] = met_covXY;
                covMET[1][1] = met_covYY;

                if (ETau_HavePair)
                {
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToElecDecay, el_pt[ETau_EIdx], el_eta[ETau_EIdx], el_phi[ETau_EIdx], el_mass[ETau_EIdx]));
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToHadDecay, tau_pt[ETau_TauIdx], tau_eta[ETau_TauIdx], tau_phi[ETau_TauIdx], tau_mass[ETau_TauIdx], tau_decayMode[ETau_TauIdx]));
                    svFitAlgo.addLogM_fixed(true, 4); //4 from slide 3 of https://indico.cern.ch/event/684622/contributions/2807248/attachments/1575090/2487044/presentation_tmuller.pdf
                }
                else if (MuTau_HavePair)
                {
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToMuDecay, mu_pt[MuTau_MuIdx], mu_eta[MuTau_MuIdx], mu_phi[MuTau_MuIdx], mu_mass[MuTau_MuIdx]));
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToHadDecay, tau_pt[ETau_TauIdx], tau_eta[ETau_TauIdx], tau_phi[ETau_TauIdx], tau_mass[ETau_TauIdx], tau_decayMode[ETau_TauIdx]));
                    svFitAlgo.addLogM_fixed(true, 4);
                }
                else if (TauTau_HavePair)
                {
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToHadDecay, tau_pt[TauTau_Tau0Idx], tau_eta[TauTau_Tau0Idx], tau_phi[TauTau_Tau0Idx], tau_mass[TauTau_Tau0Idx], tau_decayMode[TauTau_Tau0Idx]));
                    tausToFit.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToHadDecay, tau_pt[TauTau_Tau0Idx], tau_eta[TauTau_Tau0Idx], tau_phi[TauTau_Tau0Idx], tau_mass[TauTau_Tau0Idx], tau_decayMode[TauTau_Tau0Idx]));
                    svFitAlgo.addLogM_fixed(true, 5);
                }

                svFitAlgo.setLikelihoodFileName("svFitLikelihood_"+filenames[fN]+"_"+year+".root");
                svFitAlgo.integrate(tausToFit, met_sumEt*TMath::cos(met_phi), met_sumEt*TMath::sin(met_phi), covMet);

                if (svFitAlgo.isValidSolution())
                {
                    mass = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass();
                    massErr = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMassErr();
                    transverseMass = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getTransverseMass();
                    transverseMassErr = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getTransverseMassErr();
                }
                else
                {
                    mass = -99;
                    massErr = -99;
                    transverseMass = -99;
                    transverseMassErr = -99;
                }

                b_mass->Fill();
                b_massErr->Fill();
                b_transverseMass->Fill();
                b_transverseMassErr->Fill();
            } //End entry
            
            tree->Write("", TObject::kOverwrite);
        } //End year
    } //End filebase (process)
} //End function

