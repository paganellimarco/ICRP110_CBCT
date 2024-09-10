#ifndef ICRP110STANDALONEVISACTION_HH
#define ICRP110STANDALONEVISACTION_HH

#include "G4VUserVisAction.hh"

class ICRP110PhantomConstruction;

class ICRP110StandaloneVisAction: public G4VUserVisAction {
public:
  ICRP110StandaloneVisAction();
private:
  void Draw() override;
  ICRP110PhantomConstruction* fICRP110PhantomConstruction = nullptr;
};

#endif

