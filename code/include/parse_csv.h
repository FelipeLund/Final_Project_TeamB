#ifndef PARSE_CSV_H
#define PARSE_CSV_H
#include <fast-cpp-csv-parser/csv.h>

void some_func(const int num);

std::vector<double> extract_temp_for_month_day (std::string test_string, std::string& filename);

double maxTempInYear(std::string& filename);


#endif // PARSE_CSV_H