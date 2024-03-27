#define Analiz_cxx
#include "Analiz.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analiz::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analiz.C
//      root> Analiz t
//      root> t.Loop();       // Loop on all entries
//

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
   
  Double_t X = Xpos;
  Double_t Y = Ypos;

  // Create a 2D histogram
  TH2F* histogram2D = new TH2F("histogram2D", "2D Histogram", 100, -300, 300, 100, -150, 150);

  // Fill the histogram with the X and Y positions
  histogram2D->Fill(X, Y);

  // Draw the histogram on a canvas
  TCanvas* canvas = new TCanvas("canvas", "2D Histogram Canvas", 800, 600);
   histogram2D->Draw("COLZ");
   
}
