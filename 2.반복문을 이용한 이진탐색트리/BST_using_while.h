#ifndef BST_USING_WHILE_H
#define BST_USING_WHILE_H

#include "stack.h"

class tree_node {
	friend class tree;
	int key;
	int data;
	tree_node* lchild;
	tree_node* rchild;

	tree_node(int key, int data) {
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

class tree {
	tree_node* head;

	//"to_do_with_target_tree_node" 함수 포인터는 특정 target_key를 가진 트리상 노드에 수행할 작업을 위한 인터페이스임
	//"to_do_with_target_hole" 함수 포인터는 특정 target_key가 새로 삽입되기에 적합한 위치(자식 포인터 변수)에 수행할 작업을 위한 인터페이스임
	//두 함수 포인터 모두, 부모의 자식 포인터 변수를 직접 수정할 수 있도록 레퍼런스 인자를 가짐
	tree_node* search(int target_key, tree_node* (*to_do_with_target_tree_node)(tree_node*&), tree_node* (*to_do_with_target_hole)(tree_node*&));

	//"to_do' 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void preorder_traverse(void (*to_do)(tree_node*));

	//"to_do' 함수 포인터는 중위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void inorder_traverse(void (*to_do)(tree_node*));

	//"to_do' 함수 포인터는 후위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	void postorder_traverse(void (*to_do)(tree_node*));

	/*-----이 아래의 private 메소드들은 위 일반 메소드들(탐색, 순회)에 메소드 포인터(인터페이스)로 전달되어 동작하는 세부 메소드들임-----*/

	static void print_tree_node(tree_node* tree_node_ptr) {
		cout << "tree_node key : " << tree_node_ptr->key << " / tree_node data : " << tree_node_ptr->data << endl;
	}

	static void remove_childs(tree_node* tree_node_ptr);

	static tree_node* get_tree_node(tree_node*& parent_seat) {
		return parent_seat;
	}

	static tree_node* set_dummy_child(tree_node*& parent_seat) {
		return parent_seat = new tree_node(0, 0);
	}

	static tree_node* remove_target(tree_node*& target_ptr);

	static void replace_with_inorder_predecessor(tree_node*& target_ptr);

	static void replace_with_inorder_successor(tree_node*& target_ptr);

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
		tree_node* target_tree_node = search(target_key, &tree::get_tree_node, NULL);
		return target_tree_node->data;
	}

	tree_node* insert(int new_key, int new_data) {
		tree_node* made_child = search(new_key, NULL, &tree::set_dummy_child);
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
		preorder_traverse(&tree::print_tree_node);
		cout << endl;
	}

	void inorder_print() {
		cout << "inorder_traverse" << endl;
		inorder_traverse(&tree::print_tree_node);
		cout << endl;
	}

	void postorder_print() {
		cout << "postorder_traverse" << endl;
		postorder_traverse(&tree::print_tree_node);
		cout << endl;
	}
};

#endif //BST_USING_WHILE_H