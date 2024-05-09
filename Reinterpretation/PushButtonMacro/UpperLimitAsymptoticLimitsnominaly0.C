void UpperLimitAsymptoticLimitsnominaly0()
{
//=========Macro generated from canvas: c/c
//=========  (Wed May  8 09:39:16 2024) by ROOT version 6.14/09
   TCanvas *c = new TCanvas("c", "c",1247,106,600,400);
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
   
   Double_t Graph0_fx1[34] = {
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
   5000,
   5000,
   4500,
   4000,
   3500,
   3000,
   2500,
   2000,
   1750,
   1500,
   1250,
   1000,
   750,
   625,
   500,
   375,
   250,
   175};
   Double_t Graph0_fy1[34] = {
   9.378473,
   7.075887,
   3.562774,
   2.035054,
   1.338339,
   0.9799724,
   0.6492714,
   0.4456897,
   0.3546123,
   0.3135067,
   0.2917049,
   0.2080609,
   0.153349,
   0.167895,
   0.1236101,
   0.1376682,
   0.1030628,
   0.01115051,
   0.01507214,
   0.01273671,
   0.01946628,
   0.01639622,
   0.02573938,
   0.04511043,
   0.0506132,
   0.06391684,
   0.08769493,
   0.1421762,
   0.2348248,
   0.3335175,
   0.5297952,
   0.9733626,
   2.079099,
   2.735981};
   TGraph *graph = new TGraph(34,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f5bb54");
   graph->SetFillColor(ci);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","Graph",100,0,5482.5);
   Graph_Graph01->SetMinimum(0.01003546);
   Graph_Graph01->SetMaximum(10.3152);
   Graph_Graph01->SetDirectory(0);
   Graph_Graph01->SetStats(0);
   Graph_Graph01->SetLineStyle(0);
   Graph_Graph01->SetMarkerStyle(20);
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph01->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph01->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph01->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph01->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("f");
   
   Double_t Graph1_fx2[34] = {
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
   5000,
   5000,
   4500,
   4000,
   3500,
   3000,
   2500,
   2000,
   1750,
   1500,
   1250,
   1000,
   750,
   625,
   500,
   375,
   250,
   175};
   Double_t Graph1_fy2[34] = {
   7.007298,
   5.286879,
   2.599056,
   1.459971,
   0.9484781,
   0.6836135,
   0.4408997,
   0.2922289,
   0.2265218,
   0.1947918,
   0.1777403,
   0.1244518,
   0.09854753,
   0.1070169,
   0.08202258,
   0.09099099,
   0.06838825,
   0.01828551,
   0.02454765,
   0.0214932,
   0.03096693,
   0.02734298,
   0.03981561,
   0.06626079,
   0.0742303,
   0.0916394,
   0.1234123,
   0.1968873,
   0.3201746,
   0.4534543,
   0.7144451,
   1.308851,
   2.752022,
   3.635571};
   graph = new TGraph(34,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#607641");
   graph->SetFillColor(ci);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","Graph",100,0,5482.5);
   Graph_Graph12->SetMinimum(0.01645695);
   Graph_Graph12->SetMaximum(7.706199);
   Graph_Graph12->SetDirectory(0);
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
   Graph_Graph12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw("f");
   
   Double_t Graph2_fx3[17] = {
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
   Double_t Graph2_fy3[17] = {
   5.03893,
   3.801781,
   1.832212,
   1.012146,
   0.6468218,
   0.4624243,
   0.2911768,
   0.1870825,
   0.1410579,
   0.1177907,
   0.1059474,
   0.06863836,
   0.05057147,
   0.05537074,
   0.04075748,
   0.04539375,
   0.0339825};
   graph = new TGraph(17,Graph2_fx3,Graph2_fy3);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph23 = new TH1F("Graph_Graph23","Graph",100,0,5482.5);
   Graph_Graph23->SetMinimum(0.03058425);
   Graph_Graph23->SetMaximum(5.539424);
   Graph_Graph23->SetDirectory(0);
   Graph_Graph23->SetStats(0);
   Graph_Graph23->SetLineStyle(0);
   Graph_Graph23->SetMarkerStyle(20);
   Graph_Graph23->GetXaxis()->SetLabelFont(42);
   Graph_Graph23->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph23->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph23->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph23->GetXaxis()->SetTitleFont(42);
   Graph_Graph23->GetYaxis()->SetLabelFont(42);
   Graph_Graph23->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph23->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph23->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph23->GetYaxis()->SetTitleFont(42);
   Graph_Graph23->GetZaxis()->SetLabelFont(42);
   Graph_Graph23->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph23->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph23->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph23);
   
   graph->Draw("lp");
   
   Double_t Graph3_fx4[17] = {
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
   Double_t Graph3_fy4[17] = {
   4.364018,
   3.115016,
   1.734783,
   0.9596739,
   0.5432089,
   0.6204358,
   0.2859085,
   0.2151787,
   0.1795436,
   0.137297,
   0.06857254,
   0.0844547,
   0.1136599,
   0.04510781,
   0.03396277,
   0.03392053,
   0.05292512};
   graph = new TGraph(17,Graph3_fx4,Graph3_fy4);
   graph->SetName("Graph3");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph34 = new TH1F("Graph_Graph34","Graph",100,0,5482.5);
   Graph_Graph34->SetMinimum(0.03052848);
   Graph_Graph34->SetMaximum(4.797027);
   Graph_Graph34->SetDirectory(0);
   Graph_Graph34->SetStats(0);
   Graph_Graph34->SetLineStyle(0);
   Graph_Graph34->SetMarkerStyle(20);
   Graph_Graph34->GetXaxis()->SetLabelFont(42);
   Graph_Graph34->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph34->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph34->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph34->GetXaxis()->SetTitleFont(42);
   Graph_Graph34->GetYaxis()->SetLabelFont(42);
   Graph_Graph34->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph34->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph34->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph34->GetYaxis()->SetTitleFont(42);
   Graph_Graph34->GetZaxis()->SetLabelFont(42);
   Graph_Graph34->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph34->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph34->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph34);
   
   graph->Draw("lp");
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
   
   Double_t Graph4_fx5[17] = {
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
   Double_t Graph4_fy5[17] = {
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
   graph = new TGraph(17,Graph4_fx5,Graph4_fy5);
   graph->SetName("Graph4");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(6);
   graph->SetLineStyle(5);
   graph->SetMarkerColor(6);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph45 = new TH1F("Graph_Graph45","Graph",100,0,5482.5);
   Graph_Graph45->SetMinimum(0.00122337);
   Graph_Graph45->SetMaximum(31.88666);
   Graph_Graph45->SetDirectory(0);
   Graph_Graph45->SetStats(0);
   Graph_Graph45->SetLineStyle(0);
   Graph_Graph45->SetMarkerStyle(20);
   Graph_Graph45->GetXaxis()->SetLabelFont(42);
   Graph_Graph45->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph45->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph45->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph45->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph45->GetXaxis()->SetTitleFont(42);
   Graph_Graph45->GetYaxis()->SetLabelFont(42);
   Graph_Graph45->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph45->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph45->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph45->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph45->GetYaxis()->SetTitleFont(42);
   Graph_Graph45->GetZaxis()->SetLabelFont(42);
   Graph_Graph45->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph45->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph45->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph45->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph45);
   
   graph->Draw("l,p ");
   
   Double_t Graph5_fx6[9] = {
   1000,
   1500,
   2000,
   2500,
   3000,
   3500,
   4000,
   4500,
   5000};
   Double_t Graph5_fy6[9] = {
   4330,
   394.5,
   59.21,
   11.55,
   2.692,
   0.703,
   0.2003,
   0.06219,
   0.02036};
   graph = new TGraph(9,Graph5_fx6,Graph5_fy6);
   graph->SetName("Graph5");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(7);
   graph->SetLineStyle(8);
   graph->SetMarkerColor(7);
   graph->SetMarkerStyle(7);
   
   TH1F *Graph_Graph56 = new TH1F("Graph_Graph56","Graph",100,600,5400);
   Graph_Graph56->SetMinimum(0.018324);
   Graph_Graph56->SetMaximum(4762.998);
   Graph_Graph56->SetDirectory(0);
   Graph_Graph56->SetStats(0);
   Graph_Graph56->SetLineStyle(0);
   Graph_Graph56->SetMarkerStyle(20);
   Graph_Graph56->GetXaxis()->SetLabelFont(42);
   Graph_Graph56->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph56->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph56->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph56->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph56->GetXaxis()->SetTitleFont(42);
   Graph_Graph56->GetYaxis()->SetLabelFont(42);
   Graph_Graph56->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph56->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph56->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph56->GetYaxis()->SetTitleOffset(1.25);
   Graph_Graph56->GetYaxis()->SetTitleFont(42);
   Graph_Graph56->GetZaxis()->SetLabelFont(42);
   Graph_Graph56->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph56->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph56->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph56->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph56);
   
   graph->Draw("l,p ");
   
   TLegend *leg = new TLegend(0.7,0.6,0.95,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.041);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Graph2","Expected","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","68% expected","F");

   ci = TColor::GetColor("#607641");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0","95% expected","F");

   ci = TColor::GetColor("#f5bb54");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph3","observed","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph4","#Lambda = 10 TeV","L");
   entry->SetLineColor(6);
   entry->SetLineStyle(5);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","#Lambda = m_{#tau*}","L");
   entry->SetLineColor(7);
   entry->SetLineStyle(8);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
