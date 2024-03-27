
// ********************************************************************
// * EventAction.cc (Mahmutjan Litip)
// ********************************************************************

#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4Event.hh"
#include "DetectorConstruction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"

#include "HistoManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run, HistoManager* histo)
 : G4UserEventAction(), fRunAct(run), fHistoManager(histo),  
 
   fPosXScint1(0.), fPosXScint2(0.), fPosXScint3(0.), fPosXScint4(0.), fPosXScint0(0.),
   fPosYScint1(0.), fPosYScint2(0.), fPosYScint3(0.), fPosYScint4(0.), fPosYScint0(0.),
   fPosZScint1(0.), fPosZScint2(0.), fPosZScint3(0.), fPosZScint4(0.), fPosZScint0(0.), 
   fEkinScint1(0.), fEkinScint2(0.), fEkinScint3(0.), fEkinScint4(0.), fEkinScint0(0.)
   
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{  
  // initialisation per event
   fPosXScint1 = 0.; fPosXScint2 = 0.; fPosXScint3 = 0.; fPosXScint4 = 0.; fPosXScint0 = 0.; 
   fPosYScint1 = 0.; fPosYScint2 = 0.; fPosYScint3 = 0.; fPosYScint4 = 0.; fPosYScint0 = 0.;
   fPosZScint1 = 0.; fPosZScint2 = 0.; fPosZScint3 = 0.; fPosZScint4 = 0.; fPosZScint0 = 0.;
   fEkinScint1 = 0.; fEkinScint2 = 0.; fEkinScint3 = 0.; fEkinScint4 = 0.; fEkinScint0 = 0.; 
   
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*event){
if(fEkinScint2 - fEkinScint3 != 0.){
//if(fEkinScint1 != 0. && fEkinScint2 != 0. && fEkinScint3 != 0. && fEkinScint4 != 0.){
//////////////////////////////////////////////////////////////////////////////////////,
fHistoManager->Fill(fPosXScint1, fPosYScint1, fPosZScint1, fEkinScint1,
                    fPosXScint2, fPosYScint2, fPosZScint2, fEkinScint2, 
                    fPosXScint3, fPosYScint3, fPosZScint3, fEkinScint3,
                    fPosXScint4, fPosYScint4, fPosZScint4, fEkinScint4,
                    fPosXScint0, fPosYScint0, fPosZScint0, fEkinScint0);



 }  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
