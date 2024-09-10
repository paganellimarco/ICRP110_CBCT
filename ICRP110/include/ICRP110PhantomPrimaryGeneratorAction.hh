#ifndef ICRP110PhantomPrimaryGeneratorAction_h
#define ICRP110PhantomPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"

class G4GeneralParticleSource;
class G4Event;

class ICRP110PhantomPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ICRP110PhantomPrimaryGeneratorAction();
    ~ICRP110PhantomPrimaryGeneratorAction() override;

  public:
    void GeneratePrimaries(G4Event* anEvent) override;

  private:
    G4ParticleGun* fParticleGun;
    //G4GeneralParticleSource* fParticleGun;
};
#endif


