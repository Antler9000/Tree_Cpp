#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "stack.h"

template <class T>
class BST;

class BST_node {
	friend class BST<BST_node>;
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

template <class T = BST_node>
class BST {
protected :
	T* head;

private :
	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	T* search(int target_key, T* (BST::* to_do_with_target_ptr)(T*&)) {
		if (head == NULL) return (this->*to_do_with_target_ptr)(head);
		else if (target_key == head->key) return (this->*to_do_with_target_ptr)(head);

		T* search_ptr = head;
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

	T* get_T(T*& parent_seat) {
		return parent_seat;
	}

	T* set_dummy_child(T*& parent_seat) {
		return parent_seat = new T(0, 0);
	}

	T* remove_target(T*& target_ptr) {
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

	void replace_with_inorder_predecessor(T*& target_ptr) {
		T* previous_ptr = NULL;
		T* traverse_ptr = target_ptr->lchild;
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

	void replace_with_inorder_successor(T*& target_ptr) {
		T* previous_ptr = NULL;
		T* traverse_ptr = target_ptr->rchild;
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
	void preorder_traverse(void (*to_do_while_traverse)(T*, BST*), BST* optional_target_BST) {
		if (head == NULL) return;

		stack<T*> head_stack;
		T* traverse_ptr = NULL;
		head_stack.push(this->head);
		while ((traverse_ptr = head_stack.pop())) {
			(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
			if (traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
			if (traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
		}
	}

	void inorder_traverse(void (*to_do_while_traverse)(T*, BST*), BST* optional_target_BST) {
		if (head == NULL) return;

		stack<T*> head_stack;
		head_stack.push(head);
		bool new_left_spine = true;
		while (!head_stack.is_empty()) {
			while (new_left_spine && head_stack.get_top()->lchild) {
				head_stack.push(head_stack.get_top()->lchild);
			}
			T* traverse_ptr = head_stack.pop();
			(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
			if (traverse_ptr->rchild != NULL) {
				head_stack.push(traverse_ptr->rchild);
				new_left_spine = true;
			}
			else new_left_spine = false;
		}
	}

	void postorder_traverse(void (*to_do_while_traverse)(T*, BST*), BST* optional_target_BST) {
		if (head == NULL) return;

		stack<T*> head_stack;
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
				T* previous_node = head_stack.pop();
				T* present_node = head_stack.get_top();
				if (present_node && present_node->rchild && (present_node->rchild == previous_node)) new_right_spine = false;
				else new_right_spine = true;
			}
		}
	}

	static void print_node(T* target_node, BST* dummy_argument) {
		cout << "node key : " << target_node->key << " / node data : " << target_node->data << endl;
	}

	static void remove_childs(T* target_node, BST* dummy_argument) {
		if (target_node->lchild != NULL) {
			delete target_node->lchild;
			target_node->lchild = NULL;
		}
		if (target_node->rchild != NULL) {
			delete target_node->rchild;
			target_node->rchild = NULL;
		}
	}

	static void copy_node(T* source_node, BST* dest_BST) {
		dest_BST->insert(source_node->key, source_node->data);
	}


public:
	BST() {
		cout << "BST is being made!" << endl;
		head = NULL;
	}

	~BST() {
		cout << "BST is being removed" << endl;
		remove_all();
	}

	//삽입
	void insert(int new_key, int new_data) {
		T* made_child = search(new_key, &BST::set_dummy_child);
		made_child->key = new_key;
		made_child->data = new_data;
	}

	//검색
	int retrieve(int target_key) {
		return search(target_key, &BST::get_T)->data;
	}

	//삭제
	void remove(int target_key) {
		search(target_key, &BST::remove_target);
	}

	void copy_from(BST* target_BST) {
		target_BST->preorder_traverse(&BST::copy_node, this);
	}

	void remove_all() {
		cout << "remove all" << endl;
		postorder_traverse(&BST::remove_childs, NULL);
		delete head;
		head = NULL;
	}

	void preorder_print() {
		cout << "preorder traverse start" << endl;
		preorder_traverse(&BST::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void inorder_print() {
		cout << "inorder traverse start" << endl;
		inorder_traverse(&BST::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void postorder_print() {
		cout << "postorder traverse start" << endl;
		postorder_traverse(&BST::print_node, NULL);
		cout << "traverse ended" << endl << endl;
	}
};

#endif //BST_USING_WHILE_H