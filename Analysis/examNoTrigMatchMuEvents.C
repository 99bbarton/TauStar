//Look into events with muons where a trigger match is not made


void examNoTrigMatchMuEvents(TString filename, int year, TString channel)
{
    TFile* file = TFile::Open(filename, "READ");
    TTree* tree = (TTree*) file->Get("Events");

    TCut qualityCuts;
    TCut haveTrig;
    TCut matchedTrig;
    TCut notMatchedPassIsoID;
    
    if (year == 2015 || year == 2016)
    {
        if (channel == "MuTau")
        {
            qualityCuts = TCut("MuTau_HavePair && nE==0 && nMu==1 && Muon_tightId[MuTau_MuIdx] && Muon_pfIsoId[MuTau_MuIdx]>=4 && Muon_pt[MuTau_MuIdx]>=26.");
            haveTrig = TCut("(MuTau_t2016_0[0] || MuTau_t2016_1[0])");
            matchedTrig = TCut("(MuTau_t2016_0[0] && MuTau_t2016_0[1]) || (MuTau_t2016_1[0] && MuTau_t2016_1[1])");
            notMatchedPassIsoID = TCut("(Muon_pfIsoId[MuTrig_matchedNonSelMus[0]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[0]]) || (Muon_pfIsoId[MuTrig_matchedNonSelMus[1]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[1]]) || (Muon_pfIsoId[MuTrig_matchedNonSelMus[2]] >=4 && Muon_tightId[MuTrig_matchedNonSelMus[2]]) ");
        }
    }
    cout << "\nExaming events from year= " << year << " and channel= " << channel << endl;
    cout << "\nNum events passing quality cuts = " << tree->GetEntries(qualityCuts) << endl;
    cout << "Num events which have trigs = " << tree->GetEntries(qualityCuts + haveTrig) << endl;
    cout << "Num events which matched trigs = " << tree->GetEntries(qualityCuts + matchedTrig) << endl;


    cout << "\nNow for events where triggers fired but were not matched:" << endl;
    cout << "Events where the muon matching the trigger object has pfIsoId>=4 && tightId>0 = " << tree->GetEntries(notMatchedPassIsoID) << endl;
    tree->Scan("Muon_pfIsoId[MuTrig_matchedNonSelMus[0]]:Muon_tightId[MuTrig_matchedNonSelMus[0]]" , haveTrig + !matchedTrig + qualityCuts + "MuTrig_matchedNonSelMus[0] >=1");
    tree->Scan("Muon_pfIsoId[MuTrig_matchedNonSelMus[1]]:Muon_tightId[MuTrig_matchedNonSelMus[1]]" , haveTrig + !matchedTrig + qualityCuts + "MuTrig_matchedNonSelMus[1] >=1");
    tree->Scan("Muon_pfIsoId[MuTrig_matchedNonSelMus[2]]:Muon_tightId[MuTrig_matchedNonSelMus[2]]" , haveTrig + !matchedTrig + qualityCuts + "MuTrig_matchedNonSelMus[2] >=1");


}