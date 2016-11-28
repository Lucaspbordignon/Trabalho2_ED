#include "index.hpp"
#include "search.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage:\n" << argv[0] << " -i files\n" <<
			argv[0] << " -s command\n";
	} else if (strcmp(argv[1], "-i") == 0) {
		std::vector<std::string> files;
		for (int i = 2; i < argc; ++i) {
			files.push_back(argv[i]);
		}
		index_man_pages(files);
		inverted_index();
	} else if (strcmp(argv[1], "-s") == 0) {
		try {
			std::cout << "Command " << search_by_name(argv[2]) << " found"
				<< std::endl;
		} catch(std::runtime_error e) {
			std::cout << "Command " << argv[2] << " not found" << std::endl;
		}
	} else if (strcmp(argv[1], "-w") == 0) {
		search_by_word(argv[2]);
	}
	return 0;
}
