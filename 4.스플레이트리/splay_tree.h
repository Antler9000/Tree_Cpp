#ifndef splay_tree_H
#define splay_tree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class splay_tree : public BST {
	void splay_target(BST_node* greatgrandfather_of_traverse_ptr, BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target);

	//ZIG의 경우에는 부모까지 변화가 일어나는 경우이므로, 부모를 가르키는 조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	//ZIG_ZIG나 ZIG_ZAG와 같이 조부까지 변화가 일어나는 경우를 위해, 조부를 가리키는 증조부의 자식 포인터를 직접 수정할 수 있도록 레퍼런스 인자를 사용하였다.
	void L_ZIG(BST_node*& father_of_target, BST_node* target) {
		cout << "L_ZIG" << endl;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		father_of_target = target;
	}

	void R_ZIG(BST_node*& father_of_target, BST_node* target) {
		cout << "R_ZIG" << endl;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
		father_of_target = target;
	}

	void LL_ZIG_ZIG(BST_node*& grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "LL_ZIG_ZIG" << endl;
		grandfather_of_target->lchild = father_of_target->rchild;
		father_of_target->rchild = grandfather_of_target;
		grandfather_of_target = father_of_target;

		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
		grandfather_of_target = target;
	}

	void LR_ZIG_ZAG(BST_node*& grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "LR_ZIG_ZAG" << endl;
		cout << grandfather_of_target->key << " " << father_of_target->key << " " << target->key << endl;
		grandfather_of_target->lchild = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;

		grandfather_of_target->lchild = target->rchild;
		target->rchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RL_ZIG_ZAG(BST_node*& grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "RL_ZIG_ZAG" << endl;
		grandfather_of_target->rchild = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;

		grandfather_of_target->rchild = target->lchild;
		target->lchild = grandfather_of_target;
		grandfather_of_target = target;
	}

	void RR_ZIG_ZIG(BST_node*& grandfather_of_target, BST_node* father_of_target, BST_node* target) {
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