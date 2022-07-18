# Make plots of photon ID efficiency in MC

from sympy import false
import ROOT
from ROOT import TLorentzVector
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class PhoEffProducer(Module):
    elVeto = False
    def __init__(self, elVeto=False):
        self.elVeto = elVeto
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("PhoID_passID", "I")
        self.out.branch("PhoID_elVeto", "I")
        self.out.brancg("PhoID_pixelVeto", "I")
        self.out.branch("PhoID_phoPt", "F")
        self.out.branch("PhoID_phoEta", "F")
        self.out.branch("PhoID_isScEtaEB", "I")
        self.out.branch("PhoID_isScEtaEE", "I")
        self.out.branch("PhoID_phoIdx", "I")
        self.out.branch("PhoID_mvaScore", "F") 
        self.out.branch("PhoID_cutBased", "I") #0 fail, 1 loose, 2 medium, 3 tight
        


    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #https://twiki.cern.ch/CMS/EgammaIDRecipesRun2
        photons = Collection(event, "Photon")
        if len(photons) < 1:
            return False

        phoIdx = -1
        phoPT= -1
        for i, photon in enumerate(photons):
            photonID = photon.isScEtaEB or photon.isScEtaEE
            if self.elVeto:
                photonID = photonID and photon.electronVeto
            else:
                photonID = photonID and not photon.pixelSeed
            photonID = photonID and photon.pt>=20. and abs(photon.eta)<2.5
	        photonID = photonID and photon.genPartFlav == 1 

            if photon.pt > phoPT:
                phoPT = photon.pt
                phoIdx = i

	    if phoIdx < 0:
	        return False
            
        thePhoton = photons[phoIdx]
        

        self.out.fillBranch("PhoID_passID", thePhoton.mvaID_WP90)
        self.out.fillBranch("PhoID_elVeto", thePhoton.electronVeto)
        self.out.fillBranch("PhoID_pixelVeto", not thePhoton.pixelSeed)
        self.out.fillBranch("PhoID_phoPt", thePhoton.pt)
        self.out.fillBranch("PhoID_phoEta", thePhoton.eta)
        self.out.fillBranch("PhoID_isScEtaEB", thePhoton.isScEtaEB)
        self.out.fillBranch("PhoID_isScEtaEE", thePhoton.isScEtaEE)
        self.out.branch("PhoID_phoIdx", phoIdx)
        self.out.branch("PhoID_mvaScore", thePhoton.mvaID)
        self.out.branch("PhoID_cutBased", thePhoton.cutBased)


        return True


PhoEffProducerConstr = lambda elVeto: PhoEffProducer(
    elVeto = elVeto
)
