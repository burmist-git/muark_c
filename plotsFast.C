void plotsFast(){
  
  TString fileN;
  //fileN = "./Run_003.root";
  //fileN = "./Run_009_Charge_and_Time_Data_10_26_2020.root";
  fileN = "./Run_010_Charge_and_Time_Data_10_27_2020.root";
  TFile *f1 = new TFile(fileN.Data());
  TTree *tree = (TTree*)f1->Get("T");

  //
  TH1F *h1_amplitude_ch0 = new TH1F("h1_amplitude_ch0","amplitude ch0",3000,-2.5,0.1);
  TH1F *h1_amplitude_ch1 = new TH1F("h1_amplitude_ch1","amplitude ch1",3000,-2.5,0.1);
  TH1F *h1_pulseArrivalTime_ch0 = new TH1F("h1_pulseArrivalTime_ch0","pulseArrivalTime ch0",3000,-1.0,80*3);
  TH1F *h1_pulseArrivalTime_ch1 = new TH1F("h1_pulseArrivalTime_ch1","pulseArrivalTime ch1",3000,-1.0,80*3);
  TH1F *h1_dTime = new TH1F("h1_dTime","dTime (ch0 - ch1)",4000,-100.0,100.0);
  //
  TH2F *h1_amplitude_ch1_vs_ch0 = new TH2F("h1_amplitude_ch1_vs_ch0","amplitude ch1 vs ch0",400,-2.5,0.1,400,-2.5,0.1);
  //
  TH1F *h1_amplitude_cut_ch0 = new TH1F("h1_amplitude_cut_ch0","amplitude cut ch0",3000,-2.5,0.1);
  TH1F *h1_amplitude_cut_ch1 = new TH1F("h1_amplitude_cut_ch1","amplitude cut ch1",3000,-2.5,0.1);
  TH1F *h1_pulseArrivalTime_cut_ch0 = new TH1F("h1_pulseArrivalTime_cut_ch0","pulseArrivalTime cut ch0",3000,-1.0,80*3);
  TH1F *h1_pulseArrivalTime_cut_ch1 = new TH1F("h1_pulseArrivalTime_cut_ch1","pulseArrivalTime cut ch1",3000,-1.0,80*3);
  TH1F *h1_dTime_cut = new TH1F("h1_dTime_cut","dTime cut (ch0 - ch1)",4000,-100.0,100.0);

  //TH1F *h1_nphot = new TH1F("h1_nphot","nphot",20,0.0,20);
  //TH2F *h2_y_vs_x_hit = new TH2F("h2_y_vs_x_hit","y vs x hit",200,-200.0,200.0,200,-200.0,200.0);

  tree->Draw("amplitude[0]>>h1_amplitude_ch0");
  tree->Draw("amplitude[1]>>h1_amplitude_ch1");
  tree->Draw("pulseArrivalTime[0]>>h1_pulseArrivalTime_ch0");
  tree->Draw("pulseArrivalTime[1]>>h1_pulseArrivalTime_ch1");
  tree->Draw("(pulseArrivalTime[0]-pulseArrivalTime[1])>>h1_dTime");
  //
  TString cutStr;
  //Run_003.root
  //cutStr="((pulseArrivalTime[0]-pulseArrivalTime[1]) > 36) && ((pulseArrivalTime[0]-pulseArrivalTime[1]) < 39)";
  //cutStr+="&& (amplitude[0] < -0.07)";
  //cutStr+="&& (amplitude[1] < -0.1)";
  //cutStr="(amplitude[1] < -1.0)";
  //Run_009_Charge_and_Time_Data_10_26_2020.root";
  //cutStr="((pulseArrivalTime[0] > 45) && (pulseArrivalTime[0] < 60))";
  //cutStr+="&& ((pulseArrivalTime[1] > 78) && (pulseArrivalTime[1] < 96))";
  //cutStr+="&& (amplitude[0] < -0.5)";
  //cutStr+="&& (amplitude[1] < -0.5)";
  //Run_010_Charge_and_Time_Data_10_27_2020.root
  cutStr="((pulseArrivalTime[0] > 80) && (pulseArrivalTime[0] < 96))";
  cutStr+="&& ((pulseArrivalTime[1] > 40) && (pulseArrivalTime[1] < 60))";
  cutStr+="&& (amplitude[0] < -0.03)";
  cutStr+="&& (amplitude[1] < -0.5)";
  //
  tree->Draw("amplitude[0]>>h1_amplitude_cut_ch0",cutStr.Data());
  tree->Draw("amplitude[1]>>h1_amplitude_cut_ch1",cutStr.Data());
  tree->Draw("pulseArrivalTime[0]>>h1_pulseArrivalTime_cut_ch0",cutStr.Data());
  tree->Draw("pulseArrivalTime[1]>>h1_pulseArrivalTime_cut_ch1",cutStr.Data());
  tree->Draw("(pulseArrivalTime[0]-pulseArrivalTime[1])>>h1_dTime_cut",cutStr.Data());
  //
  tree->Draw("amplitude[1]:amplitude[0]>>h1_amplitude_ch1_vs_ch0",cutStr.Data());
  
  //tree->Draw("mcHit.x:mcHit.y>>h2_y_vs_x_hit");
  //likelihood distributions for efficiency calculation 
  //h_pi = new TH2F("h_pi","h_pi",pbin,pstart,pstop,50000,-200,200);
  //h_K = new TH2F("h_K","h_K",pbin,pstart,pstop,50000,-200,200); 
  //ch->Draw("(logL.pi-logL.K):mcHit.p>>h_pi","abs(mcHit.PDG)==211 && primary==1");
  //ch->Draw("(logL.pi-logL.K):mcHit.p>>h_K","abs(mcHit.PDG)==321 && primary==1");  
  // 2D histogram of K efficiency vs. pi fake rate vs. momentum (to je faca)
  //hh = new TH2F("hh","K id. efficiency;Momentum [GeV];#pi missid. prob.",pbin,pstart,pstop,100,0.005,0.10); 
  // 1D histograms of K efficiency vs. momentum for 3 different pion fake rates
  //TH1F* h_eff1 = new TH1F("h_eff1","Kaon id. efficiency at 2% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 
  //TH1F* h_eff2 = new TH1F("h_eff2","Kaon id. efficiency at 4% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 
  //TH1F* h_eff3 = new TH1F("h_eff3","Kaon id. efficiency at 2%,4%,6% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 

  //
  h1_amplitude_cut_ch0->SetLineColor(kRed);
  h1_amplitude_cut_ch1->SetLineColor(kRed);
  h1_pulseArrivalTime_cut_ch0->SetLineColor(kRed);
  h1_pulseArrivalTime_cut_ch1->SetLineColor(kRed);
  h1_dTime_cut->SetLineColor(kRed);
  //
  
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);

  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.09);

  c1->Divide(3,2);
  c1->cd(1);
  h1_amplitude_ch0->Draw();
  h1_amplitude_cut_ch0->Draw("same");
  c1->cd(2);
  h1_amplitude_ch1->Draw();
  h1_amplitude_cut_ch1->Draw("same");
  c1->cd(4);
  h1_pulseArrivalTime_ch0->Draw();
  h1_pulseArrivalTime_cut_ch0->Draw("same");
  c1->cd(5);
  h1_pulseArrivalTime_ch1->Draw();
  h1_pulseArrivalTime_cut_ch1->Draw("same");
  c1->cd(6);
  h1_dTime->Draw();
  h1_dTime_cut->Draw("same");
  //
  c1->cd(3);
  h1_amplitude_ch1_vs_ch0->Draw("ZCOLOR");

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  //h1_nphot->Draw();

  //h2_y_vs_x_hit->Draw("ZCOLOR");
}
