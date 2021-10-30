#include <iostream>
#include <string>
#include <numeric>
#include "tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	//std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
	std::cout << "filepath is stored in member variable called _filepath \n";
	_filepath = filePath;
}

//Function to create hisotgrams
void tempTrender::create_hist(std::vector<double> vector_of_degrees) const{
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 100, -20, 40);
	hist->SetFillColor(kRed + 1); //red color
	//adding all elements to histogram
	for (double element : vector_of_degrees){
    	hist->Fill(element);
	}
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation
	TCanvas* c1 = new TCanvas();

	hist->Draw();
}



void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const{
	std::cout << "Starting tempOnDay Function... \n";

	// Converting integer month and day to string for comparing with Datum column
	std::string _month;
	std::string _day;
	std::string test_string;

	// Making sure month and day is in the correct format
	if (monthToCalculate < 10){_month = "0" + std::to_string(monthToCalculate);}
	else{_month = std::to_string(monthToCalculate);}
	if (dayToCalculate < 10){_day = "0" + std::to_string(dayToCalculate);}
	else{_day = std::to_string(dayToCalculate);}

	// Final String
	test_string = _month + "-" + _day;

	// Parsing through csv and adding desired information to info_vector
	std::vector<double> info_vector;
	std::string filename = _filepath;
	info_vector = extract_temp_for_month_day (test_string, filename);


	// Creating and printing the histogram
	std::cout << "Now making a histogram.\n";
	create_hist(info_vector);
}


void tempTrender::maxTempOverTime()const {
	std::cout << "Max Temp Over Time starting... \n";
	std::vector<double> max_temps;
	std::string filename = _filepath;
	max_temps = maxTempInYears(filename);
	std::cout << "First element of max_temps vector: "<< max_temps[0] <<  "\n";
	std::cout << "Plotting Max Temp Over Time starting... \n";
	
	// Plotting the data
	std::vector<double> years = getYearsList(filename);
	TCanvas* c2 = new TCanvas();
	int n = years.size();
	max_temps.pop_back();
	TGraph *gr = new TGraph(n, &years[0], &max_temps[0]);
   	gr->SetTitle("Max Temperatures every year");
   	gr->Draw();



}

void tempTrender::dailyTempOverTime()const{
	std::cout << "Getting average daily temp for every single day... \n";
	std::vector<double> dailyTempOvertime = getDailyTempOverTime(_filepath);
	int n = dailyTempOvertime.size();
	std::cout << "Number of days: " << n << "\n";

	// Plotting the data
	double start = 1;
	std::vector<double> days_passed(n);
	std::iota(days_passed.begin(), days_passed.end(), start);
	TCanvas* c3 = new TCanvas();
	c3->SetCanvasSize(3000, 500); 

	TGraph *gr = new TGraph(n, &days_passed[0], &dailyTempOvertime[0]);
   	gr->SetTitle("Daily Temperatures over time");
   	gr->Draw("AP");
	
}
