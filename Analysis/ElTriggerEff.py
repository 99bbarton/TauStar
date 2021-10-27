import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

import math

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi, deltaR

class ElTriggerEff(Module):
    def __init__(self):
        pass

    def beginJob(self):
	pass
    
    def endJob(self):
        pass
    
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("ElTrig_elPt", "F") 
        self.out.branch("ElTrig_elEta", "F")
	self.out.branch("ElTrig_metPt", "F")
	self.out.branch("ElTrig_mt", "F")
	self.out.branch("ElTrig_cosDPhi", "F")
	self.out.branch("ElTrig_elTrig", "I")
        self.out.branch("ElTrig_bTagsL", "I")
        self.out.branch("ElTrig_bTagsM", "I")
        self.out.branch("ElTrig_bTagsT", "I")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        
        elTrig = 0 

        electrons = Collection(event, "Electron")
        if len(electrons) < 1:
                return False
        nGoodEl = 0
        # find good reconstructed electrons
        for el in electrons:
            elID = abs(el.eta)<2.5 and el.pt > 12
            elID = elID and el.mvaFall17V2Iso_WP90
            if elID:
                nGoodEl = nGoodEl + 1
                goodEl = el

        # require exactly one
        if nGoodEl != 1:
                return False        

        muons = Collection(event, "Muon")
        # We don't want reconstructed muons
        for mu in muons:
            muID = mu.pt>=8. and abs(mu.eta)<2.4
            muID = muID and mu.pfIsoId>=4 and mu.tightId
            if muID:
                return False

        #We don't want reconstructed taus
        taus = Collection(event, "Tau")
        for tau in taus:
                tauID = tau.pt>=20 and abs(tau.eta)<2.3
                tauID = tauID and tau.decayMode != 5 and tau.decayMode != 6 and tau.decayMode != 7
                tauID = tauID and (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (32&tau.idDeepTau2017v2p1VSe)
                if tauID:
                        return False        

        #Don't want b-tagged jets
        jets = Collection(event, "Jet")
        nBJetsL = 0
        nBJetsM = 0
        nBJetsT = 0
        for jet in jets:
                if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId): #TightID + lepVeto
                        #https://twiki.cern.ch/CMS/BtagRecommendation106XUL18
                        if jet.btagDeepB >= 0.1208:
                           nBJetsL += 1
                        if jet.btagDeepB >= 0.7665:
                           nBJetsT += 1
                        if jet.btagDeepB >= 0.4168: #Medium wp
                           nBJetsM += 1           
                           return False

        #We want to select W events first so as not to bias ourselves by selecting with an el trigger
        if event.MET_pt < 200: #smallest value visible in triggers for 2018
                return False
        #https://twiki.cern.ch/twiki/bin/view/CMS/JetMETPathsRun2#Single_PF_Jet_Paths_AN1  #and go to Single PF MET paths
        metTrig = False
        if hasattr(event, "HLT_PFMET200_NotCleaned"): metTrig = metTrig or event.HLT_PFMET200_NotCleaned
        if hasattr(event, "HLT_PFMET200_HBHECleaned"): metTrig = metTrig or event.HLT_PFMET200_HBHECleaned
        if hasattr(event, "HLT_PFMET200_HBHE_BeamHaloCleaned"): metTrig = metTrig or event.HLT_PFMET200_HBHE_BeamHaloCleaned
        if hasattr(event, "HLT_PFMET250_HBHECleaned"): metTrig = metTrig or event.HLT_PFMET250_HBHECleaned
        if hasattr(event, "HLT_PFMET300_HBHECleaned"): metTrig = metTrig or event.HLT_PFMET300_HBHECleaned
        if hasattr(event, "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned"): metTrig = metTrig or event.HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned
        if not metTrig:
               return False
        

        # check trigger performance
        #https://twiki.cern.ch/CMS/MuonHLT2017#Recommendations_for_2017_data_an
        trigger = False
        if hasattr(event, "HLT_Ele27_WPTight_Gsf"): trigger = trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele25_eta2p1_WPTight_Gsf"): trigger = trigger or event.HLT_Ele25_eta2p1_WPTight_Gsf
        #2017
        if hasattr(event, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf_L1DoubleEG
        if hasattr(event, "HLT_Ele35_WPTight_Gsf"): trigger = trigger or event.HLT_Ele35_WPTight_Gsf
        if hasattr(event, "HLT_Ele32_WPTight_Gsf"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf
        if trigger:
            elTrig = 1        

        #Calculate variables used for W->e+nu event selection
        # deltaPhi between the Electron and MET
        cosdphi = math.cos(deltaPhi(goodEl.phi, event.MET_phi))
        mT = 2. * event.MET_pt * goodEl.pt * (1.-cosdphi)
        mT = math.sqrt(mT)


        self.out.fillBranch("ElTrig_elPt", goodEl.pt)
        self.out.fillBranch("ElTrig_elEta", goodEl.eta)
        self.out.fillBranch("ElTrig_metPt", event.MET_pt)
        self.out.fillBranch("ElTrig_mt", mT)
        self.out.fillBranch("ElTrig_cosDPhi", cosdphi)
        self.out.fillBranch("ElTrig_elTrig", elTrig)
        self.out.fillBranch("ElTrig_bTagsL", nBJetsL)
        self.out.fillBranch("ElTrig_bTagsM", nBJetsM)
        self.out.fillBranch("ElTrig_bTagsT", nBJetsT)

        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ElTriggerEffConstr = lambda : ElTriggerEff() 
 
