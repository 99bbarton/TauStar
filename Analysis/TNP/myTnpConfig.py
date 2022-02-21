#Settings configuration for TNP fitter analyzing performance of the Single-Electron Trigger
#Currently configured for UL2018 samples
#Based off https://github.com/cms-egamma/egm_tnp_analysis/blob/master/etc/config/settings_pho_UL2018.py


#############################################################
########## General settings
#############################################################
# flag to be Tested
flags = {
#    'passing_HLT_Ele27_WPTight_Gsf' : '(passing_HLT_Ele27_WPTight_Gsf == 1)',
#    'passing_HLT_Ele25_eta2p1_WPTight_Gsf' : '(passing_HLT_Ele25_eta2p1_WPTight_Gsf == 1)',
#    'passing_HLT_Ele32_WPTight_Gsf_L1DoubleEG' : '(passing_HLT_Ele32_WPTight_Gsf_L1DoubleEG == 1)',
#    'passing_HLT_Ele35_WPTight_Gsf' : '(passing_HLT_Ele35_WPTight_Gsf == 1)',
    'passHltEle32WPTightGsf' : '(passHltEle32WPTightGsf == 1)',
    }

#baseOutDir = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_Fits/"
#baseOutDir = "/uscms/home/bbarton/nobackup/CMSSW_10_6_13/src/EgammaAnalysis/egm_tnp_analysis/Fits/"
baseOutDir = "Fits/"

#############################################################
########## samples definition  - preparing the samples
#############################################################
### samples are defined in etc/inputs/myTnpSampleDef.py

import etc.inputs.myTnpSampleDef as tnpSamples
tnpTreeDir = 'tnpEleTrig'

samplesDef = {
    'data'   : tnpSamples.UL2018['data_Run2018A'].clone()
  #  'mcLO'  : tnpSamples.UL2018['DY_LO'].clone(),
  #  'mcNLO'  : tnpSamples.UL2018['DY_NLO'].clone(),
}

## Add remaining data samples
samplesDef['data'].add_sample( tnpSamples.UL2018['data_Run2018B'] )
samplesDef['data'].add_sample( tnpSamples.UL2018['data_Run2018C'] )
samplesDef['data'].add_sample( tnpSamples.UL2018['data_Run2018D'] )

## some sample-based cuts... general cuts defined here after
## require mcTruth on MC DY samples and additional cuts
## all the samples MUST have different names (i.e. sample.name must be different for all)
## if you need to use 2 times the same sample, then rename the second one
samplesDef['data' ].set_tnpTree(tnpTreeDir)
#if not samplesDef['mcLO' ] is None: samplesDef['mcLO'].set_tnpTree(tnpTreeDir)
#if not samplesDef['mcNLO' ] is None: samplesDef['mcNLO'].set_tnpTree(tnpTreeDir)
#if not samplesDef['mcLO' ] is None: samplesDef['mcLO'].set_mcTruth()
#if not samplesDef['mcNLO' ] is None: samplesDef['mcNLO'].set_mcTruth()


## set MC weight, simple way (use tree weight) 
weightName = 'totWeight'
#if not samplesDef['mcLO' ] is None: samplesDef['mcLO' ].set_weight(weightName)
#if not samplesDef['mcNLO' ] is None: samplesDef['mcNLO' ].set_weight(weightName)


#############################################################
########## bining definition  [can be nD bining]
#############################################################
biningDef = [
   { 'var' : 'el_sc_eta' , 'type': 'float', 'bins': [0, 1.4442, 1.566, 2.5] },
   { 'var' : 'el_pt' , 'type': 'float', 'bins': [0, 29, 34, 50, 75, 100, 150, 200, 250] },
]

#############################################################
########## Cuts definition for all samples
#############################################################
### cut
cutBase   = 'el_sc_abseta < 2.5 && el_sc_et > 5'


#### or remove any additional cut (default)
additionalCuts = None


#############################################################
########## fitting params to tune fit by hand if necessary
#############################################################
tnpParNomFit = [
    "meanP[-0.0,-5.0,5.0]","sigmaP[0.9,0.5,5.0]",
    "meanF[-0.0,-5.0,5.0]","sigmaF[0.9,0.5,5.0]",
    "acmsP[60.,50.,80.]","betaP[0.05,0.01,0.08]","gammaP[0.1, -2, 2]","peakP[90.0]",
    "acmsF[60.,50.,80.]","betaF[0.05,0.01,0.08]","gammaF[0.1, -2, 2]","peakF[90.0]",
    ]

tnpParAltSigFit = [
    "meanP[-0.0,-5.0,5.0]","sigmaP[1,0.7,6.0]","alphaP[2.0,1.2,3.5]" ,'nP[3,-5,5]',"sigmaP_2[1.5,0.5,6.0]","sosP[1,0.5,5.0]",
    "meanF[-0.0,-5.0,5.0]","sigmaF[2,0.7,15.0]","alphaF[2.0,1.2,3.5]",'nF[3,-5,5]',"sigmaF_2[2.0,0.5,6.0]","sosF[1,0.5,5.0]",
    "acmsP[60.,50.,75.]","betaP[0.04,0.01,0.06]","gammaP[0.1, 0.005, 1]","peakP[90.0]",
    "acmsF[60.,50.,75.]","betaF[0.04,0.01,0.06]","gammaF[0.1, 0.005, 1]","peakF[90.0]",
    ]
    
tnpParAltSigFit_addGaus = [
    "meanP[-0.0,-5.0,5.0]","sigmaP[1,0.7,6.0]","alphaP[2.0,1.2,3.5]" ,'nP[3,-5,5]',"sigmaP_2[1.5,0.5,6.0]","sosP[1,0.5,5.0]",
    "meanF[-0.0,-5.0,5.0]","sigmaF[2,0.7,6.0]","alphaF[2.0,1.2,3.5]",'nF[3,-5,5]',"sigmaF_2[2.0,0.5,6.0]","sosF[1,0.5,5.0]",
    "meanGF[80.0,70.0,100.0]","sigmaGF[15,5.0,125.0]",
    "acmsP[60.,50.,75.]","betaP[0.04,0.01,0.06]","gammaP[0.1, 0.005, 1]","peakP[90.0]",
    "acmsF[60.,50.,85.]","betaF[0.04,0.01,0.06]","gammaF[0.1, 0.005, 1]","peakF[90.0]",
    ]

tnpParAltBkgFit = [
    "meanP[-0.0,-5.0,5.0]","sigmaP[0.9,0.5,5.0]",
    "meanF[-0.0,-5.0,5.0]","sigmaF[0.9,0.5,5.0]",
    "alphaP[0.,-5.,5.]",
    "alphaF[0.,-5.,5.]",
    ]
