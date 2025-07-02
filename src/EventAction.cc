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
/// \file B1/src/EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "RunAction.hh"
#include "G4ParticleDefinition.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
  // accumulate statistics in run action
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4ThreeVector targetCenter = fRunAction->GetTargetCenter();
  
  G4int evtID = evt->GetEventID();
	G4PrimaryParticle* priPar = evt->GetPrimaryVertex()->GetPrimary();
	G4String parName = priPar->GetParticleDefinition()->GetParticleName();
	G4double parEng = priPar->GetKineticEnergy();
	G4ThreeVector parMom = priPar->GetMomentum();
	G4ThreeVector parDir = priPar->GetMomentumDirection();
  G4ThreeVector parPos = evt->GetPrimaryVertex()->GetPosition();
  G4ThreeVector parPos_TC = (parPos - targetCenter);
  
  G4int hid = 0;

  man->FillNtupleIColumn(1, hid, evtID);
  man->FillNtupleFColumn(1, ++hid,parPos.x());
  man->FillNtupleFColumn(1, ++hid, parPos.y());
  man->FillNtupleFColumn(1, ++hid, parPos.z());
  man->FillNtupleFColumn(1, ++hid, parPos_TC.x()); // fX_emitted_TC
  man->FillNtupleFColumn(1, ++hid, parPos_TC.y()); // fY_emitted_TC
  man->FillNtupleFColumn(1, ++hid, parPos_TC.z()); // fZ_emitted_TC
  man->FillNtupleFColumn(1, ++hid, parMom.x());
  man->FillNtupleFColumn(1, ++hid, parMom.y());
  man->FillNtupleFColumn(1, ++hid, parMom.z());
  man->FillNtupleFColumn(1, ++hid, parEng);
  
  man->AddNtupleRow(1);

  
  fEventNo++;
  if (fEventNo%500==0){
  G4cout<<"Event "<< fEventNo<<G4endl;
  }
  fRunAction->AddEdep(fEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
