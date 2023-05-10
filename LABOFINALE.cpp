#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH3F.h"
#include <cmath>

// Utilizzare al CANALE 1 il GENERATORE, al CANALE 2 il TWEETER e al CANALE 3 il WOOFER
// QUELLE COMMENTATE SONO LE FORMULE E I DATI NOSTRI, CONTROLLARE LA RESISTENZA DI L
// Inserire come V sempre quello immesso

void voltTime()                                              
{                                                            // Amplitude (v) - Time (s)
    TGraph *freqGen1 = new TGraph("freqGen.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo generata
    TGraph *freqTwi1 = new TGraph("freqTwi.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo twiter
    TGraph *freqSub1 = new TGraph("freqSub.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo woofer

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "n1 Heartz Behavior"); // sovrapponi 3 grafici
    freqGen1->SetTitle("n1 Heartz Behavior; Time(s); Amplitude(V)");
    freqGen1->SetLineColor(40);
    freqGen1->SetLineWidth(3);
    freqGen1->Draw();

    freqTwi1->SetLineColor(46);
    freqTwi1->SetLineWidth(3);
    freqTwi1->Draw("CP");
    freqSub1->SetLineColor(38);
    freqSub1->SetLineWidth(3);
    freqSub1->Draw("CP");
}

void freqVolt()
{
    TCanvas *myCanvas2 = new TCanvas();

    TGraph *freqvolt = new TGraph("freqvolt.txt", "%lg %lg");
    TGraph *freqvoltTwi = new TGraph("freqvoltTwi.txt", "%lg %lg");
    TGraph *freqvoltSub = new TGraph("freqvoltSub.txt", "%lg %lg");

    TF1 *f1 = new TF1("f1", "[0]", 1000, 9000);
    TF1 *f2 = new TF1("f2", "2.19*0.8799/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);
    TF1 *f3 = new TF1("f3", "2.19*0.874/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);

    TF1 *fatt1 = new TF1("fatt1", "2.19", 1000, 9000);
    TF1 *fatt2 = new TF1("fatt2", "2.19*0.8799/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*0.00002601),2))", 1000, 9000);
    TF1 *fatt3 = new TF1("fatt3", "2.19*0.874/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*0.00002579),2))", 1000, 9000);

    fatt1->SetLineColor(kBlack); // I colori poi li mettiamo a posto
    fatt2->SetLineColor(kYellow);
    fatt3->SetLineColor(kOrange);

    fatt1->SetMinimum(0);
    fatt1->SetMaximum(3);

    fatt1->Draw();
    fatt2->Draw("SAME");
    fatt3->Draw("SAME");

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    f2->SetParameter(0, 2.601E-5); // 2.593E-5
    f3->SetParameter(0, 2.579E-5); // 2.652E-5

    freqvolt->Fit(f1, "N");
    freqvoltTwi->Fit(f2, "N");
    freqvoltSub->Fit(f3, "N");

    f1->Draw("SAME"); // Queste sarebbero da disegnare con la barra di errore
    f2->Draw("SAME");
    f3->Draw("SAME");

    double f = 1 / (2 * TMath::Pi() * TMath::Sqrt(f2->GetParameter(0) * f3->GetParameter(0)));
    std::cout << "La frequenza di crossover é " << f << "Hz" << '\n';

    TF1 *fs1 = new TF1("fs1", "f2-f3", 1000, 9000);
    Double_t a = f2->GetParameter(0);
    Double_t b = f3->GetParameter(0);
    fs1->SetParameter(0, a);
    fs1->SetParameter(1, b);

    std::cout << "La frequenza di crossover é " << fs1->GetX(0, 6000, 7000) << "Hz" << '\n';
}

void freqVolt2()
{
    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Amplitude graph restricted");
    TGraph *freqvolt = new TGraph("freqvolt2.txt", "%lg %lg");
    TGraph *freqvoltTwi = new TGraph("freqvoltTwi2.txt", "%lg %lg");
    TGraph *freqvoltSub = new TGraph("freqvoltSub2.txt", "%lg %lg");

    TF1 *f1 = new TF1("f1", "[0]", 5000, 7000);
    TF1 *f2 = new TF1("f2", "2.19*0.8799/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))", 5000, 7000);
    TF1 *f3 = new TF1("f3", "2.19*0.874/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))", 5000, 7000);

    TF1 *fatt1 = new TF1("fatt1", "2.19", 5000, 7000);
    TF1 *fatt2 = new TF1("fatt2", "2.19*0.8799/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*0.00002601),2))", 5000, 7000);
    TF1 *fatt3 = new TF1("fatt3", "2.19*0.874/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*0.00002579),2))", 5000, 7000);

    fatt1->SetLineColor(kBlack); // I colori poi li mettiamo a posto
    fatt2->SetLineColor(kYellow);
    fatt3->SetLineColor(kOrange);

    fatt1->SetMinimum(1);
    fatt1->SetMaximum(2.5);

    fatt1->Draw();
    fatt2->Draw("SAME");
    fatt3->Draw("SAME");

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    f2->SetParameter(0, 2.601E-5); // 2.593E-5
    f3->SetParameter(0, 2.579E-5); // 2.652E-5

    freqvolt->Fit(f1, "N");
    freqvoltTwi->Fit(f2, "N");
    freqvoltSub->Fit(f3, "N");

    f1->Draw("SAME"); // Queste sarebbero da disegnare con la barra di errore
    f2->Draw("SAME");
    f3->Draw("SAME");

    double f = 1 / (2 * TMath::Pi() * TMath::Sqrt(f2->GetParameter(0) * f3->GetParameter(0)));
    std::cout << "La frequenza di crossover é " << f << "Hz" << '\n';

    TF1 *fs1 = new TF1("fs1", "f2-f3", 5000, 7000);
    Double_t a = f2->GetParameter(0);
    Double_t b = f3->GetParameter(0);
    fs1->SetParameter(0, a);
    fs1->SetParameter(1, b);

    std::cout << "La frequenza di crossover é " << fs1->GetX(0, 6000, 7000) << "Hz" << '\n';
}

void freqPhase()
{

    TGraph *freq1 = new TGraph("freq1.txt", "%lg %lg");
    TGraph *freq2 = new TGraph("freq2.txt", "%lg %lg");
    TGraph *freq3 = new TGraph("freq3.txt", "%lg %lg");

    TF1 *f4 = new TF1("f4", "[0]+x*[1]", 500, 15000);
    TF1 *f5 = new TF1("f5", "[0]+x*[1]", 500, 15000);
    TF1 *f6 = new TF1("f6", "[0]+x*[1]", 500, 15000);

    freq1->Fit(f4, "N");
    freq2->Fit(f5, "N");
    freq3->Fit(f6, "N");

    /*freq1->SetMinimum(-1);
    freq1->SetMaximum(10);

    freq1->Draw();
    freq2->Draw("SAME");
    freq3->Draw("SAME");

    f4->Draw("SAME");
    f5->Draw("SAME");
    f6->Draw("SAME");*/

    Double_t par[6];
    f4->GetParameters(&par[0]); // Ci facciamo ridare i parametri di best fit
    f5->GetParameters(&par[2]);
    f6->GetParameters(&par[4]);

    /*for (int i = 0; i < 6; ++i)
    {
        std::cout << "p" << i << "= " << par[i] << '\n';
    }*/

    TGraph *freqpha = new TGraph("freqpha.txt", "%lg %lg");
    TGraph *freqphaTwi = new TGraph("freqphaTwi.txt", "%lg %lg");
    TGraph *freqphaSub = new TGraph("freqphaSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph");

    TF1 *f1 = new TF1("f1", "[0] + [1] * x ", 500, 15000);
    TF1 *f2 = new TF1("f2", "[1] + [2] * x + (180/TMath::Pi())*TMath::ATan(1/(2 * TMath::Pi() * x * [0]))", 500, 15000);
    TF1 *f3 = new TF1("f3", "[1] + [2] * x + (180/TMath::Pi())*TMath::ATan(-2 * TMath::Pi() * x * [0])", 500, 15000);

    f1->SetParameter(0, par[0]); // la funzione dovrebbe essere la stessa quindi diamo i parametri di prima
    f1->SetParameter(1, par[1]);
    f2->SetParameter(0, 2.601E-5);
    f2->SetParameter(1, par[2]);
    f2->SetParameter(2, par[3]);
    f3->SetParameter(0, 2.579E-5);
    f3->SetParameter(1, par[4]);
    f3->SetParameter(3, par[5]);

    freqpha->Fit(f1, "N");
    freqphaTwi->Fit(f2, "N");
    freqphaSub->Fit(f3, "N");

    Double_t para[8];

    f1->GetParameters(&para[0]);
    f2->GetParameters(&para[2]);
    f3->GetParameters(&para[5]);

    /*freqpha->SetMinimum(-100);
    freqpha->SetMaximum(100);

    freqpha->Draw();
    freqphaTwi->Draw("SAME");
    freqphaSub->Draw("SAME");

    f1->Draw("SAME");
    f2->Draw("SAME");
    f3->Draw("SAME");

    for (int i = 0; i < 8; ++i)
    {
        std::cout << para[i] << '\n';
    }*/

    TF1 *ft1 = new TF1("ft1", "f1-f4", 500, 15000);
    TF1 *ft2 = new TF1("ft2", "f2-f5", 500, 15000);
    TF1 *ft3 = new TF1("ft3", "f3-f6", 500, 15000);

    TF1 *fatt1 = new TF1("fatt1", "0", 500, 15000);
    TF1 *fatt2 = new TF1("fatt2", "(180/TMath::Pi())*TMath::ATan(1/(2 * TMath::Pi() * x * 0.00002601))", 500, 15000);
    TF1 *fatt3 = new TF1("fatt3", "(180/TMath::Pi())*TMath::ATan(-2 * TMath::Pi() * x * 0.00002579)", 500, 15000);

    fatt1->SetLineColor(kBlack); // I colori poi li mettiamo a posto
    fatt2->SetLineColor(kYellow);
    fatt3->SetLineColor(kOrange);

    ft1->SetLineColor(kGreen);
    ft2->SetLineColor(kRed);
    ft3->SetLineColor(kBlue);

    ft1->SetParameter(0, para[0]); // nella sottrzione alcuni parametri saranno uguali a prima, altri adattati al fit
    ft1->SetParameter(1, para[1]);
    ft1->SetParameter(2, par[0]);
    ft1->SetParameter(3, par[1]);
    ft2->SetParameter(0, para[2]);
    ft2->SetParameter(1, para[3]);
    ft2->SetParameter(2, para[4]);
    ft2->SetParameter(3, par[2]);
    ft2->SetParameter(4, par[3]);
    ft3->SetParameter(0, para[5]);
    ft3->SetParameter(1, para[6]);
    ft3->SetParameter(2, para[7]);
    ft3->SetParameter(3, par[4]);
    ft3->SetParameter(4, par[5]);

    fatt1->SetMinimum(-100);
    fatt1->SetMaximum(100);

    fatt1->Draw();
    fatt2->Draw("SAME");
    fatt3->Draw("SAME");
    ft1->Draw("SAME");
    ft2->Draw("SAME");
    ft3->Draw("SAME");

    std::cout << "Tc =" << ft2->GetParameter(0) << '\n';
    std::cout << "Tl =" << ft3->GetParameter(0) << '\n';
    double f = 1 / (2 * TMath::Pi() * TMath::Sqrt(ft2->GetParameter(0) * ft3->GetParameter(0)));
    std::cout << "La frequenza di crossover é " << f << "Hz" << '\n';

    TF1 *fs1 = new TF1("fs1", "ft2+ft3", 500, 15000);
    for (int i = 0; i < 5; ++i)
    {
        fs1->SetParameter(i, ft2->GetParameter(i));
        fs1->SetParameter(i + 5, ft3->GetParameter(i));
    }
    fs1->Draw("SAME");
    std::cout << "La frequenza di crossover é " << fs1->GetX(0, 5000, 6500) << "Hz" << '\n';
}
