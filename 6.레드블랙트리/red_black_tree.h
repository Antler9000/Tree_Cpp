#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

enum NodeColor { RED, BLACK };

class RedBlackNode {

	friend class BST_template<RedBlackNode>;
	friend class RedBlackTree;
	int key;
	int data;
	NodeColor color;
	RedBlackNode* lchild;
	RedBlackNode* rchild;

	RedBlackNode(int key, int data) {
		this->key = key;
		this->data = data;
		this->color = BLACK;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class RedBlackTree : public BST_template<RedBlackNode> {
protected :
	/*
	void remove_target(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);

	void replace_with_inorder_predecessor(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);

	void replace_with_inorder_successor(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);
	*/

	void LL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node);

	void LR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node);

	void RL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node);

	void RR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node);

public :
	RedBlackTree() : BST_template() {}

	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new RedBlackNode(new_key, new_data);
			return;
		}
		
		RedBlackNode* traverse_ptr = head;
		while (true) {
			if (new_key < traverse_ptr->key) {
				if (traverse_ptr->lchild != NULL) {
					traverse_ptr = traverse_ptr->lchild;
				}
				else {
					traverse_ptr->lchild = new RedBlackNode(new_key, new_data);
					return;
				}
			}
			else if(traverse_ptr->key < new_key) {
				if (traverse_ptr->rchild != NULL) {
					traverse_ptr = traverse_ptr->rchild;
				}
				else {
					traverse_ptr->rchild = new RedBlackNode(new_key, new_data);
					return;
				}
			}
			else {
				cout << "Cannot insert node to tree! There are same key node already!" << endl;
				return;
			}
		}
	}

	/*
	void remove(int target_key) {

	}
	*/
};

#endif //RED_BLACK_TREE_H