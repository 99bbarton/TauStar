#!/bin/bash
set -x
# Run SingleElTrigger_condor.py as a condor job



echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node

xrdcp root://cmseos.fnal.gov//store/user/bbarton/CMSSW_10_6_23.tgz .
source /cvmfs/cms.cern.ch/cmsset_default.sh
tar -xf CMSSW_10_6_23.tgz
rm CMSSW_10_6_23.tgz
cd CMSSW_10_6_23/src/
scramv1 b ProjectRename # this handles linking the already compiled code - do NOT recompile
eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers
echo $CMSSW_BASE "is the CMSSW we have on the local worker node"

python PhysicsTools/NanoAODTools/python/postprocessing/examples/SingleElTrigger_condor.py

#Copy files to eos area
echo "pwd"
pwd
echo "List all root files = "
ls *.root
echo "List all files"
ls -alh
echo "*******************************************"
OUTDIR=root://cmseos.fnal.gov//store/user/bbarton/TrigEffCondorOutputs/
echo "xrdcp output for condor to "
echo $OUTDIR
for FILE in *.root
do
  echo "xrdcp -f ${FILE} ${OUTDIR}/${FILE}"
  echo "${FILE}" 
  echo "${OUTDIR}"
 xrdcp -f ${FILE} ${OUTDIR}/${FILE} 2>&1
  XRDEXIT=$?
  if [[ $XRDEXIT -ne 0 ]]; then
    rm *.root
    echo "exit code $XRDEXIT, failure in xrdcp"
    exit $XRDEXIT
  fi
  rm ${FILE}
done

hostname
date
