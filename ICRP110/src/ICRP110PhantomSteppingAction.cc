#include "ICRP110PhantomSteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

ICRP110PhantomSteppingAction::ICRP110PhantomSteppingAction(ICRP110PhantomAnalysisManager* analysisManager) :
    G4UserSteppingAction(), fAnalysisManager(analysisManager) {}

ICRP110PhantomSteppingAction::~ICRP110PhantomSteppingAction() {}

void ICRP110PhantomSteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    
    if (track->GetDefinition()->GetParticleName() == "gamma") {
        G4ThreeVector position = track->GetPosition();
        double x = position.x() / cm;
        double y = position.y() / cm;
        double z = position.z() / cm;
        G4StepPoint* preStepPoint = step->GetPreStepPoint();
        G4StepPoint* postStepPoint = step->GetPostStepPoint();
        
        if (z  > 80.  && z < 81. ){
           //if (x > -35.  && x < 35.  && y > -35.  && y < 35. ) {
           // Controlla se c'è stata una perdita di energia
            G4double energyLoss = preStepPoint->GetKineticEnergy() - postStepPoint->GetKineticEnergy();
            if (energyLoss > 0) {
            fAnalysisManager->FillHistogram(x, y);
           //}
           }
       }
   }
}
