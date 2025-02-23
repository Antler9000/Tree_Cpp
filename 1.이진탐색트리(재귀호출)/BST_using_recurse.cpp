#include <iostream>
#include "BST_using_recurse.h"
using namespace std;

void BST::replace_with_inorder_predecessor() {
	BST* previous_ptr = NULL;
	BST* traverse_ptr = lchild;
	while (traverse_ptr->rchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->rchild;
	}
	if (previous_ptr != NULL) previous_ptr->rchild = traverse_ptr->lchild;
	else this->lchild = traverse_ptr->lchild;
	key = traverse_ptr->key;
	data = traverse_ptr->data;
	delete traverse_ptr;
	if (previous_ptr != NULL) previous_ptr->rchild = NULL;
}

void BST::replace_with_inorder_successor() {
	BST* previous_ptr = NULL;
	BST* traverse_ptr = rchild;
	while (traverse_ptr->lchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->lchild;
	}
	if (previous_ptr != NULL) previous_ptr->lchild = traverse_ptr->rchild;
	else this->rchild = traverse_ptr->rchild;
	key = traverse_ptr->key;
	data = traverse_ptr->data;
	delete traverse_ptr;
	if (previous_ptr != NULL) previous_ptr->lchild = NULL;
}

void BST::remove_target(BST*& target_child_variable) {
	if (lchild != NULL && rchild != NULL) {								//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		replace_with_inorder_successor();
	}
	else if (lchild == NULL && rchild != NULL) {
		replace_with_inorder_successor();
	}
	else if (lchild != NULL && rchild == NULL) {
		replace_with_inorder_predecessor();
	}
	else {
		delete target_child_variable;
		target_child_variable = NULL;
	}
}


int BST::retrieve(int target_key) {
	if (target_key < key) {
		if (lchild != NULL) return lchild->retrieve(target_key);
		else  cout << "there is no such key in searching." << endl;
	} 
	else if (key < target_key) {
		if (rchild != NULL) return rchild->retrieve(target_key);
		else  cout << "there is no such key in searching." << endl;
	}
	else {
		return data;
	}
}

void BST::insert(int new_key, int new_data) {
	if (new_key < key) {
		if(lchild == NULL) lchild = new BST(new_key, new_data);
		else lchild->insert(new_key, new_data);
	}
	else if(key < new_key) {
		if (rchild == NULL) rchild = new BST(new_key, new_data);
		else rchild->insert(new_key, new_data);
	}
	else {
		if (key != -1 || data != -1) cout << "cannot insert! key is same! If it is dummy_room_node, then it is okay" << endl;
	}
}

void BST::remove(int target_key) {	
	if (target_key < key) {
		if (lchild->key == target_key) {
			lchild->remove_target(lchild);
		}
		else {
			lchild->remove(target_key);
		}
	}
	else if (key < target_key) {
		if (rchild->key == target_key) {
			rchild->remove_target(rchild);
		}
		else {
			rchild->remove(target_key);
		}
	}
	else {
		cout << "should not reach here while removing!" << endl;
	}
}


