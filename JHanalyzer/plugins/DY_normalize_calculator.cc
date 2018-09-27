// -*- C++ -*-
//
// Package:    Analyzer/JHanalyzer_muon_status2223
// Class:      JHanalyzer_muon_status2223
// 
/**\class JHanalyzer_muon_status2223 JHanalyzer_muon_status2223.cc Analyzer/JHanalyzer_muon_status2223/plugins/JHanalyzer_muon_status2223.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  JunHo Choi
//         Created:  Fri, 23 Mar 2018 03:24:18 GMT
//DY_preFSR_analyzer_boson_added
//
//LHEEventProduct
//externalLHEProducer
//LHERunInfoProduct
//vector<reco::GenParticle>             "prunedGenParticles"        ""                "PAT"     

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"



using namespace edm;
using namespace reco;
using namespace std;

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"

#include <TTree.h>
#include <TFile.h>
#include <TLorentzVector.h>


//
// Class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class DY_normalize_calculator : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit DY_normalize_calculator(const edm::ParameterSet&);
      ~DY_normalize_calculator();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  //GenEventInfoProduct                   "generator"                 ""                "SIM"   


  edm::EDGetTokenT<GenEventInfoProduct> genInfo_Token;

  
  ///For Photon info///
  TTree * truweight;

  double weight;
  //  double promptphoton;

      // ----------member data ---------------------------
};
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DY_normalize_calculator::DY_normalize_calculator(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
 
  //vector<reco::GenParticle>             "genParticles"              ""                "SIM"     

  usesResource("TFileService");//genParticles

   genInfo_Token = consumes<GenEventInfoProduct>(edm::InputTag("generator"));


}


DY_normalize_calculator::~DY_normalize_calculator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DY_normalize_calculator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  cout<<"start analyze"<<endl;

  weight=1;
//////////////////////


   using namespace edm;

   edm::Handle<GenEventInfoProduct> genInfo;
   iEvent.getByToken(genInfo_Token, genInfo);
   

   ///end of LHE info//
   weight=genInfo->weight();


   
   truweight->Fill();
   //
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   //Handle<ExampleData> pIn;
   // iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   // ESHandle<SetupData> pSetup;
   //iSetup.get<SetupRecord>().get(pSetup);
#endif
}



/*
 Fsr_t->Fill();
   fsr_p->Fill();
   fsr_pl->Fill();
   photon_t->Fill();
   isr_t->Fill();

   fsr01_1->Fill();
   fsr01_2->Fill();

   fsr02_1->Fill();
   fsr02_2->Fill();

   fsr03_1->Fill();
   fsr03_2->Fill();

   fsr04_1->Fill();
   fsr04_2->Fill();
 */

// ------------ method called once each job just before starting event loop  ------------
void 
DY_normalize_calculator::beginJob()
{
  cout<<"beginjob"<<endl;
  edm::Service<TFileService> fs;
 


  truweight = fs->make<TTree>("truweight","truweight");



  truweight->Branch("weight",&weight,"weight/D");

  cout<<"end of beginjob"<<endl;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DY_normalize_calculator::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DY_normalize_calculator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DY_normalize_calculator);
