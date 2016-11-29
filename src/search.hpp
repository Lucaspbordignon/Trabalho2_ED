#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include "man_page.hpp"
#include "paths.hpp"
#include "avl_tree.hpp"

ManPage search_by_name(const char* mp_name) {
	ManPageRecord mpr;
	strcpy(mpr.name, mp_name);
	structures::AVLTree<ManPageRecord> mptree{MPTREE};
	return ManPage{mptree.find(mpr)};
}

std::set<ManPage> search_by_word(std::string text) {
	structures::AVLTree<WordPtr> tree{INVERTED_INDEX_TREE};
	WordPtr wordptr;

	// Transform to lowercase
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	strcpy(wordptr.name, text.c_str());

	Word word;

	try {
		word = Word{tree.find(wordptr)};
	} catch (std::runtime_error &error) {}

	return word.find_man_pages();
}

#endif
