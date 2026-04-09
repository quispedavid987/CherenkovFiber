#ifndef MATERIALS_HH
#define MATERIALS_HH 1

#include "globals.hh" // tipos de variables en Geant4
#include "G4Element.hh" // para la construccion de elementos
#include "G4ElementTable.hh" // Tabla de elementos
#include "G4Material.hh" // Construccion de materiales a partir de elementos
#include "G4SystemOfUnits.hh" // Sistema de unidades

class Materials
{
public:
    Materials(); // Constructor
    virtual ~Materials(); // Destructor

    // Elementos
    static G4Element* elO;
    static G4Element* elH;
    static G4Element* elN;
    static G4Element* elC;

    // Compuestos
    

    // Materiales
    static G4Material* Air; // Aire
    static G4Material* Water; // Agua
    static G4Material* PMMA; // Fibra

    // Propiedades
    static G4MaterialPropertiesTable* WaterPT1; // de agua
    static G4MaterialPropertiesTable* pmmaPT; // de fibra

private:
    void CreateElements();
    void CreateCompounds();
    void CreateMaterials();
};


#endif // MATERIALS_HH