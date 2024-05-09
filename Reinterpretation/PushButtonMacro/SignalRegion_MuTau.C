#ifdef __CLING__
#pragma cling optimize(0)
#endif
void SignalRegion_MuTau()
{
//=========Macro generated from canvas: c_MuTau/MuTau
//=========  (Thu May  9 09:08:01 2024) by ROOT version 6.30/03
   TCanvas *c_MuTau = new TCanvas("c_MuTau", "MuTau",1327,410,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_MuTau->Range(-1578.947,-951.2195,6315.789,6365.854);
   c_MuTau->SetFillColor(0);
   c_MuTau->SetBorderMode(0);
   c_MuTau->SetBorderSize(2);
   c_MuTau->SetTickx(1);
   c_MuTau->SetTicky(1);
   c_MuTau->SetLeftMargin(0.2);
   c_MuTau->SetRightMargin(0.04);
   c_MuTau->SetTopMargin(0.05);
   c_MuTau->SetBottomMargin(0.13);
   c_MuTau->SetFrameFillStyle(0);
   c_MuTau->SetFrameBorderMode(0);
   c_MuTau->SetFrameFillStyle(0);
   c_MuTau->SetFrameBorderMode(0);
   
   Double_t Graph_fx3[59] = { 605.7923, 269.5406, 222.4218, 139.1774, 374.9521, 80.11356, 116.4307, 167.4353, 354.7954, 817.0861, 226.4585, 180.1461, 170.1951, 466.1736, 418.3397, 73.26794, 135.5459,
   237.8125, 90.15318, 276.9532, 169.2311, 241.189, 146.515, 255.9955, 75.79166, 144.0586, 77.50301, 168.2577, 74.89553, 60.79702, 80.65092, 146.3037, 340.4062,
   158.1058, 132.1845, 76.79939, 192.2447, 81.71536, 238.9268, 121.7196, 278.2382, 411.0194, 296.4488, 105.9713, 235.7162, 103.121, 168.6971, 330.1744, 208.5681,
   162.0742, 230.591, 241.9389, 409.4367, 187.455, 438.8088, 53.86158, 324.5135, 239.8727, 528.6748 };
   Double_t Graph_fy3[59] = { 3061.212, 860.0612, 553.5316, 366.1831, 390.1561, 175.2122, 280.5847, 282.9319, 365.1354, 1164.25, 238.5354, 525.7245, 299.6199, 1455.529, 432.7328, 424.3882, 326.7497,
   473.513, 238.9915, 393.3286, 244.6445, 307.3699, 373.408, 1180.591, 475.6068, 361.4314, 530.8965, 286.448, 266.0496, 367.6233, 818.8204, 346.3422, 793.036,
   196.6217, 371.3661, 474.4624, 266.2256, 268.2168, 338.6946, 742.7189, 683.1901, 489.8635, 471.5176, 230.3093, 237.9462, 462.8308, 452.9666, 768.6513, 283.7946,
   232.2131, 256.6821, 262.1749, 1128.003, 335.241, 483.3431, 305.261, 989.7498, 479.3239, 671.1223 };
   TGraph *graph = new TGraph(59,Graph_fx3,Graph_fy3);
   graph->SetName("");
   graph->SetTitle("#mu#tau_{h}#gamma");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","#mu#tau_{h}#gamma",100,0,6000);
   Graph_Graph3->SetMinimum(0);
   Graph_Graph3->SetMaximum(6000);
   Graph_Graph3->SetDirectory(nullptr);
   Graph_Graph3->SetStats(0);
   Graph_Graph3->SetLineStyle(0);
   Graph_Graph3->SetMarkerStyle(20);
   Graph_Graph3->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph3->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph3);
   
   graph->Draw("ap");
   
   Double_t Graph_fx4[25] = { 351.9449, 514.6376, 211.3599, 803.6651, 283.4612, 326.1252, 186.9784, 2339.261, 108.5588, 67.17348, 285.0274, 196.226, 715.8615, 147.2868, 748.5622, 149.1228, 243.8761,
   147.0076, 330.3368, 197.144, 78.37581, 142.1521, 231.8228, 62.55448, 427.4041 };
   Double_t Graph_fy4[25] = { 979.2516, 531.6962, 393.2299, 910.1262, 298.0349, 381.1622, 233.9064, 3125.72, 389.0256, 513.2703, 360.7074, 202.8891, 1106.187, 282.0168, 841.3004, 330.8831, 816.1414,
   218.9953, 580.5537, 223.2874, 282.7703, 267.3118, 247.4021, 410.4667, 626.7664 };
   graph = new TGraph(25,Graph_fx4,Graph_fy4);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(9);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","",100,0,2566.932);
   Graph_Graph4->SetMinimum(182.6002);
   Graph_Graph4->SetMaximum(3418.003);
   Graph_Graph4->SetDirectory(nullptr);
   Graph_Graph4->SetStats(0);
   Graph_Graph4->SetLineStyle(0);
   Graph_Graph4->SetMarkerStyle(20);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph4->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph4->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph4->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph4);
   
   graph->Draw("p, ");
   
   TLegend *leg = new TLegend(0.6,0.2,0.875,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","1-prong: 59 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(8);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","3-prong: 25 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(9);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   TLatex *   tex = new TLatex(0.96,0.96,"138 fb^{-1} (13 TeV)");
   tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.2342,0.9213,"CMS");
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.0375);
   tex->SetLineWidth(2);
   tex->Draw();
   c_MuTau->Modified();
   c_MuTau->SetSelected(c_MuTau);
}
