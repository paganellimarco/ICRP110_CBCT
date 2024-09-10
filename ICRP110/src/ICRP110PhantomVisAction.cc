#include "ICRP110PhantomVisAction.hh"

#include "G4VisManager.hh"
#include "ICRP110PhantomConstruction.hh"
#include "ICRP110PhantomPseudoScene.hh"
#include "G4PhysicalVolumeModel.hh"
#include "G4Polymarker.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

void ICRP110PhantomVisAction::Draw ()
{
  // Get actual vis manager
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if (!pVisManager) return;

  auto container = fpDetectorConstruction->GetPhantumContainer();

  static G4bool first = true;
  if (first && container) {
    first = false;
    // Use ICRP110PhantomPseudoScene to build dataset in fPositionByColour
    G4ModelingParameters tmpMP;
    tmpMP.SetCulling(true);  // This avoids drawing transparent...
    tmpMP.SetCullingInvisible(true);  // ... or invisble volumes.
    const G4bool useFullExtent = true;  // To avoid clculating the extent
    G4PhysicalVolumeModel tmpPVModel
    (container,
     G4PhysicalVolumeModel::UNLIMITED,
     G4Transform3D(),
     &tmpMP,
     useFullExtent);
    ICRP110PhantomPseudoScene tmpScene
    (&tmpPVModel
     ,fPositionByMaterial
     ,fColourByMaterial);
    tmpPVModel.DescribeYourselfTo(tmpScene);
    // Make list of found materials
    for (const auto& entry: fColourByMaterial) {
      fSetOfMaterials.insert(entry.first);
    }
    for (const auto& material: fSetOfMaterials) {
      G4cout << "fSetOfMaterials: " << material->GetName() << G4endl;
    }
  }

  // Seems the quantities in ICRP110PhantomConstruction don't have units
  const G4double voxelHalfDimX = fpDetectorConstruction->GetVoxelHalfDimX()*mm;
  const G4double voxelHalfDimY = fpDetectorConstruction->GetVoxelHalfDimY()*mm;
  const G4double voxelHalfDimZ = fpDetectorConstruction->GetVoxelHalfDimZ()*mm;

  static G4bool firstPrint = true;
  G4int nDotsTotal = 0;
  const G4int nDotsPerPositionMin = 1;
  const G4int nDotsPerPositionMax = 10;
  const G4double densityMin = 1.*g/cm3;
  const G4double densityMax = 3.*g/cm3;;
  for (const auto& material: fSetOfMaterials) {
    auto& colour = fColourByMaterial[material];
    G4int nDots = 0;
    G4Polymarker dots;
    dots.SetVisAttributes(G4Colour(colour));
    dots.SetMarkerType(G4Polymarker::dots);
    dots.SetSize(G4VMarker::screen,1.);
    dots.SetInfo(material->GetName());
    const G4double currentDensity = material->GetDensity();
    const auto range = fPositionByMaterial.equal_range(material);
    for (auto posByMat = range.first; posByMat != range.second; ++posByMat) {
      G4int nDotsPerPosition
      = nDotsPerPositionMin
      + (nDotsPerPositionMax-nDotsPerPositionMin)
      *(currentDensity-densityMin)/(densityMax-densityMin);
      nDotsPerPosition = std::max(nDotsPerPositionMin,nDotsPerPosition);
      nDotsPerPosition = std::min(nDotsPerPositionMax,nDotsPerPosition);
      for (G4int i = 0; i < nDotsPerPosition; ++i) {
	const G4double x = posByMat->second.getX() + (2.*G4UniformRand()-1.)*voxelHalfDimX;
	const G4double y = posByMat->second.getY() + (2.*G4UniformRand()-1.)*voxelHalfDimY;
	const G4double z = posByMat->second.getZ() + (2.*G4UniformRand()-1.)*voxelHalfDimZ;
	dots.push_back(G4ThreeVector(x,y,z));
	++nDots;
      }
    }
    pVisManager->Draw(dots);
    if (firstPrint) {
      G4cout
      << "Number of dots for material " << material->GetName()
      << ", colour " << colour
      << ": " << nDots << G4endl;
    }
    nDotsTotal += nDots;
  }
  if (firstPrint) {
    G4cout << "Total number of dots: " << nDotsTotal << G4endl;
    firstPrint = false;
  }
}
