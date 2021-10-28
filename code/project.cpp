#include "tempTrender.h"
#include <string>
#include "parse_csv.h"
#include <iostream>

int main() {
	const std::string pathToFile = "../CleanDatasets/CleanLund"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object

	
	t.tempOnDay(8, 27); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);

	
	//Creating histogram
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature
	[#circC];Entries", 300, -20, 40);
	hist->SetFillColor(kRed + 1);
	
	//Filling the histogram
	for (int index = 0; index < degree.size()){
		hist->Fill(degree[index]); //Increment the bin corresponding 
	}
	
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation
	TCanvas* can = new TCanvas();
                
	for(int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
		hist->SetBinContent(bin, 5);
		hist->SetBinError(bin, sqrt(5.));
	}
	hist->Draw();

	std::cout::"\n";


	
	return 0;
	
}

