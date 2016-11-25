#include "avl_tree.h"

template <typename T>
void print_vector(std::vector<T>& v) {
	for (auto i = v.begin(); i != v.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << std::endl;
}

int main() {
	structures::AVLTree<double> tree;
	for (double i = 0; i < 20; ++i) {
		tree.insert(i);
	}

	tree.save_on_file("avl.dat");

	structures::AVLTree<double> loaded{"avl.dat"};
}
