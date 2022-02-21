import json

data = []

data.append({
    'name': 'DYJetsToLL_M10to50',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '94452816',
    'nFiles': '84',
    'xs': '18610.',
})

data.append({
    'name': 'DYJetsToLL_M50',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '197649078', #96233328
    'nFiles': '71',
    'xs': '6077.22',
})

data.append({
    'name': 'DY1JetsToLL_M50',
    'inputDataset': '/DY1JetsToLL_M-50_MatchEWPDG20_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '60368985',
    'nFiles': '40',
    'xs': '1112.14',
})

data.append({
    'name': 'DY2JetsToLL_M50',
    'inputDataset': '/DY2JetsToLL_M-50_MatchEWPDG20_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '27361997',
    'nFiles': '27',
    'xs': '344.987',
}) 

data.append({
    'name': 'DY4JetsToLL_M50',
    'inputDataset': '/DY4JetsToLL_M-50_MatchEWPDG20_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '8522042',
    'nFiles': '16',
    'xs': '48.8496',
})

data.append({
    'name': 'TTToSemiLeptonic',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '476408000',
    'nFiles': '391',
    'xs': '365.34',
})

data.append({
    'name': 'TTTo2L2Nu',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',    
    'nEvents': '145020000',
    'nFiles' : '155',
    'xs': '87.31',
})

data.append({
    'name': 'ST_tW_antitop',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '10949620',
    'nFiles': '16',
    'xs': '19.02828375',
})

data.append({
    'name': 'ST_tW_top',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',    
    'nEvents': '11270430',
    'nFiles': '15',
    'xs': '19.02828375',
})

data.append({
    'name' : 'ST_s_channel',
    'inputDataset': '/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '19365999',
    'nFiles': '19',
    'xs': '3.549',
})

data.append({
    'name' : 'ST_t_channel',
    'inputDataset': '/ST_t-channel_tauDecays_TuneCP5_13TeV-comphep-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '1563511',
    'nFiles': '4',
    'xs': '23.5633333333',
})

data.append({
    'name': 'WW',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '15679000',
    'nFiles' : '31',
    'xs': '118.70838',
})

data.append({
    'name': 'WZ',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '7940000',
    'nFiles': '16',
    'xs': '47.13',
})

data.append({
    'name': 'ZZ',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '3907000',
    'nFiles': '3',
    'xs': '16.523',
})

data.append({
   'name' : 'WJetsToLNu',
   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
   'nEvents': '81051269',
   'nFiles': '94',
   'xs': '61526.7',
})

data.append({
   'name' : 'W1JetsToLNu',
   'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
   'nEvents': '47863225',
   'nFiles': '62',
   'xs': '10432.3',
})

data.append({
   'name' : 'W2JetsToLNu',
   'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
   'nEvents': '27411802',
   'nFiles': '44',
   'xs': '3191.76',
})

data.append({
    'name' : 'W3JetsToLNu',
    'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM', 
    'nEvents': '18297679',
    'nFiles': '35',
    'xs': '948.761',
})

data.append({
   'name' : 'W4JetsToLNu',
   'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v2/NANOAODSIM',
   'nEvents': '9022815',
   'nFiles': '51',
   'xs': '448.896',
})




for entry in data:
    entry['year'] = '2018'
    entry['isMC'] = 'True'
    entry['isSig'] = 'False'

with open('mcsamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
