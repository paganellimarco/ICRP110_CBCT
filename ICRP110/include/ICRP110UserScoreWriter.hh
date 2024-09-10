#ifndef ICRP110UserScoreWriter_h
#define ICRP110UserScoreWriter_h 1

#include "ICRP110ScoreWriterMessenger.hh"

#include "globals.hh"
#include "G4VScoreWriter.hh"

class ICRP110UserScoreWriter:public G4VScoreWriter
{
public:
  explicit ICRP110UserScoreWriter();
  virtual ~ICRP110UserScoreWriter();
  // store a quantity into a file
  void DumpQuantityToFile(const G4String & psName, 
                          const G4String & fileName, 
                          const G4String & option);
  void SetPhantomSex(G4String);
  void SetPhantomSection(G4String);
  
private:
  ICRP110ScoreWriterMessenger* fMessenger;
  G4String fSex;
  G4String fSection;
};
#endif

