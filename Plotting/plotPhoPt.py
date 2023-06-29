#Plot photon pT distributions 
# 

import sys
import os
from array import array
from ROOT import TFile, TH1F, TCanvas, TTree, TCut, gStyle, gPad, TLegend


def getSigTree(mass, year):
    filepath = os.environ["ROOTURL"] + os.environ["TSSIGDIR"] + "Taustar_m" + mass + "_" + year + ".root"
    fil = TFile.Open(filepath, "READ")
    tree = fil.Get("Events")
    return tree

def getCuts(year, channel, isSig):
    cuts = ""
    if channel == "ETau":
        cuts += "ETau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]) && ETau_Mass>=100. && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_qq==-1"
        cuts += "&& nE==1 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Electron_mvaFall17V2Iso_WP90[ETau_EIdx] && !Photon_pixelSeed[ETau_PhotonIdx]"
        if year == "2015" or year == "2016":
            cuts += " && (HLT_Ele27_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon175 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=29." 
        elif year == "2017":
            cuts += " && (HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=34."
        elif year == "2018":
            cuts += " && ( HLT_Ele32_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10) ) && Electron_pt[ETau_EIdx]>=34."
    elif channel == "MuTau":
        cuts += "MuTau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_qq==-1 && nE==0 && nMu==1 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Muon_pfIsoId[MuTau_MuIdx]>=4"
        if year == "2015" or year == "2016":
            cuts += " && (MuTau_t2016_0[1] || MuTau_t2016_1[1]) && Muon_pt[MuTau_MuIdx]>=26."
        elif year == "2017":
            cuts += " && MuTau_t2017[1] && Muon_pt[MuTau_MuIdx]>=29."
        elif year == "2018":
            cuts += "&& MuTau_t2018[1] && Muon_pt[MuTau_MuIdx]>=26."
    elif channel == "TauTau":
        cuts += "TauTau_HaveTriplet>0 && TauTau_Mass>=100. && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx_esup]) && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx_esup]) && TauTau_qq_esup==-1"
        cuts += " && nE==0 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0"
        if year == "2015" or year == "2016":
            cuts += " && (TauTau_t2016_0[0] || TauTau_t2016_1[0])"
        elif year == "2017":
            cuts += " && (TauTau_t2017_0[0] || TauTau_t2017_1[0] || TauTau_t2017_2[0])"
        elif year == "2018":
            cuts += " && (TauTau_t2018_0[0] || TauTau_t2018_1[0] || TauTau_t2018_2[0] || TauTau_t2018_3[0])"

    if isSig and (year == "2015" or year == "2016"):
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter"
    elif isSig and (year == "2017" or year == "2018"):
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter"

    return cuts



def plotAllSig():
    OUTPATH = "../Plots/PhotonPt/Normalized/"
    canv = TCanvas("canv_phoPt", "Photon pT Distributions", 800, 600)
    #leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")
    gStyle.SetOptStat(0)
    
    ptBins = array("f", [20, 75, 100, 200, 500, 1000, 2000, 3000, 4000, 5000])
    nBins = len(ptBins) - 1

    useLeftLeg = False

    for mass in ["175","250","375","500","625","750","1000","1250","1500","1750","2000","2500","3000","3500","4000","4500","5000"]:
        print("Plotting pho pT for m=" + mass + "...")

        h_ETau = TH1F("h_ETau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
        h_MuTau = TH1F("h_MuTau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
        h_TauTau = TH1F("h_TauTau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)

        if mass == "2000":
            useLeftLeg = True
            
        for year in ["2015", "2016", "2017", "2018"]:

            filepath = os.environ["ROOTURL"] + os.environ["TSSIGDIR"] + "Taustar_m" + mass + "_" + year + ".root"
            fil = TFile.Open(filepath, "READ")
            tree = fil.Get("Events")
            tree.Draw("Photon_pt[ETau_PhotonIdx]")

            histNames = ["h_ETau_m" + mass + "_" + year, "h_MuTau_m" + mass + "_" + year, "h_TauTau_m" + mass + "_" + year]
            h_ETau_yr = TH1F(histNames[0], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_MuTau_yr = TH1F(histNames[1], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_TauTau_yr = TH1F(histNames[2], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            
            tree.Draw("Photon_pt[ETau_PhotonIdx]>>+" + histNames[0], getCuts(year=year, channel="ETau", isSig=True))
            tree.Draw("Photon_pt[MuTau_PhotonIdx]>>+" + histNames[1], getCuts(year=year, channel="MuTau", isSig=True))
            tree.Draw("Photon_pt[TauTau_PhotonIdx]>>+" + histNames[2], getCuts(year=year, channel="TauTau", isSig=True))


            if year == "2015":
                lumiFrac = 19.7 / 137.8;
            elif year == "2016":
                lumiFrac = 16.9 / 137.8;
            elif year == "2017": 
                lumiFrac = 41.5 / 137.8;
            elif year == "2018":
                lumiFrac = 59.7 / 137.8;

            h_ETau.Add(h_ETau_yr, lumiFrac)
            h_MuTau.Add(h_MuTau_yr, lumiFrac)
            h_TauTau.Add(h_TauTau_yr, lumiFrac)

            h_ETau_yr.Scale(1.0 / h_ETau_yr.GetEntries())
            h_MuTau_yr.Scale(1.0 / h_MuTau_yr.GetEntries())
            h_TauTau_yr.Scale(1.0 / h_TauTau_yr.GetEntries())

            h_ETau_yr.SetLineColor(12)
            h_MuTau_yr.SetLineColor(9)
            h_TauTau_yr.SetLineColor(46)
            h_ETau_yr.SetLineWidth(3)
            h_MuTau_yr.SetLineWidth(3)
            h_TauTau_yr.SetLineWidth(3)

            canv.cd()
            canv.Clear()
            canv.SetLogx(1)

            max_ETau = h_ETau_yr.GetMaximum()
            max_MuTau = h_MuTau_yr.GetMaximum()
            max_TauTau = h_TauTau_yr.GetMaximum()
            if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
                h_ETau_yr.Draw("hist")
                h_MuTau_yr.Draw("hist same")
                h_TauTau_yr.Draw("hist same")
            elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
                h_MuTau_yr.Draw("hist")
                h_ETau_yr.Draw("hist same")
                h_TauTau_yr.Draw("hist same")
            else:
                h_TauTau_yr.Draw("hist")
                h_MuTau_yr.Draw("hist same")
                h_ETau_yr.Draw("hist same")
            
            if useLeftLeg:
                leg = TLegend(0.15, 0.7, 0.35, 0.9, "Channels")
            else:
                leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")

            leg.AddEntry(h_ETau_yr, "ETau", "l")
            leg.AddEntry(h_MuTau_yr, "MuTau", "l")
            leg.AddEntry(h_TauTau_yr, "TauTau", "l")
            leg.Draw()
            
            canv.Update()
            canv.SaveAs(OUTPATH + "phoPt_m" + mass + "_" + year + ".png")
            
            fil.Close()
        
        h_ETau.Scale(1.0 / h_ETau.GetEntries())
        h_MuTau.Scale(1.0 / h_MuTau.GetEntries())
        h_TauTau.Scale(1.0 / h_TauTau.GetEntries())

        h_ETau.SetLineColor(12)
        h_MuTau.SetLineColor(9)
        h_TauTau.SetLineColor(46)
        h_ETau.SetLineWidth(3)
        h_MuTau.SetLineWidth(3)
        h_TauTau.SetLineWidth(3)

        canv.cd()
        canv.Clear()
        canv.SetLogx(1)

        max_ETau = h_ETau.GetMaximum()
        max_MuTau = h_MuTau.GetMaximum()
        max_TauTau = h_TauTau.GetMaximum()
        if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
            h_ETau.Draw("hist")
            h_MuTau.Draw("hist same")
            h_TauTau.Draw("hist same")
        elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
            h_MuTau.Draw("hist")
            h_ETau.Draw("hist same")
            h_TauTau.Draw("hist same")
        else:
            h_TauTau.Draw("hist")
            h_MuTau.Draw("hist same")
            h_ETau.Draw("hist same")

        leg.Clear()
            
        leg.AddEntry(h_ETau, "ETau", "l")
        leg.AddEntry(h_MuTau, "MuTau", "l")
        leg.AddEntry(h_TauTau, "TauTau", "l")
        leg.Draw()
        canv.Update()
        canv.SaveAs(OUTPATH + "phoPt_m" + mass + ".png")

if __name__ == "__main__":
    plotAllSig()



# XRDBASE = "root://cmsxrootd.fnal.gov/"
# EOSPATH = "/store/user/bbarton/"

# def plotPhoPt(sample, mass, maxPt=5000):
#     global XRDBASE, EOSPATH

#     canv = TCanvas("canv", "Photon pT Plots", 1200, 800)
#     gStyle.SetOptStat(0)

#     inFile = TFile.Open(XRDBASE + EOSPATH + sample, "READ")
#     tree = inFile.Get("Events")

#     h_pT = TH1F("h_pT", "Signal Photons m#tau*=" + mass + "GeV;photon Pt [GeV];Events", 50, 0, maxPt)
#     h_pT_frac = TH1F("h_pT_frac", "Signal Photons m#tau*=" + mass + " GeV;photon Pt [GeV];Fraction of Total Events", 50, 0, maxPt)

#     bins = [0, 1000, 2000, 3000, 4000, 5000]
#     bins = array("f", bins)
#     h_pT_course = TH1F("h_pT_course", "Signal Photons m#tau*=" + mass + " GeV;photon Pt [GeV];Fraction of Total Events", 5, bins)

#     cut_eTauTrip = "ETau_HaveTriplet"
#     cut_muTauTrip = "MuTau_HaveTriplet"
#     cut_tauTauTrip = "TauTau_HaveTriplet"
#     cut_anyTrip = cut_eTauTrip + " || " + cut_muTauTrip + "||" + cut_tauTauTrip
#     cuts = TCut(cut_anyTrip)

#     tree.Draw("Photon_pt>>h_pT", cuts)
#     tree.Draw("Photon_pt>>h_pT_frac", cuts)
#     tree.Draw("Photon_pt>>h_pT_course", cuts)

#     h_pT_frac.Scale(1.0 / h_pT_frac.GetEntries())
#     h_pT_course.Scale(1.0 / h_pT_course.GetEntries())

#     canv.Clear()
#     canv.Divide(2, 2)
#     canv.cd(1)
#     h_pT.Draw("hist")
#     #canv.SetLogy()
#     canv.cd(2)
#     h_pT_frac.Draw("E0")
#     gPad.SetLogy()
#     canv.Update()
#     canv.cd(3)
#     h_pT_course.Draw("E0")
#     #gPad.SetLogy()
#     canv.Update()
#     wait = raw_input("Hit ENTER to close")
#     canv.SaveAs("../Plots/phoPt_" + mass + ".png")


# if __name__ == "__main__":
#     if len(sys.argv) < 3:
#         print("USAGE: python plotPhoPt.py <sample file name> <sample mass> <OP: max pT")
#         exit()
#     if len(sys.argv) == 4:
#         plotPhoPt(sample=sys.argv[1], mass=sys.argv[2], maxPt=float(sys.argv[3]))
#     else:
#         plotPhoPt(sample=sys.argv[1], mass=sys.argv[2])
    
