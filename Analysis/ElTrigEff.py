#Study of the efficiency of electron triggers used for each year

import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class ElTrigEff(Module):
    def __init__(self):
        pass
    def beginJob(self):
        self.nEvents = 0
        self.nTrigEvents = 0
        self.nSigEvents = 0
        self.nTrigSigEvents = 0
        
    def endJob(self):
        Module.endJob(self)
        sigEff = self.nSigEvents / self.nEvents
        trigEff = self.nTrigEvents / self.nEvents
        trigSigEff = self.nTrigSigEvents / self.nEvents
        print "Total events considered = " + self.nEvents
        print "Signal efficiency nSigEvents/nEvents = " + sigEff
        print "Trigger efficiency nTrigEvents/nEvents = " + trigEff
        print "Triggered signal efficiency nTrigAndSigEvents/nEvents = " + trigSigEff
        
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("ElTrigEff_TP","I") #True positive
        self.out.branch("ElTrigEff_FP","I") #False positive
        self.out.branch("ElTrigEff_TN","I")
        self.out.branch("ElTrigEff_FN","I")
        self.out.branch("ElTrigEff_Trigger", "I")

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #Examine the overall trigger efficiency
        self.nEvents += 1
    
        if event.ElTau_Trigger:
            self.nTrigEvents += 1
        if event.ElTau_HaveTriplet:
            self.nSigEvents += 1
        if event.ElTau_Trigger and event.ElTau_HaveTriplet:
            self.nTrigSigEvents += 1

        #Examine triggers vs ID'd electrons
        trigger = False
        #2016
        if hasattr(event, "HLT_Ele27_WPTight_Gsf"): trigger = trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele25_eta2p1_WPTight_Gsf"): trigger = trigger or event.HLT_Ele25_eta2p1_WPTight_Gsf
        #2017
        if hasattr(event, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf_L1DoubleEG
        if hasattr(event, "HLT_Ele35_WPTight_Gsf"): trigger = trigger or event.HLT_Ele35_WPTight_Gsf
        #if hasattr(event, "HLT_Ele27_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele32_WPTight_Gsf"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf
        #2018
        #if hasattr(event, "HLT_Ele32_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele32_WPTight_Gsf

        #Count ID'd electrons
        electrons = Collection(event, "Electron")
        numIsoEl = 0
        for i, el in enumerate(electrons):
            if el.mvaFall17V2Iso:
                numIsoEl += 1

        #Score 
        truePos = 0
        falsePos = 0
        trueNeg = 0
        falseNeg = 0
        
        if trigger and numIsoEl == 1:
            truePos += 1
        elif trigger and numIsoEl != 1:
            falsePos += 1
        elif (not trigger) and numIsoEl == 1:
            falseNeg += 1
        else:
            trueNeg += 1

            
        self.out.fillBranch("ElTrigEff_TP", truePos)
        self.out.fillBranch("ElTrigEff_FP", falsePos)
        self.out.fillBranch("ElTrigEff_FN", falseNeg)
        self.out.fillBranch("ElTrigEff_TN", trueNeg)
        self.out.fillBranch("ElTrigEff_Trigger", trigger)
        return True


ElTrigEffConstr = lambda : ElTrigEff()
