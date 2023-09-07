#Script to make the necessary condor .jdl and .sh scripts to run SVfit over 

import os

inDir = os.environ["TSMC"]
outDir = "/store/user/bbarton/SVFit/"
filebases = ["DYJetsToLL_M10to50", "DYJetsToLL_M50", "ZGToLLG"]
years = ["2015", "2016", "2017", "2018"]

for filebase in filebases:
    for year in years:
        filename = filebase + "_" + year

        #Executable .sh scripts
        with open("run_" + filename + ".sh", "w+") as outFile:

            outFile.write("#!/bin/bash\n")
            outFile.write("set -x\n")
            outFile.write("OUTDIR="+ outDir + "\n")

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

            outFile.write("tauStar_SVFit ./ " + filebase + "_" + year + ".root\n")

            outFile.write("#Copy files to eos area\n")

            outFile.write('echo "*******************************************"\n')
            outFile.write('echo "xrdcp output for condor to "\n')
            outFile.write("echo $OUTDIR\n")

            outFile.write("xrdcp" + filename + ".root " + "root://cmseos.fnal.gov/${OUTDIR}\n")
            outFile.write("XRDEXIT=$?\n")
            outFile.write("if [[ $XRDEXIT -ne 0 ]]; then\n")
            outFile.write('echo "exit code $XRDEXIT, failure in xrdcp"\n')
            outFile.write("exit $XRDEXIT\n")
            outFile.write("fi\n")

            outFile.write("hostname\n")
            outFile.write("date\n")
        
        #Job configuration files
        with open("jobConfig_" + filename + ".jdl", "w") as jdlFile:
            jdlFile.write('universe = vanilla\n')
            jdlFile.write("Executable = run_" + filename + ".sh\n")
            jdlFile.write('should_transfer_files = YES\n')
            jdlFile.write('when_to_transfer_output = ON_EXIT\n')
            jdlFile.write('Output = condor_TNP_$(Cluster)_$(Process).stdout\n')
            jdlFile.write('Error = condor_TNP_$(Cluster)_$(Process).stderr\n')
            jdlFile.write('Log = condor_TNP_$(Cluster)_$(Process).log\n')
            jdlFile.write('Queue 1\n')
