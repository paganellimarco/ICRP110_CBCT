#ifndef ICRP110PhantomConstruction_H
#define ICRP110PhantomConstruction_H 1

#include "ICRP110PhantomMessenger.hh"
#include "G4PSDoseDeposit3D.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include <map>

class G4VPhysicalVolume;
class ICRP110PhantomMaterial_Female;
class ICRP110PhantomMaterial_Male;
class G4Material;

class ICRP110PhantomConstruction : public G4VUserDetectorConstruction
{
  public:
     explicit ICRP110PhantomConstruction();
    ~ICRP110PhantomConstruction();
     G4VPhysicalVolume* Construct()override;

     G4VPhysicalVolume* GetMotherVolume() {return fMotherVolume;}
     G4VPhysicalVolume* GetPhantumContainer() {return fPhantomContainer;}

     inline G4int GetNumberVoxelX(){return fNVoxelX;};
     inline G4int GetNumberVoxelY() {return fNVoxelY;};
     inline G4int GetNumberVoxelZ() {return fNVoxelZ;};

     inline G4double GetVoxelHalfDimX(){return fVoxelHalfDimX;};
     inline G4double GetVoxelHalfDimY() {return fVoxelHalfDimY;};
     inline G4double GetVoxelHalfDimZ() {return fVoxelHalfDimZ;};

     void SetPhantomSex(G4String);
     void SetPhantomSection(G4String);

 private:
  void ReadPhantomData(const G4String& sex, const G4String& section);
  void ReadPhantomDataFile(const G4String& sex, const G4String& fname, G4int);
  ICRP110PhantomMaterial_Female* fMaterial_Female;
  ICRP110PhantomMaterial_Male* fMaterial_Male;
  ICRP110PhantomMessenger* fMessenger;
 // std::vector<G4Material*> fMaterials;
  G4VPhysicalVolume* fMotherVolume;
  G4VPhysicalVolume* fPhantomContainer;
  G4int fNVoxelX;
  G4int fNVoxelY; 
  G4int fNVoxelZ;
  G4double fVoxelHalfDimX;
  G4double fVoxelHalfDimY;
  G4double fVoxelHalfDimZ;
  G4double fMinX;
  G4double fMaxX;
  G4double fMinY;
  G4double fMaxY;
  G4double fMinZ;
  G4double fMaxZ;
  G4int fNoFiles;
  G4int fNVoxels;
  size_t* fMateIDs; // index of material of each voxel
  G4String fSex;
  G4String fSection;
};
#endif

