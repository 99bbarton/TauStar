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

elVeto = True
#elVeto = False

bkgdFiles = ["root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/DY01234JetsToLL_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/DYJetsToLLM10_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/DYJetsToLL_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_s_channel_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_tW_antitop_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_tW_top_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_t_channel_antitop_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_t_channel_tauDecays_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ST_t_channel_top_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/TTTo2L2Nu_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/TTToSemiLeptonic_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/W01234JetsToLNu_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/WJetsToLNu_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/WW_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/WZ_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ZGToLLG_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/ZZ_2018.root"]


mcSigFiles = ["root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m1000_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m1250_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m1500_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m1750_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m175_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m2000_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m2500_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m250_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m3000_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m3500_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m375_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m4000_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m4500_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m5000_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m500_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m625_2018.root",
"root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m750_2018.root"
]

testfiles = ["root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01052022/Taustar_m4000_2018.root"]
#testfiles = mcSigFiles


from PhysicsTools.NanoAODTools.postprocessing.examples.PhoEffProducer import PhoEffProducerConstr

modules_ = [PhoEffProducerConstr(elVeto)]

p=PostProcessor(
    outputDir = "./",
    #inputFiles = inputFiles(),
    inputFiles = testfiles,
    cut = "",
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
