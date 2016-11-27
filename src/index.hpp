#ifndef INDEX_HPP
#define INDEX_HPP

#include "paths.hpp"
#include "utils.hpp"
#include "man_page.hpp"
#include "avl_tree.hpp"




void addPageToWord(WordPtr& wordptr, std::streampos pos) {
	Word word;

	std::ifstream input{INVERTED_INDEX};

	if (!input) {
		throw std::runtime_error("Init::addPageToWord: could not open input file");
	}

	input.seekg(wordptr.pos);

	input.read((char*) &word, sizeof(Word));

	input.close();

	word.add(pos);

	std::ofstream output{INVERTED_INDEX};

	if (!output) {
		throw std::runtime_error("Init::addPageToWord: could not open output file");
	}

	output.seekp(wordptr.pos);

	output.write((char*) &word, sizeof(Word));

	output.close();
}

/**
 * @brief      Adiciona uma nova palavra ao arquivo invertido
 *
 * @param      word  Palavra a ser adicionada
 *
 * @return     Posicao que a palavra foi inserida
 */
std::streampos addNewWord(Word& word) {
	std::ofstream output(INVERTED_INDEX, std::ios::out | std::ios::app | std::ios::binary);

	if (!output) {
		throw std::runtime_error("Init::addNewWord: could not open output file");
	}

	auto pos = output.tellp();

	output.write((char*) &word, sizeof(Word));

	output.close();

	return pos;
}




void index_man_pages() {
	auto files_names = split(exec("ls " + MPPATH), "\n");
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

void inverted_index() {
	structures::AVLTree<WordPtr> word_tree;
	std::cout << "Generating the inverted index file." << std::endl;
	auto already_indexed = 0;

	std::ofstream ofs{INVERTED_INDEX};
	std::ifstream all_manpages{MANPAGES};

	if (!all_manpages) {
		throw std::runtime_error("Init::generateInvertedIndex: could not open file");
	}

	std::streampos current_pos;
	ManPage manpage;

	// Reads all the manpages
	while(all_manpages.good()) {
		if (already_indexed % 100 == 0)
			std::cout << "Manpages indexed: " << already_indexed << std::endl;
		++already_indexed;

		current_pos = all_manpages.tellg();

		all_manpages.read((char*)&manpage, sizeof(ManPage));

		auto wordsvec = words_into_text(manpage.content);
		for (auto i = wordsvec.begin(); i != wordsvec.end(); ++i) {
			WordPtr wordptr;
			WordPtr wordptrptr;
			bool found;
			strcpy(wordptr.word, (*i).c_str());

			try {
				wordptrptr = word_tree.find(wordptr);
				found = true;
			} catch (std::runtime_error &error) {
				found = false;
			}

			// Word is already into a tree node
			if (found) {
				addPageToWord(wordptrptr, current_pos);
			} else {
				Word word;
				strcpy(word.word, (*i).c_str());
				word.add(current_pos);

				wordptr.pos = addNewWord(word);
				word_tree.insert(wordptr);
			}
		}
	}
	all_manpages.close();
	word_tree.save_on_file(INVERTED_INDEX);
}


#endif
