#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectorConstruction.h"
#include "Materials.h"

MyDetectorConstruction::MyDetectorConstruction():G4VUserDetectorConstruction(){}
MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    // Volumenes solidos (geometrias)
    G4Box*  solidWorld = nullptr;
    G4Tubs* solidTank  = nullptr;
    G4Tubs* solidFiber = nullptr;

    // Volumenes logicos (materiales)
    G4LogicalVolume* logWorld = nullptr;
    G4LogicalVolume* logTank  = nullptr;
    G4LogicalVolume* logFiber = nullptr;

    // Placement fisicos (ubicacion)
    G4PVPlacement* physWorld = nullptr;
    //G4PVPlacement* physTank  = nullptr;

    // Dimensiones del mundo
    G4double WorldSize = 1 * m;

    // Dimensiones del tanque (WCD)
    G4double fTankRadius     = 15 * cm;
    G4double fTankHeight     = 40 * cm;
    G4double fTankHalfHeight = 0.5 * fTankHeight;


    // Dimensiones de la fibra (Fiber)
    G4double fiberRadius = 5 * cm;
    G4double fiberHeight = 40 * cm;
    G4double fiberHalfHeight = 0.5 * fiberHeight;

    // Ubicaciones
    G4ThreeVector fWorldCenter = G4ThreeVector(0., 0., 0.);
    G4ThreeVector fTankCenter  = G4ThreeVector(0., 0., 0.);
    G4ThreeVector fiberCenter  = G4ThreeVector(20. * cm, 25. *cm, 0.);

    // Definiendo volumenes solidos
    solidWorld = new G4Box("World", 0.5*WorldSize, 0.5*WorldSize, 0.5*WorldSize);
    solidTank  = new G4Tubs("Tank", 0, fTankRadius, fTankHalfHeight, 0, 360 * deg);
    solidFiber = new G4Tubs("Fiber", 0, fiberRadius, fiberHalfHeight, 0, 360 * deg);

    // Definiendo volumenes logicos
    logTank  = new G4LogicalVolume(solidTank, Materials().Water, "logtank", 0 ,0 ,0);
    logWorld = new G4LogicalVolume(solidWorld, Materials().Air, "logWorld", 0, 0, 0);
    logFiber = new G4LogicalVolume(solidFiber, Materials().PMMA, "logFiber", 0, 0, 0);

    // Definiendo las posiciones PhysicalVolume
    physWorld = new G4PVPlacement(nullptr, fWorldCenter, logWorld, "World", 0, false, 0, true);
    new G4PVPlacement(nullptr, fTankCenter, logTank, "Tank", logWorld, false, 0, true);
    new G4PVPlacement(nullptr, fiberCenter, logFiber, "Fiber", logWorld, false, 0, true);

    // Atributos Colores
    G4VisAttributes* TankAtt = new G4VisAttributes(G4Colour::Blue());
    TankAtt -> SetForceSolid(true);
    logTank -> SetVisAttributes(TankAtt);

    G4VisAttributes* fiberAtt = new G4VisAttributes(G4Color::Cyan());
    fiberAtt -> SetForceSolid(true);
    logFiber -> SetVisAttributes(fiberAtt);

    return physWorld;
}
