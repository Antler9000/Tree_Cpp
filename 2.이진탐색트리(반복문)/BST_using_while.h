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

	//"to_do_with_target_tree_node" �Լ� �����ʹ� Ư�� target_key�� ���� Ʈ���� ��忡 ������ �۾��� ���� �������̽���
	//"to_do_with_target_hole" �Լ� �����ʹ� Ư�� target_key�� ���� ���ԵǱ⿡ ������ ��ġ(�ڽ� ������ ����)�� ������ �۾��� ���� �������̽���
	//�� �Լ� ������ ���, �θ��� �ڽ� ������ ������ ���� ������ �� �ֵ��� ���۷��� ���ڸ� ����
	tree_node* search(int target_key, tree_node* (*to_do_with_target_tree_node)(tree_node*&), tree_node* (*to_do_with_target_hole)(tree_node*&));

	//"to_do_while_traverse" �Լ� �����ʹ� ������ȸ�� ���鼭 �� ��忡 ������ �۾��� ���� �������̽���
	//"optional_target_tree" Ʈ�� �����ʹ� �ռ� "to_do_while_traverse" �۾����� ��� Ʈ�� �����Ͱ� �ʿ��� ��츦 ���� �μ���.
	// (eg: ���� 'A' Ʈ���� ��ȸ�ϸ� �� ��带 'B' Ʈ���� ���� ������ ��'B' Ʈ���� ����Ű�� ���� ��������)
	void preorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	void inorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	void postorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree);

	/*-----�� �Ʒ��� private �޼ҵ���� �� �Ϲ� �޼ҵ��(Ž��, ��ȸ)�� �޼ҵ� ������(�������̽�)�� ���޵Ǿ� �����ϴ� ���� �޼ҵ峪 �� �޼ҵ��� ���� �޼ҵ����-----*/

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