#include "tempTrender.h"
#include <string>
#include "parse_csv.h"
#include <iostream>

int main() {
	const std::string pathToFile = "./CleanLund.csv"; //path to data file
	tempTrender t(pathToFile); //Instantiate your analysis object
	std::cout << "Hello" << "\n";

	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);

	/*

	TH1I* hist = new TH1I("temperature", "Temperature;Temperature
	[#circC];Entries", 300, -20, 40);
	hist->SetFillColor(kRed + 1);
	hist->Fill(-3.2); //Increment the bin corresponding to -3.2 C
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation
	TCanvas* can = new TCanvas();
                
	for(int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
		hist->SetBinContent(bin, 5);
		hist->SetBinError(bin, sqrt(5.));
	}
	hist->Draw();

	std::cout::"\n";


	*/
	return 0;
	
}

