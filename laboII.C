#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH3F.h"
#include <cmath>

double myF2(double *x, double *par)
{
    double V = 4.3;
    double xx = x[0];
    double val = (344.6 * V) / sqrt(((383.73) * 383.73) + TMath::Power((2 * TMath::Pi() * xx * par[0]), -2)); //(1 / ((2 * TMath::Pi() * xx * par[0]) * (2 * TMath::Pi() * xx * par[0])))
    return val;
}

double myF3(double *x, double *par)
{
    double V = 4.3;
    double xx = x[0];
    double val = (345.7 * V) / sqrt(((383.46) * (383.46)) + (2 * TMath::Pi() * xx * par[0]) * (2 * TMath::Pi() * xx * par[0]));
    return val;
}

double myF4(double *x, double *par) //fase twee
{
    double V = 4.3;
    double xx = x[0];
    double val = ;
    return val;
}

double myF5(double *x, double *par) // fase woo
{
    double V = 4.3;
    double xx = x[0];
    double val = (345.7 * V) / sqrt(((383.46) * (383.46)) + (2 * TMath::Pi() * xx * par[0]) * (2 * TMath::Pi() * xx * par[0]));
    return val;
}

void voltTime15() // restituisce il grafico Ampiezza-Tempo
{                 // Amplitude (v) - Time (s)

    TGraph *freqGen1 = new TGraph("freqGen.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo generata
    TGraph *freqTwi1 = new TGraph("freqTwi.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo twiter
    TGraph *freqSub1 = new TGraph("freqSub.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo woofer
    TMultiGraph *mg = new TMultiGraph;
    mg->SetTitle("15 KHz - Behavior; Time(s); Amplitude(V)");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "n1 Heartz Behavior"); // sovrapponi 3 grafici

    freqGen1->SetLineColor(40);
    freqGen1->SetMarkerColor(40);

    freqTwi1->SetLineColor(46);
    freqTwi1->SetMarkerColor(46);

    freqSub1->SetLineColor(38);
    freqSub1->SetMarkerColor(38);
    mg->Add(freqTwi1);
    mg->Add(freqSub1);
    mg->Add(freqGen1);

    mg->Draw("apl");

    auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend->AddEntry(freqGen1, "Vi", "l");
    legend->AddEntry(freqTwi1, "Twitter", "l");
    legend->AddEntry(freqSub1, "Woofer", "l");
    legend->Draw();
    myCanvas1->Print("Prel15KHz.pdf");
}
void voltTime6() // restituisce il grafico Ampiezza-Tempo
{                // Amplitude (v) - Time (s)

    TGraph *freqGen1 = new TGraph("freqGen1.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo generata
    TGraph *freqTwi1 = new TGraph("freqTwi1.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo twiter
    TGraph *freqSub1 = new TGraph("freqSub1.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo woofer
    TMultiGraph *mg = new TMultiGraph;

    mg->SetTitle("6.1 KHz - Behavior; Time(s); Amplitude(V)");

    TCanvas *myCanvas2 = new TCanvas("myCanvas2", "6.1 KHeartz Behavior"); // sovrapponi 3 grafici

    freqGen1->SetLineColor(40);
    freqGen1->SetMarkerColor(40);

    freqTwi1->SetLineColor(46);
    freqTwi1->SetMarkerColor(46);

    freqSub1->SetLineColor(38);
    freqSub1->SetMarkerColor(38);
    mg->Add(freqTwi1);
    mg->Add(freqSub1);
    mg->Add(freqGen1);

    mg->Draw("apl");
    auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend->AddEntry(freqGen1, "Vi", "l");
    legend->AddEntry(freqTwi1, "Twitter", "l");
    legend->AddEntry(freqSub1, "Woofer", "l");
    legend->Draw();
    myCanvas2->Print("Prel6KHz.pdf");
}
void voltTime300() // restituisce il grafico Ampiezza-Tempo
{                  // Amplitude (v) - Time (s)

    TGraph *freqGen1 = new TGraph("freqGen2.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo generata
    TGraph *freqTwi1 = new TGraph("freqTwi2.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo twiter
    TGraph *freqSub1 = new TGraph("freqSub2.txt", "%lg %lg"); // Dati relativi alla ampiezza - tempo woofer
    TMultiGraph *mg = new TMultiGraph;
    mg->SetTitle("300 Hz - Behavior; Time(s); Amplitude(V)");

    TCanvas *myCanvas3 = new TCanvas("myCanvas3", "300 Heartz Behavior"); // sovrapponi 3 grafici

    freqGen1->SetLineColor(40);
    freqGen1->SetMarkerColor(40);

    freqTwi1->SetLineColor(46);
    freqTwi1->SetMarkerColor(46);

    freqSub1->SetLineColor(38);
    freqSub1->SetMarkerColor(38);
    mg->Add(freqTwi1);
    mg->Add(freqSub1);
    mg->Add(freqGen1);

    mg->Draw("apl");
    auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend->AddEntry(freqGen1, "Vi", "l");
    legend->AddEntry(freqTwi1, "Twitter", "l");
    legend->AddEntry(freqSub1, "Woofer", "l");
    legend->Draw();
    myCanvas3->Print("Prel300Hz.pdf");
}

void freqVolt()
{
    TGraph *freqvolt = new TGraph("freqvolt.txt", "%lg %lg");
    TGraph *freqvoltTwi = new TGraph("freqvoltTwi.txt", "%lg %lg");
    TGraph *freqvoltSub = new TGraph("freqvoltSub.txt", "%lg %lg");

    TF1 *f1 = new TF1("f1", "[0]", 2000, 8000);
    freqvolt->Fit(f1);
    double_t V = f1->GetParameter(0);
    TF1 *f2 = new TF1("f2", myF2, 2000, 8000, 1); // fit con i dati sperimentali
    TF1 *f3 = new TF1("f3", myF3, 2000, 8000, 1);

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);
    TCanvas *myCanvas2 = new TCanvas("myCanvas1", "Frequency/Amplitude graph");
    freqvolt->Draw("APE");

    freqvoltTwi->Fit(f2, "R");
    freqvoltTwi->Draw("APE");
    // freqvoltSub->Fit(f3, "R");
    // freqvoltSub->Draw(); // l'ho fatto solo per uno perchè non sono sicuro della forma, se va bene basta fare copia incolla
}

void freqVolt2()
{
    TGraph *freqvolt2 = new TGraph("freqvolt2.txt", "%lg %lg");
    TGraph *freqvoltTwi2 = new TGraph("freqvoltTwi2.txt", "%lg %lg");
    TGraph *freqvoltSub2 = new TGraph("freqvoltSub2.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Amplitude graph restricted");
}

void freqPhase()
{
    TGraph *freqpha = new TGraph("freqpha.txt", "%lg %lg");
    TGraph *freqphaTwi = new TGraph("freqphaTwi.txt", "%lg %lg");
    TGraph *freqphaSub = new TGraph("freqphaSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph");
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
