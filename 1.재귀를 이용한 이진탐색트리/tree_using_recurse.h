#ifndef TREE_USING_RECURSE_H
#define TREE_USING_RECURSE_H


#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	tree* lchild;
	tree* rchild;


public:
	node(int key, int data);
};

class tree {
	node* head;

public:
	tree();

	~tree();

	void preorder_traverse_print();

	void inorder_traverse_print();

	void postorder_traverse_print();

	int search(int target_key);

	void insert(int new_key, int new_data);

	void remove_all();

	void remove(int target_key);

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();
};


#endif //TREE_USING_RECURSE_H