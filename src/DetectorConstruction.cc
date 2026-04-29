#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4LogicalBorderSurface.hh"

#include "DetectorConstruction.h"
#include "Materials.h"

MyDetectorConstruction::MyDetectorConstruction():G4VUserDetectorConstruction(){}
MyDetectorConstruction::~MyDetectorConstruction(){}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    // Volumenes solidos (geometrias)
    G4Box*  solidWorld = nullptr;
    G4Tubs* solidTank  = nullptr;
    G4Tubs* solidBot   = nullptr;
    G4Tubs* solidTop   = nullptr;
    G4Tubs* solidSide  = nullptr;

    // Volumenes logicos (materiales)
    G4LogicalVolume* logWorld = nullptr;
    G4LogicalVolume* logTank  = nullptr;
    G4LogicalVolume* logTop   = nullptr;
    G4LogicalVolume* logBot   = nullptr;
    G4LogicalVolume* logSide  = nullptr;

    // Placement fisicos (ubicacion)
    G4PVPlacement* physWorld = nullptr;
    G4PVPlacement* physTank  = nullptr;
    G4PVPlacement* physTop   = nullptr;
    G4PVPlacement* physBot   = nullptr;
    G4PVPlacement* physSide  = nullptr;

    // Dimensiones del mundo
    G4double WorldSize = 1 * m;

    // Dimensiones del tanque (WCD)
    G4double fTankRadius     = 15 * cm;
    G4double fTankHeight     = 40 * cm;
    G4double fTankHalfHeight = 0.5 * fTankHeight;
    G4double fTankThickness  = 2 * cm;

    // Ubicaciones
    G4ThreeVector fWorldCenter = G4ThreeVector(0., 0., 0.);
    G4ThreeVector fTankCenter  = G4ThreeVector(0., 0., 0.);

    // Definiendo volumenes solidos
    solidWorld = new G4Box("World", 0.5*WorldSize, 0.5*WorldSize, 0.5*WorldSize);
    solidTank  = new G4Tubs("Tank", 0, fTankRadius, fTankHalfHeight, 0, 360 * deg);
    solidTop   = new G4Tubs("Top", 0, fTankRadius + fTankThickness, fTankThickness/2, 0, 360 * deg);
    solidBot   = new G4Tubs("Top", 0, fTankRadius + fTankThickness, fTankThickness/2, 0, 360 * deg);
    solidSide  = new G4Tubs("Side", fTankRadius, fTankRadius + fTankThickness, fTankHalfHeight, 0, 360 * deg);

    // Definiendo volumenes logicos
    logTank  = new G4LogicalVolume(solidTank, Materials().Water, "logtank", 0 ,0 ,0);
    logWorld = new G4LogicalVolume(solidWorld, Materials().Air, "logWorld", 0, 0, 0);
    logTop   = new G4LogicalVolume(solidTop, Materials().HDPE, "logTop", 0, 0, 0);
    logSide  = new G4LogicalVolume(solidSide, Materials().HDPE, "logSide", 0, 0, 0);
    logBot   = new G4LogicalVolume(solidBot, Materials().HDPE, "logBot", 0, 0, 0);

    // Definiendo las posiciones PhysicalVolume
    physWorld = new G4PVPlacement(nullptr, fWorldCenter, logWorld, "World", 0, false, 0, true);
    physTank  = new G4PVPlacement(nullptr, fTankCenter, logTank, "Tank", logWorld, false, 0, true); // physTank
    physTop   = new G4PVPlacement(nullptr, fTankCenter + G4ThreeVector(0, 0, fTankHalfHeight + fTankThickness/2), logTop, "Top", logWorld, false, 0, true);  // physTop
    physBot   = new G4PVPlacement(nullptr, fTankCenter - G4ThreeVector(0, 0, fTankHalfHeight + fTankThickness/2), logBot, "Bot", logWorld, false, 0, true);// physBot
    physSide  = new G4PVPlacement(nullptr, fTankCenter, logSide, "Side", logWorld, false, 0, true); // physSide


    new G4LogicalBorderSurface("TopSurface", physTank, physTop, Materials().LinerOptSurf);
	new G4LogicalBorderSurface("BotSurface", physTank, physBot, Materials().LinerOptSurf);
	new G4LogicalBorderSurface("SideSurface", physTank, physSide, Materials().LinerOptSurf);

    // Atributos Colores
    G4VisAttributes* WorldAtt = new G4VisAttributes(G4Colour::White());
    WorldAtt -> SetVisibility(false);
    logWorld -> SetVisAttributes(WorldAtt); 

    G4VisAttributes* TankAtt = new G4VisAttributes(G4Colour::Blue());
    TankAtt -> SetForceSolid(true);
    logTank -> SetVisAttributes(TankAtt);
 
    G4VisAttributes* TopAtt = new G4VisAttributes(G4Colour::Gray());
    TopAtt -> SetForceSolid(true);
    logTop -> SetVisAttributes(TopAtt);

    G4VisAttributes* BotAtt = new G4VisAttributes(G4Colour::Gray());
    BotAtt -> SetForceSolid(true);
    logBot -> SetVisAttributes(BotAtt);

    G4VisAttributes* SideAtt = new G4VisAttributes(G4Colour::Gray());
    SideAtt -> SetForceSolid(true);
    logSide -> SetVisAttributes(SideAtt);

    return physWorld;
}
