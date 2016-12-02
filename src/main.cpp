#include <iostream>
#include "index.hpp"
#include "search.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage:\n" << argv[0] << " -i files\n" <<
			argv[0] << " -s command\n" <<
			argv[0] << " -w word(s)\n";
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
		if (argc == 3) {
			// Only one word
			auto man_pages = search_by_word(argv[2]);
			if (man_pages.empty()) {
				std::cout << "No man pages contain '" << argv[2] << "'"
					<< std::endl;
			} else {
				std::cout << "Man pages that contain '" << argv[2] << "':"
					<< std::endl;
				std::cout << man_pages << std::endl;
			}
		} else {
			// Two or more words
			std::vector<std::string> words_to_search;
			for (auto i = 2; i < argc; ++i)
				words_to_search.push_back(argv[i]);
			auto man_pages = search_by_many_words(words_to_search);
			if (man_pages.empty()) {
				std::cout << "No man pages contain these words."
					<< std::endl;
			} else {
				std::cout << "Man pages that contain these words:"
					<< std::endl;
				std::cout << man_pages << std::endl;
			}
		}
	}

	return 0;
}
