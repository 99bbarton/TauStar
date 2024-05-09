//A macro to reproduce all plots from the paper 
//Instructions to run:
//In root: .L plotReproducer.C
//         plotReproducer()

//The 2D signal collinear mass plot (figure 2), as a scatter plot of ~100k points is incredibly unwieldy to reproduce so is omitted.
//A separate file, sigCollinMass2D.C is the auto-generated macro to reproduce it but running it will take a long time... 



//Figure 4. Limit "Brazil" plot
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

//Figure 5. Limit plot by channel
void limits3()
{
    //=========Macro generated from canvas: c/c
    //=========  (Wed May  8 09:58:13 2024) by ROOT version 6.14/09
    TCanvas *c2 = new TCanvas("c2", "c2",815,241,600,400);
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    c2->SetHighLightColor(2);
    c2->Range(-714.2857,-2.6,5238.095,2.4);
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
    c2->SetLogy();
    c2->SetTickx(1);
    c2->SetTicky(1);
    c2->SetLeftMargin(0.12);
    c2->SetRightMargin(0.04);
    c2->SetTopMargin(0.08);
    c2->SetBottomMargin(0.12);
    c2->SetFrameFillStyle(0);
    c2->SetFrameBorderMode(0);
    c2->SetFrameFillStyle(0);
    c2->SetFrameBorderMode(0);
    
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
    c2->Modified();
    c2->cd();
    c2->SetSelected(c2);
}

//Figure 3. 2D event yields - ETau channel
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

//Figure 3. 2D event yields - MuTau channel
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

//Figure 3. 2D event yields - TauTau channel
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

//Make all plots in paper
void plotReproducer()
{
    UpperLimitAsymptoticLimitsnominaly0();
    limits3();
    SignalRegion_ETau();
    SignalRegion_MuTau();
    SignalRegion_TauTau();
    //sigCollinMass2D();
}
