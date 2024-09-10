#include "SimplePhysicsList.hh"
#include "CustomComptonScattering.hh"
#include "CustomPhotoElectricEffect.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

// Includi i file header per G4eMultipleScattering e G4eIonisation
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"

SimplePhysicsList::SimplePhysicsList() : G4VModularPhysicsList() {
    SetVerboseLevel(1);
}

SimplePhysicsList::~SimplePhysicsList() {}

void SimplePhysicsList::ConstructParticle() {
    G4Gamma::GammaDefinition();
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
}

void SimplePhysicsList::ConstructProcess() {
    AddTransportation();

    G4ProcessManager *phManager = G4Gamma::GammaDefinition()->GetProcessManager();

    // Utilizzo delle classi personalizzate
    phManager->AddDiscreteProcess(new CustomPhotoElectricEffect);
    phManager->AddDiscreteProcess(new CustomComptonScattering);

    G4ProcessManager *elManager = G4Electron::ElectronDefinition()->GetProcessManager();
    elManager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
    elManager->AddProcess(new G4eIonisation, -1, 2, 2);
}

void SimplePhysicsList::SetCuts() {
    defaultCutValue = 0.3 * mm;
    SetCutsWithDefault();
}

