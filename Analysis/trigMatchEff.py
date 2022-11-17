#Check the trigger matching efficiency of leptons in the Tau* analysis channels
#Assumes samples have already been processed through ETauProducer, MuTauProducer, TauTauProducer, and TriggerProducer

from re import S
from ROOT import TFile, TTree, TCut
import sys


#Check how often the lepton in each channel matches to a trigObj
# filename (str) : name and path to file to examine
# year (str) : year of sample being examined
# channels [str, str, ...] : list of channels to examine. Default is all primary analysis channels
def calcTrigMatchEff(filename, year, channels = ["ETau", "MuTau", "TauTau"]):
    
    file = TFile.Open(filename, "READ")
    tree = file.Get("Events")

    print("\nChecking trigger matching efficienies for input file: " + filename)
    print("Year is " + year)

    objName = ""
    for channel in channels:

        tauNum = 0
        tauDen = 0
        phoNum = 0
        phoDen = 0
        lepNum = 0 
        lepDen = 0
        baseCutsPair = channel + "_HavePair"
        baseCutsTrip = channel + "_HaveTriplet"

        
        if channel == "ETau":
            objName = "electron"
            
            trigCut = ""
            if year == "2015" or year == "2016":
                trigCut = "(HLT_Ele27_WPTight_Gsf || HLT_Photon175)"
            elif year == "2017":
                trigCut = "((HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG) || HLT_Photon200)"
            elif year == "2018":
                trigCut = "(HLT_Ele32_WPTight_Gsf || HLT_Photon200)"
            lepDen = tree.GetEntries(baseCutsPair + "&&" + trigCut)
            lepNum = tree.GetEntries(baseCutsPair + "&&" + trigCut + "&&ETau_EHasTrigObj")
        elif channel == "MuTau":
            objName = "muon"

            trigCut = ""
            if year == "2015" or year == "2016":
                trigCut = "(HLT_IsoMu24 || HLT_IsoTkMu24)"
            elif year == "2017":
                trigCut = "HLT_IsoMu27"
            elif year == "2018":
                trigCut = "HLT_IsoMu24"
            lepDen = tree.GetEntries(baseCutsPair + "&&" + trigCut)
            lepNum = tree.GetEntries(baseCutsPair + "&&" + trigCut + "&&MuTau_MuHasTrigObj")
        elif channel == "TauTau":
            objName = "tau"

            trigCut = ""
            if year == "2015" or year == "2016":
                trigCut = "Trigger_diTau2016"
            elif year == "2017":
                trigCut = "Trigger_diTau2017"
            elif year == "2018":
                trigCut = "Trigger_diTau2018"
            lepDen = tree.GetEntries(baseCutsPair + "&&" + trigCut)
            lepNum = tree.GetEntries(baseCutsPair + "&&" + trigCut  + "&&(TauTau_Tau0HasTrigObj || TauTau_Tau1HasTrigObj)")
        else:
            print("Unrecognized channel")
            exit(-1)

        eff = float(lepNum) / float(lepDen) * 100
        print("For " + channel + " channel, the " + objName + " had a matching trigObj " + str(eff)[:4] + "% of events with pairs and which passed trigger")

    print("\n")
        

#Call above function with command line passed params
if __name__ == "__main__":
    if len(sys.argv) == 3:
        calcTrigMatchEff(filename = sys.argv[1], year = sys.argv[2]) 
    elif len(sys.argv) == 4:
        calcTrigMatchEff(filename = sys.argv[1], year = sys.argv[2], channels = sys.argv[3])
    else:
        print('USAGE : python trigMatchEff.py "filepath"  "year" <op: ["channel1", "channel2", ...]>')
    




            



