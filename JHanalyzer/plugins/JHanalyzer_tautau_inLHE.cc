// -*- C++ -*-
//
// Package:    Analyzer/JHanalyzer_tautau_inLHE
// Class:      JHanalyzer_tautau_inLHE
// 
/**\class JHanalyzer_tautau_inLHE JHanalyzer_tautau_inLHE.cc Analyzer/JHanalyzer_tautau_inLHE/plugins/JHanalyzer_tautau_inLHE.cc

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
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"



using namespace edm;
using namespace reco;
using namespace std;

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Run.h"//to use edm::Run                                                                                 


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

class JHanalyzer_tautau_inLHE : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit JHanalyzer_tautau_inLHE(const edm::ParameterSet&);
      ~JHanalyzer_tautau_inLHE();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  //GenEventInfoProduct                   "generator"                 ""                "SIM"   

  edm::EDGetTokenT<GenParticleCollection> genParticles_Token;
  edm::EDGetTokenT<GenEventInfoProduct> genInfo_Token;
  edm::EDGetTokenT<LHEEventProduct> LHEInfo_Token;




  TTree *TEvents;
  
  ///variables//
  double m_tautau;
  double ee_tautau;
  double pt_tautau;
  double eta_tautau;
  double phi_tautau;
  double px_tautau;
  double py_tautau;
  double pz_tautau;


  vector<double> pt_tau;
  vector<double> eta_tau;
  vector<double> phi_tau;
  vector<double> m_tau;
  vector<double> px_tau;
  vector<double> py_tau;
  vector<double> pz_tau;
  vector<double> ee_tau;

  double ntau;
  double njet;
  //scale for pdf//
  double Q;




  vector<double> weight_i; 
  
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
JHanalyzer_tautau_inLHE::JHanalyzer_tautau_inLHE(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
 
  //vector<reco::GenParticle>             "genParticles"              ""                "SIM"     

  usesResource("TFileService");
   genParticles_Token = consumes<GenParticleCollection>(edm::InputTag("genParticles"));
   genInfo_Token = consumes<GenEventInfoProduct>(edm::InputTag("generator"));
   LHEInfo_Token = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));

}


JHanalyzer_tautau_inLHE::~JHanalyzer_tautau_inLHE()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JHanalyzer_tautau_inLHE::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  ////////////initialize/////////////

  px_tautau=0;
  py_tautau=0;
  pz_tautau=0;
  ee_tautau=0;
  pt_tautau=0;
  eta_tautau=0;
  phi_tautau=0;
  m_tautau=0;



  Q=0;
  ntau=0;
  njet=0;
   using namespace edm;
   edm::Handle<LHEEventProduct> LHEInfo;
   iEvent.getByToken(LHEInfo_Token, LHEInfo);


   //---LHE info and reweight---//
   int lheinfoweightsize= LHEInfo->weights().size();
   int lheinfocommentssize = LHEInfo->comments_size();
   double w0=LHEInfo->originalXWGTUP();
   //cout <<"lheinfoweightsize="<<lheinfoweightsize<<endl;
   for (int i_lhe =0; i_lhe < lheinfoweightsize; i_lhe++){
     //weight id in lhe file//
     //cout<<"weight_id="<<LHEInfo->weights()[i_lhe].id<<endl;
     weight_i.push_back(LHEInfo->weights()[i_lhe].wgt/w0);
     //event weight//
     //cout<<LHEInfo->weights()[i_lhe].wgt/w0<<endl;                                                                                      
     
     
   }
   cout<<"lheinfocommentssize="<<lheinfocommentssize<<endl;
   for (int i =0; i < lheinfocommentssize; i++){                                                                                          
     // cout<<"comment i ="<<i<<"=" << LHEInfo->getComment(i)<<endl;                                                                       
   }                                                                                                                                        
   


   /*
  ///variables//                                                                                                                             
  vector<double> m_tautau;
  vector<double> pt_tautau;
  vector<double> eta_tautau;
  vector<double> phi_tautau;
  vector<double> px_tautau;
  vector<double> py_tautau;
  vector<double> pz_tautau;


  vector<double> pt_tau;
  vector<double> eta_tau;
  vector<double> phi_tau;
  vector<double> m_tau;


  vector<double> njet;
  //scale for pdf//                                                                                                                          
  vector<double> x1,x2,Q;

    */
   

      
   ntau=0;
   const lhef::HEPEUP& lheEvent = LHEInfo->hepeup();
   std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
   Int_t nLHEParticle = lheParticles.size();
 
   /////Particle Loop/////
   for( Int_t idxParticle = 0; idxParticle < nLHEParticle; ++idxParticle ){

     Int_t id = lheEvent.IDUP[idxParticle];
     Int_t status = lheEvent.ISTUP[idxParticle];
     double px = lheParticles[idxParticle][0];
     double py = lheParticles[idxParticle][1];
     double pz = lheParticles[idxParticle][2];
     double ee = lheParticles[idxParticle][3];
     double mm = lheParticles[idxParticle][4];
     //cout<<"idxParticle="<<idxParticle<<" id="<<id<<" status="<<status<<" px="<<px<<" py="<<py<<" pz="<<pz<<" ee="<<ee<<" mm="<<mm<<endl;
     //only final state tau in LHE level
     if( abs(id)==15 && status==1  ) ntau+=1;
     else if( (abs(id) == 1 || abs(id)== 2 || abs(id)==3 || abs(id)==4 || abs(id)==5|| abs(id)==6 || abs(id)==21 ) && status ==1 ){

       njet+=1;
       continue;
     }
     else continue;
     //if(ntau > 2) return;
     
     //now final state tau//
     TLorentzVector  v;
     v.SetPxPyPzE(px,py,pz,ee);
     double pt=v.Perp();
     double eta=v.Eta();
     double phi=v.Phi();
     double m=v.M();


     px_tau.push_back(px);
     py_tau.push_back(py);
     pz_tau.push_back(pz);
     ee_tau.push_back(ee);
     
     pt_tau.push_back(pt);
     eta_tau.push_back(eta);
     phi_tau.push_back(phi);
     m_tau.push_back(m);
     

     if(ntau<3){
       px_tautau+=px;
       py_tautau+=py;
       pz_tautau+=pz;
       ee_tautau+=ee;



	 

     }
       


   }

   TLorentzVector vv;
   vv.SetPxPyPzE(px_tautau,py_tautau,pz_tautau,ee_tautau);
   pt_tautau=vv.Perp();
   eta_tautau=vv.Eta();
   phi_tautau=vv.Phi();
   m_tautau=vv.M();
   px_tautau=vv.Px();
   py_tautau=vv.Py();
   pz_tautau=vv.Pz();
   ee_tautau=vv.E();
   Q=lheEvent.SCALUP;
   //x1=lheEvent.XPDWUP.first;
   // x2=lheEvent.XPDWUP.second;
   TEvents->Fill();


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
JHanalyzer_tautau_inLHE::beginJob()
{
  cout<<"begin job"<<endl;

  edm::Service<TFileService> fs;
  TEvents=fs->make<TTree>("TEvents","TEvents");
  //TEvents->Branch("Z_pt",&Z_pt,"Z_pt/D");
  TEvents->Branch("px_tau","std::vector<double>",&px_tau);
  TEvents->Branch("py_tau","std::vector<double>",&py_tau);
  TEvents->Branch("pz_tau","std::vector<double>",&pz_tau);
  TEvents->Branch("ee_tau","std::vector<double>",&ee_tau);
  TEvents->Branch("pt_tau","std::vector<double>",&pt_tau);
  TEvents->Branch("eta_tau","std::vector<double>",&eta_tau);
  TEvents->Branch("phi_tau","std::vector<double>",&phi_tau);
  TEvents->Branch("m_tau","std::vector<double>",&m_tau);
  TEvents->Branch("weight_i","std::vector<double>",&weight_i);


  TEvents->Branch("px_tautau",&px_tautau,"px_tautau/D");
  TEvents->Branch("py_tautau",&py_tautau,"py_tautau/D");
  TEvents->Branch("pz_tautau",&pz_tautau,"pz_tautau/D");
  TEvents->Branch("ee_tautau",&ee_tautau,"ee_tautau/D");
  TEvents->Branch("pt_tautau",&pt_tautau,"pt_tautau/D");
  TEvents->Branch("eta_tautau",&eta_tautau,"eta_tautau/D");
  TEvents->Branch("phi_tautau",&phi_tautau,"phi_tautau/D");
  TEvents->Branch("m_tautau",&m_tautau,"m_tautau/D");

  TEvents->Branch("ntau",&ntau,"ntau/D");
  TEvents->Branch("njet",&njet,"njet/D");
  
  TEvents->Branch("Q",&Q,"Q/D");
  

  cout<<"end of beginjob"<<endl;


}

// ------------ method called once each job just after ending the event loop  ------------
void 
JHanalyzer_tautau_inLHE::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JHanalyzer_tautau_inLHE::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JHanalyzer_tautau_inLHE);
