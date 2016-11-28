#ifndef WORD_HPP
#define WORD_HPP

struct Word {
	char name[50];
	std::size_t index = 0u;
	std::streampos pos[5650];

	void add(std::streampos _pos) {
		pos[index] = _pos;
		++index;
	}
};

struct WordPtr {
	char name[50];
	std::streampos pos = 0;

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

#endif
