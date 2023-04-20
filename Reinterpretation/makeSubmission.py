# A script to produce the HEPData submission for the Taustar analysis (EXO-22-007)
#Must be run from an environment with HEPDataLib installed e.g having sourced: source HEPDataEnv/bin/activate for my venv setup

import numpy as np
import pandas as pd
from hepdata_lib import Submission, Table, Variable, Uncertainty, RootFileReader
from math import sqrt

##--------------------------------------------------------------------------------------------------------------------------------

#Makes a HEPData_lib Table object of the signal process cut flow
#filepath : a string containing the filename and path to file containing cutflow information. Assumed to be in a CSV format
#returns A Table object containing the cut flow information 
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
#WARNING: Assumes a set of years, taustar masses, filename format for the output files from combine, channel mapping, and ROOT layout in the file
#dirPath : a string containing the path to the directory containing the fiDiagnostics combine output files
#includeSignalRegion : whether or not to include the signal region's covariance information in the table. default is False.
#tables : a list of HEPData_lib Table objects, one for each year in the years list initialize below
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
        var_mass = Variable("TauStar Hypothesis Mass", is_independent=True, is_binned=False, units="GeV")
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

    mass = Variable("TauStar Hypothesis Mass", is_binned = False, is_independent = True, units = "GeV")
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
# All files have been run through  https://github.com/99bbarton/TauStar/blob/main/Analysis/TNP/writeErrsToEffHists.py See note below
# Returns a HEPDataLib Table object containing the efficiencies
#TODO add plots as images
def makeEffTableEl():

    #Define HEPData objects
    tab = Table("Electron Efficiencies")
    tab.description = """Reco, ID, and trigger efficiencies observed in MC for electrons.'Type' 0 = Reco, 1 = ID, 2 = trigger"""
    var_year = Variable("Year", is_independent=True, is_binned=False)
    var_effType = Variable("Type", is_independent=True, is_binned=False) #Reco = 0, ID = 1, Trig = 2 since strs not supported
    var_eta = Variable("abs(eta)", is_independent=True, is_binned=True)
    var_pt = Variable("pT", is_independent=True, is_binned=True, units="GeV" )
    var_eff = Variable("Efficiency in MC", is_independent=False, is_binned=False)
    #Technically this should not be symmetric (upper bound on eff of 100%), however th2 objects which provide the uncertainties have symmetric errors
    var_effErr = Uncertainty("Efficiency Uncertainty", is_symmetric=True)  

    for year in [2015, 2016, 2017, 2018]:
        yrStr = str(year)

        #Get data from ROOT files
        #NB By default, the eff histograms in EGamma TNP output files don't have errors (separate histograms)
        #I have used: https://github.com/99bbarton/TauStar/blob/main/Analysis/TNP/writeErrsToEffHists.py
        # to write the appropriate errors to the eff histograms so that the data can be read in more easily here
        effDict_reco = RootFileReader("Efficiencies/effs_el_reco_" + yrStr + ".root").read_hist_2d("EGamma_EffMC2D")
        effDict_ID = RootFileReader("Efficiencies/effs_el_ID_" + yrStr + ".root").read_hist_2d("EGamma_EffMC2D")
        effDict_trig = RootFileReader("Efficiencies/effs_el_trig_" + yrStr + ".root").read_hist_2d("EGamma_EffMC2D")
    
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

## Produce a table of reco, ID, and trigger efficiencies for muons. ID, trigger are chosen to match MuTau channel selections
# File paths are hardcoded and of the form effs_mu_<eff type>_<year>.* . They were sourced and renamed from the following (2018 shown as example):
# reco : https://gitlab.cern.ch/cms-muonPOG/muonefficiencies/-/blob/master/Run2/UL/2018/NUM_TrackerMuons_DEN_genTracks_Z_abseta_pt.json
#      Reco efficiencies are not provided by the POG as TH2Fs so values from these JSONS were extracted manually to include below
# ID   : https://gitlab.cern.ch/cms-muonPOG/muonefficiencies/-/blob/master/Run2/UL/2018/2018_Z/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root
# trig : https://gitlab.cern.ch/cms-muonPOG/muonefficiencies/-/blob/master/Run2/UL/2018/2018_trigger/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root
# Returns a HEPDataLib Table object containing the efficiencies
#TODO add plots as images
def makeEffTableMu():
    
    #Define HEPData objects
    tab = Table("Muon Efficiencies")
    tab.description = """Reco, ID, and trigger efficiencies observed in MC for muons.'Type' 0 = Reco, 1 = ID, 2 = trigger"""
    var_year = Variable("Year", is_independent=True, is_binned=False)
    var_effType = Variable("Type", is_independent=True, is_binned=False) #Reco = 0, ID = 1, Trig = 2 since strs not supported
    var_eta = Variable("abs(eta)", is_independent=True, is_binned=True)
    var_pt = Variable("pT", is_independent=True, is_binned=True, units="GeV" )
    var_eff = Variable("Efficiency in MC", is_independent=False, is_binned=False)
    #Technically this should not be symmetric (upper bound on eff of 100%), however th2 objects which provide the uncertainties have symmetric errors
    var_effErr = Uncertainty("Efficiency Uncertainty", is_symmetric=True)

    #Reco efficiencies are not available from the POG as TH2Fs, only as jsons
    #Values from those JSONs were manually extracted to include below (the values' absurd quoted precision has been clipped to 5 dig after decimal)
    etaBinsReco = [(0.0, 0.9), (0.9, 1.2), (1.2, 2.1), (2.1, 2.4)]
    ptBinsReco = [(18, 50), (50, 100), (100, 200), (200, 500), (500, 1500)]
    nPtBinsReco = len(ptBinsReco)
    binsPerYrReco = len(ptBinsReco) * len(etaBinsReco)
    #Errs are in format (stat, syst)
    recoEffs_2015 = [0.99982, 1.00015, 0.99989, 0.99902] 
    recoEffErrs_2015 = [(0.00015, 0.00035), (0.00019, 0.00031), (0.00012, 0.00021), (0.00027, 0.00194)]
    recoEffs_2016 = [1.00004, 0.99979, 0.99949, 0.99907]
    recoEffErrs_2016 = [(0.00010, 0.00143), (0.00019, 0.00109), (0.00012,  0.00148), (0.00027, 0.00173)]
    recoEffs_2017 = [0.99967, 0.99978, 0.99946, 0.99935]
    recoEffErrs_2017 = [(0.00007, 0.00065), (0.00014, 0.00043), (0.00007, 0.00106), (0.00022, 0.00118)]
    recoEffs_2018 = [0.99980, 0.99975, 0.99958, 0.99903]
    recoEffErrs_2018 = [(0.00006, 0.00038), (0.00011, 0.00052), (0.00007, 0.00083), (0.00019, 0.00172)]

    #Trigger histogram names are year dependent, provide map year->name here
    trigHistNames ={2015 : "NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdTight_and_PFIsoTight_eta_pt_efficiencyMC",
                    2016 : "NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdTight_and_PFIsoTight_eta_pt_efficiencyMC",
                    2017 : "NUM_IsoMu27_DEN_CutBasedIdTight_and_PFIsoTight_abseta_pt_efficiencyMC",
                    2018 : "NUM_IsoMu24_DEN_CutBasedIdTight_and_PFIsoTight_abseta_pt_efficiencyMC"}

    for year in [2015, 2016, 2017, 2018]:
        yrStr = str(year)

        #Reco effs are appended "manually" since values were extracted from jsons
        var_year.values.extend([year] * binsPerYrReco)
        var_effType.values.extend([0] * binsPerYrReco)
        for b in range(len(etaBinsReco)):
            for ptBinN in range(nPtBinsReco):
                var_eta.values.append(etaBinsReco[b])
            var_pt.values.extend(ptBinsReco)

            if year == 2015:
                var_eff.values.extend([recoEffs_2015[b]] * nPtBinsReco) # Effs are indep of pt
                effErr = sqrt((recoEffErrs_2015[b][0] * recoEffErrs_2015[b][0]) + (recoEffErrs_2015[b][1] * recoEffErrs_2015[b][1]))
                var_effErr.values.extend([effErr] * nPtBinsReco)
            elif year == 2016:
                var_eff.values.extend([recoEffs_2016[b]] * nPtBinsReco)
                effErr = sqrt((recoEffErrs_2016[b][0] * recoEffErrs_2016[b][0]) + (recoEffErrs_2016[b][1] * recoEffErrs_2016[b][1]))
                var_effErr.values.extend([effErr] * nPtBinsReco)
            elif year == 2017:
                var_eff.values.extend([recoEffs_2017[b]] * nPtBinsReco)
                effErr = sqrt((recoEffErrs_2017[b][0] * recoEffErrs_2017[b][0]) + (recoEffErrs_2017[b][1] * recoEffErrs_2017[b][1]))
                var_effErr.values.extend([effErr] * nPtBinsReco)
            elif year == 2018:
                var_eff.values.extend([recoEffs_2018[b]] * nPtBinsReco)
                effErr = sqrt((recoEffErrs_2018[b][0] * recoEffErrs_2018[b][0]) + (recoEffErrs_2018[b][1] * recoEffErrs_2018[b][1]))
                var_effErr.values.extend([effErr] * nPtBinsReco)

        #Can extract ID and trig straight from TH2s but still need to combine syst + stat errs
        readerID = RootFileReader("Efficiencies/effs_mu_ID_" + yrStr + ".root")
        effDict_ID = readerID.read_hist_2d("NUM_TightID_DEN_TrackerMuons_abseta_pt_efficiencyMC")
        
        readerTrig = RootFileReader("Efficiencies/effs_mu_trig_" + yrStr + ".root")
        effDict_trig = readerTrig.read_hist_2d(trigHistNames[year])

        var_year.values.extend([year] * (len(effDict_ID["z"]) + len(effDict_trig["z"])))
        
        var_effType.values.extend([1] * len(effDict_ID["z"]))
        var_effType.values.extend([2] * len(effDict_trig["z"]))

        var_eta.values.extend(effDict_ID["x_edges"])
        var_eta.values.extend(effDict_trig["x_edges"])

        var_pt.values.extend(effDict_ID["y_edges"])
        var_pt.values.extend(effDict_trig["y_edges"])

        var_eff.values.extend(effDict_ID["z"])
        var_eff.values.extend(effDict_trig["z"])

        var_effErr.values.extend(effDict_ID["dz"])
        var_effErr.values.extend(effDict_trig["dz"])
        
        
    var_eff.add_uncertainty(var_effErr)

    tab.add_variable(var_year)
    tab.add_variable(var_effType)
    tab.add_variable(var_eta)
    tab.add_variable(var_pt)
    tab.add_variable(var_eff)

    return tab

##--------------------------------------------------------------------------------------------------------------------------------

## Produce a table of reco, ID, and trigger efficiencies for taus. 
# Sources of information for each efficiency type are discussed below:
# reco : Calculated using https://github.com/99bbarton/TauStar/blob/reinterpretation/Analysis/RecoEffProducer.py
#        and https://github.com/99bbarton/TauStar/blob/reinterpretation/Reinterpretation/Efficiencies/calcObjEffs.C
#        and stored here: effs_reco.root
# ID   : Calculated using https://github.com/99bbarton/TauStar/blob/reinterpretation/Reinterpretation/Efficiencies/calcObjEffs.C
#        and stored here: effs_tau_ID.root
# trig : Found here: https://github.com/cms-tau-pog/TauTriggerSFs/tree/run2_SFs/data , specifically files of the format: 2018UL_tauTriggerEff_DeepTau2017v2p1.root
# Returns a HEPDataLib Table object containing the efficiencies
#TODO add plots as images
def makeEffTableTau():
    #Define HEPData objects
    tab = Table("Tau Efficiencies")
    tab.description = """Reco, ID, and trigger efficiencies observed in MC for taus.'Type' 0 = Reco, 1 = ID, 2 = trigger"""
    var_year = Variable("Year", is_independent=True, is_binned=False)
    var_ch = Variable("Analysis Channel", is_independent=True, is_binned=False) # -1 inclusive, 0 = ETau, 1 = MuTau, 2 = TauTau,
    var_effType = Variable("Type", is_independent=True, is_binned=False) #Reco = 0, ID = 1, Trig = 2 since strs not supported
    var_eta = Variable("abs(eta)", is_independent=True, is_binned=True)
    var_pt = Variable("pT", is_independent=True, is_binned=True, units="GeV" )
    var_eff = Variable("Efficiency in MC", is_independent=False, is_binned=False)
    #Technically this should not be symmetric (upper bound on eff of 100%), however th2 objects which provide the uncertainties have symmetric errors
    var_effErr = Uncertainty("Efficiency Uncertainty", is_symmetric=True)

    chMap = ["ETau_", "MuTau_", "TauTau_"]

    for year in [2015, 2016, 2017, 2018]:
        yrStr = str(year)

        #Add reco info
        effDict_reco = RootFileReader("Efficiencies/effs_reco.root").read_hist_2d("h_tauEff_" + yrStr)
        var_year.values.extend([year] * len(effDict_reco["z"]))
        var_effType.values.extend([0] * len(effDict_reco["z"]))
        var_ch.values.extend([-1] * len(effDict_reco["z"])) #Reco is channel independent
        var_eta.values.extend(effDict_reco["x_edges"])
        var_pt.values.extend(effDict_reco["y_edges"])
        var_eff.values.extend(effDict_reco["z"])
        var_effErr.values.extend(effDict_reco["dz"])

        #ID WPs used for each channel are different so must handle each separately
        for chN in range(3):
            effDict_ID = RootFileReader("Efficiencies/effs_tau_ID.root").read_hist_2d("tauIDeff_" + chMap[chN] + yrStr)
            var_year.values.extend([year] * len(effDict_ID["z"]))
            var_effType.values.extend([1] * len(effDict_ID["z"]))
            var_ch.values.extend([chN] * len(effDict_ID["z"]))
            var_eta.values.extend(effDict_ID["x_edges"])
            var_pt.values.extend(effDict_ID["y_edges"])
            var_eff.values.extend(effDict_ID["z"])
            var_effErr.values.extend(effDict_ID["dz"])

        #Add trig info. Trigger Effs are indep of eta
        effDict_trig = RootFileReader("Efficiencies/effs_tau_trig_" + yrStr + ".root").read_hist_1d("mc_ditau_Medium_dmall_fitted")
        nBinsTrig = len(effDict_trig["y"])
        var_year.values.extend([year] * nBinsTrig)
        var_effType.values.extend([2] * nBinsTrig)
        var_ch.values.extend([2] * nBinsTrig) #Only use tau trigger for TauTau
        for i in range(nBinsTrig): #Effs apply to entire eta range
            var_eta.values.append((0, 2.3))
        var_pt.values.extend(effDict_trig["x_edges"])
        var_eff.values.extend(effDict_trig["y"])
        var_effErr.values.extend(effDict_trig["dy"])
    
    var_eff.add_uncertainty(var_effErr)

    tab.add_variable(var_year)
    tab.add_variable(var_effType)
    tab.add_variable(var_ch)
    tab.add_variable(var_eta)
    tab.add_variable(var_pt)
    tab.add_variable(var_eff)
    
    return tab


##--------------------------------------------------------------------------------------------------------------------------------

## Produce a table of reco and ID efficiencies for photons
# Sources of information for each efficiency type are discussed below:
# reco : Calculated using https://github.com/99bbarton/TauStar/blob/reinterpretation/Analysis/RecoEffProducer.py
#        and https://github.com/99bbarton/TauStar/blob/reinterpretation/Reinterpretation/Efficiencies/calcObjEffs.C
#        and stored here: effs_reco.root
# ID   : Calculated via EGamma TNP (see AN appendix for details), errors added to eff hists via: ../../Analysis/TNP/writeErrsToEffHists.py ,
# then high-pt bins extrapolated via: ../../Analysis/PhoID_FittedSFS/extrapolateSFs.py
# Returns a HEPDataLib Table object containing the efficiencies
#TODO add plots as images
def makeEffTablePho():
    #Define HEPData objects
    tab = Table("Photon Efficiencies")
    tab.description = """Reco and ID efficiencies observed in MC for photons.'Type' 0 = Reco, 1 = ID"""
    var_year = Variable("Year", is_independent=True, is_binned=False)
    var_effType = Variable("Type", is_independent=True, is_binned=False) #Reco = 0, ID = 1 since strs not supported
    var_eta = Variable("abs(eta)", is_independent=True, is_binned=True)
    var_pt = Variable("pT", is_independent=True, is_binned=True, units="GeV" )
    var_eff = Variable("Efficiency in MC", is_independent=False, is_binned=False)
    #Technically this should not be symmetric (upper bound on eff of 100%), however th2 objects which provide the uncertainties have symmetric errors
    var_effErr = Uncertainty("Efficiency Uncertainty", is_symmetric=True)  

    for year in [2015, 2016, 2017, 2018]:
        yrStr = str(year)

        #Get data from ROOT files
        effDict_reco = RootFileReader("Efficiencies/effs_reco.root").read_hist_2d("h_phoEff_" + yrStr)
        effDict_ID = RootFileReader("Efficiencies/effs_pho_ID_" + yrStr + ".root").read_hist_2d("EGamma_EffMC2D")

        #Write data to the Variable objects
        var_year.values.extend([year] * (len(effDict_reco["z"]) + len(effDict_ID["z"])))
        
        var_effType.values.extend([0] * len(effDict_reco["z"]))
        var_effType.values.extend([1] * len(effDict_ID["z"]))

        var_eta.values.extend(effDict_reco["x_edges"])
        var_eta.values.extend(effDict_ID["x_edges"])

        var_pt.values.extend(effDict_reco["y_edges"])
        var_pt.values.extend(effDict_ID["y_edges"])

        var_eff.values.extend(effDict_reco["z"])
        var_eff.values.extend(effDict_ID["z"])

        var_effErr.values.extend(effDict_reco["dz"])
        var_effErr.values.extend(effDict_ID["dz"])

    #Add the variables to the table
    var_eff.add_uncertainty(var_effErr)

    tab.add_variable(var_year)
    tab.add_variable(var_effType)
    tab.add_variable(var_eta)
    tab.add_variable(var_pt)
    tab.add_variable(var_eff)

    return tab

##--------------------------------------------------------------------------------------------------------------------------------

## Make a Table containing the limits on cross section x branching fraction as a function of tau* mass (i.e. the brazil plot)
# Reads in the outputs of the combine AsymptoticLimits. expected file format ishiggsCombineTest.AsymptoticLimits.m"+ massStr + "y0.nominal.root
def makeLimitsTable():
    print("Making limits table...")

    tab = Table("Asymptotic Limits")
    tab.description = """Exclusion limits on the cross section x branching fraction for an excited tau decaying to tau and photon"""
    tab.keywords["observables"] = ["SIG"]
    tab.add_image("Inputs/Limits/UpperLimit.nominal.pdf")

    var_mass = Variable("${Tau}$* mass", is_independent=True, is_binned=False, units="GeV")
    var_mass.values = [175,250,375,500,625,750,1000,1250,1500,1750,2000,2500,3000,3500,4000,4500,5000]
    var_expLim = Variable("Expected Limits", is_independent=False, is_binned=False)
    var_expLim.add_qualifier("Limit", "Expected")
    var_expLim.add_qualifier("SQRT(S)", 13, "TeV")
    var_expLim.add_qualifier("LUMINOSITY", 138, "fb$^{-1}$")
    
    unc_1stdDev = Uncertainty("1 std dev", is_symmetric=False)
    unc_2stdDev = Uncertainty("2 std dev", is_symmetric=False)

    for mass in var_mass.values:
        massStr = str(mass)
        reader = RootFileReader("Inputs/Limits/higgsCombineTest.AsymptoticLimits.m"+ massStr + "y0.nominal.root")
        limits = reader.read_tree("limit","limit") #Returned array is of form [-2sd, -1sd, nom, +1sd, +2sd]
        var_expLim.values.append(limits[2])
        unc_1stdDev.values.append((limits[1] - limits[2], limits[3] - limits[2])) #Calc intervals from +/-1stddev - median vals
        unc_2stdDev.values.append((limits[0] - limits[2], limits[4] - limits[2])) 

    var_expLim.add_uncertainty(unc_1stdDev)
    var_expLim.add_uncertainty(unc_2stdDev)

    tab.add_variable(var_mass)
    tab.add_variable(var_expLim)

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

    #Taustar signal L-band widths
    table_LBandWidths = makeLBandWidthsTable()
    submission.add_table(table_LBandWidths)
    print("...L-Band widths table added to submission")

    #Object reco, ID, and trig effs
    print("Making object efficiency tables...")
    print("... electrons ...")
    table_effs_el = makeEffTableEl()
    submission.add_table(table_effs_el)
    print("... muons ...")
    table_effs_mu = makeEffTableMu()
    submission.add_table(table_effs_mu)
    print("... taus ...")
    table_effs_tau =makeEffTableTau()
    submission.add_table(table_effs_tau)
    print("... photons ...")
    table_effs_pho = makeEffTablePho()
    submission.add_table(table_effs_pho)
    print("...Efficiency tables added to submission")

    #Asymptotic limits
    table_limits = makeLimitsTable()
    submission.add_table(table_limits)
    print("...limits table added to submission")

    #Meta data and text 
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

