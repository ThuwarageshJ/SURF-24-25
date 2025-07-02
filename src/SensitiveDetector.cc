#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include <fstream>

std::vector<MyHit> B1::SensitiveDetector::allHits;
int B1::SensitiveDetector::muonCount = 0;
int B1::SensitiveDetector::backgroundCount = 0;
int B1::SensitiveDetector::currentRun = 0;

void B1::SensitiveDetector::ResetCounters() {
    muonCount = 0;
    backgroundCount = 0;
}

namespace B1
{
SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector()
{
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    // auto edep = step->GetTotalEnergyDeposit();
    // auto pos = step->GetPreStepPoint()->GetPosition();
    // auto prestep = step->GetPreStepPoint();
    // auto& preStepTouch = prestep->GetTouchableHandle();
    // auto volume = preStepTouch->GetVolume();
    // auto& name = volume->GetName();
    // auto postStepPoint = step->GetPostStepPoint();
    // auto aPro = postStepPoint->GetProcessDefinedStep();
    // auto aProcess = aPro->GetProcessName();
    // auto particleDef = step->GetTrack()->GetDefinition();
    // auto pid = particleDef->GetPDGEncoding();
    // auto particleName = particleDef->GetParticleName();

    // MyHit hit;
    // hit.run = currentRun;
    // hit.x = pos.x();
    // hit.y = pos.y();
    // hit.z = pos.z();
    // hit.edep = edep;
    // hit.pid = pid;
    // allHits.push_back(hit);
    // if (abs(pid)==13){
    // G4cout <<" Particle name: " << particleName << " Pos: "<<hit.x<<" "<<hit.y<<" "<<hit.z<<" "<<hit.edep<<" Process: "<<aProcess<<G4endl;
    // }

    // if (abs(pid) == 13) muonCount++;
    // else backgroundCount++;

    return true;
}

}