#include "ICRP110ScoreWriterMessenger.hh"
#include "ICRP110UserScoreWriter.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"
#include "G4RunManager.hh"

ICRP110ScoreWriterMessenger::ICRP110ScoreWriterMessenger(ICRP110UserScoreWriter* myUsrScWriter)
  :fUserScoreWriter(myUsrScWriter)
{ 
  fPhantomDir = new G4UIdirectory("/phantom/");
  fPhantomDir -> SetGuidance("Set Your Phantom.");
  
  fSexCmd = new G4UIcmdWithAString("/phantom/setScoreWriterSex",this);
  fSexCmd -> SetGuidance("Set sex of Phantom: Male or Female.");
  fSexCmd -> SetParameterName("ScoreWriterSex",true);
  fSexCmd -> SetDefaultValue("female");
  fSexCmd -> SetCandidates("male female");
  fSexCmd -> AvailableForStates(G4State_PreInit,G4State_Idle); 
  
  fSectionCmd = new G4UIcmdWithAString("/phantom/setScoreWriterSection",this);
  fSectionCmd -> SetGuidance("Set section of Phantom: Head, Trunk or Full.");
  fSectionCmd -> SetParameterName("ScoreWriterSection",true);
  fSectionCmd -> SetDefaultValue("head");
  fSectionCmd -> SetCandidates("head trunk full");
  fSectionCmd -> AvailableForStates(G4State_PreInit,G4State_Idle); 
}

ICRP110ScoreWriterMessenger::~ICRP110ScoreWriterMessenger()
{
  delete  fSexCmd;
  delete  fSectionCmd;
  delete  fPhantomDir;
}

void ICRP110ScoreWriterMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{     
  if( command == fSexCmd )
    { 
     fUserScoreWriter -> SetPhantomSex(newValue); 
    }
  if( command == fSectionCmd )
    {
     fUserScoreWriter -> SetPhantomSection(newValue);
    }
}



