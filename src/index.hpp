#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"
#include "avl_tree.hpp"

void index_man_pages(std::vector<std::string> files_names) {
	std::cout << files_names.size() << " man pages being indexed\n";

	std::ofstream ofs{MANPAGES};

	if (!ofs) {
		throw std::runtime_error("void index_man_pages() :\
Couldn't open file " + MANPAGES);
	}

	structures::AVLTree<ManPageRecord> mptree;

	ManPage mp;
	ManPageRecord mpr;

	for (auto i = files_names.begin(); i != files_names.end(); ++i) {
		mp = ManPage{MPPATH + *i};

		strcpy(mpr.name, mp.name);
		mpr.position = ofs.tellp();

		ofs.write((char*) &mp, sizeof(ManPage));

		mptree.insert(mpr);
	}

	ofs.close();

	mptree.save_on_file(MPTREE);
}

#endif
