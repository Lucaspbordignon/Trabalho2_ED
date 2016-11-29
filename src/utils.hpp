#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <memory>
#include <set>
#include <algorithm>

/**
 * @brief Reads a whole file to a std::string
 * @param filename Path to the file that'll be readed
 */
std::string read_file(const std::string& filename);

/**
 * @brief Splits a std::string into a std::set
 * @details For example split("aaa/b/ce", "/") returns {"aaa", "b", "ce"}
 *
 * @param str The string that'll be splitted
 * @param c The char where the string will be splitted
 */
std::set<std::string> split(const std::string& str, const char* c);

/**
 * @brief Overloads the << operator for std::vector for printing
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "{";
	auto it = v.begin();
	for (; it != v.end() - 1; ++it) {
		os << *it << ", ";
	}
	os << *it << "}";
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
	for (auto it = s.begin(); it != s.end(); ++it) {
		os << *it << " ";
	}
	return os;
}

/**
 * @brief A basic progress bar is shown
 * @details Every time you call, it'll overwrite the previously shown bar.
 *
 * @param percentage A number from 0 to 1, representing the percentage of the
 * bar that'll be filled
 */
void show_progress(float percentage);

void replace_chars(std::string&, const std::string&, const char);
bool check_word(std::string);
std::set<std::string> words_into_text(std::string);

const std::string special_chars = "\n\r\t,.;\"'!@#$%%^&*()[]{}+-/<>?\\`~_:|0123456789";
const std::vector<std::string> connection_words = {
	"and", "that", "but", "or", "as", "if", "when", "than", "because",
	"while", "where", "after", "so", "though", "since", "until",
	"whether", "before", "although", "nor", "like", "once", "unless",
	"now", "except", "<->", "a", "the", "of", "to", "into", "by",
	"for", "on", "at", "in", "next", "then", "more", "only", "always",
	"never", "all", "off", "with", "this"
};

#endif
