# TNP fit configuration for Photon ID SF measurement
#2015

# flag to be Tested
flags = {
    'passingMVA94XV2wp90' : '(passingMVA94XV2wp90 == 1)',
    'passingMVA94XV2wp80' : '(passingMVA94XV2wp80 == 1)',
    }

baseOutDir = 'Fits/2016/PhoID/StatBins/'

import etc.inputs.myPhoTnpSampleDef as tnpSamples
tnpTreeDir = 'tnpPhoIDs'

samplesDef = {
    'data'   : tnpSamples.UL2016_postVFP['data_Run2016F_postVFP'].clone(),
    'mcNom'  : tnpSamples.UL2016_postVFP['DY_LO'].clone(),
    'mcAlt'  : tnpSamples.UL2016_postVFP['DY_NLO'].clone(),
    'tagSel' : tnpSamples.UL2016_postVFP['DY_LO'].clone(),
}

## Add remaining data samples
samplesDef['data'].add_sample( tnpSamples.UL2016_postVFP['data_Run2016G'] )
samplesDef['data'].add_sample( tnpSamples.UL2016_postVFP['data_Run2016H'] )


## some sample-based cuts... general cuts defined here after
## require mcTruth on MC DY samples and additional cuts
## all the samples MUST have different names (i.e. sample.name must be different for all)
## if you need to use 2 times the same sample, then rename the second one
samplesDef['data' ].set_tnpTree(tnpTreeDir)
if not samplesDef['mcNom' ] is None: samplesDef['mcNom'].set_tnpTree(tnpTreeDir)
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt'].set_tnpTree(tnpTreeDir)
if not samplesDef['tagSel' ] is None: samplesDef['tagSel'].set_tnpTree(tnpTreeDir)
if not samplesDef['mcNom' ] is None: samplesDef['mcNom'].set_mcTruth()
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt'].set_mcTruth()
if not samplesDef['tagSel' ] is None: samplesDef['tagSel'].set_mcTruth(tnpTreeDir)

#set weights
weightName = 'totWeight'
if not samplesDef['mcNom' ] is None: samplesDef['mcNom' ].set_weight(weightName)
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt' ].set_weight(weightName)
if not samplesDef['tagSel' ] is None: samplesDef['tagSel' ].set_weight(weightName)

## Set binning
biningDef = [
   { 'var' : 'abs(ph_sc_eta)' , 'type': 'float', 'bins': [0.0, 2.5] },
   { 'var' : 'ph_et' , 'type': 'float', 'bins': [20, 200, 500, 1000] },
]

### cuts
cutBase   = 'tag_Ele_pt > 35 && abs(tag_sc_eta) < 2.5 && (abs(ph_sc_eta) < 1.442 || abs(ph_sc_eta) > 1.566)'
 
#### or remove any additional cut
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
