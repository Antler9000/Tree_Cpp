#ifndef TREE_USING_WHILE_H
#define TREE_USING_WHILE_H


#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	node* lchild;
	node* rchild;

	node(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	void set_key(int key) {
		this->key = key;
	}

	void set_data(int data) {
		this->data = data;
	}
};

//일단 스택이 가지는 아이템의 타입은 node*이고, 최대 개수는 100개라고 가정하고 어레이 구현을 사용함.
class stack {
	node* head_data[100];
	int item_num;

public:
	stack() {
		for (int i = 0; i < 100; i++) {
			head_data[i] = NULL;
		}
		item_num = 0;
	}

	void push(node* new_head) {
		if (item_num >= 99) {
			cout << "cannot push to stack. it is full!" << endl;
			return;
		}
		head_data[item_num] = new_head;
		item_num++;
	}

	node* pop() {
		if (item_num <= 0) {
			cout << "cannot pop from stack. it is emptied!" << endl;
			return NULL;
		}

		return head_data[--item_num];
	}

	node* get_top() {
		if (item_num <= 0) {
			cout << "cannot get top from stack. it is emptied!" << endl;
			return NULL;
		}

		return head_data[item_num - 1];
	}

	bool is_empty() {
		if (item_num <= 0) return true;
		else return false;
	}
};

class tree {
	node* head;

	//"to_do_with_target_node" 함수 포인터는 특정 target_key를 가진 트리상 노드에 수행할 작업을 위한 인터페이스임
	//"to_do_with_target_hole" 함수 포인터는 특정 target_key가 새로 삽입되기에 적합한 위치(자식 포인터 변수)에 수행할 작업을 위한 인터페이스임
	//두 함수 포인터 모두, 부모의 자식 포인터 변수를 직접 수정할 수 있도록 레퍼런스 인자를 가짐
	node* search(int target_key, node* (*to_do_with_target_node)(node*&), node* (*to_do_with_target_hole)(node*&));

	//"to_do' 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void preorder_traverse(void (*to_do)(node*));

	//"to_do' 함수 포인터는 중위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void inorder_traverse(void (*to_do)(node*));

	//"to_do' 함수 포인터는 후위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void postorder_traverse(void (*to_do)(node*));

	/*-----이 아래의 private 메소드들은 위 일반 메소드들(탐색, 순회)에 메소드 포인터(인터페이스)로 전달되어 동작하는 세부 메소드들임-----*/

	static void print_node(node* node_ptr) {
		cout << "node key : " << node_ptr->key << " / node data : " << node_ptr->data << endl;
	}

	static void remove_childs(node* node_ptr) {
		if (node_ptr->lchild) {
			delete node_ptr->lchild;
			node_ptr->lchild = NULL;
		}
		if (node_ptr->rchild) {
			delete node_ptr->rchild;
			node_ptr->rchild = NULL;
		}
	}

	static node* get_node(node*& parent_seat) {
		return parent_seat;
	}

	static node* set_dummy_child(node*& parent_seat) {
		return parent_seat = new node(0, 0);
	}

	static node* remove_target(node*& target_ptr) {
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

	static void replace_with_inorder_predecessor(node*& target_ptr);

	static void replace_with_inorder_successor(node*& target_ptr);

public:
	tree() {
		cout << "tree is being made!" << endl;
		head = NULL;
	}

	~tree() {
		cout << "tree is being removed" << endl;
		remove_all();
	}

	int get_data(int target_key) {
		node* target_node = search(target_key, &tree::get_node, NULL);
		return target_node->data;
	}

	node* insert(int new_key, int new_data) {
		node* made_child = search(new_key, NULL, &tree::set_dummy_child);
		made_child->set_key(new_key);
		made_child->set_data(new_data);
		return made_child;
	}

	void remove(int target_key) {
		search(target_key, &tree::remove_target, NULL);
	}

	void remove_all() {
		cout << "remove all" << endl;
		postorder_traverse(&tree::remove_childs);
		delete head;
		head = NULL;
	}

	void preorder_print() {
		cout << "preorder_traverse" << endl;
		preorder_traverse(&tree::print_node);
		cout << endl;
	}

	void inorder_print() {
		cout << "inorder_traverse" << endl;
		inorder_traverse(&tree::print_node);
		cout << endl;
	}

	void postorder_print() {
		cout << "postorder_traverse" << endl;
		postorder_traverse(&tree::print_node);
		cout << endl;
	}
};

#endif //TREE_USING_WHILE_H