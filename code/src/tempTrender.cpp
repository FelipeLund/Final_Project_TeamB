#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <TLegend.h>
#include <TStyle.h>
#include <TLegendEntry.h>
#include <tempTrender.h>
#include <parse_csv.h>

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << ">>> The user supplied " << filePath <<" as the path to the data file.\n\n";
	//store in member variable called _filepath
	_filepath = filePath;

}

//Function to create histograms
void tempTrender::create_hist(std::vector<double> vector_of_degrees) const{
	TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 100, -30, 35);
	hist->SetFillColor(38); //light blue color
	//adding all elements to histogram
	for (double element : vector_of_degrees){
    	hist->Fill(element);
	}
	double mean = hist->GetMean(); //The mean of the distribution
	double stdev = hist->GetRMS(); //The standard deviation

	hist->GetXaxis()->SetTitle("Temperature [#circC]");
	hist->GetYaxis()->SetTitle("Counts");

	TCanvas* c1 = new TCanvas();

//	hist->Draw();
	
	hist->Fit("gaus", "Q");
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
//Creating a multigraph that will show in one plot 
//the maximum and minimum temperatures over the years
//defining legend for the min and max
auto mg = new TMultiGraph("mg","mg");

void tempTrender::maxTempOverTime()const{
	std::vector<double> max_temps;
	std::string filename = _filepath;
	max_temps = maxTempInYears(filename);
	std::cout << "Plotting Max Temp Over Time... \n\n";

	// Plotting the data
	std::vector<double> years = getYearsList(filename);
//Uncomment this if you want to get a plot of just 	
//the maximum temperatures over the years
	//TCanvas* c2 = new TCanvas();
	int n = years.size();
	auto *gr1 = new TGraph(n, &years[0], &max_temps[0]);
   	gr1->SetTitle("Max Temperatures every year");
	gr1->GetXaxis()->SetTitle("Time [y]");
	gr1->GetYaxis()->SetTitle("Max Temperature [#circC]");
	gr1->SetLineColor(2);
    //gr->SetLineWidth(2); //un-comment if thicker lines are preferred
    gr1->SetMarkerColor(12);
    gr1->SetMarkerStyle(5);
//Uncomment this if you want to get a plot of just 	
//the maximum temperatures over the years
   	//gr1->Draw();

//Command to add this plot to the multigraph
	mg->Add(gr1,"lp");
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
	auto *gr2 = new TGraph(n, &years[0], &min_temps[0]);
   	gr2->SetTitle("Min Temperatures every year");
	gr2->GetXaxis()->SetTitle("Time [y]");
	gr2->GetYaxis()->SetTitle("Min Temperature [#circC]");
	gr2->SetLineColor(4);
    //gr->SetLineWidth(2); //un-comment if thicker lines are preferred
    gr2->SetMarkerColor(12);
    gr2->SetMarkerStyle(5);
   	gr2->Draw();
   	TLegend *leg1 = new TLegend(0.4, 0.55, 0.72, 0.82, "");
   	TLegend *leg2 = new TLegend(0.4, 0.45, 0.72, 0.62, "");
   	leg1->SetFillStyle(0); //Hollow fill (transparent)
	leg1->SetBorderSize(0); //Get rid of the border
	leg2->SetFillStyle(0); //Hollow fill (transparent)
	leg2->SetBorderSize(0); //Get rid of the border
	TLegendEntry *le2 = leg2->AddEntry("gr2", "Min Temperatures" ,"");
	le2->SetTextColor(kBlue);
	TLegendEntry *le1 = leg1->AddEntry("gr1", "Max Temperatures" ,"");
	le1->SetTextColor(kRed);
	
//Command to add this plot to the multigraph
	mg->Add(gr2,"cp");
//Adding title
	mg->SetTitle("Multigraph; Year; Temperatures [#circC]");
//Plotting the multigraph
	mg->Draw("a");
	//leg2->AddEntry(gr2,"");
	leg1->Draw();
	leg2->Draw();	
	
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
	std::vector<string> MaxDaysList = Day_MaxDailyAvgTemp_Year(_filepath);  
	//auto ptr = MaxDaysList.begin();
	//std::cout << *ptr<< std::endl;
	std::vector<string> AllDays = getAllDatums(_filepath);
	std::vector<int> DayNoList{1};
	std::vector<int> DiffList;
	int DayCounter=1;
	auto j=0; //index for MaxDaysList
	auto ptr = MaxDaysList.begin();
	for (std::string i:AllDays) {
		if (i==*(ptr+j)) {
		    auto dptr=DayNoList.end();
			int diff = DayCounter-*(dptr-1); 
			DiffList.push_back(diff);
			DayNoList.push_back(DayCounter);
			j++;
		
		}
		DayCounter++;
	}
// uncomment next two lines to check/print what is in the MaxDaysList vector	
//	for (auto ptr2 = MaxDaysList.begin(); ptr2 != MaxDaysList.end(); ++ptr2) {
//		std::cout << *ptr2 << "," ;}
	
	std::vector<int> x(DiffList.size());
	std::iota(x.begin(), x.end(), start);

//	std::cout << " " <<DiffList.size()<< " " << x.size() << std::endl;
	TCanvas* c5 = new TCanvas();
	TGraph *gr2 = new TGraph(DiffList.size(), &x[0], &DiffList[0]);
   	gr2->SetTitle("max temp time passed diff");
	gr2->GetXaxis()->SetTitle("Time [years passed from first record]");
	gr2->GetYaxis()->SetTitle("#days between yearly max temperature");
	gr2->SetLineColor(6);
    gr2->SetMarkerColor(4);
    gr2->SetMarkerStyle(5);
   	gr2->Draw("ACP");
	
}
