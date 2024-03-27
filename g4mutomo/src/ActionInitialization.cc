//
// ********************************************************************
// * ActionInitialization.cc (Mahmutjan Litip)                       *

// ********************************************************************

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization
                            (DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
   // Histo manager
  HistoManager*  histo = new HistoManager();
  
  // Actions
  SetUserAction(new RunAction(histo));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{

  // Histo manager
  HistoManager*  histo = new HistoManager();
  
  // Actions
  //
  SetUserAction(new PrimaryGeneratorAction(""));
  
  RunAction* runAction = new RunAction(histo);  
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction(runAction, histo);
  SetUserAction(eventAction);

  SteppingAction* steppingAction = new SteppingAction(fDetConstruction, eventAction);
  SetUserAction(steppingAction);
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
