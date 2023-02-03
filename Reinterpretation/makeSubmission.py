# A script to produce the HEPData submission for the Taustar analysis (EXO-22-007)

#TODO Add table keywords

import numpy as np
import pandas as pd
from hepdata_lib import Submission, Table, Variable, Uncertainty, RootFileReader

##--------------------------------------------------------------------------------------------------------------------------------

#Makes a HEPData_lib Table object of the signal process cut flow
#\param filepath : a string containing the filename and path to file containing cutflow information. Assumed to be in a CSV format
#\returns A Table object containing the cut flow information 
def makeCutFlowTable(filepath):
    print("Making cutflow table...")

    dataframe = pd.read_csv(filepath, sep=",")

    table = Table("Signal Process Cutflow")
    table.description = "Signal process cutflow for all taustar hypothesis masses, channels, and years considered."

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
    for colN in range(len(dataframe.columns) - 1):
        if colN < 4: #First three colums were added above
            continue
       
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

# Create the HEPData submission
def makeSubmission():
    submission = Submission()

    #Add cutflow table
    table_cutFlow = makeCutFlowTable("Cutflows/signalCutflow_24Jan23.txt")
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

    print("Creating files...")
    submission.create_files("TestOutput/", remove_old=True)

if __name__ == "__main__":
    makeSubmission()

