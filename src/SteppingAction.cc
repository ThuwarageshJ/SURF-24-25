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

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // Initialize scoring volume and target center if not already done
  if (!fScoringVolume || fTargetCenter == G4ThreeVector() || !fTargetVolume) {
    const DetectorConstruction* detConstruction =
      static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
    fTargetCenter = detConstruction->GetTargetCenter();
    fTargetVolume = detConstruction->GetTargetVolume();
  }


  G4int currentEventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  if (currentEventID != fLastEventID) {
        fLastEventID = currentEventID;
        fPrimary = false;
  }

  // // Get step and track information
  auto preStepPoint = step->GetPreStepPoint();
  
  G4LogicalVolume* volume =
    preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
  if(volume!=fScoringVolume && fPrimary)return;

  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  auto postStepPoint = step->GetPostStepPoint();
  auto track = step->GetTrack();

  if (track->GetParentID() == 0 && volume == fTargetVolume && preStepPoint->GetStepStatus() == fGeomBoundary ) 
    {
      fPrimary = true;
          
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
  else if (volume==fScoringVolume){
      // auto proc = postStepPoint->GetProcessDefinedStep();
      // if(!proc){
      //   G4cout<<"hello!"<<G4endl;
      // }
      // if(proc){
      //   G4String procName = proc->GetProcessName();
        if(preStepPoint->GetStepStatus() == fGeomBoundary)
        {
          auto particleDef = track->GetDefinition();
          auto particleName = particleDef->GetParticleName();
          auto particlePID = particleDef->GetPDGEncoding();
          if (particlePID!=22){
            auto preMomentum = preStepPoint->GetMomentum();
          auto kineticEnergy = preStepPoint->GetKineticEnergy();
          auto restMass = particleDef->GetPDGMass();
          auto prePos = preStepPoint->GetPosition();
          auto prePos_TC = (prePos - fTargetCenter);
          auto postPos = postStepPoint->GetPosition();
          auto postPos_TC = (postPos - fTargetCenter);
          G4double dotZ = prePos_TC.unit().z();
          G4double phi = std::atan2(prePos_TC.y(), prePos_TC.x());
          if (phi < 0) {
            phi += 2 * CLHEP::pi;
          }
          G4double theta = std::acos(dotZ);
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
          }
          
        }
      //}
  }
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
