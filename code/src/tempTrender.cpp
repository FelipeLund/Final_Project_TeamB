#include <iostream>
#include <string>
#include "tempTrender.h"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	//std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
	std::cout << "filepath is stored in member variable called _filepath \n";
	_filepath = filePath;
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const{
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

	// Printing to make sure things work
	std::cout << "First element of info_vector "<< info_vector[0] << "\n";
	std::cout << "Now we start making the hist... \n";
}


void tempTrender::maxTempOverTime()const {
	std::cout << "Max Temp Over Time starting... \n";
}


// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
