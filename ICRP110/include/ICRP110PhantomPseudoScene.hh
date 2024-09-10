#ifndef ICRP110PhantomPseudoScene_h
#define ICRP110PhantomPseudoScene_h 1

#include "G4PseudoScene.hh"

#include "G4Colour.hh"
#include "G4ThreeVector.hh"

#include <map>

class G4PhysicalVolumeModel;
class G4Material;

class ICRP110PhantomPseudoScene: public G4PseudoScene
{
public:
  // Given a world volume, fill a multimap provided by the instantiator
  ICRP110PhantomPseudoScene
  (G4PhysicalVolumeModel*  // input...the following are outputs
   ,std::multimap<const G4Material*,G4ThreeVector>& positionByMaterial
   ,std::map     <const G4Material*,G4Colour>&      colourByMaterial);

  ~ICRP110PhantomPseudoScene();

  using G4PseudoScene::AddSolid;  // except for...
  void AddSolid(const G4Box&);
  void ProcessVolume(const G4VSolid&);

  const std::multimap<const G4Material*,G4ThreeVector>& GetPositionByMaterial()
  {return fPositionByMaterial;}

  const std::map     <const G4Material*,G4Colour>&      GetColourByMaterial()
  {return fColourByMaterial;}

private:
  G4PhysicalVolumeModel* fpPVModel;
  std::multimap<const G4Material*,G4ThreeVector>& fPositionByMaterial;
  std::map     <const G4Material*,G4Colour>&      fColourByMaterial;
};
#endif

