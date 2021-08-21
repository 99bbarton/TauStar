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
	self.h_ptnum = ROOT.TH1F('h_ptnum', 'h_ptnum', 10, 0, 100)
        self.addObject(self.h_ptnum)
        self.h_ptdenom = ROOT.TH1F('h_ptdenom', 'h_ptdenom', 10, 0, 100)
        self.addObject(self.h_ptdenom)
	self.h_mt = ROOT.TH1F('h_mt', 'mt', 15, 0, 150)
        self.addObject(self.h_mt)
        self.h_cosdphi = ROOT.TH1F('h_cosdphi', 'cos(#Delta#phi)', 10, -1, 1)
        self.addObject(self.h_cosdphi)
	self.h_metEt = ROOT.TH1F("h_metEt", "MET_sumEt", 150, 0, 1500)
	self.addObject(self.h_metEt)
	#self.h_ptEff = ROOT.TH1F('h_ptEff', 'Single Electron Trigger Efficiency', 10, 0, 100)
	#self.h_ptEff.SetXTitle("Electron pt [GeV/c]")
	#self.h_ptEff.SetYTitle("Trigger Efficiency")
        #self.addObject(self.h_ptEff)
    def endJob(self):
        Module.endJob(self)
        print("# of reconstructable events: %s: " % self.ntot)
        print(" # of events with a single reconstructed el: %s" % self.n1)
        print("  and additionally pass single electron trigger: %s" % self.n2)
        eff = float(self.n1)/float(self.ntot)
        print("     signal eff: %f " % eff)
        triggereff_el = float(self.n2)/float(self.n1)
        print("     single el trigger eff: %f " % triggereff_el)
	#self.h_ptEff.Divide(self.h_ptnum, self.h_ptdenom)
	#canv = ROOT.TCanvas("canv", "Single Electron Trigger Eff", 600, 600)
	#self.h_ptEff.Draw("err")
	#canv.SaveAs("~/nobackup/TauStar/Plots/singleElTrigEff.png")
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)""" 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
	
	#Require no muons and taus
	muons = Collection(event, "Muon")
	taus = Collection(event, "Tau")

        # We don't want reconstructed muons
        for mu in muons:
            muID = mu.pt>=27. and abs(mu.eta)<2.4
            muID = muID and mu.pfIsoId>=4 and mu.tightId
            if muID:
                return False
		
	#We don't want reconstructable taus
	for tau in taus:
		tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (32&tau.idDeepTau2017v2p1VSe)
		tauID = tauID and tau.pt>=20 and abs(tau.eta)<2.3
		if tauID:
			return False

	#Don't want b-tagged events
	jets = Collection(event, "Jet")
	nBJetsM = 0
	for jet in jets:
		 #https://twiki.cern.ch/CMS/BtagRecommendation106XUL18
		if jet.btagDeepB >= 0.4168: #Medium wp
			return False

        electrons = Collection(event, "Electron")
        nGenEls = 0
        # check if there are even any reconstructable electrons
        #for el in electrons:
        #    if el.genPartFlav==15: 
	#	nGenEls = nGenEls + 1
        #if nGenEls != 1: 
	#	return False
	if len(electrons) < 1:
		return False

        # number of denominator events
        self.ntot = self.ntot + 1

        nGoodEl = 0
        # find good reconstructed electrons
        for el in electrons:
            elID = abs(el.eta)<2.5
            elID = elID and el.mvaFall17V2Iso_WP90 
            if elID:
                nGoodEl = nGoodEl + 1
                goodEl = el

        # require exactly one
        if nGoodEl != 1: 
		return False
	
#	
        self.n1 = self.n1 + 1
	
	# check trigger performance
        #https://twiki.cern.ch/CMS/MuonHLT2017#Recommendations_for_2017_data_an
        self.h_ptdenom.Fill(goodEl.pt)
        
	trigger = False
	if hasattr(event, "HLT_Ele27_WPTight_Gsf"): Trigger = trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele25_eta2p1_WPTight_Gsf"): trigger = trigger or event.HLT_Ele25_eta2p1_WPTight_Gsf
        #2017
        if hasattr(event, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf_L1DoubleEG
        if hasattr(event, "HLT_Ele35_WPTight_Gsf"): trigger = trigger or event.HLT_Ele35_WPTight_Gsf
        #if hasattr(event, "HLT_Ele27_WPTight_Gsf"): trigger = trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele32_WPTight_Gsf"): trigger = trigger or event.HLT_Ele32_WPTight_Gsf
        if trigger:
            self.n2 = self.n2 + 1
            self.h_ptnum.Fill(goodEl.pt)

	#Calculate variables used later for W->e+nu event selection
	# deltaPhi between the Electron and MET
        cosdphi = math.cos(deltaPhi(goodEl.phi, event.MET_phi))
        self.h_cosdphi.Fill(cosdphi)
        # transverse mass
        mT = 2. * event.MET_pt * goodEl.pt * (1.-cosdphi)
        mT = math.sqrt(mT)
        self.h_mt.Fill(mT)
	self.h_metEt.Fill(event.MET_sumEt)

			
	return True	



SingleElTriggerConstr = lambda : SingleElTrigger()
######################################### END MODULE CLASS ###################################






        
#files = ["root://cmsxrootd.fnal.gov///store/mc/RunIISummer20UL18NanoAODv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v1/230000/F33C455E-704C-0847-A69C-4996D0CDD707.root"]
#files = ["root://cmseosmgm01.fnal.gov:1094//store/user/fojensen/tauHats2021/F33C455E-704C-0847-A69C-4996D0CDD707.root"];
#files = ["root://cmsxrootd.fnal.gov///store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m625_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/300236C3-B93D-8847-AE65-1973AA2F1506.root"]
#files = ["root://cmseosmgm01.fnal.gov:1094//store/user/fojensen/tauHats2021/300236C3-B93D-8847-AE65-1973AA2F1506.root"]
#files = ["root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL18NanoAODv2/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v2/100000/14F26C77-EC1C-A34E-A935-D1FBA3E420C6.root"]
#files = ["root://cmseosmgm01.fnal.gov:1094//store/user/fojensen/tauHats2021/14F26C77-EC1C-A34E-A935-D1FBA3E420C6.root"]
#files = ["root://cmsxrootd.fnal.gov///store/mc/RunIISummer20UL18NanoAODv2/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v3/100000/99D8CE15-B532-164E-BB6D-03EAC1BEE6EC.root"]
#files = ["root://cmseosmgm01.fnal.gov:1094//store/user/fojensen/tauHats2021/99D8CE15-B532-164E-BB6D-03EAC1BEE6EC.root"]

fileNames = ["WJetsToLNu_2018.root", "DYJetsToLL_2018.root", "DYJetsToLLM10_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root", 
"TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "WW_2018.root", "WZ_2018.root", "ZZ_2018.root", "ST_t_channel_antitop_2018.root", "ST_t_channel_top_2018.root"]


for fileName in fileNames:
# Run SingleElTrigger.py over all MC files
	outName = fileName.split("_2018")[0] + ".root"
	print "Processing " + fileName
	print "Will write output to " + outName
	files = ["root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdas_19072021/"+fileName]



	#c++ style syntax
	preselection = "1>0"

	p = PostProcessor(
    	".",
    	files,
    	cut=preselection,
    	branchsel=None,
    	#maxEntries = 100000,
    	modules=[SingleElTrigger()],
    	noOut=True,
    	histFileName=outName,
    	histDirName="plots",
	)
	p.run()

#os.system("mv " + outName + " ~/nobackup/TauStar/Data/TrigEffTrees/")
