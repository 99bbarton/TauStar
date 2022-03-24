#!/bin/bash
set -x
# Run tnp analyzer as a condor job


echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node

xrdcp root://cmseos.fnal.gov//store/user/bbarton/CMSSW_10_6_13.tgz .
source /cvmfs/cms.cern.ch/cmsset_default.sh
tar -xf CMSSW_10_6_13.tgz
rm CMSSW_10_6_13.tgz
cd CMSSW_10_6_13/src/
scramv1 b ProjectRename # this handles linking the already compiled code - do NOT recompile
eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers
echo $CMSSW_BASE "is the CMSSW we have on the local worker node"

cd EgammaAnalysis/egm_tnp_analysis/

python tnpEGM_fitter.py etc/config/myTnpConfig2016.py --flag passHltEle32WPTightGsf --checkBins
python tnpEGM_fitter.py etc/config/myTnpConfig2016.py --flag passHltEle32WPTightGsf --createBins
python tnpEGM_fitter.py etc/config/myTnpConfig2016.py --flag passHltEle32WPTightGsf --createHists

#Copy files to eos area
cd Fits/2016/passHltEle27WPTightGsf/
echo "pwd"
pwd
echo "List all root files = "
ls *.root
echo "List all files"
ls -alh
 
echo "*******************************************"
OUTDIR=root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_Fits/2016/
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
