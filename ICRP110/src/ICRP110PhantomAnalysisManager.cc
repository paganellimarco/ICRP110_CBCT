#include "ICRP110PhantomAnalysisManager.hh"

ICRP110PhantomAnalysisManager::ICRP110PhantomAnalysisManager() {
    fHistogram = new TH2F("PhotonPosition", "Photon Position",
                          130, -32.6, 32.6, // binning per x
                          130, -32.6, 32.6); // binning per y
}

ICRP110PhantomAnalysisManager::~ICRP110PhantomAnalysisManager() {
TFile* file = new TFile("output_330.root", "RECREATE");
    fHistogram->Write();
    file->Close();
    delete fHistogram;
}

void ICRP110PhantomAnalysisManager::FillHistogram(double x, double y) {
    fHistogram->Fill(x, y);
}

