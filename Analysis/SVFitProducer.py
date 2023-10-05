import ROOT
from math import cos, sin, sqrt
import os
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection

class SVFitProducer(Module):
    def __init__(self):
        ROOT.gInterpreter.ProcessLine(".include ../../../TauAnalysis/ClassicSVfit/src/") #Look for the files to include here
        #ROOT.gInterpreter.ProcessLine(".include ../../../TauAnalysis/ClassicSVfit/interface/")
        #for baseName in ["ClassicSVfit", "ClassicSVfitIntegrand", "MeasuredTauLepton", "svFitAuxFunctions", "svFitHistogramAdapter", "SVfitIntegratorMarkovChain"]: 
        for baseName in ["MeasuredTauLepton", "svFitAuxFunctions", "svFitHistogramAdapter", "ClassicSVfit"]:
            #if os.path.isfile("{0:s}_cc.so".format(baseName)) :
            #    ROOT.gInterpreter.ProcessLine('#include "{0:s}.h"'.format(baseName))
            if os.path.isfile("{0:s}_cc.so".format(baseName)) :
                ROOT.gInterpreter.ProcessLine(".L {0:s}_cc.so".format(baseName))
            else:
                ROOT.gInterpreter.ProcessLine(".L {0:s}.cc++".format(baseName))
        
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("SVFit_TauPairMass", "F")
        self.out.branch("SVFit_TauPairMassErr", "F")
        self.out.branch("SVFit_TauPairMT", "F")
        self.out.branch("SVFit_TauPairMTErr", "F")


    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        tauPairMass = -1
        tauPairMassErr = -1
        tauPairMT = -1
        tauPairMTErr = -1

        #Get MET info
        measuredMETx = event.MET_pt*cos(event.MET_phi)
        measuredMETy = event.MET_pt*sin(event.MET_phi)
        covMET = ROOT.TMatrixD(2,2)
        covMET[0][0] = event.MET_covXX
        covMET[1][0] = event.MET_covXY
        covMET[0][1] = event.MET_covXY
        covMET[1][1] = event.MET_covYY
        
        #Get the two reconstructed objects
        measTau1, measTau2 = None, None
        if event.ETau_HavePair:
            idx = event.ETau_EIdx
            measTau1 = ROOT.MeasuredTauLepton(2, event.Electron_pt[idx], event.Electron_eta[idx], event.Electron_phi[idx], event.Electron_mass[idx])
            idx = event.ETau_TauIdx
            measTau2 = ROOT.MeasuredTauLepton(1, event.Tau_pt[idx], event.Tau_eta[idx], event.Tau_phi[idx], event.Tau_mass[idx], event.Tau_decayMode[idx])
        elif event.MuTau_HavePair: 
            idx = event.MuTau_MuIdx
            measTau1 = ROOT.MeasuredTauLepton(3, event.Muon_pt[idx], event.Muon_eta[idx], event.Muon_phi[idx], event.Muon_mass[idx])
            idx = event.MuTau_TauIdx
            measTau2 = ROOT.MeasuredTauLepton(1, event.Tau_pt[idx], event.Tau_eta[idx], event.Tau_phi[idx], event.Tau_mass[idx], event.Tau_decayMode[idx])
        elif event.TauTau_HavePair:
            idx = event.TauTau_Tau0Idx
            measTau1 = ROOT.MeasuredTauLepton(1, event.Tau_pt[idx], event.Tau_eta[idx], event.Tau_phi[idx], event.Tau_mass[idx], event.Tau_decayMode[idx])
            idx = event.TauTau_Tau1Idx
            measTau2 = ROOT.MeasuredTauLepton(1, event.Tau_pt[idx], event.Tau_eta[idx], event.Tau_phi[idx], event.Tau_mass[idx], event.Tau_decayMode[idx])
        
        
        if measTau1 is not None and measTau2 is not None:
            #Make a vector of the two objects
            MeasTauVec = ROOT.std.vector('MeasuredTauLepton')
            measTaus = MeasTauVec()
            measTaus.push_back(measTau1)
            measTaus.push_back(measTau2)
        
            #Do the fit and extra Mass, MT and their respective errors
            SVFit = ROOT.ClassicSVfit()
            SVFit.integrate(measTaus, measuredMETx, measuredMETy, covMET)
            tauPairMass = SVFit.getHistogramAdapter().getMass()
            tauPairMassErr = SVFit.getHistogramAdapter().getMassErr()
            tauPairMT = SVFit.getHistogramAdapter().getTransverseMass()
            tauPairMTErr = SVFit.getHistogramAdapter().getTransverseMassErr()

        self.out.fillBranch("SVFit_TauPairMass", tauPairMass)
        self.out.fillBranch("SVFit_TauPairMassErr", tauPairMassErr)
        self.out.fillBranch("SVFit_TauPairMT", tauPairMT)
        self.out.fillBranch("SVFit_TauPairMTErr", tauPairMTErr)
        
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
SVFitProducerConstr = lambda : SVFitProducer()
