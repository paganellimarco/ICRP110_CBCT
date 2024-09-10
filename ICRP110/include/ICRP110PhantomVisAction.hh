#ifndef ICRP110PhantomVisAction_h
#define ICRP110PhantomVisAction_h 1

#include "G4VUserVisAction.hh"

#include "G4Colour.hh"

class G4Material;

#include <set>

class ICRP110PhantomConstruction;

class ICRP110PhantomVisAction: public G4VUserVisAction
{
public:
  ICRP110PhantomVisAction(ICRP110PhantomConstruction* dc)
  : fpDetectorConstruction(dc) {}
  void Draw();
private:
  ICRP110PhantomConstruction*                    fpDetectorConstruction;
  std::multimap<const G4Material*,G4ThreeVector> fPositionByMaterial;
  std::map     <const G4Material*,G4Colour>      fColourByMaterial;
  std::set     <const G4Material*>               fSetOfMaterials;
};

#endif
