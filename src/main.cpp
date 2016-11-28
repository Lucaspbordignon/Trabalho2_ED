#include "index.hpp"
#include "search.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (strcmp(argv[1], "index") == 0) {
		index_man_pages();
		inverted_index();
	} else if (strcmp(argv[1], "word") == 0) {
		search_by_word(argv[2]);
	} else {
		std::cout << search_by_name(argv[1]).content << std::endl;
	}
	return 0;
}
