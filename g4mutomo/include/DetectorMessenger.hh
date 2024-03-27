

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

class DetectorMessenger: public G4UImessenger
{

public:

  DetectorMessenger(DetectorConstruction* );
  ~DetectorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:

  // Pointer to the detector component
  DetectorConstruction*        Detector;

  G4UIcmdWithAString*          WorldMaterCmd;
  G4UIcmdWithAString*          ScintMaterCmd;
  G4UIcmdWithAString*          TargetMaterCmd;
 

  G4UIcmdWithADoubleAndUnit*   ScintillatorXCmd;
  G4UIcmdWithADoubleAndUnit*   ScintillatorYCmd;
  G4UIcmdWithADoubleAndUnit*   ScintillatorThicknessCmd;

  G4UIcmdWithADoubleAndUnit*   Source_To_First_Detector_SurfaceCmd;
  G4UIcmdWithADoubleAndUnit*   Detector_Plane_SeparationCmd;
  G4UIcmdWithADoubleAndUnit*   Top_and_Bottom_Detectors_SeparationCmd;

  G4UIdirectory*               mutomoDir;
  G4UIdirectory*               setupDir;
};
#endif

