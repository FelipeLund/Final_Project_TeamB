#include "parse_csv1.h"

//parsing the csv file with nuclei list
std::vector<Nucleus> parse_Nucleus(const std::string& filename) {
	io::CSVReader<2> input{filename};
//	input.set_header("Proton", "Neutron");
	int proton{};
	int neutron{};
	std::vector<Nucleus> rows{};
	while(input.read_row(proton, neutron)) {
		rows.push_back(Nucleus{proton, neutron});
	}
	return rows;
}
