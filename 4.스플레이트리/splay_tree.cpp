#include"splay_tree.h"

void splay_tree::LL_rotation() {

}

void splay_tree::RR_rotation() {

}


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
			if (grandfather_of_traverse_ptr != NULL) {
				if (grandfather_of_traverse_ptr->lchild == father_of_traverse_ptr) {
					if (father_of_traverse_ptr->lchild == traverse_ptr) {	//LL rotation
						cout << "LL rotation" << endl;
					}
					else {											//LR	rotation
						cout << "LR rotation" << endl;
					}
				}
				else {
					if (father_of_traverse_ptr->lchild == traverse_ptr) {	//RL roation
						cout << "RL rotation" << endl;
					}
					else {											//RR rotation
						cout << "RR rotation" << endl;
					}
				}
			}
			else if (father_of_traverse_ptr != NULL) {
				if (head->lchild == traverse_ptr) {
					cout << "L rotation" << endl;					//L rotation
				}
				else {											//R rotation
					cout << "R rotation" << endl;
				}
			}
			return traverse_ptr->data;
		}
	}
}
