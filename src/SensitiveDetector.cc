#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include <fstream>

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
    //StoreData(step);
    return true;
}

void SensitiveDetector::StoreData(const G4Step *step)
{ 
  // G4AnalysisManager is thread-safe in Geant4, but we need to be careful
  // Worker threads can fill ntuples, master thread handles file I/O
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  auto track = step->GetTrack();
  auto trackstatus = track->GetTrackStatus();
  track->SetTrackStatus(fStopAndKill); // Stop the track after storing data
  auto trackID = track->GetTrackID();
  auto particleDef = track->GetDefinition();
  auto particlePID = particleDef->GetPDGEncoding();
  auto particleName = particleDef->GetParticleName();
  auto restMass = particleDef->GetPDGMass();

  auto preStepPoint = step->GetPreStepPoint();
  G4int copyNumber = preStepPoint->GetTouchableHandle()->GetCopyNumber();

  auto prePos = preStepPoint->GetPosition();
  auto preMomentum = preStepPoint->GetMomentum();
  auto kineticEnergy = preStepPoint->GetKineticEnergy();
  
  auto dotZ = prePos.unit().z();
  auto dotZ_p = preMomentum.unit().z();
  auto phi = std::atan2(prePos.y(), prePos.x());
  if (phi < 0) {phi += 2 * CLHEP::pi;}
  auto theta_p = std::acos(dotZ_p);

  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  auto creator_process = "N/A";
  const G4VProcess* proc = track->GetCreatorProcess();
  if(proc){
    creator_process = proc->GetProcessName();
  }

  G4int parentID = track->GetParentID();  
  
  // Fill the SD ntuple (ntuple ID = 1)
  G4int hid = 0;
  man->FillNtupleIColumn(1, hid, eventID);
  man->FillNtupleIColumn(1, ++hid, trackID);
  man->FillNtupleSColumn(1, ++hid, particleName);
  man->FillNtupleIColumn(1, ++hid, particlePID);
  man->FillNtupleFColumn(1, ++hid, restMass);
  man->FillNtupleIColumn(1, ++hid, copyNumber);
  man->FillNtupleFColumn(1, ++hid, prePos.x());
  man->FillNtupleFColumn(1, ++hid, prePos.y());
  man->FillNtupleFColumn(1, ++hid, prePos.z());
  man->FillNtupleFColumn(1, ++hid, preMomentum.x());
  man->FillNtupleFColumn(1, ++hid, preMomentum.y());
  man->FillNtupleFColumn(1, ++hid, preMomentum.z());
  man->FillNtupleFColumn(1, ++hid, preMomentum.mag());
  man->FillNtupleFColumn(1, ++hid, kineticEnergy);
  man->FillNtupleFColumn(1, ++hid, theta_p);
  man->FillNtupleFColumn(1, ++hid, phi);
  man->FillNtupleIColumn(1, ++hid, parentID);
  man->FillNtupleSColumn(1, ++hid, creator_process);
  man->AddNtupleRow(1);
}

}