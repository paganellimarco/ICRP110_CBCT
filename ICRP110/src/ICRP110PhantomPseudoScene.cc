#include "ICRP110PhantomPseudoScene.hh"

#include "G4PhysicalVolumeModel.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

// Given a world volume, fill maps provided by the instantiator
ICRP110PhantomPseudoScene::ICRP110PhantomPseudoScene
(G4PhysicalVolumeModel* pvm  // input...the following are outputs
 ,std::multimap<const G4Material*,G4ThreeVector>& positionByMaterial
 ,std::map     <const G4Material*,G4Colour>&      colourByMaterial)
: fpPVModel(pvm)
, fPositionByMaterial(positionByMaterial)
, fColourByMaterial  (colourByMaterial)
{}

ICRP110PhantomPseudoScene::~ICRP110PhantomPseudoScene()
{}

void ICRP110PhantomPseudoScene::AddSolid(const G4Box&)
{
  const G4Material* material = fpPVModel->GetCurrentLV()->GetMaterial();
  const G4Colour& colour = fpPVModel->GetCurrentLV()->GetVisAttributes()->GetColour();
  const G4ThreeVector& position = fpCurrentObjectTransformation->getTranslation();

  // Fill maps for vis action
  fPositionByMaterial.insert(std::make_pair(material,position));
  fColourByMaterial[material] = colour;
}

void ICRP110PhantomPseudoScene::ProcessVolume(const G4VSolid&)
{
  G4ExceptionDescription ed;
  ed << "ICRP110PhantomPseudoScene::ProcessVolume called for solid that is NOT a G4Box.";
  G4Exception("ICRP110PhantomPseudoScene::ProcessVolume", "ICRP110Phantom_0000",
	      FatalException, ed, "Contact @allison");
}
