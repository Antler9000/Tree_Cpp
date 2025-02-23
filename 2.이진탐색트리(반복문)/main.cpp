#include "BST_using_while.h"

int main() {
	BST& test_BST = *(new BST());
	test_BST.insert(5, 1515);
	test_BST.insert(7, 2727);
	test_BST.insert(3, 1313);
	test_BST.insert(4, 2424);
	test_BST.insert(6, 3636);
	test_BST.insert(1, 5151);
	test_BST.insert(8, 5858);
	test_BST.preorder_print();

	BST& copied_test_BST = *(new BST());
	copied_test_BST.copy_from(&test_BST);
	copied_test_BST.preorder_print();

	test_BST.remove(7);
	test_BST.preorder_print();

	test_BST.remove(3);
	test_BST.preorder_print();

	test_BST.remove(5);
	test_BST.preorder_print();

	test_BST.remove(4);
	test_BST.preorder_print();

	test_BST.remove(6);
	test_BST.preorder_print();

	test_BST.remove(1);
	test_BST.preorder_print();

	test_BST.remove(8);
	test_BST.preorder_print();

	delete& test_BST;
	delete& copied_test_BST;
	return 0;
}