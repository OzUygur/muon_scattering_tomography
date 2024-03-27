#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"

void Legend()
{

    TCanvas *c1 = new TCanvas("c1","Data",800,800);
     //c1->Divide(2,1);
     //c1->SetLogx();
     c1->SetLogy();

     c1->SetFillColor(0);
     //c1->SetGridx();
     //c1->SetGridy();

     //c1->SetTitle("Scattering Angle (deg)");
     //c1->SetName("3GeV muon");

     gStyle->SetOptStat(1);


   
   TFile *_file1 = new TFile("analiz6.root");
   TFile *_file2 = new TFile("analiz3.root");
   

   TH1D *h1 = (TH1D*)_file1->Get("PDF(Theta)");
   TH1D *h2 = (TH1D*)_file2->Get("PDF(Theta)");
  
   

   h1->SetFillColor(2);
   h1->SetFillStyle(3001);
   h1->SetLineColor(2);


   h2->SetFillColor(4);
   h2->SetFillStyle(3001);
   h2->SetLineColor(4);
   

  
   h1->Draw("e1");
   h2->Draw("e1,same");
  


///////////////////////////////////////////////////////////////////////
   TLegend* leg1 = new TLegend(0.1,0.7,0.48,0.9);
   leg1->SetHeader("");
   leg1->AddEntry(h1,"D = 6 m","f");
   leg1->AddEntry(h2,"D = 3 m","f");
   
   leg1->Draw();
/////////////////////////////////////////////////////////////////////
   /*TText *pt1 = new TText( 0.2, 12., "Scattering Angle");
   pt1->SetTextSize(0.03);
   pt1->SetTextFont(42);
   pt1->Draw();*/
///////////////////////////////////////////////////////////////////////
   
   return;
}

