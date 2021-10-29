#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>

// Root Includes 
/*
#include <TH1F.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
*/


int main() {
	const std::string pathToFile = "../CleanDatasets/CleanLund.csv"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object
	//t.tempOnDay(8, 23); //Call some functions that you've implemented

	std::vector<double> info_vector;
	std::string filename = ("CleanLund.csv");
	info_vector = extrac_temp_for_day(12, 15, filename);
	/*
	for (double i : info_vector){
		std::cout << "i value: " << i << "\n";
		//double new_i;
	}
	*/
	t.tempOnDay(12, 15);

	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);

	

	/*
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
	hist->SetFillColor(kRed + 1);

	for (double element : info_vector){
		hist->Fill(element);
	}
	
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation
	TCanvas* can = new TCanvas();
                
	// Adding Error Bars			
	for(int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
		hist->SetBinContent(bin, 5);
		hist->SetBinError(bin, sqrt(5.));
	}
	hist->Draw();

	std::cout << "\n";
	*/



	
	return 0;
	
}

