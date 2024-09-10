#ifndef ICRP110PhantomAnalysisManager_h
#define ICRP110PhantomAnalysisManager_h

#include "TH2F.h"
#include "TFile.h"

class ICRP110PhantomAnalysisManager {
public:
    ICRP110PhantomAnalysisManager();
    ~ICRP110PhantomAnalysisManager();

    void FillHistogram(double x, double y);

private:
    TH2F* fHistogram;
};

#endif

