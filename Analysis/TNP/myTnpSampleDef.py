from libPython.tnpClassUtils import tnpSample

pogTnpTreePath2018 = "root://cmsxrootd.fnal.gov///store/group/phys_egamma/tnpTuples/tomc/2020-05-20/UL2018/merged/"

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