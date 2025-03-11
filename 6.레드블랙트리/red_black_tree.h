#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"


class red_black_node {
	enum node_color { red, black };

	friend class BST_template<red_black_node>;
	friend class red_black_tree;
	int key;
	int data;
	node_color color;
	red_black_node* lchild;
	red_black_node* rchild;

	red_black_node(int key, int data) {
		this->key = key;
		this->data = data;
		this->color = black;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class red_black_tree : public BST_template<red_black_node> {
protected :
	/*
	void remove_target(red_black_node*& target_ptr, stack<red_black_node*>* ancester_node_stack);

	void replace_with_inorder_predecessor(red_black_node*& target_ptr, stack<red_black_node*>* ancester_node_stack);

	void replace_with_inorder_successor(red_black_node*& target_ptr, stack<red_black_node*>* ancester_node_stack);
	*/

	void LL_rotation(red_black_node* target_node, red_black_node* parent_node);

	void LR_rotation(red_black_node* target_node, red_black_node* parent_node);

	void RL_rotation(red_black_node* target_node, red_black_node* parent_node);

	void RR_rotation(red_black_node* target_node, red_black_node* parent_node);

public :
	red_black_tree() : BST_template() {}

	/*
	void insert(int new_key, int new_data);

	void remove(int target_key);
	*/
};

#endif //RED_BLACK_TREE_H