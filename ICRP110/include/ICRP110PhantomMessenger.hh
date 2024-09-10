#ifndef ICRP110PhantomMessenger_h
#define ICRP110PhantomMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
class ICRP110PhantomConstruction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;

class ICRP110PhantomMessenger: public G4UImessenger
{
public:
  explicit ICRP110PhantomMessenger(ICRP110PhantomConstruction* myUsrPhtm);
  ~ICRP110PhantomMessenger();    
  void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
  ICRP110PhantomConstruction*    fUserPhantom;
  G4UIdirectory*                 fPhantomDir;
  G4UIcmdWithAString*            fSexCmd; 
  G4UIcmdWithAString*            fSectionCmd;
};
#endif

