#include "index.hpp"
#include "search.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argv[1])
		index_man_pages();
	std::cout << search_by_name(argv[2]).content << std::endl;
	return 0;
}
