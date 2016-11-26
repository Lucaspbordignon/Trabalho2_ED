#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"

void index_man_pages() {
	auto files_names = split(exec("ls " + PATH), "\n");
	std::cout << files_names.size() << " man pages\n";
	std::ofstream ofs{MANPAGES};

	if (!ofs) {
		throw std::runtime_error("void index_man_pages() :\
Couldn't open file " + MANPAGES);
	}

	ManPage mp;

	for (auto i = files_names.begin(); i != files_names.end(); ++i) {
		mp = ManPage{PATH + *i};

		ofs.write((char*) &mp, sizeof(ManPage));
	}

	ofs.close();
}

#endif
