void limits3()
{
//=========Macro generated from canvas: c/c
//=========  (Wed May  8 09:58:13 2024) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",815,241,600,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(-714.2857,-2.6,5238.095,2.4);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.04);
   c->SetTopMargin(0.08);
   c->SetBottomMargin(0.12);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   
   TH1F *hframe__1 = new TH1F("hframe__1","",1000,0,5000);
   hframe__1->SetMinimum(0.01);
   hframe__1->SetMaximum(100);
   hframe__1->SetDirectory(0);
   hframe__1->SetStats(0);
   hframe__1->SetLineStyle(0);
   hframe__1->SetMarkerStyle(20);
   hframe__1->GetXaxis()->SetTitle("#tau* mass [GeV]");
   hframe__1->GetXaxis()->SetNdivisions(508);
   hframe__1->GetXaxis()->SetLabelFont(42);
   hframe__1->GetXaxis()->SetLabelOffset(0.007);
   hframe__1->GetXaxis()->SetTitleSize(0.05);
   hframe__1->GetXaxis()->SetTitleOffset(0.9);
   hframe__1->GetXaxis()->SetTitleFont(42);
   hframe__1->GetYaxis()->SetTitle("#sigma #times B(#tau*#rightarrow#tau#gamma) (fb)");
   hframe__1->GetYaxis()->CenterTitle(true);
   hframe__1->GetYaxis()->SetLabelFont(42);
   hframe__1->GetYaxis()->SetLabelOffset(0.007);
   hframe__1->GetYaxis()->SetTitleSize(0.05);
   hframe__1->GetYaxis()->SetTitleOffset(0.9);
   hframe__1->GetYaxis()->SetTitleFont(42);
   hframe__1->GetZaxis()->SetLabelFont(42);
   hframe__1->GetZaxis()->SetLabelOffset(0.007);
   hframe__1->GetZaxis()->SetLabelSize(0.05);
   hframe__1->GetZaxis()->SetTitleSize(0.06);
   hframe__1->GetZaxis()->SetTitleFont(42);
   hframe__1->Draw(" ");
   
   TPaveText *pt = new TPaveText(0.2,0.675,0.3,0.775,"NDC, NB");
   pt->SetFillColor(0);
   TText *pt_LaTex = pt->AddText("#Lambda = 10 TeV");
   pt_LaTex->SetTextAngle(-40);
   pt_LaTex->SetTextAlign(22);
   pt->Draw();
   
   pt = new TPaveText(0.5,0.7,0.6,0.8,"NDC, NB");
   pt->SetFillColor(0);
   pt_LaTex = pt->AddText("#Lambda = #tau* mass");
   pt_LaTex->SetTextAngle(-45);
   pt_LaTex->SetTextAlign(22);
   pt->Draw();
   
   Double_t expected_fx1[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t expected_fy1[17] = {
   12.5124,
   8.762,
   5.473828,
   3.030654,
   2.078751,
   1.463193,
   1.073194,
   0.7183969,
   0.5209438,
   0.4817906,
   0.401761,
   0.2906177,
   0.2157716,
   0.194328,
   0.2037874,
   0.1824829,
   0.1179193};
   TGraph *graph = new TGraph(17,expected_fx1,expected_fy1);
   graph->SetName("expected");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(97);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(97);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_expected1 = new TH1F("Graph_expected1","Graph",100,0,5482.5);
   Graph_expected1->SetMinimum(0.1061273);
   Graph_expected1->SetMaximum(13.75185);
   Graph_expected1->SetDirectory(0);
   Graph_expected1->SetStats(0);
   Graph_expected1->SetLineStyle(0);
   Graph_expected1->SetMarkerStyle(20);
   Graph_expected1->GetXaxis()->SetLabelFont(42);
   Graph_expected1->GetXaxis()->SetLabelOffset(0.007);
   Graph_expected1->GetXaxis()->SetLabelSize(0.05);
   Graph_expected1->GetXaxis()->SetTitleSize(0.06);
   Graph_expected1->GetXaxis()->SetTitleOffset(0.9);
   Graph_expected1->GetXaxis()->SetTitleFont(42);
   Graph_expected1->GetYaxis()->SetLabelFont(42);
   Graph_expected1->GetYaxis()->SetLabelOffset(0.007);
   Graph_expected1->GetYaxis()->SetLabelSize(0.05);
   Graph_expected1->GetYaxis()->SetTitleSize(0.06);
   Graph_expected1->GetYaxis()->SetTitleOffset(1.25);
   Graph_expected1->GetYaxis()->SetTitleFont(42);
   Graph_expected1->GetZaxis()->SetLabelFont(42);
   Graph_expected1->GetZaxis()->SetLabelOffset(0.007);
   Graph_expected1->GetZaxis()->SetLabelSize(0.05);
   Graph_expected1->GetZaxis()->SetTitleSize(0.06);
   Graph_expected1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_expected1);
   
   graph->Draw("pl");
   
   Double_t observed_fx2[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t observed_fy2[17] = {
   13.28937,
   7.035374,
   5.125497,
   4.009924,
   1.674743,
   1.791251,
   1.400888,
   0.4315101,
   0.3755992,
   0.5438737,
   0.3216817,
   0.2653404,
   0.2044924,
   0.1826938,
   0.1620316,
   0.1447339,
   0.2288868};
   graph = new TGraph(17,observed_fx2,observed_fy2);
   graph->SetName("observed");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(97);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(97);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_observed2 = new TH1F("Graph_observed2","Graph",100,0,5482.5);
   Graph_observed2->SetMinimum(0.1302605);
   Graph_observed2->SetMaximum(14.60383);
   Graph_observed2->SetDirectory(0);
   Graph_observed2->SetStats(0);
   Graph_observed2->SetLineStyle(0);
   Graph_observed2->SetMarkerStyle(20);
   Graph_observed2->GetXaxis()->SetLabelFont(42);
   Graph_observed2->GetXaxis()->SetLabelOffset(0.007);
   Graph_observed2->GetXaxis()->SetLabelSize(0.05);
   Graph_observed2->GetXaxis()->SetTitleSize(0.06);
   Graph_observed2->GetXaxis()->SetTitleOffset(0.9);
   Graph_observed2->GetXaxis()->SetTitleFont(42);
   Graph_observed2->GetYaxis()->SetLabelFont(42);
   Graph_observed2->GetYaxis()->SetLabelOffset(0.007);
   Graph_observed2->GetYaxis()->SetLabelSize(0.05);
   Graph_observed2->GetYaxis()->SetTitleSize(0.06);
   Graph_observed2->GetYaxis()->SetTitleOffset(1.25);
   Graph_observed2->GetYaxis()->SetTitleFont(42);
   Graph_observed2->GetZaxis()->SetLabelFont(42);
   Graph_observed2->GetZaxis()->SetLabelOffset(0.007);
   Graph_observed2->GetZaxis()->SetLabelSize(0.05);
   Graph_observed2->GetZaxis()->SetTitleSize(0.06);
   Graph_observed2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_observed2);
   
   graph->Draw("pl, ");
   
   Double_t expected_fx3[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t expected_fy3[17] = {
   6.737445,
   5.623687,
   3.755654,
   2.215154,
   1.409625,
   1.052533,
   0.6821855,
   0.4103343,
   0.3209253,
   0.3082043,
   0.2559522,
   0.2037245,
   0.1712101,
   0.1408666,
   0.1074515,
   0.2210676,
   0.1067051};
   graph = new TGraph(17,expected_fx3,expected_fy3);
   graph->SetName("expected");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(214);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(214);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_expected3 = new TH1F("Graph_expected3","Graph",100,0,5482.5);
   Graph_expected3->SetMinimum(0.09603455);
   Graph_expected3->SetMaximum(7.400519);
   Graph_expected3->SetDirectory(0);
   Graph_expected3->SetStats(0);
   Graph_expected3->SetLineStyle(0);
   Graph_expected3->SetMarkerStyle(20);
   Graph_expected3->GetXaxis()->SetLabelFont(42);
   Graph_expected3->GetXaxis()->SetLabelOffset(0.007);
   Graph_expected3->GetXaxis()->SetLabelSize(0.05);
   Graph_expected3->GetXaxis()->SetTitleSize(0.06);
   Graph_expected3->GetXaxis()->SetTitleOffset(0.9);
   Graph_expected3->GetXaxis()->SetTitleFont(42);
   Graph_expected3->GetYaxis()->SetLabelFont(42);
   Graph_expected3->GetYaxis()->SetLabelOffset(0.007);
   Graph_expected3->GetYaxis()->SetLabelSize(0.05);
   Graph_expected3->GetYaxis()->SetTitleSize(0.06);
   Graph_expected3->GetYaxis()->SetTitleOffset(1.25);
   Graph_expected3->GetYaxis()->SetTitleFont(42);
   Graph_expected3->GetZaxis()->SetLabelFont(42);
   Graph_expected3->GetZaxis()->SetLabelOffset(0.007);
   Graph_expected3->GetZaxis()->SetLabelSize(0.05);
   Graph_expected3->GetZaxis()->SetTitleSize(0.06);
   Graph_expected3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_expected3);
   
   graph->Draw("pl, ");
   
   Double_t observed_fx4[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t observed_fy4[17] = {
   5.63679,
   5.388008,
   3.301532,
   1.170831,
   0.8121038,
   1.304465,
   0.7194269,
   0.7167087,
   0.3342487,
   0.2070959,
   0.1904485,
   0.3000737,
   0.4031449,
   0.133707,
   0.1021586,
   0.1152626,
   0.08331892};
   graph = new TGraph(17,observed_fx4,observed_fy4);
   graph->SetName("observed");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(214);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(214);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_observed4 = new TH1F("Graph_observed4","Graph",100,0,5482.5);
   Graph_observed4->SetMinimum(0.07498703);
   Graph_observed4->SetMaximum(6.192138);
   Graph_observed4->SetDirectory(0);
   Graph_observed4->SetStats(0);
   Graph_observed4->SetLineStyle(0);
   Graph_observed4->SetMarkerStyle(20);
   Graph_observed4->GetXaxis()->SetLabelFont(42);
   Graph_observed4->GetXaxis()->SetLabelOffset(0.007);
   Graph_observed4->GetXaxis()->SetLabelSize(0.05);
   Graph_observed4->GetXaxis()->SetTitleSize(0.06);
   Graph_observed4->GetXaxis()->SetTitleOffset(0.9);
   Graph_observed4->GetXaxis()->SetTitleFont(42);
   Graph_observed4->GetYaxis()->SetLabelFont(42);
   Graph_observed4->GetYaxis()->SetLabelOffset(0.007);
   Graph_observed4->GetYaxis()->SetLabelSize(0.05);
   Graph_observed4->GetYaxis()->SetTitleSize(0.06);
   Graph_observed4->GetYaxis()->SetTitleOffset(1.25);
   Graph_observed4->GetYaxis()->SetTitleFont(42);
   Graph_observed4->GetZaxis()->SetLabelFont(42);
   Graph_observed4->GetZaxis()->SetLabelOffset(0.007);
   Graph_observed4->GetZaxis()->SetLabelSize(0.05);
   Graph_observed4->GetZaxis()->SetTitleSize(0.06);
   Graph_observed4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_observed4);
   
   graph->Draw("pl, ");
   
   Double_t expected_fx5[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t expected_fy5[17] = {
   9.398453,
   6.297688,
   2.303569,
   1.272412,
   0.8297162,
   0.6039124,
   0.3722903,
   0.2631627,
   0.2156917,
   0.1691581,
   0.1678375,
   0.1091642,
   0.08355287,
   0.1120144,
   0.07132558,
   0.07353788,
   0.06150833};
   graph = new TGraph(17,expected_fx5,expected_fy5);
   graph->SetName("expected");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(210);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(210);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_expected5 = new TH1F("Graph_expected5","Graph",100,0,5482.5);
   Graph_expected5->SetMinimum(0.05535749);
   Graph_expected5->SetMaximum(10.33215);
   Graph_expected5->SetDirectory(0);
   Graph_expected5->SetStats(0);
   Graph_expected5->SetLineStyle(0);
   Graph_expected5->SetMarkerStyle(20);
   Graph_expected5->GetXaxis()->SetLabelFont(42);
   Graph_expected5->GetXaxis()->SetLabelOffset(0.007);
   Graph_expected5->GetXaxis()->SetLabelSize(0.05);
   Graph_expected5->GetXaxis()->SetTitleSize(0.06);
   Graph_expected5->GetXaxis()->SetTitleOffset(0.9);
   Graph_expected5->GetXaxis()->SetTitleFont(42);
   Graph_expected5->GetYaxis()->SetLabelFont(42);
   Graph_expected5->GetYaxis()->SetLabelOffset(0.007);
   Graph_expected5->GetYaxis()->SetLabelSize(0.05);
   Graph_expected5->GetYaxis()->SetTitleSize(0.06);
   Graph_expected5->GetYaxis()->SetTitleOffset(1.25);
   Graph_expected5->GetYaxis()->SetTitleFont(42);
   Graph_expected5->GetZaxis()->SetLabelFont(42);
   Graph_expected5->GetZaxis()->SetLabelOffset(0.007);
   Graph_expected5->GetZaxis()->SetLabelSize(0.05);
   Graph_expected5->GetZaxis()->SetTitleSize(0.06);
   Graph_expected5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_expected5);
   
   graph->Draw("pl, ");
   
   Double_t observed_fx6[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t observed_fy6[17] = {
   7.937112,
   5.062185,
   2.341253,
   1.552649,
   0.9994834,
   0.6719634,
   0.3002771,
   0.2376094,
   0.3313557,
   0.2309509,
   0.1319832,
   0.09844388,
   0.08209129,
   0.09477852,
   0.06718383,
   0.06874504,
   0.0565896};
   graph = new TGraph(17,observed_fx6,observed_fy6);
   graph->SetName("observed");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(210);
   graph->SetLineWidth(2);
   graph->SetMarkerColor(210);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_observed6 = new TH1F("Graph_observed6","Graph",100,0,5482.5);
   Graph_observed6->SetMinimum(0.05093064);
   Graph_observed6->SetMaximum(8.725164);
   Graph_observed6->SetDirectory(0);
   Graph_observed6->SetStats(0);
   Graph_observed6->SetLineStyle(0);
   Graph_observed6->SetMarkerStyle(20);
   Graph_observed6->GetXaxis()->SetLabelFont(42);
   Graph_observed6->GetXaxis()->SetLabelOffset(0.007);
   Graph_observed6->GetXaxis()->SetLabelSize(0.05);
   Graph_observed6->GetXaxis()->SetTitleSize(0.06);
   Graph_observed6->GetXaxis()->SetTitleOffset(0.9);
   Graph_observed6->GetXaxis()->SetTitleFont(42);
   Graph_observed6->GetYaxis()->SetLabelFont(42);
   Graph_observed6->GetYaxis()->SetLabelOffset(0.007);
   Graph_observed6->GetYaxis()->SetLabelSize(0.05);
   Graph_observed6->GetYaxis()->SetTitleSize(0.06);
   Graph_observed6->GetYaxis()->SetTitleOffset(1.25);
   Graph_observed6->GetYaxis()->SetTitleFont(42);
   Graph_observed6->GetZaxis()->SetLabelFont(42);
   Graph_observed6->GetZaxis()->SetLabelOffset(0.007);
   Graph_observed6->GetZaxis()->SetLabelSize(0.05);
   Graph_observed6->GetZaxis()->SetTitleSize(0.06);
   Graph_observed6->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_observed6);
   
   graph->Draw("pl, ");
   TLatex *   tex = new TLatex(0.96,0.936,"138 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.048);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.12,0.936,"CMS");
tex->SetNDC();
   tex->SetTextFont(61);
   tex->SetTextSize(0.052);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1578,0.892,"");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.03952);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH1F *hframe__2 = new TH1F("hframe__2","",1000,0,5000);
   hframe__2->SetMinimum(0.01);
   hframe__2->SetMaximum(100);
   hframe__2->SetDirectory(0);
   hframe__2->SetStats(0);
   hframe__2->SetLineStyle(0);
   hframe__2->SetMarkerStyle(20);
   hframe__2->GetXaxis()->SetTitle("#tau* mass [GeV]");
   hframe__2->GetXaxis()->SetNdivisions(508);
   hframe__2->GetXaxis()->SetLabelFont(42);
   hframe__2->GetXaxis()->SetLabelOffset(0.007);
   hframe__2->GetXaxis()->SetTitleSize(0.05);
   hframe__2->GetXaxis()->SetTitleOffset(0.9);
   hframe__2->GetXaxis()->SetTitleFont(42);
   hframe__2->GetYaxis()->SetTitle("#sigma #times B(#tau*#rightarrow#tau#gamma) (fb)");
   hframe__2->GetYaxis()->CenterTitle(true);
   hframe__2->GetYaxis()->SetLabelFont(42);
   hframe__2->GetYaxis()->SetLabelOffset(0.007);
   hframe__2->GetYaxis()->SetTitleSize(0.05);
   hframe__2->GetYaxis()->SetTitleOffset(0.9);
   hframe__2->GetYaxis()->SetTitleFont(42);
   hframe__2->GetZaxis()->SetLabelFont(42);
   hframe__2->GetZaxis()->SetLabelOffset(0.007);
   hframe__2->GetZaxis()->SetLabelSize(0.05);
   hframe__2->GetZaxis()->SetTitleSize(0.06);
   hframe__2->GetZaxis()->SetTitleFont(42);
   hframe__2->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.7,0.6,0.95,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.041);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("expected","e+#tau_{h} expected","L");
   entry->SetLineColor(97);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("observed","e+#tau_{h} observed","L");
   entry->SetLineColor(97);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("expected","#mu+#tau_{h} expected","L");
   entry->SetLineColor(214);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("observed","#mu+#tau_{h} observed","L");
   entry->SetLineColor(214);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("expected","#tau_{h}+#tau_{h} expected","L");
   entry->SetLineColor(210);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("observed","#tau_{h}+#tau_{h} observed","L");
   entry->SetLineColor(210);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph0_fx7[17] = {
   175,
   250,
   375,
   500,
   625,
   750,
   1000,
   1250,
   1500,
   1750,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t Graph0_fy7[17] = {
   28.988,
   21.568,
   15.57,
   11.845,
   9.1358,
   7.0675,
   4.2595,
   2.5543,
   1.5285,
   0.9069,
   0.53708,
   0.18693,
   0.075051,
   0.027155,
   0.0098806,
   0.0036315,
   0.0013593};
   graph = new TGraph(17,Graph0_fx7,Graph0_fy7);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph07 = new TH1F("Graph_Graph07","Graph",100,0,5482.5);
   Graph_Graph07->SetMinimum(0.00122337);
   Graph_Graph07->SetMaximum(31.88666);
   Graph_Graph07->SetDirectory(0);
   Graph_Graph07->SetStats(0);
   Graph_Graph07->SetLineStyle(0);
   Graph_Graph07->SetMarkerStyle(20);
   Graph_Graph07->GetXaxis()->SetLabelFont(42);
   Graph_Graph07->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph07->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph07->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph07->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph07->GetXaxis()->SetTitleFont(42);
   Graph_Graph07->GetYaxis()->SetLabelFont(42);
   Graph_Graph07->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph07->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph07->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph07->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph07->GetYaxis()->SetTitleFont(42);
   Graph_Graph07->GetZaxis()->SetLabelFont(42);
   Graph_Graph07->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph07->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph07->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph07->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph07);
   
   graph->Draw("l, p, ");
   
   Double_t Graph1_fx8[9] = {
   1000,
   1500,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t Graph1_fy8[9] = {
   4330,
   394.5,
   59.21,
   11.55,
   2.692,
   0.703,
   0.2003,
   0.06219,
   0.02036};
   graph = new TGraph(9,Graph1_fx8,Graph1_fy8);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph18 = new TH1F("Graph_Graph18","Graph",100,600,5400);
   Graph_Graph18->SetMinimum(0.018324);
   Graph_Graph18->SetMaximum(4762.998);
   Graph_Graph18->SetDirectory(0);
   Graph_Graph18->SetStats(0);
   Graph_Graph18->SetLineStyle(0);
   Graph_Graph18->SetMarkerStyle(20);
   Graph_Graph18->GetXaxis()->SetLabelFont(42);
   Graph_Graph18->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph18->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph18->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph18->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph18->GetXaxis()->SetTitleFont(42);
   Graph_Graph18->GetYaxis()->SetLabelFont(42);
   Graph_Graph18->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph18->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph18->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph18->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph18->GetYaxis()->SetTitleFont(42);
   Graph_Graph18->GetZaxis()->SetLabelFont(42);
   Graph_Graph18->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph18->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph18->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph18->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph18);
   
   graph->Draw("l, p, ");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
