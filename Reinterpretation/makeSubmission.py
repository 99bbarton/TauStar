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
    for colN in range(len(dataframe.columns - 1)):
        if colN < 4: #First three colums were added above
            continue
       
        cutVar = Variable(dataframe.columns[colN], is_independent=False, is_binned=False, units="Expected Events")
        cutVar.values = dataframe[dataframe.columns[colN]]
        cutErr = Uncertainty(dataframe.columns[colN+1], is_symmetric = True, units "Expected Events")
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
    if includeSignalRegion: #Safety check against including signal region information
        print("\n\n WARNING: You have chosen to include the signal region (A) total covariance matrix in the table.")
        response = raw_input("Are you sure you wish to continue? Enter YES to continue or anything else to abort")
        if response != "YES":
            exit(-1)
    
    #Initialize what data to include and how to access+label it
    years = ["2015", "2016", "2017", "2018"]
    masses = ["175","250","375","500","625","750","1000","1250","1500","1750","2000","2500","3000","3500","4000","4500","5000"]
    filebase = "fitDiagnosticsTest_m"
    pathToHistBase = "shapes_fit_b/"
    channels = {"ch1":"ETau","ch2":"MuTau","ch3":"TauTau","ch4":"ETauLowPt","ch5":"MuTauLowPt","ch6":"TauTauLowPt","ch7":"EE","ch8":"MuMu","ch9":"EMu"}

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
        var_ch = Variable(channels[chNum], is_independent=True, is_binned=False)
        var_reg = Variable("Region", is_independent = True, is_binned=False)
        var_binNumX = Variable("Bin Number X", is_independent=True, is_binned=False)
        var_binNumY = Variable("Bin Number Y", is_independent=True, is_binned=False)
        var_cov = Variable("Total Covariance", is_independent=False, is_binned=False)

        #Read in each file and extract total covariance matrix for each channel and region
        for mass in masses:
            filename = filebase + mass + "y" + year + ".root"
            fileReader = RootFileReader(dirPath + filename)
    
            for chCount, chNum in enumerate(channels.keys()):
                #Channels each have different regions, create the appropriate list
                if chCount < 3:
                    regions = ["B1", "B3", "C1", "C3", "D1", "D3"]
                    if includeSignalRegion:
                        regions.insert(0, "A")
                elif chCount < 6:
                    regions = ["A1", "A2", "B1", "B3", "C1", "C3", "D1", "D3"]
                else:
                    regions = ""
                    
                for region in regions: 
                    covHistDict = fileReader.read_hist_2d(pathToHistBase + chNum + "_" + region + "/total_covar")
                    var_binNumX.values.append(covHistDict["x"])
                    var_binNumX.values.append(covHistDict["y"])
                    var_cov.values.append(covHistDict["z"])

                    #Need to add indep var entries corresponding to each new covariance value
                    numVals = len(covHistDict["z"])
                    assert len(covHistDict["x"]) == numVals
                    assert len(covHistDict["y"]) == numVals

                    var_mass.values.append([mass] * numVals)
                    var_ch.values.append([channels[chNum]] * numVals)
                    var_reg.values.append([region] * numVals)

        #Complete the year's table
        tables[yearN].add_variable(var_mass)
        tables[yearN].add_variable(var_ch)
        tables[yearN].add_variable(var_reg)
        tables[yearN].add_variable(var_binNumX)
        tables[yearN].add_variable(var_binNumY)
        tables[yearN].add_variable(var_cov)

    return tables





                

            
    
    

    





##--------------------------------------------------------------------------------------------------------------------------------
# Create the HEPData submission
def makeSubmission():
    submission = Submission()
    submission.add_image("Graphics/fitRegions.pdf")

    table_cutFlow = makeCutFlowTable("Cutflows/signalCutflow_24Jan23.txt")
    submission.add_table(table_cutFlow)



if __name__ == "__main__":
    makeSubmission()

