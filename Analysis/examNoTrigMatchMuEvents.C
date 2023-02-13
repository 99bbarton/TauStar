//Look into events with muons where a trigger match is not made


void examNoTrigMatchMuEvents(TString filename, int year, TString channel)
{
    TFile* file = TFile::Open(filename, "READ");
    TTree* tree = (TTree*) file->Get("Events");

    TCut qualityCuts;
    TCut haveTrig;
    TCut matchedTrig;
    TCut notMatchedPassIsoID;
    TCut notMatchedPassIsoID2_0;
    TCut notMatchedPassIsoID2_1;
    TCut noSemiLepbs;
    
    if (year == 2015 || year == 2016)
    {
        if (channel == "MuTau")
        {
            qualityCuts = TCut("MuTau_HavePair && nE==0 && nMu==1 && Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4 && Muon_pt[MuTau_MuIdx]>=26.");
            haveTrig = TCut("(MuTau_t2016_0[0] || MuTau_t2016_1[0])");
            matchedTrig = TCut("(MuTau_t2016_0[0] && MuTau_t2016_0[1]) || (MuTau_t2016_1[0] && MuTau_t2016_1[1])");
            notMatchedPassIsoID = TCut("MuTrig_nMatchedNonSelMus == 1 && (Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]])");
	    notMatchedPassIsoID2_0 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]]");
            notMatchedPassIsoID2_1 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[1]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[1]]");
            noSemiLepbs = TCut("Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_MuTau==1 && JetMask_bL==1)==0");
        }
    }
    if (year == 2017)
    {
        if (channel == "MuTau")
        {
            qualityCuts = TCut("MuTau_HavePair && nE==0 && nMu==1 && Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4 && Muon_pt[MuTau_MuIdx]>=29.");
            haveTrig = TCut("MuTau_t2017[0]");
            matchedTrig = TCut("MuTau_t2017[0] && MuTau_t2017[1]");
            notMatchedPassIsoID = TCut("MuTrig_nMatchedNonSelMus == 1 && (Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]])");
	    notMatchedPassIsoID2_0 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]]");
            notMatchedPassIsoID2_1 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[1]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[1]]");
            noSemiLepbs = TCut("Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_MuTau==1 && JetMask_bL==1)==0");
        }
    }
    if (year == 2018)
    {
         if (channel == "MuTau")
        {
            qualityCuts = TCut("MuTau_HavePair && nE==0 && nMu==1 && Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4 && Muon_pt[MuTau_MuIdx]>=26.");
            haveTrig = TCut("MuTau_t2018[0]");
            matchedTrig = TCut("MuTau_t2018[0] && MuTau_t2018[1]");
            notMatchedPassIsoID = TCut("MuTrig_nMatchedNonSelMus == 1 && (Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]])");
            notMatchedPassIsoID2_0 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]]");
	    notMatchedPassIsoID2_1 = TCut("MuTrig_nMatchedNonSelMus == 2 && Muon_pfIsoId[MuTrig_matchedNonSelMus[1]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[1]]");
            noSemiLepbs = TCut("Sum$(Jet_pt_nom>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && JetMask_MuTau==1 && JetMask_bL==1)==0");
        }
    }


    cout << "\nExaming events from year= " << year << " and channel= " << channel << endl;
    cout << "\nNum events passing quality cuts = " << tree->GetEntries(qualityCuts) << endl;
    cout << "Num events which have trigs = " << tree->GetEntries(qualityCuts + haveTrig) << endl;
    cout << "Num events which matched trigs = " << tree->GetEntries(qualityCuts + matchedTrig) << endl;
    
    cout << "\nNow events where triggers fired but were not matched:" << endl;
    cout << "Events where the muon matching the trigger object has pfIsoId>4 && tightId>0 = " << tree->GetEntries(qualityCuts + notMatchedPassIsoID) << endl;
    cout << "Events where the first of two muons matching the trigger object has pfIsoId>4 && tightId>0 = " << tree->GetEntries(qualityCuts + notMatchedPassIsoID2_0) << endl;
    cout << "Events where the second of two muons matching the trigger object has pfIsoId>4 && tightId>0 = " << tree->GetEntries(qualityCuts + notMatchedPassIsoID2_1) << endl;
    cout << "Further cutting out semi-lep b decays leaves = " << tree->GetEntries(qualityCuts + notMatchedPassIsoID + noSemiLepbs) << endl;

    tree->Scan("Muon_pt[MuTrig_matchedNonSelMus[0]]", qualityCuts+ notMatchedPassIsoID + noSemiLepbs);
    tree->Scan("Muon_pt[MuTau_MuIdx]:Muon_eta[MuTau_MuIdx]:Muon_pt[MuTrig_matchedNonSelMus[0]]:Muon_eta[MuTrig_matchedNonSelMus[0]]", qualityCuts + notMatchedPassIsoID2_0 + noSemiLepbs);
    tree->Scan("Muon_pt[MuTau_MuIdx]:Muon_eta[MuTau_MuIdx]:Muon_pt[MuTrig_matchedNonSelMus[1]]:Muon_eta[MuTrig_matchedNonSelMus[1]]", qualityCuts + notMatchedPassIsoID2_1 + noSemiLepbs);
}
