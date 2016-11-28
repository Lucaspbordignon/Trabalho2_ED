#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"
#include "word.hpp"
#include "avl_tree.hpp"

// Add a manpage into an existing word. Means that the record already exists
// into the tree.
void add_manpage_to_word(WordPtr& wordptr, std::streampos pos) {
	Word word;
	std::fstream fs{INVERTED_INDEX,
		std::ios::in | std::ios::out | std::ios::binary};

	if (!fs) {
		throw std::runtime_error("add_manpage_to_word(): Couldn't open file");
	}

	fs.seekg(wordptr.pos);
	fs.read((char*) &word, sizeof(Word));
	fs.close();

	word.add(pos);

	fs.seekp(wordptr.pos);
	fs.write((char*) &word, sizeof(Word));
	fs.close();
}

std::streampos add_new_word(Word& word) {
	std::ofstream output{INVERTED_INDEX, std::ios::app | std::ios::binary};

	if (!output) {
		throw std::runtime_error("add_new_word(): Couldn't open file");
	}

	auto position = output.tellp();
	output.write((char*) &word, sizeof(Word));
	output.close();

	return position;
}

void inverted_index() {
	// Creates the tree with the valid words
	structures::AVLTree<WordPtr> word_tree;
	std::cout << "Generating the inverted index file." << std::endl;
	auto already_indexed = 0;

	std::ofstream ofs{INVERTED_INDEX, std::ios::out | std::ios::binary};
	ofs.close();
	std::ifstream all_manpages{MANPAGES, std::ios::in | std::ios::binary};

	if (!all_manpages) {
		throw std::runtime_error("inverted_index(): Couldn't open file");
	}

	std::streampos current_pos;
	ManPage manpage;

	// Reads all the manpages
	while (all_manpages.good()) {
		if (!(already_indexed % 50))
			std::cout << "Manpages indexed: " << already_indexed << std::endl;
		++already_indexed;

		current_pos = all_manpages.tellg();

		all_manpages.read((char*)&manpage, sizeof(ManPage));

		// Set with all valid words of the 'manpage'
		auto wordset = words_into_text(manpage.content);

		for (auto i = wordset.begin(); i != wordset.end(); ++i) {
			WordPtr wordptr, wordptr_node;
			bool found;

			strcpy(wordptr.name, (*i).c_str());

			// Checks if the word is already into the tree
			try {
				wordptr_node = word_tree.find(wordptr);
				found = true;
			} catch (std::runtime_error &error) {
				found = false;
			}

			if (found) {
				add_manpage_to_word(wordptr_node, current_pos);
			} else {
				Word word;
				strcpy(word.name, (*i).c_str());
				word.add(current_pos);
				wordptr.pos = add_new_word(word);
				word_tree.insert(wordptr);
			}
		}
	}
	all_manpages.close();
	word_tree.save_on_file(INVERTED_INDEX_TREE);
	std::cout << "Done." << std::endl;
}

void index_man_pages() {
	auto files_names = split(exec("ls " + MPPATH), "\n");
	std::cout << files_names.size() << " man pages being indexed\n";

	std::ofstream ofs{MANPAGES};

	if (!ofs) {
		throw std::runtime_error("void index_man_pages() :\
Couldn't open file " + MANPAGES);
	}

	structures::AVLTree<ManPageRecord> mptree;

	ManPage mp;
	ManPageRecord mpr;

	for (auto i = files_names.begin(); i != files_names.end(); ++i) {
		mp = ManPage{MPPATH + *i};

		strcpy(mpr.name, mp.name);
		mpr.position = ofs.tellp();

		ofs.write((char*) &mp, sizeof(ManPage));

		mptree.insert(mpr);
	}

	ofs.close();

	mptree.save_on_file(MPTREE);
	std::cout << "Done." << std::endl;
}

#endif
