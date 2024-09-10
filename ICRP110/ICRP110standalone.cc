//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4VisExecutive.hh"
#include "G4VisExtent.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"

#include "ICRP110StandaloneVisAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->RegisterRunDurationUserVisAction
    ("ICRP110_HumanPhantoms standalone example",
     new ICRP110StandaloneVisAction,
     G4VisExtent(-1*m,1*m,-1*m,1*m,-1*m,1*m));
  visManager->Initialize ();

  G4UImanager::GetUIpointer()->ApplyCommand ("/control/execute standalone.mac");
  ui->SessionStart();

  delete ui;
  delete visManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

