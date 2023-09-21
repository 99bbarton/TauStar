

from ROOT import TH1F, TCanvas, TFile, gStyle, THStack, TLegend, gPad
import os

## -------------------------------------------------------------------------------------------------------------------------------------------------------------------
FILEPATH = os.environ["ROOTURL"] + "/" + os.environ["TSSVFIT"]

def plotSVFit():
    #File names
    years = ["2015", "2016", "2017"]#, "2018"]
    channels = ["ETau", "MuTau", "TauTau"]
    #bkgdFiles = ["DYJetsToLL_M10to50", "DYJetsToLL_M50", "ZGToLLG"]
    bkgdFiles = ["ZGToLLG"]
    #sigFiles = ["Taustar_m175", "Taustar_m250","Taustar_m375","Taustar_m500","Taustar_m625","Taustar_m750","Taustar_m1000","Taustar_m1250","Taustar_m1500","Taustar_m1750","Taustar_m2000","Taustar_m2500","Taustar_m3000","Taustar_m3500","Taustar_m4000","Taustar_m4500","Taustar_m5000"]
    sigFiles = ["Taustar_m175", "Taustar_m250","Taustar_m375","Taustar_m500","Taustar_m625"]

    #Plotting related
    canv = TCanvas("canv", "SVFit Tau Pair Mass", 1000, 800)
    gStyle.SetOptStat(0)
    bkgdColors = [16, 27]
    sigColors = [2, 4, 6, 7, 415, 32, 36, 634]
    leg = TLegend(0.7, 0.6, 0.9, 0.9)

    #Histogram Limits
    nBins = 50
    binMin = 0
    binMax = 500

    hs_bkgd = []
    hs_sig = []
    stack_bkgd = THStack("stack_bkgd", "SVFit Mass;Tau Pair Mass [GeV];Events")
    
    #Background
    print("Getting background...")
    for bkgdFN, bkgdFileBase in enumerate(bkgdFiles):
        hs_bkgd.append(TH1F("h_"+bkgdFileBase, "SVFit Tau Pair Mass; Tau Pair Mass [GeV];Events", nBins, binMin, binMax))
        
        for yearN, year in enumerate(years):
            fil = TFile.Open(FILEPATH + bkgdFileBase+"_"+year+".root", "READ")
            tree = fil.Get("Events")
            
            for ch in channels:
                h_temp = TH1F("h_"+bkgdFileBase+"_"+year+"_"+ch, bkgdFileBase, nBins, binMin, binMax)
                
                cuts = getCuts(year, ch)
                weight = getWeight(ch, isSig=False)
    
                tree.Draw("SVFit_TauPairMass>>+h_"+bkgdFileBase+"_"+year+"_"+ch, cuts + " * " + weight)
                hs_bkgd[bkgdFN].Add(h_temp)
                del h_temp
                #h_bkgd.Add(h_temp)
                print(bkgdFileBase + " hist now has # entries = " + str(hs_bkgd[bkgdFN].GetEntries()))
            fil.Close()
    
        hs_bkgd[bkgdFN].SetLineColor(bkgdColors[bkgdFN])
        hs_bkgd[bkgdFN].SetFillColor(bkgdColors[bkgdFN])
        hs_bkgd[bkgdFN].SetAxisRange(0.1, 30,"Y")
        hs_bkgd[bkgdFN].SetMinimum(0.1)
        stack_bkgd.Add(hs_bkgd[bkgdFN])
        leg.AddEntry(hs_bkgd[bkgdFN],bkgdFileBase, "F")
    
    #Signal
    print("Getting signal...")
    for sigFN, sigFileBase in enumerate(sigFiles):
        hs_sig.append(TH1F("h_"+sigFileBase, sigFileBase, nBins, binMin, binMax))
        
        for yearN, year in enumerate(years):
            fil = TFile.Open(FILEPATH + sigFileBase+"_"+year+".root", "READ")
            tree = fil.Get("Events")
            
            for ch in channels:
                h_temp = TH1F("h_"+sigFileBase+"_"+year+"_"+ch, sigFileBase, nBins, binMin, binMax)

                cuts = getCuts(year, ch)
                weight = getWeight(ch, isSig=True)

                tree.Draw("SVFit_TauPairMass>>+h_"+sigFileBase+"_"+year+"_"+ch, cuts + " * " + weight)
                hs_sig[sigFN].Add(h_temp)
                del h_temp
                print(sigFileBase + " hist now has # entries = " + str(hs_sig[sigFN].GetEntries()))
            fil.Close()
    
        hs_sig[sigFN].SetLineColor(sigColors[sigFN])
        hs_sig[sigFN].SetLineWidth(2)
        hs_sig[sigFN].SetAxisRange(0.1, 30,"Y")
        hs_sig[sigFN].SetMinimum(0.1)
        leg.AddEntry(hs_sig[sigFN], sigFileBase, "L")
    
    print("Plotting...")
    canv.Clear()
    canv.SetLogy(1)
    gPad.SetLeftMargin(0.15)
    if len(hs_bkgd) > 1:
        stack_bkgd.Draw("HIST")
    else:
        hs_bkgd[0].Draw("HIST")
    for hSig in hs_sig:
        hSig.Draw("HIST SAME")
    
    leg.Draw("SAME")
    
    canv.SaveAs("../Plots/svFitMasses.png")
    wait=raw_input("Hit Enter to end...")

## -------------------------------------------------------------------------------------------------------------------------------------------------------------------

#Return the full signal region cuts (except the mass cut) for the given year and channel as a single string
#Also require a valid SVFit result
def getCuts(year, channel):
    cuts = "("
    if channel == "ETau":
        cuts += "ETau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]) && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_qq==-1"
        cuts += "&& nE==1 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Electron_mvaFall17V2Iso_WP90[ETau_EIdx] && !Photon_pixelSeed[ETau_PhotonIdx] && Photon_pt[ETau_PhotonIdx]>=100."
        if year == "2015" or year == "2016":
            cuts += " && (HLT_Ele27_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon175 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=29." 
        elif year == "2017":
            cuts += " && (HLT_Ele32_WPTight_Gsf_L1DoubleEG && Trigger_L1EG && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10)) && Electron_pt[ETau_EIdx]>=34."
        elif year == "2018":
            cuts += " && ( HLT_Ele32_WPTight_Gsf && (ETau_EHasTrigObj>0 && (ETau_EHasTrigObj%10)>0) || HLT_Photon200 && (ETau_EHasTrigObj>=10) ) && Electron_pt[ETau_EIdx]>=34."
    elif channel == "MuTau":
        cuts += "MuTau_HaveTriplet>0 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_qq==-1 && nE==0 && nMu==1 && ZEE_HavePair==0 && ZMuMu_HavePair==0 && Muon_pfIsoId[MuTau_MuIdx]>=4 && Photon_pt[ETau_PhotonIdx]>=100."
        if year == "2015" or year == "2016":
            cuts += " && (MuTau_t2016_0[1] || MuTau_t2016_1[1]) && Muon_pt[MuTau_MuIdx]>=26."
        elif year == "2017":
            cuts += " && MuTau_t2017[1] && Muon_pt[MuTau_MuIdx]>=29."
        elif year == "2018":
            cuts += "&& MuTau_t2018[1] && Muon_pt[MuTau_MuIdx]>=26."
    elif channel == "TauTau":
        cuts += "TauTau_HaveTriplet>0 && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx_esup]) && (16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx_esup]) && TauTau_qq_esup==-1 && Photon_pt[ETau_PhotonIdx]>=75."
        cuts += " && nE==0 && nMu==0 && ZEE_HavePair==0 && ZMuMu_HavePair==0"
        if year == "2015" or year == "2016":
            cuts += " && (TauTau_t2016_0[0] || TauTau_t2016_1[0])"
        elif year == "2017":
            cuts += " && (TauTau_t2017_0[0] || TauTau_t2017_1[0] || TauTau_t2017_2[0])"
        elif year == "2018":
            cuts += " && (TauTau_t2018_0[0] || TauTau_t2018_1[0] || TauTau_t2018_2[0] || TauTau_t2018_3[0])"
    if year == "2015" or year == "2016":
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter"
    elif year == "2017" or year == "2018":
        cuts += "&& Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter"

    cuts += " && SVFit_Valid && SVFit_TauPairMass > 10"
    cuts += ")"
    return cuts

## -------------------------------------------------------------------------------------------------------------------------------------------------------------------

def getWeight(channel, isSig):
    
    weightTag = "("
    
    #crossection
    weightTag += "xsWeight"

    #lumi_13TeV
    weightTag += " * lumiWeight[1]"

    #CMS_pileup
    weightTag += " * puWeight[1]"

    #l1ecal
    weightTag += " * L1PreFiringWeight_ECAL_Nom"

    #PDF reweighting
    if isSig:
        weightTag += " * PDFWeights_varWeightsRMS" #central

    if channel=="MuTau":
        #l1muon
        weightTag += " * L1PreFiringWeight_Muon_Nom"
        
    weightTag += " * (genWeight<0?-1.:+1.)"

    if channel=="ETau":
        #CMS_eff_t_antie1p
        weightTag += " * (ETau_nProng==1 ? ETau_SFTau_e[1] : 1.)"
        #CMS_eff_t_antie3p
        weightTag += " * (ETau_nProng==3 ? ETau_SFTau_e[1] : 1.)"
        #CMS_eff_t_antimu1p
        weightTag += " * (ETau_nProng==1 ? ETau_SFTau_mu[1] : 1.)"
        #CMS_eff_t_antimu3p
        weightTag += " * (ETau_nProng==3 ? ETau_SFTau_mu[1] : 1.)"
        #CMS_eff_t_antijet1p
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_nProng==1) ? ETau_SFTau_jet_tight[1] : 1.)"
        #CMS_eff_t_antijet3p
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && ETau_nProng==3) ? ETau_SFTau_jet_tight[1] : 1.)"
        #CMS_eff_e_reco
        weightTag += " * ETau_SFE_reco[1]"
        #CMS_eff_e_id
        weightTag += " * ETau_SFE_id[1]"
        #CMS_eff_etrigger_data
        weightTag += " * ETau_TriggerEffData[1]"
        #CMS_eff_etrigger_mc
        weightTag += " * (1./ETau_TriggerEffMC[1])"
        #CMS_btag_light
        weightTag += " * JetETau_bTagWeight_light[1]"
        #CMS_btag_light_corr
        #weightTag += " * JetETau_bTagWeight_lightcorr[1]";
        #CMS_btag_heavy
        weightTag += " * JetETau_bTagWeight_bc[1]"
        #CMS_btag_heavy_corr
        #weightTag += " * JetETau_bTagWeight_bccorr[1]";
        #if (haveTriplet) {
        #CMS_eff_g_id
        weightTag += " * ETau_SFPhoton_id[1]"
        #CMS_eff_g_pv
        weightTag += " * ETau_SFPhoton_pv[1]"

    elif channel=="MuTau":
        #CMS_eff_t_antie1p
        weightTag += " * (MuTau_nProng==1 ? MuTau_SFTau_e[1] : 1.)"
        #CMS_eff_t_antie3p
        weightTag += " * (MuTau_nProng==3 ? MuTau_SFTau_e[1] : 1.)"
        #CMS_eff_t_antimu1p
        weightTag += " * (MuTau_nProng==1 ? MuTau_SFTau_mu[1] : 1.)"
        #CMS_eff_t_antimu3p
        weightTag += " * (MuTau_nProng==3 ? MuTau_SFTau_mu[1] : 1.)"
        #CMS_eff_t_antijet1p
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_nProng==1) ? MuTau_SFTau_jet_tight[1] : 1.)"
        #CMS_eff_t_antijet3p
        weightTag += " * (((32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && MuTau_nProng==3) ? MuTau_SFTau_jet_tight[1] : 1.)"
        #CMS_eff_m_reco
        weightTag += " * MuTau_SFMu_reco[1]"
        #CMS_eff_m_id
        weightTag += " * MuTau_SFMu_id[1]"
        #CMS_eff_m_iso
        weightTag += " * MuTau_SFMu_iso[1]"
        #CMS_eff_mtrigger_data
        weightTag += " * MuTau_TriggerEffData[1]"
        #CMS_eff_mtrigger_mc
        weightTag += " * (1./MuTau_TriggerEffMC[1])"
        #CMS_btag_light
        weightTag += " * JetMuTau_bTagWeight_light[1]"
        #CMS_btag_light_corr
        #weightTag += " * JetMuTau_bTagWeight_lightcorr[1]";
        #CMS_btag_heavy
        weightTag += " * JetMuTau_bTagWeight_bc[1]"
        #CMS_btag_heavy_corr
        #weightTag += " * JetMuTau_bTagWeight_bccorr[1]";
        #if (haveTriplet) {
        #CMS_eff_g_id
        weightTag += " * MuTau_SFPhoton_id[1]"
        #CMS_eff_g_csev
        weightTag += " * MuTau_SFPhoton_csev[1]"
        #}
    elif channel=="TauTau":
        #CMS_eff_t_antie1p
        weightTag += " * (TauTau_Tau0nProng==1 ? TauTau_SFTau0_e[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==1 ? TauTau_SFTau1_e[1] : 1.)"
        #CMS_eff_t_antie3p
        weightTag += " * (TauTau_Tau0nProng==3 ? TauTau_SFTau0_e[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==3 ? TauTau_SFTau1_e[1] : 1.)"
        #CMS_eff_t_antimu1p
        weightTag += " * (TauTau_Tau0nProng==1 ? TauTau_SFTau0_mu[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==1 ? TauTau_SFTau1_mu[1] : 1.)"
        #CMS_eff_t_antimu3p
        weightTag += " * (TauTau_Tau0nProng==3 ? TauTau_SFTau0_mu[1] : 1.)"
        weightTag += " * (TauTau_Tau1nProng==3 ? TauTau_SFTau1_mu[1] : 1.)"
        #CMS_eff_t_antijet1p
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==1) ? TauTau_SFTau0_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==1) ? TauTau_SFTau1_jet_medium_pt[1] : 1.)"
        #CMS_eff_t_antijet3p
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==3) ? TauTau_SFTau0_jet_medium_pt[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==3) ? TauTau_SFTau1_jet_medium_pt[1] : 1.)"
        #CMS_eff_tttrigger1p
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==1) ? TauTau_SFTau0_trigger_medium[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==1) ? TauTau_SFTau1_trigger_medium[1] : 1.)"
        #CMS_eff_tttrigger3p
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && TauTau_Tau0nProng==3) ? TauTau_SFTau0_trigger_medium[1] : 1.)"
        weightTag += " * (((16&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TauTau_Tau1nProng==3) ? TauTau_SFTau1_trigger_medium[1] : 1.)"
        #if (haveTriplet) {
        #CMS_eff_g_id
        weightTag += " * TauTau_SFPhoton_id[1]"
        #CMS_eff_g_csev
        weightTag += " * TauTau_SFPhoton_csev[1]"
        #}

    weightTag += ")"

    return weightTag

## -------------------------------------------------------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    plotSVFit()
