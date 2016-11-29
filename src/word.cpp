#include "word.hpp"
#include "paths.hpp"

Word::Word(const WordPtr& wp) {
	std::ifstream input{INVERTED_INDEX, std::ios::in | std::ios::binary};

	if (!input) {
		throw std::runtime_error("Word::Word(const WordPtr&) : "
				"Couldn't open file " + INVERTED_INDEX);
	}

	input.seekg(wp.pos);
	input.read((char*)this, sizeof(Word));
	input.close();
}

void Word::add(std::streampos _pos) {
	pos[index] = _pos;
	++index;
}

std::set<ManPage> Word::find_man_pages() const {
	std::ifstream all_manpages(MANPAGES, std::ios::in | std::ios::binary);
	std::set<ManPage> output;

	ManPage mp;
	for (auto i = 0u; i < index; ++i) {
		all_manpages.seekg(pos[i]);
		all_manpages.read((char*)&mp, sizeof(ManPage));
		output.insert(mp);
	}

	all_manpages.close();

	return output;
}

// Add a manpage into an existing word. Means that the record already exists
// into the tree.
void WordPtr::add_manpage_to_word(const std::streampos& mp_position) const {
	std::fstream fs{INVERTED_INDEX,
		std::ios::in | std::ios::out | std::ios::binary};

	if (!fs) {
		throw std::runtime_error("add_manpage_to_word(): Couldn't open file");
	}

	Word word;

	fs.seekg(pos);
	fs.read((char*) &word, sizeof(Word));

	word.add(mp_position);

	fs.seekp(pos);
	fs.write((char*) &word, sizeof(Word));

	fs.close();
}
