//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 21 19:20:15 2023 by ROOT version 6.30/02
// from TTree Data/Ntuple
// found on file: analiz.root
//////////////////////////////////////////////////////////

#ifndef Analiz_h
#define Analiz_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Analiz {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        posX1;
   Double_t        posY1;
   Double_t        posZ1;
   Double_t        Ekin1;
   Double_t        posX2;
   Double_t        posY2;
   Double_t        posZ2;
   Double_t        Ekin2;
   Double_t        posX3;
   Double_t        posY3;
   Double_t        posZ3;
   Double_t        Ekin3;
   Double_t        posX4;
   Double_t        posY4;
   Double_t        posZ4;
   Double_t        Ekin4;
   Double_t        posX0;
   Double_t        posY0;
   Double_t        posZ0;
   Double_t        Ekin0;

   // List of branches
   TBranch        *b_posX1;   //!
   TBranch        *b_posY1;   //!
   TBranch        *b_posZ1;   //!
   TBranch        *b_Ekin1;   //!
   TBranch        *b_posX2;   //!
   TBranch        *b_posY2;   //!
   TBranch        *b_posZ2;   //!
   TBranch        *b_Ekin2;   //!
   TBranch        *b_posX3;   //!
   TBranch        *b_posY3;   //!
   TBranch        *b_posZ3;   //!
   TBranch        *b_Ekin3;   //!
   TBranch        *b_posX4;   //!
   TBranch        *b_posY4;   //!
   TBranch        *b_posZ4;   //!
   TBranch        *b_Ekin4;   //!
   TBranch        *b_posX0;   //!
   TBranch        *b_posY0;   //!
   TBranch        *b_posZ0;   //!
   TBranch        *b_Ekin0;   //!

   Analiz(TTree *tree=0);
   virtual ~Analiz();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analiz_cxx
Analiz::Analiz(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("analiz.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("analiz.root");
      }
      f->GetObject("Data",tree);

   }
   Init(tree);
}

Analiz::~Analiz()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analiz::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analiz::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analiz::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("posX1", &posX1, &b_posX1);
   fChain->SetBranchAddress("posY1", &posY1, &b_posY1);
   fChain->SetBranchAddress("posZ1", &posZ1, &b_posZ1);
   fChain->SetBranchAddress("Ekin1", &Ekin1, &b_Ekin1);
   fChain->SetBranchAddress("posX2", &posX2, &b_posX2);
   fChain->SetBranchAddress("posY2", &posY2, &b_posY2);
   fChain->SetBranchAddress("posZ2", &posZ2, &b_posZ2);
   fChain->SetBranchAddress("Ekin2", &Ekin2, &b_Ekin2);
   fChain->SetBranchAddress("posX3", &posX3, &b_posX3);
   fChain->SetBranchAddress("posY3", &posY3, &b_posY3);
   fChain->SetBranchAddress("posZ3", &posZ3, &b_posZ3);
   fChain->SetBranchAddress("Ekin3", &Ekin3, &b_Ekin3);
   fChain->SetBranchAddress("posX4", &posX4, &b_posX4);
   fChain->SetBranchAddress("posY4", &posY4, &b_posY4);
   fChain->SetBranchAddress("posZ4", &posZ4, &b_posZ4);
   fChain->SetBranchAddress("Ekin4", &Ekin4, &b_Ekin4);
   fChain->SetBranchAddress("posX0", &posX0, &b_posX0);
   fChain->SetBranchAddress("posY0", &posY0, &b_posY0);
   fChain->SetBranchAddress("posZ0", &posZ0, &b_posZ0);
   fChain->SetBranchAddress("Ekin0", &Ekin0, &b_Ekin0);
   Notify();
}

Bool_t Analiz::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analiz::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analiz::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
///////////////////////////////////////////////////////
#include <iostream>
#include <cmath>

// Function to calculate partial derivatives
void calculatePartialDerivatives(double X, double Y, double Z, double X1, double Y1, double Z1, double X2, double Y2, double Z2, double& dTheta_dX, double& dTheta_dY, double& dTheta_dZ) {
    dTheta_dX = 1 / (1 + pow((X2 - X) / (Z2 - Z), 2)) - 1 / (1 + pow((X - X1) / (Z - Z1), 2));

    dTheta_dY = 1 / (1 + pow((Y2 - Y) / (Z2 - Z), 2)) - 1 / (1 + pow((Y - Y1) / (Z - Z1), 2));
    
    double dTheta_dZx = (X2 - X) / ((Z2 - Z) * (Z2 - Z) + (X2 - X) * (X2 - X)) - (X - X1) / ((Z - Z1) * (Z - Z1) + (X - X1) * (X - X1));
    double dTheta_dZy = (Y2 - Y) / ((Z2 - Z) * (Z2 - Z) + (Y2 - Y) * (Y2 - Y)) - (Y - Y1) / ((Z - Z1) * (Z - Z1) + (Y - Y1) * (Y - Y1));
    
    dTheta_dZ = (dTheta_dZx + dTheta_dZy)/2;

}

// Function to find the root using Newton's method
void findRoot(double X1, double Y1, double Z1, double X2, double Y2, double Z2, double& X, double& Y, double Z, double tolerance = 1e-6) {
    // Initial guess
    X = (X1 + X2)/2;
    Y = (Y1 + Y2)/2;
    Z = (Z2 - Z1)/2;
    
    // Maximum number of iterations
    int maxIterations = 1000;

    for (int i = 0; i < maxIterations; ++i) {
        double dTheta_dX, dTheta_dY, dTheta_dZ;
        double alpha = 0.001;
        calculatePartialDerivatives(X, Y, Z, X1, Y1, Z1, X2, Y2, Z2, dTheta_dX, dTheta_dY, dTheta_dZ);

        // Update variables using Newton's method
        X -= alpha * dTheta_dX;
        Y -= alpha * dTheta_dY;
        Z -= alpha * dTheta_dZ;
       

        // Check for convergence
        if (sqrt(pow(dTheta_dX, 2) + pow(dTheta_dY, 2) + pow(dTheta_dZ, 2)) < tolerance) {
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////
// Function to calculate the partial derivatives
void calculateGradient(double X, double Y, double X1, double X2, double Y1, double Y2, double& Dx, double& Dy) {
    
    double A = pow((X - X2),2) + pow((Y - Y2),2);
    double B = pow((X - X1),2) + pow((Y - Y1),2);

    Dx = (Y2 - Y) / A + (Y1 - Y) / B;
    Dy = (X - X2) / A + (X - X1) / B;
}

// Gradient Descent OptimiYation
void gradientDescent(double& X, double& Y, double X1, double X2, double Y1, double Y2, double learningRate, int maxIterations, double tolerance) {
    int iteration = 100000;
    while (iteration < maxIterations) {
        double Dx, Dy;
        calculateGradient(X, Y, X1, X2, Y1, Y2, Dx, Dy);

        X += learningRate * Dx;
        Y += learningRate * Dy;

        double theta = atan((X2 - X) / (Y2 - Y)) - atan((X - X1) / (Y - Y1));

        if (fabs(theta) < tolerance) {
            std::cout << "Converged after " << iteration << " iterations." << std::endl;
            return;
        }

        iteration++;
    }

    std::cout << "Did not converge within the specified number of iterations." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////


#endif // #ifdef Analiz_cxx
