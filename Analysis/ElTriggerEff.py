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
        self.out.branch("ElTrig_elDeltaEtaSC", "F") #delta eta(supercluster eta, el) with sign
        self.out.branch("ElTrig_metPt", "F")
        self.out.branch("ElTrig_mt", "F")
        self.out.branch("ElTrig_cosDPhi", "F")
        self.out.branch("ElTrig_elTrig", "I")
        self.out.branch("ElTrig_bTagsL", "I")
        self.out.branch("ElTrig_bTagsM", "I")
        self.out.branch("ElTrig_bTagsT", "I")
        self.out.branch("ElTrig_metFlags", "I")
        #self.out.branch("ElTrig_elRecoSF", "F")
        #self.out.branch("ElTrig_elIDSF", "F")
        self.out.branch("ElTrig_HLT_Ele25_eta2p1_WPTight_Gsf", "I")
        self.out.branch("ElTrig_HLT_Ele27_WPTight_Gsf", "I")
        self.out.branch("ElTrig_HLT_Ele32_WPTight_Gsf", "I")
        self.out.branch("ElTrig_HLT_Ele32_WPTight_Gsf_L1DoubleEG", "I")
        self.out.branch("ElTrig_HLT_Ele35_WPTight_Gsf", "I")
        self.out.branch("ElTrig_HLT_Ele38_WPTight_Gsf", "I")
        self.out.branch("ElTrig_HLT_Ele40_WPTight_Gsf", "I")

        #baseDir = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/ElIDSFs/"
        #elRecoSFFile = ROOT.TFile.Open(baseDir + "egammaEffi_ptAbove20.txt_EGM2D_UL2018.root")
        #self.hElRecoSF = elRecoSFFile.Get("EGamma_SF2D")
        #elIDSFFile = ROOT.TFile.Open(baseDir + "egammaEffi.txt_Ele_wp80iso_EGM2D.root")
        #elIDSFFile = ROOT.TFile.Open(baseDir + "egammaEffi.txt_Ele_wp90iso_EGM2D.root")
        #self.hElIDSF = elIDSFFile.Get("EGamma_SF2D")
    
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
            #elID = elID and el.mvaFall17V2Iso_WP90
            elID = elID and el.mvaFall17V2Iso_WP80
            if elID:
                nGoodEl = nGoodEl + 1
                goodEl = el

        # require exactly one
        if nGoodEl != 1:
                return False        

        #Get the electron reco and MVA ID scale factors from E-Gamma hists
        #elRecoSF = self.hElRecoSF.GetBinContent(self.hElRecoSF.FindBin(goodEl.eta, goodEl.pt))
        #elIDSF = self.hElIDSF.GetBinContent(self.hElIDSF.FindBin(goodEl.eta, goodEl.pt))

        muons = Collection(event, "Muon")
        # We don't want reconstructed muons
        for mu in muons:
            muID = mu.pt>=8. and abs(mu.eta)<2.4
            #muID = muID and mu.pfIsoId>=4 and mu.tightId
            muID = muID and mu.pfIsoId>=4 and mu.mediumId
            if muID:
                return False

        #We don't want reconstructed taus
        taus = Collection(event, "Tau")
        for tau in taus:
                tauID = tau.pt>=20 and abs(tau.eta)<2.3
                tauID = tauID and tau.decayMode != 5 and tau.decayMode != 6 and tau.decayMode != 7
                #tauID = tauID and (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (32&tau.idDeepTau2017v2p1VSe)
                tauID = tauID and (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (16&tau.idDeepTau2017v2p1VSe)
                if tauID:
                        return False        

        #Don't want b-tagged jets - CURRENTLY NO CUT IS APPLIED - MUST BE APPLIED IN ANALYSIS
        jets = Collection(event, "Jet")
        nBJetsL = 0
        nBJetsM = 0
        nBJetsT = 0
        for jet in jets:
                if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId): #TightID + lepVeto
                        if deltaR(jet, goodEl) >= 0.4:
                            #https://twiki.cern.ch/CMS/BtagRecommendation106XUL18
                            if jet.btagDeepB >= 0.1208:
                                nBJetsL += 1
                            if jet.btagDeepB >= 0.7665:
                                nBJetsT += 1
                            if jet.btagDeepB >= 0.4168: #Medium wp
                                nBJetsM += 1           
                

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
        
        
        metFlags = event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter 
        metFlags = metFlags and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_eeBadScFilter and event.Flag_ecalBadCalibFilter


        # check trigger performance
        #https://twiki.cern.ch/CMS/MuonHLT2017#Recommendations_for_2017_data_an
        trigger = False
        if hasattr(event, "HLT_Ele25_eta2p1_WPTight_Gsf"): 
            trigger = trigger or event.HLT_Ele25_eta2p1_WPTight_Gsf
            if event.HLT_Ele25_eta2p1_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele25_eta2p1_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele25_eta2p1_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele25_eta2p1_WPTight_Gsf", -1)
        if hasattr(event, "HLT_Ele27_WPTight_Gsf"): 
            trigger = trigger or event.HLT_Ele27_WPTight_Gsf
            if event.HLT_Ele27_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele27_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele27_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele27_WPTight_Gsf", -1)
        if hasattr(event, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"):
            trigger = trigger or event.HLT_Ele32_WPTight_Gsf_L1DoubleEG
            if event.HLT_Ele32_WPTight_Gsf_L1DoubleEG:
                self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf_L1DoubleEG", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf_L1DoubleEG", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf_L1DoubleEG", -1)
        if hasattr(event, "HLT_Ele32_WPTight_Gsf"):
            trigger = trigger or event.HLT_Ele32_WPTight_Gsf
            if event.HLT_Ele32_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele32_WPTight_Gsf", -1)
        if hasattr(event, "HLT_Ele35_WPTight_Gsf"): 
            trigger = trigger or event.HLT_Ele35_WPTight_Gsf
            if event.HLT_Ele35_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele35_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele35_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele35_WPTight_Gsf", -1)
        if hasattr(event, "HLT_Ele38_WPTight_Gsf"):
            trigger = trigger or event.HLT_Ele38_WPTight_Gsf
            if event.HLT_Ele38_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele38_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele38_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele38_WPTight_Gsf", -1)
        if hasattr(event, "HLT_Ele40_WPTight_Gsf"): 
            trigger = trigger or event.HLT_Ele40_WPTight_Gsf
            if event.HLT_Ele40_WPTight_Gsf:
                self.out.fillBranch("ElTrig_HLT_Ele40_WPTight_Gsf", 1)
            else:
                self.out.fillBranch("ElTrig_HLT_Ele40_WPTight_Gsf", 0)
        else:
            self.out.fillBranch("ElTrig_HLT_Ele40_WPTight_Gsf", -1)        
        if trigger:
            elTrig = 1        

        #Calculate variables used for W->e+nu event selection
        # deltaPhi between the Electron and MET
        cosdphi = math.cos(deltaPhi(goodEl.phi, event.MET_phi))
        mT = 2. * event.MET_pt * goodEl.pt * (1.-cosdphi)
        mT = math.sqrt(mT)


        self.out.fillBranch("ElTrig_elPt", goodEl.pt)
        self.out.fillBranch("ElTrig_elEta", goodEl.eta)
        self.out.fillBranch("ElTrig_elDeltaEtaSC", goodEl.deltaEtaSC)
        self.out.fillBranch("ElTrig_metPt", event.MET_pt)
        self.out.fillBranch("ElTrig_mt", mT)
        self.out.fillBranch("ElTrig_cosDPhi", cosdphi)
        self.out.fillBranch("ElTrig_elTrig", elTrig)
        self.out.fillBranch("ElTrig_bTagsL", nBJetsL)
        self.out.fillBranch("ElTrig_bTagsM", nBJetsM)
        self.out.fillBranch("ElTrig_bTagsT", nBJetsT)
        self.out.fillBranch("ElTrig_metFlags", metFlags)
        #self.out.fillBranch("ElTrig_elRecoSF", elRecoSF)
        #self.out.fillBranch("ElTrig_elIDSF", elIDSF)

        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ElTriggerEffConstr = lambda : ElTriggerEff() 
 
