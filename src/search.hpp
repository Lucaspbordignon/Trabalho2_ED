#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include "man_page.hpp"
#include "paths.hpp"
#include "avl_tree.hpp"

ManPage search_by_name(std::string mp_name) {
	ManPageRecord mpr;
	strcpy(mpr.name, mp_name.c_str());
	structures::AVLTree<ManPageRecord> mptree{MPTREE};
	return ManPage{mptree.find(mpr)};
}

#endif
