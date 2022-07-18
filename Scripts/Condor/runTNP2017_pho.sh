#!/bin/bash
set -x
# Run tnp analyzer as a condor job

FLAG=passingMVA94XV2wp90

###############################
###   Choose which config file an associated path you want to run with ####
## ------------------------------------------------------------------------------
TNP_CONFIG=myPhoConfig2017.py
MAIN_DIR=2017/PhoID/FineBins/PassElVeto/

#$TNP_CONFIG=myPhoConfig2017_courseBins.py
#MAIN_DIR=2017/PhoID/CourseBins/PassElVeto/

#$TNP_CONFIG=myPhoConfig2017_pV.py
#MAIN_DIR=2017/PhoID/FineBins/PixelVeto/

#$TNP_CONFIG=myPhoConfig2017_courseBins_pV.py
#MAIN_DIR=2017/PhoID/CourseBins/PixelVeto/

## ------------------------------------------------------------------------------------------------------
OUTDIR=root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_Fits/$MAIN_DIR

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
cd Fits/$MAIN_DIR/$FLAG/
echo "pwd"
pwd
echo "List all root files = "
ls *.root
echo "List all files"
ls -alh
 
echo "*******************************************"
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
