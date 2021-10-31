#include "parse_csv.h"
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <numeric>

//parsing the csv file with nuclei list

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
    // NOTE: it will miss the last year!!!!
    for (int year : years){
        std::vector<double> temps; 
        while(in.read_row(datum, tid, temp, quality)){
            
            if (stoi(datum.substr(0,4)) == year){
				temps.push_back(temp);
            };
			if (stoi(datum.substr(0,4)) != year){  
            break;}
		};
		auto max = *max_element(std::begin(temps), std::end(temps));
        max_temp_vector.push_back(max);
    };

    return max_temp_vector;
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
            in.read_row(datum,tid, temp, quality);
            //std::cout << datum << "\n";
            day_temp.push_back(temp);
        }
        double average = accumulate(day_temp.begin(), day_temp.end(), 0.0) / day_temp.size();
        dailyTempOverTime.push_back(average);
    }

    return dailyTempOverTime;
}
