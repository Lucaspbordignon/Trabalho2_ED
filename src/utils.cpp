#include "utils.hpp"

std::string read_file(std::string filename) {
	std::ifstream ifs{filename};

	if (!ifs) {
		throw std::runtime_error("std::string read_file(std::string) : \
Couldn't open file " + filename);
	}

	std::string content{std::istreambuf_iterator<char>(ifs),
		std::istreambuf_iterator<char>()};
	return content;
}

// executes a linux command
std::string exec(const std::string cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("exec: popen() failed!");
	}

	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}

	return result;
}

std::vector<std::string> split(std::string str, const char* c) {
	std::vector<std::string> output;

	std::size_t begin = 0;
	auto end = str.find_first_of(c);

	while (begin < str.length()) {
		output.push_back(str.substr(begin, end - begin));
		begin = end + 1;
		end = str.find_first_of(c, begin);
	}

	return output;
}

template<typename T>
void print_vector(std::vector<T> v) {
	std::copy(v.begin(), v.end(),
			std::ostream_iterator<T>(std::cout, ", "));
}

const std::vector<std::string> connection_words = {
	"and", "that", "but", "or", "as", "if", "when", "than", "because",
	"while", "where", "after", "so", "though", "since", "until",
	"whether", "before", "although", "nor", "like", "once", "unless",
   	"now", "except", "<->", "a", "the", "of", "to", "into", "by",
	"for", "on", "at", "in", "next", "then", "more", "only", "always",
	"never", "all", "off", "with", "this"
};

void replace_chars(std::string& str, const std::string& to_replace, const char by) {
	for (auto i = to_replace.begin(); i != to_replace.end(); ++i) {
		std::replace(str.begin(), str.end(), *i, by);
	}
}

bool check_word(std::string str) {
	auto found = find(connection_words.begin(), connection_words.end(), str) != connection_words.end();
	return !found && (str.size() > 2);
}

const std::string SPECIAL_CHARS = "\n\r\t,.;\"'!@#$%%^&*()[]{}+-/<>?\\`~_:|0123456789";

std::set<std::string> words_into_text(std::string text) {
	std::set<std::string> valid;

	std::transform(text.begin(), text.end(), text.begin(), ::tolower);

	replace_chars(text, SPECIAL_CHARS, ' ');

	auto wordvec = split(text, " ");

	for (auto i = wordvec.begin(); i != wordvec.end(); ++i) {
		if (check_word(*i)) {
			valid.insert(*i);
		}
	}

	return valid;
}
