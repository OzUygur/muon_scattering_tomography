
// Version   : Geant4.10.1
// Author    : Mahmutjan Litip (IRADETS)

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
//#include "RunAction.hh"
//#include "EventAction.hh"
//#include "G4Run.hh"
//#include "G4Step.hh"
#include "G4Event.hh"


#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SubtractionSolid.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"

//#include "G4Timer.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"





////////////////////////////////////////////////////////////////////////////
DetectorConstruction::DetectorConstruction(): 

        WorldLV(0), fWorldPV(0),
        Scintillator1LV(0), fScintillator1PV(0),
        Scintillator2LV(0), fScintillator2PV(0),
        Scintillator3LV(0), fScintillator3PV(0),
        Scintillator4LV(0), fScintillator4PV(0),
        Scintillator0LV(0), fScintillator0PV(0),

        SampleBox1LV(0),     fSampleBox1PV(0),
        SampleBox2LV(0),     fSampleBox2PV(0),
        SampleBox3LV(0),     fSampleBox3PV(0),
        SampleBox4LV(0),     fSampleBox4PV(0)

        //TargetBoxLV(0)
        //fTimer(0)


/*
        fScoringVolume1(0),
        fScoringVolume2(0),
        fScoringVolume3(0),
        fScoringVolume4(0)
*/



{
    //fTimer = new G4Timer;
   
    // Default dimensions
  
    ScintillatorX   =  6.0 * m;
    ScintillatorY   =  3.0 * m;
    ScintillatorThickness = 10.0 * mm;
     
    Source_To_First_Detector_Surface = 0.5*m;
    Detector_Plane_Separation = 30.*cm;
    Top_and_Bottom_Detectors_Separation = 300.*cm;




    // Messenger to change parameters of the geometry

    //WorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_AIR" );
    //ScintMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_PLASTIC_SC_VINYLTOLUENE" );
    //TargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_PLASTIC_SC_VINYLTOLUENE" );
     
    WorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_Galactic" );
    ScintMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_Galactic" );
    TargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( "G4_Galactic" );




    detectorMessenger = new DetectorMessenger ( this );

}
/////////////////////////////////////////////////////////////////////////////
DetectorConstruction::~DetectorConstruction()
{
    delete detectorMessenger;
    //delete fTimer;
    for (auto visAttributes: fVisAttributes) {
    delete visAttributes;
  }
}

/////////////////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorConstruction::Construct()
{

    // Cleanup old geometry

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4RunManager::GetRunManager()->ReinitializeGeometry();  

    ConstructDetector();
    return fWorldPV;
}

/////////////////////////////////////////////////////////////////////////////
void DetectorConstruction::ConstructDetector()
{
    //---------------------------------
    // define materials
    //---------------------------------

    //---------------------------------
    // Treatment room - World volume
    //---------------------------------

    const G4double  WorldX = 10.0 * m;		
    const G4double  WorldY = 10.0 * m;
    const G4double  WorldZ = 20.0* m;

    /*const G4double ContainerX = 4.*m;
    const G4double ContainerY = 4.*m;
    const G4double ContainerZ = 2.9*m;*/

    G4double ssd = Source_To_First_Detector_Surface;                   //(source to scint1)
    G4double d = Detector_Plane_Separation;                            //(scint1 to scint2 && scint3 to scint4)
    G4double D = Top_and_Bottom_Detectors_Separation;                  //(scint2 to scint3)

    //G4double ssd = (WorldZ/2-D)/2;                    

    
    G4double SourceToScint1 = ssd + ScintillatorThickness/2;          // muon source plane is just 0.0*m up from the first detector plane
    G4double SourceToScint2 = SourceToScint1 + d; 
    G4double SourceToScint3 = SourceToScint2 + D; 
    G4double SourceToScint4 = SourceToScint3 + d; 

    const G4double  ThreatZPos = ssd + 2.0*m;

    
   
    //---------------------------------
    // World
    //---------------------------------

    G4Box* World = new G4Box ( "World", WorldX/2, WorldY/2, WorldZ/2 );
    WorldLV = new G4LogicalVolume ( World, WorldMaterial, "WorldLV", 0, 0, 0 );
    fWorldPV = new G4PVPlacement ( 0, G4ThreeVector(0,0,0), "fWorldPV", WorldLV, 0, false, 0 );



    //---------------------------------
    // Scintillators[i=4]
    //--------------------------------- 
   
    G4Box* ScintillatorS   = new G4Box ( "Scintillator", ScintillatorX/2, ScintillatorY/2, ScintillatorThickness/2);

    // Scintillator1
    Scintillator1LV  = new G4LogicalVolume ( ScintillatorS, ScintMaterial, "Scintillator1LV",0,0,0);
    fScintillator1PV = new G4PVPlacement (0,G4ThreeVector(0.,0, SourceToScint1), "Scintillator1PV", Scintillator1LV,fWorldPV,false,0);
    //fScoringVolume1 = Scintillator1LV;

    // Scintillator2
    Scintillator2LV  = new G4LogicalVolume( ScintillatorS, ScintMaterial, "Scintillator2LV",0,0,0);
    fScintillator2PV = new G4PVPlacement(0,G4ThreeVector(0.,0, SourceToScint2), "Scintillator2PV", Scintillator2LV,fWorldPV,false,0);
    //fScoringVolume2 = Scintillator2LV;

    // Scintillator3
    Scintillator3LV  = new G4LogicalVolume( ScintillatorS, ScintMaterial, "Scintillator3LV",0,0,0);
    fScintillator3PV = new G4PVPlacement(0,G4ThreeVector(0.,0, SourceToScint3), "Scintillator3PV", Scintillator3LV,fWorldPV,false,0);
    //fScoringVolume3 = Scintillator3LV;

    // Scintillator4
    Scintillator4LV  = new G4LogicalVolume( ScintillatorS, ScintMaterial, "Scintillator4PV",0,0,0);
    fScintillator4PV = new G4PVPlacement(0,G4ThreeVector(0.,0, SourceToScint4),"Scintillator4PV", Scintillator4LV,fWorldPV,false,0);
    //fScoringVolume4 = Scintillator4LV;


//---------------------------------------------------------------------------------------------------

/*

  //~~~~~~~~~~~~~~//                               
  //  Shield Box  //
  //~~~~~~~~~~~~~~//                               
  G4double ShieldSizeXY = 20.*cm;
  G4double ShieldSizeZ = 1.0*cm;
  G4Material* ShieldBox_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
  
  G4VSolid* ShieldBoxS = new G4Box("ShieldBox",ShieldSizeXY/2, ShieldSizeXY/2, ShieldSizeZ/2);
  G4LogicalVolume* ShieldBoxLV = new G4LogicalVolume(ShieldBoxS,ShieldBox_mat,"ShieldBox");
  new G4PVPlacement(0,G4ThreeVector(0., 0., ThreatZPos-12.*cm), ShieldBoxLV, "ShieldBox", WorldLV, false, 0);
  new G4PVPlacement(0,G4ThreeVector(0., 0., ThreatZPos+12.*cm), ShieldBoxLV, "ShieldBox", WorldLV, false, 0);


  //~~~~~~~~~~~~~~//                               
  // Sample Boxes//
  //~~~~~~~~~~~~~~// 
                              
  G4Material* SampleMaterial1 = G4NistManager::Instance()->FindOrBuildMaterial("G4_U");
  G4Material* SampleMaterial2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
  G4Material* SampleMaterial3 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
  G4Material* SampleMaterial4 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

  G4double  boxsize = 10.*cm;
  G4VSolid* SampleBox1S = new G4Box("SampleBox1",boxsize/2, boxsize/2, boxsize/2);
  SampleBox1LV = new G4LogicalVolume(SampleBox1S,SampleMaterial1,"SampleBox1");
  fSampleBox1PV = new G4PVPlacement(0,G4ThreeVector(0., 100.*cm, ThreatZPos), SampleBox1LV, "SampleBox1", WorldLV, false,0);

  G4VSolid* SampleBox2S = new G4Box("SampleBox2",boxsize/2, boxsize/2, boxsize/2);
  SampleBox2LV = new G4LogicalVolume(SampleBox2S,SampleMaterial2,"SampleBox2");
  fSampleBox2PV = new G4PVPlacement(0,G4ThreeVector(100.*cm, 0., ThreatZPos), SampleBox2LV, "SampleBox2", WorldLV, false,0);

  G4VSolid* SampleBox3S = new G4Box("SampleBox3",boxsize/2, boxsize/2, boxsize/2);
  SampleBox3LV = new G4LogicalVolume(SampleBox3S,SampleMaterial3,"SampleBox3");
  fSampleBox3PV = new G4PVPlacement(0,G4ThreeVector(-100.*cm, 0., ThreatZPos), SampleBox3LV, "SampleBox3", WorldLV, false,0);


  G4VSolid* SampleBox4S = new G4Box("SampleBox4",boxsize/2, boxsize/2, boxsize/2);
  SampleBox4LV = new G4LogicalVolume(SampleBox4S,SampleMaterial4,"SampleBox4");
  fSampleBox4PV = new G4PVPlacement(0,G4ThreeVector(0., -100.*cm,  ThreatZPos), SampleBox4LV, "SampleBox4", WorldLV, false,0);




  //~~~~~~~~~~~~~~//                               
  // Sample Tube  //
  //~~~~~~~~~~~~~~//  
    G4double r1_out = 5.*cm; 
    G4double r1_in = 0.*cm; 
    G4double hz = 5.*cm;
    G4double startingangle = 0.*degree;
    G4double spanningangle = 360.*degree;
 
    
    G4Material* SampleTube_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_U");

    G4Tubs* SampleTubeS   = new G4Tubs ( "SampleTube", r1_in, r1_out, hz, startingangle, spanningangle);
    G4LogicalVolume*SampleTubeLV  = new G4LogicalVolume (SampleTubeS, SampleTube_mat, "SampleTube");
    new G4PVPlacement (0, G4ThreeVector(0.*cm, 0.*cm, ThreatZPos), SampleTubeLV,"SampleTube", WorldLV,false,0);

//---------------------------------------------------------------------------------------------------

 

   // Referance Scintillator Plane

    //G4Box* RefS   = new G4Box ( "Scintillator0", ScintillatorX/2, ScintillatorY/2, ScintillatorThickness/2);
    //G4Box* RefS   = new G4Box ( "RefScint", ScintillatorX/2, ScintillatorY/2, D/2-ScintillatorThickness/2);
    //G4Box* RefS   = new G4Box ( "RefScint", 10.*cm, 10.*cm, 10.*cm);

    //Scintillator0LV  = new G4LogicalVolume(RefS, TargetMaterial, "Scintillator0LV",0,0,0);
    //G4RotationMatrix* RY = new G4RotationMatrix();
    //RY->rotateY(45*deg);
    //fScintillator0PV = new G4PVPlacement(0,G4ThreeVector(0,0, SourceToScint2+D/2),"Scintillator0PV", Scintillator0LV,fWorldPV,false,0);
    //fScoringVolumeR = Scintillator0LV;

  
 
*/
//---------------------------------------------------------------------------------------------------

 

/*

    //---------------------------------
    // Container
    //---------------------------------

    G4Box* ContainerS   = new G4Box ( "Container", ContainerX/2, ContainerY/2, ContainerZ/2);
    G4LogicalVolume* ContainerLV  = new G4LogicalVolume ( ContainerS, WorldMaterial, "ContainerLV",0,0,0);
    new G4PVPlacement (0,G4ThreeVector(0.,0, SourceToScint2+D/2), "ContainerPV", ContainerLV,fWorldPV,false,0);
 


  G4double VoxelSize = ContainerY/400;

  G4double XLayerSizeX = ContainerX;
  G4double XLayerSizeY = VoxelSize;
  G4double XLayerSizeZ = VoxelSize;


  G4double PLayerSizeX = ContainerX;
  G4double PLayerSizeY = ContainerY;
  G4double PLayerSizeZ = VoxelSize;


  G4int NbOfPLayers = ContainerZ/PLayerSizeZ;
  G4int NbOfXLayers = PLayerSizeX/VoxelSize;
  G4int NbOfVoxels = XLayerSizeX/VoxelSize;



   // PLayer

  G4Box* solidPLayer = new G4Box ( "PLayer", PLayerSizeX / 2, PLayerSizeY / 2, PLayerSizeZ / 2);
  G4LogicalVolume* PLayerLV = new G4LogicalVolume ( solidPLayer, WorldMaterial, "PLayer", 0, 0, 0 );
  //G4VPhysicalVolume* PLayerPV =  new G4PVPlacement ( 0, G4ThreeVector ( ), "PLayer", PLayerLV,  PhantomPV, false, 0);

   new G4PVReplica ("PLayer",                                  //its name
                                           PLayerLV,           //its Logical volume
                                           ContainerLV,          //its mother
                                           kZAxis,             //axis of replication
                                           NbOfPLayers,        //number of replica
                                           VoxelSize);         //witdth of replica

  

  // XLayer

  G4Box* solidXLayer = new G4Box ( "XLayer", XLayerSizeX / 2, XLayerSizeY / 2, XLayerSizeZ / 2);
  G4LogicalVolume* XLayerLV = new G4LogicalVolume ( solidXLayer, WorldMaterial, "XLayer", 0, 0, 0 );
  //G4VPhysicalVolume* XLayerPV = new G4PVPlacement ( 0, G4ThreeVector ( ), "XLayer", XLayerLV,  PLayerPV, false, 0);


  new G4PVReplica ("XLayer",                                  //its name
                                           XLayerLV,           //its Logical volume
                                           PLayerLV,          //its mother
                                           kYAxis,             //axis of replication
                                           NbOfXLayers,        //number of replica
                                           VoxelSize);          //witdth of replica



  // Voxels

  G4Box* solidVoxel = new G4Box ( "Voxel", VoxelSize / 2, VoxelSize / 2, VoxelSize / 2);
  G4LogicalVolume* VoxelLV = new G4LogicalVolume ( solidVoxel, WorldMaterial, "Voxel", 0, 0, 0 );
  //new G4PVPlacement ( 0, G4ThreeVector ( ), "Voxel", VoxelLV,  XLayerPV, false, 0);


   new G4PVReplica ("Voxel",                                  //its name
                                           VoxelLV,           //its Logical volume
                                           XLayerLV,          //its mother
                                           kXAxis,             //axis of replication
                                           NbOfVoxels,        //number of replica
                                           VoxelSize);          //witdth of replica



 

    
  //~~~~~~~~~~~~~~//                               
  //High-Z element//
  //~~~~~~~~~~~~~~//

    for (G4int i=0;i<10;i++)
    for (G4int j=0;j<5;j++)
    
    {                  // beginning of the for loop->

        G4double longer = (i-4)*4.*cm;   //  longer side
        G4double shorter = (j-2)*4.*cm;   // shorter side

  G4double voxel = 4.*cm;  


  G4double ThreatZPos = SourceToScint2+D/2;     
 
 //1) element1

 //...Material(M).......................................................... 
  G4Material* MThreat_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pd");

  G4VSolid* MThreatS = new G4Box("MThreat",voxel/2, voxel/2, voxel/2);
  G4LogicalVolume* MThreatLV = new G4LogicalVolume(MThreatS,MThreat_mat,"MThreat");
    new G4PVPlacement(0,G4ThreeVector(0.8*m+5*voxel, longer, ThreatZPos), MThreatLV, "MThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(0.8*m+shorter+2*voxel,shorter+2*voxel , ThreatZPos), MThreatLV, "MThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(0.8*m-5*voxel, longer, ThreatZPos), MThreatLV, "MThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(0.8*m+shorter-2*voxel,-shorter+2*voxel, ThreatZPos), MThreatLV, "MThreat", WorldLV, false, 0);
 
 //2) element2 
 //...Material(U)........................................................
  G4Material* UThreat_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pd");

  G4VSolid* UThreatS = new G4Box("UThreat",voxel/2, voxel/2, voxel/2);
  G4LogicalVolume* UThreatLV = new G4LogicalVolume(UThreatS,UThreat_mat,"UThreat");
    new G4PVPlacement(0,G4ThreeVector(0.25*m+3*voxel, longer, ThreatZPos), UThreatLV, "UThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(0.25*m+shorter, -4*voxel, ThreatZPos), UThreatLV, "UThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(0.25*m-3*voxel, longer, ThreatZPos), UThreatLV, "UThreat", WorldLV, false, 0);

   
    
//3) element3 
 //...Material(O)........................................................
  G4Material* OThreat_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pd");

  G4VSolid* OThreatS = new G4Box("OThreat",voxel/2, voxel/2, voxel/2);
  G4LogicalVolume* OThreatLV = new G4LogicalVolume(OThreatS,OThreat_mat,"OThreat");
    new G4PVPlacement(0,G4ThreeVector(-0.25*m+3*voxel, longer, ThreatZPos), OThreatLV, "OThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(-0.25*m+shorter, -4*voxel, ThreatZPos), OThreatLV, "OThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(-0.25*m-3*voxel, longer, ThreatZPos), OThreatLV, "OThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(-0.25*m+shorter, 5*voxel, ThreatZPos), OThreatLV, "OThreat", WorldLV, false, 0);


//4) element4
 //...Material(N).......................................................... 
  
    G4Material* NThreat_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pd");
    G4VSolid* NThreatS = new G4Box("NThreat",voxel/2, voxel/2, voxel/2);
    G4LogicalVolume* NThreatLV = new G4LogicalVolume(NThreatS,NThreat_mat,"NThreat");
    new G4PVPlacement(0,G4ThreeVector(-0.8*m+5*voxel, longer, ThreatZPos), NThreatLV, "NThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(-0.8*m+longer, longer, ThreatZPos), NThreatLV, "NThreat", WorldLV, false, 0);
    new G4PVPlacement(0,G4ThreeVector(-0.8*m-5*voxel, longer, ThreatZPos), NThreatLV, "NThreat", WorldLV, false, 0);



      
       }               // <-end of the for loop
   


  */


    //---------------------------------
    // Visualization attributes
    //---------------------------------

    green = new G4VisAttributes ( G4Colour ( 25 / 255. , 255 / 255. ,  25 / 255. ) );

    blue = new G4VisAttributes ( G4Colour ( 0 / 255. , 0 / 255. ,  235 / 255. ) );

    skyblue = new G4VisAttributes ( G4Colour ( 135 / 255. , 206 / 255. ,  235 / 255. ) );

    darkOrange = new G4VisAttributes ( G4Colour ( 205 / 255. , 102 / 255. ,  000 / 255. ) );

    red = new G4VisAttributes ( G4Colour ( 255 / 255., 0 / 255. , 0 / 255. ) );

    yellow = new G4VisAttributes ( G4Colour ( 255 / 255., 255 / 255. , 0 / 255. ) );

    pink = new G4VisAttributes ( G4Colour ( 255 / 255., 0 / 255. , 255 / 255. ) );

    grey = new G4VisAttributes ( G4Colour ( 75 / 255., 75 / 255. , 75 / 255. ) );

    //WorldLV -> SetVisAttributes ( G4VisAttributes::Invisible );
     //World -> SetVisibility(false);
    //Scintillator0LV-> SetVisAttributes (pink);
    
  auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visAttributes->SetVisibility(false);
  
  WorldLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);


 


    //---------------------------------
    // Display parameters
    //---------------------------------

    G4cout << " =========================================================================================" << G4endl;
    G4cout << G4endl << * ( G4Material::GetMaterialTable() ) << G4endl;
    G4cout << " =========================================================================================" << G4endl;
    G4cout << "  World size                    : " << WorldX / cm << " X " << WorldY / cm << " X " << WorldZ / cm << " cm3 " << G4endl;
    G4cout << " =========================================================================================" << G4endl;

}




/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetWorldMaterial ( G4String materialChoice )
{
    G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( materialChoice );
    if ( pttoMaterial ) {
        WorldMaterial = pttoMaterial;
        if ( WorldLV ) {
            WorldLV->SetMaterial ( WorldMaterial );
            G4RunManager::GetRunManager()->PhysicsHasBeenModified();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetScintMaterial ( G4String materialChoice )
{



    
    G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( materialChoice );
    if ( pttoMaterial ) {
        ScintMaterial = pttoMaterial;

        if ( Scintillator1LV && Scintillator2LV && Scintillator3LV && Scintillator4LV ) {
             Scintillator1LV->SetMaterial ( ScintMaterial );
             Scintillator2LV->SetMaterial ( ScintMaterial );
             Scintillator3LV->SetMaterial ( ScintMaterial );
             Scintillator4LV->SetMaterial ( ScintMaterial );
            G4RunManager::GetRunManager()->PhysicsHasBeenModified();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetTargetMaterial ( G4String materialChoice )
{
    G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial ( materialChoice );
    if ( pttoMaterial ) {
        TargetMaterial = pttoMaterial;
        if ( TargetBoxLV ) {
            TargetBoxLV->SetMaterial ( TargetMaterial );
            G4RunManager::GetRunManager()->PhysicsHasBeenModified();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void DetectorConstruction::SetScintillatorX ( G4double value ) {
    ScintillatorX = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetScintillatorY ( G4double value ) {
    ScintillatorY = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetScintillatorThickness ( G4double value ) {
    ScintillatorThickness = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetSource_To_First_Detector_Surface( G4double value ) {
    Source_To_First_Detector_Surface = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetDetector_Plane_Separation( G4double value ) {
    Detector_Plane_Separation = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::SetTop_and_Bottom_Detectors_Separation( G4double value ) {
    Top_and_Bottom_Detectors_Separation = value;
    G4RunManager::GetRunManager() -> ReinitializeGeometry();
}

/////////////////////////////////////////////////////////////////////////////





