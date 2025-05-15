#include "red_black_tree.h"

int main() {
	RedBlackTree& test_tree = *(new RedBlackTree());
	test_tree.insert(5, 55);
	test_tree.insert(9, 99);
	test_tree.insert(8, 88);
	test_tree.insert(7, 77);
	test_tree.insert(1, 11);
	test_tree.insert(2, 22);
	test_tree.insert(3, 33);
	test_tree.preorder_print();

	RedBlackTree& copied_test_tree = *(new RedBlackTree());
	copied_test_tree.copy_from(&test_tree);
	copied_test_tree.preorder_print();

	test_tree.remove(1);
	test_tree.preorder_print();

	test_tree.remove(2);
	test_tree.preorder_print();

	test_tree.remove(3);
	test_tree.preorder_print();

	test_tree.remove(5);
	test_tree.preorder_print();

	test_tree.remove(7);
	test_tree.preorder_print();

	test_tree.remove(8);
	test_tree.preorder_print();

	test_tree.remove(9);
	test_tree.preorder_print();

	delete& test_tree;
	return 0;
}