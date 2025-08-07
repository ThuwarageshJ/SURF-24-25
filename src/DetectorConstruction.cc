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
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4LogicalVolumeStore.hh"

#include "GB01BOptrChangeCrossSection.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(G4bool bf, G4double target_thickness):
  fBiasingOn(bf),fTargetZ(target_thickness)
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Dimensions
  G4double env_sizeXY = 200 * cm;
  G4double env_sizeZ = 200 * cm;
  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4double targetXY = 10 * cm;
  G4double targetZ = fTargetZ * cm;

  // Positions
  G4ThreeVector pos_target = G4ThreeVector(0* cm, 0 * cm, 0 * cm);

  // Materials
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_Fe");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  auto solidWorld =
    new G4Box("World",  // its name
              0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        world_mat,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  
  // Envelope
  auto solidEnv = new G4Box("Envelope",  // its name
                            0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
                                      env_mat,  // its material
                                      "Envelope");  // its name

  auto physEnv = new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    logicEnv,  // its logical volume
                    "Envelope",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking
  
  // Tungsten Target
  auto solidTarget = new G4Box("Target", 0.5*targetXY, 0.5*targetXY, 0.5*targetZ);


  auto logicTarget = new G4LogicalVolume(solidTarget,  // its solid
                                         target_mat,  // its material
                                         "Target");  // its name
                  
  auto physTarget = new G4PVPlacement(nullptr,  // no rotation
                    pos_target,  // at position
                    logicTarget,  // its logical volume
                    "Target",  // its name
                    logicEnv,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking
  
  //
  // Detector
  //
  // G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Galactic");

  // G4int Nrings = 10;
  // G4int Ndetectors = Nrings + 4; 
  // G4double ringwidth_angle = 1.0*deg;
  // G4double startPhi = 0.0*deg;
  // G4double deltaPhi = 360.0*deg;
  // G4double detectorZ = 25.0*um;

  // //std::vector<G4PVPlacement*> physDetectors;
  // logicDetectors.reserve(Ndetectors);
  // //physDetectors.reserve(Ndetectors);

  // for (G4int i = 0; i < Nrings; i++) {
  //   G4double r_min = (env_sizeZ / 2) * std::tan(i * ringwidth_angle);
  //   G4double r_max = (env_sizeZ / 2) * std::tan((i + 1) * ringwidth_angle);
  //   G4Tubs* shellSolid = new G4Tubs("DetectorCell", r_min, r_max, 0.5 * detectorZ, startPhi, deltaPhi);
  //   G4LogicalVolume* logicDetector = new G4LogicalVolume(shellSolid, detector_mat, "Detector");
  //   auto physDetectorCell = new G4PVPlacement(nullptr,  // no rotation
  //                                             G4ThreeVector(0, 0, (env_sizeZ - detectorZ) / 2),  // at position
  //                                             logicDetector,  // its logical volume
  //                                             "DetectorCell",  // its name
  //                                             logicEnv,  // its mother volume
  //                                             false,  // no boolean operation
  //                                             i+1,  // copy number
  //                                             checkOverlaps);  // overlaps checking
  //   logicDetectors.push_back(logicDetector);
  //   //physDetectors.push_back(physDetectorCell);
  // }
  // G4double r_min = (env_sizeZ / 2) * std::tan((Nrings-1) * ringwidth_angle);
  // G4double r_max = (env_sizeZ / 2) * std::tan(Nrings * ringwidth_angle);
  // G4Tubs* shellSolid = new G4Tubs("DetectorCell", r_min, r_max, 0.5 * detectorZ, startPhi, deltaPhi);
  // //Hollow box-like shell (subtraction)
  // G4Box* outerBox = new G4Box("Outer", env_sizeXY/2, env_sizeXY/2, detectorZ/2);
  // G4SubtractionSolid* shell1 = new G4SubtractionSolid("Shell", outerBox, shellSolid,0, G4ThreeVector(0,0,0));
  // G4Box* outerBox1 = new G4Box("Outer", env_sizeXY/2, env_sizeXY/2,  (env_sizeZ/2 - detectorZ) / 2);
  // G4Box* innerBox1 = new G4Box("Inner", env_sizeXY/2 - detectorZ, env_sizeXY/2 - detectorZ,  (env_sizeZ/2 - detectorZ) / 2);
  // G4SubtractionSolid* shell2 = new G4SubtractionSolid("Shell", outerBox1, innerBox1, 0, G4ThreeVector(0,0,0));
  // G4UnionSolid* unionReg2 = new G4UnionSolid("Reg2", shell1, shell2, 0, G4ThreeVector(0, 0, -(env_sizeZ/4)));
  // G4LogicalVolume* logicDetector = new G4LogicalVolume(unionReg2, detector_mat, "Detector");
  // auto physDetectorCell = new G4PVPlacement(nullptr,  // no rotation
  //                                             G4ThreeVector(0, 0, (env_sizeZ- detectorZ) / 2),  // at position
  //                                             logicDetector,  // its logical volume
  //                                             "DetectorCell",  // its name
  //                                             logicEnv,  // its mother volume
  //                                             false,  // no boolean operation
  //                                             Nrings+1,  // copy number
  //                                             checkOverlaps);  // overlaps checking
  // logicDetectors.push_back(logicDetector);
  // //physDetectors.push_back(physDetectorCell);

  // G4Box* outerBox3 = new G4Box("Outer", env_sizeXY/2, env_sizeXY/2,  (env_sizeZ/2 - detectorZ) / 2);
  // G4Box* innerBox3 = new G4Box("Inner", env_sizeXY/2 - detectorZ, env_sizeXY/2 - detectorZ,  (env_sizeZ/2 - detectorZ) / 2);
  // G4SubtractionSolid* shell3 = new G4SubtractionSolid("Shell", outerBox3, innerBox3, 0, G4ThreeVector(0,0,0));
  // G4Box* Box3 = new G4Box("Left", env_sizeXY/2, env_sizeXY/2, detectorZ/2);
  // G4UnionSolid* unionReg3 = new G4UnionSolid("Reg3", shell3, Box3, 0, G4ThreeVector(0, 0, -(env_sizeZ/4)));
  // G4LogicalVolume* logicDetector3 = new G4LogicalVolume(unionReg3, detector_mat, "Detector");
  // auto physDetectorCell3 = new G4PVPlacement(nullptr,  // no rotation
  //                                             G4ThreeVector(0, 0, -(env_sizeZ/2- detectorZ) / 2),  // at position
  //                                             logicDetector3,  // its logical volume
  //                                             "DetectorCell",  // its name
  //                                             logicEnv,  // its mother volume
  //                                             false,  // no boolean operation
  //                                             Nrings+2,  // copy number
  //                                             checkOverlaps);  // overlaps checking
  // logicDetectors.push_back(logicDetector3);                                 
  
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicEnv;
  fTargetCenter = pos_target;
  fTargetVolume = logicTarget;

  //
  // always return the physical World
  //
  return physWorld;
}
void DetectorConstruction::ConstructSDandField()
{
  // Sensitive Detector
  //
  SensitiveDetector *SD = new SensitiveDetector("SensitiveDetector");
  
  SetSensitiveDetector("Target", SD, true);

  if(fBiasingOn) {
    // -- Fetch volume for biasing:
    G4LogicalVolume* logicVolumeBiased = G4LogicalVolumeStore::GetInstance()->GetVolume("Target");

    GB01BOptrChangeCrossSection *biasingOperator = new GB01BOptrChangeCrossSection("gamma", 1000);
    biasingOperator->AttachTo(logicVolumeBiased);
    G4cout << " Attaching biasing operator " << biasingOperator->GetName() << " to logical volume "
	   << logicVolumeBiased->GetName() << G4endl;
  }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
