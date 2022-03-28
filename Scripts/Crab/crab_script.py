import datetime
then = datetime.datetime.now()
print ("Start date and time: ", then.strftime("%Y-%m-%d %H:%M:%S"))

import os
print "pwd: %s" % os.system("pwd")

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

import sys
print sys.argv
for arg in sys.argv:
    print arg

#interactive
#if len(sys.argv)<2:
#    print "missing year parameter!"
#year = int(sys.argv[1])

#crab
#== CMSSW: ['crab_script.py', '1', 'arg1=2016'] data
# mc
if len(sys.argv)<3:
    print "missing year parameter!"
#year = int(sys.argv[2][5:])
year = 2018

print "chosen year: %d " % year

from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import runsAndLumis

isSignalMC=False

testfile = [
"root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/WJetsToLNu_2018.root"
]


#print testfile

cut_ElTau = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=27. && (Electron_mvaFall17V2Iso_WPL||Electron_mvaFall17V2noIso_WPL))>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (32&Tau_idDeepTau2017v2p1VSe))>0"
cut_MuTau = "Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=24. && Muon_tightId && Muon_pfIsoId>=1)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>0"
cut_TauTau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>=2"
#cut_ElMu = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=12. && Electron_mvaFall17V2Iso_WP90)>0 && Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=8. && Muon_tightId && Muon_pfIsoId>=2)>0"
cut_MET = "MET_pt>=170."
#https://twiki.cern.ch/CMS/MissingETOptionalFiltersRun2
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"
#cut_ = "(" + cut_ElTau + " || " + cut_MuTau + " || " + cut_TauTau + " || " + cut_ElMu + ") && " + cut_Flag
cut_ = "(" + cut_ElTau + " || " + cut_MuTau + " || " + cut_TauTau + "|| " + cut_MET + ") && " + cut_Flag
cut_ = "1>0"
print cut_

#from PhysicsTools.NanoAODTools.postprocessing.examples.EEProducer import EEProducerConstr
#from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuProducer import MuMuProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ZProducer import ZProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElTauProducer import ElTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauProducer import MuTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.TauTauProducer import TauTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElMuProducer import ElMuProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElTriggerEff import ElTriggerEffConstr
#from PhysicsTools.NanoAODTools.postprocessing.modules.jme import jetmetHelperRun2

#jmeCorrections = createJMECorrector(isMC, "2018", "", "Total", True, "AK4PFchs", False)

applyZVeto = False
applyBVeto = False
print("applyZVeto: %s, applyBVeto: %s" % (applyZVeto, applyBVeto))
#modules_ = [ZProducerConstr(applyZVeto), JetProducerConstr(year, applyBVeto), ElTauProducerConstr(), MuTauProducerConstr(), TauTauProducerConstr(), ElMuProducerConstr()]
#modules_ = [ElTauProducerConstr(isSignalMC)]
modules_ = [ElTriggerEffConstr()]

#MC
if len(sys.argv)==3 or len(sys.argv)==4:
    if len(sys.argv)==3: w = float(sys.argv[2]) #interactive
    if len(sys.argv)==4: w = eval(str(sys.argv[3])[5:]) #crab
    print ("will run xsWeightProducer: %f" % w)
    from PhysicsTools.NanoAODTools.postprocessing.examples.xsWeightProducer import xsWeightProducer
    modules_ += [xsWeightProducer(w)]
    #from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_ElTau import SFProducerConstr_ElTau
    #from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_MuTau import SFProducerConstr_MuTau
    #from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_TauTau import SFProducerConstr_TauTau
    #modules_ += [SFProducerConstr_ElTau(year), SFProducerConstr_MuTau(year), SFProducerConstr_TauTau(year)]


p=PostProcessor(
    outputDir = "./",
    inputFiles = inputFiles(),
    #inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    #maxEntries = 100000,
    provenance = True,
    fwkJobReport = True,
    #haddFileName = "ran_m1000_f1_fprime0p1.root",
    #jsonInput = runsAndLumis(),
    #jsonInput = "Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt",
    outputbranchsel = "keep_and_drop.txt"
)

p.run()

now = datetime.datetime.now()
print ("Finish date and time: ", now.strftime("%Y-%m-%d %H:%M:%S"))
duration = now - then
print ("Total seconds elapsed: ", duration.total_seconds())
