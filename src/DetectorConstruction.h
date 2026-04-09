#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh" // clave para construccion

class G4VPhysicalVolume;
class G4LogicalVolume;

class MyDetectorConstruction : public G4VUserDetectorConstruction // clase heredada
{
public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

private:
 //   G4LogicalVolume* fLogicWCD; // lo que vamos a construir
//    G4LogicalVolume* fLogicFiber;
};

#endif