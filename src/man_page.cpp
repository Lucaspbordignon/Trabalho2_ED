#include "man_page.hpp"
#include "utils.hpp"
#include "paths.hpp"

/**
 * @brief Creates the ManPage object from a file (.txt)
 */
ManPage::ManPage(const std::string& filename) {
	auto str = read_file(filename);
	strcpy(content, str.c_str());

	auto begin = filename.find_last_of("/") + 1;
	auto end = filename.find_last_of(".") - begin;
	strcpy(name, filename.substr(begin, end).c_str());
}

/**
 * @brief Loads a previously saved ManPage object
 */
ManPage::ManPage(const ManPageRecord& mpr) {
	std::ifstream ifs{MANPAGES, std::ifstream::binary};

	if (!ifs) {
		throw std::runtime_error("ManPage::ManPage(ManPageRecord) : "
				"Couldn't open file " + MANPAGES);
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
