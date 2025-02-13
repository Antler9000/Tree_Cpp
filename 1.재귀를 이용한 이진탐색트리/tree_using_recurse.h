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

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();

public:
	tree();

	~tree();

	int get_data(int target_key);

	void insert(int new_key, int new_data);

	void remove(int target_key);

	void remove_all();

	void preorder_print();

	void inorder_print();

	void postorder_print();
};

#endif //TREE_USING_RECURSE_H