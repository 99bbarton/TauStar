import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR

class MuTrigProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuTau_t2016_0", "O", 2, None, None)
        self.out.branch("MuTau_t2016_1", "O", 2, None, None)
        self.out.branch("MuTau_t2017", "O", 2, None, None)
        self.out.branch("MuTau_t2018", "O", 2, None, None)
        self.out.branch("EMu_1Mu_t2016_0", "O", 2, None, None)
        self.out.branch("EMu_1Mu_t2016_1", "O", 2, None, None)
        self.out.branch("EMu_1Mu_t2017", "O", 2, None, None)
        self.out.branch("EMu_1Mu_t2018", "O", 2, None, None)
        self.out.branch("MuMu_Mu0_t2016_0", "O", 2, None, None)
        self.out.branch("MuMu_Mu0_t2016_1", "O", 2, None, None)
        self.out.branch("MuMu_Mu0_t2017", "O", 2, None, None)
        self.out.branch("MuMu_Mu0_t2018", "O", 2, None, None)
        self.out.branch("MuMu_Mu1_t2016_0", "O", 2, None, None)
        self.out.branch("MuMu_Mu1_t2016_1", "O", 2, None, None)
        self.out.branch("MuMu_Mu1_t2017", "O", 2, None, None)
        self.out.branch("MuMu_Mu1_t2018", "O", 2, None, None)
        self.out.branch("MuTrig_nMatchedNonSelMus", "i")
        self.out.branch("MuTrig_matchedNonSelMus", "i", lenVar="MuTrig_nMatchedNonSelMus")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        
        MuTau_t2016_0 = [False, False]
        MuTau_t2016_1 = [False, False]
        MuTau_t2017 = [False, False]
        MuTau_t2018 = [False, False]
        EMu_1Mu_t2016_0 = [False, False]
        EMu_1Mu_t2016_1 = [False, False]
        EMu_1Mu_t2017 = [False, False]
        EMu_1Mu_t2018 = [False, False]
        MuMu_Mu0_t2016_0 = [False, False]
        MuMu_Mu0_t2016_1 = [False, False]
        MuMu_Mu0_t2017 = [False, False]
        MuMu_Mu0_t2018 = [False, False]
        MuMu_Mu1_t2016_0 = [False, False]
        MuMu_Mu1_t2016_1 = [False, False]
        MuMu_Mu1_t2017 = [False, False]
        MuMu_Mu1_t2018 = [False, False]
        nMatchedNonSelMus = 0
        matchedNonSelMus = []

        if event.MuTau_HavePair or event.EMu_HavePair or event.MuMu_HavePair:
            trigObjs = Collection(event, "TrigObj")
            muons = Collection(event, "Muon")
            goodMuons = {}
            if event.MuTau_HavePair:
                goodMuons["MuTau"] = event.MuTau_MuIdx
            if event.EMu_HavePair:
                goodMuons["EMu"] = event.EMu_MuIdx
            if event.MuMu_HavePair:
                goodMuons["MuMu_0"] = event.MuMu_Mu0Idx
                goodMuons["MuMu_1"] = event.MuMu_Mu1Idx 

            #Format [TriggerName, FilterName(s), filterBits, sum(filterBits)]
            t2016_0 = ["HLT_IsoMu24", "Iso", 2, 2]
            t2016_1 = ["HLT_IsoTkMu24", "IsoTkMu", 8, 8]
            t2017 = ["HLT_IsoMu27", ["Iso", "SingleMuon"], [2, 8], 10]
            t2018 = ["HLT_IsoMu24", ["Iso", "SingleMuon"], [2, 8], 10]

            conditResult_2016_0 = False
            if hasattr(event, t2016_0[0]):
                condit = "event.%s"%t2016_0[0]
                conditResult_2016_0 = eval(condit)
                MuTau_t2016_0[0] = conditResult_2016_0
                EMu_1Mu_t2016_0[0] = conditResult_2016_0
                MuMu_Mu0_t2016_0[0] = conditResult_2016_0
                MuMu_Mu1_t2016_0[0] = conditResult_2016_0

            conditResult_2016_1 = False
            if hasattr(event, t2016_1[0]):
                condit = "event.%s"%t2016_1[0] 
                conditResult_2016_1 = eval(condit)
                MuTau_t2016_1[0] = conditResult_2016_1
                EMu_1Mu_t2016_1[0] = conditResult_2016_1
                MuMu_Mu0_t2016_1[0] = conditResult_2016_1
                MuMu_Mu1_t2016_1[0] = conditResult_2016_1

            conditResult_2017 = False
            if hasattr(event, t2017[0]):
                condit_2017 = "event.%s"%t2017[0]
                conditResult_2017 = eval(condit)
                MuTau_t2017[0] = conditResult_2017
                EMu_1Mu_t2017[0] = conditResult_2017
                MuMu_Mu0_t2017[0] = conditResult_2017
                MuMu_Mu1_t2017[0] = conditResult_2017
            
            conditResult_2018 = False
            if hasattr(event, t2018[0]):
                condit_2018 = "event.%s"%t2018[0]
                conditResult_2018 = eval(condit)
                MuTau_t2018[0] = conditResult_2018
                EMu_1Mu_t2018[0] = conditResult_2018
                MuMu_Mu0_t2018[0] = conditResult_2018
                MuMu_Mu1_t2018[0] = conditResult_2018

            
            writeNoMatchInfo = False
            for muCh in goodMuons.keys():
                muIdx = goodMuons[muCh]
                muon = muons[muIdx]

                for trigObj in trigObjs:
                    #https://indico.cern.ch/event/742871/contributions/3068139/attachments/1683609/2706137/2018-07-03-trigger_object_matching_for_offline.pdf
                    if deltaR(trigObj, muon) > 0.15:
                        continue
                    if abs(muon.pt - trigObj.pt) < (0.2 * muon.pt): #Require pt match within 20%
                        continue

                    muMatch_2016_0 = conditResult_2016_0 and ((trigObj.filterBits & t2016_0[3]) > 0) #bit comp is only what we expect if trig is present
                    muMatch_2016_1 = conditResult_2016_1 and ((trigObj.filterBits & t2016_1[3]) > 0)
                    muMatch_2017   = conditResult_2017 and ((trigObj.filterBits & t2017[3]) > 0)
                    muMatch_2018   = conditResult_2018 and ((trigObj.filterBits & t2018[3]) > 0)

                    
                    if muCh == "MuTau":
                        MuTau_t2016_0[1] = muMatch_2016_0
                        MuTau_t2016_1[1] = muMatch_2016_1
                        MuTau_t2017[1] = muMatch_2017
                        MuTau_t2018[1] = muMatch_2018
                        if (MuTau_t2016_0[0] and not MuTau_t2016_0[1]) or (MuTau_t2016_1[0] and not MuTau_t2016_1[1]): #If triggered but not matched, store more info
                            writeNoMatchInfo = True
                        if (MuTau_t2017[0] and not MuTau_t2017[1]) or (MuTau_t2018[0] and not MuTau_t2018[1]):
                            writeNoMatchInfo = True
                    elif muCh == "EMu":
                        EMu_1Mu_t2016_0[1] = muMatch_2016_0
                        EMu_1Mu_t2016_1[1] = muMatch_2016_1
                        EMu_1Mu_t2017[1] = muMatch_2017
                        EMu_1Mu_t2018[1] = muMatch_2018
                        if (EMu_1Mu_t2016_0[0] and not EMu_1Mu_t2016_0[1]) or (EMu_1Mu_t2016_1[0] and not EMu_1Mu_t2016_1[1]):
                            writeNoMatchInfo = True
                        if (EMu_1Mu_t2017[0] and not EMu_1Mu_t2017[1]) or (EMu_1Mu_t2018[0] and not EMu_1Mu_t2018[1]):
                            writeNoMatchInfo = True
                    elif muCh == "MuMu_0":
                        MuMu_Mu0_t2016_0[1] = muMatch_2016_0
                        MuMu_Mu0_t2016_1[1] = muMatch_2016_1
                        MuMu_Mu0_t2017[1] = muMatch_2017
                        MuMu_Mu0_t2018[1] = muMatch_2018
                        if (MuMu_Mu0_t2016_0[0] and not MuMu_Mu0_t2016_0[1]) or (MuMu_Mu0_t2016_1[0] and not MuMu_Mu0_t2016_1[1]): 
                            writeNoMatchInfo = True
                        if (MuMu_Mu0_t2017[0] and not MuMu_Mu0_t2017[1]) or (MuMu_Mu0_t2018[0] and not MuMu_Mu0_t2018[1]):
                            writeNoMatchInfo = True
                    elif muCh == "MuMu_1":
                        MuMu_Mu1_t2016_0[1] = muMatch_2016_0
                        MuMu_Mu1_t2016_1[1] = muMatch_2016_1
                        MuMu_Mu1_t2017[1] = muMatch_2017
                        MuMu_Mu1_t2018[1] = muMatch_2018
                        if (MuMu_Mu1_t2016_0[0] and not MuMu_Mu1_t2016_0[1]) or (MuMu_Mu1_t2016_1[0] and not MuMu_Mu1_t2016_1[1]): 
                            writeNoMatchInfo = True
                        if (MuMu_Mu1_t2017[0] and not MuMu_Mu1_t2017[1]) or (MuMu_Mu1_t2018[0] and not MuMu_Mu1_t2018[1]):
                            writeNoMatchInfo = True
                                
            if writeNoMatchInfo: #If a trigger had fired but a match was not made, look through other muons to see what matches trigObjs
                for muIdx, mu in enumerate(muons):
                    if muIdx in goodMuons.values():
                        continue
            
                    for trigObj in trigObjs:
                        if deltaR(trigObj, muon) > 0.15:
                            continue
                        if abs(muon.pt - trigObj.pt) < (0.2 * muon.pt): #Require pt match within 20%
                            continue

                        muMatch_2016_0 = conditResult_2016_0 and ((trigObj.filterBits & t2016_0[3]) > 0) #bit comp is only what we expect if trig is present
                        muMatch_2016_1 = conditResult_2016_1 and ((trigObj.filterBits & t2016_1[3]) > 0)
                        muMatch_2017   = conditResult_2017 and ((trigObj.filterBits & t2017[3]) > 0)
                        muMatch_2018   = conditResult_2018 and ((trigObj.filterBits & t2018[3]) > 0)

                        if muMatch_2016_0 or muMatch_2016_1 or muMatch_2017 or muMatch_2018: # trigObj matched to a non-reco'd (chosen) muon. store its location
                            nMatchedNonSelMus += 1
                            matchedNonSelMus.append(muIdx)
        


        self.out.fillBranch("MuTau_t2016_0", MuTau_t2016_0)
        self.out.fillBranch("MuTau_t2016_1", MuTau_t2016_1)
        self.out.fillBranch("MuTau_t2017", MuTau_t2017)
        self.out.fillBranch("MuTau_t2018", MuTau_t2018)
        self.out.fillBranch("EMu_1Mu_t2016_0", EMu_1Mu_t2016_0)
        self.out.fillBranch("EMu_1Mu_t2016_1", EMu_1Mu_t2016_1)
        self.out.fillBranch("EMu_1Mu_t2017", EMu_1Mu_t2017)
        self.out.fillBranch("EMu_1Mu_t2018", EMu_1Mu_t2018)
        self.out.fillBranch("MuMu_Mu0_t2016_0", MuMu_Mu0_t2016_0)
        self.out.fillBranch("MuMu_Mu0_t2016_1", MuMu_Mu0_t2016_1)
        self.out.fillBranch("MuMu_Mu0_t2017", MuMu_Mu0_t2017) 
        self.out.fillBranch("MuMu_Mu0_t2018", MuMu_Mu0_t2018)
        self.out.fillBranch("MuMu_Mu1_t2016_0", MuMu_Mu1_t2016_0)
        self.out.fillBranch("MuMu_Mu1_t2016_1", MuMu_Mu1_t2016_1)
        self.out.fillBranch("MuMu_Mu1_t2017", MuMu_Mu1_t2017)
        self.out.fillBranch("MuMu_Mu1_t2018", MuMu_Mu1_t2018)
        self.out.fillBranch("MuTrig_nMatchedNonSelMus", nMatchedNonSelMus)
        self.out.fillBranch("MuTrig_matchedNonSelMus", matchedNonSelMus)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTrigProducerConstr = lambda : MuTrigProducer()
