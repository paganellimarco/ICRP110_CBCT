#include "ICRP110PhantomPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"

ICRP110PhantomPrimaryGeneratorAction::ICRP110PhantomPrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    //fParticleSource = new G4GeneralParticleSource();

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "gamma");
    fParticleGun->SetParticleDefinition(particle);
    //fParticleSource->SetParticleDefinition(particle);

    // Imposta la posizione della particella
    G4double posZ = -80.5 * cm;
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, posZ));
    //fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0, 0, posZ));
}

ICRP110PhantomPrimaryGeneratorAction::~ICRP110PhantomPrimaryGeneratorAction() {
    delete fParticleGun;
    //delete fParticleSource;
}

void ICRP110PhantomPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Genera energia uniformemente distribuita tra 10 e 140 keV
    G4double minEnergy = 10. * keV;
    G4double maxEnergy = 140. * keV;
    G4double energy = minEnergy + G4UniformRand() * (maxEnergy - minEnergy);
    fParticleGun->SetParticleEnergy(energy);

    // Genera direzione uniformemente distribuita in un cono di 11 gradi attorno a z
    G4double coneAngle = 16. * degree;
    G4double pi = 3.141592654;
    G4double phi = G4UniformRand() * 2. * pi;
    G4double theta = acos(1. - G4UniformRand() * (1. - cos(coneAngle)));
    G4ThreeVector direction(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    fParticleGun->SetParticleMomentumDirection(direction);



/*
G4double coneAngleY = 11. * degree;   // Apertura del cono sull'asse y
G4double coneAngleX = 9.85 * degree;  // Apertura del cono sull'asse x

// Genera un punto casuale all'interno di un rettangolo di dimensioni 2*tan(coneAngleX) x 2*tan(coneAngleY)
G4double sideX = 2. * tan(coneAngleX);
G4double sideY = 2. * tan(coneAngleY);
G4double x = (G4UniformRand() - 0.5) * sideX;
G4double y = (G4UniformRand() - 0.5) * sideY;

// Calcola la distanza dal centro del rettangolo alla coordinata (x, y)
G4double r = sqrt(x * x + y * y);

// Calcola theta e phi
G4double phi = atan2(y, x); // angolo azimutale nel piano xy
G4double theta = atan(r);   // angolo di inclinazione

// Converti da coordinate sferiche a cartesiane
G4ThreeVector direction(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));

// Imposta la direzione del momento della particella
fParticleGun->SetParticleMomentumDirection(direction);

*/


    fParticleGun->GeneratePrimaryVertex(anEvent);
    //fParticleSource->GeneratePrimaryVertex(anEvent);
}

