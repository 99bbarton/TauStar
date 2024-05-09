#ifdef __CLING__
#pragma cling optimize(0)
#endif
void SignalRegion()
{
//=========Macro generated from canvas: c/
//=========  (Thu May  9 09:08:58 2024) by ROOT version 6.30/03
   TCanvas *c = new TCanvas("c", "",781,105,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->Range(-1578.947,-951.2195,6315.789,6365.854);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.2);
   c->SetRightMargin(0.04);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.13);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph_fx7[59] = { 605.7923, 269.5406, 222.4218, 139.1774, 374.9521, 80.11356, 116.4307, 167.4353, 354.7954, 817.0861, 226.4585, 180.1461, 170.1951, 466.1736, 418.3397, 73.26794, 135.5459,
   237.8125, 90.15318, 276.9532, 169.2311, 241.189, 146.515, 255.9955, 75.79166, 144.0586, 77.50301, 168.2577, 74.89553, 60.79702, 80.65092, 146.3037, 340.4062,
   158.1058, 132.1845, 76.79939, 192.2447, 81.71536, 238.9268, 121.7196, 278.2382, 411.0194, 296.4488, 105.9713, 235.7162, 103.121, 168.6971, 330.1744, 208.5681,
   162.0742, 230.591, 241.9389, 409.4367, 187.455, 438.8088, 53.86158, 324.5135, 239.8727, 528.6748 };
   Double_t Graph_fy7[59] = { 3061.212, 860.0612, 553.5316, 366.1831, 390.1561, 175.2122, 280.5847, 282.9319, 365.1354, 1164.25, 238.5354, 525.7245, 299.6199, 1455.529, 432.7328, 424.3882, 326.7497,
   473.513, 238.9915, 393.3286, 244.6445, 307.3699, 373.408, 1180.591, 475.6068, 361.4314, 530.8965, 286.448, 266.0496, 367.6233, 818.8204, 346.3422, 793.036,
   196.6217, 371.3661, 474.4624, 266.2256, 268.2168, 338.6946, 742.7189, 683.1901, 489.8635, 471.5176, 230.3093, 237.9462, 462.8308, 452.9666, 768.6513, 283.7946,
   232.2131, 256.6821, 262.1749, 1128.003, 335.241, 483.3431, 305.261, 989.7498, 479.3239, 671.1223 };
   TGraph *graph = new TGraph(59,Graph_fx7,Graph_fy7);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(7);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","",100,0,6000);
   Graph_Graph7->SetMinimum(0);
   Graph_Graph7->SetMaximum(6000);
   Graph_Graph7->SetDirectory(nullptr);
   Graph_Graph7->SetStats(0);
   Graph_Graph7->SetLineStyle(0);
   Graph_Graph7->SetMarkerStyle(20);
   Graph_Graph7->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph7->GetXaxis()->SetLabelFont(42);
   Graph_Graph7->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph7->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph7->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph7->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph7->GetXaxis()->SetTitleFont(42);
   Graph_Graph7->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph7->GetYaxis()->SetLabelFont(42);
   Graph_Graph7->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph7->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph7->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph7->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph7->GetYaxis()->SetTitleFont(42);
   Graph_Graph7->GetZaxis()->SetLabelFont(42);
   Graph_Graph7->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph7->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph7->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph7->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph7->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph7);
   
   graph->Draw("ap");
   
   Double_t Graph_fx8[25] = { 351.9449, 514.6376, 211.3599, 803.6651, 283.4612, 326.1252, 186.9784, 2339.261, 108.5588, 67.17348, 285.0274, 196.226, 715.8615, 147.2868, 748.5622, 149.1228, 243.8761,
   147.0076, 330.3368, 197.144, 78.37581, 142.1521, 231.8228, 62.55448, 427.4041 };
   Double_t Graph_fy8[25] = { 979.2516, 531.6962, 393.2299, 910.1262, 298.0349, 381.1622, 233.9064, 3125.72, 389.0256, 513.2703, 360.7074, 202.8891, 1106.187, 282.0168, 841.3004, 330.8831, 816.1414,
   218.9953, 580.5537, 223.2874, 282.7703, 267.3118, 247.4021, 410.4667, 626.7664 };
   graph = new TGraph(25,Graph_fx8,Graph_fy8);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(7);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph8 = new TH1F("Graph_Graph8","",100,0,2566.932);
   Graph_Graph8->SetMinimum(182.6002);
   Graph_Graph8->SetMaximum(3418.003);
   Graph_Graph8->SetDirectory(nullptr);
   Graph_Graph8->SetStats(0);
   Graph_Graph8->SetLineStyle(0);
   Graph_Graph8->SetMarkerStyle(20);
   Graph_Graph8->GetXaxis()->SetLabelFont(42);
   Graph_Graph8->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph8->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph8->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph8->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph8->GetXaxis()->SetTitleFont(42);
   Graph_Graph8->GetYaxis()->SetLabelFont(42);
   Graph_Graph8->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph8->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph8->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph8->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph8->GetYaxis()->SetTitleFont(42);
   Graph_Graph8->GetZaxis()->SetLabelFont(42);
   Graph_Graph8->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph8->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph8->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph8->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph8->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph8);
   
   graph->Draw("p, ");
   
   Double_t Graph_fx9[60] = { 151.3547, 231.0141, 778.3325, 86.54205, 525.8122, 145.0286, 206.9138, 137.7002, 212.3169, 291.6674, 152.8056, 107.2275, 277.1103, 59.43156, 328.7989, 151.2296, 106.5608,
   98.4726, 169.1531, 143.726, 109.0544, 565.2507, 179.6461, 407.0396, 108.8802, 134.7443, 202.7484, 360.4036, 275.9856, 394.6246, 140.1145, 175.6763, 185.5105,
   129.9887, 216.9445, 99.85422, 532.3759, 105.7108, 136.6489, 146.9976, 259.9381, 209.8997, 78.94966, 120.1665, 235.7826, 282.0501, 231.2387, 395.4024, 50.48038,
   112.6312, 140.9106, 152.9212, 481.5781, 142.3033, 170.6667, 178.7946, 121.4075, 111.53, 413.5515, 132.1305 };
   Double_t Graph_fy9[60] = { 350.8557, 287.2748, 1542.52, 276.3183, 1512.186, 268.1361, 229.2807, 262.5666, 304.8028, 345.1287, 276.0703, 566.4855, 338.4816, 287.6259, 638.3698, 303.4715, 258.8474,
   194.4475, 427.6865, 149.0745, 168.7584, 593.1776, 370.9439, 798.4213, 551.0842, 273.207, 395.8518, 425.1862, 337.0548, 642.681, 240.5083, 420.9118, 422.2477,
   197.4932, 287.2578, 171.3329, 708.3751, 400.2828, 397.4517, 276.3179, 512.1372, 239.7927, 352.7623, 425.0085, 600.7783, 384.1601, 314.3991, 643.4521, 262.7697,
   552.961, 249.7244, 166.1886, 1149.239, 222.2063, 589.6366, 221.0975, 356.6824, 352.8158, 541.4108, 181.9854 };
   graph = new TGraph(60,Graph_fx9,Graph_fy9);
   graph->SetName("");
   graph->SetTitle("#tau_{h}#tau_{h}#gamma");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph9 = new TH1F("Graph_Graph9","#tau_{h}#tau_{h}#gamma",100,0,6000);
   Graph_Graph9->SetMinimum(0);
   Graph_Graph9->SetMaximum(6000);
   Graph_Graph9->SetDirectory(nullptr);
   Graph_Graph9->SetStats(0);
   Graph_Graph9->SetLineStyle(0);
   Graph_Graph9->SetMarkerStyle(20);
   Graph_Graph9->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph9->GetXaxis()->SetLabelFont(42);
   Graph_Graph9->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph9->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph9->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph9->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph9->GetXaxis()->SetTitleFont(42);
   Graph_Graph9->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph9->GetYaxis()->SetLabelFont(42);
   Graph_Graph9->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph9->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph9->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph9->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph9->GetYaxis()->SetTitleFont(42);
   Graph_Graph9->GetZaxis()->SetLabelFont(42);
   Graph_Graph9->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph9->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph9->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph9->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph9->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph9);
   
   graph->Draw("p, ");
   
   Double_t Graph_fx10[28] = { 136.4825, 82.47861, 105.1947, 636.8141, 134.7858, 43.53759, 207.2553, 276.535, 165.7324, 115.6749, 135.6037, 271.5265, 157.7349, 284.776, 370.9437, 216.5126, 147.365,
   88.03145, 131.8063, 201.3382, 92.51708, 157.7895, 249.3754, 143.3967, 139.4203, 166.7797, 219.6564, 176.0669 };
   Double_t Graph_fy10[28] = { 233.2085, 157.9795, 224.0422, 906.8841, 138.751, 356.7756, 821.1541, 296.8181, 406.9968, 196.5328, 172.3978, 481.523, 276.5338, 391.124, 388.8084, 271.2009, 319.2422,
   378.0294, 419.824, 242.353, 178.0424, 220.707, 381.5013, 264.1662, 156.3705, 290.3495, 319.5273, 344.5213 };
   graph = new TGraph(28,Graph_fx10,Graph_fy10);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(8);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph10 = new TH1F("Graph_Graph10","",100,0,696.1417);
   Graph_Graph10->SetMinimum(61.9377);
   Graph_Graph10->SetMaximum(983.6974);
   Graph_Graph10->SetDirectory(nullptr);
   Graph_Graph10->SetStats(0);
   Graph_Graph10->SetLineStyle(0);
   Graph_Graph10->SetMarkerStyle(20);
   Graph_Graph10->GetXaxis()->SetLabelFont(42);
   Graph_Graph10->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph10->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph10->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph10->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph10->GetXaxis()->SetTitleFont(42);
   Graph_Graph10->GetYaxis()->SetLabelFont(42);
   Graph_Graph10->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph10->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph10->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph10->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph10->GetYaxis()->SetTitleFont(42);
   Graph_Graph10->GetZaxis()->SetLabelFont(42);
   Graph_Graph10->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph10->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph10->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph10->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph10->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph10);
   
   graph->Draw("p, ");
   
   Double_t Graph_fx11[41] = { 129.0576, 189.9817, 373.4706, 155.5825, 263.0032, 296.9265, 251.7598, 183.7128, 169.6233, 177.0053, 226.6913, 121.5156, 257.1689, 419.9987, 101.8109, 728.4952, 60.17837,
   817.201, 370.5422, 144.5045, 69.13374, 134.9233, 166.9688, 104.9206, 218.3362, 133.5971, 532.2877, 182.3528, 86.36743, 122.3882, 718.7362, 1761.813, 52.47724,
   280.1347, 408.4519, 54.74392, 235.4891, 111.0667, 495.6254, 206.7441, 90.16321 };
   Double_t Graph_fy11[41] = { 286.6593, 491.2535, 483.7285, 432.763, 387.1464, 307.2563, 416.8382, 686.5387, 518.0114, 389.7571, 269.7402, 235.8688, 438.1288, 876.5725, 142.5102, 1014.82, 355.0847,
   871.4875, 452.6487, 415.9586, 411.8144, 223.5249, 197.9058, 238.3413, 528.7435, 232.7145, 678.4143, 462.2296, 353.8559, 163.9141, 949.9609, 5181.479, 294.0331,
   332.893, 516.9855, 295.4889, 290.1168, 208.8233, 756.6091, 292.7796, 99.3961 };
   graph = new TGraph(41,Graph_fx11,Graph_fy11);
   graph->SetName("");
   graph->SetTitle("e#tau_{h}#gamma");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(6);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph11 = new TH1F("Graph_Graph11","e#tau_{h}#gamma",100,0,6000);
   Graph_Graph11->SetMinimum(0);
   Graph_Graph11->SetMaximum(6000);
   Graph_Graph11->SetDirectory(nullptr);
   Graph_Graph11->SetStats(0);
   Graph_Graph11->SetLineStyle(0);
   Graph_Graph11->SetMarkerStyle(20);
   Graph_Graph11->GetXaxis()->SetTitle("min collinear mass [GeV]");
   Graph_Graph11->GetXaxis()->SetLabelFont(42);
   Graph_Graph11->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph11->GetXaxis()->SetLabelSize(0.04);
   Graph_Graph11->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph11->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph11->GetXaxis()->SetTitleFont(42);
   Graph_Graph11->GetYaxis()->SetTitle("max collinear mass [GeV]");
   Graph_Graph11->GetYaxis()->SetLabelFont(42);
   Graph_Graph11->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph11->GetYaxis()->SetLabelSize(0.04);
   Graph_Graph11->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph11->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph11->GetYaxis()->SetTitleFont(42);
   Graph_Graph11->GetZaxis()->SetLabelFont(42);
   Graph_Graph11->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph11->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph11->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph11->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph11);
   
   graph->Draw("p, ");
   
   Double_t Graph_fx12[22] = { 145.41, 72.99173, 70.92158, 204.1326, 340.5949, 123.9075, 400.8178, 111.05, 63.98508, 213.2921, 446.543, 226.8407, 117.2659, 136.6524, 96.85616, 532.5793, 126.432,
   214.3904, 319.9348, 487.524, 179.112, 184.8359 };
   Double_t Graph_fy12[22] = { 236.3533, 241.617, 285.261, 340.7227, 357.9142, 226.6367, 421.8664, 373.7509, 412.2383, 271.8565, 530.1425, 305.2176, 456.3667, 394.8323, 270.9519, 1080.658, 147.9153,
   544.3028, 352.7005, 869.0994, 347.6511, 248.7342 };
   graph = new TGraph(22,Graph_fx12,Graph_fy12);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetMarkerColor(6);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","",100,17.12566,579.4387);
   Graph_Graph12->SetMinimum(54.64096);
   Graph_Graph12->SetMaximum(1173.932);
   Graph_Graph12->SetDirectory(nullptr);
   Graph_Graph12->SetStats(0);
   Graph_Graph12->SetLineStyle(0);
   Graph_Graph12->SetMarkerStyle(20);
   Graph_Graph12->GetXaxis()->SetLabelFont(42);
   Graph_Graph12->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph12->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph12->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph12->GetXaxis()->SetTitleFont(42);
   Graph_Graph12->GetYaxis()->SetLabelFont(42);
   Graph_Graph12->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph12->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph12->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph12->GetYaxis()->SetTitleFont(42);
   Graph_Graph12->GetZaxis()->SetLabelFont(42);
   Graph_Graph12->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph12->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph12->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetZaxis()->SetTitleOffset(1);
   Graph_Graph12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw("p, ");
   
   TLegend *leg = new TLegend(0.55,0.2,0.87,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","e#tau_{h}#gamma: 63 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(6);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","#mu#tau_{h}#gamma: 84 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(7);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","#tau_{h}#tau_{h}#gamma: 88 events","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(8);
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
   c->Modified();
   c->SetSelected(c);
}
