#ifndef B1SensitiveDetector_h
#define B1SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
// #include "G4Step.hh"
// #include "G4TouchableHistory.hh"
// #include "G4String.hh"
#include <vector>

namespace B1{
class SensitiveDetector : public G4VSensitiveDetector
{
    public:
        SensitiveDetector(const G4String& name);
        virtual ~SensitiveDetector();        
        virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory* history) override;
        // TrackerHitsCollection* fHitsCollection = nullptr;
        void StoreData(const G4Step*);
        G4bool firstTrack=false;
        G4int curtrackID = -1;
};
}
#endif
