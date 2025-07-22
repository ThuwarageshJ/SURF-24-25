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


#include "G4BiasingProcessInterface.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction, G4bool BGSides) 
  : fEventAction(eventAction), fBGSides(BGSides) {
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
      fTargetHalfXLength = targetBox->GetXHalfLength();
      fTargetHalfYLength = targetBox->GetYHalfLength();
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

  if ((particlePID == 22) && (track->GetCurrentStepNumber() == 1)) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillH1(0, preStepPoint->GetKineticEnergy());
    // Get the process defined in this step
    const G4VProcess *process = postStepPoint->GetProcessDefinedStep();
    // Check if the process is a G4BiasingProcessInterface
    const G4BiasingProcessInterface *biasingProcess = dynamic_cast<const G4BiasingProcessInterface *>(process);
    if (biasingProcess) {
        G4VProcess *wrappedProcess = biasingProcess->GetWrappedProcess();
        if (!wrappedProcess) {
          G4cout << "Wrapped process is null!" << G4endl;
        }
    }
  }

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
    StoreData(step, volume, 0);
  }
  else if (volume==fScoringVolume && preStepPoint->GetStepStatus() == fGeomBoundary)
  // in scoring volume.
  {
    auto prePos = preStepPoint->GetPosition();
    auto prePos_TC = (prePos - fTargetCenter);
    auto fromTargetFlag = (
        std::abs(prePos_TC.x()) == fTargetHalfXLength ||
        std::abs(prePos_TC.y()) == fTargetHalfYLength ||
        std::abs(prePos_TC.z()) == fTargetHalfZLength
    );

    G4bool store = (fBGSides)? fromTargetFlag : (prePos_TC.z()==fTargetHalfZLength);

    if(store) 
    // Store only particles coming out through rear face, OR, from all sides, depending on fBGSides
    { 
      StoreData(step, volume, 1);
    }  
  }
}

void SteppingAction::StoreData(const G4Step *step, G4LogicalVolume *volume, G4int type)
{ 
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  auto track = step->GetTrack();
  auto trackstatus = track->GetTrackStatus();
  auto trackID = track->GetTrackID();
  auto particleDef = track->GetDefinition();
  auto particlePID = particleDef->GetPDGEncoding();
  auto particleName = particleDef->GetParticleName();

  auto preStepPoint = step->GetPreStepPoint();
  auto postStepPoint = step->GetPostStepPoint();
  auto prePos = preStepPoint->GetPosition();
  auto prePos_TC = (prePos - fTargetCenter);
  auto postPos = postStepPoint->GetPosition();
  auto postPos_TC = (postPos - fTargetCenter);

  auto preMomentum = preStepPoint->GetMomentum();
  auto kineticEnergy = preStepPoint->GetKineticEnergy();
  auto restMass = particleDef->GetPDGMass();

  auto dotZ = prePos_TC.unit().z();
  auto dotZ_p = preMomentum.unit().z();
  auto phi = std::atan2(prePos_TC.y(), prePos_TC.x());
  if (phi < 0) {phi += 2 * CLHEP::pi;}
  auto theta_r = std::acos(dotZ);
  auto theta_p = std::acos(dotZ_p);

  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  auto process_type = (type==1 ? "outgoing": "intarget");
  if(trackstatus == fStopAndKill && type==0){process_type = "kill";}

  auto creator_process = "N/A";
  auto post_process = "N/A";
  const G4VProcess* proc = track->GetCreatorProcess();
  if(proc){
    creator_process = proc->GetProcessName();
    if (creator_process=="muPairProd"){
      G4cout<<"Yehehehhehehe"<<G4endl;
    }
  }
  const G4VProcess* postProc = postStepPoint->GetProcessDefinedStep();
  if(postProc){
    post_process = postProc->GetProcessName();
  }

  G4int parentID = track->GetParentID();  
  
  G4int hid = 0;
  man->FillNtupleIColumn(hid, eventID);
  man->FillNtupleIColumn(++hid, trackID);
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
  man->FillNtupleFColumn(++hid, preMomentum.mag());
  man->FillNtupleFColumn(++hid, kineticEnergy);
  man->FillNtupleFColumn(++hid, theta_p);
  man->FillNtupleFColumn(++hid, theta_r);
  man->FillNtupleFColumn(++hid, phi);
  man->FillNtupleIColumn(++hid, parentID);
  man->FillNtupleSColumn(++hid, creator_process);
  man->FillNtupleSColumn(++hid, post_process);
  man->FillNtupleSColumn(++hid, process_type);
  man->AddNtupleRow(0);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
