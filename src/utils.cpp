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
