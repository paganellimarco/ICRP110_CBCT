#ifndef SIMPLEPHYSICSLIST_HH
#define SIMPLEPHYSICSLIST_HH

#include "G4SystemOfUnits.hh"
#include "G4VModularPhysicsList.hh"

class SimplePhysicsList : public G4VModularPhysicsList {
public:
    SimplePhysicsList();
    virtual ~SimplePhysicsList();

    // Override dei metodi virtuali
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
};

#endif

