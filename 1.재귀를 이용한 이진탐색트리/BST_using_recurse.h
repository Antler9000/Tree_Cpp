#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	tree* lchild;
	tree* rchild;


public:
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

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();

public:
	tree() {
		cout << "tree is made!" << endl;
		head = NULL;
	}

	~tree() {
		remove_all();
	}

	int get_data(int target_key);

	void insert(int new_key, int new_data);

	void remove(int target_key);

	void remove_all() {
		if (head != NULL) {
			if (head->lchild != NULL) head->lchild->remove_all();
			if (head->rchild != NULL) head->rchild->remove_all();
			delete head;
			head = NULL;
		}
	}

	void preorder_print() {
		if (head == NULL) {
			cout << "cannot traverse. head is NULL." << endl;
			return;
		}
		cout << "node key : " << head->key << " / node data : " << head->data << endl;
		if (head->lchild != NULL) head->lchild->preorder_print();
		if (head->rchild != NULL) head->rchild->preorder_print();
	}

	void inorder_print() {
		if (head == NULL) {
			cout << "cannot traverse. head is NULL." << endl;
			return;
		}
		if (head->lchild != NULL) head->lchild->inorder_print();
		cout << "node key : " << head->key << " / node data : " << head->data << endl;
		if (head->rchild != NULL) head->rchild->inorder_print();
	}


	void postorder_print() {
		if (head == NULL) {
			cout << "cannot traverse. head is NULL." << endl;
			return;
		}
		if (head->lchild != NULL) head->lchild->postorder_print();
		if (head->rchild != NULL) head->rchild->postorder_print();
		cout << "node key : " << head->key << " / node data : " << head->data << endl;
	}

};

#endif //TREE_USING_RECURSE_H