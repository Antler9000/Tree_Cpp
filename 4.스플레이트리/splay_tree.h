#ifndef splay_tree_H
#define splay_tree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class splay_tree : public BST {
	void splay_target(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target);

	void L_rotation(BST_node* father_of_target, BST_node* target) {
		cout << "L rotation" << endl;
		head = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
	}

	void R_rotation(BST_node* father_of_target, BST_node* target) {
		cout << "R rotation" << endl;
		head = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
	}

	void LL_rotation(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "LL rotation" << endl;
		grandfather_of_target->lchild = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
	}

	void LR_rotation(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "LR rotation" << endl;
		grandfather_of_target->lchild = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
	}

	void RL_rotation(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "RL rotation" << endl;
		grandfather_of_target->rchild = target;
		father_of_target->lchild = target->rchild;
		target->rchild = father_of_target;
	}

	void RR_rotation(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
		cout << "RR rotation" << endl;
		grandfather_of_target->rchild = target;
		father_of_target->rchild = target->lchild;
		target->lchild = father_of_target;
	}


public :
	splay_tree() : BST() {}

	int retrieve(int target_key);
};

#endif //SPLAY_TREE_H