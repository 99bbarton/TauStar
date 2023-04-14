# A script to produce the HEPData submission for the Taustar analysis (EXO-22-007)
#Must be run from an environment with HEPDataLib installed e.g having sourced: source HEPDataEnv/bin/activate for my venv setup

import numpy as np
import pandas as pd
from hepdata_lib import Submission, Table, Variable, Uncertainty, RootFileReader
from time import sleep

##--------------------------------------------------------------------------------------------------------------------------------

#Makes a HEPData_lib Table object of the signal process cut flow
#\param filepath : a string containing the filename and path to file containing cutflow information. Assumed to be in a CSV format
#\returns A Table object containing the cut flow information 
def makeCutFlowTable(filepath):
    print("Making cutflow table...")

    dataframe = pd.read_csv(filepath, sep=",", header=0, index_col=False)
    channelMap = {"ETau" : 1, "MuTau" : 2, "TauTau" : 3} #HEPDatalib variables can only hold numerical values, not strings
    for ch in channelMap.keys():
        dataframe.replace(ch, channelMap[ch], inplace = True)

    table = Table("Signal Process Cutflow")
    table.description = """Signal process cutflow for all taustar hypothesis masses, channels, and years.
    Channel map: {1 = ETau, 2 = MuTau, 3 = TauTau}
    Cut descriptions:
        - numLeps : 1e0mu for ETau, 0e1mu For muTau, 0e0mu for TauTau 
        - havePair : 1e + 1tauh for ETau, 1mu + 1tauh for MuTau, 2tauh for TauTau
        - trigger : passed appropriate high level trigger (HLT) for channel and year
        - m_vis : Visible mass of pair is >= 100 GeV
        - Zveto : No Z->ee or Z->mumu pairs
        - bveto : No btagged jets in event (only for ETau and MuTau)
        - gamma20GeV : have a photon with pt>20GeV
        - gamma100GeV : have a photon with pt>20GeV"""

    #Add the different signal processes to the table
    year = Variable("Year", is_independent=True, is_binned=False)
    year.values = dataframe["year"]   
    table.add_variable(year) 
    mass = Variable("Taustar Mass", is_independent=True, is_binned=False, units="GeV")
    mass.values = dataframe["mass"]
    table.add_variable(mass)
    channel = Variable("Channel", is_independent=True, is_binned=False)
    channel.values = dataframe["channel"]
    table.add_variable(channel)

    #Add the cut flow to the table
    for colN in range(3,len(dataframe.columns) - 3, 2):
        cutVar = Variable(dataframe.columns[colN], is_independent=False, is_binned=False, units="Expected Events")
        cutVar.values = dataframe[dataframe.columns[colN]]
        cutErr = Uncertainty(dataframe.columns[colN+1], is_symmetric = True)
        cutErr.values = dataframe[dataframe.columns[colN+1]]
        cutVar.add_uncertainty(cutErr)
        
        table.add_variable(cutVar)
        
    return table       

##--------------------------------------------------------------------------------------------------------------------------------

#Make a set of HEPData_lib Tables containing the total covariance matrices for each year, taustar mass, channel, and region
#\WARNING: Assumes a set of years, taustar masses, filename format for the output files from combine, channel mapping, and ROOT layout in the file
#\param dirPath : a string containing the path to the directory containing the fiDiagnostics combine output files
#\param includeSignalRegion : whether or not to include the signal region's covariance information in the table. default is False.
#\returns tables : a list of HEPData_lib Table objects, one for each year in the years list initialize below
def makeCovarianceTables(dirPath, includeSignalRegion=False):
    print("Making covariance matrice tables...")
    if includeSignalRegion: #Safety check against including signal region information
        print("\n\n WARNING: You have chosen to include the signal region (A) total covariance matrix in the table.")
        response = raw_input("Are you sure you wish to continue? Enter YES to continue or anything else to abort")
        if response != "YES":
            exit(-1)
    
    #Initialize what data to include and how to access+label it
    years = ["2015", "2016", "2017", "2018"]
    masses = [175,250,375,500,625,750,1000,1250,1500,1750,2000,2500,3000,3500,4000,4500,5000]
    filebase = "fitDiagnosticsTest_m"
    pathToHistBase = "shapes_fit_b/"
    #channels = {"ch1":"ETau","ch2":"MuTau","ch3":"TauTau","ch4":"ETauLowPt","ch5":"MuTauLowPt","ch6":"TauTauLowPt","ch7":"EE","ch8":"MuMu","ch9":"EMu"}
    channelMap = {"ch1":1,"ch2":2,"ch3":3,"ch4":4,"ch5":5,"ch6":6,"ch7":7,"ch8":8,"ch9":9}
    regionMap = {"A" : 1, "A1":2, "A3":3, "B1" : 4, "B3" : 5, "C1":6, "C3":7, "D1":8, "D3":9}

    tables = []

    for yearN, year in enumerate(years):
        #Initialize the year's table
        tableTitle = "Total Covariance for "
        if year == "0":
            tableTitle += "All Periods"
        elif year == "2015":
            tableTitle += "2016preHiPM"
        elif year == "2016":
            tableTitle += "2016postHiPM"
        else:
            tableTitle += year
        tables.append(Table(tableTitle))

        #Initialize the variables which will be added to the table
        var_mass = Variable("TauStar Hypothesis Mass", is_independent=True, is_binned=False, units="GeV/c^2")
        var_ch = Variable("Analysis Channel", is_independent=True, is_binned=False)
        var_reg = Variable("Region", is_independent = True, is_binned=False)
        var_binNumX = Variable("Bin Number X", is_independent=True, is_binned=False)
        var_binNumY = Variable("Bin Number Y", is_independent=True, is_binned=False)
        var_cov = Variable("Total Covariance", is_independent=False, is_binned=False)

        #Read in each file and extract total covariance matrix for each channel and region
        for mass in masses:
            filename = filebase + str(mass) + "y" + year + ".root"
            fileReader = RootFileReader(dirPath + filename)
    
            for chCount, chNum in enumerate(channelMap.keys()):
                #Channels each have different regions, create the appropriate list
                if chCount < 3:
                    regions = ["B1", "B3", "C1", "C3", "D1", "D3"]
                    if includeSignalRegion:
                        regions.insert(0, "A")
                elif chCount < 6:
                    regions = ["A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"]
                else:
                    regions = ""
                    
                for region in regions: 
                    covHistDict = fileReader.read_hist_2d(pathToHistBase + chNum + "_" + region + "/total_covar")
                    var_binNumX.values.extend(covHistDict["x"])
                    var_binNumY.values.extend(covHistDict["y"])
                    var_cov.values.extend(covHistDict["z"])

                    #Need to add indep var entries corresponding to each new covariance value
                    numVals = len(covHistDict["z"])
                    if len(covHistDict["x"]) != numVals:
                        print("WARNING x values have different length")
                    if len(covHistDict["y"]) != numVals:
                        print("WARNING y values have different length")
                    #assert len(covHistDict["y"]) == numVals

                    for i in range(numVals):
                        var_mass.values.append(mass)
                        var_ch.values.append(channelMap[chNum])
                        var_reg.values.append(regionMap[region])

        #Complete the year's table
        tables[yearN].add_variable(var_mass)
        tables[yearN].add_variable(var_ch)
        tables[yearN].add_variable(var_reg)
        tables[yearN].add_variable(var_binNumX)
        tables[yearN].add_variable(var_binNumY)
        tables[yearN].add_variable(var_cov)
        tables[yearN].description = """Background-only-fit total covariance matrix for all channels and regions. 
        Values are extracted from the Higgs Combine tool's fitDiagnostics option. 
        Channel map: {1=ETau, 2=MuTau, 3=TauTau, 4=ETauLowPt, 5=MuTauLowPt, 6=TauTauLowPt, 7=EE, 8=MuMu, 9=EMu}
        Region map: {1=A, 2=A1, 3=A3, 4=B1, 5=B3, 6=C1, 7=C3, 8=D1, 8=D3}
        Please see associated image ("fitRegions.pdf") for guide on region and channel setup."""
        tables[yearN].add_image("Inputs/fitRegions.pdf")

    return tables

##--------------------------------------------------------------------------------------------------------------------------------

#Make a HEPDataLib table of the fractional widths of the mass L-band windo used as signal regions
#Width values are the minimum widths where 90% of the signal for each taustar hypothesis mass falls within the L-band
def makeLBandWidthsTable():
    print("Making L-band widths table...")

    table = Table("Signal Region L-Band Widths")
    table.description = """The signal region is defined a an L-shaped band in the 2D collinear mass plane (min vs max collinear mass). 
    The width of the band is chosen to be the value such that 90% of signal falls within the band for each taustar hypothesis mass """

    mass = Variable("TauStar Hypothesis Mass", is_binned = False, is_independent = True, units = "GeV/c^2")
    mass.values = [175,250,375,500,625,750,1000,1250,1500,1750,2000,2500,3000,3500,4000,4500,5000]
    widths = Variable("Fractional Width of L-Band", is_independent = False, is_binned = False)
    widths.values = [0.47, 0.35, 0.26, 0.21, 0.19, 0.17, 0.15, 0.13, 0.12, 0.11, 0.11, 0.10, 0.10, 0.10, 0.11, 0.13, 0.16]

    assert len(mass.values) == len(widths.values)

    table.add_variable(mass)
    table.add_variable(widths)

    return table

##--------------------------------------------------------------------------------------------------------------------------------


## Produce a table of reco, ID, and trigger efficiencies for electrons
# File paths are hardcoded and of the form effs_el_<eff type>_<year>.root. They were sourced and renamed from the following:
# reco : https://twiki.cern.ch/twiki/pub/CMS/EgammaUL2016To2018/  Reco SF files of the form: egammaEffi_ptAbove20.txt_EGM2D_UL2018.root
# ID   : https://twiki.cern.ch/twiki/pub/CMS/EgammaUL2016To2018/ MVA ID WP90 SF files of the form: egammaEffi.txt_Ele_wp90iso_EGM2D.root
# trig : Calculated via EGamma TNP packages and stored in files of the form: singleElTrigEff_2015_effsHaveErrs.root found at:
# /store/user/bbarton/TrigEffStudies/SingleElTrigEff/PassingMVAID/FineEtaBinning/PhotonOR/
# Returns a HEPDataLib Table object containing the efficiencies
#TODO add plots as images
def makeEffTableEl():

    #Define HEPData objects
    tab = Table("Electron Efficiencies")
    tab.description = """Reco, ID, and trigger efficiencies observed in MC for electrons.'Type' 0 = Reco, 1 = ID, 2 = trigger"""
    var_year = Variable("Year", is_independent=True, is_binned=False)
    var_effType = Variable("Type", is_independent=True, is_binned=False) #Reco = 0, ID = 1, Trig = 2 since strs not supported
    var_eta = Variable("abs(eta)", is_independent=True, is_binned=True)
    var_pt = Variable("pT", is_independent=True, is_binned=True, units="GeV/c" )
    var_eff = Variable("Efficiency in MC", is_independent=False, is_binned=False)
    #Technically this should not be symmetric (upper bound on eff of 100%), however th2 objects which provide the uncertainties have symmetric errors
    var_effErr = Uncertainty("Efficiency Uncertainty", is_symmetric=True)  
 
    for year in [2015, 2016, 2017, 2018]:
        yrStr = str(year)

        #Get data from ROOT files
        #NB By default, the eff histograms in EGamma TNP output files don't have errors (separate histograms)
        #I have used: https://github.com/99bbarton/TauStar/blob/main/Analysis/TNP/writeErrsToEffHists.py
        # to write the appropriate errors to the eff histograms so that the data can be read in more easily here
        effDict_reco = RootFileReader.read_hist_2D("effs_el_reco_" + yrStr + "/EGamma_EffMC2D")
        effDict_ID = RootFileReader.read_hist_2D("effs_el_ID_" + yrStr + "/EGamma_EffMC2D")
        effDict_trig = RootFileReader.read_hist_2D("effs_el_trig_" + yrStr + "/EGamma_EffMC2D")
    
        #Add data to the Variable/Uncertainty objects
        numEntries_reco = len(effDict_reco["z"])
        numEntries_ID = len(effDict_ID["z"])
        numEntries_trig = len(effDict_trig["z"])
        numEntriesForYear = numEntries_reco + numEntries_ID + numEntries_trig

        var_year.values.extend([year] * numEntriesForYear)

        var_effType.values.extend([0] * numEntries_reco)
        var_effType.values.extend([1] * numEntries_ID)
        var_effType.values.extend([2] * numEntries_trig)

        var_eta.values.extend(effDict_reco["x_edges"])
        var_eta.values.extend(effDict_ID["x_edges"])
        var_eta.values.extend(effDict_trig["x_edges"])

        var_pt.values.extend(effDict_reco["y_edges"])
        var_pt.values.extend(effDict_ID["y_edges"])
        var_pt.values.extend(effDict_trig["y_edges"])

        var_eff.values.extend(effDict_reco["z"])
        var_eff.values.extend(effDict_ID["z"])
        var_eff.values.extend(effDict_trig["z"])

        var_effErr.values.extend(effDict_reco["dz"])
        var_effErr.values.extend(effDict_ID["dz"])
        var_effErr.values.extend(effDict_trig["dz"])

    #Add the variables to the table
    var_eff.add_uncertainty(var_effErr)

    tab.add_variable(var_year)
    tab.add_variable(var_effType)
    tab.add_variable(var_eta)
    tab.add_variable(var_pt)
    tab.add_variable(var_eff)

    return tab

##--------------------------------------------------------------------------------------------------------------------------------

# Create the HEPData submission
def makeSubmission():
    submission = Submission()

    #Add cutflow table
    table_cutFlow = makeCutFlowTable("Cutflows/signalCutflow_08Feb23.csv")
    table_cutFlow.keywords["observables"] = ["N"]
    submission.add_table(table_cutFlow)
    print("...cutflow table added to submission")

    #Add covariance matrice tables
    tables_covar = makeCovarianceTables(dirPath="CovarianceMatrices/")
    for table in tables_covar:
        submission.add_table(table)
    print("...covariance tables added to submission")

    table_LBandWidths = makeLBandWidthsTable()
    submission.add_table(table_LBandWidths)
    print("...L-Band widths table added to submission")

    print("Adding text...")
    for table in submission.tables:
        table.keywords["cmenergies"] = ["13000"] 
    submission.read_abstract("Inputs/abstract.txt")
    submission.add_link("CMS CADI", "https://cms.cern.ch/iCMS/analysisadmin/cadilines?line=EXO-22-007")
    print("...text added to submission") 


    print("Creating files...")
    submission.create_files("TestOutput/", remove_old=True)

if __name__ == "__main__":
    makeSubmission()

