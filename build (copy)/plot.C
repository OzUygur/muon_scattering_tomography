#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TH2D.h"

void plot()
{

    TCanvas *c1 = new TCanvas("c1","Data",600,300);
     //c1->Divide(2,1);
     //c1->SetLogx();
     //c1->SetLogy();
     //c1->SetLogz();

     c1->SetFillColor(0);
     //c1->SetGridx();
     //c1->SetGridy();

    
     gStyle->SetOptStat(0);


   
   TFile *_file1 = new TFile("analiz.root");
   //TFile *_file2 = new TFile("analiz-b.root");
   

   TH2D *h = (TH2D*)_file1->Get("YZ");
  // TH2D *h2 = (TH2D*)_file2->Get("XY");

   
   //Subtract Histograms

   //TH2D* h3 = (TH2D*) h1->Clone("Subtr_hist");
   //h3->Add(h2, -1);
   
   h->Draw("cont4z");
   h->SetAxisRange(30., 60.,"Z");



   c1->SaveAs("YZPos-SSP.png");
   //h3->SaveAs("XV.csv");

/////////////////////////////////////////////////////////////////////
   /*TText *pt1 = new TText( 0.2, 12., "Scattering Angle");
   pt1->SetTextSize(0.03);
   pt1->SetTextFont(42);
   pt1->Draw();*/
///////////////////////////////////////////////////////////////////////
   
   return;
}
