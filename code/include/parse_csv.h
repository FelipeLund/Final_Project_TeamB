#ifndef PARSE_CSV_H
#define PARSE_CSV_H
#include <fast-cpp-csv-parser/csv.h>


std::vector<double> extract_temp_for_month_day (const std::string test_string, const std::string& filename);

std::vector<double> maxTempInYears(std::string& filename);

std::vector<double> getYearsList(const std::string& filename);

std::vector<double> minTempInYears(std::string& filename);

std::vector<std::string> getAllDatums(const std::string& filename);

std::vector<double> getDailyTempOverTime(const std::string& filename);

int getIndexOfTemp(std::vector<double> v, double K);

std::vector<std::string> Day_MaxDailyAvgTemp_Year(const std::string& filename);
//std::vector<double> Day_MaxDailyAvgTemp_Year(const std::string& filename);//use this to get max temperature vector instead of the days

#endif // PARSE_CSV_H
