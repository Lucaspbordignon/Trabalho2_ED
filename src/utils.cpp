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

std::vector<std::string> split(const std::string& str, const char* c) {
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
