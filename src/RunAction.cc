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
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "G4Run.hh"
#include <direct.h>
#include <fstream>

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AccumulableManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // add new units for dose
  //
  const G4double milligray = 1.e-3 * gray;
  const G4double microgray = 1.e-6 * gray;
  const G4double nanogray = 1.e-9 * gray;
  const G4double picogray = 1.e-12 * gray;

  new G4UnitDefinition("milligray", "milliGy", "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy", "Dose", microgray);
  new G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray);
  new G4UnitDefinition("picogray", "picoGy", "Dose", picogray);

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Register(fEdep);
  accumulableManager->Register(fEdep2);
  if (fTargetCenter == G4ThreeVector()) {
    const DetectorConstruction* detConstruction =
      static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fTargetCenter = detConstruction->GetTargetCenter();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  SensitiveDetector::currentRun = run->GetRunID();
  SensitiveDetector::ResetCounters();

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  //man->SetNtupleDirectoryName(Ntupledir);
  // Add date and time to the output filename
  G4int eventsize = run->GetNumberOfEventToBeProcessed();
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  char date_mmdd[8];
  strftime(date_mmdd, sizeof(date_mmdd), "%m%d", ltm);
  char datetime[32];
  snprintf(datetime, sizeof(datetime), "%d_%s", eventsize, date_mmdd);
  G4String filename = G4String("rootfiles/output_") + datetime + ".root";
  man->OpenFile(filename);

  man->CreateH1("Gamma", "Gamma_KE", 100, 0., 8000*MeV);

  man->CreateNtuple("Particles", "Particles");
  man->CreateNtupleIColumn("fEventID");
  man->CreateNtupleIColumn("fTrackID");
  man->CreateNtupleSColumn("fParticleName");
  man->CreateNtupleIColumn("fPID");
  man->CreateNtupleFColumn("fParticleMass");
  man->CreateNtupleFColumn("fX");
  man->CreateNtupleFColumn("fY");
  man->CreateNtupleFColumn("fZ");
  man->CreateNtupleFColumn("fX_TC");
  man->CreateNtupleFColumn("fY_TC");
  man->CreateNtupleFColumn("fZ_TC");
  man->CreateNtupleFColumn("fPostX");
  man->CreateNtupleFColumn("fPostY");
  man->CreateNtupleFColumn("fPostZ");
  man->CreateNtupleFColumn("fPostX_TC");
  man->CreateNtupleFColumn("fPostY_TC");
  man->CreateNtupleFColumn("fPostZ_TC");
  man->CreateNtupleFColumn("fPx");
  man->CreateNtupleFColumn("fPy");
  man->CreateNtupleFColumn("fPz");
  man->CreateNtupleFColumn("fP");
  man->CreateNtupleFColumn("fKE");
  man->CreateNtupleFColumn("fTheta_P");
  man->CreateNtupleFColumn("fTheta_R");
  man->CreateNtupleFColumn("fPhi");
  man->CreateNtupleIColumn("fParentID");
  man->CreateNtupleSColumn("fCreatorProcess");
  man->CreateNtupleSColumn("fPostProcess");
  man->CreateNtupleSColumn("fType");
  man->FinishNtuple(0);

  man->CreateNtuple("Primaries", "Primaries");
  man->CreateNtupleIColumn(1, "fEventID");
  man->CreateNtupleFColumn(1, "fX_emitted");
  man->CreateNtupleFColumn(1, "fY_emitted");
  man->CreateNtupleFColumn(1, "fZ_emitted");
  man->CreateNtupleFColumn(1, "fX_emitted_TC");
  man->CreateNtupleFColumn(1, "fY_emitted_TC");
  man->CreateNtupleFColumn(1, "fZ_emitted_TC");
  man->CreateNtupleFColumn(1, "fPx_emitted");
  man->CreateNtupleFColumn(1, "fPy_emitted");
  man->CreateNtupleFColumn(1, "fPz_emitted");
  man->CreateNtupleFColumn(1, "fKE_emitted");
  man->CreateNtupleFColumn(1, "fX_hit");
  man->CreateNtupleFColumn(1, "fY_hit");
  man->CreateNtupleFColumn(1, "fZ_hit");
  man->CreateNtupleFColumn(1, "fX_hit_TC");
  man->CreateNtupleFColumn(1, "fY_hit_TC");
  man->CreateNtupleFColumn(1, "fZ_hit_TC");
  man->CreateNtupleFColumn(1, "fPx_hit");
  man->CreateNtupleFColumn(1, "fPy_hit");
  man->CreateNtupleFColumn(1, "fPz_hit");
  man->CreateNtupleFColumn(1, "fKE_hit");
  man->FinishNtuple(1);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance
  //
  G4double edep = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();

  G4double rms = edep2 - edep * edep / nofEvents;
  if (rms > 0.)
    rms = std::sqrt(rms);
  else
    rms = 0.;

  const auto detConstruction = static_cast<const DetectorConstruction*>(
    G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detConstruction->GetScoringVolume()->GetMass();
  G4double dose = edep / mass;
  G4double rmsDose = rms / mass;

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const auto generatorAction = static_cast<const PrimaryGeneratorAction*>(
    G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction) {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy, "Energy");
  }

  // Print
  //
  if (IsMaster()) {
    G4cout << G4endl << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout << G4endl << "--------------------End of Local Run------------------------";
  }

  G4cout << G4endl << " The run consists of " << nofEvents << " " << runCondition << G4endl
         << " Cumulated dose per run, in scoring volume : " << G4BestUnit(dose, "Dose")
         << " rms = " << G4BestUnit(rmsDose, "Dose") << G4endl
         << " Energy = " << fEdep.GetValue()<< G4endl
         << "------------------------------------------------------------" << G4endl << G4endl;

  G4cout << "Total hits: " << SensitiveDetector::allHits.size() << G4endl;

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  SensitiveDetector::allHits.clear();
  man->Write();
  man->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double edep)
{
  fEdep += edep;
  fEdep2 += edep * edep;
  //G4cout<<" fEdep added!"<<fEdep.GetValue()<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
