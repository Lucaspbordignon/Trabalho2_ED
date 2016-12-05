#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include "man_page.hpp"
#include "word.hpp"
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

std::set<ManPage> search_by_many_words(std::vector<std::string> text_vector) {
	std::set<ManPage> result;

	std::vector<Word> words_vector;
	structures::AVLTree<WordPtr> tree{INVERTED_INDEX_TREE};

	for (auto i = 0u; i < text_vector.size(); ++i) {
		WordPtr wordptr;
		strcpy(wordptr.name, text_vector[i].c_str());
		try {
			Word word_found = Word{tree.find(wordptr)};
			words_vector.push_back(word_found);
		} catch (std::runtime_error &error) {
			return result;
		}
	}

	auto actual_words_set = words_vector.front().find_man_pages();
	for (auto i = words_vector.begin(); i != words_vector.end(); ++i) {
		std::set<ManPage> to_compare = (*i).find_man_pages();

		// Intersection
		auto first_begin = actual_words_set.begin();
		auto first_end = actual_words_set.end();
		auto second_begin = to_compare.begin();
		auto second_end = to_compare.end();
		result.clear();
		while (first_begin != first_end && second_begin != second_end) {
			if (*first_begin < *second_begin) ++first_begin;
			else if (*second_begin < *first_begin) ++second_begin;
			else {
				result.insert(*first_begin);
				++first_begin;
				++second_begin;
			}
		}
		actual_words_set = result;
	}
	return result;
}

#endif
