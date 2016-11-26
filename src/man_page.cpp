#include "man_page.hpp"
#include "utils.hpp"
#include "paths.hpp"

ManPage::ManPage(std::string filename) {
	auto str = read_file(filename);

	auto begin = str.find_first_of("\n") + 1;
	// find first space OR comma
	auto end = str.find_first_of(" ,", begin) - begin;

	strcpy(name, str.substr(begin, end).c_str());
	strcpy(content, str.c_str());
}

ManPage::ManPage(const ManPageRecord& mpr) {
	std::ifstream ifs{MANPAGES};

	if (!ifs) {
		throw std::runtime_error("ManPage::ManPage(ManPageRecord) :\
Couldn't open file " + MANPAGES);
	}

	ifs.seekg(mpr.position);
	ifs.read((char*) this, sizeof(ManPage));
	ifs.close();
}

std::ostream& operator<<(std::ostream& os, const ManPage& mp) {
	os << mp.name;
	return os;
}

std::ostream& operator<<(std::ostream& os, const ManPageRecord& mpr) {
	os << mpr.name;
	return os;
}
