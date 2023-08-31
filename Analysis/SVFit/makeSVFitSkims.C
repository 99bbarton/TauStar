


void makeSVFitSkims()
{
    const int N_FILES = 2;
    TString filenames[N_FILES] = {"DYJetsToLL_M50", "ZGToLLG"};
    //TString filenames[N_FILES] = {"DYJetsToLL_M10to50", "DYJetsToLL_M50", "ST_s_channel", "ST_tW_antitop", "ST_tW_top", "ST_t_channel_antitop", "ST_t_channel_top", "TTGamma_Dilept", "TTGamma_SingleLept", "TTTo2L2Nu", "TTToSemiLeptonic", "WGToLNuG", "WJetsToLNu", "WW", "WZ", "ZGToLLG", "ZZ" };
    TString inDir = "root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_22022023/";
    TString outDir = "/uscms_data/d3/bbarton/CMSSW_10_6_27/src/Data/";
    const int N_YEARS = 4;
    TString years[N_YEARS] = {"2015", "2016", "2017", "2018"};

    TCut cuts_ETau = "(ETau_HavePair && ETau_Mass >= 25 && ETau_Mass <= 200 && Electron_genPartFlav[ETau_EIdx]==15 && Tau_genPartFlav[ETau_TauIdx]==15)";
    TCut cuts_MuTau = "(MuTau_HavePair && MuTau_Mass >= 25 && MuTau_Mass <= 200 && Muon_genPartFlav[MuTau_MuIdx]==15 && Tau_genPartFlav[MuTau_TauIdx]==15)";
    TCut cuts_TauTau = "(TauTau_HavePair && TauTau_Mass >= 25 && TauTau_Mass <= 200 && Tau_genPartFlav[TauTau_Tau0Idx]==15 && Tau_genPartFlav[TauTau_Tau1Idx]==15)";
    TCut cuts = cuts_ETau + " || " + cuts_MuTau + " || " + cuts_TauTau;

    for (int yrN = 0; yrN < N_YEARS; yrN++)
    {
        for (int fN = 0; fN < N_FILES; fN++)
        {
            char inPath[100];
            sprintf(inPath, "%s%s_%s.root", inDir.Data(), filenames[fN].Data(), years[yrN].Data());
            TFile* inFile = TFile::Open(inPath, "READ");
            TTree* inTree = (TTree*) file->Get("Events");

            inTree->SetBranchStatus("*", false);
            inTree->SetBranchStatus("ETau_HavePair", true);
            inTree->SetBranchStatus("ETau_TauIdx", true);
            inTree->SetBranchStatus("ETau_EIdx", true);
            inTree->SetBranchStatus("MuTau_HavePair", true);
            inTree->SetBranchStatus("MuTau_TauIdx", true);
            inTree->SetBranchStatus("MuTau_MuIdx", true);
            inTree->SetBranchStatus("TauTau_HavePair", true);
            inTree->SetBranchStatus("TauTau_Tau0Idx", true);
            inTree->SetBranchStatus("TauTau_Tau1Idx", true);
            inTree->SetBranchStatus("Tau_pt", true);
            inTree->SetBranchStatus("Tau_eta", true);
            inTree->SetBranchStatus("Tau_phi", true);
            inTree->SetBranchStatus("Tau_mass", true);
            inTree->SetBranchStatus("Tau_decayMode", true);
            inTree->SetBranchStatus("Electron_pt", true);
            inTree->SetBranchStatus("Electron_eta", true);
            inTree->SetBranchStatus("Electron_phi", true);
            inTree->SetBranchStatus("Electron_mass", true);
            inTree->SetBranchStatus("Electron_genPartFlav", true);
            inTree->SetBranchStatus("Muon_pt", true);
            inTree->SetBranchStatus("Muon_eta", true);
            inTree->SetBranchStatus("Muon_phi", true);
            inTree->SetBranchStatus("Muon_mass", true);
            inTree->SetBranchStatus("Muon_genPartFlav", true);
            inTree->SetBranchStatus("MET_covXX", true);
            inTree->SetBranchStatus("MET_covXY", true);
            inTree->SetBranchStatus("MET_covYY", true);
            inTree->SetBranchStatus("MET_pt", true);
            inTree->SetBranchStatus("MET_phi", true);
            inTree->SetBranchStatus("ETau_Mass", true);
            inTree->SetBranchStatus("MuTau_Mass", true);
            inTree->SetBranchStatus("TauTau_Mass", true);
            inTree->SetBranchStatus("Tau_genPartFlav", true);

            char outPath[100];
            sprintf(outPath, "%s%s_%s_SVFitSkim.root", outDir.Data(), filenames[fN].Data(), years[yrN].Data());
            TFile* outFile = TFile::Open(outPath, "RECREATE");
            TTree* outTree = inTree->CopyTree(cuts);
            outFile->Write();

            inTree->SetBranchStatus("*", true);
        }//End file
    }//End year
    
    
}