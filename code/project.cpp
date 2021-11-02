#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>



void project() {
	std::string pathToFile; //path to data file

	//Interface and interactive
	std::cout << "\n-------------------- Welcome! --------------------\n";
	std::cout << "This program will: \n";
	std::cout << "(1) Print a histogram of temperatures on a specific day through time. \n(2) Show 2 separates plots of the maximum and minimum temperatures each year. \n(3) Show a plot of the mean temperature on every day throughout time.\n\n";

	std::cout << "First, enter the path of a clean data file (e.g. ./ClnData/CleanLund.csv): ";
	std::cin >> pathToFile;
	
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	std::cout << "Now, enter a month and day for which you want to see a histogram of temperatures through time (mm dd): ";

	int mm, dd;
	std::cin >> mm >> dd;
	
	// Creating the histogram for specified date
	t.tempOnDay(mm, dd);

	// Plotting the maximum teperature for each year
	t.maxTempOverTime();

	//Plotting the minimum temperature for each year
	//this will create the histogram for the coldest days over the years. 
	t.minTempOverYears();

	// Plotting daily temperature over time
	t.dailyTempOverTime();

	std::cout << "---------------------- Done! ----------------------\n";

}
