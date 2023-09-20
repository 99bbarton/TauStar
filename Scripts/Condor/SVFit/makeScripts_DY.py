#Script to make the necessary condor .jdl and .sh scripts to run SVfit over 

import os

outDirBase = "/store/user/bbarton/SVFit/DY/DY0/"
years = ["2015", "2016", "2017", "2018"]

inDirBase = os.environ["TSMC"] + "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M50_"
inParams = {"2015": [inDirBase + "2015_29032023/230329_204708/0000/", 66], "2016":[inDirBase + "2016_29032023/230329_195413/0000/", 61], "2017": [inDirBase+ "2017_29032023/230329_185945/0000/", 75 ], "2018": ["2018_29032023/230329_180553/0000/", 71]}

for year in years:

    inDir = inParams[year][0]
    nTrees = inParams[year][1]
    for treeN in range(1, nTrees+1):
        filename = "tree_" + str(treeN)

        #Executable .sh scripts
        with open("run_" + year + "_" + filename + ".sh", "w+") as outFile:

            outFile.write("#!/bin/bash\n")
            outFile.write("set -x\n")
            outFile.write("OUTDIR="+ outDirBase + year + "/\n")

            outFile.write('echo "Starting job on " `date` #Date/time of start of job\n')
            outFile.write('echo "Running on: `uname -a`" #Condor job is running on this node\n')
            outFile.write('echo "System software: `cat /etc/redhat-release`" #Operating System on that node\n')

            outFile.write("xrdcp root://cmseos.fnal.gov//store/user/bbarton/CMSSW_10_6_27.tgz .\n")
            outFile.write("source /cvmfs/cms.cern.ch/cmsset_default.sh\n")
            outFile.write("tar -xf CMSSW_10_6_27.tgz\n")
            outFile.write("rm CMSSW_10_6_27.tgz\n")
            outFile.write("cd CMSSW_10_6_27/src/\n")
            outFile.write("scramv1 b ProjectRename # this handles linking the already compiled code - do NOT recompile\n")
            outFile.write("eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers\n")

            outFile.write("xrdcp root://cmseos.fnal.gov/" + inDir +"/"+ filename + ".root .\n")

            outFile.write("tauStar_SVFit ./ " + filename + ".root\n")

            outFile.write("#Copy files to eos area\n")

            outFile.write('echo "*******************************************"\n')
            outFile.write('echo "xrdcp output for condor to "\n')
            outFile.write("echo $OUTDIR\n")

            outFile.write("xrdcp " + filename + ".root " + "root://cmseos.fnal.gov/${OUTDIR}\n")
            outFile.write("XRDEXIT=$?\n")
            outFile.write("if [[ $XRDEXIT -ne 0 ]]; then\n")
            outFile.write('echo "exit code $XRDEXIT, failure in xrdcp"\n')
            outFile.write("exit $XRDEXIT\n")
            outFile.write("fi\n")

            outFile.write("hostname\n")
            outFile.write("date\n")
        
        #Job configuration files
        with open("jobConfig_" + year + "_" + filename + ".jdl", "w") as jdlFile:
            jdlFile.write('universe = vanilla\n')
            jdlFile.write("Executable = run_" + year + "_" + filename + ".sh\n")
            jdlFile.write('should_transfer_files = YES\n')
            jdlFile.write('when_to_transfer_output = ON_EXIT\n')
            jdlFile.write('Output = condor_SVFit_$(Cluster)_$(Process).stdout\n')
            jdlFile.write('Error = condor_SVFit_$(Cluster)_$(Process).stderr\n')
            jdlFile.write('Log = condor_SVFit_$(Cluster)_$(Process).log\n')
            jdlFile.write('Queue 1\n')
