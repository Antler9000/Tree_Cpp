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
};

class tree {
	tree_node* head;

	//"to_do_with_target_tree_node" 함수 포인터는 특정 target_key를 가진 트리상 노드에 수행할 작업을 위한 인터페이스임
	//"to_do_with_target_hole" 함수 포인터는 특정 target_key가 새로 삽입되기에 적합한 위치(자식 포인터 변수)에 수행할 작업을 위한 인터페이스임
	//두 함수 포인터 모두, 부모의 자식 포인터 변수를 직접 수정할 수 있도록 레퍼런스 인자를 가짐
	tree_node* search(int target_key, tree_node* (*to_do_with_target_tree_node)(tree_node*&), tree_node* (*to_do_with_target_hole)(tree_node*&));

	//"to_do_while_traverse" 함수 포인터는 전위순회로 돌면서 각 노드에 수행할 작업을 위한 인터페이스임
	//"optional_target_tree" 트리 포인터는 앞선 "to_do_while_traverse" 작업에서 대상 트리 포인터가 필요한 경우를 위한 인수임.
	// (eg: 기존 'A' 트리를 순회하며 각 노드를 'B' 트리에 복사 삽입할 때'B' 트리를 가리키기 위한 포인터임)
	void preorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	void inorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	void postorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	/*-----이 아래의 private 메소드들은 위 일반 메소드들(탐색, 순회)에 메소드 포인터(인터페이스)로 전달되어 동작하는 세부 메소드나 그 메소드의 하위 메소드들임-----*/

	static void print_tree_node(tree_node* target_node, tree* dummy_argument) {
		cout << "tree_node key : " << target_node->key << " / tree_node data : " << target_node->data << endl;
	}

	static void remove_childs(tree_node* target_node, tree* dummy_argument) {
		if (target_node->lchild != NULL) {
			delete target_node->lchild;
			target_node->lchild = NULL;
		}
		if (target_node->rchild != NULL) {
			delete target_node->rchild;
			target_node->rchild = NULL;
		}
	}

	static void copy_node(tree_node* source_node, tree* dest_tree) {
		dest_tree->insert(source_node->key, source_node->data);
	}

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

	void insert(int new_key, int new_data) {
		tree_node* made_child = search(new_key, NULL, &tree::set_dummy_child);
		made_child->key = new_key;
		made_child->data = new_data;
	}

	void copy_from(tree* target_tree) {
		target_tree->preorder_traverse(&tree::copy_node, this);
	}

	void remove(int target_key) {
		search(target_key, &tree::remove_target, NULL);
	}

	void remove_all() {
		cout << "remove all" << endl;
		postorder_traverse(&tree::remove_childs, NULL);
		delete head;
		head = NULL;
	}

	void preorder_print() {
		cout << "preorder_traverse" << endl;
		preorder_traverse(&tree::print_tree_node, NULL);
		cout << endl;
	}

	void inorder_print() {
		cout << "inorder_traverse" << endl;
		inorder_traverse(&tree::print_tree_node, NULL);
		cout << endl;
	}

	void postorder_print() {
		cout << "postorder_traverse" << endl;
		postorder_traverse(&tree::print_tree_node, NULL);
		cout << endl;
	}
};

#endif //BST_USING_WHILE_H