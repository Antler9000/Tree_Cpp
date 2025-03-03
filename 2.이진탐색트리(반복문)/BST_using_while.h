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
	//"to_do_with_target_ptr" �޼ҵ� �����ʹ� Ư�� target_key�� ���� ��带 ����Ű�� �ڽ� �����Ϳ� ������ �۾��̳�,
	//Ư�� target_key ��尡 ���Ե� �� �ִ� NULL �ڽ� �����Ϳ� ������ �۾��� �Ѱ��ִ� �������̽���.
	//����Ǵ� ����-�˻�-���������� �θ� �ڽ��� ����Ű�� ������ ������ ���� ������ �� �־�� �ϱ⿡, �޼ҵ� �����ʹ� ���۷��� ���ڸ� ����
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
		if (target_ptr->lchild != NULL && target_ptr->rchild != NULL) {				//�� �ڽ� ��� �ִ� ��쿣, ���������ڿ� �����ļ��� �߿��� �׳� �����ļ���(������ �ڽ� Ʈ������ ���� ���� Ű ���� ���)�� ���ֱ����
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


	//"to_do_while_traverse" �Լ� �����ʹ� ������ȸ�� ���鼭 �� ��忡 ������ �۾��� ���� �������̽���
	//"optional_target_BST" BST �����ʹ� �ռ� "to_do_while_traverse" �۾����� ��� BST �����Ͱ� �ʿ��� ��츦 ���� �μ���.
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

	//����
	void insert(int new_key, int new_data) {
		T* made_child = search(new_key, &BST::set_dummy_child);
		made_child->key = new_key;
		made_child->data = new_data;
	}

	//�˻�
	int retrieve(int target_key) {
		return search(target_key, &BST::get_T)->data;
	}

	//����
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