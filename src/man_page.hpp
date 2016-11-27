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

struct Word {
	char word[50];

	unsigned int index = 0;

	std::streampos pos[5650];

	void add(std::streampos _pos) {
		pos[index] = _pos;
		++index;
	}

	inline bool operator<(const Word& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	inline bool operator>(const Word& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	inline bool operator==(const Word& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}

	inline bool operator!=(const Word& rhs) const {
		return !(*this == rhs);
	}
};

struct WordPtr {
	char word[50];
	std::streampos pos = 0;

	inline bool operator<(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) < 0;
	}

	inline bool operator>(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) > 0;
	}

	inline bool operator==(const WordPtr& rhs) const {
		return strcmp(word, rhs.word) == 0;
	}

	inline bool operator!=(const WordPtr& rhs) const {
		return !(*this == rhs);
	}
};

std::ostream& operator<<(std::ostream&, const ManPage&);
std::ostream& operator<<(std::ostream&, const ManPageRecord&);

#endif
