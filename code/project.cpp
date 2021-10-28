#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>
#include <TH1F.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>


std::vector<double> extrac_temp_for_day(int month, int day, const std::string& filename){
	// Converting integer month and day to string for comparing with Datum column
	std::string _month;
	std::string _day;
	std::string test_string;
	if (month < 10){
		_month = "0" + std::to_string(month);
	}
	else{
		_month = std::to_string(month);
	}
	if (day < 10){
		_day = "0" + std::to_string(day);
	}
	else{
		_day = std::to_string(day);
	}

	// Final String
	test_string = _month + "-" + _day;

	// Parsing Through csv and extracting values 
	std::vector<double> info_vector;
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

	//Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;
	
	// Pushing to info vector
	while(in.read_row(datum, tid, temp, quality)){
		if (datum.substr(5, 5) == test_string){
			//std::cout << "Getting temperature for date: " << datum <<  "\n";
			info_vector.push_back(temp);
		};

	};
	
	/*
	for (double i : info_vector){
		std::cout << "i value: " << i << "\n";
	};
	*/

	return info_vector;
}

int main() {
	const std::string pathToFile = "../CleanDatasets/CleanLund/"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//std::vector<double> info_for_hist{parse_smhi(_filename)};


	std::vector<double> info_vector;
	std::string filename = ("CleanLund.csv");

	info_vector = extrac_temp_for_day(12, 15, filename);
	
	
	for (double i : info_vector){
		std::cout << "i value: " << i << "\n";
		//double new_i;
	}

	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);

	
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



	
	return 0;
	
}

