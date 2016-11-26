#ifndef MAN_PAGES_HPP
#define MAN_PAGES_HPP

#include <cstring>
#include <iostream>
#include "utils.hpp"

struct ManPage {
	char name[50];
	char content[139715];  // biggest man page

	ManPage() = default;

	explicit ManPage(std::string filename) {
		auto str = read_file(filename);

		auto begin = str.find_first_of("\n") + 1;
		// find first space OR comma
		auto end = str.find_first_of(" ,", begin) - begin;

		strcpy(name, str.substr(begin, end).c_str());
		strcpy(content, str.c_str());
	}
};

std::ostream& operator<<(std::ostream& os, const ManPage& mp) {
	os << mp.name;
	return os;
}

struct ManPageRecord {
	char name[50];
	std::streampos position;  // position in man_pages.dat

	inline bool operator<(const ManPageRecord& rhs) const {
		return strcmp(name, rhs.name) < 0;
	}

	inline bool operator>(const ManPageRecord& rhs) const {
		return strcmp(name, rhs.name) > 0;
	}

	inline bool operator==(const ManPageRecord& rhs) const {
		return strcmp(name, rhs.name) == 0;
	}

	inline bool operator!=(const ManPageRecord& rhs) const {
		return !(*this == rhs);
	}
};

std::ostream& operator<<(std::ostream& os, const ManPageRecord& mpr) {
	os << mpr.name;
	return os;
}

#endif
