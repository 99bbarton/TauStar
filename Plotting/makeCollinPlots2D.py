
import os
from ROOT import TCanvas, TLegend, gStyle, TFile, TTree, TH2F, TGraph2D, TMultiGraph, gPad, TLine

#Return the full signal region cuts for the given year and channel as a single string
def getCuts(year, channel):
    cuts = ""
    if channel == "ETau":
        cuts += "ETau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]) && ETau_Mass>=100. && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_qq==-1"
        cuts += "&& nE==1 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Electron_mvaFall17V2Iso_WP90[ETau_EIdx] && !Photon_pixelSeed[ETau_PhotonIdx] && Photon_pt[ETau_PhotonIdx]>=100."
        if year == "2015" or year == "2016":
            cuts += " && (HLT_Ele27_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon175 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=29." 
        elif year == "2017":
            cuts += " && (HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=34."
        elif year == "2018":
            cuts += " && ( HLT_Ele32_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10) ) && Electron_pt[ETau_EIdx]>=34."
    elif channel == "MuTau":
        cuts += "MuTau_HaveTriplet>0 && MuTau_Mass>=100. && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_qq==-1 && nE==0 && nMu==1 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Muon_pfIsoId[MuTau_MuIdx]>=4 && Photon_pt[ETau_PhotonIdx]>=100."
        if year == "2015" or year == "2016":
            cuts += " && (MuTau_t2016_0[1] || MuTau_t2016_1[1]) && Muon_pt[MuTau_MuIdx]>=26."
        elif year == "2017":
            cuts += " && MuTau_t2017[1] && Muon_pt[MuTau_MuIdx]>=29."
        elif year == "2018":
            cuts += "&& MuTau_t2018[1] && Muon_pt[MuTau_MuIdx]>=26."
    elif channel == "TauTau":
        cuts += "TauTau_HaveTriplet>0 && TauTau_Mass>=100. && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx_esup]) && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx_esup]) && TauTau_qq_esup==-1 && Photon_pt[ETau_PhotonIdx]>=75."
        cuts += " && nE==0 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0"
        if year == "2015" or year == "2016":
            cuts += " && (TauTau_t2016_0[0] || TauTau_t2016_1[0])"
        elif year == "2017":
            cuts += " && (TauTau_t2017_0[0] || TauTau_t2017_1[0] || TauTau_t2017_2[0])"
        elif year == "2018":
            cuts += " && (TauTau_t2018_0[0] || TauTau_t2018_1[0] || TauTau_t2018_2[0] || TauTau_t2018_3[0])"
    if year == "2015" or year == "2016":
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter"
    elif year == "2017" or year == "2018":
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter"

    return cuts


def makePlots():
    OUTPATH = "../Plots/CollinMass2D/sigCollinMass2D"
    canv = TCanvas("canv_collinMass", "2D Collinear Mass Distributions", 1000, 800)
    gStyle.SetOptStat(0)
    #colors = [595, 602, 597, 434, 426, 419, 411, 414, 402, 797, 626, 634, 610, 618, 619]
    colors = [595, 602, 434, 411, 426, 419, 597, 414, 402, 797, 626, 634, 610, 618, 619]
    #colors = [884, 874, 881, 876, 890, 855, 852, 867, 835, 844, 419, 413]
    alpha = 1

    masses = ["1000", "2000", "3000", "5000"]
    minEdges=(0, 100)
    maxEdges=(6000, 7000)
    nBins = (maxEdges[0]-minEdges[0], maxEdges[1]-minEdges[1])

    graphs = TMultiGraph()
    hists = []

    for massN, mass in enumerate(masses):
        print("Plotting massN " + str(massN + 1) + "/" + str(len(masses)))

        h_mass = TH2F("h_"+mass, "Signal Collinear Mass;Min Collinear Mass [GeV]; Max Collinear Mass [GeV]", nBins[0], minEdges[0], maxEdges[0], nBins[1], minEdges[1], maxEdges[1])

        for year in ["2015", "2016", "2017", "2018"]:
            filepath = os.environ["ROOTURL"] + os.environ["TSSIGDIR"] + "Taustar_m" + mass + "_" + year + ".root"
            fil = TFile.Open(filepath, "READ")
            tree = fil.Get("Events")

            lumiFrac = 1.0
            if year == "2015":
                lumiFrac = 19.7 / 137.8
            elif year == "2016":
                lumiFrac = 16.9 / 137.8
            elif year == "2017":
                lumiFrac = 41.5 / 137.8
            elif year == "2018":
                lumiFrac = 59.7 / 137.8

            for ch in ["ETau", "MuTau", "TauTau"]:
                h_ch = TH2F("h_"+mass+"_"+year+"_"+ch, "Collinear Mass;Min Collinear Mass [GeV]; Max Collinear Mass [GeV]", nBins[0], minEdges[0], maxEdges[0], nBins[1], minEdges[1], maxEdges[1])
            
                tree.Draw(ch + "_MaxCollMass:"+ch+"_MinCollMass>>+h_"+mass+"_"+year+"_"+ch, getCuts(year=year, channel=ch))
                h_mass.Add(h_ch)

            fil.Close()

        hists.append(h_mass)

    outFile = TFile.Open(OUTPATH + ".root", "RECREATE")
    outFile.cd()
            
    canv.cd()
    canv.SetLeftMargin(0.15) #Make margins larger so axis titles don't get cut off
    leg = TLegend(0.7, 0.2, 0.9, 0.5, "#tau* Mass [GeV]")
    for hN, hist in enumerate(hists):
        hist.SetMarkerColorAlpha(colors[hN], alpha)
        hist.SetMarkerStyle(20)
        hist.SetMarkerSize(0.2)
        hist.SetLineColorAlpha(colors[hN], alpha)
        hist.SetLineWidth(10)
        if hN == 0:
            hist.Draw("P")
        else:
            hist.Draw("P SAME")
        leg.AddEntry(hist, masses[hN], "LP")
        
        hist.Write()

    leg.Draw()
    canv.Update()
    wait = raw_input("Hit Enter to close and save plot...")
    outFile.Close()
    canv.SaveAs(OUTPATH + ".pdf")
    canv.SaveAs(OUTPATH + ".png")
    #Draw L-band
    widths = {"175":0.47,"250":0.35,"375":0.25,"500":0.21,"625":0.19,"750":0.17,"1000":0.15,"1250":0.13,"1500":0.13,"1750":0.12,"2000":0.11,"2500":0.10,"3000":0.11,"3500":0.10,"4000":0.11,"4500":0.13,"5000":0.14}


    line_hLow = []
    line_hUp = []
    line_vLow = []
    line_vUp = []
    for massN, mass in enumerate(masses):
        massFlt = float(mass)
        lowerBound = massFlt - (massFlt * widths[mass])
        upperBound = massFlt + (massFlt * widths[mass])
        line_hLow.append(TLine(100, lowerBound, upperBound, lowerBound))
        line_hUp.append(TLine(100, upperBound, lowerBound, upperBound))
        line_vLow.append(TLine(lowerBound, upperBound, lowerBound, maxEdges[1]))
        line_vUp.append(TLine(upperBound, lowerBound, upperBound, maxEdges[1]))
        line_hLow[massN].SetLineColor(colors[massN])
        line_hUp[massN].SetLineColor(colors[massN])
        line_vLow[massN].SetLineColor(colors[massN])
        line_vUp[massN].SetLineColor(colors[massN])
        line_hLow[massN].SetLineWidth(2)
        line_hUp[massN].SetLineWidth(2)
        line_vLow[massN].SetLineWidth(2)
        line_vUp[massN].SetLineWidth(2)
        line_hLow[massN].Draw("same")
        line_hUp[massN].Draw("same")
        line_vLow[massN].Draw("same")
        line_vUp[massN].Draw("same")
        canv.Update()

    wait = raw_input("Hit Enter to close and save plot...")
    canv.SaveAs(OUTPATH + "_Lbands.png")


if __name__ == "__main__":
    makePlots()
