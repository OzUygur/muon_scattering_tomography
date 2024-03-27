//******************************************************************************
// PrimaryGeneratorAction.cc
//
// 1.00 JMV, LLNL, Jan-2007:  First version.
//******************************************************************************
//

#include <iomanip>
#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
using namespace std;

#include "G4Event.hh"

//----------------------------------------------------------------------------//
PrimaryGeneratorAction::PrimaryGeneratorAction(const char *inputfile)
: G4VUserPrimaryGeneratorAction(),
  fGun(0)

{

  // define a particle gun
  //particleGun = new G4ParticleGun();
  G4int n_particle = 1;
  fGun  = new G4ParticleGun(n_particle);

  // Read the cry input file
  std::ifstream inputFile;
  inputFile.open(inputfile,std::ios::in);
  char buffer[1000];

  if (inputFile.fail()) {
    if( *inputfile !=0)  //....only complain if a filename was given
      G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << inputfile << G4endl;
    InputState=-1;
  }else{
    std::string setupString("");
    while ( !inputFile.getline(buffer,1000).eof()) {
      setupString.append(buffer);
      setupString.append(" ");
    }

    CRYSetup *setup=new CRYSetup(setupString,"../data");

    gen = new CRYGenerator(setup);

    // set random number generator
    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
    InputState=0;
  }
  // create a vector to store the CRY particle properties
  vect=new std::vector<CRYParticle*>;

  // Create the table containing all particle names
  particleTable = G4ParticleTable::GetParticleTable();

  // Create the messenger file
  gunMessenger = new PrimaryGeneratorMessenger(this);
}
//----------------------------------------------------------------------------//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::InputCRY()
{
  InputState=1;
}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::UpdateCRY(std::string* MessInput)
{
  CRYSetup *setup=new CRYSetup(*MessInput,"../data");

  gen = new CRYGenerator(setup);

  // set random number generator
  RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
  setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
  InputState=0;

}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::CRYFromFile(G4String newValue)
{
  // Read the cry input file
  std::ifstream inputFile;
  inputFile.open(newValue,std::ios::in);
  char buffer[1000];

  if (inputFile.fail()) {
    G4cout << "Failed to open input file " << newValue << G4endl;
    G4cout << "Make sure to define the cry library on the command line" << G4endl;
    InputState=-1;
  }else{
    std::string setupString("");
    while ( !inputFile.getline(buffer,1000).eof()) {
      setupString.append(buffer);
      setupString.append(" ");
    }

    CRYSetup *setup=new CRYSetup(setupString,"../data");

    gen = new CRYGenerator(setup);

  // set random number generator
    RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
    setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
    InputState=0;
  }
}

//----------------------------------------------------------------------------//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  if (InputState != 0) {
    G4String* str = new G4String("CRY library was not successfully initialized");
    //G4Exception(*str);
    G4Exception("PrimaryGeneratorAction", "1",
                RunMustBeAborted, *str);
  }

  G4String particleName;
  vect->clear();
  gen->genEvent(vect);



  //....debug output
  /*G4cout //<< "\nEvent=" << anEvent->GetEventID() << " "
         << "--> Number of generated particles = " << vect->size()
         << G4endl;*/


  for ( unsigned j=0; j<vect->size(); j++) {
    particleName=CRYUtils::partName((*vect)[j]->id());
/*
    //....debug output  
    cout << "  "          << particleName << " "
         << "charge="      << (*vect)[j]->charge() << " "
         << setprecision(4)
         << "energy (MeV)=" << (*vect)[j]->ke()*MeV << " "
         << "pos (m)"
         << G4ThreeVector((*vect)[j]->x(), (*vect)[j]->y(), (*vect)[j]->z())
         << " " << "direction cosines "
         << G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w())
         << " " << endl;
*/
//-----------------------------------------------------------------------------------------------------
    G4double size = 1.0; 
    G4double x0 = size * (*vect)[j]->x()*m;
    G4double y0 = size * (*vect)[j]->y()*m;
    G4double z0 = size * (*vect)[j]->z()*m;
 
  
   fGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    G4double mom = 1.;
    G4double px = mom * (*vect)[j]->u();
    G4double py = mom * (*vect)[j]->v();
    G4double pz = mom * (*vect)[j]->w();

    fGun->SetParticleMomentumDirection(G4ThreeVector(px, py, -pz));
//-----------------------------------------------------------------------------------------------------


    fGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
    fGun->SetParticleEnergy((*vect)[j]->ke()*MeV);
    //fGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->y()*m, (*vect)[j]->z()*m));
    //fGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w()));
    fGun->SetParticleTime((*vect)[j]->t());
    fGun->GeneratePrimaryVertex(anEvent);
    delete (*vect)[j];
  }
}
