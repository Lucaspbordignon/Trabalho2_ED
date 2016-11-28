#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include "man_page.hpp"
#include "paths.hpp"
#include "avl_tree.hpp"

ManPage search_by_name(std::string mp_name) {
	ManPageRecord mpr;
	strcpy(mpr.name, mp_name.c_str());
	structures::AVLTree<ManPageRecord> mptree{MPTREE};
	return ManPage{mptree.find(mpr)};
}

void search_by_word(std::string text) {
	structures::AVLTree<WordPtr> tree{INVERTED_INDEX_TREE};
	WordPtr wordptr, wordptr_node;

	// Transform to lowercase
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	strcpy(wordptr.name, text.c_str());

	try {
		wordptr_node = tree.find(wordptr);
	} catch (std::runtime_error &error) {
		std::cout << "Word '" << text << "' not found." << std::endl;
		return;
	}

	std::ifstream input{INVERTED_INDEX};
	if (!input) {
		throw std::runtime_error("search_by_word(): Couldn't open file");
	}

	Word word;
	input.seekg(wordptr_node.pos);
	input.read((char*)&word, sizeof(Word));
	input.close();

	std::ifstream all_manpages(MANPAGES, std::ios::in | std::ios::binary);
	for (auto i = 0; i <= word.index; ++i) {
		ManPage mp;
		all_manpages.seekg(word.pos[i]);
		all_manpages.read((char*)&mp, sizeof(ManPage));
		std::cout << "Command: " << mp.name << std::endl;
	}
	all_manpages.close();


	std::cout << word.index << " manpages have this word." << std::endl;
	tree.save_on_file(INVERTED_INDEX_TREE);
}

#endif
