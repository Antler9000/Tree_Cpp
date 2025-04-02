#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

enum NodeColor { RED, BLACK };

//이상하게 여기에만 정의해놨는데도 이 연산자 오버로딩에서는 중복정의 에러가 떠서, 그냥 inline으로 박제해서 해결함
//ostream 클래스는 복사생성자가 없으므로, 값복사가 아니라 레퍼런스 방식으로 전달 받음
inline ostream& operator <<(ostream& out, NodeColor color) {
	if (color == RED) {
		out << "RED";
	}
	else {
		out << "BLACK";
	}
	return out;
}

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

	void print_node() {
		cout << "node key : " << key << " / node data : " << data << " / node color : " << color << endl;
	}
};

class RedBlackTree : public BST_template<RedBlackNode> {
protected :
	/*
	void remove_target(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);

	void replace_with_inorder_predecessor(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);

	void replace_with_inorder_successor(RedBlackNode*& target_ptr, stack<RedBlackNode*>* ancester_node_stack);
	*/

	void check_and_resolve_4_nodes_while_descent(Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* target_node = route_stack->pop();
		RedBlackNode* parent_node = route_stack->pop();

		if (is_4_node(target_node)) {
			target_node->lchild->color = BLACK;
			target_node->rchild->color = BLACK;
			if (parent_node != NULL && parent_node->color == RED) {
				RedBlackNode* grand_parent_node = route_stack->pop();
				RedBlackNode* great_grand_parent_node = route_stack->pop();

				resolve_consecutive_red_nodes(target_node, parent_node, grand_parent_node, great_grand_parent_node);

				if (great_grand_parent_node != NULL) route_stack->push(great_grand_parent_node);
				route_stack->push(grand_parent_node);
			}
			else split_4_node(target_node);
		}

		route_stack->push(parent_node);
		route_stack->push(target_node);
	}

	void check_and_resolve_4_nodes_on_destination(Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* target_node = route_stack->pop();
		RedBlackNode* parent_node = route_stack->pop();

		if (parent_node->color == RED) {
			RedBlackNode* grand_parent_node = route_stack->pop();
			RedBlackNode* great_grand_parent_node = route_stack->pop();
			resolve_consecutive_red_nodes(target_node, parent_node, grand_parent_node, great_grand_parent_node);
		}
	}

	bool is_4_node(RedBlackNode* target_node) {
		if (target_node->lchild != NULL && target_node->rchild != NULL) {
			if (target_node->lchild->color == RED && target_node->rchild->color == RED) {
				return true;
			}
		}
		return false;
	}

	void split_4_node(RedBlackNode* target_node) {
		if (target_node != head) target_node->color = RED;
	}

	void resolve_consecutive_red_nodes(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode* grand_parent_node, RedBlackNode* great_grand_parent_node) {
		if (great_grand_parent_node == NULL) {
			select_proper_rotation(target_node, parent_node, head);
		}
		else if (great_grand_parent_node->lchild == grand_parent_node) {
			select_proper_rotation(target_node, parent_node, great_grand_parent_node->lchild);
		}
		else {
			select_proper_rotation(target_node, parent_node, great_grand_parent_node->rchild);
		}
	}

	void select_proper_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node) {
		if (grand_parent_node->lchild == parent_node) {
			if (parent_node->lchild == target_node) {
				LL_rotation(target_node, parent_node, grand_parent_node);
			}
			else {
				LR_rotation(target_node, parent_node, grand_parent_node);
			}
		}
		else {
			if (parent_node->lchild == target_node) {
				RL_rotation(target_node, parent_node, grand_parent_node);
			}
			else {
				RR_rotation(target_node, parent_node, grand_parent_node);
			}
		}
	}

	void LL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->color = RED;
		parent_node->color = BLACK;
		target_node->color = RED;

		grand_parent_node->lchild = parent_node->rchild;
		parent_node->rchild = grand_parent_node;
		grand_parent_node = parent_node;
	}

	void LR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->lchild = target_node;
		parent_node->rchild = target_node->lchild;
		target_node->lchild = parent_node;
		LL_rotation(parent_node, target_node, grand_parent_node);
	}

	void RL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->rchild = target_node;
		parent_node->lchild = target_node->rchild;
		target_node->rchild = parent_node;
		RR_rotation(parent_node, target_node, grand_parent_node);
	}

	void RR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->color = RED;
		parent_node->color = BLACK;
		target_node->color = RED;

		grand_parent_node->rchild = parent_node->lchild;
		parent_node->lchild = grand_parent_node;
		grand_parent_node = parent_node;
	}

public :
	RedBlackTree() : BST_template() {}

	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new RedBlackNode(new_key, new_data);
			return;
		}
		
		RedBlackNode* traverse_ptr = head;
		Stack<RedBlackNode*> route_stack;
		while (true) {
			route_stack.push(traverse_ptr);
			check_and_resolve_4_nodes_while_descent(&route_stack);

			if (new_key < traverse_ptr->key) {
				if (traverse_ptr->lchild != NULL) {
					traverse_ptr = traverse_ptr->lchild;
				}
				else {
					traverse_ptr->lchild = new RedBlackNode(new_key, new_data);
					traverse_ptr->lchild->color = RED;
					route_stack.push(traverse_ptr->lchild);
					check_and_resolve_4_nodes_on_destination(&route_stack);
					return;
				}
			}
			else if(traverse_ptr->key < new_key) {
				if (traverse_ptr->rchild != NULL) {
					traverse_ptr = traverse_ptr->rchild;
				}
				else {
					traverse_ptr->rchild = new RedBlackNode(new_key, new_data);
					traverse_ptr->rchild->color = RED;
					route_stack.push(traverse_ptr->rchild);
					check_and_resolve_4_nodes_on_destination(&route_stack);
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