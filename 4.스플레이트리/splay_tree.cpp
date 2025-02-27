#include"splay_tree.h"

int splay_tree::retrieve(int target_key) {
	BST_node* traverse_ptr = head;
	BST_node* father_of_traverse_ptr = NULL;
	BST_node* grandfather_of_traverse_ptr = NULL;
	while (traverse_ptr != NULL) {
		if (target_key < traverse_ptr->key) {
			grandfather_of_traverse_ptr = father_of_traverse_ptr;
			father_of_traverse_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->lchild;
		}
		else if (traverse_ptr->key < target_key) {
			grandfather_of_traverse_ptr = father_of_traverse_ptr;
			father_of_traverse_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->rchild;
		}
		else {
			splay_target(grandfather_of_traverse_ptr, father_of_traverse_ptr, traverse_ptr);
			return traverse_ptr->data;
		}
	}
}

void splay_tree::splay_target(BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
	if (grandfather_of_target != NULL) {
		if (grandfather_of_target->lchild == father_of_target) {
			if (father_of_target->lchild == target) LL_rotation(grandfather_of_target, father_of_target, target);
			else	 LR_rotation(grandfather_of_target, father_of_target, target);
		}
		else {
			if (father_of_target->lchild == target) RL_rotation(grandfather_of_target, father_of_target, target);
			else RR_rotation(grandfather_of_target, father_of_target, target);
		}
	}
	else if (father_of_target != NULL) {
		if (head->lchild == target) L_rotation(father_of_target, target);
		else R_rotation(father_of_target, target);
	}
	else {
		//We cannot splay the head. So, let's do nothing.
	}
}