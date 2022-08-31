
void printTagPtMaxes()
{
  //2018
  TFile* file2018A = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2018/Merged/UL2018_runA.root", "READ");
  TFile* file2018B = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2018/Merged/UL2018_runB.root", "READ");
  TFile* file2018C = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2018/Merged/UL2018_runC.root", "READ");
  TFile* file2018D = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2018/Merged/UL2018_runD.root", "READ");

  TTree* tree2018A = (TTree*) file2018A->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2018B = (TTree*) file2018B->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2018C = (TTree*) file2018C->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2018D = (TTree*) file2018D->Get("tnpPhoIDs/fitter_tree");

  cout << "2018A photon eT max = " << tree2018A->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2018B photon eT max = " << tree2018B->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2018C photon eT max = " << tree2018C->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2018D photon eT max = " << tree2018D->GetMaximum("ph_sc_et") << " GeV" << endl;


  //2017
  TFile* file2017B = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/UL2017_runB.ROOT", "READ");
  TFile* file2017C = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/UL2017_runC.root", "READ");
  TFile* file2017D = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/UL2017_runD.root", "READ");
  TFile* file2017E = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/UL2017_runE.root", "READ");
  TFile* file2017F = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2017/Merged/UL2017_runF.ROOT", "READ");

    
  TTree* tree2017B = (TTree*) file2017B->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2017C = (TTree*) file2017C->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2017D = (TTree*) file2017D->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2017E = (TTree*) file2017E->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2017F = (TTree*) file2017F->Get("tnpPhoIDs/fitter_tree");

  cout << "2017B photon eT max = " << tree2017B->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2017C photon eT max = " << tree2017C->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2017D photon eT max = " << tree2017D->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2017E photon eT max = " << tree2017E->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2017F photon eT max = " << tree2017F->GetMaximum("ph_sc_et") << " GeV" << endl;


  //2016
  TFile* file2016F = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016postVFP/Merged/UL2016_runF.ROOT", "READ");
  TFile* file2016G = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016postVFP/Merged/UL2016_runG.root", "READ");
  TFile* file2016H = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016postVFP/Merged/UL2016_runH.root", "READ");

  TTree* tree2016F = (TTree*) file2016F->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2016G = (TTree*) file2016G->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2016H = (TTree*) file2016H->Get("tnpPhoIDs/fitter_tree");

  cout << "2016F photon eT max = " << tree2016F->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2016G photon eT max = " << tree2016G->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2016H photon eT max = " << tree2016H->GetMaximum("ph_sc_et") << " GeV" << endl;

  //2015
  TFile* file2015B = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/UL2015_runB.root", "READ");
  TFile* file2015C = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/UL2015_runC.root", "READ");
  TFile* file2015D = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/UL2015_runD.root", "READ");
  TFile* file2015E = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/UL2015_runE.root", "READ");
  TFile* file2015F = TFile::Open("root://cmseos.fnal.gov//store/user/bbarton/TrigEffStudies/TNP_TagTuples/UL2016preVFP/Merged/UL2015_runF.root", "READ");

    
  TTree* tree2015B = (TTree*) file2015B->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2015C = (TTree*) file2015C->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2015D = (TTree*) file2015D->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2015E = (TTree*) file2015E->Get("tnpPhoIDs/fitter_tree");
  TTree* tree2015F = (TTree*) file2015F->Get("tnpPhoIDs/fitter_tree");

  cout << "2015B photon eT max = " << tree2015B->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2015C photon eT max = " << tree2015C->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2015D photon eT max = " << tree2015D->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2015E photon eT max = " << tree2015E->GetMaximum("ph_sc_et") << " GeV" << endl;
  cout << "2015F photon eT max = " << tree2015F->GetMaximum("ph_sc_et") << " GeV" << endl;
}    
    
    
    
    
