
// ********************************************************************
//  *EventAction.hh (Mahmutjan Litip)
// ********************************************************************


#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


// Event action class


class RunAction;
class HistoManager;
class G4Box;


class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*, HistoManager*);
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    

// related to SteppingAction   
   void AddToScint1(G4double dx, G4double dy, G4double dz, G4double dk)
  {fPosXScint1 = dx; fPosYScint1 = dy; fPosZScint1 = dz; fEkinScint1 = dk;};

  void AddToScint2(G4double dx, G4double dy, G4double dz, G4double dk)
  {fPosXScint2 = dx; fPosYScint2 = dy; fPosZScint2 = dz; fEkinScint2 = dk;};
  
  void AddToScint3(G4double dx, G4double dy, G4double dz, G4double dk)
  {fPosXScint3 = dx; fPosYScint3 = dy; fPosZScint3 = dz; fEkinScint3 = dk;};
  
  void AddToScint4(G4double dx, G4double dy, G4double dz, G4double dk)
  {fPosXScint4 = dx; fPosYScint4 = dy; fPosZScint4 = dz; fEkinScint4 = dk;};
  
  void AddToScint0(G4double dx, G4double dy, G4double dz, G4double dk)
  {fPosXScint0 = dx; fPosYScint0 = dy; fPosZScint0 = dz; fEkinScint0 = dk;};

   
  private:


    RunAction* fRunAct;
    HistoManager* fHistoManager;
    G4Box* fScintBox;

    G4double fPosXScint1, fPosYScint1, fPosZScint1, fEkinScint1;
    G4double fPosXScint2, fPosYScint2, fPosZScint2, fEkinScint2;
    G4double fPosXScint3, fPosYScint3, fPosZScint3, fEkinScint3;
    G4double fPosXScint4, fPosYScint4, fPosZScint4, fEkinScint4;
    G4double fPosXScint0, fPosYScint0, fPosZScint0, fEkinScint0;
    
};

                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
