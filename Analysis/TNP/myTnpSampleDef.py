from libPython.tnpClassUtils import tnpSample

#Paths to EGamma POG official tag tuples
pogTnpTreePath2018 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/tomc/2020-05-20/UL2018/merged/"
pogTnpTreePath2017 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/tomc/2020-05-20/UL2017/merged/"
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
    'DY_LO'              : tnpSample('DY_LO',
                                       pogTnpTreePath2017 + 'DY_LO.root ',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       pogTnpTreePath2017 + 'DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2017B' : tnpSample('data_Run2017B' , pogTnpTreePath2017 + 'Run2017B.root' , lumi = 4.793961427),
    'data_Run2017C' : tnpSample('data_Run2017C' , pogTnpTreePath2017 + 'Run2017C.root' , lumi = 9.631214821 ),
    'data_Run2017D' : tnpSample('data_Run2017D' , pogTnpTreePath2017 + 'Run2017D.root' , lumi = 4.247682053 ),
    'data_Run2017E' : tnpSample('data_Run2017E' , pogTnpTreePath2017 + 'Run2017E.root' , lumi = 9.313642402 ),
    'data_Run2017F' : tnpSample('data_Run2017F' , pogTnpTreePath2017 + 'Run2017F.root' , lumi = 13.510934811),

    }

UL2016_postVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       pogTnpTreePath2016 + 'DY_LO_L1matched.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_amcatnloext',
                                       pogTnpTreePath2016 + 'DY_NLO_L1matched.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2016F_postVFP' : tnpSample('data_Run2016F_postVFP' , pogTnpTreePath2016 + 'Run2016F_L1merged.root' , lumi = 0.414987426),
    'data_Run2016G' : tnpSample('data_Run2016G' , pogTnpTreePath2016 + 'Run2016G_L1matched.root' , lumi = 7.634508755),
    'data_Run2016H' : tnpSample('data_Run2016H' , pogTnpTreePath2016 + 'Run2016H_L1matched.root' , lumi = 8.802242522),
    }

UL2016_preVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       pogTnpTreePath2015 + 'DY_LO_L1matched.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       pogTnpTreePath2015 + 'DY_NLO_L1matched.root',
                                       isMC = True, nEvts =  -1 ),


    #'data_Run2016B' : tnpSample('data_Run2016B' , pogTnpTreePath2015 + 'UL2016_SingleEle_Run2016B.root' , lumi = 0.030493962),
    'data_Run2016B_ver2' : tnpSample('data_Run2016B_ver2' , pogTnpTreePath2015 + 'Run2016B_L1matched.root' , lumi = 5.879330594),
    'data_Run2016C' : tnpSample('data_Run2016C' , pogTnpTreePath2015 + 'Run2016C_L1matched.root' , lumi = 2.64992914),
    'data_Run2016D' : tnpSample('data_Run2016D' , pogTnpTreePath2015 + 'Run2016D_L1matched.root' , lumi = 4.292865604),
    'data_Run2016E' : tnpSample('data_Run2016E' , pogTnpTreePath2015 + 'Run2016E_L1matched.root' , lumi = 4.185165152),
    'data_Run2016F' : tnpSample('data_Run2016F' , pogTnpTreePath2015 + 'Run2016F_L1matched.root' , lumi = 2.725508364),
    }
