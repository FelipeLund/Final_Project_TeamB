#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include "tempTrender.h"
#include "parse_csv.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << ">>> The user supplied " << filePath <<" as the path to the data file.\n\n";
	//store in member variable called _filepath
	_filepath = filePath;

}

//Function to create histograms
void tempTrender::create_hist(std::vector<double> vector_of_degrees) const{
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 100, -20, 40);
	hist->SetFillColor(kRed + 1); //red color
	//adding all elements to histogram
	for (double element : vector_of_degrees){
    	hist->Fill(element);
	}
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation

	hist->GetXaxis()->SetTitle("Temperature [#circ C]");
	hist->GetYaxis()->SetTitle("Counts");

	TCanvas* c1 = new TCanvas();

	hist->Draw();
}


void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const{

	// Converting integer month and day to string for comparing with Datum column
	std::string _month;
	std::string _day;
	std::string test_string;

	// Making sure month and day is in the correct format
	if (monthToCalculate < 10){
		_month = "0" + std::to_string(monthToCalculate);
	}
	else{
		_month = std::to_string(monthToCalculate);
	}

	if (dayToCalculate < 10){
		_day = "0" + std::to_string(dayToCalculate);
	}
	else{
		_day = std::to_string(dayToCalculate);
	}

	// Final String
	test_string = _month + "-" + _day;
	std::cout << ">>> The user supplied the date (mm-dd): " << test_string << "\n\n";

	// Parsing through csv and adding desired information to info_vector
	std::vector<double> info_vector;
	std::string filename = _filepath;
	info_vector = extract_temp_for_month_day (test_string, filename);

	// Creating and printing the histogram
	std::cout << "Making the histogram...\n\n";
	create_hist(info_vector);

}

void tempTrender::maxTempOverTime()const{
	std::vector<double> max_temps;
	std::string filename = _filepath;
	max_temps = maxTempInYears(filename);
	std::cout << "Plotting Max Temp Over Time... \n\n";

	// Plotting the data
	std::vector<double> years = getYearsList(filename);
	TCanvas* c2 = new TCanvas();
	int n = years.size();
	TGraph *gr = new TGraph(n, &years[0], &max_temps[0]);
   	gr->SetTitle("Max Temperatures every year");
	gr->GetXaxis()->SetTitle("Time [y]");
	gr->GetYaxis()->SetTitle("Max Temperature [#circ C]");
	gr->SetLineColor(6);
    //gr->SetLineWidth(2); //un-comment if thicker lines are preferred
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(5);
   	gr->Draw();
}

void tempTrender::minTempOverYears()const{
	std::vector<double> min_temps;
	std::string filename = _filepath;
	min_temps = minTempInYears(filename);
	std::cout << "Plotting the minimum temperature Over Time... \n\n";

	// Plotting the data
	std::vector<double> years = getYearsList(filename);
	TCanvas* c3 = new TCanvas();
	int n = years.size();
	TGraph *gr = new TGraph(n, &years[0], &min_temps[0]);
   	gr->SetTitle("Min Temperatures every year");
	gr->GetXaxis()->SetTitle("Time [y]");
	gr->GetYaxis()->SetTitle("Min Temperature [#circ C]");
	gr->SetLineColor(6);
    //gr->SetLineWidth(2); //un-comment if thicker lines are preferred
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(5);
   	gr->Draw();
}

void tempTrender::dailyTempOverTime()const{
	std::vector<double> dailyTempOvertime = getDailyTempOverTime(_filepath);
	int n = dailyTempOvertime.size();
	std::cout << "Plotting average daily temp for " << n << " days...\n\n";

	// Plotting the data
	double start = 1;
	std::vector<double> days_passed(n);
	std::iota(days_passed.begin(), days_passed.end(), start);
	TCanvas* c4 = new TCanvas();
	c4->SetCanvasSize(3000, 500); //width, height

	TGraph *gr = new TGraph(n, &days_passed[0], &dailyTempOvertime[0]);
   	gr->SetTitle("Average Daily Temperatures over time");
	gr->GetXaxis()->SetTitle("Time [#days passed from first record]");
	gr->GetYaxis()->SetTitle("Average Temperature [#circ C]");
	gr->SetLineColor(6);
    gr->SetMarkerColor(4);
   	gr->Draw("AP");

	// Finding the time between each year's max temperature
	std::vector<int> indices = max_temp_positions(_filepath);
	std:vector<int> diff;
	for (int i=1; i<indices.size(); i++){
		diff.push_back(days_passed[i]-days_passed[i-1]);
	}

	std::vector<int> x(indices.size());
	std::iota(x.begin(), x.end(), start);
	
	TCanvas* c5 = new TCanvas();
	TGraph *gr2 = new TGraph(n, &x[0], &diff[0]);
   	gr2->SetTitle("max temp time passed diff");
	gr2->GetXaxis()->SetTitle("Time [..]");
	gr2->GetYaxis()->SetTitle("diff");
	gr2->SetLineColor(6);
    gr2->SetMarkerColor(4);
   	gr2->Draw("AP");
	

}

// Diff between days of max daily avg temperatures // uncomment and move this where you want

//std::vector<string> MaxDaysList = Day_MaxDailyAvgTemp_Year(_filepath);  
//std::vector<string> AllDays = getAllDatums(_filepath);
//std::vector<int> DayNoList;
//std::vector<int> DiffList;
//int DayCounter=1;
//int j=0; //index for MaxDaysList
//for (i:AllDays) {
//	if (i==MaxDaysList[j]) {
//		int diff=DayCounter-DayNoList[DayNoList.back]; 
//		DiffList.push_back(diff);
//		DayNoList.push_back(DayCounter);
//		j++;
		
//	}
//	DayCounter++
//}




