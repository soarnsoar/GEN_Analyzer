// -*- C++ -*-
//
// Package:    Analyzer/DYanalyzerGEN
// Class:      DYanalyzerGEN
// 
/**\class DYanalyzerGEN DYanalyzerGEN.cc Analyzer/DYanalyzerGEN/plugins/DYanalyzerGEN.cc

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

#include "TH1F.h"
#include "TFile.h"

using namespace edm;
using namespace reco;
using namespace std;

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"



//#include <TTree.h>
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

class DYanalyzerGEN : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit DYanalyzerGEN(const edm::ParameterSet&);
  ~DYanalyzerGEN();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  //TFile * outputFile_;

  TH1F * h_dimuon_pt, * h_dimuon_eta, * h_dimuon_phi, *h_dimuon_mass;
  TH1F * h_muonp_pt, * h_muonp_eta, * h_muonp_phi, *h_muonp_mass;
  TH1F * h_muonm_pt, * h_muonm_eta, * h_muonm_phi, *h_muonm_mass;

  TH1F * h_dielectron_pt, * h_dielectron_eta, * h_dielectron_phi, *h_dielectron_mass;
  TH1F * h_electronp_pt, * h_electronp_eta, * h_electronp_phi, *h_electronp_mass;
  TH1F * h_electronm_pt, * h_electronm_eta, * h_electronm_phi, *h_electronm_mass;
  
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
DYanalyzerGEN::DYanalyzerGEN(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
 
  //vector<reco::GenParticle>             "genParticles"              ""                "SIM"     

  usesResource("TFileService");
   genParticles_Token = consumes<GenParticleCollection>(edm::InputTag("genParticles"));
   genInfo_Token = consumes<GenEventInfoProduct>(edm::InputTag("generator"));

}


DYanalyzerGEN::~DYanalyzerGEN()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DYanalyzerGEN::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  ////////////initialize/////////////


   using namespace edm;
   Handle<reco::GenParticleCollection> genParticles;
   iEvent.getByToken(genParticles_Token, genParticles);//genParticle                                                                                         
   edm::Handle<GenEventInfoProduct> genInfo;
   iEvent.getByToken(genInfo_Token, genInfo);
   //GenEventInfoProduct                   "generator"                 ""                "SIM"   //
   
   float weight=genInfo->weight();


   //   for(int i = 0; i < gensize; ++ i) {///scan all gen particles
  // const GenParticle & p = (*genParticles)[i];
     
   //}///end of gen loop
   int gensize= genParticles->size();
   
   vector<int> gen_motherindex;
   for(int i = 0; i < gensize; ++ i) {
     const GenParticle & p = (*genParticles)[i];

     int mother = -1;
     
     for( reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit ) {
       if( p.mother()==&(*mit) ) {
         mother = std::distance(genParticles->begin(),mit);
         break;
       }


     }
     gen_motherindex.push_back(mother);
     
   }//end of find motherindex










   //cout<<"@@Nparticle="<<gensize<<endl;
   //Particles//

   int i_muonp=-1, i_muonm=-1;
   int i_electronp=-1, i_electronm=-1;
   

   for(int i = 0; i < gensize; ++ i) {
     const GenParticle & p = (*genParticles)[i];
     int id = p.pdgId();
     int fromhard=p.statusFlags().fromHardProcess();
     int status = p.status();
     //double px = p.px();
     //double py = p.py();
     //double pz = p.pz();
     //double ee = p.energy();
     int prompt = p.statusFlags().isPrompt();



     if(prompt && fromhard && status==1){
       //cout<<"i="<<i<<" status="<<status<<" id="<<id<<" mother="<<gen_motherindex[i]<<endl;
       if(id==13){
	 i_muonp=i;
       }
       else if(id==-13){
	 i_muonm=i;
       }
       else if(id==11){
	 i_electronp=i;
       }
       else if(id==-11){
	 i_electronm=i;
       }


     }
   }
   TLorentzVector vp,vm,vdilep;
   if(i_muonp!=-1 && i_muonm!=-1){ //if dimuon events
     
     const GenParticle & lepp = (*genParticles)[i_muonp];
     const GenParticle & lepm = (*genParticles)[i_muonm];

     vp.SetPxPyPzE(lepp.px(),lepp.py(),lepp.pz(),lepp.energy());
     vm.SetPxPyPzE(lepm.px(),lepm.py(),lepm.pz(),lepm.energy());
     vdilep=vp+vm;
     
     
     h_dimuon_pt->Fill(  vdilep.Perp(),weight );
     h_dimuon_eta->Fill(  vdilep.Eta() ,weight);
     h_dimuon_phi->Fill(  vdilep.Phi() ,weight);
     h_dimuon_mass->Fill(  vdilep.M() ,weight);

     h_muonp_pt->Fill(vp.Perp(),weight);
     h_muonp_eta->Fill(vp.Eta(),weight);
     h_muonp_phi->Fill(vp.Phi(),weight);

     h_muonm_pt->Fill(vm.Perp(),weight);
     h_muonm_eta->Fill(vm.Eta(),weight);
     h_muonm_phi->Fill(vm.Phi(),weight);

   }
   else if(i_electronp!=-1 && i_electronm != -1){ //if dielectron events


     const GenParticle & lepp = (*genParticles)[i_electronp];
     const GenParticle & lepm = (*genParticles)[i_electronm];
     
     vp.SetPxPyPzE(lepp.px(),lepp.py(),lepp.pz(),lepp.energy());
     vm.SetPxPyPzE(lepm.px(),lepm.py(),lepm.pz(),lepm.energy());
     vdilep=vp+vm;
     
     
     h_dielectron_pt->Fill(  vdilep.Perp() ,weight);
     h_dielectron_eta->Fill(  vdilep.Eta() ,weight);
     h_dielectron_phi->Fill( vdilep.Phi() ,weight);
     h_dielectron_mass->Fill( vdilep.M() ,weight);

     h_electronp_pt->Fill(vp.Perp(),weight);
     h_electronp_eta->Fill(vp.Eta(),weight);
     h_electronp_phi->Fill(vp.Phi(),weight);

     h_electronm_pt->Fill(vm.Perp(),weight);
     h_electronm_eta->Fill(vm.Eta(),weight);
     h_electronm_phi->Fill(vm.Phi(),weight);



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



// ------------ method called once each job just before starting event loop  ------------
void 
DYanalyzerGEN::beginJob()
{
  edm::Service<TFileService> fs;

  //outputFile_ = new TFile( "histoGEN.root", "RECREATE" );  
  /**
  TH1F * h_dimuon_pt, * h_dimuon_eta, * h_dimuon_phi, *h_dimuon_mass;
  TH1F * h_muonp_pt, * h_muonp_eta, * h_muonp_phi, *h_muonp_mass;
  TH1F * h_muonm_pt, * h_muonm_eta, * h_muonm_phi, *h_muonm_mass;

  TH1F * h_dielectron_pt, * h_dielectron_eta, * h_dielectron_phi, *h_dielectron_mass;
  TH1F * h_elep_pt, * h_elep_eta, * h_elep_phi, *h_elep_mass;
  TH1F * h_elem_pt, * h_elem_eta, * h_elem_phi, *h_elem_mass;
  **/
  h_dimuon_pt=fs->make<TH1F>("dimuon_pt","pT(#mu#mu)",50,0,100);
  h_dimuon_eta=fs->make<TH1F>("dimuon_eta","#eta(#mu#mu)",50,-5,5);
  h_dimuon_phi=fs->make<TH1F>("dimuon_phi","#phi(#mu#mu)",50,-4,4);
  h_dimuon_mass=fs->make<TH1F>("dimuon_mass","M(#mu#mu)",50,40,140);

  h_muonp_pt=fs->make<TH1F>("muonp_pt","pT(#mu+)",50,0,100);
  h_muonp_eta=fs->make<TH1F>("muonp_eta","#eta(#mu+)",50,-5,5);
  h_muonp_phi=fs->make<TH1F>("muonp_phi","#phi(#mu+)",50,-4,4);


  h_muonm_pt=fs->make<TH1F>("muonm_pt","pT(#mu-)",50,0,100);
  h_muonm_eta=fs->make<TH1F>("muonm_eta","#eta(#mu-)",50,-5,5);
  h_muonm_phi=fs->make<TH1F>("muonm_phi","#phi(#mu-)",50,-4,4);


  h_dielectron_pt=fs->make<TH1F>("dielectron_pt","pT(ee)",50,0,100);
  h_dielectron_eta=fs->make<TH1F>("dielectron_eta","#eta(ee)",50,-5,5);
  h_dielectron_phi=fs->make<TH1F>("dielectron_phi","#phi(ee)",50,-4,4);
  h_dielectron_mass=fs->make<TH1F>("dielectron_mass","M(ee)",50,40,140);


  h_electronp_pt=fs->make<TH1F>("electronp_pt","pT(e+)",50,0,100);
  h_electronp_eta=fs->make<TH1F>("electronp_eta","#eta(e+)",50,-5,5);
  h_electronp_phi=fs->make<TH1F>("electronp_phi","#phi(e+)",50,-4,4);


  h_electronm_pt=fs->make<TH1F>("electronm_pt","pT(e-)",50,0,100);
  h_electronm_eta=fs->make<TH1F>("electronm_eta","#eta(e-)",50,-5,5);
  h_electronm_phi=fs->make<TH1F>("electronm_phi","#phi(e-)",50,-4,4);

  
    


}

// ------------ method called once each job just after ending the event loop  ------------
void 
DYanalyzerGEN::endJob() 
{
  //outputFile_->Write();
  //outputFile_->Close();

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DYanalyzerGEN::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DYanalyzerGEN);
