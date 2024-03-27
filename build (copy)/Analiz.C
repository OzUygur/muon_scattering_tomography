#define Analiz_cxx
#include "Analiz.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include<bits/stdc++.h> // timer
#include <cstdlib> // random number generator
using namespace std;

void Analiz::Loop(){
// In a ROOT session, you can do:
// root> .L Analiz.C
// root> Analiz t
// root> t.Loop();       
if (fChain == 0) return;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
  // Create a 1D histogram
  TH1F* hist1 = new TH1F("Theta", "Scattering Angle", 100, -1, 1);
  // Create a 2D histogram
  TH2F* hist2 = new TH2F("XY", "XY", 100, -300, 300, 100, -150, 150);
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   for (Long64_t jentry=0; jentry<nentries;jentry++){
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
//-------------------------------------------------------------------------------------------------------------
auto N = jentry;
auto clock_start = clock();
  //Spatial Resolution sigma_xyz

auto pitch_x  = 0.;                           //pixel width (fiber to fiber distance)
auto pitch_y  = 0.;                           //pixel width (fiber to fiber distance)
auto sigma_x = pitch_x/sqrt(12);               //sigma_x = pitch_x/sqrt(12)
auto sigma_y = pitch_y/sqrt(12);              //sigma_y = pitch_y/sqrt(12)
 
auto K = 1 + (posZ3-posZ2)/(posZ2-posZ1);    //detector plane separation to top-bottom detector separation + 1
auto sigma_z  = ((sigma_x + sigma_y)/2)/sqrt(2*pow(K,2)-2*abs(K)+2.);         

auto    RandomInt   = rand();                //creat Random Integer to make +/- (-1)^n

auto g_x  = (sigma_x)*pow(-1,RandomInt);
auto g_y  = (sigma_y)*pow(-1,RandomInt);
auto g_z  = (sigma_z);

auto X1 = posX2 + g_x;
auto X2 = posX3 + g_x;

auto Y1 = posY2 + g_y;
auto Y2 = posY3 + g_y;

auto Z1 = posZ2 + g_z;
auto Z2 = posZ3 + g_z;

/*  

double Theta = 0.001;
double Z = Z1;
double X = 0;
double Y = 0;

do {
    

    double X_new = (X1 + X2) / 2 + (Z2 + Z1) / (2*tan(Theta));
    double Y_new = (Y1 + Y2) / 2 + (Z2 + Z1) / (2*tan(Theta));
    double Theta_new = atan((Y2 - Y_new) / (X2 - X_new)) - atan((Y_new - Y1) / (X_new - X1));
    ++Z;
    X = X_new; Y = Y_new; Theta = Theta_new;
   } 

while (Z < Z2);
*/

//double X = (X1 + X2) / 2;
//double Y = (Y1 + Y2) / 2;
//double Theta = atan((Y2 - Y) / (X2 - X)) - atan((Y - Y1) / (X - X1));
/*
for (double Z = Z1; Z < Z2; ++Z) {

    double a1 = (Z - Z1) / (X - X1);
    double b1 = (Z1 * X - Z * X1) / (X - X1);
    double a2 = (Z2 - Z) / (X2 - X);
    double b2 = (Z * X2 - Z2 * X) / (X2 - X);
    
    double c1 = (Z - Z1) / (Y - Y1);
    double d1 = (Z1 * Y - Z * Y1) / (Y - Y1);
    double c2 = (Z2 - Z) / (Y2 - Y);
    double d2 = (Z * Y2 - Z2 * Y) / (Y2 - Y);

    double X_new = (b1 - b2) / (a2 - a1);
    double Y_new = (d1 - d2) / (c2 - c1);

    X = X_new;
    Y = Y_new;
}
*/

double X, Y, Z, Theta;
findRoot(X1, Y1, Z1, X2, Y2, Z2, X, Y, Z);

/*

double learningRate = 0.001;
double tolerance = 1e-6;
int maxIterations = 1000;
//gradientDescent(X, Y, X1, X2, Y1, Y2, learningRate, maxIterations, tolerance);
*/
Theta = atan((Y2-Y)/(X2-X)) - atan((Y-Y1)/(X-X1));
///////////////////////////////////////////////////////////////////////
/*double X, Y, Z, Theta;
double ThetaMin = 0.0001; double ThetaMax = 0.1;
for (double th = ThetaMin; th < ThetaMax; ++th){
 for( double z = Z1; z < Z2; ++z){
X = (X1 + X2)/2 + (Z2 - Z1)/2*tan(th);
Y = (Y1 + Y2)/2 + (Z2 - Z1)/2*tan(th);
Z = z;}}

double ThetaX = atan((Z2-Z)/(X2-X)) - atan((Z-Z1)/(X-X1));
double ThetaY = atan((Z2-Z)/(Y2-Y)) - atan((Z-Z1)/(Y-Y1));
Theta = (ThetaX + ThetaY)/2;
*/

/*
double X, Y, Z;
double alpha = 0.1;
int epoch = 1;
double Ax = (X1-X2); double Bx = (Z2-Z1); double Cx = Z1*X2 - X1*Z2;
double Ay = (Y1-Y2); double By = (Z2-Z1); double Cy = Z1*Y2 - Y1*Z2;
double dx = fabs(Ax*Z + Bx*X + Cx)/sqrt(pow(Ax,2) + pow(Bx,2));
double dy = fabs(Ay*Z + By*Y + Cy)/sqrt(pow(Ay,2) + pow(By,2));

for(double z = Z1; z < Z2; ++z){
 for(int i = 0; i < epoch; ++i){
double Dx = (Bx/sqrt(pow(Ax,2) + pow(Bx,2)))*((Ax*Z + Bx*X + Cx)/fabs(Ax*Z + Bx*X + Cx));
double Dy = (By/sqrt(pow(Ay,2) + pow(By,2)))*((Ay*Z + By*Y + Cy)/fabs(Ay*Z + By*Y + Cy));

X = X - alpha * Dx;
Y = Y - alpha * Dy;
Z = z;}}
double Theta = atan((Y2 - Y) / (X2 - X)) - atan((Y - Y1) / (X - X1));
///////////////////////////////////////////////////////////////////////


//std::cout << "Root: X = " << X << ", Y = " << Y << ", Z = " << Z << std::endl;
for( double z = Z1; z < Z2; ++z){
X = z*(X2 - X1)/(Z2 - Z1) - (X1*Z2 - Z1*X2)/(Z2 - Z1);
Y = z*(Y2 - Y1)/(Z2 - Z1) - (Y1*Z2 - Z1*Y2)/(Z2 - Z1);
Z = z;
}

double V1[] = {(X-X1), (Y-Y1), (Z-Z1)};
double V2[] = {(X2-X), (Y2-Y), (Z2-Z)};
double L1 = sqrt(pow(V1[0],2)+pow(V1[1],2)+pow(V1[2],2));
double L2 = sqrt(pow(V2[0],2)+pow(V2[1],2)+pow(V2[2],2));
double V1DOTV2 = (V1[0]*V2[0] + V1[1]*V2[1] + V1[2]*V2[2]);
auto Theta = acos(V1DOTV2/(L1*L2));
*/


std::cout << "N " << N << " of total: " << nentries <<  std::endl;

auto clock_end = clock();
auto time_elapsed = 1000 * (clock_end - clock_start) / CLOCKS_PER_SEC;
auto CPU_Time = time_elapsed;

// Fill histograms
if((Ekin2-Ekin3) > 0.001){

hist1->Fill(Theta);
hist2->Fill(-X, Y);
}}

// Draw histograms
TCanvas* canvas1 = new TCanvas("canvas1", "Scattering Angle", 800, 600);
hist1->Draw("hist");

TCanvas* canvas2 = new TCanvas("canvas2", "2D Histogram Canvas", 600, 300);
hist2->Draw("CONT4Z");
}
