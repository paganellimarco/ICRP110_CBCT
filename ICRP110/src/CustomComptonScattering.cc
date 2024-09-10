#include "CustomComptonScattering.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleChange.hh"

CustomComptonScattering::CustomComptonScattering() : G4ComptonScattering() {}

CustomComptonScattering::~CustomComptonScattering() {}

G4VParticleChange* CustomComptonScattering::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep) {
    G4VParticleChange* particleChange = G4ComptonScattering::PostStepDoIt(aTrack, aStep);

    // Uccidi la particella primaria
    particleChange->ProposeTrackStatus(fStopAndKill);

    // Uccidi eventuali particelle secondarie
    for (size_t i = 0; i < particleChange->GetNumberOfSecondaries(); ++i) {
        particleChange->GetSecondary(i)->SetTrackStatus(fStopAndKill);
    }

    return particleChange;
}

