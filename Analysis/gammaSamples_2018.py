import json

data = []

data.append({
    'name': 'WGToLNuG',
    'inputDataset': '/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '9850083',    
    'nFiles': '16',
    'xs': '489.0',
})

data.append({
    'name': 'ZGToLLG',
    'inputDataset': '/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM',
    'nEvents': '29919798',
    'nFiles': '55',
    'xs': '55.48',
})

data.append({
    'name': 'Taustar_m250_2018',
    'inputDataset': '/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '1',
    'xs': '0.02135'
})

data.append({
    'name': 'Taustar_m1000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'xs': '0.004236'
})

data.append({
    'name': 'Taustar_m2000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m2000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '9',
    'xs': '0.0005328'
})

data.append({
    'name': 'Taustar_m4000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m4000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'xs': '8.056e-06'
})


f = open("gammaSamples_2018.txt", "w")
for entry in data:
    inputDataset_ = entry['inputDataset']
    inputDataset_ = inputDataset_[:len(inputDataset_)-10]
    inputDataset_ = inputDataset_.replace("_", "\_")
    #line = "\\verb|%s| & %s\\\ \n" % (inputDataset_, entry['xs'])
    line = "%s & %s\\\ \n" % (inputDataset_, entry['xs'])
    f.write(line)
f.close()

for entry in data:
    entry['year'] = '2018'
    entry['isMC'] = 'True'
    entry['isSig'] = 'False'

with open('gammaSamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
