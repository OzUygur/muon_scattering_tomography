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
  TH1F* hist1 = new TH1F("Ekin1", "Kinetic Energy On the First Deetctor", 100, 0, 10);
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

auto pitch_x  = 0.0;                           //pixel width (fiber to fiber distance)
auto pitch_y  = 0.0;                           //pixel width (fiber to fiber distance)
auto sigma_x = pitch_x/sqrt(12);               //sigma_x = pitch_x/sqrt(12)
auto sigma_y = pitch_y/sqrt(12);              //sigma_y = pitch_y/sqrt(12)
 
auto K = 1 + (posZ3-posZ2)/(posZ2-posZ1);    //detector plane separation to top-bottom detector separation + 1
auto sigma_z  = ((sigma_x + sigma_y)/2)/sqrt(2*pow(K,2)-2*abs(K)+2.);         

auto    RandomInt   = rand();                //creat Random Integer to make +/- (-1)^n

auto g_x  = (sigma_x)*pow(-1,RandomInt);
auto g_y  = (sigma_y)*pow(-1,RandomInt);
auto g_z  = (sigma_z);

auto X1 = posX1 + g_x;
auto X2 = posX2 + g_x;
auto X3 = posX3 + g_x;
auto X4 = posX4 + g_x;

auto Y1 = posY1 + g_y;
auto Y2 = posY2 + g_y;
auto Y3 = posY3 + g_y;
auto Y4 = posY4 + g_y;

auto Z1 = posZ1 + g_z;
auto Z2 = posZ2 + g_z;
auto Z3 = posZ3 + g_z;
auto Z4 = posZ4 + g_z;

// XY Plane (a b)
auto a1 = (Y2-Y1)/(X2-X1);
auto b1 = (Y1*X2-X1*Y2)/(X2-X1);
auto a2 = (Y4-Y3)/(X4-X3);
auto b2 = (Y3*X4-X3*Y4)/(X4-X3);
auto posX_xy = (b2-b1)/(a1-a2);
auto posY_xy = (a1*b2-a2*b1)/(a1-a2);

// ZX Plane (c d)
auto c1=(X2-X1)/(Z2-Z1);
auto d1=(X1*Z2-X2*Z1)/(Z2-Z1);
auto c2=(X4-X3)/(Z4-Z3);
auto d2=(X3*Z4-X4*Z3)/(Z4-Z3);
auto posX_zx = (c1*d2-c2*d1)/(c1-c2);
auto posZ_zx = (d2-d1)/(c1-c2);

// YZ Plane (e f)
auto e1=(Z2-Z1)/(Y2-Y1);
auto f1=(Z1*Y2-Z2*Y1)/(Y2-Y1);
auto e2=(Z4-Z3)/(Y4-Y3);
auto f2=(Z3*Y4-Z4*Y3)/(Y4-Y3);
auto posY_yz = (f2-f1)/(e1-e2);
auto posZ_yz= (f2*e1-f1*e2)/(e1-e2);

auto X  =  (posX_xy + posX_zx)/2;
auto Y  =  (posY_xy + posY_yz)/2;
auto Z  =  (posZ_yz + posZ_zx)/2; 


auto ThetaXY = atan(a2) - atan(a1);
auto ThetaXZ = atan(c2) - atan(c1);
auto ThetaZY = atan(e2) - atan(e1);
auto Theta = 1000*(ThetaXY + ThetaXZ + ThetaZY)/3;

/////////////////////////////////////////////////////
/*
//auto N = 100;
//for(int i = 0; i < N; ++i){
  //for(int j = 0; j<100;++j){

//https://pdg.lbl.gov/2015/AtomicNuclearProperties/HTML/air_dry_1_atm.html
auto X0_air = 36.62; // radiation length of air 36.62 g/cm2

//https://cosmic.lbl.gov/SKliewer/Cosmic_Rays/Muons.htm
auto p_r = 0.75;
auto Lambda_air = pow((0.0136/3),2)/X0_air;
auto Vr = (pow(p_r,2)*Lambda_air);
//auto Vr = 1.28e-4;
auto dVr = 1e-3;
auto alpha = 0.01;
auto S = fabs(sqrt(Vr));
auto cost = log(S) + pow(fTheta/S,2);
auto d_cost = (N - pow((fTheta/S),2))/S; // derivative of cost function

//Gradient Descent
S = S + alpha*d_cost;
Vr = pow(S/1000,2);
*/
////////////////////////////////////////////////////////
 // Gradient Descent
        auto alpha = 0.01;
        auto X0_air = 36.62; // radiation length of air 36.62 g/cm2
        auto p_r = 0.75;
        auto Lambda_air = pow((0.0136 / 3), 2) / X0_air;
        auto Vr = (pow(p_r, 2) * Lambda_air);

        auto sumTh2 = 0.0;
        auto Th2 = pow(Theta, 2);
        sumTh2 = Th2 + sumTh2;
        auto J = (N / 2) * log(Vr) + sumTh2 / (2 * Vr);
        auto DJ = (N / 2) * (1 / Vr) - sumTh2 / (4 * Vr * Vr);

        Vr -= alpha * DJ;

        cout << "Theta = " << Theta << endl;
        cout << "Vr = " << Vr << endl;

        // Pass length in the planes
        auto Lxy = (cos(atan(a1)) + cos(atan(a2))) / 2 * (cos(atan(a1)) * cos(atan(a2)));
        auto Lxz = (cos(atan(c1)) + cos(atan(c2))) / 2 * (cos(atan(c1)) * cos(atan(c2)));
        auto Lyz = (cos(atan(e1)) + cos(atan(e2))) / 2 * (cos(atan(e1)) * cos(atan(e2)));
        auto L = sqrt(pow(Lxy, 2) + pow(Lxz, 2) + pow(Lyz, 2));
        auto Lambda = fabs(Vr / (L * pow(p_r, 2)));

        cout << N << " Of->" << nentries << "-> Entries" << endl;
        cout << "Lambda = " << Lambda << endl;

        auto clock_end = clock();
        auto time_elapsed = 1000 * (clock_end - clock_start) / CLOCKS_PER_SEC;
        auto CPU_Time = time_elapsed;
        if (Lambda < 1e-1-7 and Lambda > 100) return;
        // Fill histograms
        hist1->Fill(Ekin1);
        hist2->Fill(-X, Y, Lambda);
    }

    // Draw histograms
    TCanvas* canvas1 = new TCanvas("canvas1", "Energy", 800, 600);
    hist1->Draw("hist");

    TCanvas* canvas2 = new TCanvas("canvas2", "2D Histogram Canvas", 600, 300);
    hist2->Draw("CONT4Z");
}
