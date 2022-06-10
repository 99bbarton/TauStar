# Make plots of photon ID efficiency in MC

from sympy import false
import ROOT
from ROOT import TLorentzVector
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class PhoEffProducer(Module):
    noIso = False
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
        self.out.branch("PhoID_phoPt", "F")
        self.out.branch("PhoID_phoEta", "F")


    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #https://twiki.cern.ch/CMS/EgammaIDRecipesRun2
        photons = Collection(event, "Photon")
        if len(photons) < 1:
            return False

        phoIdx = 0
        phoPT= -1
        for i, photon in enumerate(photons):
            photonID = photon.isScEtaEB or photon.isScEtaEE
            if self.elVeto:
                photonID = photonID and photon.electronVeto
            else:
                photonID = photonID and not photon.pixelSeed
            photonID = photonID and photon.pt>=20. and abs(photon.eta)<2.5 

            if photon.pt > phoPT:
                phoPT = photon.pt
                phoIdx = i

	
        thePhoton = photons[phoIdx]
        

        self.out.fillBranch("PhoID_passID", thePhoton.mvaID_WP90)
        self.out.fillBranch("PhoID_elVeto", self.elVeto)
        self.out.fillBranch("PhoID_phoPt", thePhoton.pt)
        self.out.fillBranch("PhoID_phoEta", thePhoton.eta)

        return True


PhoEffProducerConstr = lambda elVeto: PhoEffProducer(
    elVeto = elVeto
)
