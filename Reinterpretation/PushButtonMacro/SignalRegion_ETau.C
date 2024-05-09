#ifdef __CLING__
#pragma cling optimize(0)
#endif
void SignalRegion_ETau()
{
//=========Macro generated from canvas: c_ETau/ETau
//=========  (Thu May  9 09:07:34 2024) by ROOT version 6.30/03
   TCanvas *c_ETau = new TCanvas("c_ETau", "ETau",103,537,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_ETau->Range(-1578.947,-951.2195,6315.789,6365.854);
   c_ETau->SetFillColor(0);
   c_ETau->SetBorderMode(0);
   c_ETau->SetBorderSize(2);
   c_ETau->SetTickx(1);
   c_ETau->SetTicky(1);
   c_ETau->SetLeftMargin(0.2);
   c_ETau->SetRightMargin(0.04);
   c_ETau->SetTopMargin(0.05);
   c_ETau->SetBottomMargin(0.13);
   c_ETau->SetFrameFillStyle(0);
   c_ETau->SetFrameBorderMode(0);
   c_ETau->SetFrameFillStyle(0);
   c_ETau->SetFrameBorderMode(0);
   
   Double_t Graph_fx1[41] = { 129.0576, 189.9817, 373.4706, 155.5825, 263.0032, 296.9265, 251.7598, 183.7128, 169.6233, 177.0053, 226.6913, 121.5156, 257.1689, 419.9987, 101.8109, 728.4952, 60.17837,
   817.201, 370.5422, 144.5045, 69.13374, 134.9233, 166.9688, 104.9206, 218.3362, 133.5971, 532.2877, 182.3528, 86.36743, 122.3882, 718.7362, 1761.813, 52.47724,
   280.1347, 408.4519, 54.74392, 235.4891, 111.0667, 495.6254, 206.7441, 90.16321 };
   Double_t Graph_fy1[41] = { 286.6593, 491.2535, 483.7285, 432.763, 387.1464, 307.2563, 416.8382, 686.5387, 518.0114, 389.7571, 269.7402, 235.8688, 438.1288, 876.5725, 142.5102, 1014.82, 355.0847,
   871.4875, 452.6487, 415.9586, 411.8144, 223.5249, 197.9058, 238.3413, 528.7435, 232.7145, 678.4143, 462.2296, 353.8559, 163.9141, 949.9609, 5181.479, 294.0331,
   332.893, 516.9855, 295.4889, 290.1168, 208.8233, 756.6091, 292.7796, 99.3961 };
   TGraph *graph = new TGraph(41,Graph_fx1,Graph_fy1);
   graph->SetName("");
   graph->SetTitle("e#tau_{h}#gamma");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","e#tau_{h}#gamma",100,0,6000);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(6000);
   Graph_Graph1->SetDirectory(nullptr);
   Graph_Graph1->SetStats(0);
   Graph_Graph1->SetLineStyle(0);
   Graph_Graph1->SetMarkerStyle(20);
   Graph_Graph1->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("ap");
   
   Double_t Graph_fx2[22] = { 145.41, 72.99173, 70.92158, 204.1326, 340.5949, 123.9075, 400.8178, 111.05, 63.98508, 213.2921, 446.543, 226.8407, 117.2659, 136.6524, 96.85616, 532.5793, 126.432,
   214.3904, 319.9348, 487.524, 179.112, 184.8359 };
   Double_t Graph_fy2[22] = { 236.3533, 241.617, 285.261, 340.7227, 357.9142, 226.6367, 421.8664, 373.7509, 412.2383, 271.8565, 530.1425, 305.2176, 456.3667, 394.8323, 270.9519, 1080.658, 147.9153,
   544.3028, 352.7005, 869.0994, 347.6511, 248.7342 };
   graph = new TGraph(22,Graph_fx2,Graph_fy2);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(9);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","",100,17.12566,579.4387);
   Graph_Graph2->SetMinimum(54.64096);
   Graph_Graph2->SetMaximum(1173.932);
   Graph_Graph2->SetDirectory(nullptr);
   Graph_Graph2->SetStats(0);
   Graph_Graph2->SetLineStyle(0);
   Graph_Graph2->SetMarkerStyle(20);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph2->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph2->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph2->GetZaxis()->SetTitleOffset(1);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   graph->Draw("p, ");
   
   TLegend *leg = new TLegend(0.6,0.2,0.875,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","1-prong: 41 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(8);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","3-prong: 22 events","P");
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
   c_ETau->Modified();
   c_ETau->SetSelected(c_ETau);
}
