from libPython.tnpClassUtils import tnpSample

#Paths to my tag tuples
myTnpTreePath2018 = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2018/Merged/"
#myTnpTreePath2017 = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/"
myTnpTreePath2017 = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/31Aug22/UL2017/Merged/" #Added HLT_Ele35 L1 seeds
myTnpTreePath2016 = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016postVFP/Merged/"
myTnpTreePath2015 = "root://cmsxrootd.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/"

UL2018 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       myTnpTreePath2018 + 'UL2018_DY_LO.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       myTnpTreePath2018 + 'UL2018_DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2018A' : tnpSample('data_Run2018A' , myTnpTreePath2018 + 'UL2018_runA.root' , lumi = 14.02672485),
    'data_Run2018B' : tnpSample('data_Run2018B' , myTnpTreePath2018 + 'UL2018_runB.root' , lumi = 7.060617355),
    'data_Run2018C' : tnpSample('data_Run2018C' , myTnpTreePath2018 + 'UL2018_runC.root' , lumi = 6.894770971),
    'data_Run2018D' : tnpSample('data_Run2018D' , myTnpTreePath2018 + 'UL2018_runD.root' , lumi = 31.74220577),
    }

UL2017 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       myTnpTreePath2017 + 'UL2017_DY_LO.root ',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       myTnpTreePath2017 + 'UL2017_DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2017B' : tnpSample('data_Run2017B' , myTnpTreePath2017 + 'UL2017_runB.root' , lumi = 4.793961427),
    'data_Run2017C' : tnpSample('data_Run2017C' , myTnpTreePath2017 + 'UL2017_runC.root' , lumi = 9.631214821 ),
    'data_Run2017D' : tnpSample('data_Run2017D' , myTnpTreePath2017 + 'UL2017_runD.root' , lumi = 4.247682053 ),
    'data_Run2017E' : tnpSample('data_Run2017E' , myTnpTreePath2017 + 'UL2017_runE.root' , lumi = 9.313642402 ),
    'data_Run2017F' : tnpSample('data_Run2017F' , myTnpTreePath2017 + 'UL2017_runF.root' , lumi = 13.510934811),

    }

UL2016_postVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       myTnpTreePath2016 + 'UL2016_DY_LO.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_amcatnloext',
                                       myTnpTreePath2016 + 'UL2016_DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    'data_Run2016F_postVFP' : tnpSample('data_Run2016F_postVFP' , myTnpTreePath2016 + 'UL2016_runF.root' , lumi = 0.414987426),
    'data_Run2016G' : tnpSample('data_Run2016G' , myTnpTreePath2016 + 'UL2016_runG.root' , lumi = 7.634508755),
    'data_Run2016H' : tnpSample('data_Run2016H' , myTnpTreePath2016 + 'UL2016_runH.root' , lumi = 8.802242522),
    }

UL2016_preVFP = {
    ### MiniAOD TnP for IDs scale factors
    'DY_LO'              : tnpSample('DY_LO',
                                       myTnpTreePath2015 + 'UL2015_DY_LO.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_NLO'                 : tnpSample('DY_NLO',
                                       myTnpTreePath2015 + 'UL2015_DY_NLO.root',
                                       isMC = True, nEvts =  -1 ),


    #'data_Run2016B' : tnpSample('data_Run2016B' , myTnpTreePath2015 + 'UL2016_SingleEle_Run2016B.root' , lumi = 0.030493962),
    'data_Run2016B' : tnpSample('data_Run2016B' , myTnpTreePath2015 + 'UL2015_runB.root' , lumi = 5.879330594),
    'data_Run2016C' : tnpSample('data_Run2016C' , myTnpTreePath2015 + 'UL2015_runC.root' , lumi = 2.64992914),
    'data_Run2016D' : tnpSample('data_Run2016D' , myTnpTreePath2015 + 'UL2015_runD.root' , lumi = 4.292865604),
    'data_Run2016E' : tnpSample('data_Run2016E' , myTnpTreePath2015 + 'UL2015_runE.root' , lumi = 4.185165152),
    'data_Run2016F' : tnpSample('data_Run2016F' , myTnpTreePath2015 + 'UL2015_runF.root' , lumi = 2.725508364),
    }
