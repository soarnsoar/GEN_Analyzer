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

#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <TLorentzVector.h>



//Range of weight//




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



  //TH1D (const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup)

  //tautau//
  vector<TH1D*> h_m_tautau;
  vector<TH1D*> h_ee_tautau;
  vector<TH1D*> h_pt_tautau;
  vector<TH1D*> h_eta_tautau;
  vector<TH1D*> h_phi_tautau;
  vector<TH1D*> h_px_tautau;
  vector<TH1D*> h_py_tautau;
  vector<TH1D*> h_pz_tautau;

  

  double m_tautau;
  double ee_tautau;
  double pt_tautau;
  double eta_tautau;
  double phi_tautau;
  double px_tautau;
  double py_tautau;
  double pz_tautau;





  //tau//
  vector<TH1D*> h_pt_tau;
  vector<TH1D*> h_eta_tau;
  vector<TH1D*> h_phi_tau;
  vector<TH1D*> h_m_tau;
  vector<TH1D*> h_px_tau;
  vector<TH1D*> h_py_tau;
  vector<TH1D*> h_pz_tau;
  vector<TH1D*> h_ee_tau;

  vector<double> pt_tau;
  vector<double> eta_tau;
  vector<double> phi_tau;
  vector<double> m_tau;
  vector<double> px_tau;
  vector<double> py_tau;
  vector<double> pz_tau;
  vector<double> ee_tau;

  //extra//

  vector<TH1D*> h_ntau;
  vector<TH1D*> h_njet;
  vector<TH1D*> h_Q;
  
  double ntau;
  double njet;
  //scale for pdf//
  double Q;






  vector<int> id_weight;
  int istart;
  int iend;
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
JHanalyzer_tautau_inLHE::JHanalyzer_tautau_inLHE(const edm::ParameterSet& iConfig) :
  istart(iConfig.getParameter<uint32_t>("istart")),
  iend(iConfig.getParameter<uint32_t>("iend"))
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
  vector<double> weight_i; 
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
   //cout<<"id_weight.size="<<id_weight.size()<<endl;
   //cout<<"lheinfoweightsize="<<lheinfoweightsize<<endl;
   for (unsigned int i_w = 0 ; i_w< id_weight.size(); i_w++){
     for (int i_lhe =0; i_lhe < lheinfoweightsize; i_lhe++){
       //weight id in lhe file//
       //cout <<"id_weight[i_w]"<<id_weight[i_w]<<endl;
       //cout<<"LHEInfo->weights()[i_lhe].id="<<LHEInfo->weights()[i_lhe].id<<endl;
       
       if(TString::Itoa(id_weight[i_w],10)==LHEInfo->weights()[i_lhe].id  ){//if index is matched
	 weight_i.push_back(LHEInfo->weights()[i_lhe].wgt/w0);
	 //cout<<"!!!MATCH!!!"<<endl;
       }
       //cout<<"i_lhe="<<i_lhe<<"weight_id="<<LHEInfo->weights()[i_lhe].id<<endl;
       //weight_i.push_back(LHEInfo->weights()[i_lhe].wgt/w0);
       //event weight//
       //cout<<LHEInfo->weights()[i_lhe].wgt/w0<<endl;                                                                                      
     
       
     }
   }
   //cout<<"lheinfocommentssize="<<lheinfocommentssize<<endl;
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


  
   
   

   //FillHisto//
   //for all weights
   cout<<"weight_i.size="<<weight_i.size()<<endl;
   
   for(unsigned int i_w=0 ;i_w < weight_i.size(); i_w++){
     double this_w=weight_i[i_w];
     
     //tau variables//
     for(unsigned int i_tau=0; i_tau < ntau;i_tau++){
       //cout<<this_w<<endl;
       //cout<<"px_tau[i_tau]="<<px_tau[i_tau]<<endl;
       //cout<<"py_tau[i_tau]="<<py_tau[i_tau]<<endl;
       //cout<<"pz_tau[i_tau]="<<pz_tau[i_tau]<<endl;
       //cout<<"ee_tau[i_tau]="<<ee_tau[i_tau]<<endl;
       
       h_pt_tau.at(i_w)->Fill(pt_tau[i_tau],this_w);
       h_eta_tau.at(i_w)->Fill(eta_tau[i_tau],this_w);
       h_phi_tau.at(i_w)->Fill(phi_tau[i_tau],this_w);
       h_m_tau.at(i_w)->Fill(m_tau[i_tau],this_w);
       h_px_tau.at(i_w)->Fill(px_tau[i_tau],this_w);
       h_py_tau.at(i_w)->Fill(py_tau[i_tau],this_w);
       h_pz_tau.at(i_w)->Fill(pz_tau[i_tau],this_w);
       h_ee_tau.at(i_w)->Fill(ee_tau[i_tau],this_w);



     }

     //event variables//
     h_pt_tautau.at(i_w)->Fill(pt_tautau,this_w);
     h_eta_tautau.at(i_w)->Fill(eta_tautau,this_w);
     h_phi_tautau.at(i_w)->Fill(phi_tautau,this_w);
     h_m_tautau.at(i_w)->Fill(m_tautau,this_w);
     h_px_tautau.at(i_w)->Fill(px_tautau,this_w);
     h_py_tautau.at(i_w)->Fill(py_tautau,this_w);
     h_pz_tautau.at(i_w)->Fill(pz_tautau,this_w);
     h_ee_tautau.at(i_w)->Fill(ee_tautau,this_w);

     h_ntau.at(i_w)->Fill(ntau,this_w);
     h_njet.at(i_w)->Fill(njet,this_w);
     h_Q.at(i_w)->Fill(Q,this_w);
   }
   

   //x1=lheEvent.XPDWUP.first;
   // x2=lheEvent.XPDWUP.second;
   //TEvents->Fill();


   


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
  
  ////Set weight id to save////
  //int istart =2001; int iend=2090; // for mg232 dytautau sample. lhapdf=292200
  cout << "##istart=" << istart << endl;
  cout << "##iend=" << iend<< endl;
  
  for (int i = istart; i < iend+1; i++){ 
    id_weight.push_back(i);
  }
  

  edm::Service<TFileService> fs;
  int N_weight=id_weight.size();
  for( int i = 0 ; i < N_weight; i++){
    TString str_id_weight=TString::Itoa(id_weight[i],10);
    TH1D *h;

    
    h_m_tautau.push_back(h);
    h_px_tautau.push_back(h);
    h_py_tautau.push_back(h);
    h_pz_tautau.push_back(h);
    h_ee_tautau.push_back(h);
    h_pt_tautau.push_back(h);
    h_eta_tautau.push_back(h);
    h_phi_tautau.push_back(h);

    h_m_tau.push_back(h);
    h_px_tau.push_back(h);
    h_py_tau.push_back(h);
    h_pz_tau.push_back(h);
    h_ee_tau.push_back(h);
    h_pt_tau.push_back(h);
    h_eta_tau.push_back(h);
    h_phi_tau.push_back(h);
    h_ntau.push_back(h);
    h_njet.push_back(h);
    h_Q.push_back(h);


    







    
    h_m_tautau.at(i)=fs->make<TH1D>("h_m_tautau_"+str_id_weight,"h_m_tautau_"+str_id_weight,1000,0.,1000.);
    h_px_tautau.at(i)=fs->make<TH1D>("h_px_tautau_"+str_id_weight,"h_px_tautau_"+str_id_weight,1000,-500.,500.);
    h_py_tautau.at(i)=fs->make<TH1D>("h_py_tautau_"+str_id_weight,"h_py_tautau_"+str_id_weight,1000,-500.,500.);
    h_pz_tautau.at(i)=fs->make<TH1D>("h_pz_tautau_"+str_id_weight,"h_pz_tautau_"+str_id_weight,1000,-500.,500.);
    h_ee_tautau.at(i)=fs->make<TH1D>("h_ee_tautau_"+str_id_weight,"h_ee_tautau_"+str_id_weight,1000,0.,1000.);
    h_pt_tautau.at(i)=fs->make<TH1D>("h_pt_tautau_"+str_id_weight,"h_pt_tautau_"+str_id_weight,500,0.,500.);
    h_eta_tautau.at(i)=fs->make<TH1D>("h_eta_tautau_"+str_id_weight,"h_eta_tautau_"+str_id_weight,100,-5.,5.);
    h_phi_tautau.at(i)=fs->make<TH1D>("h_phi_tautau_"+str_id_weight,"h_phi_tautau_"+str_id_weight,100,-4,4);

    h_m_tau.at(i)=fs->make<TH1D>("h_m_tau_"+str_id_weight,"h_m_tau_"+str_id_weight,1000, 0., 1000.);
    h_px_tau.at(i)=fs->make<TH1D>("h_px_tau_"+str_id_weight,"h_px_tau_"+str_id_weight,1000,-500.,500.);
    h_py_tau.at(i)=fs->make<TH1D>("h_py_tau_"+str_id_weight,"h_py_tau_"+str_id_weight,1000,-500.,500.);
    h_pz_tau.at(i)=fs->make<TH1D>("h_pz_tau_"+str_id_weight,"h_pz_tau_"+str_id_weight,1000,-500.,500.);
    h_ee_tau.at(i)=fs->make<TH1D>("h_ee_tau_"+str_id_weight,"h_ee_tau_"+str_id_weight,1000,0.,1000.);
    h_pt_tau.at(i)=fs->make<TH1D>("h_pt_tau_"+str_id_weight,"h_pt_tau_"+str_id_weight,1000,-500.,500.);
    h_eta_tau.at(i)=fs->make<TH1D>("h_eta_tau_"+str_id_weight,"h_eta_tau_"+str_id_weight,100,-5,5);
    h_phi_tau.at(i)=fs->make<TH1D>("h_phi_tau_"+str_id_weight,"h_phi_tau_"+str_id_weight,100,-4,4);

    h_ntau.at(i)=fs->make<TH1D>("h_ntau_"+str_id_weight,"h_ntau_"+str_id_weight,5,0,5);
    h_njet.at(i)=fs->make<TH1D>("h_njet_"+str_id_weight,"h_njet_"+str_id_weight,5,0,5);
    h_Q.at(i)=fs->make<TH1D>("h_Q_"+str_id_weight,"h_Q_"+str_id_weight,1000,0,1000);


    //delete h
  }
  
  



  //TEvents->Branch("Z_pt",&Z_pt,"Z_pt/D");
  
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
