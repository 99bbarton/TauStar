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

        genPartRecoStatus = [0] * event["nGenPart"]
        genVisTauRecoStatus = [0] * event["nGenVisTau"]

        #Loop through genParticles and denote which ones are valid to be matched to for the particles we care about by writing their negative pdgIDs, else 0
        pdgIDs = [11, -11, 13, -13, 22] #el, mu, pho
        for i, genPart in enumerate(genParts):
            if (genPart.pdgId in pdgIDs) and (genPart.statusFlags & 8192) > 0 and (genPart.status == 1): #8192 = isLastCopy, status=1 is stable
                if (abs(genPart.pdgId) % 11 == 0) and genPart.pt <= 5.0: #Reco els and phos are only saved for pt>5 
                    continue
                #https://cms-nanoaod-integration.web.cern.ch/integration/cms-swCMSSW_10_6_X/mc106Xul17v2_doc.html#:~:text=Unclustered%20Energy%20Up-,Muon,-slimmedMuons%20after%20basic
                if abs(genPart.pdgId) == 13 and genPart.pt <= 18.0: #Reco mu selection at link above. Note pt>3 are saved if also passing an ID. Ignore those here to only study reco eff
                    continue
                
                if genPart.pdgId < 0:
                    genPartRecoStatus[i] = genPart.pdgId #Valid to be matched to later
                else:
                    genPartRecoStatus[i] = -1*genPart.pdgId
            else:
                genPartRecoStatus[i] = -1 #Not relevant for us

                
        for j, genVisTau in enumerate(genVisTaus):
            if genVisTau.pt <= 18.0:
                genVisTauRecoStatus[j] = -1 #Reco taus are pt>18
                

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
            if tau.genPartFlav == 5: #If a hadronic tau decay, points to GenVisTau collection rather than GenPart
                if tau.genPartIdx >= event["nGenVisTau"]:
                    print("WARNING tau.genPartIdx > nGenVisTau:  genParts[tau.genPartIdx].pdgID= " + str(genParts[tau.genPartIdx].pdgId))
                elif deltaR(tau, genVisTaus[tau.genPartIdx]) < 0.15:
                    genVisTauRecoStatus[tau.genPartIdx] = 15
                else:
                    print("WARNING tau DR match failed: tau.eta, tau.phi : genVisTau.eta, genVisTau.phi = "+str(tau.eta)+", "+str(tau.phi)+" : "+str(genVisTaus[tau.genPartIdx].eta)+", "+str(genVisTaus[tau.genPartIdx].phi))


        self.out.fillBranch("Eff_recoPartsStatus", genPartRecoStatus)
        self.out.fillBranch("Eff_recoVisTausStatus", genVisTauRecoStatus)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

RecoEffProducerConstr = lambda : RecoEffProducer()
