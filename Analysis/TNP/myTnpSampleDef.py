from libPython.tnpClassUtils import tnpSample

#Paths to EGamma POG official tag tuples
pogTnpTreePath2018 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/tomc/2020-05-20/UL2018/merged/"
pogTnpTreePath2017 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/tomc/2020-05-20/UL2018/merged/"
pogTnpTreePath2016 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/rasharma/2021-02-10/UL2016postVFP/merged/"
pogTnpTreePath2015 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/rasharma/2021-02-10/UL2016preVFP/merged/"

UL2018 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       pogTnpTreePath2018 + 'DY_LO.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       pogTnpTreePath2018 + 'DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2018A' : tnpSample('data_Run2018A' , pogTnpTreePath2018 + 'Run2018A.root' , lumi = 14.02672485),
    'data_Run2018B' : tnpSample('data_Run2018B' , pogTnpTreePath2018 + 'Run2018B.root' , lumi = 7.060617355),
    'data_Run2018C' : tnpSample('data_Run2018C' , pogTnpTreePath2018 + 'Run2018C.root' , lumi = 6.894770971),
    'data_Run2018D' : tnpSample('data_Run2018D' , pogTnpTreePath2018 + 'Run2018D.root' , lumi = 31.74220577),
    }

UL2017 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'              : tnpSample('DY_madgraph',
                                       pogTnpTreePath2017 + 'DYJetsToEE.root ',
                                       isMC = True, nEvts =  -1 ),
#    'DY_amcatnlo'                 : tnpSample('DY_amcatnlo',
#                                       eosUL2017 + 'DYJetsToLLM50amcatnloFXFX.root',
#                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnloext'                 : tnpSample('DY_amcatnloext',
                                       pogTnpTreePath2017 + 'DYJetsToLL_amcatnloFXFX.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2017B' : tnpSample('data_Run2017B' , pogTnpTreePath2017 + 'SingleEle_RunB.root' , lumi = 4.793961427),
    'data_Run2017C' : tnpSample('data_Run2017C' , pogTnpTreePath2017 + 'SingleEle_RunC.root' , lumi = 9.631214821 ),
    'data_Run2017D' : tnpSample('data_Run2017D' , pogTnpTreePath2017 + 'SingleEle_RunD.root' , lumi = 4.247682053 ),
    'data_Run2017E' : tnpSample('data_Run2017E' , pogTnpTreePath2017 + 'SingleEle_RunE.root' , lumi = 9.313642402 ),
    'data_Run2017F' : tnpSample('data_Run2017F' , pogTnpTreePath2017 + 'SingleEle_RunF.root' , lumi = 13.510934811),

    }

UL2016_postVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'              : tnpSample('DY_madgraph',
                                       pogTnpTreePath2016 + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_postVFP_UL2016.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnloext'                 : tnpSample('DY_amcatnloext',
                                       pogTnpTreePath2016 + 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_postVFP_UL2016.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2016F_postVFP' : tnpSample('data_Run2016F_postVFP' , pogTnpTreePath2016 + 'UL2016_SingleEle_Run2016F_postVFP.root' , lumi = 0.414987426),
    'data_Run2016G' : tnpSample('data_Run2016G' , pogTnpTreePath2016 + 'UL2016_SingleEle_Run2016G.root' , lumi = 7.634508755),
    'data_Run2016H' : tnpSample('data_Run2016H' , pogTnpTreePath2016 + 'UL2016_SingleEle_Run2016H.root' , lumi = 8.802242522),
    }

UL2016_preVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'              : tnpSample('DY_madgraph',
                                       pogTnpTreePath2015 + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_preVFP_UL2016.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnloext'                 : tnpSample('DY_amcatnloext',
                                       pogTnpTreePath2015 + 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_preVFP_UL2016.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2016B' : tnpSample('data_Run2016B' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016B.root' , lumi = 0.030493962),
    'data_Run2016B_ver2' : tnpSample('data_Run2016B_ver2' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016B_ver2.root' , lumi = 5.879330594),
    'data_Run2016C' : tnpSample('data_Run2016C' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016C.root' , lumi = 2.64992914),
    'data_Run2016D' : tnpSample('data_Run2016D' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016D.root' , lumi = 4.292865604),
    'data_Run2016E' : tnpSample('data_Run2016E' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016E.root' , lumi = 4.185165152),
    'data_Run2016F' : tnpSample('data_Run2016F' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016F.root' , lumi = 2.725508364),
    }