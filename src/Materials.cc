#include "Materials.h"
#include "globals.hh"

// ------------------- Water 1 (Pierre Auger Offline Framework) -------------------------------

// array of photon energies for Cerenkov processes in WCD tanks
// this energy range corresponds to the efficiency region of Auger WCD large PMTs
static G4double water1PhotonEnergy[] = {
	2.08*eV,  2.16*eV,  2.19*eV,  2.23*eV,  2.27*eV,  2.32*eV,
	2.36*eV,  2.41*eV,  2.46*eV,  2.50*eV,  2.56*eV,  2.61*eV,
	2.67*eV,  2.72*eV,  2.79*eV,  2.85*eV,  2.92*eV,  2.99*eV,
	3.06*eV,  3.14*eV,  3.22*eV,  3.31*eV,  3.40*eV,  3.49*eV,
	3.59*eV,  3.70*eV,  3.81*eV,  3.94*eV,  4.07*eV,  4.20*eV
};

G4int water1ArrEntries = sizeof(water1PhotonEnergy) / sizeof(G4double);
G4double scaleAbsLen = 100*m;

static G4double water1AbsLen[] = {
	0.092*scaleAbsLen, 0.133*scaleAbsLen, 0.180*scaleAbsLen, 0.203*scaleAbsLen, 0.226*scaleAbsLen, 0.258*scaleAbsLen,
	0.284*scaleAbsLen, 0.302*scaleAbsLen, 0.403*scaleAbsLen, 0.560*scaleAbsLen, 0.735*scaleAbsLen, 0.818*scaleAbsLen,
	0.923*scaleAbsLen, 0.923*scaleAbsLen, 0.993*scaleAbsLen, 0.993*scaleAbsLen, 1.000*scaleAbsLen, 0.941*scaleAbsLen,
	0.889*scaleAbsLen, 0.842*scaleAbsLen, 0.754*scaleAbsLen, 0.655*scaleAbsLen, 0.480*scaleAbsLen, 0.380*scaleAbsLen,
	0.311*scaleAbsLen, 0.257*scaleAbsLen, 0.212*scaleAbsLen, 0.171*scaleAbsLen, 0.137*scaleAbsLen, 0.102*scaleAbsLen
};


static G4double water1PhotonEnergyShort[] = {2.08*eV, 4.20*eV};
static G4double water1RefIndex[] = {1.33, 1.33};

static G4double linerAbsLen[] = {
	10*m,  10*m,  10*m,  10*m,  10*m,  10*m,
	10*m,  10*m,  10*m,  10*m,  10*m,  10*m,
	10*m,  10*m,  10*m,  10*m,  10*m,  10*m,
	10*m,  10*m,  10*m,  10*m,  10*m,  10*m,
	10*m,  10*m,  10*m,  10*m,  10*m,  10*m
};

// Arrays parala fibra
// array of photon energies in the red-UV range for scintillation processes
static G4double scinPhotonEnergy[] = {
	2.00*eV, 2.03*eV, 2.06*eV, 2.09*eV, 2.12*eV,
	2.15*eV, 2.18*eV, 2.21*eV, 2.24*eV, 2.27*eV,
	2.30*eV, 2.33*eV, 2.36*eV, 2.39*eV, 2.42*eV,
	2.45*eV, 2.48*eV, 2.51*eV, 2.54*eV, 2.57*eV,
	2.60*eV, 2.63*eV, 2.66*eV, 2.69*eV, 2.72*eV,
	2.75*eV, 2.78*eV, 2.81*eV, 2.84*eV, 2.87*eV,
	2.90*eV, 2.93*eV, 2.96*eV, 2.99*eV, 3.02*eV,
	3.05*eV, 3.08*eV, 3.11*eV, 3.14*eV, 3.17*eV,
	3.20*eV, 3.23*eV, 3.26*eV, 3.29*eV, 3.32*eV,
	3.35*eV, 3.38*eV, 3.41*eV, 3.44*eV, 3.47*eV
};

G4int scinArrEntries = sizeof(scinPhotonEnergy)/sizeof(G4double);

static G4double pmmaRefIndex[] = {
	1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
	1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
	1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
	1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60,
	1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60, 1.60
};

static G4double pmmaAbsLen[] = {
	10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m,
	10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m,
	10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 10.00*m, 1.0*m,
	0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m,
	0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m, 0.0001*m
};

static G4double pmmaEmission[] = {
	0.05, 0.10, 0.30, 0.50, 0.75, 1.00, 1.50, 1.85, 2.30, 2.75,
	3.25, 3.80, 4.50, 5.20, 6.00, 7.00, 8.50, 9.50, 11.1, 12.4,
	12.9, 13.0, 12.8, 12.3, 11.1, 11.0, 12.0, 11.0, 17.0, 16.9,
	15.0, 9.00, 2.50, 1.00, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
};

static bool isInitialized = 0;
G4Element* Materials::elH;
G4Element* Materials::elO;
G4Element* Materials::elN;
G4Element* Materials::elC;

G4Material* Materials::Air;
G4Material* Materials::Water;
G4Material* Materials::PMMA;
G4Material* Materials::HDPE;

G4MaterialPropertiesTable* Materials::WaterPT1;
G4MaterialPropertiesTable* Materials::pmmaPT;
G4MaterialPropertiesTable* Materials::linerPT1;

Materials::Materials()
{
    if (isInitialized) {return;}
    isInitialized = true;
    CreateElements();
    CreateCompounds();
    CreateMaterials();
}

Materials::~Materials(){}

void Materials::CreateElements()
{
    elN  = new G4Element("Nitrogen", "N", 7, 14.01 * g/mole);
    elO  = new G4Element("Oxygen", "O", 8, 16.00 * g/mole);
    elH  = new G4Element("Hydrogen", "H", 1, 1.01 * g/mole);
    elC  = new G4Element("Carbon", "C", 6, 12.0107 * g/mole);
    G4cout << "Creado elementos .... OK!" << G4endl;
}

void Materials::CreateCompounds()
{

}

void Materials::CreateMaterials()
{
    Air = new G4Material("Air", 1.29e-3 * g/cm3, 2); // Aire
    Air -> AddElement(elN, 0.7);
    Air -> AddElement(elO, 0.3);

    Water = new G4Material("Water", 1 * g/cm3, 2); // Agua
    Water -> AddElement(elH, 2);
    Water -> AddElement(elO, 1);


	PMMA = new G4Material("PMMA", 1.190 * g/cm3, 3); // Fibra
	PMMA -> AddElement(elC, 5);
	PMMA -> AddElement(elH, 8);
	PMMA -> AddElement(elO, 2);

	HDPE = new G4Material("HDPE", 0.94 * g/cm3, 2); // Tyvek
	HDPE -> AddElement(elC, 2);
	HDPE -> AddElement(elH, 4);


    // Agregando propiedades al agua
    // Define different PropertiesTable for different water "types"
	WaterPT1 = new G4MaterialPropertiesTable();
	WaterPT1->AddProperty("RINDEX", water1PhotonEnergyShort, water1RefIndex, 2);
	WaterPT1->AddProperty("ABSLENGTH", water1PhotonEnergy, water1AbsLen, water1ArrEntries);
	Water->SetMaterialPropertiesTable(WaterPT1);

	// Agregando propiedades a la fibra
    pmmaPT = new G4MaterialPropertiesTable();
	pmmaPT->AddProperty("RINDEX", scinPhotonEnergy, pmmaRefIndex, scinArrEntries);
	pmmaPT->AddProperty("WLSABSLENGTH", scinPhotonEnergy, pmmaAbsLen, scinArrEntries);
	pmmaPT->AddProperty("WLSCOMPONENT", scinPhotonEnergy, pmmaEmission, scinArrEntries);
	pmmaPT->AddConstProperty("WLSTIMECONSTANT", 0.5 * ns); // 
	PMMA->SetMaterialPropertiesTable(pmmaPT);


	// Agregando propiedades al Tyvek
	linerPT1 = new G4MaterialPropertiesTable();
	linerPT1->AddProperty("ABSLENGTH", water1PhotonEnergy,linerAbsLen, water1ArrEntries);
	HDPE->SetMaterialPropertiesTable(linerPT1);

    G4cout << "Creando Materiales .... OK!" << G4endl;

}