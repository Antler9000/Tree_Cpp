#include "splay_tree.h"

int main() {
	splay_tree& test_tree = *(new splay_tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	test_tree.insert(1, 5151);
	test_tree.insert(8, 5858);
	test_tree.preorder_print();

	cout << "retrieve test" << endl;
	cout << test_tree.retrieve(5) << endl;
	cout << test_tree.retrieve(7) << endl;
	cout << test_tree.retrieve(8) << endl;

	splay_tree& copied_test_tree = *(new splay_tree());
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