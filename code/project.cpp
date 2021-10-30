#include "tempTrender.h"
#include "parse_csv.h"
#include <string>
#include <iostream>



int main() {
	const std::string pathToFile = "./ClnData/CleanLund.csv"; //path to data file

	tempTrender t(pathToFile); //Instantiate your analysis object
	t.tempOnDay(12, 15);
	t.maxTempOverTime();
	t.dailyTempOverTime();

	return 0;	
}
