#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>

// Root Includes 
#include <TH1F.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>

//Extracting information to a vector
std::vector<double> info_vector = extract_temp_for_month_day ("05-10", "./ClnData/CleanLund.csv");	

//Function to create hisotgrams
void create_hist(std::vector<double> vector_of_degrees){
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 100, -20, 40);
	hist->SetFillColor(kRed + 1); //red color
	//adding all elements to histogram
	for (double element : vector_of_degrees){
		hist->Fill(element);
	}
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation
	TCanvas* can = new TCanvas();

	hist->Draw();
}
	

int main() {
	const std::string pathToFile = "./ClnData/CleanLund.csv"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object

	return 0;	
}

