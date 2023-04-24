#Script to make nice versions of supplemental plots for HEPData submissions
#Reads in histograms from various sources, puts them in CMS style, and saves image files
#More thorough discussion of data sources and details in ../makeSubmission.py
#Intentionally a crude plotting macro to make changing individual plots easy

import CMS_lumi as lumiStyle
import tdrstyle
from ROOT import TFile, TCanvas, TH2F, TH1F, gPad, gStyle
from math import sqrt
from array import array

#Choose which plots are made
ELECTRONS = True
PHOTONS = True
MUONS = True
TAUS = True

canv = TCanvas("effCanv", "Efficiency Plotting", 1000, 800)
canv.SetLeftMargin(0.15) #Make margins larger so axis titles don't get cut off
canv.SetRightMargin(0.15)
canv.SetBottomMargin(0.15)

years = ["2015", "2016", "2017", "2018"]
yrNames = {"2015" : "2016preHIPM", "2016" : "2016postHIPM", "2017" : "2017", "2018":"2018"}
lumis = {"2015" : "19.7 fb^{-1}", "2016" : "16.9 fb^{-1}", "2017" : "41.5 fb^{-1}", "2018" : "59.7 fb^{-1}"}

if ELECTRONS:
    print("Plotting electron efficiencies...")
    types = ["reco", "ID", "trig"]
    for year in years:
        for effType in types:
            inFile = TFile("effs_el_" + effType + "_" + year + ".root")
            hist = inFile.Get("EGamma_EffMC2D")
            hist.SetTitle("Electron " + effType + " Efficiency in MC: " + yrNames[year] + ";Electron #eta;Electron pT [GeV]")
            hist.SetMaximum(1.0)
            canv.cd()
            hist.Draw("COLZ TEXTE")
            lumiStyle.lumi_13TeV = lumis[year]
            lumiStyle.CMS_lumi(gPad, 4, 0)
            tdrstyle.setTDRStyle()
            gStyle.SetPaintTextFormat("4.2f") 
            gPad.SetLogy(1)
            gPad.Modified()
            canv.Update()
            canv.SaveAs("../Inputs/eff_el_" + effType + "_" + yrNames[year] + ".png")
            inFile.Close()


if PHOTONS:
    print("Plotting photon efficiencies...")
    #Reco
    inFile = TFile.Open("effs_reco.root")
    for year in years:
        hist = inFile.Get("h_phoEff_" + year)
        hist.SetMaximum(1.0)
        canv.cd()
        hist.Draw("COLZ TEXTE")
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f")
        gPad.SetLogy(1)
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_pho_reco_" + yrNames[year] + ".png")
    inFile.Close()

    #ID
    for year in years:
        inFile = TFile("effs_pho_ID_" + year + ".root")
        hist = inFile.Get("EGamma_EffMC2D")
        hist.SetMaximum(1.0)
        canv.cd()
        hist.Draw("COLZ TEXTE")
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f")
        gPad.SetLogy(1)
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_pho_ID_" + yrNames[year] + ".png")
        inFile.Close()


if MUONS:
    print("Plotting muon efficiencies...")
    #Reco
    #Reco efficiencies are not available from the POG as TH2Fs, only as jsons
    #Values from those JSONs were manually extracted to include below (the values' absurd quoted precision has been clipped to 5 dig after decimal)
    etaBinsReco = [0.0, 0.9, 1.2, 2.1, 2.4]
    #effs and Errs are in format {year : [[effs], [(stat, syst)]]}
    recoEffs = {"2015" : [[0.99982, 1.00015, 0.99989, 0.99902], [(0.00015, 0.00035), (0.00019, 0.00031), (0.00012, 0.00021), (0.00027, 0.00194)]],
                "2016" : [[1.00004, 0.99979, 0.99949, 0.99907], [(0.00010, 0.00143), (0.00019, 0.00109), (0.00012, 0.00148), (0.00027, 0.00173)]],
                "2017" : [[0.99967, 0.99978, 0.99946, 0.99935], [(0.00007, 0.00065), (0.00014, 0.00043), (0.00007, 0.00106), (0.00022, 0.00118)]],
                "2018" : [[0.99980, 0.99975, 0.99958, 0.99903], [(0.00006, 0.00038), (0.00011, 0.00052), (0.00007, 0.00083), (0.00019, 0.00172)]]}
    
    for year in years:
        hist = TH1F("eff_mu_reco_"+year, "Muon Reco Efficiency in MC;Muon |#eta|", len(etaBinsReco)-1, array("f",etaBinsReco))
        for i in range(len(etaBinsReco) - 1):
            hist.SetBinContent(i+1, recoEffs[year][0][i])
            hist.SetBinError(i+1, sqrt(recoEffs[year][1][i][0]**2 + recoEffs[year][1][i][1]**2)) #Combine stat and syst errors
        
        canv.cd()
        gPad.SetLogy(0)
        hist.Draw("ERR")
        lumiStyle.lumi_13TeV = lumis[year]
        lumiStyle.CMS_lumi(gPad, 4, 10)
        tdrstyle.setTDRStyle()
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_mu_reco_" + yrNames[year] + ".png")

    #ID
    for year in years:
        inFile = TFile("effs_mu_ID_" + year + ".root")
        hist = inFile.Get("NUM_TightID_DEN_TrackerMuons_abseta_pt_efficiencyMC")
        hist.SetMaximum(1.0)
        canv.cd()
        hist.Draw("COLZ TEXTE")
        lumiStyle.lumi_13TeV = lumis[year]
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f")
        gPad.SetLogy(1)
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_mu_ID_" + yrNames[year] + ".png")
        inFile.Close()

    #Trig
    #Trigger histogram names are year dependent, provide map year->name here
    trigHistNames ={"2015" : "NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdTight_and_PFIsoTight_eta_pt_efficiencyMC",
                    "2016" : "NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdTight_and_PFIsoTight_eta_pt_efficiencyMC",
                    "2017" : "NUM_IsoMu27_DEN_CutBasedIdTight_and_PFIsoTight_abseta_pt_efficiencyMC",
                    "2018" : "NUM_IsoMu24_DEN_CutBasedIdTight_and_PFIsoTight_abseta_pt_efficiencyMC"}

    for year in years:
        inFile = TFile("effs_mu_trig_" + year + ".root")
        hist = inFile.Get(trigHistNames[year])
        hist.SetMaximum(1.0)
        canv.cd()
        hist.Draw("COLZ TEXTE")
        lumiStyle.lumi_13TeV = lumis[year]
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f")
        gPad.SetLogy(1)
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_mu_trig_" + yrNames[year] + ".png")
        inFile.Close()


if TAUS:
    print("Plotting tau efficiencies...")

    #Reco
    inFile = TFile.Open("effs_reco.root")
    for year in years:
        hist = inFile.Get("h_tauEff_" + year)
        hist.SetMaximum(1.0)
        canv.cd()
        hist.Draw("COLZ TEXTE")
        lumiStyle.lumi_13TeV = lumis[year]
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f")
        gPad.SetLogy(1)
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_tau_reco_" + yrNames[year] + ".png")
    inFile.Close()

    #ID
    chs = ["ETau_", "MuTau_", "TauTau_"]
    inFile = TFile.Open("effs_tau_ID.root")
    for year in years:
        for ch in chs:
            hist = inFile.Get("tauIDeff_" + ch + year)
            hist.SetMaximum(1.0)
            canv.cd()
            hist.Draw("COLZ TEXTE")
            lumiStyle.lumi_13TeV = lumis[year]
            lumiStyle.CMS_lumi(gPad, 4, 0)
            tdrstyle.setTDRStyle()
            gStyle.SetPaintTextFormat("4.2f")
            gPad.SetLogy(1)
            gPad.Modified()
            canv.Update()
            canv.SaveAs("../Inputs/eff_tau_ID_" + ch + yrNames[year] + ".png")
    inFile.Close()

    #Trig
    for year in years:
        inFile = TFile("effs_tau_trig_" + year + ".root")
        hist = inFile.Get("mc_ditau_Medium_dmall_fitted")
        hist.SetTitle(";Tau pT [GeV];Per Leg diTau Trigger Efficiency in MC")
        hist.SetMaximum(1.2)
        canv.cd()
        gPad.SetLogy(0)
        hist.Draw("P E1")
        lumiStyle.lumi_13TeV = lumis[year]
        lumiStyle.CMS_lumi(gPad, 4, 0)
        tdrstyle.setTDRStyle()
        gStyle.SetPaintTextFormat("4.2f") 
        gPad.Modified()
        canv.Update()
        canv.SaveAs("../Inputs/eff_tau_trig_" + yrNames[year] + ".png")
        inFile.Close()



