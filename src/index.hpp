#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"
#include "avl_tree.hpp"

void index_man_pages(std::vector<std::string> files_names) {
	auto n = files_names.size();
	std::cout << n << " man pages being indexed\n";

	std::remove(MANPAGES.c_str());
	std::ofstream ofs{MANPAGES};

	if (!ofs) {
		throw std::runtime_error("void index_man_pages() :\
Couldn't open file " + MANPAGES);
	}

	structures::AVLTree<ManPageRecord> mptree;

	ManPage mp;
	ManPageRecord mpr;

	std::cout << "Reading man pages and saving to " << MANPAGES << std::endl;

	for (auto i = 0u; i < n; ++i) {
		show_progress(((float)i+1)/((float)n));

		mp = ManPage{files_names[i]};

		strcpy(mpr.name, mp.name);
		mpr.position = ofs.tellp();

		ofs.write((char*) &mp, sizeof(ManPage));

		mptree.insert(mpr);
	}

	ofs.close();

	std::cout << std::endl << "Saving inverted tree to " << MPTREE << std::endl;
	mptree.save_on_file(MPTREE);
}

#endif
