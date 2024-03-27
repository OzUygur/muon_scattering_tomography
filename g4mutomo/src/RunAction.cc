//
// ********************************************************************
// * RunAction.cc (Mahmutjan Litip)
// ********************************************************************

#include "RunAction.hh"
#include "G4Run.hh"
//#include "Run.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(HistoManager* histo) : G4UserRunAction(),
fHistoManager(histo)
{ 
  
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1); 
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{ }

/*
G4Run* RunAction::GenerateRun()
{
  return new Run; 
}
*/
//////////////////////////////////////////////////////////////////////////////////
void RunAction::BeginOfRunAction(const G4Run* )
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  
  fHistoManager->book();
}
//////////////////////////////////////////////////////////////////////////////////
void RunAction::EndOfRunAction(const G4Run* run)
{
/*
   G4int NbOfEvents = run->GetNumberOfEvent();
  const Run* aRun = static_cast<const Run*>(run);

  // Compute RMS Theta
  //
  G4double theta  = aRun->GetTheta();
  G4double theta2 = aRun->GetTheta2();
  G4double rmsTheta = theta2 - theta*theta/NbOfEvents;
  if (rmsTheta > 0.) rmsTheta = std::sqrt(rmsTheta); else rmsTheta = 0.;

  G4cout << "RMS Theta: " << rmsTheta << G4endl;
*/
  fHistoManager->save(); 

 

}

