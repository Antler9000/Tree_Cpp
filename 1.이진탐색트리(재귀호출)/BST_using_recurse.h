#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;

class BST;

class node {
	int data;
	int key;
	node* lchild;
	node* rchild;

	friend BST;

	node(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	~node() {
		delete lchild;
		delete rchild;
	}
};

class BST {
	node* head;

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꿔야하므로, 레퍼런스 인자로 받음
	void remove_target(node*& remove_target_node);

	void replace_with_inorder_predecessor(node* remove_target_node);

	void replace_with_inorder_successor(node* remove_target_node);

public:
	BST() {
		head = NULL;
	}

	~BST() {
		remove_all();
	}

	//삽입
	void insert(int new_key, int new_data) {
		cout << "inserting node.... (key : " << new_key << ", data : " << new_data << " )" << endl;
		if (head == NULL) {
			head = new node(new_key, new_data);
		}
		else {
			insert_recurse(head, new_key, new_data);
		}
		cout << "insert ended" << endl;
	}

	void insert_recurse(node* search_target_node, int new_key, int new_data);

	//검색
	int retrieve(int retrieve_target_key) {
		if (head == NULL) {
			cout << "cannot retrieve. becuase tree is null." << endl;
			return -1;
		}

		cout << "retrieving node.... (key : " << retrieve_target_key << " )" << endl;
		int retrieve_value = retrieve_recurse(head, retrieve_target_key);
		cout << "retrieving ended" << endl;
		return retrieve_value;
	}

	int retrieve_recurse(node* search_target_node, int retrieive_target_key);

	//삭제
	void remove(int remove_target_key) {
		if (head == NULL) {
			cout << "cannot remove. becuase tree is null." << endl;
			return;
		}
		
		if (head->key == remove_target_key) {
			remove_target(head);
		}
		else {
			cout << "removing node.... (key : " << remove_target_key << " )" << endl;
			remove_recurse(head, remove_target_key);
			cout << "removing ended" << endl;
		}
	}

	void remove_recurse(node* search_target_node, int remove_target_key);

	//트리 복사
	void copy_from(BST* source_BST) {		
		if (source_BST == NULL) {
			cout << "cannot copying. becuase tree is null." << endl;
			return;
		}
		
		if (source_BST->head == NULL) {
			cout << "cannot coping. becuase head is null." << endl;
			return;
		}

		cout << "copying tree..." << endl;
		copy_from_recurse(source_BST->head);
		cout << "copying dended" << endl;
	}

	void copy_from_recurse(node* source_node) {
		insert(source_node->key, source_node->data);
		if (source_node->lchild != NULL) copy_from_recurse(source_node->lchild);
		if (source_node->rchild != NULL) copy_from_recurse(source_node->rchild);
	}

	//트리 삭제
	void remove_all() {
		delete head;
		head = NULL;
	}

	//전위 순회
	void preorder_print() {
		if (head == NULL) {
			cout << "cannot traverse print. becuase head is null." << endl;
			return;
		}

		cout << "preorder traverse..." << endl;
		preorder_print_recurse(head);
		cout << "traverse ended" << endl;
	}

	void preorder_print_recurse(node* target_node) {
		cout << "node key : " << target_node->key << " / node data : " << target_node->data << endl;
		if (target_node->lchild != NULL) preorder_print_recurse(target_node->lchild);
		if (target_node->rchild != NULL) preorder_print_recurse(target_node->rchild);
	}

	//중위 순회
	void inorder_print() {
		if (head == NULL) {
			cout << "cannot traverse print. becuase head is null." << endl;
			return;
		}

		cout << "inorder traverse..." << endl;
		inorder_print_recurse(head);
		cout << "traverse ended" << endl;
	}

	void inorder_print_recurse(node* target_node) {
		if (target_node->lchild != NULL) inorder_print_recurse(target_node->lchild);
		cout << "node key : " << target_node->key << " / node data : " << target_node->data << endl;
		if (target_node->rchild != NULL) inorder_print_recurse(target_node->rchild);
	}

	//후위 순회
	void postorder_print() {
		if (head == NULL) {
			cout << "cannot traverse print. becuase head is null." << endl;
			return;
		}

		cout << "postorder traverse..." << endl;
		postorder_print_recurse(head);
		cout << "traverse ended" << endl;
	}

	void postorder_print_recurse(node* target_node) {
		if (target_node->lchild != NULL) postorder_print_recurse(target_node->lchild);
		if (target_node->rchild != NULL) postorder_print_recurse(target_node->rchild);
		cout << "node key : " << target_node->key << " / node data : " << target_node->data << endl;
	}

};

#endif //BST_USING_RECURSE_H