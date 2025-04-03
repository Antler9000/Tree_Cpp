#ifndef SplayTree_H
#define SplayTree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

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

	//ZIG의 경우에는 부모까지 변화가 일어나는 경우이므로, 부모를 가르키는 조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	//ZIG_ZIG나 ZIG_ZAG와 같이 조부까지 변화가 일어나는 경우를 위해, 조부를 가리키는 증조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
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