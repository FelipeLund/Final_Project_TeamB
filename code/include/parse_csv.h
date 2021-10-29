#ifndef PARSE_CSV_H
#define PARSE_CSV_H
#include <fast-cpp-csv-parser/csv.h>

void some_func(const int num);

std::vector<double> extract_temp_for_month_day (std::string test_string, std::string& filename);

std::vector<double> maxTempInYears(std::string& filename);

std::vector<int> getYearsList(const std::string& filename);

double avgTempInDay(int day_number,const std::string& filename);

std::vector<std::string> getAllDatums(const std::string& filename);


#endif // PARSE_CSV_H