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
	//삽입 메소드에서 삽입 위치를 찾기 위해 빈 리프노드 자리로 탐색하는 과정에서 매번 호출되는 메소드다.
	//4노드가 있으면 이를 쪼개놓고 내려가는 로직을 수행한다.
	void check_and_resolve_4_nodes_while_descent(Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* target_node = route_stack->pop();
		RedBlackNode* parent_node = route_stack->pop();

		if (is_4_node(target_node)) {
			target_node->lchild->color = BLACK;
			target_node->rchild->color = BLACK;
			if (parent_node != NULL && parent_node->color == RED) {
				RedBlackNode* grand_parent_node = route_stack->pop();
				RedBlackNode* great_grand_parent_node = route_stack->pop();

				do_proper_rotation(target_node, parent_node, grand_parent_node, great_grand_parent_node);

				if (great_grand_parent_node != NULL) route_stack->push(great_grand_parent_node);
				route_stack->push(grand_parent_node);
			}
			else split_4_node(target_node);
		}

		route_stack->push(parent_node);
		route_stack->push(target_node);
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

	//삽입 메소드에서는 빈 리프노드에 레드 노드의 형태로 삽입이 일어난다.
	//그렇게 삽입이 일어났는데 "조부노드-부모노드-삽입노드"가 "블랙-레드-레드"이렇게 연속적인 레드로 구성될 경우,
	//이를 확인하고 회전으로 해결하기 위한 메소드다.
	void check_and_resolve_4_nodes_on_destination(Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* target_node = route_stack->pop();
		RedBlackNode* parent_node = route_stack->pop();

		if (parent_node->color == RED) {
			RedBlackNode* grand_parent_node = route_stack->pop();
			RedBlackNode* great_grand_parent_node = route_stack->pop();
			do_proper_rotation(target_node, parent_node, grand_parent_node, great_grand_parent_node);
		}
	}

	void do_proper_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode* grand_parent_node, RedBlackNode* great_grand_parent_node) {
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

	//회전으로 인해 조부 노드의 위치가 변하면, 증조부 노드의 자식 포인터도 그에 맞게 업데이트해줘야 한다.
	//따라서 조부 노드의 경우에는 단순히 해당 노드의 포인터를 값으로 받아오지 않고, 증조부 노드의 자식 포인터의 레퍼런스 인자로 받아왔다.
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

	//조부 노드의 인자를 레퍼런스 인자로 받아오는 이유는 위 select_proper_rotation(...)메소드에 기재되어 있다.
	void LL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->color = RED;
		parent_node->color = BLACK;
		target_node->color = RED;

		grand_parent_node->lchild = parent_node->rchild;
		parent_node->rchild = grand_parent_node;
		grand_parent_node = parent_node;
	}

	//조부 노드의 인자를 레퍼런스 인자로 받아오는 이유는 위 select_proper_rotation(...)메소드에 기재되어 있다.
	void LR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->lchild = target_node;
		parent_node->rchild = target_node->lchild;
		target_node->lchild = parent_node;
		LL_rotation(parent_node, target_node, grand_parent_node);
	}

	//조부 노드의 인자를 레퍼런스 인자로 받아오는 이유는 위 select_proper_rotation(...)메소드에 기재되어 있다.
	void RL_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->rchild = target_node;
		parent_node->lchild = target_node->rchild;
		target_node->rchild = parent_node;
		RR_rotation(parent_node, target_node, grand_parent_node);
	}

	//조부 노드의 인자를 레퍼런스 인자로 받아오는 이유는 위 select_proper_rotation(...)메소드에 기재되어 있다.
	void RR_rotation(RedBlackNode* target_node, RedBlackNode* parent_node, RedBlackNode*& grand_parent_node){
		grand_parent_node->color = RED;
		parent_node->color = BLACK;
		target_node->color = RED;

		grand_parent_node->rchild = parent_node->lchild;
		parent_node->lchild = grand_parent_node;
		grand_parent_node = parent_node;
	}

	//삭제 대상이 리프 노드여서 아에 삭제되는 경우,
	//그 노드를 가리키는 부모노드의 자식 포인터를 null로 해야하기에 레퍼런스 인자를 두었다.
	void remove_target(RedBlackNode*& target_node, Stack<RedBlackNode*>* route_stack) {
		if (target_node->lchild != NULL && target_node->rchild != NULL) {				//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
			replace_with_inorder_successor(target_node, route_stack);
		}
		else if (target_node->lchild == NULL && target_node->rchild != NULL) {
			replace_with_inorder_successor(target_node, route_stack);
		}
		else if (target_node->lchild != NULL && target_node->rchild == NULL) {
			replace_with_inorder_predecessor(target_node, route_stack);
		}
		else {
			delete target_node;
			target_node = NULL;
		}
	}

	//이진탐색트리에서의 replace_with_inorder_predecessor(...)과 차이점은,
	//중위 선행자나 후속자의 삭제 문제로 대체할 때, 트리의 블랙 노드의 균형이 깨지는 것을 방지하기 위해서 다음을 수행한다는 점이다.
	void replace_with_inorder_predecessor(RedBlackNode*& target_node, Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* traverse_ptr = target_node->lchild;
		route_stack->push(traverse_ptr);
		while (traverse_ptr->rchild != NULL) {
			traverse_ptr = traverse_ptr->rchild;
			route_stack->push(traverse_ptr);
		}
		RedBlackNode* predecessor_node = route_stack->pop();
		RedBlackNode* parent_of_predecessor = route_stack->pop();
		RedBlackNode* grand_parent_of_predecessor = route_stack->pop();
		target_node->key = predecessor_node->key;
		target_node->data = predecessor_node->data;

		//1.중위 선행자나 후속자 자신이 레드 노드인가?
		// -> 그렇다면 그냥 삭제하면 된다
		if (predecessor_node->color == RED) {
			if (parent_of_predecessor == NULL) parent_of_predecessor->lchild = NULL;
			else parent_of_predecessor->rchild = NULL;
			delete predecessor_node;
			return;
		}
		//2.위 경우가 아니라면, 중위 선행자나 후속자에게 자식으로 레드 리프 노드가 달려있는가?
		// -> 그렇다면 중위 선행자나 후속자의 부모에 해당 자식을 붙일 때, 해당 빨간 자식 노드의 색깔을 검은색으로 바꾸면 된다
		if ((predecessor_node->lchild != NULL) && (predecessor_node->lchild->color == RED)) {
			predecessor_node->key = predecessor_node->lchild->key;
			predecessor_node->data = predecessor_node->lchild->data;
			delete predecessor_node->lchild;
			predecessor_node->lchild == NULL;
			return;
		}
		//3.위 경우도 아니라면, 균형을 맞추기 위해 댕겨올 자매노드의 자식(=조카) 레드노드가 있는가?
		// -> 그렇다면 회전을 통해서 블랙 노드의 균형을 맞추면 된다. 색깔은 회전 이전에 원래 그 자리에 위치해있던 노드의 색깔을 물려받도록 한다
		RedBlackNode* brother_ptr = NULL;
		if (parent_of_predecessor == NULL) brother_ptr = parent_of_predecessor->rchild;
		else brother_ptr = parent_of_predecessor->lchild;
		
		if ((brother_ptr->lchild) && (brother_ptr->lchild->color == RED)) {
			do_proper_rotation(brother_ptr->lchild, brother_ptr, parent_of_predecessor, grand_parent_of_predecessor);
			return;
		}
		else if ((brother_ptr->rchild) && (brother_ptr->rchild->color == RED)) {
			do_proper_rotation(brother_ptr->rchild, brother_ptr, parent_of_predecessor, grand_parent_of_predecessor);
			return;
		}
		
		//4.위 경우도 아니라면, 부모노드가 레드노드인가?
		// -> 부모노드가 블랙노드가 되고 자매 노드가 레드 노드가 되도록 변경하여 균형을 맞추자


		//5.위 경우도 아니라면
		// -> 자매 노드를 레드 노드가 되도록 하고서, 부모노드 위치의 삭제 문제로 변환하여 다시 3번부터 수행하도록 하자


	}

	//이진탐색트리에서의 replace_with_inorder_successor()과 차이점은 바로 위의 replace_with_inorder_predecessor(...)메소드에 기재되어 있는 것과 같다.
	void replace_with_inorder_successor(RedBlackNode*& target_ptr, Stack<RedBlackNode*>* route_stack) {
		RedBlackNode* previous_ptr = NULL;
		RedBlackNode* traverse_ptr = target_ptr->rchild;
		while (traverse_ptr->lchild != NULL) {
			previous_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->lchild;
		}
		if (previous_ptr != NULL) previous_ptr->lchild = traverse_ptr->rchild;
		else target_ptr->rchild = traverse_ptr->rchild;
		target_ptr->key = traverse_ptr->key;
		target_ptr->data = traverse_ptr->data;
		delete traverse_ptr;
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
			else if (traverse_ptr->key < new_key) {
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

	void remove(int target_key) {
		Stack<RedBlackNode*> route_stack;

		if (head->key == target_key) {
			route_stack.push(head);
			remove_target(head, &route_stack);
			return;
		} 

		RedBlackNode* traverse_ptr = head;
		while (true) {
			if (target_key < traverse_ptr->key) {
				if (traverse_ptr->lchild != NULL) {
					route_stack.push(traverse_ptr);
					traverse_ptr = traverse_ptr->lchild;
				}
				else {
					cout << "Cannot remove! Cannot find such target node!" << endl;
					return;
				}
			}
			else if (traverse_ptr->key < target_key) {
				if (traverse_ptr->rchild != NULL) {
					route_stack.push(traverse_ptr);
					traverse_ptr = traverse_ptr->rchild;
				}
				else {
					cout << "Cannot remove! Cannot find such target node!" << endl;
					return;
				}
			}
			else {
				RedBlackNode* parent = route_stack.get_top();
				route_stack.push(traverse_ptr);
				if (parent->lchild = traverse_ptr) {
					remove_target(parent->lchild, &route_stack);
				}
				else {
					remove_target(parent->rchild, &route_stack);
				}
				return;
			}
		}
	}
};

#endif //RED_BLACK_TREE_H