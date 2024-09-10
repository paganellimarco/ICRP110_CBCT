#ifndef CustomPhotoElectricEffect_h
#define CustomPhotoElectricEffect_h 1

#include "G4PhotoElectricEffect.hh"

class CustomPhotoElectricEffect : public G4PhotoElectricEffect {
public:
    CustomPhotoElectricEffect();
    ~CustomPhotoElectricEffect();

    G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step& aStep) override;
};

#endif

