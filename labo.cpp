#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH3F.h"
#include <cmath>

double myF2(double *x, double *par)
{
    double V = 4.35;
    double xx = x[0];
    double val = 4.35287 / TMath::Sqrt(1 + 1 / TMath::Power((2 * TMath::Pi() * xx * par[0]), 2)); //(1 / ((2 * TMath::Pi() * xx * par[0]) * (2 * TMath::Pi() * xx * par[0])))
    return val;
}

double myF3(double *x, double *par)
{
    double V = 4.35;
    double xx = x[0];
    double val = (345.7 * V) / sqrt(((383.46) * (383.46)) + (2 * TMath::Pi() * xx * par[0]) * (2 * TMath::Pi() * xx * par[0]));
    return val;
}

double myF4(double *x, double *par) // fase twee
{
    double V = 4.3;
    double xx = x[0];
    double val = TMath::ATan(1 / (2 * TMath::Pi() * xx * par[0] * 391.73));
    return val;
}

double myF5(double *x, double *par) // fase woo
{
    double V = 4.3;
    double xx = x[0];
    double val = TMath::ATan(((2 * TMath::Pi() * xx * par[0]) / 383.46));
    return val;
}

void voltTime() // restituisce il grafico Ampiezza-Tempo
{               // Amplitude (v) - Time (s)

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
    freqvolt->Fit(f1);
    double_t V = f1->GetParameter(0);
    TF1 *f2 = new TF1("f2", "4.35287/TMath::Sqrt(1+1/TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000); // fit con i dati sperimentali
    TF1 *f3 = new TF1("f3", "4.35287 / TMath::Sqrt(1+TMath::Power((2*TMath::Pi()*x*[0]),2))", 1000, 9000);

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    freqvoltTwi->SetMinimum(0);
    freqvoltTwi->SetMaximum(5);

    f2->SetParameter(0, 0.00001985);
    freqvoltTwi->Fit(f2);
    freqvoltTwi->Draw();

    f3->SetParameter(0, 0.00005358);
    freqvoltSub->Fit(f3);
    freqvoltSub->Draw("SAME");

    freqvolt->Draw("SAME");
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

    f2->SetParameter(0, 0.00001985);
    freqvoltTwi->Fit(f2);
    freqvoltTwi->Draw();

    f3->SetParameter(0, 0.00005358);
    freqvoltSub->Fit(f3);
    freqvoltSub->Draw("SAME");

    freqvolt->Draw("SAME");
}

void freqPhase()
{
    TGraph *freqpha = new TGraph("freqpha.txt", "%lg %lg");
    TGraph *freqphaTwi = new TGraph("freqphaTwi.txt", "%lg %lg");
    TGraph *freqphaSub = new TGraph("freqphaSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph");

    TF1 *f1 = new TF1("f1", "[0]", 1000, 9000);
    TF1 *f2 = new TF1("f2", "TMath::ATan(1/(2 * TMath::Pi() * x * [0]))", 1000, 9000); // fit con i dati sperimentali
    TF1 *f3 = new TF1("f3", "TMath::ATan(-2 * TMath::Pi() * x * [0])", 1000, 9000);

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);

    freqphaTwi->SetMinimum(-100);
    freqphaTwi->SetMaximum(100);

    f2->SetParameter(0, 0.00001985);
    freqphaTwi->Fit(f2);
    freqphaTwi->Draw();

    f3->SetParameter(0, 0.00005358);
    freqphaSub->Fit(f3);
    freqphaSub->Draw("SAME");

    f1->SetParameter(0, 0);
    freqpha->Fit(f1);
    freqpha->Draw("SAME");


    TGraph *freq1 = new TGraph("freq1.txt", "%lg %lg"); // Dati relativi al canale 1
    TGraph *freq2 = new TGraph("freq2.txt", "%lg %lg"); // Dati relativi al canale 2
    TGraph *freq3 = new TGraph("freq3.txt", "%lg %lg"); // Dati relativi al canale 3

    freq1->SetTitle("Systematic Error; Frequency (Hz); Phase(rad)");
    TF1 *f4 = new TF1("f4", "[0]+x*[1]", 0, 100); 
    TF1 *f5 = new TF1("f5", "[2]+x*[3]", 0, 100);
    TF1 *f6 = new TF1("f6", "[4]+x*[5]", 0, 100);
    f1->SetParameter(0, 0);
    f2->SetParameter(0, 0);
    f3->SetParameter(0, 0);
    f1->SetParameter(1, 0);
    f2->SetParameter(1, 0);
    f3->SetParameter(1, 0);

    freq1->Fit(f4);
    freq2->Fit(f5);
    freq3->Fit(f6);

    TF1 *ft1 = new TF1("ft1", "f1-f4", 0, 100); 
    TF1 *ft2 = new TF1("ft2", "f2-f5", 0, 100); 
    TF1 *ft3 = new TF1("ft3", "f3-f6", 0, 100); 

    //da qui in poi non so come ndare avanti perchè non mi ricordo quella dei fotoni, guarda cosa riesci a fare. 

}

void freqPhase2()
{
    TGraph *freqpha2 = new TGraph("freqpha2.txt", "%lg %lg");
    TGraph *freqphaTwi2 = new TGraph("freqphaTwi2.txt", "%lg %lg");
    TGraph *freqphaSub2 = new TGraph("freqphaSub2.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph restricted");
}

void sisErr() // dipendenza lineare errore sistematico (t=1 microsec) , non c'è la y sennò da problemi di compilazione
{
    TGraph *freq1 = new TGraph("freq1.txt", "%lg %lg"); // Dati relativi al canale 1
    TGraph *freq2 = new TGraph("freq2.txt", "%lg %lg"); // Dati relativi al canale 2
    TGraph *freq3 = new TGraph("freq3.txt", "%lg %lg"); // Dati relativi al canale 3

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Systematic Error");
    freq1->SetTitle("Systematic Error; Frequency (Hz); Phase(rad)");
    TF1 *f1 = new TF1("f1", "[0]+x*[1]", 0, 100); //?? l'intercetta all'ordinata è 0 o tengo parametro libero??
    TF1 *f2 = new TF1("f2", "[2]+x*[3]", 0, 100);
    TF1 *f3 = new TF1("f3", "[4]+x*[5]", 0, 100);
    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);
    freq1->Fit(f1);
    freq2->Fit(f2);
    freq3->Fit(f3);
    freq1->Draw("APE");
    freq2->Draw("CD");
    freq3->Draw("CD");

    std::cout << "Fit Parameters :"
              << "\n";
    for (int i{0}; i < 3; ++i)
    {
        for (int j{0}; j < 3; ++j)
        {
            std::cout << "f" << i << " = " << f1->GetParameter(j) << "\n";
        }
    }
}
