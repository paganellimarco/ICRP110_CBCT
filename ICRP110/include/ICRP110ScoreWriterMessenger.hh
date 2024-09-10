#ifndef ICRP110ScoreWriterMessenger_h
#define ICRP110ScoreWriterMessenger_h 1
#include "G4UImessenger.hh"
#include "globals.hh"

class ICRP110UserScoreWriter;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class ICRP110ScoreWriterMessenger: public G4UImessenger
{
public:
  explicit ICRP110ScoreWriterMessenger(ICRP110UserScoreWriter* myUsrScWriter);
  ~ICRP110ScoreWriterMessenger();
    
  void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
  ICRP110UserScoreWriter*    fUserScoreWriter;
  G4UIdirectory*             fPhantomDir;
  G4UIcmdWithAString*        fSexCmd;  
  G4UIcmdWithAString*        fSectionCmd;
};
#endif

