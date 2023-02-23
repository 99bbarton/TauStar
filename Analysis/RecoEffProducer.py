import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR

class RecoEffProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("Eff_recoPartsStatus","I", "GenPart_nGenPart", None, None)
        self.out.branch("Eff_recoVisTausStatus","I", "GenVisTau_nGenVisTau", None, None)

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        genParts = Collection(event, "GenPart")
        genVisTaus = Collection(event, "GenVisTau")
        electrons = Collection(event, "Electron")
        muons = Collection(event, "Muon")
        photons = Collection(event, "Photon")

        genPartRecoStatus = [-1] * genParts_nGenPart
        genVisTauRecoStatus = [0] * genVisTaus.GenVisTau_nGenVisTau

        #Loop through genParticles and denote which ones are valid to be matched to for the particles we care about
        pdgIDs = [11, 13, 22] #el, mu, pho
        for i, genPart in enumerate(genParts):
            if (genPart.pdgId in pdgIDs) and (genPart.statusFlags & 4096) > 0 and (genPart.status == 1): #bit13 = 4098 = isLastCopy, status=1 is stable
                genPartRecoStatus[i] = 0 #Valid to be matched to later
            else:
                genPartRecoStatus[i] = -1 #Not relevant for us

        # Iterate through the relevant reco particles, setting the corresponding genParticles reco status to the reco particles pdgID
        for el in electrons:
            if genPartRecoStatus[el.genPartIdx] == 0:
                genPartRecoStatus[el.genPartIdx] = 11
        for mu in muons:
            if genPartRecoStatus[mu.genPartIdx] == 0:
                genPartRecoStatus[mu.genPartIdx] = 13
        for pho in photons:
            if genPartRecoStatus[pho.genPartIdx] == 0:
                genPartRecoStatus[pho.genPartIdx] = 22
        for tau in taus:
            genVisTauRecoStatus[tau.genPartIdx] == 15


        self.out.fillBranch("Eff_recoPartsStatus", genPartRecoStatus)
        self.out.fillBranch("Eff_recoVisTausStatus", genVisTauRecoStatus)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

RecoEffProducerConstr = lambda : RecoEffProducer()
