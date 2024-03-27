//
// ********************************************************************
//  SteppingAction.cc (Mahmutjan Litip)
// ********************************************************************

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//#include "MuonPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(
                      const DetectorConstruction* detectorConstruction,
                      EventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)

{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{


   // get volume
  G4VPhysicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // get particle name
   particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();


  // kinetic energy

  G4double ekin = step->GetPreStepPoint()->GetKineticEnergy()/GeV;

  
  // position
  G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();

  G4double X = pos.x()/cm;            
  G4double Y = pos.y()/cm;
  G4double Z = pos.z()/cm;



 if(step->GetTrack()->GetParentID() != 0 ) return; 

 if(particleName == "mu-" or particleName == "mu+"){

  if ( volume == fDetConstruction->GetScintillator1PV()){
    fEventAction->AddToScint1(X, Y, Z, ekin);
                              
                             
     }
  

  if ( volume == fDetConstruction->GetScintillator2PV()){
    fEventAction->AddToScint2(X, Y, Z, ekin);
                              
                             
     }
  

  if ( volume == fDetConstruction->GetScintillator3PV()){
    fEventAction->AddToScint3(X, Y, Z, ekin);
                              
                              
     }

  if ( volume == fDetConstruction->GetScintillator4PV()){
    fEventAction->AddToScint4(X, Y, Z, ekin);
                              
                              
    }


  if ( volume == fDetConstruction->GetScintillator0PV()){
    fEventAction->AddToScint0(X, Y, Z, ekin);
                              
                              
    }

  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
