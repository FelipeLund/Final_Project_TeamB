#ifndef PARSE_CSV_H
#define PARSE_CSV_H
#include <fast-cpp-csv-parser/csv.h>

void some_func(const int num);

std::vector<double> extract_temp_for_month_day (const std::string test_string, const std::string& filename);

std::vector<double> maxTempInYears(std::string& filename);

std::vector<int> max_temp_positions(const std::string& filename);

std::vector<double> getYearsList(const std::string& filename);

std::vector<std::string> getAllDatums(const std::string& filename);

std::vector<double> getDailyTempOverTime(const std::string& filename);


#endif // PARSE_CSV_H
