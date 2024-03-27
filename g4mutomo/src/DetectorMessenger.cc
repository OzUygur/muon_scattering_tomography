

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh" 
#include "G4UIcmdWithAString.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
  :Detector(detector)
{
  mutomoDir = new G4UIdirectory("/mutomo/");
  mutomoDir->SetGuidance("UI commands specific to mutomo work.");
  
  setupDir = new G4UIdirectory("/mutomo/setup/");
  setupDir->SetGuidance("setup control.");

  WorldMaterCmd = new G4UIcmdWithAString("/mutomo/setup/WorldMaterial",this);
  WorldMaterCmd -> SetGuidance("Select material for the world");
  WorldMaterCmd -> SetParameterName("choice",false);
  WorldMaterCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintMaterCmd = new G4UIcmdWithAString("/mutomo/setup/ScintMaterial",this);
  ScintMaterCmd -> SetGuidance("Select material for the Scintillator");
  ScintMaterCmd -> SetParameterName("choice",false);
  ScintMaterCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  TargetMaterCmd = new G4UIcmdWithAString("/mutomo/setup/TargetMaterial",this);
  TargetMaterCmd -> SetGuidance("Select material for the Target");
  TargetMaterCmd -> SetParameterName("choice",false);
  TargetMaterCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ScintillatorXCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/ScintillatorX",this);
  ScintillatorXCmd -> SetGuidance("Set ScintillatorX");
  ScintillatorXCmd -> SetParameterName("Size",false);
  ScintillatorXCmd -> SetDefaultUnit("mm");  
  ScintillatorXCmd -> SetUnitCandidates("mm cm");  
  ScintillatorXCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintillatorYCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/ScintillatorY",this);
  ScintillatorYCmd -> SetGuidance("Set ScintillatorY");
  ScintillatorYCmd -> SetParameterName("Size",false);
  ScintillatorYCmd -> SetDefaultUnit("mm");  
  ScintillatorYCmd -> SetUnitCandidates("mm cm");  
  ScintillatorYCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  ScintillatorThicknessCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/ScintillatorThickness",this);
  ScintillatorThicknessCmd -> SetGuidance("Set Scintillator thickness");
  ScintillatorThicknessCmd -> SetParameterName("Size",false);
  ScintillatorThicknessCmd -> SetDefaultUnit("mm");  
  ScintillatorThicknessCmd -> SetUnitCandidates("mm cm");  
  ScintillatorThicknessCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);


  Source_To_First_Detector_SurfaceCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/ssd",this);
  Source_To_First_Detector_SurfaceCmd -> SetGuidance("Source_To_First_Detector_Surface");
  Source_To_First_Detector_SurfaceCmd -> SetParameterName("Size",false);
  Source_To_First_Detector_SurfaceCmd -> SetDefaultUnit("mm");  
  Source_To_First_Detector_SurfaceCmd -> SetUnitCandidates("mm cm");  
  Source_To_First_Detector_SurfaceCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);


  Detector_Plane_SeparationCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/d",this);
  Detector_Plane_SeparationCmd -> SetGuidance("Set Detector_Plane_Separation");
  Detector_Plane_SeparationCmd -> SetParameterName("Size",false);
  Detector_Plane_SeparationCmd -> SetDefaultUnit("mm");  
  Detector_Plane_SeparationCmd -> SetUnitCandidates("mm cm");  
  Detector_Plane_SeparationCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);


  Top_and_Bottom_Detectors_SeparationCmd = new G4UIcmdWithADoubleAndUnit("/mutomo/setup/D",this);
  Top_and_Bottom_Detectors_SeparationCmd -> SetGuidance("Set Top_and_Bottom_Detectors_Separation");
  Top_and_Bottom_Detectors_SeparationCmd -> SetParameterName("Size",false);
  Top_and_Bottom_Detectors_SeparationCmd -> SetDefaultUnit("mm");  
  Top_and_Bottom_Detectors_SeparationCmd -> SetUnitCandidates("mm cm");  
  Top_and_Bottom_Detectors_SeparationCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);


}

DetectorMessenger::~DetectorMessenger()
{ 
  delete WorldMaterCmd;
  delete ScintMaterCmd;
  delete TargetMaterCmd;

  delete ScintillatorXCmd;
  delete ScintillatorYCmd;
  delete ScintillatorThicknessCmd;

  delete Source_To_First_Detector_SurfaceCmd;
  delete Detector_Plane_SeparationCmd;
  delete Top_and_Bottom_Detectors_SeparationCmd;

  delete setupDir;
  delete mutomoDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == WorldMaterCmd )
    { Detector->SetWorldMaterial(newValue);}

  if( command == ScintMaterCmd )
    { Detector->SetScintMaterial(newValue);}

  if( command == TargetMaterCmd )
    { Detector->SetTargetMaterial(newValue);}


  if( command == ScintillatorXCmd )
    { Detector -> SetScintillatorX(ScintillatorXCmd -> GetNewDoubleValue(newValue));}

  if( command == ScintillatorYCmd )
    { Detector -> SetScintillatorY(ScintillatorYCmd -> GetNewDoubleValue(newValue));}

  if( command == ScintillatorThicknessCmd )
    { Detector -> SetScintillatorThickness(ScintillatorThicknessCmd -> GetNewDoubleValue(newValue));}


  if( command == Source_To_First_Detector_SurfaceCmd )
    { Detector -> SetSource_To_First_Detector_Surface(Source_To_First_Detector_SurfaceCmd -> GetNewDoubleValue(newValue));}

  if( command == Detector_Plane_SeparationCmd )
    { Detector -> SetDetector_Plane_Separation(Detector_Plane_SeparationCmd -> GetNewDoubleValue(newValue));}

  if( command == Top_and_Bottom_Detectors_SeparationCmd )
    { Detector -> SetTop_and_Bottom_Detectors_Separation(Top_and_Bottom_Detectors_SeparationCmd -> GetNewDoubleValue(newValue));}





}

