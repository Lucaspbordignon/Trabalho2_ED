#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"
#include "word.hpp"
#include "avl_tree.hpp"

void inverted_index() {
	// Creates the tree with the valid words
	std::cout << "Generating the inverted index file." << std::endl;

	std::remove(INVERTED_INDEX.c_str());

	structures::AVLTree<WordPtr> word_tree;

	std::ifstream all_manpages{MANPAGES, std::ios::in | std::ios::binary};

	if (!all_manpages) {
		throw std::runtime_error("inverted_index(): Couldn't open file");
	}

	ManPage manpage;

	auto i = 0u;

	// Reads all the manpages
	for (auto current_pos = all_manpages.tellg();
			all_manpages.read((char*)&manpage, sizeof(ManPage));
			current_pos = all_manpages.tellg()) {
		if(++i % 100 == 0) {
			std::cout << "Man pages indexed: " << i << "\r";
			std::cout.flush();
		}

		// Set with all valid words of the 'manpage'
		auto wordset = words_into_text(manpage.content);

		bool found;
		WordPtr wordptr, wpfound;
		for (auto i = wordset.begin(); i != wordset.end(); ++i) {
			strcpy(wordptr.name, (*i).c_str());

			// Checks if the word is already into the tree
			try {
				wpfound = word_tree.find(wordptr);
				found = true;
			} catch (std::runtime_error &error) {
				Word word;
				strcpy(word.name, (*i).c_str());
				word.add(current_pos);
				wordptr.pos = word.save();
				word_tree.insert(wordptr);
				found = false;
			}

			if (found)
				wpfound.add_manpage_to_word(current_pos);
		}
	}

	all_manpages.close();
	word_tree.save_on_file(INVERTED_INDEX_TREE);

	std::cout << std::endl << "Done." << std::endl;
}

void index_man_pages(const std::vector<std::string>& files_names) {
	auto n = files_names.size();
	std::cout << n << " man pages being indexed\n";

	std::remove(MANPAGES.c_str());
	std::ofstream ofs{MANPAGES, std::ofstream::binary};

	if (!ofs) {
		throw std::runtime_error("void index_man_pages() : Couldn't open file "
				+ MANPAGES);
	}

	structures::AVLTree<ManPageRecord> mptree;

	ManPage mp;
	ManPageRecord mpr;

	std::cout << "Reading man pages and saving to " << MANPAGES << std::endl;

	int t = n / 10;
	float percentage = 0;

	for (auto i = 0u; i < n; ++i) {
		if (i % t == 0) {
			show_progress(percentage += 0.1);
		}

		mp = ManPage{files_names[i]};

		strcpy(mpr.name, mp.name);
		mpr.position = ofs.tellp();

		ofs.write((char*) &mp, sizeof(ManPage));

		mptree.insert(mpr);
	}
	show_progress(1);

	ofs.close();

	std::cout << "Saving inverted tree to " << MPTREE << std::endl;
	mptree.save_on_file(MPTREE);
	std::cout << "Done." << std::endl;
}

#endif
