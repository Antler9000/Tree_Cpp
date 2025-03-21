#include "splay_tree.h"

int main() {
	SplayTree& test_tree = *(new SplayTree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	test_tree.insert(1, 5151);
	test_tree.insert(8, 5858);
	test_tree.preorder_print();

	cout << "retrieve test 8" << endl;
	test_tree.retrieve(8);
	test_tree.preorder_print();

	cout << "retrieve test 4" << endl;
	test_tree.retrieve(4);
	test_tree.preorder_print();

	cout << "retrieve test 3" << endl;
	test_tree.retrieve(3);
	test_tree.preorder_print();

	cout << "retrieve test 3" << endl;
	test_tree.retrieve(3);
	test_tree.preorder_print();

	cout << "retrieve test 7" << endl;
	test_tree.retrieve(7);
	test_tree.preorder_print();

	cout << "retrieve test 5" << endl;
	test_tree.retrieve(5);
	test_tree.preorder_print();


	SplayTree& copied_test_tree = *(new SplayTree());
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

	test_tree.remove(1);
	test_tree.preorder_print();

	test_tree.remove(8);
	test_tree.preorder_print();

	delete& test_tree;
	return 0;
}