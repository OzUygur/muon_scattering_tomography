
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "G4AnalysisManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const G4int MaxHisto = 60;
const G4int MaxNtCol = 50;

class G4Run;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:

    HistoManager();
   ~HistoManager();

    void book();
    void save();

    void Fill(G4double posX1, G4double posY1, G4double posZ1, G4double Ekin1,   
              G4double posX2, G4double posY2, G4double posZ2, G4double Ekin2,  
              G4double posX3, G4double posY3, G4double posZ3, G4double Ekin3,  
              G4double posX4, G4double posY4, G4double posZ4, G4double Ekin4,   
              G4double posX0, G4double posY0, G4double posZ0, G4double Ekin0);
              
                         
    //void PrintStatistic(); 

  private:

    G4String      fFileName[2];
    G4bool        fFactoryOn;    

    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

