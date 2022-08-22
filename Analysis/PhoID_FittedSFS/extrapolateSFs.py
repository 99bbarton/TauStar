#Calculate scale factors of highest pt bins via linear extrapolation
#Following the example layed out here: https://twiki.cern.ch/twiki/bin/view/CMS/EGMPhotonIDHighPtPhotons

import sys
import os
from ROOT import TH2F, TCanvas, gStyle, TFile, TGraph
from array import array
from math import sqrt

##
#@param filepath : filename and path of root file containing SFs to extrapolate
#@param ptBinsToFit : a list of pt bin centers to include in the fit for extrapolation
#@param binToExtrap : bin center of the bin to replace existing efficiencies/SFs with extrapolated ones
def extrapolateSFs(filepath="", binToExtrap=750):
    gStyle.SetPaintTextFormat("4.2f")
    gStyle.SetOptStat(0)

    inFile = TFile(filepath, "read")
    #Get 2D efficiency plots and SF plots
    effData = inFile.Get("EGamma_EffData2D")
    effMC = inFile.Get("EGamma_EffMC2D")
    sf2D = inFile.Get("EGamma_SF2D")
    statData2D =  inFile.Get("statData")
    statMC2D =  inFile.Get("statMC")
    altEffMC2D = inFile.Get("altMCEff")

    canv = TCanvas("canv", "SF Comparison", 1000, 600)
    canv.Divide(2,1)
    canv.cd(1)
    canv.SetLogy()

    sfCopy= sf2D.Clone()
    sfCopy.Draw("colz texte")

     #fitCanv = TCanvas("fitCanv", "Fit Examination", 600, 600)

    nEtaBins = effData.GetNbinsX()
    etaBins = [-2.125, -1.783, -1.505, -1.122, -0.4, 0.4, 1.122, 1.505, 1.783, 2.125] #Eta bin centers
    ptBinsToFit=[67.5, 87.5, 150, 350]
    ptGraphBins = array("f", ptBinsToFit)

    for x, eta in enumerate(etaBins):
        fitBinsData = []
        fitBinsMC = []
        x=x+1
        for y, pt in enumerate(ptBinsToFit): #Copy the bin contents of the bins specified by ptBinsToFit to make graphs
            bin = effData.FindBin(eta, pt)
            fitBinsData.append(effData.GetBinContent(bin))
            fitBinsMC.append(effMC.GetBinContent(bin))
        
        fitBinsData = array("f", fitBinsData)
        fitBinsMC = array("f", fitBinsMC)

        #Make a graph of the extracted efficiencies
        graphData = TGraph(len(ptGraphBins), ptGraphBins, fitBinsData)
        graphMC = TGraph(len(ptGraphBins), ptGraphBins, fitBinsMC)
        
        #Fit a line to the graphs and extract parameters
        fitResultData = graphData.Fit("pol1", "SQ", "AP") #Remove the Q option to show fit results
        fitResultMC = graphMC.Fit("pol1", "SQ", "AP")

        interData = fitResultData.Parameter(0)
        interDataErr = fitResultData.Error(0)
        slopeData = fitResultData.Parameter(1)
        slopeDataErr = fitResultData.Error(1)
        covData01 = fitResultData.CovMatrix(0,1)
        interMC = fitResultMC.Parameter(0)
        interMCErr = fitResultMC.Error(0)
        slopeMC = fitResultMC.Parameter(1)
        slopeMCErr = fitResultMC.Error(1)
        covMC01 = fitResultMC.CovMatrix(0,1)

        #Extrapolate a new efficiency
        prevBinCent = ptBinsToFit[-1]
        extrapValData = (binToExtrap * slopeData) + interData #eff_new = m_data * x + b_data
        extrapErrData = sqrt(((interData**2) * (interDataErr**2)) + ((slopeData**2) * (slopeDataErr**2)) + (2 * slopeData * interData * covData01)) #Full err propagation   
        extrapValMC = (binToExtrap * slopeMC) + interMC # Sim for MC
        extrapErrMC = sqrt(((interMC**2) * (interMCErr**2)) + ((slopeMC**2) * (slopeMCErr**2)) + (2 * slopeMC * interMC * covMC01))

        #Set new last bin efficiency contents
        binToFill = effData.GetBin(x, effData.GetNbinsY())
        effData.SetBinContent(binToFill, extrapValData)
        effMC.SetBinContent(binToFill, extrapValMC)

        #Calculate and store new SFs and uncertainties
        #Uncertainties added in quadrature from data and MC extrapolation and then added in quadrature to existing error
        newSF = extrapValData / extrapValMC
        newSFErr = (extrapErrData * extrapErrData) + (extrapErrMC * extrapErrMC) #Actually the squared error
        oldErr = sf2D.GetBinError(binToFill)
        statDataErr = statData2D.GetBinContent(binToFill)
        statMCErr = statMC2D.GetBinContent(binToFill)
        altMCErr = altEffMC2D.GetBinContent(binToFill)
        #Since we're replacing the SF calculated from data with one from extrapolation, stat error is no longer relevant
        #We therefore need to remove the old stat errors by subtracting out in quadrature
        #Also remove altMC systematic as per pog guidance
        oldErr = oldErr**2
        statDataErr = statDataErr**2
        statMCErr = statMCErr**2
        altMCErr = altMCErr**2
        oldErr = oldErr - statDataErr - statMCErr - altMCErr
        newSFErr = sqrt(newSFErr + oldErr)  
        sf2D.SetBinContent(binToFill, newSF)
        sf2D.SetBinError(binToFill, newSFErr)

        print("New sf +/- err = " + str(newSF) + " +/- " + str(newSFErr))
    

    canv.cd(2)
    canv.SetLogy()
    sf2D.Draw("colz texte")

    buff = raw_input("Hit enter to close: ")

    os.system("cp " + filepath + " " + filepath[:-5] + "_extrap.root" )
    outFile = TFile(filepath[:-5] + "_extrap.root", "recreate")
    outFile.WriteObject(sf2D, "EGamma_SF2D")
    outFile.WriteObject(effData, "EGamma_EffData2D")
    outFile.WriteObject(effMC, "EGamma_EffMC2D")

    outFile.Close()


if __name__ == "__main__":
    extrapolateSFs(sys.argv[1])
    





        

    



            



