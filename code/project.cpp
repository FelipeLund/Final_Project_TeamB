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


void test_func(int a){
	std::cout << a << "\n";
}

int main() {
	const std::string pathToFile = "./ClnData/CleanLund.csv"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object
	t.tempOnDay(12, 15);
	t.maxTempOverTime();
	getYearsList("CleanLund.csv");

	std::string test_string = "12-15";
	std::vector<double> info_vector = maxTempInYears(t._filepath);
	std::vector<int> year_vector = getYearsList(t._filepath);

	/*
	for (auto i : info_vector){
		std::cout<< i<<", ";
	};
	*/

	std::cout << "Size of yearsList vector : " << year_vector.size() << "\n";
	std::cout << "First year in years list: " << year_vector[0] << "\n";
	int n = year_vector.size();
	std::cout << "Last year in years list: " << year_vector[n-1] << "\n";
	std::cout << "Size of maxtempYear vector : " << info_vector.size() << "\n";

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

