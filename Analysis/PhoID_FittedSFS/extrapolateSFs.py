#Calculate scale factors of highest pt bins via linear extrapolation
#Following the example layed out here: https://twiki.cern.ch/twiki/bin/view/CMS/EGMPhotonIDHighPtPhotons

import sys
import os
from ROOT import TH2F, TCanvas, gStyle, TFile, TGraph
from array import array
from math import sqrt

##Make new SF and uncertainty histograms with an additional pT bin
##Note, binning is hardcoded and must be altered manually if needed
# filepath : filename and path of root file containing SFs to extrapolate
def addHigherPtBins(filepath=""):

    inFile = TFile(filepath, "read")

    #Get 2D efficiency plots and SF plots
    hists_old = []
    hists_old.append(inFile.Get("EGamma_EffData2D"))
    hists_old.append(inFile.Get("EGamma_EffMC2D"))
    hists_old.append(inFile.Get("EGamma_SF2D"))
    hists_old.append(inFile.Get("statData"))
    hists_old.append(inFile.Get("statMC"))
    hists_old.append(inFile.Get("altMCEff"))


    #Define binning, since bins are custom, unfortunately must be hardcoded
    #The highest pT bin does not exist in the hists read above but will be added to those below
    etaBins = [-2.5, -2.0, -1.566, -1.4442, -0.8, 0.0, 0.8, 1.4442, 1.566, 2.0, 2.5]
    etaBins = array('f', etaBins)
    etaBinCents = [-2.25, -1.78, -1.5, -1.12, -0.4, 0.4, 1.12, 1.5, 1.78, 2.25]
    nEtaBins = len(etaBinCents)
    ptBins = [20, 35, 50, 75, 100, 200, 500, 1000, 4000]
    ptBins = array("f", ptBins)
    ptBinCents = [27.5, 42.5, 62.5, 87.5, 150, 350, 750, 2500]
    nPtBinsNew = len(ptBinCents)
    
    
    #Define new histograms to replace the old ones
    hists_new = []
    hists_new.append(TH2F("EGamma_EffData2D_new", "Photon ID Data Eff;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    hists_new.append(TH2F("EGamma_EffMC2D_new", "Photon ID MC Eff;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    hists_new.append(TH2F("EGamma_SF2D_new", "Photon ID Scale Factors;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    hists_new.append(TH2F("statData_new", "Photon ID Data Eff Stat Uncertainty;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    hists_new.append(TH2F("statMC_new", "Photon ID MC Stat Uncertainty;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    hists_new.append(TH2F("altMCEff_new", "Photon ID AltMC Syst;Photon #eta;Photon pT [GeV]", nEtaBins, etaBins, nPtBinsNew, ptBins))
    
    #Copy over bin contents and uncertainties
    for hN in range(len(hists_old)):
        for etaInd, eta in enumerate(etaBinCents):
            for ptInd, pt in enumerate(ptBinCents):
                if ptInd < (nPtBinsNew - 1): #If a bin that is present in old hists
                    bin_old = hists_old[0].FindBin(eta, pt)
                    bin_new = hists_new[0].FindBin(eta, pt)
                
                    binCont = hists_old[hN].GetBinContent(bin_old)
                    binErr = hists_old[hN].GetBinError(bin_old)

                    hists_new[hN].SetBinContent(bin_new, binCont)
                    hists_new[hN].SetBinError(bin_new, binErr)
                else:
                    bin_new = hists_new[0].FindBin(eta, pt)
                    hists_new[hN].SetBinContent(bin_new, 0) #Set the added higher pT bins to 0 for later filling
                    hists_new[hN].SetBinError(bin_new, 0)

    #Write the new hists to a new file
    outFilePath = filepath[:-5] + "_extended.root"
    outFile = TFile(outFilePath, "recreate")
    outFile.WriteObject(hists_new[0], "EGamma_EffData2D_new")
    outFile.WriteObject(hists_new[1], "EGamma_EffMC2D_new")
    outFile.WriteObject(hists_new[2], "EGamma_SF2D_new")
    outFile.WriteObject(hists_new[3], "statData_new")
    outFile.WriteObject(hists_new[4], "statMC_new")
    outFile.WriteObject(hists_new[5], "altMCEff_new")
    outFile.Close()

    return outFilePath
    

           

##Extrapolate SFs and uncertainties to high-pT bins
# filepath : filename and path of root file containing SFs to extrapolate
# ptBinsToFit : a list of pt bin centers to include in the fit for extrapolation
# binsToExtrap : a list of bin centers of the bins to replace existing efficiencies/SFs with extrapolated ones
def extrapolateSFs(filepath="", binsToExtrap=[750, 2500]):
    gStyle.SetPaintTextFormat("4.2f")
    gStyle.SetOptStat(0)

    inFile = TFile(filepath, "read")
    #Get 2D efficiency plots and SF plots
    effData = inFile.Get("EGamma_EffData2D_new")
    effMC = inFile.Get("EGamma_EffMC2D_new")
    sf2D = inFile.Get("EGamma_SF2D_new")
    statData2D =  inFile.Get("statData_new")
    statMC2D =  inFile.Get("statMC_new")
    altEffMC2D = inFile.Get("altMCEff_new")

    canv = TCanvas("canv", "SF Comparison", 1000, 600)
    canv.Divide(2,1)
    canv.cd(1)


    sfCopy= sf2D.Clone()
    sfCopy.Draw("colz texte")
    canv.SetLogy()

    nEtaBins = effData.GetNbinsX()
    etaBins = [-2.125, -1.783, -1.505, -1.122, -0.4, 0.4, 1.122, 1.505, 1.783, 2.125] #Eta bin centers
    ptBinsToFit=[62.5, 87.5, 150, 350]
    ptGraphBins = array("f", ptBinsToFit)

    #Find the central (avg) pT value of the fit bins for later use in weighting the extrapolation
    lowBin = effData.FindBin(etaBins[0], ptBinsToFit[0])
    highBin = effData.FindBin(etaBins[0], ptBinsToFit[-1])
    ptAvgInFit = ((effData.GetYaxis().GetBinLowEdge(highBin) + effData.GetYaxis().GetBinWidth(highBin)) - effData.GetYaxis().GetBinLowEdge(lowBin)) / 2


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

        binToFillY= effData.GetNbinsY() - (len(binsToExtrap) - 1)
        for binToExtrap in binsToExtrap:
            #Extrapolate a new efficiency
            extrapValData = (binToExtrap * slopeData) + interData #eff_new = (m_data * x) + b_data
            extrapErrData = sqrt(((interData**2) * (interDataErr**2)) + ((slopeData**2) * (slopeDataErr**2)) + (2 * slopeData * interData * covData01)) #Full err propagation   
            extrapValMC = (binToExtrap * slopeMC) + interMC # Sim for MC
            extrapErrMC = sqrt(((interMC**2) * (interMCErr**2)) + ((slopeMC**2) * (slopeMCErr**2)) + (2 * slopeMC * interMC * covMC01))
            #Weight on error from eqn (2) here: https://w3.pppl.gov/~hammett/work/1999/stderr.pdf
            extrapBinWidth = effData.GetYaxis().GetBinWidth(effData.FindBin(etaBins[0], binToExtrap)) #The width of bin were extrapolating
            extrapErrWeight = (binToExtrap - ptAvgInFit) / extrapBinWidth
            extrapErrWeight = (1 + extrapErrWeight**2) / len(ptBinsToFit)
        

            #Set new last bin efficiency contents
            binToFill = effData.GetBin(x, binToFillY)
            effData.SetBinContent(binToFill, extrapValData)
            effMC.SetBinContent(binToFill, extrapValMC)

            #Calculate and store new SFs and uncertainties
            #Uncertainties added in quadrature from data and MC extrapolation and then added in quadrature to existing error
            newSF = extrapValData / extrapValMC
            newSFErr = (extrapErrData * extrapErrData * extrapErrWeight) + (extrapErrMC * extrapErrMC * extrapErrWeight) #Actually the squared error
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

            print("New sf +/- err for (" + str(x) + ", " + str(binToFillY) + ")= " + str(newSF) + " +/- " + str(newSFErr))

            binToFillY += 1
    

    canv.cd(2)
    sf2D.Draw("colz texte")
    canv.SetLogy()

    buff = raw_input("Hit enter to close: ")

    os.system("cp " + filepath + " " + filepath[:-5] + "_extrap.root" )
    outFile = TFile(filepath[:-5] + "_extrap.root", "recreate")
    outFile.WriteObject(sf2D, "EGamma_SF2D")
    outFile.WriteObject(effData, "EGamma_EffData2D")
    outFile.WriteObject(effMC, "EGamma_EffMC2D")

    outFile.Close()


if __name__ == "__main__":
    if len(sys.argv) == 2:
        extendedFilePath = addHigherPtBins(sys.argv[1])
        extrapolateSFs(extendedFilePath)
    else:
        print("USAGE: extrapolateSFs.py <input file path>")





        

    



            



