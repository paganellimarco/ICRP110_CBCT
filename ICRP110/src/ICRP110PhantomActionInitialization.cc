#include "ICRP110PhantomActionInitialization.hh"
#include "ICRP110PhantomPrimaryGeneratorAction.hh"
#include "ICRP110PhantomSteppingAction.hh"

ICRP110PhantomActionInitialization::ICRP110PhantomActionInitialization() :
    G4VUserActionInitialization(), fAnalysisManager(new ICRP110PhantomAnalysisManager())
{}

ICRP110PhantomActionInitialization::~ICRP110PhantomActionInitialization() {
    delete fAnalysisManager;
}

void ICRP110PhantomActionInitialization::BuildForMaster() const {}

void ICRP110PhantomActionInitialization::Build() const {
    SetUserAction(new ICRP110PhantomPrimaryGeneratorAction);
    SetUserAction(new ICRP110PhantomSteppingAction(fAnalysisManager));
}

