#include "BST_using_recurse.h"

int main() {
	BST& test_BST = *(new BST());
	test_BST.insert(5, 1515);
	test_BST.insert(7, 2727);
	test_BST.insert(3, 1313);
	test_BST.insert(4, 2424);
	test_BST.insert(6, 3636);
	test_BST.preorder_print();

	BST& copied_BST = *(new BST());
	copied_BST.copy_from(&test_BST);
	copied_BST.preorder_print();

	test_BST.remove(7);
	test_BST.preorder_print();

	test_BST.remove(5);
	test_BST.preorder_print();

	test_BST.remove(6);
	test_BST.preorder_print();

	test_BST.remove(4);
	test_BST.preorder_print();

	test_BST.remove(3);
	test_BST.preorder_print();

	test_BST.remove_all();
	test_BST.preorder_print();

	return 0;
}