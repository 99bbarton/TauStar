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
            conditResult_2016_1 = False
            conditResult_2017 = False
            conditResult_2018 = False
            if hasattr(event, t2016_0[0]):
                condit = "event.%s"%t2016_0[0]
                conditResult_2016_0 = eval(condit)
                MuTau_t2016_0[0] = EMu_1Mu_t2016_0[0] = MuMu_Mu0_t2016_0[0] = MuMu_Mu1_t2016_0[0] = conditResult_2016_0

            if hasattr(event, t2016_1[0]):
                condit = "event.%s"%t2016_1[0] 
                conditResult_2016_1 = eval(condit)
                MuTau_t2016_1[0] = EMu_1Mu_t2016_1[0] = MuMu_Mu0_t2016_1[0] = MuMu_Mu1_t2016_1[0] = conditResult_2016_1

            if hasattr(event, t2017[0]):
                condit_2017 = "event.%s"%t2017[0]
                conditResult_2017 = eval(condit)
                MuTau_t2017[0] = EMu_1Mu_t2017[0] = MuMu_Mu0_t2017[0] = MuMu_Mu1_t2017[0] = conditResult_2017
            
            if hasattr(event, t2018[0]):
                condit_2018 = "event.%s"%t2018[0]
                conditResult_2018 = eval(condit)
                MuTau_t2018[0] = EMu_1Mu_t2018[0] = MuMu_Mu0_t2018[0] = MuMu_Mu1_t2018[0] = conditResult_2018

            for trigObj in trigObjs:
                muMatch = False
                for muCh in goodMuons.keys():
                    muIdx = goodMuons[muCh]
                    muon = muons[muIdx]

                    #https://indico.cern.ch/event/742871/contributions/3068139/attachments/1683609/2706137/2018-07-03-trigger_object_matching_for_offline.pdf
                    if deltaR(trigObj, muon) > 0.15:
                        continue
                    
                    muMatch_2016_0 = conditResult_2016_0 and (trigObj.filterBits & t2016_0[3]) #bit comp is only what we expect if trig is present
                    muMatch_2016_1 = conditResult_2016_1 and (trigObj.filterBits & t2016_1[3])
                    muMatch_2017   = conditResult_2017 and (trigObj.filterBits & t2017[3])
                    muMatch_2018   = conditResult_2018 and (trigObj.filterBits & t2018[3])

                    if muCh == "MuTau":
                        MuTau_t2016_0[1] = muMatch_2016_0
                        MuTau_t2016_1[1] = muMatch_2016_1
                        MuTau_t2017[1] = muMatch_2017
                        MuTau_t2018[1] = muMatch_2018
                    elif muCh == "EMu":
                        EMu_1Mu_t2016_0[1] = muMatch_2016_0
                        EMu_1Mu_t2016_1[1] = muMatch_2016_1
                        EMu_1Mu_t2017[1] = muMatch_2017
                        EMu_1Mu_t2018[1] = muMatch_2018
                    elif muCh == "MuMu_0":
                        MuMu_Mu0_t2016_0[1] = muMatch_2016_0
                        MuMu_Mu0_t2016_1[1] = muMatch_2016_1
                        MuMu_Mu0_t2017[1] = muMatch_2017
                        MuMu_Mu0_t2018[1] = muMatch_2018
                    elif muCh == "MuMu_1":
                        MuMu_Mu1_t2016_0[1] = muMatch_2016_0
                        MuMu_Mu1_t2016_1[1] = muMatch_2016_1
                        MuMu_Mu1_t2017[1] = muMatch_2017
                        MuMu_Mu1_t2018[1] = muMatch_2018

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

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTrigProducerConstr = lambda : MuTrigProducer()
