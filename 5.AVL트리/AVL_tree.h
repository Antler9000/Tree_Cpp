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
	int max(int a, int b) { 
		return (a>b) ? a : b; 
	}

	void update_height(AVL_node* target_node) {
		int height_from_lchild = 0;
		int height_from_rchild = 0;
		if (target_node->lchild != NULL) height_from_lchild = 1 + target_node->lchild->height_from_leaf;
		if (target_node->rchild != NULL) height_from_rchild = 1 + target_node->rchild->height_from_leaf;
		target_node->height_from_leaf = max(height_from_lchild, height_from_rchild);
	}

	void LL_rotation(AVL_node* target_node, AVL_node* parent_node) {
		cout << "LL 회전" << endl;			
		if (parent_node->lchild == target_node) {
			parent_node->lchild = target_node->lchild;
			target_node->lchild = target_node->lchild->rchild;
			parent_node->lchild->rchild = target_node;
		}
		else {
			parent_node->rchild = target_node->lchild;
			target_node->lchild = target_node->lchild->rchild;
			parent_node->rchild->rchild = target_node;
		}
		parent_node->lchild->height_from_leaf = target_node->height_from_leaf - 1;
		update_height(target_node);
	}

	void LR_rotation(AVL_node* target_node, AVL_node* parent_node) {
		cout << "LR 회전" << endl;
	}

	void RL_rotation(AVL_node* target_node, AVL_node* parent_node) {
		cout << "RL 회전" << endl;
	}

	void RR_rotation(AVL_node* target_node, AVL_node* parent_node) {
		cout << "RR 회전" << endl;
		if (parent_node->lchild == target_node) {
			parent_node->lchild = target_node->rchild;
			target_node->rchild = target_node->rchild->lchild;
			parent_node->lchild->lchild = target_node;
		}
		else {
			parent_node->rchild = target_node->rchild;
			target_node->rchild = target_node->rchild->lchild;
			parent_node->rchild->lchild = target_node;
		}
		parent_node->rchild->height_from_leaf = target_node->height_from_leaf - 1;
		update_height(target_node);
	}

	void balancing_target_node(AVL_node* target_node, AVL_node* parent_node) {
		int left_height = 0;
		int right_height = 0;
		if (target_node->lchild != NULL) left_height = 1 + target_node->lchild->height_from_leaf;
		if (target_node->rchild != NULL) right_height = 1 + target_node->rchild->height_from_leaf;

		if (left_height - right_height >= 2) {
			if (target_node->lchild->rchild == NULL) {
				LL_rotation(target_node, parent_node);
			}
			else if (target_node->lchild->lchild == NULL) {
				LR_rotation(target_node, parent_node);
			}
			else {
				if (target_node->lchild->lchild->height_from_leaf > target_node->lchild->rchild->height_from_leaf) {
					LL_rotation(target_node, parent_node);
				}
				else {
					LR_rotation(target_node, parent_node);
				}
			}
		}
		else if (right_height - left_height >= 2) {
			if (target_node->rchild->rchild == NULL) {
				RL_rotation(target_node, parent_node);
			}
			else if (target_node->rchild->lchild == NULL) {
				RR_rotation(target_node, parent_node);
			}
			else {
				if (target_node->rchild->lchild->height_from_leaf > target_node->rchild->rchild->height_from_leaf) {
					RL_rotation(target_node, parent_node);
				}
				else {
					RR_rotation(target_node, parent_node);
				}
			}
		}
	}

	void balancing_all_target_to_root(stack<AVL_node*>* ancester_node_stack) {
		while (ancester_node_stack->is_empty() == false) {
			AVL_node* retraverse_node = ancester_node_stack->pop();
			AVL_node* parent_of_retraverse_node = ancester_node_stack->get_top();
			update_height(retraverse_node);
			cout << "node's height : " << retraverse_node->height_from_leaf << endl;	//debug
			balancing_target_node(retraverse_node, parent_of_retraverse_node);
		}
	}

public :
	AVL_tree() : BST_template() {}

	void insert(int new_key, int new_data) {
		cout << endl << "inserting key : " << new_key << endl;					//debug
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