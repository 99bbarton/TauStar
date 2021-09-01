#!/usr/bin/env python
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor
from importlib import import_module
import os
import sys
import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi, deltaR

class SingleElTrigger(Module):
    def __init__(self):
        self.writeHistFile = True
    def beginJob(self, histFile=None, histDirName=None):
        Module.beginJob(self, histFile, histDirName)
        self.ntot = 0
        self.n1 = 0
        self.n2 = 0
        self.h_ptnum = ROOT.TH1F('h_ptnum', 'h_ptnum', 50, 0, 500)
        self.addObject(self.h_ptnum)
        self.h_ptdenom = ROOT.TH1F('h_ptdenom', 'h_ptdenom', 50, 0, 500)
        self.addObject(self.h_ptdenom)
        self.h_mt = ROOT.TH1F('h_mt', 'mt', 15, 0, 150)
        self.addObject(self.h_mt)
        self.h_cosdphi = ROOT.TH1F('h_cosdphi', 'cos(#Delta#phi)', 10, -1, 1)
        self.addObject(self.h_cosdphi)
        self.h_metPt = ROOT.TH1F("h_metPt", "MET_pt", 75, 0, 750)
        self.addObject(self.h_metPt)
	
        self.counts = [["Baseline", 0], ["One el", 0], ["No Muons", 0], ["No Taus", 0], ["b-tag", 0], ["MET>200", 0], ["MET trig", 0], ["Trig", 0]]
	
    def endJob(self):
        Module.endJob(self)
        print("# of reconstructable events: %s: " % self.ntot)
        print(" # of events with a single reconstructed el: %s" % self.n1)
        print("  and additionally pass single electron trigger: %s" % self.n2)
        eff = float(self.n1)/float(self.ntot)
        print("     signal eff: %f " % eff)
        triggereff_el = float(self.n2)/float(self.n1)
        print("     single el trigger eff: %f " % triggereff_el)
        print self.counts
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)""" 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
	
        self.counts[0][1] += 1

	#Require no muons and taus
        muons = Collection(event, "Muon")
        taus = Collection(event, "Tau")
        electrons = Collection(event, "Electron")

        # number of denominator events
        self.ntot = self.ntot + 1        

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
        self.counts[1][1] += 1

        # We don't want reconstructed muons
        for mu in muons:
            muID = mu.pt>=27. and abs(mu.eta)<2.4
            muID = muID and mu.pfIsoId>=4 and mu.tightId
            if muID:
                return False
	
        self.counts[2][1] += 1	
	
	#We don't want reconstructable taus
        for tau in taus:
        	tauID = tau.pt>=20 and abs(tau.eta)<2.3
        	tauID = tauID and tau.idDecayModeNewDMs != 5 and tau.idDecayModeNewDMs != 6 and tau.idDecayModeNewDMs != 7
        	tauID = tauID and (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (32&tau.idDeepTau2017v2p1VSe)
        	if tauID:
        		return False  
        self.counts[3][1] += 1

	

        #Don't want b-tagged events
        jets = Collection(event, "Jet")
        nBJetsM = 0
        for jet in jets:
        	if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId): #TightID + lepVeto
         		#https://twiki.cern.ch/CMS/BtagRecommendation106XUL18
        		if jet.btagDeepB >= 0.4168: #Medium wp
        			return False
        self.counts[4][1] += 1
	
	
	#We want to select W events first so as not to bias ourselves by selecting with an el trigger
        if event.MET_pt < 200: #smallest value visible in triggers for 2018
        	return False
        self.counts[5][1] += 1
        #Use a MET trigger since W events have MET
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
        self.counts[6][1] += 1
        
	
	#Count this as a signal like event	
        self.n1 = self.n1 + 1
        self.h_ptdenom.Fill(goodEl.pt)	

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
            self.n2 = self.n2 + 1
            self.h_ptnum.Fill(goodEl.pt)
	
        self.counts[7][1] += 1

	#Calculate variables used for W->e+nu event selection
        # deltaPhi between the Electron and MET
        cosdphi = math.cos(deltaPhi(goodEl.phi, event.MET_phi))
        mT = 2. * event.MET_pt * goodEl.pt * (1.-cosdphi)
        mT = math.sqrt(mT)
        #met_sumEt = event.MET_sumEt
        #These cuts chosen by taking ratio of backgrounds to WJets
        #if mT < 50 or mT > 110:
        #       return False
	#print cosdphi	
        #if cosdphi >=0:
        #        return False
        #if met_sumEt < 800:
        #        return False

        self.h_cosdphi.Fill(cosdphi)
        self.h_mt.Fill(mT)
        self.h_metPt.Fill(event.MET_pt)

			
        return True	



SingleElTriggerConstr = lambda : SingleElTrigger()
######################################### END MODULE CLASS ###################################

def standaloneRun():	

	isData = True
	#treeVersion = "20082021"
	treeVersion = "30082021"
	year = "2018"

	fileNames = []
	if isData:
		fileNames = ["WJetsToLNu_2018.root", "DYJetsToLL_2018.root", "DYJetsToLLM10_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root", 
		"TTTo2L2Nu_bVeto_2018.root", "TTToSemiLeptonic_bVeto_2018.root", "WW_2018.root", "WZ_2018.root", "ZZ_2018.root", "ST_t_channel_antitop_2018.root", "ST_t_channel_top_2018.root"]
	else:
		fileNames = ["ElectronA_2018.root", "ElectronB_2018.root", "ElectronC_2018.root", "ElectronD_2018.root"]

	fileNames = ["WJetsToLNu_2018.root"]

	print "Trees version date is " + treeVersion
	print "Year is " + year
	print "isData = " + str(isData)
	print "All input files (" + str(len(fileNames)) + "):"
	print fileNames

	for fileName in fileNames:
	# Run SingleElTrigger.py over all MC files
		outName = fileName.split("_"+year)[0] + ".root"
		print "Processing " + fileName
		print "Will write output to " + outName
		files = ["root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_"+treeVersion+"/"+fileName]



		#c++ style syntax
		preselection = "1>0"

		#p = PostProcessor(
    		#".",
    		#files,
    		#cut=preselection,
    		#branchsel=None,
    		#maxEntries = 100000,
    		#modules=[SingleElTrigger()],
    		#noOut=True,
    		#histFileName=outName,
    		#histDirName="plots",
		#)
		#p.run()


if __name__ == "__main__":
	standaloneRun()
