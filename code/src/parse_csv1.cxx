#include "parse_csv1.h"

//parsing the csv file with nuclei list

std::vector<string> parse_smhi(const std::string& filename) {
	io::CSVReader<4> input{filename};
	input.set_header("Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet" );
	std::string Datum{};
	std::string Tid{};
	double LuftTemp{};
	double Kvalitet{};
	
	std::vector<string> rows{};
	while(input.read_row(Datum, Tid, LuftTemp, Kvalitet)) {
		rows.push_back();
	}
	return rows;
}
