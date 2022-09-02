#!/bin/bash
set -x
# Run tnp analyzer as a condor job

FLAG=passTriggerOR

###############################
###   Choose which config file an associated path you want to run with ####
## ------------------------------------------------------------------------------
TNP_CONFIG=myElTnpConfig2018.py
MAIN_DIR=2018/PassMVAID/PhotonOR/

## ------------------------------------------------------------------------------------------------------
OUTDIR=/store/user/bbarton/TrigEffStudies/TNP_Fits/$MAIN_DIR

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

python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --checkBins
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --createBins
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --createHists
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --doFit
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --doFit --mcSig --altSig
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --doFit --altSig
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --doFit --altBkg
python tnpEGM_fitter.py etc/config/$TNP_CONFIG --flag $FLAG --sumUp

#Copy files to eos area

echo "*******************************************"
echo "xrdcp output for condor to "
echo $OUTDIR


xrdcp -rf Fits/${MAIN_DIR}${FLAG} root://cmseos.fnal.gov/${OUTDIR}
XRDEXIT=$?
if [[ $XRDEXIT -ne 0 ]]; then
  echo "exit code $XRDEXIT, failure in xrdcp"
  exit $XRDEXIT
fi

hostname
date
