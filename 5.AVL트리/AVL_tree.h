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
	void balancing_target_node(AVL_node* target_node) {
		int left_height = 0;
		int right_height = 0;
		if (target_node->lchild != NULL) left_height = target_node->lchild->height_from_leaf;
		if (target_node->rchild != NULL) right_height = target_node->rchild->height_from_leaf;

		if (left_height - right_height >= 2) {
			if (target_node->lchild->rchild == NULL) {
				cout << "LL 회전" << endl;
			}
			else if (target_node->lchild->lchild == NULL) {
				cout << "LR 회전" << endl;
			}
			else {
				if (target_node->lchild->lchild->height_from_leaf > target_node->lchild->rchild->height_from_leaf) {
					cout << "LL 회전" << endl;
				}
				else {
					cout << "LR 회전" << endl;
				}
			}
		}
		else if (right_height - left_height >= 2) {
			if (target_node->rchild->rchild == NULL) {
				cout << "RL 회전" << endl;
			}
			else if (target_node->rchild->lchild == NULL) {
				cout << "RR 회전" << endl;
			}
			else {
				if (target_node->rchild->lchild->height_from_leaf > target_node->rchild->rchild->height_from_leaf) {
					cout << "RL 회전" << endl;
				}
				else {
					cout << "RR 회전" << endl;
				}
			}
		}
	}

	void balancing_all_target_to_root(stack<AVL_node*>* ancester_node_stack) {
		while (ancester_node_stack->is_empty() == false) {
			AVL_node* reverse_traverse_node = ancester_node_stack->pop();
			balancing_target_node(reverse_traverse_node);
		}
	}

public :
	AVL_tree() : BST_template() {}

	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new AVL_node(new_key, new_data);
			return;
		}

		AVL_node* traverse_ptr = head;
		stack<AVL_node*> ancester_node_stack;
		while (true) {
			if (new_key < traverse_ptr->key) {
				if(traverse_ptr->lchild == NULL){
					traverse_ptr->lchild = new AVL_node(new_key, new_data);
					ancester_node_stack.push(traverse_ptr);
					balancing_all_target_to_root(&ancester_node_stack);
					return;
				}
				else {
					ancester_node_stack.push(traverse_ptr);
					traverse_ptr = traverse_ptr->lchild;
				}
			}
			else {
				if (traverse_ptr->rchild == NULL) {
					traverse_ptr->rchild = new AVL_node(new_key, new_data);
					ancester_node_stack.push(traverse_ptr);
					balancing_all_target_to_root(&ancester_node_stack);
					return;
				}
				else {
					ancester_node_stack.push(traverse_ptr);
					traverse_ptr = traverse_ptr->rchild;
				}
			}
		}
	}

	void remove(int target_key) {
		if (head == NULL) {
			cout << "Cannot remove! tree is emptied" << endl;
			return;
		}

		if (head->key == target_key) {
			BST_template<AVL_node>::remove_target(head);
			return;
		}

		AVL_node* traverse_ptr = head;
		while (true) {
			if (target_key < traverse_ptr->key) {
				if (traverse_ptr->lchild->key == target_key) {
					BST_template<AVL_node>::remove_target(traverse_ptr->lchild);
					return;
				}
				else traverse_ptr = traverse_ptr->lchild;
			}
			else {
				if (traverse_ptr->rchild->key == target_key) {
					BST_template<AVL_node>::remove_target(traverse_ptr->rchild);
					return;
				}
				else traverse_ptr = traverse_ptr->rchild;
			}
		}
	}
};

#endif //AVL_TREE_H