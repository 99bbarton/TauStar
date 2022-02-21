import json

data = []
lumiMask = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'

data.append({
    'name': 'MET_2018A',
    'inputDataset': '/MET/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD',
    'nFiles': '40',
    'lumiMask': lumiMask,
})

data.append({
    'name': 'MET_2018B',
    'inputDataset': '/MET/Run2018B-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD',
    'nFiles': '22',
    'lumiMask': lumiMask,
})

data.append({
    'name': 'MET_2018C',
    'inputDataset': '/MET/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD',
    'nFiles': '24',
    'lumiMask': lumiMask,
})

data.append({
    'name': 'MET_2018D',
    'inputDataset': '/MET/Run2018D-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD',
    'nFiles': '121',
    'lumiMask': lumiMask,
})

#data['people'].append({
#    'name': 'MET_2018A',
#    'inputDataset': '/MET/Run2018A-UL2018_MiniAODv1_NanoAODv2-v2/NANOAOD',
#    'nFiles': '59',
#    'lumiMask': lumiMask,
#    'year': year,
#})

#data['people'].append({
#    'name': 'MET_2018B',
#    'inputDataset': '/MET/Run2018B-UL2018_MiniAODv1_NanoAODv2-v5/NANOAOD',
#    'nFiles': '19',
#    'lumiMask': lumiMask,
#    'year': year,
#})

#data['people'].append({
#    'name': 'MET_2018C',
#    'inputDataset': '/MET/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
#    'nFiles': '30',
#    'lumiMask': lumiMask,
#    'year': year,
#})

#data['people'].append({
#    'name': 'MET_2018D',
#    'inputDataset': '/MET/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
#    'nFiles': '132',
#    'lumiMask': lumiMask,
#    'year': year,
#})

for entry in data:
    entry['year'] = '2018'
    entry['isMC'] = 'False'
    entry['isSig'] = 'False'

with open('metsamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
