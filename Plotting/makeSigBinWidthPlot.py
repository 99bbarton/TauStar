# Make a plot of signal bin widths

from ROOT import TCanvas, TGraphErrors
from array import array


canv = TCanvas("canv", "Signal Bin Widths", 800, 800)
canv.SetLeftMargin(0.15)

masses = array("f", [175, 250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000, 4500, 5000])
fracWidths = array("f", [0.47, 0.35, 0.26, 0.21, 0.19, 0.17, 0.15, 0.13, 0.12, 0.11, 0.11, 0.10, 0.10, 0.10, 0.11, 0.13, 0.16])
widths = []
xWidths = []
nMasses = len(masses)

tableStr = ""
print("\nMass,[BinLowEdge,BinHighEdge]")
for massN, mass in enumerate(masses):
    widths.append(fracWidths[massN] * masses[massN])
    xWidths.append(0)
    print(str(mass) + ", [" + "{:.6}".format(mass - widths[-1]) + ", " + "{:.6}".format(mass + widths[-1]) + "]")
    tableStr += "[" + "{:.6}".format(mass - widths[-1]) + ", " + "{:.6}".format(mass + widths[-1]) + "]&"

tableStr = tableStr[:-1]
print("\n" + tableStr + "\n")

widths = array("f", widths)
xWidths = array("f", xWidths)

graph = TGraphErrors(nMasses, masses, masses, xWidths, widths)
graph.SetTitle("Signal L-Band Widths;#tau* Hypothesis Mass [GeV];Signal Bin Mass Coverage [GeV]")
graph.SetMarkerStyle(5)
graph.SetMarkerSize(2)

graph.Draw("AP")

canv.SaveAs("signalBinWidths.png")
canv.SaveAs("signalBinWidths.pdf")

resp = raw_input("Hit Enter to close... ")
