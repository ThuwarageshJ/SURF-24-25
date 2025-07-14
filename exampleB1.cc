//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under the terms  and *
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
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "QBBC.hh"
#include "QGSP_BERT.hh"
#include "FTFP_BERT.hh"
#include "G4EmExtraPhysics.hh"

#include "G4Gamma.hh"
#include "G4GammaConversionToMuons.hh"
#include "G4ProcessManager.hh"
#include "G4WrapperProcess.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "G4BiasingProcessInterface.hh"
#include "G4BiasingHelper.hh"

#include "G4GenericBiasingPhysics.hh"
#include "G4EmExtraParameters.hh"
#include "G4EmParameters.hh"

#include "G4PhysicsListHelper.hh"

// #include "Randomize.hh"

using namespace B1;

namespace B1{
class CustomPhysicsList : public FTFP_BERT {
  public:
      CustomPhysicsList() : FTFP_BERT(){
        G4EmParameters::Instance()->SetGeneralProcessActive(false);
      }
  
      ~CustomPhysicsList() {}
      
      // void ConstructProcess()
      // {
      //   FTFP_BERT::ConstructProcess();
        
      //   G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
      //   G4ParticleDefinition* particle = G4Gamma::Gamma();
      //   G4GammaConversionToMuons* gammaMuConv = new G4GammaConversionToMuons();
      //   gammaMuConv -> SetCrossSecFactor(1000.0);
      //   ph->RegisterProcess(gammaMuConv, particle);
        
      //   G4cout << "G4GammaConversionToMuons process registered for gamma particles" << G4endl;
      // }
  };
}

namespace B1{
void PrintProcesses() {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleTable::G4PTblDicIterator *particleIterator = particleTable->GetIterator();
      particleIterator->reset();

      while ((*particleIterator)()) {
          G4ParticleDefinition *particle = particleIterator->value();
          G4String particleName = particle->GetParticleName();
          G4ProcessManager *pmanager = particle->GetProcessManager();
          G4cout << "Particle: " << particleName << G4endl;

          if (pmanager) {
              G4ProcessVector *processVector = pmanager->GetProcessList();
              for (size_t i = 0; i < processVector->size(); ++i) {
                  G4VProcess *process = (*processVector)[i];
                  G4String processName = process->GetProcessName();
                  G4cout << " Process: " << processName << G4endl;
              }
          } else {
              G4cout << " No process manager found for this particle." << G4endl;
          }
      }
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  G4cout << "Hello from main!" << G4endl;
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4bool biasingFlag = false;

  if (argc>=3){
    biasingFlag = (std::string(argv[2]) == "on") ? true : false;
  }
  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);

  // use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);
  // Construct the default run manager
  //
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  
  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new DetectorConstruction(biasingFlag));

  auto physicsList = new CustomPhysicsList();
  // G4GammaConversionToMuons* ha = new G4GammaConversionToMuons();
  // ha->SetCrossSecFactor(1000);

  if(biasingFlag){
    G4GenericBiasingPhysics *biasingPhysics = new G4GenericBiasingPhysics();

    const std::vector<G4String> biasedList = {"GammaToMuPair"};
    biasingPhysics->Bias("gamma", biasedList);
    physicsList->RegisterPhysics(biasingPhysics);
    G4cout << "      ********************************************************* " << G4endl;
    G4cout << "      ********** processes are wrapped for biasing ************ " << G4endl;
    G4cout << "      ********************************************************* " << G4endl;
  }
  PrintProcesses();
  physicsList->DumpList();
  runManager->SetUserInitialization(physicsList);
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());
  // Initialize visualization with the default graphics system
  auto visManager = new G4VisExecutive(argc, argv);
  // Constructors can also take optional arguments:
  // - a graphics system of choice, eg. "OGL"
  // - and a verbosity argument - see /vis/verbose guidance.
  // auto visManager = new G4VisExecutive(argc, argv, "OGL", "Quiet");
  // auto visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();
  // Process macro or start UI session

  //
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
  //std::cin.get();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
