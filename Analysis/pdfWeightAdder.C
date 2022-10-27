// Macro to add PDF weights to nanoAODtrees
// calcAlphas, calcRenomrmWeight, and calcFacorizeWeight lightly modified from versions sent by Carlos at https://cms-pub-talk.web.cern.ch/t/comments-on-anv7/6774/3

// Compilation instuctions:
/*
  This macro requires both ROOT and the LHAPDF library so must be compiled against both.
  To compile using root on LPC:
  - Set up a CMS env 
  - run:  lhapdf-config --cflags --ldflags     to get the paths necessary for compilation
      and linking against LHAPDF
  - start root:    root
  - in root, run :  gSystem->AddIncludePath(" -I/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/lhapdf/6.2.1-pafccj3/include ")     where the path matches the include path from the lhapdf-config
  - in root, run : gSystem->AddLinkedLibs("-L/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/lhapdf/6.2.1-pafccj3/lib -lLHAPDF")   where the path matches the include path from the lhapdf-config
  - in root, compile this script:    .L pdfWeightAdder.C+
  - The functions below can now be run

*/

#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#include <cmath>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

using namespace LHAPDF;

//TString FILEPATH_BASE = "root://cmsxrootd.fnal.gov//store/user/"; //The path to the directory containing files to be used

TString FILEPATH_BASE = "../Data/PdfWeights/";
const int LHAPDF_NOM =303600; // nominal PDF used to generate the sample. This should also be used for e.g. the muF uncertainty below
// Nominal pdf is NNPDF31_nnlo_as_0118 => lhapdfnumber_base = 303600
const int LHAPDF_VAR_LOW = 303601; //The LHAPDF number of the first variation
const int LHAPDF_VAR_HIGH = 303700; //The LHAPDF number of the last variation
int nVars = 100; //The number of variations // WARNING /// this is assumed to be 100 in the weightsForVar branch def below
int nVarsUD = 2 * nVars; //doubled to include up and down   ///// WARNING   //////// this is assumed to be 200 in the weightsForVar branch def below




void addPDFWeightsToNanoAOD(TString filename, int nQCD);
double calcAlphas(double q2);
double calcRenormWeight(double q, int up_or_dn, int nQCD);
double calcFactorizWeight(LHAPDF::PDF* pdf, double id1, double id2, double x1, double x2, double q, int up_or_dn);

/*
int main(int argc, char* argv[])
{
  TString filename = "ZZ_2018.root";
  int nQCD = 0;

  addPDFWeightsToNanoAOD(filename, nQCD);

  return 0;
  }*/


/* Reads in nominal weighting information from the Events tree in filename and calculates and stores new weights in the tree
    TString filename : the name of the root file to be read, relative to FILEPATH_BASE. This file will be updated in place
    int nQCD : the number of QCD vertices (i.e. gg/gq/qq -> gluino gluino or stop stop) in the diagram
*/
void addPDFWeightsToNanoAOD(TString filename, int nQCD)
{
    TFile* file = TFile::Open(FILEPATH_BASE + filename, "UPDATE");
    TTree* tree = (TTree*) file->Get("Events");
    
    //Set up storage of new weights
    double alphas;
    double renormWeights[2]; //Up, down
    double factorizWeights[nVarsUD];
    double weightsForVar[nVars]; 
    TBranch *b_alphas = tree->Branch("PDFWeights_alphas", &alphas, "PDFWeights_alphas/F");
    TBranch *b_renormWeights = tree->Branch("PDFWeights_renormWeights", renormWeights, "PDFWeights_renormWeights[2]/F");
    TBranch *b_nVarsUD = tree->Branch("PDFWeights_nVarsUD", &nVarsUD, "PDFWeights_nVarsUD/i");
    TBranch *b_nVars = tree->Branch("PDFWeights_nVars", &nVars, "PDFWeights_nVars/i");
    b_nVarsUD->Fill();
    b_nVars->Fill();
    TBranch *b_factorizeWeights = tree->Branch("PDFWeights_factorizeWeights", factorizWeights, "PDFWeights_factorizeWeights[200]/F");
    TBranch *b_weightsForVar = tree->Branch("PDFWeights_weightsForVar", weightsForVar, "PDFWeights_weightsForVar[100]/F");

    //Get the PDFs
    PDF* nomPDF = LHAPDF::mkPDF(LHAPDF_NOM); //Nominal PDF
    PDF* varPDFs[nVars];
    for (int i = 0; i< nVars; i++)
      {
	varPDFs[i] = LHAPDF::mkPDF(LHAPDF_VAR_LOW + i);
      }
    
    const int VAR_UP = 1;
    const int VAR_DOWN = -1;
    float q;
    float scalePDF, x1, x2; //The existing variables in the tree that we'll need to calc the new weights
    int id1, id2;
    tree->SetBranchAddress("Generator_id1", &id1);
    tree->SetBranchAddress("Generator_id2", &id2);
    tree->SetBranchAddress("Generator_scalePDF", &scalePDF);
    tree->SetBranchAddress("Generator_x1", &x1);
    tree->SetBranchAddress("Generator_x2", &x2);
    int nEntries = tree->GetEntries();
    for (int entryN = 0; entryN < nEntries; entryN++)
    {
        //Get the existing values from the tree
        tree->GetEntry(entryN);
        q = sqrt(scalePDF);

        //Calc the new weights
        alphas = calcAlphas(scalePDF);
        renormWeights[0] = calcRenormWeight(q, VAR_UP, nQCD); //Up varation
        renormWeights[1] = calcRenormWeight(q, VAR_DOWN, nQCD); //Down variation
        for (int varN = 0; varN < nVars; varN++) 
        {
            factorizWeights[varN] = calcFactorizWeight(varPDFs[varN], id1, id2, x1, x2, q, VAR_UP); //Up var
            factorizWeights[varN+1] = calcFactorizWeight(varPDFs[varN], id1, id2, x1, x2, q, VAR_UP); //Down var

            // weight using https://lhapdf.hepforge.org/group__reweight__double.html, one per replica.
            weightsForVar[varN] = LHAPDF::weightxxQ(id1, id2, x1, x2, scalePDF, nomPDF, varPDFs[varN]); // id1, id2, x1, x2, scalePDF available in nanoAOD
        }

        //Fill the tree
        b_alphas->Fill();
        b_renormWeights->Fill();
        b_factorizeWeights->Fill();
        b_weightsForVar->Fill();
    }
    
    tree->Write("", TObject::kOverwrite); // save only the new version of the tree

}

// q2 == Generator_scalePDF in NanoAOD
double calcAlphas(double q2) 
{ 
    double mZ = 91.2; //Z boson mass in the NNPDF31_nnlo_as_0118 docs (http://lhapdfsets.web.cern.ch/lhapdfsets/current/NNPDF31_nnlo_as_0118/NNPDF31_nnlo_as_0118.info )
    double alphas_mZ = 0.118; //alpha_s evaluated at Z boson mass, based on the NNPDF31_nnlo_as_0118 docs (http://lhapdfsets.web.cern.ch/lhapdfsets/current/NNPDF31_nnlo_as_0118/NNPDF31_nnlo_as_0118.info )
    int nFlavors = 5; //effective number of flavors
    double b0 = (33 - 2.0 * nFlavors) / (12 * M_PI); 
    return alphas_mZ / (1 + alphas_mZ * b0 * std::log(q2 / std::pow(mZ,2))); // alphas evolution
}

// Will always be 1 for electroweak processes at LO
//number of QCD vertices (i.e. gg/gq/qq -> gluino gluino or stop stop) 
double calcRenormWeight(double q, int up_or_dn, int nQCD) 
{ 
    double q2 = q*q;
    double k2 = 1;

    if      ( up_or_dn ==  1 ) k2 = 4; // 2*q ==> 4*q2
    else if ( up_or_dn == -1 ) k2 = 0.25; // 0.5*q ==> 0.25*q2
    else {
      throw std::invalid_argument("up_or_dn must be -1 or 1");
    }
    
    double alphas_old = calcAlphas(q2);
    double alphas_new = calcAlphas(k2*q2);
 
    return std::pow(alphas_new / alphas_old, nQCD);
}


double calcFactorizWeight(LHAPDF::PDF* pdf, double id1, double id2, double x1, double x2, double q, int up_or_dn) 
{
    double q2 = q*q;
    double k2 = 1;

    if      ( up_or_dn ==  1 ) k2 = 4; // 2*q ==> 4*q2
    else if ( up_or_dn == -1 ) k2 = 0.25; // 0.5*q ==> 0.25*q2
    else {
        throw std::invalid_argument("up_or_dn must be -1 or 1");
    }

    double pdf1old = pdf->xfxQ2(id1,x1,q2);
    double pdf2old = pdf->xfxQ2(id2,x2,q2);
    double pdf1new = pdf->xfxQ2(id1,x1,k2*q2);
    double pdf2new = pdf->xfxQ2(id2,x2,k2*q2);

    return (pdf1new*pdf2new)/(pdf1old*pdf2old);
}
