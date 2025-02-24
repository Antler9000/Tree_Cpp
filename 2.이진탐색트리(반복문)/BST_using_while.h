#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "stack.h"

class BST_node {
	friend class BST;
	friend class splay_tree;
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

class BST {
protected :
	BST_node* head;

private :
	//"to_do_with_target_ptr" 메소드 포인터는 특정 target_key를 가진 노드를 가리키는 자식 포인터에 수행할 작업이나,
	//특정 target_key 노드가 삽입될 수 있는 NULL 자식 포인터에 수행할 작업을 넘겨주는 인터페이스임.
	//응용되는 삽입-검색-삭제에서는 부모가 자식을 가리키는 포인터 변수를 직접 수정할 수 있어야 하기에, 메소드 포인터는 레퍼런스 인자를 가짐
	BST_node* search(int target_key, BST_node* (BST::*to_do_with_target_ptr)(BST_node*&));

	BST_node* get_BST_node(BST_node*& parent_seat) {
		return parent_seat;
	}

	BST_node* set_dummy_child(BST_node*& parent_seat) {
		return parent_seat = new BST_node(0, 0);
	}

	BST_node* remove_target(BST_node*& target_ptr);

	void replace_with_inorder_predecessor(BST_node*& target_ptr);

	void replace_with_inorder_successor(BST_node*& target_ptr);


	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_BST" BST 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 BST 포인터가 필요한 경우를 위한 인수임.
	void preorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST);

	void inorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST);

	void postorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST);

	static void print_BST_node(BST_node* target_node, BST* dummy_argument) {
		cout << "BST_node key : " << target_node->key << " / BST_node data : " << target_node->data << endl;
	}

	static void remove_childs(BST_node* target_node, BST* dummy_argument) {
		if (target_node->lchild != NULL) {
			delete target_node->lchild;
			target_node->lchild = NULL;
		}
		if (target_node->rchild != NULL) {
			delete target_node->rchild;
			target_node->rchild = NULL;
		}
	}

	static void copy_node(BST_node* source_node, BST* dest_BST) {
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
		BST_node* made_child = search(new_key, &BST::set_dummy_child);
		made_child->key = new_key;
		made_child->data = new_data;
	}

	//검색
	int retrieve(int target_key) {
		return search(target_key, &BST::get_BST_node)->data;
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
		preorder_traverse(&BST::print_BST_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void inorder_print() {
		cout << "inorder traverse start" << endl;
		inorder_traverse(&BST::print_BST_node, NULL);
		cout << "traverse ended" << endl << endl;
	}

	void postorder_print() {
		cout << "postorder traverse start" << endl;
		postorder_traverse(&BST::print_BST_node, NULL);
		cout << "traverse ended" << endl << endl;
	}
};

#endif //BST_USING_WHILE_H