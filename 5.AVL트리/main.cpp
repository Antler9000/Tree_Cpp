#include "AVL_tree.h"

int main() {
	AVL_tree& test_tree = *(new AVL_tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	test_tree.insert(2, 5252);
	test_tree.insert(8, 5858);
	test_tree.insert(1, 5151);
	test_tree.insert(9, 1919);
	test_tree.insert(0, 5050);
	test_tree.insert(10, 1010);
	test_tree.preorder_print();

	AVL_tree& copied_test_tree = *(new AVL_tree());
	copied_test_tree.copy_from(&test_tree);
	copied_test_tree.preorder_print();

	test_tree.remove(7);
	test_tree.preorder_print();

	test_tree.remove(3);
	test_tree.preorder_print();

	test_tree.remove(5);
	test_tree.preorder_print();

	test_tree.remove(4);
	test_tree.preorder_print();

	test_tree.remove(6);
	test_tree.preorder_print();

	test_tree.remove(2);
	test_tree.preorder_print();

	test_tree.remove(8);
	test_tree.preorder_print();

	delete& test_tree;
	return 0;
}