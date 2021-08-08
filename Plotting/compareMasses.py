#Compare the mass distributions of different tau star mass points
#Usage: python compareMasses.py <input directory> <bin width fraction (0,1]> <bool useMCTruth>

import os
import sys
import numpy as np
import ROOT
from ROOT import TFile
from ROOT import TCut
from ROOT import TTree
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TCanvas
from ROOT import gROOT
from ROOT import TDirectory
from ROOT import TCandle
from ROOT import TStyle
from ROOT import TVector
from ROOT import TMultiGraph
from ROOT import TLegend
from ROOT import TGraph
from array import array


def triggerEffs(trees):
    effs = []
    for tree in trees:
        trigEntries = tree.GetEntries("ElTau_HaveTriplet&&ElTau_Trigger")
        tripEntries = tree.GetEntries("ElTau_HaveTriplet")
        effs.append(float(trigEntries) / tripEntries)
    print "Trigger Efficiencies: (HaveTriplet && Trigger) / HaveTriplet:"
    print effs
    print "Average efficiency = " + str(sum(effs)/len(effs))
    


def scanBinWidths(hists, masses, sortIndices):

    canv = TCanvas("widthCanv", "Fractional Width Graphs", 800, 600)
    graphs = TMultiGraph()
    leg = TLegend(0.6, 0.3, 0.8, 0.5)
    
    for i in range(len(hists)):
        ind = sortIndices[i]
        hist = hists[i]
        mass = masses[ind]
        
        #halfWidth = hist.GetStdDev()
        halfWidth = 1
        mean = hist.GetMean()
        lowBin = hist.FindBin(mean - halfWidth)
        highBin = hist.FindBin(mean + halfWidth)
        low = hist.GetBinCenter(lowBin)
        high = hist.GetBinCenter(highBin)
 
        lows = []
        highs = []
        fracWidths = []
        fracEvents = []
        totalEvents = hist.Integral()
        changed = True
        while changed:
            eventsIn = hist.Integral(lowBin, highBin)
            #fracEvents.append(eventsIn)
            fracEvents.append(eventsIn / totalEvents)
            fracWidths.append(((high - low) / 2) / float(mass))
            lows.append(low)
            highs.append(high)

            changed = False
            if lowBin > 1:
                lowBin -= 1
                low = hist.GetBinCenter(lowBin)
                changed = True
            if highBin < hist.GetNbinsX() - 1:
                highBin += 1
                high = hist.GetBinCenter(highBin)
                changed = True

            if (eventsIn / totalEvents) > 0.98:
                break
                

           # lowerInteg = 9999999
           # upperInteg = 9999999
           # if lowBin > 1:
           #     lowBin -= 1
           #     lowerInteg = hist.Integral(lowBin, highBin)
           #     #lowBin += 1
           # if highBin < hist.GetNbinsX() - 1:
           #     highBin += 1
           #     upperInteg = hist.Integral(lowBin, highBin)
                #highBin -= 1

           # if lowerInteg == upperInteg:
           #     break
                
          #  if lowerInteg < upperInteg:
          #      lowBin -= 1
          #      low = hist.GetBinCenter(lowBin)
          #  elif upperInteg < lowerInteg:
          #      highBin += 1
          #      high = hist.GetBinCenter(highBin)
          #  else:
          #      break
        
        graph = TGraph(len(fracWidths), array('f',fracWidths), array('f',fracEvents))
        if i == 0:
            i = 46
        if i == 5:
            i = 12
        graph.SetLineColor(i)
        if i == 12:
            i = 5
        graphs.Add(graph)
        leg.AddEntry(graph, mass, "L")
        graphs.Draw()
        del graph
        
    graphs.SetTitle("Signal Bin Widths;Fractional Bin Half Width;Fraction of Events in Bin")
    #graphs.SetTitle("Signal in Signal Bin;Fractional Bin Half Width;Events in Signal Bin")
    ROOT.gStyle.SetPalette(55) #kRainBow
    graphs.Draw("A PLC")
    leg.SetHeader("Nominal #tau* Mass", "C")
    leg.Draw("same") 
    canv.SaveAs("Plots/binWidthCurves.png")
        
        


def main(argv):
    if len(argv) < 4:
        print "Usage: python compareMasses.py <input directory> <bin width fraction (0,1]> <bool useMCTruth>"
        exit
    dirPath = argv[1]

    files = next(os.walk(dirPath))[2]
    trees = []
    masses = []

    for f in files:
        #rootFile = TFile(dirPath + f, "READ")
        #tree = rootFile.Get("Events")
        #trees.append(tree)
        fComps = f.split("_")
        mass = fComps[1][1:] 
        masses.append(mass)

        
    rootFile0 = TFile(dirPath + files[0], "READ")
    rootFile1 = TFile(dirPath + files[1], "READ")
    rootFile2 = TFile(dirPath + files[2], "READ")
    rootFile3 = TFile(dirPath + files[3], "READ")
    rootFile4 = TFile(dirPath + files[4], "READ")
    rootFile5 = TFile(dirPath + files[5], "READ")
    rootFile6 = TFile(dirPath + files[6], "READ")
    rootFile7 = TFile(dirPath + files[7], "READ")
    rootFile8 = TFile(dirPath + files[8], "READ")
    rootFile9 = TFile(dirPath + files[9], "READ")

    tree0 = rootFile0.Get("Events")
    tree1 = rootFile1.Get("Events")
    tree2 = rootFile2.Get("Events")
    tree3 = rootFile3.Get("Events")
    tree4 = rootFile4.Get("Events")
    tree5 = rootFile5.Get("Events")
    tree6 = rootFile6.Get("Events")
    tree7 = rootFile7.Get("Events")
    tree8 = rootFile8.Get("Events")
    tree9 = rootFile9.Get("Events")

    trees.append(tree0)
    trees.append(tree1)
    trees.append(tree2)
    trees.append(tree3)
    trees.append(tree4)
    trees.append(tree5)
    trees.append(tree6)
    trees.append(tree7)
    trees.append(tree8)
    trees.append(tree9)


    masses_np = np.array(masses, dtype="i")
    sortIndices = np.argsort(masses_np)

        
    candleCanv = TCanvas("candleCanv", "Candlestick Plots", 700, 700)
    hists = []
    for i in range(len(trees)):
        index = sortIndices[i]
        mass = masses[index]
        tree = trees[index]
        baseCuts = TCut("ElTau_HaveTriplet")
        elCuts = ""
        tauCuts = ""
        if argv[3] == "True":    
            elCuts = baseCuts + TCut("ElTau_DRGenMatch==1") 
            tauCuts = baseCuts + TCut("ElTau_DRGenMatch==5")
        else:
            elCuts = baseCuts + TCut("abs(ElTau_ElCollMass-"+mass+")<=abs(ElTau_TauCollMass-"+mass+")")
            tauCuts = baseCuts + TCut("abs(ElTau_TauCollMass-"+mass+")<=abs(ElTau_ElCollMass-"+mass+")")
        #trees[i].Draw("ElTau_DRGenMatch")
        #wait = raw_input("waiting...")
        elHist = TH1F("elHist"+mass, "Reco #tau* Mass, e Matched: m=" + mass, 301, -2000, 1000)
        tauHist = TH1F("tauHist"+mass, "Reco #tau* Mass, #tau Matched: m=" + mass, 301, -2000, 1000)
        hists.append(TH1F("combHist"+mass, "Reco #tau* Mass: m=" + mass, 301, -2000, 1000))

        tree.Draw("ElTau_ElCollMass-" + mass + ">>+elHist"+mass, elCuts)
        tree.Draw("ElTau_TauCollMass-" + mass + ">>+tauHist"+mass, tauCuts)
        hists[i].Add(elHist, tauHist)
        hists[i].Draw()

        
    #canv = TCanvas("c", "c", 800, 600)
    #canv.Divide(2,1)
    #canv.cd(1)
    #hists[4].Draw("hist")
    #canv.cd(2)
    #hists[5].Draw("hist")
    #inputd = raw_input("waiting...")

    #candleCanv.cd()
    
    

    candles = TH2F("candles","Reco #tau* Mass", 17, 124.5, 2124.5, 301, -2000, 1000) 
    candles.SetXTitle("Nominal #tau* mass [GeV]")
    candles.SetYTitle("Reconstructed - nominal #tau* mass [GeV]")
    
    for i in range(len(trees)):
        for b in range(hists[i].GetNbinsX()):
            candles.Fill(float(masses[i]), hists[i].GetBinCenter(b), hists[i].GetBinContent(b))
        candles.Draw("CANDLEX1")
    
    candleCanv.cd()
    ROOT.gStyle.SetOptStat(0)
    candles.SetYTitle("Reconstructed - nominal #tau* mass [GeV]")
    candles.Draw("CANDLEX1")
    TCandle.SetBoxRange(float(argv[2]))
    candles.SetYTitle("Reconstructed - nominal #tau* mass [GeV]")
    candles.GetYaxis().SetTitle("Reconstructed - nominal #tau* mass [GeV]")
    candleCanv.Update()    
    candleCanv.SaveAs("Plots/massComparisons.png")


    scanBinWidths(hists, masses, sortIndices)
    triggerEffs(trees)

    
                     
if __name__ == "__main__":
    main(sys.argv)







