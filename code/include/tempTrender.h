#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include "parse_csv.h"

// Root canvas includes 
#include <TH1F.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>

class tempTrender {
	public:
		std::string _filepath;
	explicit tempTrender(const std::string& filePath); //Construct using the specified file
	~tempTrender() {} //Destructor


	// Make a histogram of the temperature on this day
	void tempOnDay(int monthToCalculate, int dayToCalculate) const; 

	void maxTempOverTime() const;

	void dailyTempOverTime() const;

	//Function to create hisotgrams
	void create_hist(std::vector<double> vector_of_degrees) const;
	


	private:
	
};
#endif
