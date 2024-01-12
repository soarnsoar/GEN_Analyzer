// -*- C++ -*-
//
// Package:    Analyzer/JHanalyzer_Bmeson
// Class:      JHanalyzer_Bmeson
// 
/**\class JHanalyzer_Bmeson JHanalyzer_Bmeson.cc Analyzer/JHanalyzer_Bmeson/plugins/JHanalyzer_Bmeson.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  JunHo Choi
//         Created:  Fri, 23 Mar 2018 03:24:18 GMT
//
//

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

class JHanalyzer_Bmeson : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit JHanalyzer_Bmeson(const edm::ParameterSet&);
      ~JHanalyzer_Bmeson();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  //GenEventInfoProduct                   "generator"                 ""                "SIM"   

  edm::EDGetTokenT<GenParticleCollection> genParticles_Token;
  edm::EDGetTokenT<GenEventInfoProduct> genInfo_Token;


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
JHanalyzer_Bmeson::JHanalyzer_Bmeson(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
 
  //vector<reco::GenParticle>             "genParticles"              ""                "SIM"     

  usesResource("TFileService");
   genParticles_Token = consumes<GenParticleCollection>(edm::InputTag("genParticles"));
   genInfo_Token = consumes<GenEventInfoProduct>(edm::InputTag("generator"));

}


JHanalyzer_Bmeson::~JHanalyzer_Bmeson()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JHanalyzer_Bmeson::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  ////////////initialize/////////////


   using namespace edm;
   Handle<reco::GenParticleCollection> genParticles;
   iEvent.getByToken(genParticles_Token, genParticles);//genParticle                                                                                         
   edm::Handle<GenEventInfoProduct> genInfo;
   iEvent.getByToken(genInfo_Token, genInfo);
   //GenEventInfoProduct                   "generator"                 ""                "SIM"   //

   //weight=genInfo->weight();


   //   for(int i = 0; i < gensize; ++ i) {///scan all gen particles
  // const GenParticle & p = (*genParticles)[i];
     
   //}///end of gen loop
   unsigned int gensize= genParticles->size();
   
   //vector<vector<int>> gen_motherindex;
   vector<int> gen_motherindex;
   for(unsigned int i = 0; i < gensize; ++ i) {
     const GenParticle & p = (*genParticles)[i];
     int mother = -1;
     //vector<int> _this_motherlist;
     for( reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit ) {
       if( p.mother()==&(*mit) ) {
         mother = std::distance(genParticles->begin(),mit);//first mother...
         break;
	 //_this_motherlist.push_back(mother);
       }
      

     }
     gen_motherindex.push_back(mother);
     //gen_motherindex.push_back(_this_motherlist);
     //cout << "nmother=" << _this_motherlist.size() << endl;
   }//end of find motherindex
   //cout<<"#########################"<<endl;
   cout<<"@@Nparticle="<<gensize<<endl;
   cout << "i" << setw(15) << "status " << setw(15) << "pid" << setw(15) << "pt" << setw(15) << "eta" << setw(15) << "phi" << setw(15) << "E" << setw(15) << "M" << setw(15) << "motheridx" << setw(15) << "mother pid" << endl;
   for(unsigned int i = 0; i < gensize; ++ i) {
     //https://github.com/cms-sw/cmssw/blob/master/DataFormats/HepMCCandidate/interface/GenParticle.h
     const GenParticle & p = (*genParticles)[i];
     int pid = p.pdgId();
     int fromhard=p.statusFlags().fromHardProcess();
     int status = p.status();
     double pt = p.pt();//https://github.com/cms-sw/cmssw/blob/e8154a2ff2a04ce4431ed5ed83d6ae84913c90c3/DataFormats/Candidate/interface/LeafCandidate.h#L140
     double eta = p.eta();
     double phi = p.phi();
     double px = p.px();
     double py = p.py();
     double pz = p.pz();
     double ee = p.energy();
     double mass = p.mass();
     int prompt = p.statusFlags().isPrompt();//
     int motheridx = gen_motherindex[i];
     
     if(motheridx>-1){
       //if(  abs( genParticles->at(motheridx).pdgId()  ) == 511 || abs(pid)==511){
       if(  abs( genParticles->at(motheridx).pdgId()  ) == 511 && abs(pid)==511){
	 cout << "!!!!!!" << endl;
	 cout << i << setw(15) << status  << setw(15) << pid << setw(15) << pt << setw(15) << eta << setw(15) << phi << setw(15) << ee << setw(15) << mass << setw(15) << motheridx << setw(15) << genParticles->at(motheridx).pdgId() << endl;
       }
     }
   }


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
 fsr_t->Fill();
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
JHanalyzer_Bmeson::beginJob()
{


}

// ------------ method called once each job just after ending the event loop  ------------
void 
JHanalyzer_Bmeson::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JHanalyzer_Bmeson::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JHanalyzer_Bmeson);
