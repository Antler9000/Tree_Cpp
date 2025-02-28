#include"splay_tree.h"

int splay_tree::retrieve(int target_key) {
	BST_node* traverse_ptr = head;
	BST_node* father_of_traverse_ptr = NULL;
	BST_node* grandfather_of_traverse_ptr = NULL;
	BST_node* greatgrandfather_of_traverse_ptr = NULL;
	while (traverse_ptr != NULL) {
		if (target_key < traverse_ptr->key) {
			greatgrandfather_of_traverse_ptr = grandfather_of_traverse_ptr;
			grandfather_of_traverse_ptr = father_of_traverse_ptr;
			father_of_traverse_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->lchild;
		}
		else if (traverse_ptr->key < target_key) {
			greatgrandfather_of_traverse_ptr = grandfather_of_traverse_ptr;
			grandfather_of_traverse_ptr = father_of_traverse_ptr;
			father_of_traverse_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->rchild;
		}
		else {
			splay_target(greatgrandfather_of_traverse_ptr, grandfather_of_traverse_ptr, father_of_traverse_ptr, traverse_ptr);
			return traverse_ptr->data;
		}
	}
}

void splay_tree::splay_target(BST_node* greatgrandfather_of_traverse_ptr, BST_node* grandfather_of_target, BST_node* father_of_target, BST_node* target) {
	if (greatgrandfather_of_traverse_ptr != NULL) {
		if (greatgrandfather_of_traverse_ptr->lchild == grandfather_of_target) {
			if (grandfather_of_target->lchild == father_of_target) {
				if (father_of_target->lchild == target) LL_ZIG_ZIG(greatgrandfather_of_traverse_ptr->lchild, father_of_target, target);
				else	 LR_ZIG_ZAG(greatgrandfather_of_traverse_ptr->lchild, father_of_target, target);
			}
			else {
				if (father_of_target->lchild == target) RL_ZIG_ZAG(greatgrandfather_of_traverse_ptr->lchild, father_of_target, target);
				else RR_ZIG_ZIG(greatgrandfather_of_traverse_ptr->lchild, father_of_target, target);
			}
		}
		else {
			if (grandfather_of_target->lchild == father_of_target) {
				if (father_of_target->lchild == target) LL_ZIG_ZIG(greatgrandfather_of_traverse_ptr->rchild, father_of_target, target);
				else	 LR_ZIG_ZAG(greatgrandfather_of_traverse_ptr->rchild, father_of_target, target);
			}
			else {
				if (father_of_target->lchild == target) RL_ZIG_ZAG(greatgrandfather_of_traverse_ptr->rchild, father_of_target, target);
				else RR_ZIG_ZIG(greatgrandfather_of_traverse_ptr->rchild, father_of_target, target);
			}
		}
	}
	else if (grandfather_of_target != NULL) {
		if (grandfather_of_target->lchild == father_of_target) {
			if (father_of_target->lchild == target) LL_ZIG_ZIG(head, father_of_target, target);
			else	 LR_ZIG_ZAG(head, father_of_target, target);
		}
		else {
			if (father_of_target->lchild == target) RL_ZIG_ZAG(head, father_of_target, target);
			else RR_ZIG_ZIG(head, father_of_target, target);
		}
	}
	else if (father_of_target != NULL) {
		if (father_of_target->lchild == target) L_ZIG(head, target);
		else R_ZIG(head, target);
	}
	else {
		//We cannot splay the head. So, let's do nothing.
	}
}