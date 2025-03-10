#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class AVL_node {
	friend class BST_template<AVL_node>;
	friend class AVL_tree;
	int key;
	int data;
	int height_from_leaf;
	AVL_node* lchild;
	AVL_node* rchild;

	AVL_node(int key, int data) {
		this->key = key;
		this->data = data;
		this->height_from_leaf = 0;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class AVL_tree : public BST_template<AVL_node> {
protected :
	void remove_target(AVL_node*& target_ptr, stack<AVL_node*>* ancester_node_stack);

	void replace_with_inorder_predecessor(AVL_node*& target_ptr, stack<AVL_node*>* ancester_node_stack);

	void replace_with_inorder_successor(AVL_node*& target_ptr, stack<AVL_node*>* ancester_node_stack);

	void balancing_all_target_to_root(stack<AVL_node*>* ancester_node_stack);

	void balancing_target_node(AVL_node* target_node, AVL_node* parent_node);

	void LL_rotation(AVL_node* target_node, AVL_node* parent_node);

	void LR_rotation(AVL_node* target_node, AVL_node* parent_node);

	void RL_rotation(AVL_node* target_node, AVL_node* parent_node);

	void RR_rotation(AVL_node* target_node, AVL_node* parent_node);

	void update_height(AVL_node* target_node) {
		int height_from_lchild = 0;
		int height_from_rchild = 0;
		if (target_node->lchild != NULL) height_from_lchild = 1 + target_node->lchild->height_from_leaf;
		if (target_node->rchild != NULL) height_from_rchild = 1 + target_node->rchild->height_from_leaf;
		target_node->height_from_leaf = max(height_from_lchild, height_from_rchild);
	}

	int max(int a, int b) {
		return (a > b) ? a : b;
	}

public :
	AVL_tree() : BST_template() {}

	void insert(int new_key, int new_data);

	void remove(int target_key);
};

#endif //AVL_TREE_H