#Plot photon ID efficiency

from ROOT import TFile, TCanvas, TH1F, TCut, gStyle, TLegend
from array import array
import os


def plotPhoEff(dirpath, channel=""):
    canv = TCanvas("canv", "Photon ID Efficiencies", 100, 600)
    gStyle.SetOptStat(0)
    
    cuts = TCut("")
    elCut = TCut("ETau_HavePair")
    muCut = TCut("MuTau_HavePair")
    idCut = TCut("PhoID_passID")
    cuts = cuts

    if channel == "el":
        cuts = cuts + elCut
    elif channel == "mu":
        cuts = cuts + muCut

    ptBins = array("f", [20, 35, 50, 100, 200, 500, 1000] )
    nBins = len(ptBins - 1)
    colors = [1, 2, 4, 4, 6, 7, 8, 9, 12, 30, 36, 38, 46]
    colIdx = 0

    leg = TLegend(0.7, 0.1, 0.9, 0.3)

    for filename in os.listdir(dirpath):
        splitName = filename.split("_")
        mass = splitName[1][1:]
        elVeto = splitName[2][:-5]
        if elVeto == ""

        file = TFile(filename, "read")
        tree = file.Get("Events")

        nameSuffix = "_" mass

        hNum = TH1F("hNum" + nameSuffix, "Photon ID Eff: " + mass + " " + elVeto + " " + channel +";photon pt;mvaID_WP90 Efficiency", nBins, ptBins)
        hDenom = TH1F("hDenom" + nameSuffix, "Photon ID Eff: " + mass + " "  + elVeto + " " + channel +";photon pt;mvaID_WP90 Efficiency", nBins, ptBins)

        tree.Draw("PhoID_phoPt>>+hNum"+nameSuffix, cuts + idCut)
        tree.Draw("PhoID_phoPt>>+hDenom"+nameSuffix, cuts)

        hNum.Sumw2()
        hNum.Divide(hDenom)

        hNum.SetLineColor(colors[colIdx])
        colIdx += 1

        leg.AddEntry("hNum" + nameSuffix, mass, "L")

        canv.cd()
        if colIdx == 0:
            hNum.Draw("E")
        else:
            hNum.Draw("E same")
        hNum.SetMaximum(1.0)
    
    leg.Draw()
    canv.SaveAs("../Plots/phoIDeffs.png")


