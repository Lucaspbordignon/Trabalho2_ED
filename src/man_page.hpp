#ifndef MAN_PAGES_HPP
#define MAN_PAGES_HPP

#include <cstring>
#include <iostream>

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

struct ManPage {
	char name[50];
	char content[139715];  // biggest man page

	ManPage() = default;

	explicit ManPage(std::string);
	explicit ManPage(const ManPageRecord&);
};

std::ostream& operator<<(std::ostream&, const ManPage&);
std::ostream& operator<<(std::ostream&, const ManPageRecord&);

#endif
