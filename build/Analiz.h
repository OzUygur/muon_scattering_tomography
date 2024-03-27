//////////////////////////////////////////////////////////
// This class has been doublematically generated on
// Thu Dec 21 19:20:15 2023 by ROOT version 6.30/02
// from TTree Data/Ntuple
// found on file: analiz.root
//////////////////////////////////////////////////////////

#ifndef Analiz_h
#define Analiz_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <cmath>
#include<bits/stdc++.h> // timer
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
std::tuple<double, double, double, double, double> SSP(double X1, double Y1, double Z1,
                                                       double X2, double Y2, double Z2,
                                                       double X3, double Y3, double Z3,
                                                       double X4, double Y4, double Z4, 
                                                       int N){
                                                     
double clock_start = clock();

double TX_in = atan(((X2-X1))/(Z2-Z1));
double TY_in = atan((Y2-Y1)/(Z2-Z1));
double TX_out = atan((X4-X3)/(Z4-Z3));  
double TY_out = atan((Y4-Y3)/(Z4-Z3));

double DTX = (TX_out - TX_in);
double DTY = (TY_out - TY_in);
double Theta = (DTX + DTY)/2;

/*
double sumTheta2 = 0.0;

// Calculate the sum of squared differences from the mean

for (int i = 0; i < N; ++i) {
 double Theta2 = Theta * Theta;
 sumTheta2 += Theta2;

}

// Calculate the variance
double varTheta = sumTheta2 / N;

// Calculate the standard deviation
double stdTheta = sqrt(varTheta);

*/


double KX_in = tan(TX_in);
double KY_in = tan(TY_in);
double BX_in = (KX_in)*(Z2*X1-X2*Z1)/(X2-X1);              
double BY_in = (KY_in)*(Z2*Y1-Y2*Z1)/(Y2-Y1);
double X,Y,Z;
if(fabs(DTX) > 0.005 or fabs(DTY) > 0.005){
double KX_out = tan(atan(KX_in) + DTX);
double BX_out = (KX_out)*(Z4*X3-X4*Z3)/(X4-X3); 
                 
double KY_out = tan(atan(KY_in) + DTY);
double BY_out = (KY_out)*(Z4*Y3-Y4*Z3)/(Y4-Y3);


X = (BX_in*KX_out - BX_out*KX_in)/(KX_out - KX_in); 
Y = (BY_in*KY_out - BY_out*KY_in)/(KY_out - KY_in); 
double ZX = (BX_in - BX_out)/(KX_out - KX_in);
double ZY = (BY_in - BY_out)/(KY_out - KY_in);
Z = (ZX + ZY)/2;}

double clock_end = clock();
double time_elapsed = 1000 * (clock_end - clock_start) / CLOCKS_PER_SEC;
double CPU_Time = time_elapsed;

return std::make_tuple(X, Y, Z, Theta, CPU_Time);
 
}

////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<double, double, double, double, double> POCA(double X1, double Y1, double Z1,
                                                        double X2, double Y2, double Z2,
                                                        double X3, double Y3, double Z3,
                                                        double X4, double Y4, double Z4){
                                               
double clock_start = clock();  
                                                                                            
// Calculate position
double u1[] = {(X2-X1), (Y2-Y1), (Z2-Z1)};
double u2[] = {(X4-X3), (Y4-Y3), (Z4-Z3)};
double w[] = {-(X3-X1), -(Y3-Y1), -(Z3-Z1)};

double u1DOTu1 = (u1[0]*u1[0] + u1[1]*u1[1] + u1[2]*u1[2]);
double u2DOTu2 = (u2[0]*u2[0] + u2[1]*u2[1] + u2[2]*u2[2]);
double u1DOTu2 = (u1[0]*u2[0] + u1[1]*u2[1] + u1[2]*u2[2]);
double u1DOTw = (u1[0]*w[0] + u1[1]*w[1] + u1[2]*w[2]);
double u2DOTw = (u2[0]*w[0] + u2[1]*w[1] + u2[2]*w[2]);

double a = u1DOTu1; 
double b = u1DOTu2; 
double c = u2DOTu2;

double d = u1DOTw; 
double e = u2DOTw;
double delta = a*c-b*b;

double t1 = (b*e-c*d)/delta; 
double t2 = (a*e-b*d)/delta;

double P01[] = {X1, Y1, Z1};
double P02[] = {X3, Y3, Z3};

double P1[] =  {(P01[0] + t1*u1[0]), (P01[1] + t1*u1[1]), (P01[1] + t1*u1[2])};  
double P2[] =  {(P02[0] + t2*u2[0]), (P02[1] + t2*u2[1]), (P02[2] + t2*u2[2])}; 
double POCA[] = {(P1[0]+P2[0])/2,(P1[1]+P2[1])/2,(P1[2]+P2[2])/2};

double L1 = sqrt(pow(u1[0],2)+pow(u1[1],2)+pow(u1[2],2));
double L2 = sqrt(pow(u2[0],2)+pow(u2[1],2)+pow(u2[2],2));    

double Theta1 = acos(u1[2]/L1);
double Theta2 = acos(u2[2]/L2);
double Theta = 1000*(Theta2 - Theta1); 
double X,Y,Z;
if(fabs(Theta) > 0.005){
X = (POCA[0]); 
Y = (POCA[1]); 
Z = (POCA[2]);
}


double clock_end = clock();
double time_elapsed = 1000 * (clock_end - clock_start) / CLOCKS_PER_SEC;
double CPU_Time = time_elapsed;                                              
                                                   
return std::make_tuple(X, Y, Z, Theta, CPU_Time);
}

////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<double, double, double, double, double> POLAR(double X1, double Y1, double Z1,
                                                         double X2, double Y2, double Z2,
                                                         double X3, double Y3, double Z3,
                                                         double X4, double Y4, double Z4) {

double clock_start = clock();

// Calculate Theta
double u1[] = {X2 - X1, Y2 - Y1, Z2 - Z1};
double u2[] = {X4 - X3, Y4 - Y3, Z4 - Z3};
double L1 = sqrt(pow(u1[0], 2) + pow(u1[1], 2) + pow(u1[2], 2));
double L2 = sqrt(pow(u2[0], 2) + pow(u2[1], 2) + pow(u2[2], 2));
double Theta1 = acos(u1[2] / L1);
double Theta2 = acos(u2[2] / L2);
double Theta = 1000 * (Theta2 - Theta1);

// Polar Coordinate for X
double R1x = sqrt(X1 * X1 + Z1 * Z1);
double R2x = sqrt(X2 * X2 + Z2 * Z2);
double R3x = sqrt(X3 * X3 + Z3 * Z3);
double R4x = sqrt(X4 * X4 + Z4 * Z4);
double Th1x = atan2(Z1, X1);
double Th2x = atan2(Z2, X2);
double Th3x = atan2(Z3, X3);
double Th4x = atan2(Z4, X4);

double fux = atan2((R2x * cos(Th2x) - R1x * cos(Th1x)), (R1x * sin(Th1x) - R2x * sin(Th2x)));
double pux = 0.5 * (R1x * cos(Th1x - fux) + R2x * cos(Th2x - fux));
double fdx = atan2((R4x * cos(Th4x) - R3x * cos(Th3x)), (R3x * sin(Th3x) - R4x * sin(Th4x)));
double pdx = 0.5 * (R3x * cos(Th3x - fdx) + R4x * cos(Th4x - fdx));
double Thx = atan2((pux * cos(fdx) - pdx * cos(fux)), (pdx * sin(fux) - pux * sin(fdx)));
double Rx = 0.5 * pux / (cos(Thx - fux)) + 0.5 * pdx / (cos(Thx - fdx));
double X = Rx * cos(Thx);
double Zx = Rx * sin(Thx);

// Polar Coordinate for Y
double R1y = sqrt(Y1 * Y1 + Z1 * Z1);
double R2y = sqrt(Y2 * Y2 + Z2 * Z2);
double R3y = sqrt(Y3 * Y3 + Z3 * Z3);
double R4y = sqrt(Y4 * Y4 + Z4 * Z4);
double Th1y = atan2(Z1, Y1);
double Th2y = atan2(Z2, Y2);
double Th3y = atan2(Z3, Y3);
double Th4y = atan2(Z4, Y4);

double fuy = atan2((R2y * cos(Th2y) - R1y * cos(Th1y)), (R1y * sin(Th1y) - R2y * sin(Th2y)));
double puy = 0.5 * (R1y * cos(Th1y - fuy) + R2y * cos(Th2y - fuy));
double fdy = atan2((R4y * cos(Th4y) - R3y * cos(Th3y)), (R3y * sin(Th3y) - R4y * sin(Th4y)));
double pdy = 0.5 * (R3y * cos(Th3y - fdy) + R4y * cos(Th4y - fdy));
double Thy = atan2((puy * cos(fdy) - pdy * cos(fuy)), (pdy * sin(fuy) - puy * sin(fdy)));
double Ry = 0.5 * puy / (cos(Thy - fuy)) + 0.5 * pdy / (cos(Thy - fdy));
double Y = Ry * cos(Thy);
double Zy = Ry * sin(Thy);

// Calculate Z
double Z = (Zx + Zy) / 2;

double clock_end = clock();
double time_elapsed = 1000 * (clock_end - clock_start) / CLOCKS_PER_SEC;
double CPU_Time = time_elapsed;

return std::make_tuple(X, Y, Z, Theta, CPU_Time);

}
double ScatteringDensity(double& Theta, int N, double Z, double Z1, 
                         double X, double X1, double Z2, double X2, 
                         double Y, double Y1, double Y2, double P) {
                          
    // Initialize variables
    double sumTh2 = 0.0;
    double Vr = 0.0;
    double p_r = 3/P;  


    // Gradient Descent
    for (int i = 0; i < N; ++i) {
    
        double Th2 = pow(Theta, 2);
        sumTh2 += Th2;
        double Sigma = sqrt(sumTh2)/N;
        Vr = pow(Sigma,2);
    }

    double a1 = (Z - Z1) / (X - X1);
    double a2 = (Z2 - Z) / (X2 - X);
    double c1 = (Z - Z1) / (Y - Y1);
    double c2 = (Z2 - Z) / (Y2 - Y);

    double Lxz = (cos(atan(a1)) + cos(atan(a2))) / 2 * (cos(atan(a1)) * cos(atan(a2)));
    double Lyz = (cos(atan(c1)) + cos(atan(c2))) / 2 * (cos(atan(c1)) * cos(atan(c2)));
    double L = sqrt(pow(Lxz, 2) + pow(Lyz, 2));
    
    //std::cout << "L = " << L << std::endl;

    return fabs(Vr / (L * pow(p_r, 2)));
}


#endif // #ifdef Analiz_cxx
