#include "parse_csv.h"
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>

void some_func(const int num){
    std::cout << "some_func_called to print " << num << "\n"; 
}

std::vector<double> extract_temp_for_month_day (const std::string test_string, const std::string& filename){
    
    // Creating empty vector and opening csv file
    std::vector<double> info_vector;
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

	//Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;
	
	// Pushing to info vector
	while(in.read_row(datum, tid, temp, quality)){
		if (datum.substr(5, 5) == test_string){
			info_vector.push_back(temp);
		};

	};

    return info_vector;
}

std::vector<double> getYearsList(const std::string& filename){
    std::vector<double> years_vector;

    // Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");
    

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;

	// Pushing to info vector
	while(in.read_row(datum, tid, temp, quality)){
		years_vector.push_back(stoi(datum.substr(0,4)));
	};

    // Removing duplicates
    auto last = std::unique(years_vector.begin(), years_vector.end());
    years_vector.erase(last, years_vector.end());

    return years_vector;
}


std::vector<double> maxTempInYears(std::string& filename){
    std::vector<double> max_temp_vector;
    std::vector<double> years = getYearsList(filename);

    // Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;


    // For each year, append all temps to a vector called temps, find the max of temps
    // Append the max of temps to max_temp_vector
    for (int year : years){
        std::vector<double> temps; 
        while(in.read_row(datum, tid, temp, quality)){
            
            if (stoi(datum.substr(0,4)) == year){
				temps.push_back(temp);
            }
			if (stoi(datum.substr(0,4)) != year){  
	            break;
			}
		}
		auto max = *max_element(std::begin(temps), std::end(temps));
        max_temp_vector.push_back(max);
    }

    return max_temp_vector;
}


//Code for finding the minimun temperature of the years
	std::vector<double> minTempInYears(std::string& filename){
    std::vector<double> min_temp_vector;
    std::vector<double> years = getYearsList(filename);

    // Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;

//Have to decide if we are plotting only the hottest or both the hottest and coldest temperatures over the years
    // For each year, append all temps to a vector called temps, find the min of temps
    // Append the min of temps to min_temp_vector
    for (int year : years){
        std::vector<double> temps; 
        while(in.read_row(datum, tid, temp, quality)){
            
            if (stoi(datum.substr(0,4)) == year){
				temps.push_back(temp);
            };
			if (stoi(datum.substr(0,4)) != year){  
            break;}
		};
		auto min = *min_element(std::begin(temps), std::end(temps));
        min_temp_vector.push_back(min);
    };

    return min_temp_vector;
}

std::vector<std::string> getAllDatums(const std::string& filename){
    // Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;


    // Storing all datums in a vector
    std::vector<std::string> all_datums;
    while(in.read_row(datum, tid, temp, quality)){
        all_datums.push_back(datum);
    }

    // Removing duplicates
    auto last = std::unique(all_datums.begin(), all_datums.end());
    all_datums.erase(last, all_datums.end());

    return all_datums;
}

using namespace std;
 
// Function to get the index of an double type element (in this project, the temperature) from a vector
int getIndexOfTemp(std::vector<double> v, double K){
    int j=0;
    int index;
    for (double i:v) {
		if (i==K){
			index=j;
			//std::cout<<index;
			return index;
			break;}
		j++;}
	return 0;	
    }



std::vector<double> getDailyTempOverTime(const std::string& filename){
    // Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;

    // Creating vectors to be used
    std::vector<double> dailyTempOverTime;
    std::vector<std::string> all_datums = getAllDatums(filename);
    int n = all_datums.size();
    std::string last_datum = all_datums[n - 1];

    for (std::string day : all_datums){
        if (day == last_datum){break;}
        in.read_row(datum, tid, temp, quality);
        std::vector<double> day_temp;
        while (day == datum){
            in.read_row(datum, tid, temp, quality);
            //std::cout << datum << "\n";
            day_temp.push_back(temp);
        }
        double average = accumulate(day_temp.begin(), day_temp.end(), 0.0) / day_temp.size();
        dailyTempOverTime.push_back(average);
    }

    return dailyTempOverTime;
}


// Function that gets day for max daily average temperature for every year
std::vector<std::string> Day_MaxDailyAvgTemp_Year(const std::string& filename){
//if you want the max avg daily temperatures per year instead, use function call below and return max_avg_dailytemp_vector   
//std::vector<double> Day_MaxDailyAvgTemp_Year(const std::string& filename){

	// Opening file and specifying variables for columns
	io::CSVReader<4> in(filename);
	in.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    //Specifying variables in each column
	std::string datum{}; std::string tid{};
	std::string quality{}; double temp;
	
	std::vector<double> max_avg_dailytemp_vector;
	
    std::vector<double> years = getYearsList(filename);
    
    std::vector<std::string> Day_MaxAvgTemp_Year;
	in.read_row(datum, tid, temp, quality);
	std::string date = datum;
	
	// loop through each year
	for (double year:years) {
			std::vector<double> AvgDailyTempsYear;
			std::vector<std::string> days{};
			days.push_back(date);
			
			std::vector<double> DailyTemps;
			
			// read through file
			while(in.read_row(datum, tid, temp, quality)){
				//see if reading current
				if (year != stoi(datum.substr(0,4)))
					{date=datum;
					break;}
				if (year == stoi(datum.substr(0,4))){			
					// for current year, check the date, store the temperature per day in a vector
					if (date==datum){
						DailyTemps.push_back(temp);
					}
					// if date changes, find the average for previous day and store in another vector
					if (date!=datum){
						double average = accumulate(DailyTemps.begin(), DailyTemps.end(), 0.0) / (DailyTemps.size());
						AvgDailyTempsYear.push_back(average);
						days.push_back(date);
						date=datum;//update date
						std::vector<double> DailyTemps; //make new DailyTemps vector
					}	
				}				
			}
			//find the max average temperature for current year and store in vector
			auto max = *max_element(std::begin(AvgDailyTempsYear), std::end(AvgDailyTempsYear));
	       	max_avg_dailytemp_vector.push_back(max);	
        	
        	//find the index of the max temp found and use it to find the day for it
        	int index_max = getIndexOfTemp(AvgDailyTempsYear, max);     
        	std::string & day_max = days[index_max];   	
           	Day_MaxAvgTemp_Year.push_back(day_max);  //store the day for the max avg temp for that year
        	      	     	
		}
		//return max_avg_dailytemp_vector;	// use this if the max temperature vector is desired instead of the day vector
		return Day_MaxAvgTemp_Year;	
	}


