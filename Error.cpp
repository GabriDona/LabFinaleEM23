void gaussErr()
{
    using namespace std;
	ifstream ifs("Err10k.txt");
	int pi;
	TCanvas* c=new TCanvas("c","c",600,600);
	TH1D* hist=new TH1D("hist","Err10k.txt",100,2.126,2.129);
	while(ifs.is_open() && !ifs.eof()){
		ifs >> pi;
		hist->Fill(pi);
	}
	hist->Draw();
	
	ifs.close();
}
