#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "stack.h"

template <class T>
class BST_template;


class BST_node {
	friend class BST_template<BST_node>;
	int key;
	int data;
	BST_node* lchild;
	BST_node* rchild;

	BST_node(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};


//이진 탐색 트리를 상속받아 더 특수화된 트리(eg. SplayTree 등)를 만들 때 내부 노드 클래스를 변경하기 쉽도록, 사용할 내부 노드 클래스를 템플릿 인자로 정의하였다.
//따라서, 이진 탐색 트리에서 더 특수화된 트리을 정의하고 싶다면, BST_template에 자신이 정의한 새 노드 클래스를 인자로 준 것을 그것을 상속받으면 된다. (eg. class SplayTree : public BST_template<SplayNode> {};)
//또한 우리가 일반적으로 사용할 이진 탐색 트리도 이 템플릿에 BST_node를 인자로 준 특수화된 경우로 class BST를 이 다음 클래스로 정의해놓았으니 그것을 사용하면 된다.
template <class NodeType = BST_node>
class BST_template {
protected :
	NodeType* head;

	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	NodeType* search(int target_key, NodeType* (BST_template::* to_do_with_target_ptr)(NodeType*&)) {
		if (head == NULL) return (this->*to_do_with_target_ptr)(head);
		else if (target_key == head->key) return (this->*to_do_with_target_ptr)(head);

		NodeType* search_ptr = head;
		while (true) {
			if (target_key < search_ptr->key) {
				if (search_ptr->lchild != NULL && search_ptr->lchild->key != target_key)  search_ptr = search_ptr->lchild;
				else return (this->*to_do_with_target_ptr)(search_ptr->lchild);
			}
			else {
				if (search_ptr->rchild != NULL && search_ptr->rchild->key != target_key)search_ptr = search_ptr->rchild;
				else return (this->*to_do_with_target_ptr)(search_ptr->rchild);
			}
		}
	}

	NodeType* get_T(NodeType*& parent_seat) {
		return parent_seat;
	}

	NodeType* set_dummy_child(NodeType*& parent_seat) {
		return parent_seat = new NodeType(0, 0);
	}

	NodeType* remove_target(NodeType*& target_ptr) {
		if (target_ptr->lchild != NULL && target_ptr->rchild != NULL) {				//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
			replace_with_inorder_successor(target_ptr);
		}
		else if (target_ptr->lchild == NULL && target_ptr->rchild != NULL) {
			replace_with_inorder_successor(target_ptr);
		}
		else if (target_ptr->lchild != NULL && target_ptr->rchild == NULL) {
			replace_with_inorder_predecessor(target_ptr);
		}
		else {
			delete target_ptr;
			target_ptr = NULL;
			return target_ptr;
		}
	}

	void replace_with_inorder_predecessor(NodeType*& target_ptr) {
		NodeType* previous_ptr = NULL;
		NodeType* traverse_ptr = target_ptr->lchild;
		while (traverse_ptr->rchild != NULL) {
			previous_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->rchild;
		}
		if (previous_ptr != NULL) previous_ptr->rchild = traverse_ptr->lchild;
		else target_ptr->lchild = traverse_ptr->lchild;
		target_ptr->key = traverse_ptr->key;
		target_ptr->data = traverse_ptr->data;
		delete traverse_ptr;
	}

	void replace_with_inorder_successor(NodeType*& target_ptr) {
		NodeType* previous_ptr = NULL;
		NodeType* traverse_ptr = target_ptr->rchild;
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


	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void preorder_traverse(void (*to_do_while_traverse)(NodeType*, BST_template*), BST_template* optional_target_BST) {
		if (head == NULL) return;

		Stack<NodeType*> head_stack;
		NodeType* traverse_ptr = NULL;
		head_stack.push(this->head);
		while ((traverse_ptr = head_stack.pop())) {
			(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
			if (traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
			if (traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
		}
	}

	void inorder_traverse(void (*to_do_while_traverse)(NodeType*, BST_template*), BST_template* optional_target_BST) {
		if (head == NULL) return;

		Stack<NodeType*> head_stack;
		head_stack.push(head);
		bool new_left_spine = true;
		while (!head_stack.is_empty()) {
			while (new_left_spine && head_stack.get_top()->lchild) {
				head_stack.push(head_stack.get_top()->lchild);
			}
			NodeType* traverse_ptr = head_stack.pop();
			(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
			if (traverse_ptr->rchild != NULL) {
				head_stack.push(traverse_ptr->rchild);
				new_left_spine = true;
			}
			else new_left_spine = false;
		}
	}

	void postorder_traverse(void (*to_do_while_traverse)(NodeType*, BST_template*), BST_template* optional_target_BST) {
		if (head == NULL) return;

		Stack<NodeType*> head_stack;
		head_stack.push(head);
		bool new_left_spine = true;
		bool new_right_spine = true;
		while (!head_stack.is_empty()) {
			while (new_left_spine && head_stack.get_top()->lchild) {
				head_stack.push(head_stack.get_top()->lchild);
			}
			if (new_right_spine && head_stack.get_top()->rchild) {
				head_stack.push(head_stack.get_top()->rchild);
				new_left_spine = true;
			}
			else {
				(*to_do_while_traverse)(head_stack.get_top(), optional_target_BST);
				new_left_spine = false;
				NodeType* previous_node = head_stack.pop();
				NodeType* present_node = head_stack.get_top();
				if (present_node && present_node->rchild && (present_node->rchild == previous_node)) new_right_spine = false;
				else new_right_spine = true;
			}
		}
	}

	static void print_node(NodeType* target_node, BST_template* dummy_argument) {
		cout << "node key : " << target_node->key << " / node data : " << target_node->data << endl;
	}

	static void remove_childs(NodeType* target_node, BST_template* dummy_argument) {
		if (target_node->lchild != NULL) {
			delete target_node->lchild;
			target_node->lchild = NULL;
		}
		if (target_node->rchild != NULL) {
			delete target_node->rchild;
			target_node->rchild = NULL;
		}
	}

	static void copy_node(NodeType* source_node, BST_template* dest_BST) {
		dest_BST->insert(source_node->key, source_node->data);
	}


public:
	BST_template() {
		cout << "BST is being made!" << endl;
		head = NULL;
	}

	~BST_template() {
		cout << "BST is being removed" << endl;
		remove_all();
	}

	void insert(int new_key, int new_data) {
		NodeType* made_child = search(new_key, &BST_template::set_dummy_child);
		made_child->key = new_key;
		made_child->data = new_data;
	}

	int retrieve(int target_key) {
		return search(target_key, &BST_template::get_T)->data;
	}

	void remove(int target_key) {
		search(target_key, &BST_template::remove_target);
	}

	void copy_from(BST_template* target_BST) {
		target_BST->preorder_traverse(&BST_template::copy_node, this);
	}

	void remove_all() {
		cout << "remove all" << endl;
		postorder_traverse(&BST_template::remove_childs, NULL);
		delete head;
		head = NULL;
	}

	void preorder_print() {
		cout << "preorder traverse start" << endl;
		preorder_traverse(&BST_template::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void inorder_print() {
		cout << "inorder traverse start" << endl;
		inorder_traverse(&BST_template::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void postorder_print() {
		cout << "postorder traverse start" << endl;
		postorder_traverse(&BST_template::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}
};


class BST : public BST_template<BST_node> {
public:
	BST() : BST_template() {}
};

#endif //BST_USING_WHILE_H