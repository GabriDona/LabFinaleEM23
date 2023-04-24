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