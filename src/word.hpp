#ifndef WORD_HPP
#define WORD_HPP

#include <cstring>
#include <set>
#include <fstream>
#include "man_page.hpp"

struct WordPtr {
	char name[50];
	std::streampos pos = 0;

	void add_manpage_to_word(const std::streampos&) const;

	inline bool operator<(const WordPtr& rhs) const {
		return strcmp(name, rhs.name) < 0;
	}

	inline bool operator>(const WordPtr& rhs) const {
		return strcmp(name, rhs.name) > 0;
	}

	inline bool operator==(const WordPtr& rhs) const {
		return strcmp(name, rhs.name) == 0;
	}

	inline bool operator!=(const WordPtr& rhs) const {
		return !(*this == rhs);
	}
};

struct Word {
	char name[50];
	std::size_t index = 0u;
	std::streampos pos[5642];

	Word() = default;

	explicit Word(const WordPtr& wp);

	void add(std::streampos _pos);

	std::set<ManPage> find_man_pages() const;

	std::streampos save() const;
};

#endif
