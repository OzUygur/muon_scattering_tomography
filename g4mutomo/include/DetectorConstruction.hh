

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorMessenger;
class G4VisAttributes;


//class G4Timer;
//class G4Event;


class DetectorConstruction : public G4VUserDetectorConstruction
{

public:

  DetectorConstruction();
  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  // get methods
  //
    const G4VPhysicalVolume* GetWorldPV() const;
    const G4VPhysicalVolume* GetScintillator1PV() const;
    const G4VPhysicalVolume* GetScintillator2PV() const;
    const G4VPhysicalVolume* GetScintillator3PV() const;
    const G4VPhysicalVolume* GetScintillator4PV() const;
    const G4VPhysicalVolume* GetScintillator0PV() const;

    const G4VPhysicalVolume* GetSampleBox1PV() const;
    const G4VPhysicalVolume* GetSampleBox2PV() const;
    const G4VPhysicalVolume* GetSampleBox3PV() const;
    const G4VPhysicalVolume* GetSampleBox4PV() const;



    G4double GetTop_and_Bottom_Detectors_Separation() const {return Top_and_Bottom_Detectors_Separation;};
    G4double GetDetector_Plane_Separation() const {return Detector_Plane_Separation;};

  
 

private: 

  void ConstructDetector();

public: 

  void SetWorldMaterial (G4String value);
  void SetScintMaterial (G4String value);
  void SetTargetMaterial (G4String value);

  void SetScintillatorX (G4double value);
  void SetScintillatorY (G4double value);
  void SetScintillatorThickness (G4double value);

  void SetSource_To_First_Detector_Surface (G4double value);
  void SetDetector_Plane_Separation (G4double value);
  void SetTop_and_Bottom_Detectors_Separation (G4double value);

private:

  G4VisAttributes* blue;
  G4VisAttributes* skyblue;
  G4VisAttributes* red;
  G4VisAttributes* green;
  G4VisAttributes* darkOrange;
  G4VisAttributes* yellow;
  G4VisAttributes* pink;
  G4VisAttributes* grey;

  G4Material*         WorldMaterial;
  G4Material*         ScintMaterial;
  G4Material*         TargetMaterial;
  
  G4LogicalVolume*    WorldLV;
  G4VPhysicalVolume*  fWorldPV;

  G4LogicalVolume*    EnvelopeLV;
  G4VPhysicalVolume*  EnvelopePV;

  G4LogicalVolume*    Scintillator1LV;
  G4VPhysicalVolume*  fScintillator1PV;

  G4LogicalVolume*    Scintillator2LV;
  G4VPhysicalVolume*  fScintillator2PV;

  G4LogicalVolume*    Scintillator3LV;
  G4VPhysicalVolume*  fScintillator3PV;

  G4LogicalVolume*    Scintillator4LV;
  G4VPhysicalVolume*  fScintillator4PV;

  G4LogicalVolume*    Scintillator0LV;
  G4VPhysicalVolume*  fScintillator0PV;

  G4LogicalVolume*    TargetBoxLV;
  //G4VPhysicalVolume*  fTargetBoxPV;

  G4LogicalVolume*    SampleBox1LV;
  G4VPhysicalVolume*  fSampleBox1PV;
  G4LogicalVolume*    SampleBox2LV;
  G4VPhysicalVolume*  fSampleBox2PV;
  G4LogicalVolume*    SampleBox3LV;
  G4VPhysicalVolume*  fSampleBox3PV;
  G4LogicalVolume*    SampleBox4LV;
  G4VPhysicalVolume*  fSampleBox4PV;


  DetectorMessenger*  detectorMessenger; 

  G4double            ScintillatorX;
  G4double            ScintillatorY;
  G4double            ScintillatorThickness;
  G4double            Detector_Plane_Separation;
  G4double            Top_and_Bottom_Detectors_Separation;
  G4double            Source_To_First_Detector_Surface;

  std::vector<G4VisAttributes*> fVisAttributes;

  //G4Timer* fTimer;
   //G4Event* event;

  
};


inline const G4VPhysicalVolume* DetectorConstruction::GetWorldPV() const { 
  return fWorldPV; 
}

inline const G4VPhysicalVolume* DetectorConstruction::GetScintillator1PV() const { 
  return fScintillator1PV; 
}

inline const G4VPhysicalVolume* DetectorConstruction::GetScintillator2PV() const { 
  return fScintillator2PV; 
}

inline const G4VPhysicalVolume* DetectorConstruction::GetScintillator3PV() const { 
  return fScintillator3PV; 
}

inline const G4VPhysicalVolume* DetectorConstruction::GetScintillator4PV() const { 
  return fScintillator4PV; 
}

inline const G4VPhysicalVolume* DetectorConstruction::GetScintillator0PV() const { 
  return fScintillator0PV; 
}



#endif

