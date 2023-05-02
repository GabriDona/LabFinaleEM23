#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH3F.h"
#include <cmath>

// Utilizzare al CANALE 1 il GENERATORE, al CANALE 2 il TWEETER e al CANALE 3 il WOOFER
// QUELLE COMMENTATE SONO LE FORMULE E I DATI NOSTRI, CONTROLLARE LA RESISTENZA DI L
// Inserire come V sempre quello immesso

void voltTime()                                              // restituisce il grafico Ampiezza-Tempo
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
    TF1 *f2 = new TF1("f2", "4.35287/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);
    // V*0.8796/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))
    TF1 *f3 = new TF1("f3", "4.35287/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);
    // V*0.9016/Tmath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))

    TF1 *fatt1 = new TF1("fatt1", "4.3528", 1000, 9000);
    TF1 *fatt2 = new TF1("fatt2", "4.3528/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*0.00001985),2))", 1000, 9000);
    // V*0.8796/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*0.00002593),2))
    TF1 *fatt3 = new TF1("fatt3", "4.3528/TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*0.00005358),2))", 1000, 9000);
    // V*0.9016/Tmath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*0.00002652),2))

    fatt1->SetLineColor(kBlack); // I colori poi li mettiamo a posto
    fatt2->SetLineColor(kYellow);
    fatt3->SetLineColor(kOrange);

    fatt1->SetMinimum(0);
    fatt1->SetMaximum(5);

    fatt1->Draw();
    fatt2->Draw("SAME");
    fatt3->Draw("SAME");

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    f2->SetParameter(0, 0.00001985); // 2.593E-5
    f3->SetParameter(0, 0.00005358); // 2.652E-5

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

    std::cout << "La frequenza di crossover é " << fs1->GetX(0, 4000, 5000) << "Hz" << '\n';
}

void freqVolt2()
{
    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Amplitude graph restricted");
    TGraph *freqvolt = new TGraph("freqvolt.txt", "%lg %lg");
    TGraph *freqvoltTwi = new TGraph("freqvoltTwi.txt", "%lg %lg");
    TGraph *freqvoltSub = new TGraph("freqvoltSub.txt", "%lg %lg");

    TF1 *f1 = new TF1("f1", "[0]", 1000, 9000);
    freqvolt->Fit(f1);
    double_t V = f1->GetParameter(0);
    TF1 *f2 = new TF1("f2", "4.35287/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000); // fit con i dati sperimentali
    TF1 *f3 = new TF1("f3", "4.35287 / TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    freqvoltTwi->SetMinimum(0);
    freqvoltTwi->SetMaximum(5);

    f2->SetParameter(0, 0.00001985); // 2.593E-5
    freqvoltTwi->Fit(f2);
    freqvoltTwi->Draw();

    f3->SetParameter(0, 0.00005358); // 2.652E-5
    freqvoltSub->Fit(f3);
    freqvoltSub->Draw("SAME");

    freqvolt->Draw("SAME");
}

void freqPhase()
{

    TGraph *freq1 = new TGraph("freq1.txt", "%lg %lg");
    TGraph *freq2 = new TGraph("freq2.txt", "%lg %lg");
    TGraph *freq3 = new TGraph("freq3.txt", "%lg %lg");

    TF1 *f4 = new TF1("f4", "[0]+x*[1]", 1050, 8900);
    TF1 *f5 = new TF1("f5", "[0]+x*[1]", 1050, 8900);
    TF1 *f6 = new TF1("f6", "[0]+x*[1]", 1050, 8900);

    freq1->Fit(f4, "N");
    freq2->Fit(f5, "N");
    freq3->Fit(f6, "N");

    /*freq1->SetMinimum(-1);
    freq1->SetMaximum(10);

    freq1->Draw();
    freq2->Draw("SAME");
    freq3->Draw("SAME");*/

    Double_t par[6];
    f4->GetParameters(&par[0]); // Ci facciamo ridare i parametri di best fit
    f5->GetParameters(&par[2]);
    f6->GetParameters(&par[4]);

    for (int i = 0; i < 6; ++i)
    {
        std::cout << "p" << i << "= " << par[i] << '\n';
    }

    TGraph *freqpha = new TGraph("freqpha.txt", "%lg %lg");
    TGraph *freqphaTwi = new TGraph("freqphaTwi.txt", "%lg %lg");
    TGraph *freqphaSub = new TGraph("freqphaSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph");

    TF1 *f1 = new TF1("f1", "[0] + [1] * x ", 1000, 9000);
    TF1 *f2 = new TF1("f2", "[1] + [2] * x + (180/TMath::Pi())*TMath::ATan(1/(2 * TMath::Pi() * x * [0]))", 1050, 8900);
    TF1 *f3 = new TF1("f3", "[1] + [2] * x + (180/TMath::Pi())*TMath::ATan(-2 * TMath::Pi() * x * [0])", 1050, 8900);

    f1->SetParameter(0, par[0]); // la funzione dovrebbe essere la stessa quindi diamo i parametri di prima
    f1->SetParameter(1, par[1]);
    f2->SetParameter(0, 0.00001985); // 2.593E-5
    f2->SetParameter(1, par[2]);
    f2->SetParameter(2, par[3]);
    f3->SetParameter(0, 0.00005358); // 2.652E-5
    f3->SetParameter(1, par[4]);
    f3->SetParameter(3, par[5]);

    freqpha->Fit(f1, "N");
    freqphaTwi->Fit(f2, "N");
    freqphaSub->Fit(f3, "N");

    Double_t para[8];

    f1->GetParameters(&para[0]);
    f2->GetParameters(&para[2]);
    f3->GetParameters(&para[5]);

    // freqpha->Draw();
    // freqphaTwi->Draw();
    // freqphaSub->Draw("SAME");

    /*for (int i = 0; i < 8; ++i)
    {
        std::cout << para[i] << '\n';
    }*/

    TF1 *ft1 = new TF1("ft1", "f1-f4", 0, 10000);
    TF1 *ft2 = new TF1("ft2", "f2-f5", 0, 10000);
    TF1 *ft3 = new TF1("ft3", "f3-f6", 0, 10000);

    TF1 *fatt1 = new TF1("fatt1", "0", 0, 10000);
    TF1 *fatt2 = new TF1("fatt2", "(180/TMath::Pi())*TMath::ATan(1/(2 * TMath::Pi() * x * 0.00001985))", 0, 10000);
    //(180/TMath::Pi())*TMath::ATan(1/(2 * TMath::Pi() * x * 0.00002593))
    TF1 *fatt3 = new TF1("fatt3", "(180/TMath::Pi())*TMath::ATan(-2 * TMath::Pi() * x * 0.00005358)", 0, 10000);
    //(180/TMath::Pi())*TMath::ATan(-2 * TMath::Pi() * x * 0.00002652)

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

    std::cout << "Tc =" << ft2->GetParameter(0) << '\n'; //QUESTI NON VENGONO
    std::cout << "Tl =" << ft3->GetParameter(0) << '\n'; //SONO DA RICONTROLLARE CON I DATI GIUSTI
    double f = 1 / (2 * TMath::Pi() * TMath::Sqrt(ft2->GetParameter(0) * ft3->GetParameter(0)));
    std::cout << "La frequenza di crossover é " << f << "Hz" << '\n';

    TF1 *fs1 = new TF1("fs1", "ft2+ft3", 1000, 9000);
    for( int i=0; i<5; ++i) {
        fs1->SetParameter(i, ft2->GetParameter(i));
        fs1->SetParameter(i+5, ft3->GetParameter(i));
    }
    fs1->Draw("SAME");
    std::cout << "La frequenza di crossover é " << fs1->GetX(0, 5000, 6500) << "Hz" << '\n';
}

void freqPhase2()
{
    TGraph *freqpha2 = new TGraph("freqpha2.txt", "%lg %lg");
    TGraph *freqphaTwi2 = new TGraph("freqphaTwi2.txt", "%lg %lg");
    TGraph *freqphaSub2 = new TGraph("freqphaSub2.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph restricted");
}
