//A modified version of https://github.com/fojensen/nanoAOD-tools/blob/TauTauGamma/analysis/finalYieldsList.c
// to produce a .csv file with the final event yields of each background process


#include <TFile.h>
#include <TH1D.h>
#include <iostream>
#include <iomanip>

void runPoint(TString process, TString channel)
{
    double x, xerr;

    TString channel_;
    if (channel=="ETau") channel_="ch1";
    if (channel=="MuTau") channel_="ch2";
    if (channel=="TauTau") channel_="ch3";

    TString fname = "/uscms_data/d3/fojensen/excitedTau_04032022/CMSSW_10_6_30/src/PhysicsTools/NanoAODTools/condor/fitDiagnosticsTest.m1y0.nominal.root";

    TFile * f = TFile::Open(fname, "READ");
    TString hname = "shapes_fit_b/" + channel_ +"_A/" + process;
    //std::cout << "channel = " << channel << " channel_ = " << channel_ << " : Hist name = " <<hname << std::endl;
    TH1D * h = (TH1D*)f->Get(hname);
    //std::cout << h->GetEntries() << std::endl;
    
    x = h->GetBinContent(1);
    xerr = h->GetBinError(1);

    const bool lumiNorm = false;
    if (lumiNorm) {
        double lumi = 137.62;
        double lumierr = 0.016;
        xerr = (xerr*xerr)/(x*x) + (lumierr*lumierr);
        xerr = x * sqrt(xerr) / lumi;
        x = x / lumi; 
    }

    TString name;
    if (process=="ST") name = "single-top";
    if (process=="DB") name = "di-boson";
    if (process=="TT") name = "$t\\bar{t}$";
    if (process=="DY") name = "Drell-Yan/Z";
    if (process=="jet1") name = "1-prong";
    if (process=="jet3") name = "3-prong";

    std::cout << std::setprecision(3);
    std::cout << process << "," << channel << "," << x << "," << xerr << std::endl;

    f->Close();
}

void finalYieldsList()
{
    TString channels[3] = {"ETau", "MuTau", "TauTau"};
    for (int chN = 0; chN < 3; chN++)
    {
      //std::cout << "Channel passed is " << channels[chN] << std::endl;
        runPoint("ST", channels[chN]);
        runPoint("DB", channels[chN]);
        runPoint("TT", channels[chN]);
        runPoint("DY", channels[chN]);
        runPoint("jet1", channels[chN]);
        runPoint("jet3", channels[chN]);
    }
}
