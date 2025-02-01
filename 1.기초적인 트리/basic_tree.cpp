#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
public :
	node(int key, int data) {
		cout << "node is made!" << endl;
		this->key = key;
		this->data = data;
	}
};

class tree {
	node* head;
	tree* lchild;
	tree* rchild;

public:
	tree() {
		cout << "tree is made!" << endl;
		head = NULL;
		lchild = NULL;
		rchild = NULL;
	}

	~tree() {

	}

	int search(int target_key) {
		if (head != NULL) {
			if (head->key == target_key) return head->data;
			else {
				if (lchild != NULL) search(lchild->search(target_key));
				if (rchild != NULL) search(rchild->search(target_key));
			}
		}
	}

	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new node(new_key, new_data);
		}
		else {
			if (new_key < head->key) {
				lchild->insert(new_key, new_data);
			}
			else if(head->key < new_key) {
				rchild->insert(new_key, new_data);
			}
			else {
				cout << "cannot insert! key is same!" << endl;
			}
		}
	}

	int remove(int target_key) {

	}
};
int main() {
	tree& test_tree = *(new tree());
	test_tree.insert(5, 1515);
	cout << "searched data is " << test_tree.search(5) << endl;
	return 0;
}