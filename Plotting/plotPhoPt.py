#Plot photon pT distributions 
# 

import sys
from array import array
from ROOT import TFile, TH1F, TCanvas, TTree, TCut, gStyle, gPad

XRDBASE = "root://cmseos.fnal.gov/"
EOSPATH = "/store/user/fojensen/excitedTau_09082022/"

def plotPhoPt(sample, mass, maxPt=5000):
    global XRDBASE, EOSPATH

    canv = TCanvas("canv", "Photon pT Plots", 1200, 800)
    gStyle.SetOptStat(0)

    inFile = TFile.Open(XRDBASE + EOSPATH + sample, "READ")
    tree = inFile.Get("Events")

    h_pT = TH1F("h_pT", "Signal Photons m#tau*=" + mass + "GeV;photon Pt [GeV];Events", 50, 0, maxPt)
    h_pT_frac = TH1F("h_pT_frac", "Signal Photons m#tau*=" + mass + " GeV;photon Pt [GeV];Fraction of Total Events", 50, 0, maxPt)

    bins = [0, 1000, 2000, 3000, 4000, 5000]
    bins = array("f", bins)
    h_pT_course = TH1F("h_pT_course", "Signal Photons m#tau*=" + mass + " GeV;photon Pt [GeV];Fraction of Total Events", 5, bins)

    cut_eTauTrip = "ETau_HaveTriplet"
    cut_muTauTrip = "MuTau_HaveTriplet"
    cut_tauTauTrip = "TauTau_HaveTriplet"
    cut_anyTrip = cut_eTauTrip + " || " + cut_muTauTrip + "||" + cut_tauTauTrip
    cuts = TCut(cut_anyTrip)

    tree.Draw("Photon_pt>>h_pT", cuts)
    tree.Draw("Photon_pt>>h_pT_frac", cuts)
    tree.Draw("Photon_pt>>h_pT_course", cuts)

    h_pT_frac.Scale(1.0 / h_pT_frac.GetEntries())
    h_pT_course.Scale(1.0 / h_pT_course.GetEntries())

    canv.Clear()
    canv.Divide(2, 2)
    canv.cd(1)
    h_pT.Draw("hist")
    #canv.SetLogy()
    canv.cd(2)
    h_pT_frac.Draw("E0")
    gPad.SetLogy()
    canv.Update()
    canv.cd(3)
    h_pT_course.Draw("E0")
    #gPad.SetLogy()
    canv.Update()
    wait = raw_input("Hit ENTER to close")
    canv.SaveAs("../Plots/phoPt_" + mass + ".png")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("USAGE: python plotPhoPt.py <sample file name> <sample mass> <OP: max pT")
        exit()
    if len(sys.argv) == 4:
        plotPhoPt(sample=sys.argv[1], mass=sys.argv[2], maxPt=float(sys.argv[3]))
    else:
        plotPhoPt(sample=sys.argv[1], mass=sys.argv[2])
    
