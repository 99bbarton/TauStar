#Settings configuration for TNP fitter analyzing performance of the Single-Electron Trigger
#Configured for UL2018 samples
#Based off https://github.com/cms-egamma/egm_tnp_analysis/blob/master/etc/config/settings_pho_UL2018.py


#############################################################
########## General settings
#############################################################
# flag to be Tested
flags = {
    'passHltEle32WPTightGsf' : '(passHltEle32WPTightGsf == 1)',
    }

baseOutDir = "Fits/2018/PassMVAID/Pt20/"

#############################################################
########## samples definition  - preparing the samples
#############################################################
### samples are defined in etc/inputs/myTnpSampleDef.py

import etc.inputs.myTnpSampleDef as tnpSamples
tnpTreeDir = 'tnpEleTrig'

samplesDef = {
    'data'   : tnpSamples.UL2018['data_Run2018A'].clone(),
    'mcNom'  : tnpSamples.UL2018['DY_LO'].clone(),
    'mcAlt'  : tnpSamples.UL2018['DY_NLO'].clone(),
    'tagSel' : tnpSamples.UL2018['DY_LO'].clone()
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
if not samplesDef['mcNom' ] is None: samplesDef['mcNom'].set_tnpTree(tnpTreeDir)
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt'].set_tnpTree(tnpTreeDir)
if not samplesDef['tagSel' ] is None: samplesDef['tagSel'].set_tnpTree(tnpTreeDir)
if not samplesDef['mcNom' ] is None: samplesDef['mcNom'].set_mcTruth()
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt'].set_mcTruth()
if not samplesDef['tagSel' ] is None: samplesDef['tagSel'].set_mcTruth(tnpTreeDir)


if not samplesDef['tagSel'] is None:
    samplesDef['tagSel'].rename('mcAltSel_DY_LO')
    samplesDef['tagSel'].set_cut('tag_Ele_pt > 35')
    samplesDef['tagSel'].set_cut('abs(tag_Ele_eta) <= 2.1') 

## set MC weight, simple way (use tree weight) 
weightName = 'totWeight'
if not samplesDef['mcNom' ] is None: samplesDef['mcNom' ].set_weight(weightName)
if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt' ].set_weight(weightName)
if not samplesDef['tagSel' ] is None: samplesDef['tagSel' ].set_weight(weightName)

#weightName = 'weights_2018_runABCD.totWeight'
#if not samplesDef['mcNom' ] is None: samplesDef['mcNom' ].set_weight(weightName)
#if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt' ].set_weight(weightName)
#if not samplesDef['tagSel'] is None: samplesDef['tagSel'].set_weight(weightName)
#if not samplesDef['mcNom' ] is None: samplesDef['mcNom' ].set_puTree('/eos/cms/store/group/phys_egamma/asroy/Tag-and-Probe_Tree/UL2018_MINIAOD_Nm1/PU_Trees/DY_madgraph_pho.pu.puTree.root')
#if not samplesDef['mcAlt' ] is None: samplesDef['mcAlt' ].set_puTree('/eos/cms/store/group/phys_egamma/asroy/Tag-and-Probe_Tree/UL2018_MINIAOD_Nm1/PU_Trees/DY_amcatnloext_pho.pu.puTree.root')
#if not samplesDef['tagSel'] is None: samplesDef['tagSel'].set_puTree('/eos/cms/store/group/phys_egamma/asroy/Tag-and-Probe_Tree/UL2018_MINIAOD_Nm1/PU_Trees/DY_madgraph_pho.pu.puTree.root')




#############################################################
########## bining definition  [can be nD bining]
#############################################################
biningDef = [
   { 'var' : 'el_sc_eta' , 'type': 'float', 'bins': [-2.5, -2, -1.566, -1.4442, -0.8, 0, 0.8, 1.4442, 1.566, 2, 2.5] },
   { 'var' : 'el_pt' , 'type': 'float', 'bins': [20, 34, 50, 75, 100, 150, 200, 500]  },
]

#############################################################
########## Cuts definition for all samples
#############################################################
### cut
cutBase   = 'abs(el_sc_eta) <= 2.5 && el_sc_et > 5 && passingMVA94Xwp90isoV2 == 1'


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
