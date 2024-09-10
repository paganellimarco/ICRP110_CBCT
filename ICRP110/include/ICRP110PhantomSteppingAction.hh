#ifndef ICRP110PhantomSteppingAction_h
#define ICRP110PhantomSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "ICRP110PhantomAnalysisManager.hh"

class ICRP110PhantomSteppingAction : public G4UserSteppingAction {
public:
    ICRP110PhantomSteppingAction(ICRP110PhantomAnalysisManager* analysisManager);
    virtual ~ICRP110PhantomSteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

private:
    ICRP110PhantomAnalysisManager* fAnalysisManager;
};

#endif

