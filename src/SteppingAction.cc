//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {
  // Initialize scoring volume and target center if not already done
  // To check if fTargetHalfZLength has no value stored in it, compare to 0 (uninitialized double is 0 by default in this context)
  if (!fScoringVolume || fTargetCenter == G4ThreeVector() || !fTargetVolume || fTargetHalfZLength == 0 ) {
    const DetectorConstruction* detConstruction =
      static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
    fTargetCenter = detConstruction->GetTargetCenter();
    fTargetVolume = detConstruction->GetTargetVolume();
    G4Box* targetBox = dynamic_cast<G4Box*>(fTargetVolume->GetSolid());
    if(targetBox){
      fTargetHalfZLength = targetBox->GetZHalfLength();   
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{

  G4int currentEventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  if (currentEventID != fLastEventID) {
        fLastEventID = currentEventID;
        fPrimaryStored = false;
  }

  // // Get step and track information
  auto preStepPoint = step->GetPreStepPoint();
  auto postStepPoint = step->GetPostStepPoint();
  G4LogicalVolume* volume =
    preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  auto track = step->GetTrack();
  auto particleDef = track->GetDefinition();
  auto particlePID = particleDef->GetPDGEncoding();
  
  if(volume!=fScoringVolume && fPrimaryStored && (abs(particlePID)!=13 && abs(particlePID)!=211))return;
  // If you're in target volume, proceed only if (1) you haven't stored primary particle data yet, or, (2) it's a pion or a muon
  // If you're in scoring volume, always proceed

  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  if (track->GetParentID() == 0 && volume == fTargetVolume && preStepPoint->GetStepStatus() == fGeomBoundary ) 
  // Store details of primary event. Might help with findign correlations
  {
    fPrimaryStored = true;
        
    G4ThreeVector firstPos = preStepPoint->GetPosition();
    G4ThreeVector firstMom = preStepPoint->GetMomentum();
    G4ThreeVector firstPos_TC = (firstPos - fTargetCenter);
    auto kineticEnergy = preStepPoint->GetKineticEnergy();

    G4int hid = 11;

    man->FillNtupleFColumn(1, hid, firstPos.x()); // fX_hit
    man->FillNtupleFColumn(1, ++hid, firstPos.y()); // fY_hit
    man->FillNtupleFColumn(1, ++hid, firstPos.z()); // fZ_hit
    man->FillNtupleFColumn(1, ++hid, firstPos_TC.x()); // fX_hit_TC
    man->FillNtupleFColumn(1, ++hid, firstPos_TC.y()); // fY_hit_TC
    man->FillNtupleFColumn(1, ++hid, firstPos_TC.z()); // fZ_hit_TC
    man->FillNtupleFColumn(1, ++hid, firstMom.x()); // fPx_hit
    man->FillNtupleFColumn(1, ++hid, firstMom.y()); // fPy_hit
    man->FillNtupleFColumn(1, ++hid, firstMom.z()); // fPz_hit
    man->FillNtupleFColumn(1, ++hid, kineticEnergy); // fKE_hit

  }
  else if (volume==fTargetVolume && (abs(particlePID)==13 || abs(particlePID)==211))
  // You're in target volume, and it's either a muon or a pion
  { 
    StoreData(step, volume);
  }
  else if (volume==fScoringVolume && preStepPoint->GetStepStatus() == fGeomBoundary)
  // in scoring volume.
  {
    auto prePos = preStepPoint->GetPosition();
    auto prePos_TC = (prePos - fTargetCenter);

    if(prePos_TC.z()==fTargetHalfZLength) 
    // Store only particles coming out through rear face.
    { 
      StoreData(step, volume);
    }  
  }
}

void SteppingAction::StoreData(const G4Step *step, G4LogicalVolume *volume)
{ 
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  auto track = step->GetTrack();
  auto trackstatus = track->GetTrackStatus();
  auto particleDef = track->GetDefinition();
  auto particlePID = particleDef->GetPDGEncoding();
  auto particleName = particleDef->GetParticleName();

  auto preStepPoint = step->GetPreStepPoint();
  auto postStepPoint = step->GetPostStepPoint();
  auto prePos = preStepPoint->GetPosition();
  auto prePos_TC = (prePos - fTargetCenter);
  auto postPos = postStepPoint->GetPosition();
  auto postPos_TC = (postPos - fTargetCenter);
  
  auto proc = postStepPoint->GetProcessDefinedStep();
  auto procname = proc->GetProcessName();

  auto dotZ = prePos_TC.unit().z();
  auto phi = std::atan2(prePos_TC.y(), prePos_TC.x());
  if (phi < 0) {phi += 2 * CLHEP::pi;}
  auto theta = std::acos(dotZ);

  auto preMomentum = preStepPoint->GetMomentum();
  auto kineticEnergy = preStepPoint->GetKineticEnergy();
  auto restMass = particleDef->GetPDGMass();

  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
      
  G4int hid = 0;
  man->FillNtupleIColumn(hid, eventID);
  man->FillNtupleSColumn(++hid, particleName);
  man->FillNtupleIColumn(++hid, particlePID);
  man->FillNtupleFColumn(++hid, restMass);
  man->FillNtupleFColumn(++hid, prePos.x());
  man->FillNtupleFColumn(++hid, prePos.y());
  man->FillNtupleFColumn(++hid, prePos.z());
  man->FillNtupleFColumn(++hid, prePos_TC.x());
  man->FillNtupleFColumn(++hid, prePos_TC.y());
  man->FillNtupleFColumn(++hid, prePos_TC.z());
  man->FillNtupleFColumn(++hid, postPos.x());
  man->FillNtupleFColumn(++hid, postPos.y());
  man->FillNtupleFColumn(++hid, postPos.z());
  man->FillNtupleFColumn(++hid, postPos_TC.x());
  man->FillNtupleFColumn(++hid, postPos_TC.y());
  man->FillNtupleFColumn(++hid, postPos_TC.z());
  man->FillNtupleFColumn(++hid, preMomentum.x());
  man->FillNtupleFColumn(++hid, preMomentum.y());
  man->FillNtupleFColumn(++hid, preMomentum.z());
  man->FillNtupleFColumn(++hid, kineticEnergy);
  man->FillNtupleFColumn(++hid, theta);
  man->FillNtupleFColumn(++hid, phi);
  man->AddNtupleRow(0);

  if(volume==fTargetVolume){
  G4cout << "EventID: " << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() << G4endl;
  G4cout << "Particle: " << particleName << " (PID: " << particlePID << ")" << G4endl;
  //G4cout << "Rest mass: " << restMass << G4endl;
  G4cout << "Pre-step position: " << prePos << " (TC: " << prePos_TC << ")" << G4endl;
  G4cout << "Post-step position: " << postPos << " (TC: " << postPos_TC << ")" << G4endl;
  if(trackstatus==fStopAndKill){
    G4cout<<" I DIED"<<G4endl;
    G4cout<<" procname: "<<procname<<G4endl;
  }
  //G4cout << "Pre-step momentum: " << preMomentum << G4endl;
  //G4cout << "Kinetic energy: " << kineticEnergy << G4endl;
  //G4cout << "Theta: " << theta << ", Phi: " << phi << G4endl;
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
