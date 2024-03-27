//
// ********************************************************************
// * SteppingAction.hh (Mahmutjan Litip)
// ********************************************************************


#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;
class G4TouchableHistory;

// Stepping action class.

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(const DetectorConstruction* detectorConstruction,
                    EventAction* eventAction);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const DetectorConstruction* fDetConstruction;
  EventAction*  fEventAction;
  G4String particleName;
   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
