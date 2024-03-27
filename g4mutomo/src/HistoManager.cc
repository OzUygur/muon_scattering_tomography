
#include "HistoManager.hh"
#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


HistoManager::HistoManager()
{
  fFileName[0] = "analiz.csv";
  fFactoryOn = false;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::book()
{
  // Create or get analysis manager

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(2);
   // Default settings
  analysisManager->SetNtupleMerging(true);
     // Note: merging ntuples is available only with Root output
  analysisManager->SetFileName("analiz");

      

  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile(fFileName[0]);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " << fFileName 
           << G4endl;
    return;
  }
  

  //analysisManager->SetFirstNtupleId(1);
                         
  // Create 1st ntuple (id = 1)
  
  analysisManager->CreateNtuple("Data", "Ntuple");
 
  analysisManager->CreateNtupleDColumn("posX1");
  analysisManager->CreateNtupleDColumn("posY1");
  analysisManager->CreateNtupleDColumn("posZ1");
  analysisManager->CreateNtupleDColumn("Ekin1");

  
  analysisManager->CreateNtupleDColumn("posX2");
  analysisManager->CreateNtupleDColumn("posY2");
  analysisManager->CreateNtupleDColumn("posZ2");
  analysisManager->CreateNtupleDColumn("Ekin2");

  
  analysisManager->CreateNtupleDColumn("posX3");
  analysisManager->CreateNtupleDColumn("posY3");
  analysisManager->CreateNtupleDColumn("posZ3");
  analysisManager->CreateNtupleDColumn("Ekin3");

  
  analysisManager->CreateNtupleDColumn("posX4");
  analysisManager->CreateNtupleDColumn("posY4");
  analysisManager->CreateNtupleDColumn("posZ4");
  analysisManager->CreateNtupleDColumn("Ekin4");

  
  analysisManager->CreateNtupleDColumn("posX0");
  analysisManager->CreateNtupleDColumn("posY0");
  analysisManager->CreateNtupleDColumn("posZ0");
  analysisManager->CreateNtupleDColumn("Ekin0");
  analysisManager->FinishNtuple();
  
  
  fFactoryOn = true;       
  G4cout << "\n----> Histogram Tree is opened in " << fFileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::save()
{
  if (fFactoryOn) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->Write();
    analysisManager->CloseFile();  
    G4cout << "\n----> Histogram Tree is saved in " << fFileName << G4endl;
      
    delete G4AnalysisManager::Instance();
    fFactoryOn = false;
  }                    
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


  //Fill Ntuple
void HistoManager::Fill(G4double posX1, G4double posY1, G4double posZ1, G4double Ekin1,
                        G4double posX2, G4double posY2, G4double posZ2, G4double Ekin2,
                        G4double posX3, G4double posY3, G4double posZ3, G4double Ekin3,
                        G4double posX4, G4double posY4, G4double posZ4, G4double Ekin4,
                        G4double posX0, G4double posY0, G4double posZ0, G4double Ekin0) {

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Fill Ntuple for Detector 1
    analysisManager->FillNtupleDColumn(0, posX1);
    analysisManager->FillNtupleDColumn(1, posY1);
    analysisManager->FillNtupleDColumn(2, posZ1);
    analysisManager->FillNtupleDColumn(3, Ekin1);

    // Fill Ntuple for Detector 2
    analysisManager->FillNtupleDColumn(4, posX2);
    analysisManager->FillNtupleDColumn(5, posY2);
    analysisManager->FillNtupleDColumn(6, posZ2);
    analysisManager->FillNtupleDColumn(7, Ekin2);

    // Fill Ntuple for Detector 3
    analysisManager->FillNtupleDColumn(8, posX3);
    analysisManager->FillNtupleDColumn(9, posY3);
    analysisManager->FillNtupleDColumn(10, posZ3);
    analysisManager->FillNtupleDColumn(11, Ekin3);

    // Fill Ntuple for Detector 4
    analysisManager->FillNtupleDColumn(12, posX4);
    analysisManager->FillNtupleDColumn(13, posY4);
    analysisManager->FillNtupleDColumn(14, posZ4);
    analysisManager->FillNtupleDColumn(15, Ekin4);

    // Fill Ntuple for Central Detector (assuming ID 0)
    analysisManager->FillNtupleDColumn(16, posX0);
    analysisManager->FillNtupleDColumn(17, posY0);
    analysisManager->FillNtupleDColumn(18, posZ0);
    analysisManager->FillNtupleDColumn(19, Ekin0);
    
    analysisManager->AddNtupleRow( );
  
}

  


