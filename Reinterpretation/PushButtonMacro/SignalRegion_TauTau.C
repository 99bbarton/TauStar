#ifdef __CLING__
#pragma cling optimize(0)
#endif
void SignalRegion_TauTau()
{
//=========Macro generated from canvas: c_TauTau/TauTau
//=========  (Thu May  9 09:08:27 2024) by ROOT version 6.30/03
   TCanvas *c_TauTau = new TCanvas("c_TauTau", "TauTau",67,382,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_TauTau->Range(-1578.947,-951.2195,6315.789,6365.854);
   c_TauTau->SetFillColor(0);
   c_TauTau->SetBorderMode(0);
   c_TauTau->SetBorderSize(2);
   c_TauTau->SetTickx(1);
   c_TauTau->SetTicky(1);
   c_TauTau->SetLeftMargin(0.2);
   c_TauTau->SetRightMargin(0.04);
   c_TauTau->SetTopMargin(0.05);
   c_TauTau->SetBottomMargin(0.13);
   c_TauTau->SetFrameFillStyle(0);
   c_TauTau->SetFrameBorderMode(0);
   c_TauTau->SetFrameFillStyle(0);
   c_TauTau->SetFrameBorderMode(0);
   
   Double_t Graph_fx5[60] = { 151.3547, 231.0141, 778.3325, 86.54205, 525.8122, 145.0286, 206.9138, 137.7002, 212.3169, 291.6674, 152.8056, 107.2275, 277.1103, 59.43156, 328.7989, 151.2296, 106.5608,
   98.4726, 169.1531, 143.726, 109.0544, 565.2507, 179.6461, 407.0396, 108.8802, 134.7443, 202.7484, 360.4036, 275.9856, 394.6246, 140.1145, 175.6763, 185.5105,
   129.9887, 216.9445, 99.85422, 532.3759, 105.7108, 136.6489, 146.9976, 259.9381, 209.8997, 78.94966, 120.1665, 235.7826, 282.0501, 231.2387, 395.4024, 50.48038,
   112.6312, 140.9106, 152.9212, 481.5781, 142.3033, 170.6667, 178.7946, 121.4075, 111.53, 413.5515, 132.1305 };
   Double_t Graph_fy5[60] = { 350.8557, 287.2748, 1542.52, 276.3183, 1512.186, 268.1361, 229.2807, 262.5666, 304.8028, 345.1287, 276.0703, 566.4855, 338.4816, 287.6259, 638.3698, 303.4715, 258.8474,
   194.4475, 427.6865, 149.0745, 168.7584, 593.1776, 370.9439, 798.4213, 551.0842, 273.207, 395.8518, 425.1862, 337.0548, 642.681, 240.5083, 420.9118, 422.2477,
   197.4932, 287.2578, 171.3329, 708.3751, 400.2828, 397.4517, 276.3179, 512.1372, 239.7927, 352.7623, 425.0085, 600.7783, 384.1601, 314.3991, 643.4521, 262.7697,
   552.961, 249.7244, 166.1886, 1149.239, 222.2063, 589.6366, 221.0975, 356.6824, 352.8158, 541.4108, 181.9854 };
   TGraph *graph = new TGraph(60,Graph_fx5,Graph_fy5);
   graph->SetName("");
   graph->SetTitle("#tau_{h}#tau_{h}#gamma");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","#tau_{h}#tau_{h}#gamma",100,0,6000);
   Graph_Graph5->SetMinimum(0);
   Graph_Graph5->SetMaximum(6000);
   Graph_Graph5->SetDirectory(nullptr);
   Graph_Graph5->SetStats(0);
   Graph_Graph5->SetLineStyle(0);
   Graph_Graph5->SetMarkerStyle(20);
   Graph_Graph5->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph5->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph5->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph5->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph5->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph5->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph5->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph5->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph5->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph5->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph5);
   
   graph->Draw("ap");
   
   Double_t Graph_fx6[28] = { 136.4825, 82.47861, 105.1947, 636.8141, 134.7858, 43.53759, 207.2553, 276.535, 165.7324, 115.6749, 135.6037, 271.5265, 157.7349, 284.776, 370.9437, 216.5126, 147.365,
   88.03145, 131.8063, 201.3382, 92.51708, 157.7895, 249.3754, 143.3967, 139.4203, 166.7797, 219.6564, 176.0669 };
   Double_t Graph_fy6[28] = { 233.2085, 157.9795, 224.0422, 906.8841, 138.751, 356.7756, 821.1541, 296.8181, 406.9968, 196.5328, 172.3978, 481.523, 276.5338, 391.124, 388.8084, 271.2009, 319.2422,
   378.0294, 419.824, 242.353, 178.0424, 220.707, 381.5013, 264.1662, 156.3705, 290.3495, 319.5273, 344.5213 };
   graph = new TGraph(28,Graph_fx6,Graph_fy6);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(9);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","",100,0,696.1417);
   Graph_Graph6->SetMinimum(61.9377);
   Graph_Graph6->SetMaximum(983.6974);
   Graph_Graph6->SetDirectory(nullptr);
   Graph_Graph6->SetStats(0);
   Graph_Graph6->SetLineStyle(0);
   Graph_Graph6->SetMarkerStyle(20);
   Graph_Graph6->GetXaxis()->SetLabelFont(42);
   Graph_Graph6->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph6->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph6->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph6->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   Graph_Graph6->GetYaxis()->SetLabelFont(42);
   Graph_Graph6->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph6->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph6->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph6->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph6->GetYaxis()->SetTitleFont(42);
   Graph_Graph6->GetZaxis()->SetLabelFont(42);
   Graph_Graph6->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph6->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph6->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph6->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph6->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph6);
   
   graph->Draw("p, ");
   
   TLegend *leg = new TLegend(0.6,0.2,0.875,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","1-prong: 60 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(8);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","3-prong: 28 events","P");
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
   c_TauTau->Modified();
   c_TauTau->SetSelected(c_TauTau);
}
