#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <memory>
#include <unistd.h>
#include <algorithm>
#include <set>

std::string read_file(std::string filename);

// executes a linux command
std::string exec(const std::string cmd);

std::vector<std::string> split(std::string str, const char* c);

template<typename T>
void print_vector(std::vector<T> v);
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
