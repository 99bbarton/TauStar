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
        self.out.branch("Eff_recoPartsStatus","I", lenVar="nGenPart")
        self.out.branch("Eff_recoVisTausStatus","I", lenVar="nGenVisTau")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        genParts = Collection(event, "GenPart")
        genVisTaus = Collection(event, "GenVisTau")
        electrons = Collection(event, "Electron")
        muons = Collection(event, "Muon")
        photons = Collection(event, "Photon")
        taus = Collection(event, "Tau")

        genPartRecoStatus = [-1] * event["nGenPart"]
        genVisTauRecoStatus = [0] * event["nGenVisTau"]

        #Loop through genParticles and denote which ones are valid to be matched to for the particles we care about by writing their negative pdgIDs, else 0
        pdgIDs = [11, -11, 13, -13, 22] #el, mu, pho
        for i, genPart in enumerate(genParts):
            if (genPart.pdgId in pdgIDs) and (genPart.statusFlags & 8192) > 0 and (genPart.status == 1): #8192 = isLastCopy, status=1 is stable
                if genPart.pdgId < 0:
                    genPartRecoStatus[i] = genPart.pdgId #Valid to be matched to later
                else:
                    genPartRecoStatus[i] = -1*genPart.pdgId
            else:
                genPartRecoStatus[i] = -1 #Not relevant for us

        # Iterate through the relevant reco particles, setting the corresponding genParticles reco status to the reco particles pdgID
        for el in electrons:
            if genPartRecoStatus[el.genPartIdx] == -11:
                genPartRecoStatus[el.genPartIdx] = 11
        for mu in muons:
            if genPartRecoStatus[mu.genPartIdx] == -13:
                genPartRecoStatus[mu.genPartIdx] = 13
        for pho in photons:
            if genPartRecoStatus[pho.genPartIdx] == -22:
                genPartRecoStatus[pho.genPartIdx] = 22
        for tau in taus:
            if tau.genPartFlav == 5: #If a hadronic tau decay
                if tau.genPartIdx >= event["nGenVisTau"]:
                    print("WARNING tau.genPartIdx > nGenVisTau:  genParts[tau.genPartIdx].pdgID= " + str(genParts[tau.genPartIdx].pdgId))
                else:
                    genVisTauRecoStatus[tau.genPartIdx] == 15


        self.out.fillBranch("Eff_recoPartsStatus", genPartRecoStatus)
        self.out.fillBranch("Eff_recoVisTausStatus", genVisTauRecoStatus)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

RecoEffProducerConstr = lambda : RecoEffProducer()
