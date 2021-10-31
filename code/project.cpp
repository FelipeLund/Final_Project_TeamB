#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>



int main() {
	std::string pathToFile; //path to data file

	//Interface and interactive
	std::cout << "\n-------------------- Welcome! --------------------\n";
	std::cout << "This program will: \n";
	std::cout << "(1) Print a histogram of temperatures on a specific day through time. \n(2) Show a plot of the maximum temperature each year. \n(3) Show a plot of the mean temperature on every day throughout time.\n\n";

	std::cout << "First, enter the path of a clean data file (e.g. ./ClnData/CleanLund.csv): ";
	std::cin >> pathToFile;
	
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	std::cout << "Now, enter a month and day for which you want to see a histogram of temperatures through time (mm dd): ";

	int mm, dd;
	std::cin >> mm >> dd;
	

	t.tempOnDay(mm, dd);
	t.maxTempOverTime();
	t.dailyTempOverTime();

	return 0;	
}
