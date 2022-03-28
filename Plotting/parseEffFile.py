#Parse the efficiency output file from TNP analyzer and produce efficiency and scale factor plots

from ROOT import TH1F, TH2F, TCanvas, TRatioPlot, TColor, gStyle, TLegend, gPad, TH2F
from array import array

gStyle.SetOptStat(0)    

ptBinLowEdges = [34.0, 50.0, 75.0, 100.0, 150.0, 200.0]
etaBinLowEdges = [0, 1.444, 1.566, 2.500]
ptBinLabels = ["[34, 50)", "[50, 75)", "[75, 100)", "[100, 150)", "[150, 200)"]
etaBinLabels = ["[0, 1.444)", "[1.444, 1.566)", "[1.566, 2.500)"]


dataEff_eta0 = TH1F("dataEff_eta0", "HLT_Ele32_WPTight_Gsf Trig Eff: 0 <= #eta < 1.444; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))
dataEff_eta1 = TH1F("dataEff_eta1.4", "HLT_Ele32_WPTight_Gsf Trig Eff: 1.444 <= eta < 1.566; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))
dataEff_eta2 = TH1F("dataEff_eta1.5", "HLT_Ele32_WPTight_Gsf Trig Eff: 1.566 <= #eta < 2.500; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))
mcEff_eta0 = TH1F("mcEff_eta0", "MC Efficiency: 0 <= #eta < 1.444; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))
mcEff_eta1 = TH1F("mcEff_eta1.4", "MC Efficiency: 1.444 <= #eta < 1.566; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))
mcEff_eta2 = TH1F("mcEff_eta1.5", "MC Efficiency: 1.566 <= #eta < 2.5; el Pt; Efficiency", len(ptBinLowEdges)-1, array("f", ptBinLowEdges))

hSFs = TH2F("hSFs", "Single El Trigger SFs (Data / MC); Electron SC Eta; Electron pT", len(etaBinLowEdges)-1, array("f", etaBinLowEdges), len(ptBinLowEdges)-3, array("f", ptBinLowEdges[2:]))

file = open("egammaEff.txt")
lines = file.readlines()

for line in lines:
    stripLine = " ".join(line.split())
    
    splitLine = stripLine.split(" ")

    etaMin = splitLine[0][1:]
    etaMax = splitLine[1][1:]
    ptMin = splitLine[2][1:]
    ptMax = splitLine[3][1:]
    dataEff = splitLine[4]
    dataEffErr = splitLine[5]
    mcEff = splitLine[6]
    mcEffErr = splitLine[7]

    etaRange = -1
    if etaMax == "1.444":
        etaRange = 0
    elif etaMax == "1.566":
        etaRange = 1
    elif etaMax == "2.500":
        etaRange = 2
    else:
        print("WARNING, invalid eta ")
      
    ptBin = -1
    if ptMax == "29.000":
        ptBin = 1
    elif ptMax == "34.000":
        ptBin = 2
    elif ptMax == "50.000":
        ptBin = 3
    elif ptMax == "75.000":
        ptBin = 4
    elif ptMax == "100.000":
        ptBin = 5
    elif ptMax == "150.000":
        ptBin = 6
    elif ptMax == "200.000":
        ptBin = 7
    elif ptMax == "250.000":
        ptBin = 8
    else:
        print("WARNING, invalid pt")

    if etaRange == 0:
        dataEff_eta0.SetBinContent(ptBin, float(dataEff))
        dataEff_eta0.SetBinError(ptBin, float(dataEffErr))
        mcEff_eta0.SetBinContent(ptBin, float(mcEff))
        mcEff_eta0.SetBinError(ptBin, float(mcEffErr))
    elif etaRange == 1:
        dataEff_eta1.SetBinContent(ptBin, float(dataEff))
        dataEff_eta1.SetBinError(ptBin, float(dataEffErr))
        mcEff_eta1.SetBinContent(ptBin, float(mcEff))
        mcEff_eta1.SetBinError(ptBin, float(mcEffErr))
    elif etaRange == 2:
        dataEff_eta2.SetBinContent(ptBin, float(dataEff))
        dataEff_eta2.SetBinError(ptBin, float(dataEffErr))
        mcEff_eta2.SetBinContent(ptBin, float(mcEff))
        mcEff_eta2.SetBinError(ptBin, float(mcEffErr))

    print ("ptMax, etaMax = " + ptMax + ", " + etaMax)
    bin = hSFs.FindBin(float(etaMax) - 0.1, float(ptMax) - 2 ) #Find bin number, adjust to avoid bin boundary issues
    print("bin = " + str(bin))
    hSFs.SetBinContent(bin, float(dataEff)/float(mcEff))


dataEff_eta0.SetLineColor(632 + 2) #kRed + 2
dataEff_eta1.SetLineColor(616 + 2) #kMagenta + 2
dataEff_eta2.SetLineColor(632 - 3) 
mcEff_eta0.SetLineColor(600) #kBlue
mcEff_eta1.SetLineColor(432 + 2) #kCyan + 2
mcEff_eta2.SetLineColor(600 - 6)

dataEff_eta0.SetMaximum(1.0)
dataEff_eta1.SetMaximum(1.0)
dataEff_eta2.SetMaximum(1.0)
mcEff_eta0.SetMaximum(1.0)
mcEff_eta1.SetMaximum(1.0)
mcEff_eta2.SetMaximum(1.0)

effCanv = TCanvas("effCanv", "Tag & Probe Efficiencies", 1000, 600)

ratio_eta0 = TRatioPlot(dataEff_eta0, mcEff_eta0, "divsym")
ratio_eta0.SetH1DrawOpt("e")
ratio_eta0.SetH2DrawOpt("e")
ratio_eta1 = TRatioPlot(dataEff_eta1, mcEff_eta1, "divsym")
ratio_eta1.SetH1DrawOpt("e")
ratio_eta1.SetH2DrawOpt("e")
ratio_eta2 = TRatioPlot(dataEff_eta2, mcEff_eta2, "divsym")
ratio_eta2.SetH1DrawOpt("e")
ratio_eta2.SetH2DrawOpt("e")

effCanv.Divide(3,1)
effCanv.cd(1)
ratio_eta0.Draw()
gPad.Modified()
gPad.Update()
pad0 = ratio_eta0.GetUpperPad()
leg0 = pad0.BuildLegend(0.5, 0.3, 0.9, 0.5)
leg0.Clear()
leg0.AddEntry(dataEff_eta0, "Data 2018", "ep")
leg0.AddEntry(mcEff_eta0, "MC 2018", "ep")
pad0.Modified()
pad0.Update()

effCanv.cd(2)
ratio_eta1.Draw()
gPad.Modified()
gPad.Update()
pad1 = ratio_eta1.GetUpperPad()
leg1 = pad1.BuildLegend(0.5, 0.3, 0.9, 0.5)
leg1.Clear()
leg1.AddEntry(dataEff_eta1, "Data 2018", "ep")
leg1.AddEntry(mcEff_eta1, "MC 2018", "ep")
pad1.Modified()
pad1.Update()


effCanv.cd(3)
ratio_eta2.Draw()
gPad.Modified()
gPad.Update()
pad2 = ratio_eta2.GetUpperPad()
leg2 = pad2.BuildLegend(0.5, 0.3, 0.9, 0.5)
leg2.Clear()
leg2.AddEntry(dataEff_eta2, "Data 2018", "ep")
leg2.AddEntry(mcEff_eta2, "MC 2018", "ep")
pad2.Modified()
pad2.Update()

effCanv.SaveAs("Plots/tnpEffCurves.png")


sfCanv = TCanvas("sfCanv", "Tag & Probe Scale Factors", 600, 600)
sfCanv.cd()

for i in range(len(etaBinLowEdges)):
    hSFs.GetXaxis().SetBinLabel(i, etaBinLabels[i-1])
    for j in range(len(ptBinLowEdges)-1):
        hSFs.GetYaxis().SetBinLabel(j, ptBinLabels[j-1])
        
        #hSFs.SetBinError(i, j, err)

gStyle.SetPaintTextFormat("4.2f")

hSFs.Draw("col text")

sfCanv.SaveAs("Plots/tnpSFs.png")



