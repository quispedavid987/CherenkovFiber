#include "PrimaryGeneratorAction.h"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const{
PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
SetUserAction(generator);
}


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Declaramos la existencia de disparos de las particulas
    fParticleGun1 = new G4ParticleGun(1); 
    fParticleGun2 = new G4ParticleGun(1); 

    // Llamamos a la tabla de particulas
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    // Definiendo las particulas
    G4ParticleDefinition* particle1 = particleTable -> FindParticle("mu-");
    G4ParticleDefinition* particle2 = particleTable -> FindParticle("opticalphoton"); 

    // Alistando las particulas para el disparo
    fParticleGun1 -> SetParticleDefinition(particle1);
    fParticleGun2 -> SetParticleDefinition(particle2);

    // Direccion del momento de las particulas    
    fParticleGun1 -> SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
    fParticleGun2 -> SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
    
    // Definiendo la energia de las particulas
    fParticleGun1 -> SetParticleEnergy(80. * MeV);
    fParticleGun2 -> SetParticleEnergy(3. * eV);

    // Definiendo el punto de partida
    fParticleGun1 -> SetParticlePosition(G4ThreeVector(0., 0., 45. * cm));
    fParticleGun2 -> SetParticlePosition(G4ThreeVector(20. * cm, 25. * cm, 25. *cm));
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun1 -> GeneratePrimaryVertex(anEvent);
    fParticleGun2 -> GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
delete fParticleGun1;
delete fParticleGun2;
}