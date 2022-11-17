#The uncertainties on Tag and Probe effs and SFs are by default stored in EGamma_SF2D and separate systematics hists
#This script takes those uncertainties and also writes them to BinErrors of the EffData2D and EffMC2D histograms

import sys
from math import sqrt
from ROOT import TFile, TH2F


##Writes errors from data to EffData2D and MC to EffMC2D
# filepath : path to input file
#Output file is filepath + _effsHaveErrs.
def writeErrsToEffData2D(filepath):
    inFile = TFile(filepath, "read")

    #Read in the data
    h_effData2D = inFile.Get("EGamma_EffData2D")
    h_effMC2D = inFile.Get("EGamma_EffMC2D")
    h_SF2D = inFile.Get("EGamma_SF2D")
    h_statData = inFile.Get("statData")
    h_statMC = inFile.Get("statMC")
    h_altMCEff = inFile.Get("altMCEff")
    h_altTagSelection = inFile.Get("altTagSelection")
    h_altBkgModel = inFile.Get("altBkgModel")
    h_altSignalModel = inFile.Get("altSignalModel")

    #Combine and write errors to EffMC2D and EffData2D
    for xBin in range(h_effData2D.GetNbinsX()+1):
        for yBin in range(h_effData2D.GetNbinsY()+1):

            #Data
            dataErrs = []
            #dataErrs.append(h_effData2D.GetBinError(xBin, yBin))
            dataErrs.append(h_statData.GetBinContent(xBin, yBin)) 
            dataErrs.append(h_altBkgModel.GetBinContent(xBin, yBin))
            dataErrs.append(h_altSignalModel.GetBinContent(xBin, yBin))
            dataCombErr = combineErrors(dataErrs)
            h_effData2D.SetBinError(xBin, yBin, dataCombErr)

            #MC
            mcErrs = []
            #mcErrs.append(h_effMC2D.GetBinError(xBin, yBin)) #Zero by default in TNP code
            mcErrs.append(h_statMC.GetBinContent(xBin, yBin)) 
            mcErrs.append(h_altMCEff.GetBinContent(xBin, yBin))
            mcErrs.append(h_altTagSelection.GetBinContent(xBin, yBin))
            
            mcCombErr = combineErrors(mcErrs)
            h_effMC2D.SetBinError(xBin, yBin, mcCombErr)

    #Write histograms to output file
    outFilePath = filepath[:-5] + "_effsHaveErrs.root"
    outFile = TFile(outFilePath, "recreate")
    outFile.WriteObject(h_SF2D, "EGamma_SF2D")
    outFile.WriteObject(h_effData2D, "EGamma_EffData2D")
    outFile.WriteObject(h_effMC2D, "EGamma_EffMC2D")
    outFile.WriteObject(h_statData, "statData")
    outFile.WriteObject(h_statMC, "statMC")
    outFile.WriteObject(h_altMCEff, "altMCEff") 
    outFile.WriteObject(h_altTagSelection, "altTagSelection") 
    outFile.WriteObject(h_altBkgModel, "altBkgModel") 
    outFile.WriteObject(h_altSignalModel, "altSignalModel") 
    outFile.Close()    


##Combine values in errors in quadrature
# errors : a list of error values to combine
#returns : combined error
def combineErrors(errors):
    combErr = 0
    for err in errors:
        combErr += err**2
    return sqrt(combErr)
    


if __name__ == "__main__":
    if len(sys.argv) == 2:
        writeErrsToEffData2D(sys.argv[1])
    else:
        print("USAGE: writeErrsToEffData2D.py <filepath>")

