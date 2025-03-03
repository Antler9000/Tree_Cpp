#ifndef splay_tree_H
#define splay_tree_H

#include "../2.����Ž��Ʈ��(�ݺ���)/BST_using_while.h"

class splay_node {
	friend class splay_tree;
	friend class BST<splay_node>;
	int key;
	int data;
	splay_node* lchild;
	splay_node* rchild;

	splay_node(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class splay_tree : public BST<splay_node> {
	void splay_target(splay_node* greatgrandfather_of_traverse_ptr, splay_node* grandfather_of_target, splay_node* father_of_target, splay_node* target);

	//ZIG�� ��쿡�� �θ���� ��ȭ�� �Ͼ�� ����̹Ƿ�, �θ� ����Ű�� ������ �ڽ� �����͸� ���� ������ �� �ֵ��� ���۷��� ���ڸ� ����Ͽ���.
	//ZIG_ZIG�� ZIG_ZAG�� ���� ���α��� ��ȭ�� �Ͼ�� ��츦 ����, ���θ� ����Ű�� �������� �ڽ� �����͸� ���� ������ �� �ֵ��� ���۷��� ���ڸ� ����Ͽ���.
	void L_ZIG(splay_node*& father_of_target, splay_node* target) {
		cout << "L_ZIG" << endl;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		father_of_target = target;
	}

	void R_ZIG(splay_node*& father_of_target, splay_node* target) {
		cout << "R_ZIG" << endl;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
		father_of_target = target;
	}

	void LL_ZIG_ZIG(splay_node*& grandfather_of_target, splay_node* father_of_target, splay_node* target) {
		cout << "LL_ZIG_ZIG" << endl;
		grandfather_of_target->lchild = father_of_target->rchild;
		father_of_target->rchild = grandfather_of_target;
		grandfather_of_target = father_of_target;

		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		grandfather_of_target = target;
	}

	void LR_ZIG_ZAG(splay_node*& grandfather_of_target, splay_node* father_of_target, splay_node* target) {
		cout << "LR_ZIG_ZAG" << endl;
		cout << grandfather_of_target->key << " " << father_of_target->key << " " << target->key << endl;
		grandfather_of_target->lchild = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;

		grandfather_of_target->lchild = target->rchild;
		target->rchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RL_ZIG_ZAG(splay_node*& grandfather_of_target, splay_node* father_of_target, splay_node* target) {
		cout << "RL_ZIG_ZAG" << endl;
		grandfather_of_target->rchild = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;

		grandfather_of_target->rchild = target->lchild;
		target->lchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RR_ZIG_ZIG(splay_node*& grandfather_of_target, splay_node* father_of_target, splay_node* target) {
		cout << "RR_ZIG_ZIG" << endl;
		grandfather_of_target->rchild = father_of_target->lchild;
		father_of_target->lchild = grandfather_of_target;
		grandfather_of_target = father_of_target;

		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
		grandfather_of_target = target;
	}


public :
	splay_tree() : BST() {}

	int retrieve(int target_key);
};

#endif //SPLAY_TREE_H