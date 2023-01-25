# A script to produce the HEPData submission for the Taustar analysis (EXO-22-007)


import numpy as np
import pandas as pd
from hepdata_lib import Submission, Table, Variable, Uncertainty

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
# Create the HEPData submission
def makeSubmission():
    submission = Submission()

    table_cutFlow = makeCutFlowTable("Cutflows/signalCutflow_24Jan23.txt")
    submission.add_table(table_cutFlow)



if __name__ == "__main__":
    makeSubmission()

