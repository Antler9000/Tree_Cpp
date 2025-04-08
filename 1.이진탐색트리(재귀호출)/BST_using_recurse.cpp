#include <iostream>
#include "BST_using_recurse.h"
using namespace std;

void BST::replace_with_inorder_predecessor(node* remove_target_node) {
	node* previous_ptr = NULL;
	node* traverse_ptr = remove_target_node->lchild;
	while (traverse_ptr->rchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->rchild;
	}
	if (previous_ptr != NULL) previous_ptr->rchild = traverse_ptr->lchild;
	else remove_target_node->lchild = traverse_ptr->lchild;
	remove_target_node->key = traverse_ptr->key;
	remove_target_node->data = traverse_ptr->data;
	delete traverse_ptr;
	if (previous_ptr != NULL) previous_ptr->rchild = NULL;
}

void BST::replace_with_inorder_successor(node* remove_target_node) {
	node* previous_ptr = NULL;
	node* traverse_ptr = remove_target_node->rchild;
	while (traverse_ptr->lchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->lchild;
	}
	if (previous_ptr != NULL) previous_ptr->lchild = traverse_ptr->rchild;
	else remove_target_node->rchild = traverse_ptr->rchild;
	remove_target_node->key = traverse_ptr->key;
	remove_target_node->data = traverse_ptr->data;
	delete traverse_ptr;
	if (previous_ptr != NULL) previous_ptr->lchild = NULL;
}

void BST::remove_target(node*& remove_target_node) {
	if (remove_target_node->lchild != NULL && remove_target_node->rchild != NULL) {								//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		replace_with_inorder_successor(remove_target_node);
	}
	else if (remove_target_node->lchild == NULL && remove_target_node->rchild != NULL) {
		replace_with_inorder_successor(remove_target_node);
	}
	else if (remove_target_node->lchild != NULL && remove_target_node->rchild == NULL) {
		replace_with_inorder_predecessor(remove_target_node);
	}
	else {
		delete remove_target_node;
		remove_target_node = NULL;
	}
}

void BST::insert_recurse(node* search_target_node, int new_key, int new_data) {
	if (new_key < search_target_node->key) {
		if(search_target_node->lchild == NULL) search_target_node->lchild = new node(new_key, new_data);
		else insert_recurse(search_target_node->lchild, new_key, new_data);
	}
	else if(search_target_node->key < new_key) {
		if (search_target_node->rchild == NULL) search_target_node->rchild = new node(new_key, new_data);
		else insert_recurse(search_target_node->rchild, new_key, new_data);
	}
	else {
		cout << "cannot insert! key is same! If it is dummy_room_node, then it is okay" << endl;
	}
}

int BST::retrieve_recurse(node* search_target_node, int retrieve_target_key) {
	if (retrieve_target_key < search_target_node->key) {
		if (search_target_node->lchild != NULL) return retrieve_recurse(search_target_node->lchild, retrieve_target_key);
		else  cout << "there is no such key in searching." << endl;
	}
	else if (retrieve_target_key > search_target_node->key) {
		if (search_target_node->rchild != NULL) return retrieve_recurse(search_target_node->rchild, retrieve_target_key);
		else  cout << "there is no such key in searching." << endl;
	}
	else {
		return search_target_node->data;
	}
}

void BST::remove_recurse(node* search_target_node, int remove_target_key) {
	if (remove_target_key < search_target_node->key) {
		if (search_target_node->lchild->key == remove_target_key) {
			remove_target(search_target_node->lchild);
		}
		else {
			remove_recurse(search_target_node->lchild, remove_target_key);
		}
	}
	else if (remove_target_key > search_target_node->key) {
		if (search_target_node->rchild->key == remove_target_key) {
			remove_target(search_target_node->rchild);
		}
		else {
			remove_recurse(search_target_node->rchild, remove_target_key);
		}
	}
	else {
		cout << "should not reach here while remove_recurse()" << endl;
	}
}


