#ifndef ICRP110PhantomActionInitialization_h
#define ICRP110PhantomActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "ICRP110PhantomAnalysisManager.hh"


class ICRP110PhantomActionInitialization: public G4VUserActionInitialization {
public:
    explicit ICRP110PhantomActionInitialization();
    virtual ~ICRP110PhantomActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    ICRP110PhantomAnalysisManager* fAnalysisManager;
};
#endif

