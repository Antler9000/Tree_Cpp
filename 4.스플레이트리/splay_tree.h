#ifndef SplayTree_H
#define SplayTree_H

#include "../2.����Ž��Ʈ��(�ݺ���)/BST_using_while.h"

class SplayNode {
	friend class SplayTree;
	friend class BST_template<SplayNode>;
	int key;
	int data;
	SplayNode* lchild;
	SplayNode* rchild;

	SplayNode(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	inline void print_node() {
		cout << "node key : " << key << " / node data : " << data << endl;
	}
};

class SplayTree : public BST_template<SplayNode> {
	void splay_target(SplayNode* greatgrandfather_of_traverse_ptr, SplayNode* grandfather_of_target, SplayNode* father_of_target, SplayNode* target);

	//ZIG�� ��쿡�� �θ���� ��ȭ�� �Ͼ�� ����̹Ƿ�, �θ� ����Ű�� ������ �ڽ� �����͸� ���� ������ �� �ֵ��� ���۷��� ���ڸ� ����Ͽ���.
	//ZIG_ZIG�� ZIG_ZAG�� ���� ���α��� ��ȭ�� �Ͼ�� ��츦 ����, ���θ� ����Ű�� �������� �ڽ� �����͸� ���� ������ �� �ֵ��� ���۷��� ���ڸ� ����Ͽ���.
	void L_ZIG(SplayNode*& father_of_target, SplayNode* target) {
		cout << "L_ZIG" << endl;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		father_of_target = target;
	}

	void R_ZIG(SplayNode*& father_of_target, SplayNode* target) {
		cout << "R_ZIG" << endl;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
		father_of_target = target;
	}

	void LL_ZIG_ZIG(SplayNode*& grandfather_of_target, SplayNode* father_of_target, SplayNode* target) {
		cout << "LL_ZIG_ZIG" << endl;
		grandfather_of_target->lchild = father_of_target->rchild;
		father_of_target->rchild = grandfather_of_target;
		grandfather_of_target = father_of_target;

		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		grandfather_of_target = target;
	}

	void LR_ZIG_ZAG(SplayNode*& grandfather_of_target, SplayNode* father_of_target, SplayNode* target) {
		cout << "LR_ZIG_ZAG" << endl;
		cout << grandfather_of_target->key << " " << father_of_target->key << " " << target->key << endl;
		grandfather_of_target->lchild = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;

		grandfather_of_target->lchild = target->rchild;
		target->rchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RL_ZIG_ZAG(SplayNode*& grandfather_of_target, SplayNode* father_of_target, SplayNode* target) {
		cout << "RL_ZIG_ZAG" << endl;
		grandfather_of_target->rchild = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;

		grandfather_of_target->rchild = target->lchild;
		target->lchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RR_ZIG_ZIG(SplayNode*& grandfather_of_target, SplayNode* father_of_target, SplayNode* target) {
		cout << "RR_ZIG_ZIG" << endl;
		grandfather_of_target->rchild = father_of_target->lchild;
		father_of_target->lchild = grandfather_of_target;
		grandfather_of_target = father_of_target;

		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
		grandfather_of_target = target;
	}


public :
	SplayTree() : BST_template() {}

	int retrieve(int target_key);
};

#endif //SPLAY_TREE_H