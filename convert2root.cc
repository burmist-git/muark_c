//Date        : Thu Oct 22 15:54:41 CEST 2020
//Autor       : Leonid Burmistrov
//Description : Converts the data from muon ark.

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int _verbose = 1;

using namespace std;

void conv2root(TString inData, TString outRoot);

int main(int argc, char *argv[]){
  
  TString inData;
  TString outRoot;
  if(argc == 3 ){
    inData = argv[1];
    outRoot = argv[2];
    if(_verbose>0){
      cout<<"In data file  : "<<inData<<endl
	  <<"Out root file : "<<outRoot<<endl;
    }
    conv2root( inData, outRoot);
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"        [1] - In data file"<<endl
        <<"        [2] - out root file"<<endl;
  }

  return 0;
}

void conv2root(TString inData, TString outRoot){
  //=== Charge [pC], Pulse Arrival Time[ns], Amplitude[V] === TRIG DELAY = 1 ==  OFFSET CH0 = 0.00 == TRIG ENABLE CH0= 1 == TRIG THRESH CH0 = -0.02 === OFFSET CH1 = 0.00 == TRIG ENABLE CH1= 0 == TRIG THRESH CH1 = -0.02 ===
  //0.000 120.950 -0.035067   0.000  7.352 -0.002386 UnixTime = 1603637726.401 date = 2020.10.25, time = 7h.55m.26s.401ms RawTriggerRate =  0.000015 MHz
  //
  //0.000 121.831 -0.158125   0.000  0.883 0.001590 UnixTime = 1603637726.681 date = 2020.10.25, time = 7h.55m.26s.681ms RawTriggerRate =  0.000000 MHz
  const Int_t nChannels_c = 2;
  Int_t nChannels = nChannels_c;
  Int_t eventID = -1;
  Double_t UnixTime;
  Float_t rawTriggerRate;
  Float_t charge[nChannels_c], charge_ch0, charge_ch1;
  Float_t pulseArrivalTime[nChannels_c], pulseArrivalTime_ch0, pulseArrivalTime_ch1;
  Float_t amplitude[nChannels_c], amplitude_ch0, amplitude_ch1;
  ///////////////////Root file with data/////////////////
  TFile *hfile = new TFile( outRoot, "RECREATE", "USBWC Data", 1);
  if (hfile->IsZombie()) {
    cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	 << outRoot << ": check that the path is correct!!!"
	 << endl;
    exit(-1);
  }
  TTree *tree = new TTree("T", "USBWC measuremtns Data Tree");
  hfile->SetCompressionLevel(2);
  tree->SetAutoSave(1000000);
  // Create new event
  TTree::SetBranchStyle(0);
  //Event USBWC
  tree->Branch("nChannels",&nChannels, "nChannels/I");
  tree->Branch("eventID",&eventID, "eventID/I");
  tree->Branch("UnixTime",&UnixTime, "UnixTime/D");
  tree->Branch("rawTriggerRate",&rawTriggerRate ,"rawTriggerRateF");  
  tree->Branch("charge", charge, "charge[nChannels]/F");
  tree->Branch("pulseArrivalTime", pulseArrivalTime, "pulseArrivalTime[nChannels]/F");
  tree->Branch("amplitude", amplitude, "amplitude[nChannels]/F");  
  ///////////////////////////////////////////////////////
  eventID = -1;
  UnixTime = -999.0;
  rawTriggerRate = -999.0;
  for(int j = 0;j<nChannels;j++){
    charge[j] = -999.0;
    pulseArrivalTime[j] = -999.0;
    amplitude[j] = -999.0;
  }
  string mot;
  ifstream indata;
  indata.open(inData.Data()); 
  assert(indata.is_open());
  for(int i=0;i<45;i++)
    indata  >> mot;
  while ((indata>>charge_ch0>>pulseArrivalTime_ch0>>amplitude_ch0>>charge_ch1>>pulseArrivalTime_ch1>>amplitude_ch1) &&
	 (indata>>mot>>mot>>UnixTime) &&
	 (indata>>mot>>mot>>mot>>mot>>mot>>mot>>mot>>mot>>rawTriggerRate) &&
	 (indata>>mot)){
    eventID++;
    //
    charge[0] = charge_ch0;
    pulseArrivalTime[0] = pulseArrivalTime_ch0;
    amplitude[0] = amplitude_ch0;
    //
    charge[1] = charge_ch1;
    pulseArrivalTime[1] = pulseArrivalTime_ch1;
    amplitude[1] = amplitude_ch1;
    tree->Fill();
    if(_verbose>1){
      cout<<"nChannels      = "<<nChannels<<endl
	  <<"eventID        = "<<eventID<<endl
	  <<"UnixTime       = "<<UnixTime<<endl
	  <<"rawTriggerRate = "<<rawTriggerRate<<endl;
      for(int i = 0;i<nChannels;i++){
	cout<<setw(12)<<charge[i]
	    <<setw(12)<<pulseArrivalTime[i]
	    <<setw(12)<<amplitude[i]<<endl;
      }
    }
  }
  indata.close(); 
  hfile = tree->GetCurrentFile();
  hfile->Write();
  hfile->Close();
}
