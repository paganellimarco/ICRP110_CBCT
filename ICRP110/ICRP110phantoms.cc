#include "G4UImanager.hh"
#include "G4UIsession.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "ICRP110PhantomConstruction.hh"
#include "ICRP110PhantomActionInitialization.hh"
#include "G4ScoringManager.hh"
#include "ICRP110UserScoreWriter.hh"
#include "ICRP110PhantomVisAction.hh"
#include "QGSP_BIC_HP.hh"
#include "SimplePhysicsList.hh"
#include "G4RunManagerFactory.hh"

int main(int argc,char** argv)
{
 auto* runManager = G4RunManagerFactory::CreateRunManager();
 G4int nThreads = 48;
 runManager->SetNumberOfThreads(nThreads);
  
  // Activate UI-command base scorer
 G4ScoringManager* scorerManager = G4ScoringManager::GetScoringManager();
 scorerManager -> SetVerboseLevel(1);

//====================================================================
// Un-comment this line for user defined score writer
    //scorerManager -> SetScoreWriter(new ICRP110UserScoreWriter());
//====================================================================

 // Set mandatory initialization classes
  auto userPhantom = new ICRP110PhantomConstruction();
  runManager -> SetUserInitialization(userPhantom);
  
  runManager -> SetUserInitialization(new SimplePhysicsList());

  //runManager -> SetUserInitialization(new QGSP_BIC_HP());

 // runManager -> SetUserInitialization(new ICRP110PhantomPhysicsList);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->RegisterRunDurationUserVisAction
  ("phantom",new ICRP110PhantomVisAction(userPhantom));
  visManager -> Initialize();
 
  auto actions = new ICRP110PhantomActionInitialization();
  runManager -> SetUserInitialization(actions);

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc==1)   // Define UI session for interactive mode.
    { 
      G4cout << " UI session starts ..." << G4endl;
      auto ui = new G4UIExecutive(argc, argv);
      UImanager -> ApplyCommand("/control/execute vis.mac");     
      ui -> SessionStart();
      delete ui;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager -> ApplyCommand(command+fileName);
    }     

delete visManager;

delete runManager;

return 0;
}
