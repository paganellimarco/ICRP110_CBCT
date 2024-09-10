#include "ICRP110StandaloneVisAction.hh"

#include "ICRP110PhantomConstruction.hh"
#include "ICRP110PhantomMessenger.hh"
#include "G4VVisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ICRP110StandaloneVisAction::ICRP110StandaloneVisAction()
{
  fICRP110PhantomConstruction = new ICRP110PhantomConstruction;
  new ICRP110PhantomMessenger(fICRP110PhantomConstruction);
  // Don't instantiate the detector here - give time for /phantom/ commands.
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ICRP110StandaloneVisAction::Draw() {
  // Instantiate the detector "just in time" *after* possible /phantom/ commands.
  // Instantiatie as "static" so that it is instantiated only once.
  static auto theWorld = fICRP110PhantomConstruction->Construct();
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if (pVisManager) {
    pVisManager->DrawGeometry(theWorld);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
