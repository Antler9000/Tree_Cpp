#include "BST_using_recurse.h"

int main() {
	tree& test_tree = *(new tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove(7);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove(5);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove(6);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove(4);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove(3);
	cout << "traverse" << endl;
	test_tree.preorder_print();

	test_tree.remove_all();
	cout << "traverse" << endl;
	test_tree.preorder_print();

	return 0;
}