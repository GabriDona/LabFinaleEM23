#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH3F.h"
#include <cmath>


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

void freqVolt() {
    TGraph *freqvolt = new TGraph("freqvolt.txt", "%lg %lg");
    TGraph *freqvoltTwi = new TGraph("freqvoltTwi.txt", "%lg %lg");
    TGraph *freqvoltSub = new TGraph("freqvoltSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Amplitude graph");

    TF1 *f1 = new TF1("f1", "[0]", 0, 100);
    freqvolt->Fit(f1);
    double_t V = f1->GetParameter(0);
    TF1 *f2 = new TF1("f2", "(344.6*V)/radq((391.73)^2 + (2*Pi*x*[2])^(-2))", 0, 100000); // fit con i dati sperimentali
    TF1 *f3 = new TF1("f3", "(345.7*V)/radq((383.46)^2 + (2*Pi*x*[3])^2)", 0, 100000);

    f1->SetLineColor(kGreen);
    f2->SetLineColor(kRed);
    f3->SetLineColor(kBlue);
    
    freqvoltTwi->Fit(f2);
    freqvoltSub->Fit(f3);
    freqvolt->Draw("APE");
    freqvoltTwi->Draw("CD");
    freqvoltSub->Draw("CD"); // l'ho fatto solo per uno perchè non sono sicuro della forma, se va bene basta fare copia incolla

}

void freqVolt2() {
    TGraph *freqvolt2 = new TGraph("freqvolt2.txt", "%lg %lg");
    TGraph *freqvoltTwi2 = new TGraph("freqvoltTwi2.txt", "%lg %lg");
    TGraph *freqvoltSub2 = new TGraph("freqvoltSub2.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Amplitude graph restricted");
}

void freqPhase() {
    TGraph *freqpha = new TGraph("freqpha.txt", "%lg %lg");
    TGraph *freqphaTwi = new TGraph("freqphaTwi.txt", "%lg %lg");
    TGraph *freqphaSub = new TGraph("freqphaSub.txt", "%lg %lg");

    TCanvas *myCanvas1 = new TCanvas("myCanvas1", "Frequency/Phase graph");
}

void freqPhase2() {
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