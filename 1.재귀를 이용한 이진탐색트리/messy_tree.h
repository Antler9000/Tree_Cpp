#ifndef MESSY_TREE_H
#define MESSY_TREE_H


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

	void traverse_print();

	int search(int target_key);

	void insert(int new_key, int new_data);

	void remove_all();

	void remove(int target_key);

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();
};


#endif //MESSY_TREE_H