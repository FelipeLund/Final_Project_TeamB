#include <iostream>
#include <string>
#include "tempTrender.h"
#include "parse_csv.h"
#include "csv.hpp"

tempTrender::tempTrender(const std::string& filePath) {
	std::cout << "The user supplied " << filePath <<" as the path to the data file.\n";
	std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";
	_filepath = filePath;
}

/*
reading the csv{
	...
	...
	...
	return std::string date;
}

*/
std::string date = "1945-12-28"; //test string
//converting date data to integers
int year = std::stoi(date.substr(0,4));
int month = std::stoi(date.substr(5,2));
int day = std::stoi(date.substr(8,2))

//controling funtion
std::cout << date << "splitted" << day << month << year << std::endl;


void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const {
	//std::cout << _filepath << "\n";
	//std::cout << "Month: " << monthToCalculate << "\n";
	//std::cout << "Day: " << dayToCalculate << "\n";
	//io::CSVReader<3> in(_filepath);
	//in.read_header(io::ignore_extra_column, "Date", "Time", "Temp", "Quality");
	//LineReader file (char* _filepath);
	//while(char* line = in.next_line()){
	//std::cout<< line << "\n"
	}

//Make a histogram of the temperature on this day
void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const {
	//for (){}
 	}

// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
