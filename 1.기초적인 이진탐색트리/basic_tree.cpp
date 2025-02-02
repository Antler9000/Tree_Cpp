#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	tree* lchild;
	tree* rchild;


public :
	node(int key, int data) {
		cout << "node is made!" << endl;
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class tree {
	node* head;

public:
	tree() {
		cout << "tree is made!" << endl;
	}

	~tree() {

	}

	int search(int target_key) {
		if (head == NULL) {
			cout << "can not search. there is no such key." << endl;
		}

		if (target_key < head->key) {
			if (head->lchild != NULL) return head->lchild->search(target_key);
		} 
		else if (head->key < target_key) {
			if (head->rchild != NULL) return head->rchild->search(target_key);
		}
		else {
			return head->data;
		}
	}

	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new node(new_key, new_data);
		}
		else {
			if (new_key < head->key) {
				head->lchild = new tree();
				head->lchild->insert(new_key, new_data);
			}
			else if(head->key < new_key) {
				head->rchild = new tree();
				head->rchild->insert(new_key, new_data);
			}
			else {
				cout << "cannot insert! key is same!" << endl;
			}
		}
	}

	int remove(int target_key) {
		if (head != NULL) {
			cout << "cannot remove! tree is emptied!" << endl;
			return -1;
		}

	}
};
int main() {
	tree& test_tree = *(new tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	cout << "searched data is " << test_tree.search(5) << endl;
	cout << "searched data is " << test_tree.search(7) << endl;
	cout << "searched data is " << test_tree.search(3) << endl;
	return 0;
}