#define Analiz_cxx
#include "Analiz.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <cstdlib> // random number generator
using namespace std;

void Analiz::Loop(){
// In a ROOT session, you can do:
// root> .L Analiz.C
// root> Analiz t
// root> t.Loop();       
if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
///////////////////////////////////////////////////////////////////////////////////////

 // Create 1D histograms
  TH1F* hist_dE = new TH1F("dE", "Energy Loss (MeV)", 100, 0., 100.);
  
  TH1F* hist_Theta_ssp = new TH1F("Theta", "Scattering Angle (mrad)", 100, -200., 200.);
  TH1F* hist_Theta_poca = new TH1F("Theta", "Scattering Angle (mrad)", 100, -200., 200.);
  
  TH1F* hist_cpu_ssp = new TH1F("CPU", "CPU Time (ms)", 100, 0., 0.5);
  TH1F* hist_cpu_poca = new TH1F("CPU", "CPU Time (ms)", 100, 0., 0.5);
  		
  // Create a 2D histogram
  TH2F* hist_ssp = new TH2F("XY", "XY", 300, -300., 300., 150, -150., 150.);
  TH2F* hist_poca = new TH2F("XY", "XY", 300, -300., 300., 150, -150., 150.);
  
///////////////////////////////////////////////////////////////////////////////////////
   for (Long64_t jentry=0; jentry<nentries;jentry++){
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
//---------------------------------------------------------------------------------------
double N = jentry;

//Spatial Resolution sigma_xyz

double pitch_x  = 0.5;                           //pixel width (fiber to fiber distance)
double pitch_y  = 0.5;
                           //pixel width (fiber to fiber distance)
double sigma_x = pitch_x/sqrt(12);               //sigma_x = pitch_x/sqrt(12)
double sigma_y = pitch_y/sqrt(12);              //sigma_y = pitch_y/sqrt(12)         
double sigma_z  = 0.;    

int n = (static_cast<double>(rand()) / RAND_MAX) * 2 - 1;
double g_x  = (sigma_x)*pow(-1,n);
double g_y  = (sigma_y)*pow(-1,n);
double g_z  = (sigma_z);

double X1 = posX1 + g_x;
double X2 = posX2 + g_x;
double X3 = posX3 + g_x;
double X4 = posX4 + g_x;

double Y1 = posY1 + g_y;
double Y2 = posY2 + g_y;
double Y3 = posY3 + g_y;
double Y4 = posY4 + g_y;

double Z1 = posZ1 + g_z;
double Z2 = posZ2 + g_z;
double Z3 = posZ3 + g_z;
double Z4 = posZ4 + g_z;

/////////////////////SSP//////////////////////////////////
auto ssp = SSP(X1, Y1, Z1, 
               X2, Y2, Z2,
               X3, Y3, Z3,
               X4, Y4, Z4, 
               nentries);

double X_ssp = get<0>(ssp);
double Y_ssp = get<1>(ssp);
double Z_ssp = get<2>(ssp);
double Theta_ssp = get<3>(ssp);
double cpu_ssp = get<4>(ssp);
/////////////////////POCA//////////////////////////////////
auto poca = POCA(X1, Y1, Z1, 
                 X2, Y2, Z2,
                 X3, Y3, Z3,
                 X4, Y4, Z4);

double X_poca = get<0>(poca);
double Y_poca = get<1>(poca);
double Z_poca = get<2>(poca);
double Theta_poca = get<3>(poca);
double cpu_poca = get<4>(poca);
//////////////////////////////////////////////////////////
auto polar = POLAR(X1, Y1, Z1, 
                   X2, Y2, Z2,
                   X3, Y3, Z3,
                   X4, Y4, Z4);

double X_polar = get<0>(polar);
double Y_polar = get<1>(polar);
double Z_polar = get<2>(polar);
double Theta_polar = get<3>(polar);
double cpu_polar = get<4>(polar);

        cout << N << " Of->" << nentries << "-> Entries" << endl;
        double dE = 1000*(Ekin2-Ekin3);
        double dE_dX = 1.8;
      
        
        // Fill histograms
        hist_dE->Fill(dE);
        hist_dE->GetXaxis()->SetTitle("Energy Loss (MeV)");
        hist_dE->GetYaxis()->SetTitle("Frequency");
        double mean_dE = hist_dE->GetMean();
        double std_dE = hist_dE->GetStdDev();
      
        hist_Theta_ssp->Fill(Theta_ssp);
        hist_Theta_ssp->GetXaxis()->SetTitle("Scattering Angle (mrad)");
        hist_Theta_ssp->GetYaxis()->SetTitle("Frequency");
        double stdTheta_ssp = hist_Theta_ssp->GetStdDev();
        
        hist_Theta_poca->Fill(Theta_poca);
        hist_Theta_poca->GetXaxis()->SetTitle("Scattering Angle (mrad)");
        hist_Theta_poca->GetYaxis()->SetTitle("Frequency");
        double stdTheta_poca = hist_Theta_poca->GetStdDev();
        
        hist_cpu_ssp->Fill(cpu_polar);
        hist_cpu_ssp->SetLineColor(kRed);
        hist_cpu_ssp->GetXaxis()->SetTitle("CPU Time (ms)");
        hist_cpu_ssp->GetYaxis()->SetTitle("Frequency");
        
        hist_cpu_poca->Fill(cpu_poca);
        hist_cpu_poca->SetLineColor(kBlue);
        hist_cpu_poca->GetXaxis()->SetTitle("CPU Time (ms)");
        hist_cpu_poca->GetYaxis()->SetTitle("Frequency");
        
        
        double l1 = sqrt(pow((X2-X_ssp), 2) + pow((Y2-Y_ssp), 2) + pow((Z2-Z_ssp), 2));
        double l2 = sqrt(pow((X_ssp-X1), 2) + pow((Y_ssp-Y1), 2) + pow((Z_ssp-Z1), 2));
        double d = sqrt(pow((X2-X1), 2) + pow((Y2-Y1), 2) + pow((Z2-Z1), 2));
        double A = (Y3-Y2); double B = (X2-X3); double C = (Y2*X3 - X2*Y3);
        double D_ssp = fabs(A*X_ssp + B*Y_ssp + C)/sqrt(A*A + B*B);
        double D_poca = fabs(A*X_poca + B*Y_poca + C)/sqrt(A*A + B*B);
        
          
        double l = l1 + l2;
        double dencity_air = 0.00125;
        double Stp = 2.3;
        double lE = Stp * dencity_air * l;
        double Pr = (Ekin2 + Ekin3)/6;
        double Lambda_ssp = pow(stdTheta_ssp/Pr,2)/l;
        double Lambda_poca = pow(stdTheta_poca/Pr,2)/l;
        double Lambda_air = pow((14/3000)*sqrt(1/36.62),2);
        
        double dE_air = dE_dX*l*dencity_air;
        
        //std::cout << "dE = " << dE << std::endl;
        //std::cout << "dE_air = " << dE_air << std::endl;
        
        double diff = l - d;
         //if(D_ssp > 0){  
         if(dE > dE_air){  // Scattering denciry more than 
        
        hist_ssp->Fill(-X_polar, Y_polar);
        hist_ssp->SetTitle("Polar Algorithm");
        hist_ssp->GetXaxis()->SetTitle("X Hit Positions (cm)");
        hist_ssp->GetYaxis()->SetTitle("Y Hit Positions (cm)");
        hist_ssp->GetZaxis()->SetTitle("Frequency");
        hist_ssp->GetZaxis()->SetRangeUser(0, 100);
        //hist_ssp->Scale(1.0 / hist_ssp->Integral());
         }
        
         if(dE_air > 0.015){  // Scattering denciry more than 
        hist_poca->Fill(-X_poca, Y_poca);
        hist_poca->SetTitle("POCA Algorithm");
        hist_poca->GetXaxis()->SetTitle("X Hit Positions (cm)");
        hist_poca->GetYaxis()->SetTitle("Y Hit Positions (cm)");
        hist_poca->GetZaxis()->SetTitle("Frequency");
        hist_poca->GetZaxis()->SetRangeUser(0, 100);
        //hist_poca->Scale(1.0 / hist_poca->Integral());

          
       }
   }
  
    

    // Draw histograms
    TCanvas* canvas1 = new TCanvas("canvas1", "Energy Loss", 800, 600);
    hist_dE->Draw("hist");
    
    TCanvas* canvas2 = new TCanvas("canvas2", "Theta", 800, 600);
    hist_Theta_ssp->Draw("hist");
    hist_Theta_poca->Draw("hist, same");

    TCanvas* canvas3 = new TCanvas("canvas2", "CPU", 800, 600);
    hist_cpu_ssp->Draw("hist");
    hist_cpu_poca->Draw("hist, same");
    
    // Create a legend
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // (x1, y1, x2, y2) in normalized coordinates
    legend->SetBorderSize(0); // Remove border
    legend->SetFillColor(0);  // Set fill color to white

    // Add entry to the legend
    legend->AddEntry(hist_cpu_ssp, "POLAR", "l"); // "l" option for a line
    legend->AddEntry(hist_cpu_poca, "POCA", "l"); // "l" option for a line

    // Draw the legend
    legend->Draw();
    
    
    
    TCanvas* canvas4 = new TCanvas("canvas3", "Reconstructed Image", 800, 800);
    canvas4->Divide(1, 2);
  
  
    canvas4->cd(1);
    hist_ssp->Draw("CONT4Z");
    hist_ssp->SetStats(0); // Turn off statistics
    
    canvas4->cd(2);
    hist_poca->Draw("CONT4Z");
    hist_poca->SetStats(0); // Turn off statistics
    
   // Redraw the histogram with the updated range
    canvas4->Update();

}
