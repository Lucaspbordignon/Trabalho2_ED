#include "utils.hpp"
#define barWidth 70

std::string read_file(const std::string& filename) {
	std::ifstream ifs{filename};

	if (!ifs) {
		throw std::runtime_error("std::string read_file(std::string) : "
				"Couldn't open file " + filename);
	}

	return std::string{std::istreambuf_iterator<char>(ifs),
		std::istreambuf_iterator<char>()};
}

std::set<std::string> split(const std::string& str, const char* c) {
	std::set<std::string> output;

	std::size_t begin = 0;
	auto end = str.find_first_of(c);

	while (end != std::string::npos) {
		if (end - begin)
			output.insert(str.substr(begin, end - begin));
		begin = end + 1;
		end = str.find_first_of(c, begin);
	}

	if (str.length() - begin) {
		output.insert(str.substr(begin, str.length() - begin));
	}

	return output;
}

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

void show_progress(const float percentage) {
	if (percentage <= 1) {
		std::cout << "[";
		int pos = barWidth * percentage;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "#";
			else std::cout << "-";
		}
		std::cout << "] " << int(percentage * 100.0) << " %\r";
		std::cout.flush();
		if (percentage == 1) {
			std::cout << std::endl;
		}
	}
}

void replace_chars(std::string& str, const std::string& to_replace, const char by) {
	for (auto i = to_replace.begin(); i != to_replace.end(); ++i)
		std::replace(str.begin(), str.end(), *i, by);
}

bool check_word(std::string str) {
	auto found = find(connection_words.begin(), connection_words.end(), str) != connection_words.end();
	return !found && (str.size() > 2);
}

std::set<std::string> words_into_text(std::string text) {
	std::set<std::string> valid_words;

	// Transform the 'text' to lowercase
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);

	// Replaces all the special characters with spaces, for 'split'.
	replace_chars(text, special_chars, ' ');

	auto wordvec = split(text, " ");

	for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
		if (check_word(*i))
			valid_words.insert(*i);
	}
	return valid_words;
}
