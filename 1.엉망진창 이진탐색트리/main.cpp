#include "messy_tree.h"

int main() {
	tree& test_tree = *(new tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	cout << "traverse" << endl;
	test_tree.traverse();


	test_tree.remove(7);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(5);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(6);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(4);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(3);
	cout << "traverse" << endl;
	test_tree.traverse();



	test_tree.traverse_remove();
	cout << "traverse" << endl;
	test_tree.traverse();


	return 0;
}