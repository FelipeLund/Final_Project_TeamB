#include "parse_csv.h"
#include <string>
#include <iostream>

//parsing the csv file with nuclei list

void some_func(const int num){
    std::cout << "some_func_called to print " << num << "\n"; 
}

std::vector<double> extract_temp_for_month_day (std::string test_string, std::string& filename){
    
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


