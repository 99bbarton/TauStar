#Plot photon pT distributions 
# 

import sys
import os
from array import array
from ROOT import TFile, TH1F, TCanvas, TTree, TCut, gStyle, gPad, TLegend, THStack

#---------------------------------------------------------------------------------------------------------

def getDataTree(dataset, year):
    filepath = os.environ["ROOTURL"] + os.environ["TSDATA"] + dataset + "_" + year + ".root"
    fil = TFile.Open(filepath, "READ")
    tree = fil.Get("Events")
    return tree


#---------------------------------------------------------------------------------------------------------


def getSigTree(mass, year):
    filepath = os.environ["ROOTURL"] + os.environ["TSSIGDIR"] + "Taustar_m" + mass + "_" + year + ".root"
    fil = TFile.Open(filepath, "READ")
    tree = fil.Get("Events")
    return tree


#---------------------------------------------------------------------------------------------------------

def getCuts(year, channel, isSig, process=""):
    if year not in ["2015", "2016", "2017", "2018"]:
        print("ERROR: Unrecognized year when getting cuts")

    cuts = "("
    if channel == "ETau":
        cuts += "ETau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]) && ETau_Mass>=100. && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_qq==-1"
        cuts += "&& nE==1 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Electron_mvaFall17V2Iso_WP90[ETau_EIdx] && !Photon_pixelSeed[ETau_PhotonIdx] && Photon_pt[ETau_PhotonIdx]>=20."
        if year == "2015" or year == "2016":
            cuts += " && (HLT_Ele27_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon175 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=29." 
        elif year == "2017":
            cuts += " && (HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=34."
        elif year == "2018":
            cuts += " && ( HLT_Ele32_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10) ) && Electron_pt[ETau_EIdx]>=34."
        if len(process) > 0 or isSig:
            cuts += " && (Tau_genPartFlav[ETau_TauIdx]==5 || (Tau_genPartFlav[ETau_TauIdx]==1||Tau_genPartFlav[ETau_TauIdx]==2||Tau_genPartFlav[ETau_TauIdx]==3||Tau_genPartFlav[ETau_TauIdx]==4))"
            
    elif channel == "MuTau":
        cuts += "MuTau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_qq==-1 && nE==0 && nMu==1 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Muon_pfIsoId[MuTau_MuIdx]>=4 && Photon_pt[MuTau_PhotonIdx]>=20."
        if year == "2015" or year == "2016":
            cuts += " && (MuTau_t2016_0[1] || MuTau_t2016_1[1]) && Muon_pt[MuTau_MuIdx]>=26."
        elif year == "2017":
            cuts += " && MuTau_t2017[1] && Muon_pt[MuTau_MuIdx]>=29."
        elif year == "2018":
            cuts += "&& MuTau_t2018[1] && Muon_pt[MuTau_MuIdx]>=26."
        
        if len(process) > 0 or isSig:
            cuts += " && (Tau_genPartFlav[MuTau_TauIdx]==5 || (Tau_genPartFlav[MuTau_TauIdx]==1||Tau_genPartFlav[MuTau_TauIdx]==2||Tau_genPartFlav[MuTau_TauIdx]==3||Tau_genPartFlav[MuTau_TauIdx]==4))"
    elif channel == "TauTau":
        cuts += "TauTau_HaveTriplet>0 && TauTau_Mass>=100. && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_qq==-1"
        cuts += " && nE==0 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Photon_pt[TauTau_PhotonIdx]>=20."
        if year == "2015" or year == "2016":
            cuts += " && (TauTau_t2016_0[0] || TauTau_t2016_1[0])"
        elif year == "2017":
            cuts += " && (TauTau_t2017_0[0] || TauTau_t2017_1[0] || TauTau_t2017_2[0])"
        elif year == "2018":
            cuts += " && (TauTau_t2018_0[0] || TauTau_t2018_1[0] || TauTau_t2018_2[0] || TauTau_t2018_3[0])"
            
        if len(process) > 0 or isSig:
            tau0_tau = "Tau_genPartFlav[TauTau_Tau0Idx]==5"
            tau1_tau = "Tau_genPartFlav[TauTau_Tau1Idx]==5"
            tau0_lep = "Tau_genPartFlav[TauTau_Tau0Idx]==1||Tau_genPartFlav[TauTau_Tau0Idx]==2||Tau_genPartFlav[TauTau_Tau0Idx]==3||Tau_genPartFlav[TauTau_Tau0Idx]==4"
            tau1_lep = "Tau_genPartFlav[TauTau_Tau1Idx]==1||Tau_genPartFlav[TauTau_Tau1Idx]==2||Tau_genPartFlav[TauTau_Tau1Idx]==3||Tau_genPartFlav[TauTau_Tau1Idx]==4"
            cuts += " && ((" + tau0_tau +" || " + tau0_lep + ") && (" + tau1_tau + "||"+ tau1_lep +"))" 

    elif channel == "EE":
        cuts += "EE_HaveTriplet>0 && Photon_pt[EE_PhotonIdx]>=20. && Photon_mvaID_WP90[EE_PhotonIdx] && !Photon_pixelSeed[EE_PhotonIdx] && ((EE_Mass>=60. && EE_Mass<125.) || (EE_TripletMass>=60. && EE_TripletMass<125.)) && Electron_mvaFall17V2Iso_WP90[EE_E0Idx] && Electron_mvaFall17V2Iso_WP90[EE_E1Idx] && EE_qq==-1 && nE==2 && nMu==0"
        if year == "2015" or year == "2016":
            e0a = "HLT_Ele27_WPTight_Gsf && (EE_E0HasTrigObj>0 && (EE_E0HasTrigObj%10)>0)"
            e0b = "HLT_Photon175 && EE_E0HasTrigObj>=10"
            e1a = "HLT_Ele27_WPTight_Gsf && (EE_E1HasTrigObj>0 && (EE_E1HasTrigObj%10)>0)"
            e1b = "HLT_Photon175 && EE_E1HasTrigObj>=10"
            triggerPath = "((" + e0a + "&&" + e1a + ") || (" + e0a + "&&" + e1b + ") || (" + e0b + "&&" + e1a + ") || (" + e0b + "&&" + e1b + "))"
            cuts += " && " + triggerPath
            cuts += " && Electron_pt[EE_E0Idx]>=29. && Electron_pt[EE_E1Idx]>=29."
        elif year == "2017":
            e0a = "HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (EE_E0HasTrigObj>0 && (EE_E0HasTrigObj%10)>0)"
            e0b = "HLT_Photon200 && EE_E0HasTrigObj>=10"
            e1a = "HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (EE_E1HasTrigObj>0 && (EE_E1HasTrigObj%10)>0)"
            e1b = "HLT_Photon200 && EE_E1HasTrigObj>=10"
            triggerPath = "((" + e0a + "&&" + e1a + ") || (" + e0a + "&&" + e1b + ") || (" + e0b + "&&" + e1a + ") || (" + e0b + "&&" + e1b + "))"
            cuts += " && " + triggerPath
            cuts += " && Electron_pt[EE_E0Idx]>=34. && Electron_pt[EE_E1Idx]>=34."
        elif year == "2018":
            e0a = "HLT_Ele32_WPTight_Gsf && (EE_E0HasTrigObj>0 && (EE_E0HasTrigObj%10)>0)"
            e0b = "HLT_Photon200 && EE_E0HasTrigObj>=10"
            e1a = "HLT_Ele32_WPTight_Gsf && (EE_E1HasTrigObj>0 && (EE_E1HasTrigObj%10)>0)"
            e1b = "HLT_Photon200 && EE_E1HasTrigObj>=10"
            triggerPath = "((" + e0a + "&&" + e1a + ") || (" + e0a + "&&" + e1b + ") || (" + e0b + "&&" + e1a + ") || (" + e0b + "&&" + e1b + "))"
            cuts += " && " + triggerPath
            cuts += " && Electron_pt[EE_E0Idx]>=34. && Electron_pt[EE_E1Idx]>=34."
    elif channel == "MuMu":
        cuts += "MuMu_HaveTriplet>0 && Photon_pt[MuMu_PhotonIdx]>=20. && Photon_mvaID_WP90[MuMu_PhotonIdx] && Photon_electronVeto[MuMu_PhotonIdx] && ((MuMu_Mass>=60. && MuMu_Mass<125.) || (MuMu_TripletMass>=60. && MuMu_TripletMass<125.)) && Muon_tightId[MuMu_Mu0Idx] && Muon_tightId[MuMu_Mu1Idx] && Muon_pfIsoId[MuMu_Mu0Idx]>=4 && Muon_pfIsoId[MuMu_Mu1Idx]>=4 && nE==0 && nMu==2 && MuMu_qq==-1"
        if year == "2015" or year == "2016":
            cuts += " && ((MuMu_Mu0_t2016_0[1] || MuMu_Mu0_t2016_1[1]) && (MuMu_Mu1_t2016_0[1] || MuMu_Mu1_t2016_1[1])) && Muon_pt[MuMu_Mu0Idx]>=26. && Muon_pt[MuMu_Mu1Idx]>=26."
        elif year == "2017":
            cuts += " && MuMu_Mu0_t2017[1] && MuMu_Mu1_t2017[1] && Muon_pt[MuMu_Mu0Idx]>=29. && Muon_pt[MuMu_Mu1Idx]>=29."
        elif year == "2018":
            cuts += " && MuMu_Mu0_t2018[1] && MuMu_Mu1_t2018[1] && Muon_pt[MuMu_Mu0Idx]>=26. && Muon_pt[MuMu_Mu1Idx]>=26."
    elif channel == "EMu":
        cuts += "EMu_HaveTriplet>0 && Photon_pt[EMu_PhotonIdx]>=20. && Photon_mvaID_WP90[EMu_PhotonIdx] && !Photon_pixelSeed[EMu_PhotonIdx] && EMu_Mass>=91.1876 && Muon_tightId[EMu_MuIdx] && nE==1 && nMu==1 && Electron_mvaFall17V2Iso_WP90[EMu_EIdx] && Muon_pfIsoId[EMu_MuIdx]>=4 && EMu_qq==-1"
        if year == "2015" or year == "2016":
            lowMuHighE = "(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=25. && (64&EMu_EMuTrigObjBits)>0"
            highMuLowE = "(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) && Muon_pt[EMu_MuIdx]>=25. && Electron_pt[EMu_EIdx]>=20. && (64&EMu_EMuTrigObjBits)>0"
            singleEE = "HLT_Ele27_WPTight_Gsf && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=29. && EMu_EHasTrigObj>0"
            singleMu = "(EMu_1Mu_t2016_0[1] || EMu_1Mu_t2016_1[1]) && Muon_pt[EMu_MuIdx]>=26. && Electron_pt[EMu_EIdx]>=20."
            cuts += " && (" + lowMuHighE + " || " + highMuLowE + " || " + singleEE + " || " + singleMu + ")"
        elif year == "2017":
            lowMuHighE = "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=25. && (64&EMu_EMuTrigObjBits)>0"
            highMuLowE = "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL && Muon_pt[EMu_MuIdx]>=25. && Electron_pt[EMu_EIdx]>=20. && (64&EMu_EMuTrigObjBits)>0"
            singleEE = "HLT_Ele35_WPTight_Gsf && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=37. && EMu_EHasTrigObj>0"
            singleMu = "EMu_1Mu_t2017[1] && Muon_pt[EMu_MuIdx]>=29. && Electron_pt[EMu_EIdx]>=20."
            cuts += " && (" + lowMuHighE + " || " + highMuLowE + " || " + singleEE + " || " + singleMu + ")"
        elif year == "2018":
            lowMuHighE = "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=25. && (64&EMu_EMuTrigObjBits)"
            highMuLowE = "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL && Muon_pt[EMu_MuIdx]>=25. && Electron_pt[EMu_EIdx]>=20. && (64&EMu_EMuTrigObjBits)"
            singleEE = "HLT_Ele32_WPTight_Gsf && Muon_pt[EMu_MuIdx]>=15. && Electron_pt[EMu_EIdx]>=34. && EMu_EHasTrigObj>0"
            singleMu = "EMu_1Mu_t2018[1] && Muon_pt[EMu_MuIdx]>=26. && Electron_pt[EMu_EIdx]>=20."
            cuts += " && (" + lowMuHighE + " || " + highMuLowE + " || " + singleEE + " || " + singleMu + ")"
    else:
        print("WARNING: Unrecognized channel when getting cuts")

    if isSig and (year == "2015" or year == "2016"):
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter"
    elif isSig and (year == "2017" or year == "2018"):
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter"
    
    #These cuts handle separation of prompt vs non-prompt photons in MC to avoid double counting
    if process == "ZGToLLG_" or process == "WGToLNuG_" or process == "TTGamma_SingleLept_" or process == "TTGamma_Dilept_":
        #print("This is a prompt photon sample")
        cuts += " && Photon_genPartFlav["+channel+"_PhotonIdx]==1"
    elif process == "DYJetsToLL_M50_" or process == "DYJetsToLL_M50_NLO_" or process == "DYJetsToLL_M10to50_" or process == "WJetsToLNu_" or process == "TTToSemiLeptonic_" or process == "TTTo2L2Nu_":
        cuts += " && Photon_genPartFlav["+channel+"_PhotonIdx]!=1"
        #print("This is a non-prompt photon sample")
    elif process not in ["WW_", "WZ_", "ZZ_", "ST_s_channel_", "ST_tW_antitop_", "ST_t_channel_antitop_", "ST_t_channel_top_"] :
        print("ERROR: Unrecognized process (" + process + ") when getting cuts")

    cuts += ")"

    if len(cuts) < 10:
        print("ERROR: Returned cuts are empty")
    return cuts


#Return the proper weighting for the MC sample
def getWeights(channel, isSig):
    weightTag = "(xsWeight * lumiWeight[1] * puWeight[1] * L1PreFiringWeight_ECAL_Nom"

    if isSig:
        weightTag += " * PDFWeights_varWeightsRMS"


    if channel=="EMu" or channel=="MuMu" or channel=="MuTau":
        weightTag += " * L1PreFiringWeight_Muon_Nom"

    weightTag += " * (genWeight<0?-1.:+1.)"

    if channel=="EE":
        weightTag += " * EE_SFE0_reco[1] * EE_SFE1_reco[1]"
        weightTag += " * EE_SFE0_id[1] * EE_SFE1_id[1]"
        weightTag += " * EE_TriggerEffData[1]"
        weightTag += " * (1./EE_TriggerEffMC[1])"
        weightTag += " * EE_SFPhoton_id[1]"
        weightTag += " * EE_SFPhoton_pv[1]"
    elif channel=="MuMu":
        weightTag += " * MuMu_SFMu0_reco[1] * MuMu_SFMu1_reco[1]"
        weightTag += " * MuMu_SFMu0_id[1] * MuMu_SFMu1_id[1]"
        weightTag += " * MuMu_SFMu0_iso[1] * MuMu_SFMu1_iso[1]"
        weightTag += " * MuMu_TriggerEffData[1]"
        weightTag += " * (1./MuMu_TriggerEffMC[1])"
        weightTag += " * MuMu_SFPhoton_id[1]"
        weightTag += " * MuMu_SFPhoton_csev[1]"
    elif channel=="EMu":
        weightTag += " * EMu_SFE_reco[1]"
        weightTag += " * EMu_SFE_id[1]"
        weightTag += " * EMu_SFMu_reco[1]"
        weightTag += " * EMu_SFMu_id[1]"
        weightTag += " * EMu_SFMu_iso[1]"
        weightTag += " * EMu_SFEMu_trigger[1]"
        weightTag += " * EMu_SFPhoton_id[1]"
        weightTag += " * EMu_SFPhoton_pv[1]"
    elif channel=="ETau":
        weightTag += " * (ETau_nProng==1 ? ETau_SFTau_e[1] : 1.)"
        weightTag += " * (ETau_nProng==3 ? ETau_SFTau_e[1] : 1.)"
        weightTag += " * (ETau_nProng==1 ? ETau_SFTau_mu[1] : 1.)"
        weightTag += " * (ETau_nProng==3 ? ETau_SFTau_mu[1] : 1.)"
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_nProng==1) ? ETau_SFTau_jet_tight[1] : 1.)"
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_nProng==3) ? ETau_SFTau_jet_tight[1] : 1.)"
        weightTag += " * ETau_SFE_reco[1]"
        weightTag += " * ETau_SFE_id[1]"
        weightTag += " * ETau_TriggerEffData[1]"
        weightTag += " * (1./ETau_TriggerEffMC[1])"
        weightTag += " * JetETau_bTagWeight_light[1]"
        weightTag += " * JetETau_bTagWeight_lightcorr[1]"
        weightTag += " * JetETau_bTagWeight_bc[1]"
        weightTag += " * JetETau_bTagWeight_bccorr[1]"
        weightTag += " * ETau_SFPhoton_id[1]"
        weightTag += " * ETau_SFPhoton_pv[1]"
    elif channel=="MuTau":
        weightTag += " * (MuTau_nProng==1 ? MuTau_SFTau_e[1] : 1.)"
        weightTag += " * (MuTau_nProng==3 ? MuTau_SFTau_e[1] : 1.)"
        weightTag += " * (MuTau_nProng==1 ? MuTau_SFTau_mu[1] : 1.)"
        weightTag += " * (MuTau_nProng==3 ? MuTau_SFTau_mu[1] : 1.)"
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_nProng==1) ? MuTau_SFTau_jet_tight[1] : 1.)"
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_nProng==3) ? MuTau_SFTau_jet_tight[1] : 1.)"
        weightTag += " * MuTau_SFMu_reco[1]"
        weightTag += " * MuTau_SFMu_id[1]"
        weightTag += " * MuTau_SFMu_iso[1]"
        weightTag += " * MuTau_TriggerEffData[1]"
        weightTag += " * (1./MuTau_TriggerEffMC[1])"
        weightTag += " * JetMuTau_bTagWeight_light[1]"
        weightTag += " * JetMuTau_bTagWeight_lightcorr[1]"
        weightTag += " * JetMuTau_bTagWeight_bc[1]"
        weightTag += " * JetMuTau_bTagWeight_bccorr[1]"
        weightTag += " * MuTau_SFPhoton_id[1]"
        weightTag += " * MuTau_SFPhoton_csev[1]"
    if channel=="TauTau":
        weightTag += " * (TauTau_Tau0nProng==1 ? TauTau_SFTau0_e[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==1 ? TauTau_SFTau1_e[1] : 1.)"
        weightTag += " * (TauTau_Tau0nProng==3 ? TauTau_SFTau0_e[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==3 ? TauTau_SFTau1_e[1] : 1.)"
        weightTag += " * (TauTau_Tau0nProng==1 ? TauTau_SFTau0_mu[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==1 ? TauTau_SFTau1_mu[1] : 1.)"
        weightTag += " * (TauTau_Tau0nProng==3 ? TauTau_SFTau0_mu[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==3 ? TauTau_SFTau1_mu[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==1) ? TauTau_SFTau0_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==1) ? TauTau_SFTau1_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==3) ? TauTau_SFTau0_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==3) ? TauTau_SFTau1_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==1) ? TauTau_SFTau0_trigger_medium[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==1) ? TauTau_SFTau1_trigger_medium[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==3) ? TauTau_SFTau0_trigger_medium[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==3) ? TauTau_SFTau1_trigger_medium[1] : 1.)"
        weightTag += " * TauTau_SFPhoton_id[1]"
        weightTag += " * TauTau_SFPhoton_csev[1]"

    weightTag += ")"
    return weightTag

    #---------------------------------------------------------------------------------------------------------

def plotAllSig():
    OUTPATH = "../Plots/PhotonPt/Normalized/"
    canv = TCanvas("canv_phoPt_sig", "Signal MC Photon pT Distributions", 800, 600)
    #leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")
    gStyle.SetOptStat(0)
    
    ptBins = array("f", [20, 75, 100, 200, 500, 1000, 2000, 3000, 4000, 5000])
    nBins = len(ptBins) - 1

    useLeftLeg = False

    for mass in ["175","250","375","500","625","750","1000","1250","1500","1750","2000","2500","3000","3500","4000","4500","5000"]:
        print("Plotting pho pT for m=" + mass + "...")

        h_ETau = TH1F("h_ETau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
        h_MuTau = TH1F("h_MuTau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
        h_TauTau = TH1F("h_TauTau_m" + mass, "Photon pT: m" + mass + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)

        if mass == "2000":
            useLeftLeg = True
            
        for year in ["2015", "2016", "2017", "2018"]:

            filepath = os.environ["ROOTURL"] + os.environ["TSSIGDIR"] + "Taustar_m" + mass + "_" + year + ".root"
            fil = TFile.Open(filepath, "READ")
            tree = fil.Get("Events")

            histNames = ["h_ETau_m" + mass + "_" + year, "h_MuTau_m" + mass + "_" + year, "h_TauTau_m" + mass + "_" + year]
            h_ETau_yr = TH1F(histNames[0], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_MuTau_yr = TH1F(histNames[1], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_TauTau_yr = TH1F(histNames[2], "Photon pT: m" + mass + " " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            
            tree.Draw("Photon_pt[ETau_PhotonIdx]>>+" + histNames[0], getCuts(year=year, channel="ETau", isSig=True))
            tree.Draw("Photon_pt[MuTau_PhotonIdx]>>+" + histNames[1], getCuts(year=year, channel="MuTau", isSig=True))
            tree.Draw("Photon_pt[TauTau_PhotonIdx]>>+" + histNames[2], getCuts(year=year, channel="TauTau", isSig=True))


            if year == "2015":
                lumiFrac = 19.7 / 137.8
            elif year == "2016":
                lumiFrac = 16.9 / 137.8
            elif year == "2017": 
                lumiFrac = 41.5 / 137.8
            elif year == "2018":
                lumiFrac = 59.7 / 137.8

            h_ETau.Add(h_ETau_yr, lumiFrac)
            h_MuTau.Add(h_MuTau_yr, lumiFrac)
            h_TauTau.Add(h_TauTau_yr, lumiFrac)

            h_ETau_yr.Scale(1.0 / h_ETau_yr.GetEntries())
            h_MuTau_yr.Scale(1.0 / h_MuTau_yr.GetEntries())
            h_TauTau_yr.Scale(1.0 / h_TauTau_yr.GetEntries())

            h_ETau_yr.SetLineColor(12)
            h_MuTau_yr.SetLineColor(9)
            h_TauTau_yr.SetLineColor(46)
            h_ETau_yr.SetLineWidth(3)
            h_MuTau_yr.SetLineWidth(3)
            h_TauTau_yr.SetLineWidth(3)

            canv.cd()
            canv.Clear()
            canv.SetLogx(1)

            max_ETau = h_ETau_yr.GetMaximum()
            max_MuTau = h_MuTau_yr.GetMaximum()
            max_TauTau = h_TauTau_yr.GetMaximum()
            if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
                h_ETau_yr.Draw("hist")
                h_MuTau_yr.Draw("hist same")
                h_TauTau_yr.Draw("hist same")
            elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
                h_MuTau_yr.Draw("hist")
                h_ETau_yr.Draw("hist same")
                h_TauTau_yr.Draw("hist same")
            else:
                h_TauTau_yr.Draw("hist")
                h_MuTau_yr.Draw("hist same")
                h_ETau_yr.Draw("hist same")
            
            if useLeftLeg:
                leg = TLegend(0.15, 0.7, 0.35, 0.9, "Channels")
            else:
                leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")

            leg.AddEntry(h_ETau_yr, "ETau", "l")
            leg.AddEntry(h_MuTau_yr, "MuTau", "l")
            leg.AddEntry(h_TauTau_yr, "TauTau", "l")
            leg.Draw()
            
            canv.Update()
            canv.SaveAs(OUTPATH + "phoPt_m" + mass + "_" + year + ".png")
            
            fil.Close()
        
        h_ETau.Scale(1.0 / h_ETau.GetEntries())
        h_MuTau.Scale(1.0 / h_MuTau.GetEntries())
        h_TauTau.Scale(1.0 / h_TauTau.GetEntries())

        h_ETau.SetLineColor(12)
        h_MuTau.SetLineColor(9)
        h_TauTau.SetLineColor(46)
        h_ETau.SetLineWidth(3)
        h_MuTau.SetLineWidth(3)
        h_TauTau.SetLineWidth(3)

        canv.cd()
        canv.Clear()
        canv.SetLogx(1)

        max_ETau = h_ETau.GetMaximum()
        max_MuTau = h_MuTau.GetMaximum()
        max_TauTau = h_TauTau.GetMaximum()
        if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
            h_ETau.Draw("hist")
            h_MuTau.Draw("hist same")
            h_TauTau.Draw("hist same")
        elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
            h_MuTau.Draw("hist")
            h_ETau.Draw("hist same")
            h_TauTau.Draw("hist same")
        else:
            h_TauTau.Draw("hist")
            h_MuTau.Draw("hist same")
            h_ETau.Draw("hist same")

        leg.Clear()
            
        leg.AddEntry(h_ETau, "ETau", "l")
        leg.AddEntry(h_MuTau, "MuTau", "l")
        leg.AddEntry(h_TauTau, "TauTau", "l")
        leg.Draw()
        canv.Update()
        canv.SaveAs(OUTPATH + "phoPt_m" + mass + ".png")

#---------------------------------------------------------------------------------------------------------

def plotAllData(frac=False):
    OUTPATH = "../Plots/PhotonPt/Normalized/Data/"

    canv = TCanvas("canv_phoPt_data", "Observed Photon pT Distributions", 800, 600)
    #leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")
    gStyle.SetOptStat(0)
    colors = [595, 602, 434]
    

    ptBins = array("f", [20, 75, 100, 500, 1000])
    nBins = len(ptBins) - 1

    if not frac:
        stack_all = THStack("hs_all", "Observed Photon pT;pT [GeV];Events / bin")
        h_ETau_all = TH1F("h_ETau", "Observed Photon pT;pT [GeV];Events / bin", nBins, ptBins)
        h_MuTau_all = TH1F("h_MuTau", "Observed Photon pT;pT [GeV];Events / bin", nBins, ptBins)
        h_TauTau_all = TH1F("h_TauTau", "Observed Photon pT;pT [GeV];Events / bin", nBins, ptBins)

    for year in ["2015", "2016", "2017", "2018"]:
        print("Plotting pho pT for year= " + year + "...")

        if frac:
            h_ETau = TH1F("h_ETau_" + year, "Photon pT: " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_MuTau = TH1F("h_MuTau_" + year, "Photon pT: " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_TauTau = TH1F("h_TauTau_" + year, "Photon pT: " + year + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
        else:
            h_ETau = TH1F("h_ETau_" + year, "Photon pT: " + year + ";pT [GeV];Events / bin", nBins, ptBins)
            h_MuTau = TH1F("h_MuTau_" + year, "Photon pT: " + year + ";pT [GeV];Events / bin", nBins, ptBins)
            h_TauTau = TH1F("h_TauTau_" + year, "Photon pT: " + year + ";pT [GeV];Events / bin", nBins, ptBins)

        for dataset in ["Electron", "SingleMuon", "Tau"]:
            filepath = os.environ["ROOTURL"] + os.environ["TSDATA"] + dataset + "_" + year + ".root"
            fil = TFile.Open(filepath, "READ")
            tree = fil.Get("Events")

            histNames = ["h_ETau_" + year + "_" + dataset, "h_MuTau_" + year + "_" + dataset, "h_TauTau_" + year + "_" + dataset]
            h_ETau_ds = TH1F(histNames[0], "Photon pT: " + year + " " + dataset + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_MuTau_ds = TH1F(histNames[1], "Photon pT: " + year + " " + dataset + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            h_TauTau_ds = TH1F(histNames[2], "Photon pT: " + year + " " + dataset + ";pT [GeV];Fraction of Events / bin", nBins, ptBins)
            
            tree.Draw("Photon_pt[ETau_PhotonIdx]>>+" + histNames[0], getCuts(year=year, channel="ETau", isSig=False))
            tree.Draw("Photon_pt[MuTau_PhotonIdx]>>+" + histNames[1], getCuts(year=year, channel="MuTau", isSig=False))
            tree.Draw("Photon_pt[TauTau_PhotonIdx]>>+" + histNames[2], getCuts(year=year, channel="TauTau", isSig=False))

            h_ETau.Add(h_ETau_ds)
            h_MuTau.Add(h_MuTau_ds)
            h_TauTau.Add(h_TauTau_ds)

            if frac:
                h_ETau_ds.Scale(1.0 / h_ETau_ds.GetEntries())
                h_MuTau_ds.Scale(1.0 / h_MuTau_ds.GetEntries())
                h_TauTau_ds.Scale(1.0 / h_TauTau_ds.GetEntries())

            h_ETau_ds.SetLineColor(colors[0])
            h_MuTau_ds.SetLineColor(colors[1])
            h_TauTau_ds.SetLineColor(colors[2])
            h_ETau_ds.SetFillColor(colors[0])
            h_MuTau_ds.SetFillColor(colors[1])
            h_TauTau_ds.SetFillColor(colors[2])
            #h_ETau_ds.SetLineWidth(10)
            #h_MuTau_ds.SetLineWidth(10)
            #h_TauTau_ds.SetLineWidth(10)

            canv.cd()
            canv.Clear()
            canv.SetLogy(1)

            if frac:
                max_ETau = h_ETau_ds.GetMaximum()
                max_MuTau = h_MuTau_ds.GetMaximum()
                max_TauTau = h_TauTau_ds.GetMaximum()
                if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
                    h_ETau_ds.Draw("hist")
                    h_MuTau_ds.Draw("hist same")
                    h_TauTau_ds.Draw("hist same")
                elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
                    h_MuTau_ds.Draw("hist")
                    h_ETau_ds.Draw("hist same")
                    h_TauTau_ds.Draw("hist same")
                else:
                    h_TauTau_ds.Draw("hist")
                    h_MuTau_ds.Draw("hist same")
                    h_ETau_ds.Draw("hist same")
                
            leg = TLegend(0.7, 0.7, 0.9, 0.9, "Channels")

            if frac:
                leg.AddEntry(h_ETau_ds, "ETau", "l")
                leg.AddEntry(h_MuTau_ds, "MuTau", "l")
                leg.AddEntry(h_TauTau_ds, "TauTau", "l")
                
            leg.Draw()
            
            canv.Update()
            canv.SaveAs(OUTPATH + "phoPt_" + year + "_" + dataset + ".png")
            
            fil.Close()
            #End datset

        h_ETau.SetLineColor(colors[0])
        h_MuTau.SetLineColor(colors[1])
        h_TauTau.SetLineColor(colors[2])
        h_ETau.SetFillColor(colors[0])
        h_MuTau.SetFillColor(colors[1])
        h_TauTau.SetFillColor(colors[2])
        #h_ETau.SetLineWidth(10)
        #h_MuTau.SetLineWidth(10)
        #h_TauTau.SetLineWidth(10)

        if frac:
            h_ETau.Scale(1.0 / h_ETau.GetEntries())
            h_MuTau.Scale(1.0 / h_MuTau.GetEntries())
            h_TauTau.Scale(1.0 / h_TauTau.GetEntries())
        else:
            h_ETau_all.Add(h_ETau)
            h_MuTau_all.Add(h_MuTau)
            h_TauTau_all.Add(h_TauTau)

        canv.cd()
        canv.Clear()
        canv.SetLogy(1)
        
        if frac:
            canv.SetLogx(1)

            max_ETau = h_ETau.GetMaximum()
            max_MuTau = h_MuTau.GetMaximum()
            max_TauTau = h_TauTau.GetMaximum()
            if max_ETau >= max_MuTau and max_ETau >= max_TauTau:
                h_ETau.Draw("hist")
                h_MuTau.Draw("hist same")
                h_TauTau.Draw("hist same")
            elif max_MuTau >= max_ETau and max_MuTau >= max_TauTau:
                h_MuTau.Draw("hist")
                h_ETau.Draw("hist same")
                h_TauTau.Draw("hist same")
            else:
                h_TauTau.Draw("hist")
                h_MuTau.Draw("hist same")
                h_ETau.Draw("hist same")
        else:
            stack_yr = THStack("stack_"+year," Observed Photon pT: " + year + ";pT [GeV];Events / bin")
            stack_yr.Add(h_ETau)
            stack_yr.Add(h_MuTau)
            stack_yr.Add(h_TauTau)
            stack_yr.Draw("hist")

        leg.Clear()
        leg.AddEntry(h_ETau, "ETau", "F")
        leg.AddEntry(h_MuTau, "MuTau", "F")
        leg.AddEntry(h_TauTau, "TauTau", "F")
        leg.Draw()
        canv.Update()
        if frac:
            canv.SaveAs(OUTPATH + "phoPt_" + year + "frac.png")
        else:
            canv.SaveAs(OUTPATH + "phoPt_" + year + ".png")
        #End year

    if not frac:
        h_ETau_all.SetLineColor(colors[0])
        h_MuTau_all.SetLineColor(colors[1])
        h_TauTau_all.SetLineColor(colors[2])
        h_ETau_all.SetFillColor(colors[0])
        h_MuTau_all.SetFillColor(colors[1])
        h_TauTau_all.SetFillColor(colors[2])

        canv.Clear()
        canv.SetLogy(1)
        stack_all.Add(h_ETau_all)
        stack_all.Add(h_MuTau_all)
        stack_all.Add(h_TauTau_all)
        stack_all.Draw("hist")
        leg.Draw()
        canv.Update()
        canv.SaveAs(OUTPATH + "phoPt_all.png")



#Plot data and MC phton pT distributions for the six channels of the analysis
def plotDataMCAgreement():

    #Graphics settings
    canv = TCanvas("canvData_MC", "Data MC Agreement", 1800, 1000)
    gStyle.SetOptStat(0)
    colors = [884, 874, 876, 890, 855, 852, 867, 835, 844, 419, 413]
    leg = TLegend(0.7, 0.7, 0.9, 0.9)
    leg.SetNColumns(1)
    leg.SetTextSize(0.04)
    legDict = {} # Keep track of processes which are included in the legend to avoid duplication

    #What to plot
    #channels = ["EE", "MuMu", "EMu", "ETau", "MuTau", "TauTau"]
    channels = ["EE", "EMu", "MuMu"]
    #channels = ["EE"]
    years = ["2015", "2016", "2017", "2018"]
    #years = ["2018"]
    #backgrounds = {"DB" : ["WW_", "WZ_", "ZZ_"]}
    backgrounds = {"DY" : ["DYJetsToLL_M50_", "DYJetsToLL_M50_NLO_", "ZGToLLG_"], "DB" : ["WW_", "WZ_", "ZZ_"], "TT" : ["TTTo2L2Nu_", "TTToSemiLeptonic_", "TTGamma_Dilept_", "TTGamma_SingleLept_"], "ST" : ["ST_s_channel_", "ST_tW_antitop_", "ST_t_channel_antitop_", "ST_t_channel_top_"], "WJ" : ["WJetsToLNu_", "WGToLNuG_"]}
    chToDatasets = {"ETau":"Electron", "MuTau":"SingleMuon", "TauTau":"Tau", "EE":"Electron", "MuMu":"SingleMuon", "EMu":"EMu"}
    
    binLowEdges = [20, 35, 50, 75, 100, 200, 500, 1000]

    hs_bkgds = []
    hs_bkgdTot = []
    hs_data = []
    for channel in channels:
        print("Processing channel = " + channel)

        hs_bkgds.append(THStack("h_bkgds_"+channel, channel + ";Photon pT [GeV];Events"))
        hs_bkgdTot.append(TH1F("h_bkgdTot_"+channel, channel + ";Photon pT [GeV];Events", len(binLowEdges)-1 , array("f",binLowEdges)))
        hs_data.append(TH1F("h_data_"+channel, channel + ";Photon pT [GeV];Events", len(binLowEdges)-1 , array("f",binLowEdges)))
        
        #Get background events
        colN = 0
        for bkgd in backgrounds.keys():
            fileBaseList = backgrounds[bkgd]
            print("\tProcessing backgrounds of type = " + bkgd)
            h_bkgd = TH1F("h_"+channel+"_"+bkgd, channel + ";Photon pT [GeV];Events", len(binLowEdges)-1 , array("f",binLowEdges))
            colN += 1

            for fileBase in fileBaseList:
                for year in years:
                    print("\t\tProcessing file = " + fileBase + year + ".root")
                    filepath = os.environ["ROOTURL"] + os.environ["TSMC"] +"/"+ fileBase + year + ".root"
                    inFile = TFile.Open(filepath, "READ")
                    tree = inFile.Get("Events")
                    
                    h_temp = TH1F("h_temp", "", len(binLowEdges)-1 , array("f",binLowEdges))
                    cutsWeights = "(" + getCuts(year=year, channel=channel, isSig=False, process=fileBase) + ") * " + getWeights(channel=channel, isSig=False)
                    tree.Draw("Photon_pt[" + channel + "_PhotonIdx]>>+h_temp", cutsWeights)
                    h_bkgd.Add(h_temp)

                    del h_temp
                    inFile.Close()
                #End years
            #End background sub-type  
            h_bkgd.SetLineColor(colors[colN])
            h_bkgd.SetFillColor(colors[colN])

            hs_bkgds[-1].Add(h_bkgd)
            hs_bkgdTot[-1].Add(h_bkgd)
            if bkgd not in legDict.keys():
                leg.AddEntry(h_bkgd, bkgd, "F")
                legDict[bkgd] = True
        #END backgrounds

        #Now get data events
        dataset = chToDatasets[channel]
        print("\tProcessing data from " + dataset)

        for year in years:
            print("\t\tProcessing file = " + dataset+"_"+year+".root")
            filepath = os.environ["ROOTURL"] + os.environ["TSDATA"] + dataset + "_" + year + ".root"
            fil = TFile.Open(filepath, "READ")
            tree = fil.Get("Events")

            h_temp = TH1F("h_temp", "", len(binLowEdges)-1 , array("f",binLowEdges))
            tree.Draw("Photon_pt[" + channel + "_PhotonIdx]>>+h_temp", getCuts(year=year, channel=channel, isSig=False))
            hs_data[-1].Add(h_temp)
            del h_temp
                
            fil.Close()

        hs_data[-1].SetLineWidth(3)
        hs_data[-1].SetLineColor(1)
        hs_data[-1].SetMarkerStyle(8)
        hs_data[-1].SetMarkerSize(1)
        
        if "Data" not in legDict.keys():
            leg.AddEntry(hs_data[-1], "Data", "LP")
            legDict["Data"] = True

        #End data retrieval
    #End data collection
    
    #Plot the data
    canv.Divide(3,len(channels)/3)
    for chN in range(len(channels)):
        canv.cd(chN + 1)
        gPad.SetLogy(1)
        hs_bkgds[chN].Draw("HIST")
        hs_data[chN].Draw("SAME P")
        #hs_bkgds[chN].Draw("SAME HIST")
        leg.Draw()

    resp = raw_input("Hit ENTER to save and close plots... ")
    canv.SaveAs("../Plots/PhotonPt/phoPt_DataMC.png")
    canv.SaveAs("../Plots/PhotonPt/phoPt_DataMC.pdf")



if __name__ == "__main__":
#    plotAllSig()
#    plotAllData(frac=True)
    #plotAllData(frac=False)
    plotDataMCAgreement()



