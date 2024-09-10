#ifndef CustomComptonScattering_h
#define CustomComptonScattering_h 1

#include "G4ComptonScattering.hh"

class CustomComptonScattering : public G4ComptonScattering {
public:
    CustomComptonScattering();
    ~CustomComptonScattering();

    G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step& aStep) override;
};

#endif

