 #Script to redo fitting of the high pt bins of completed TNP measurements
#

import os

#List of bins to redo the fits of
binList = ["30", "31", "32", "33", "34"]
#List of fits to redo for each bin
fitList = ["--doFit", "--doFit --altSig", "--doFit --altBkg"]
#List of config files
configs = ["myPhoConfig2015_noVeto.py", "myPhoConfig2016_noVeto.py", "myPhoConfig2017_noVeto.py", "myPhoConfig2018_noVeto.py"]
#configs = ["myPhoConfig2015_noVeto.py"]

commandBase = "python tnpEGM_fitter.py etc/config/" 
flag = " --flag passingMVA94XV2wp90 "
binBase = " --iBin "

for config in configs:
    for fit in fitList:
        for binN in binList:
            command = commandBase + config + flag + fit + binBase + binN
            print("command = " + command)
            os.system(command)

    os.system(commandBase + config + flag + "--sumUp")
