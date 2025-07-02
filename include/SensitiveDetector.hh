#ifndef B1SensitiveDetector_h
#define B1SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
// #include "G4Step.hh"
// #include "G4TouchableHistory.hh"
// #include "G4String.hh"
#include <vector>

struct MyHit {
    int run;
    double x, y, z, edep;
    int pid;
};

namespace B1{
class SensitiveDetector : public G4VSensitiveDetector
{
    public:
        SensitiveDetector(const G4String& name);
        virtual ~SensitiveDetector();        
        virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory* history) override;
        // TrackerHitsCollection* fHitsCollection = nullptr;
        static std::vector<MyHit> allHits;
        static int muonCount;
        static int backgroundCount;
        static int currentRun;
        static void ResetCounters();
};
}
#endif
