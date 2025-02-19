#include <iostream>
#include "BST_using_recurse.h"
using namespace std;

void tree::replace_with_inorder_predecessor() {
	tree* previous_ptr = NULL;
	tree* traverse_ptr = head->lchild;
	while (traverse_ptr->head->rchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->head->rchild;
	}
	if (previous_ptr != NULL) previous_ptr->head->rchild = traverse_ptr->head->lchild;
	else this->head->lchild = traverse_ptr->head->lchild;
	head->key = traverse_ptr->head->key;
	head->data = traverse_ptr->head->data;
	delete traverse_ptr;
}

void tree::replace_with_inorder_successor() {
	tree* previous_ptr = NULL;
	tree* traverse_ptr = head->rchild;
	while (traverse_ptr->head->lchild != NULL) {
		previous_ptr = traverse_ptr;
		traverse_ptr = traverse_ptr->head->lchild;
	}
	if (previous_ptr != NULL) previous_ptr->head->lchild = traverse_ptr->head->rchild;
	else this->head->rchild = traverse_ptr->head->rchild;
	head->key = traverse_ptr->head->key;
	head->data = traverse_ptr->head->data;
	delete traverse_ptr;
}

int tree::get_data(int target_key) {
	if (head == NULL) {
		cout << "can not search. there is no such key." << endl;
		return -1;
	}

	if (target_key < head->key) {
		if (head->lchild != NULL) return head->lchild->get_data(target_key);
		else  cout << "there is no such key in searching." << endl;
	} 
	else if (head->key < target_key) {
		if (head->rchild != NULL) return head->rchild->get_data(target_key);
		else  cout << "there is no such key in searching." << endl;
	}
	else {
		return head->data;
	}
}

void tree::insert(int new_key, int new_data) {
	if (head == NULL) {
		head = new node(new_key, new_data);
	}
	else {
		if (new_key < head->key) {
			if(head->lchild == NULL) head->lchild = new tree();
			head->lchild->insert(new_key, new_data);
		}
		else if(head->key < new_key) {
			if (head->rchild == NULL) head->rchild = new tree();
			head->rchild->insert(new_key, new_data);
		}
		else {
			cout << "cannot insert! key is same!" << endl;
			return;
		}
	}
}

void tree::remove(int target_key) {
	if (head == NULL) {
		cout << "cannot remove! tree is emptied!" << endl;
		return;
	}

			
	if (target_key < head->key) {
		if (head->lchild->head->lchild == NULL && head->lchild->head->rchild == NULL) {	
			delete head->lchild;
			head->lchild = NULL;
		}
		else {
			head->lchild->remove(target_key);
		}
	}
	else if (head->key < target_key) {
		if (head->rchild->head->lchild == NULL && head->rchild->head->rchild == NULL) {
			delete head->rchild;
			head->rchild = NULL;
		}
		else {
			head->rchild->remove(target_key);
		}
	}
	else {
		if (head->lchild != NULL && head->rchild != NULL) {								//�� �ڽ� ��� �ִ� ��쿣, ���������ڿ� �����ļ��� �߿��� �׳� �����ļ���(������ �ڽ� Ʈ������ ���� ���� Ű ���� ���)�� ���ֱ����
			replace_with_inorder_successor();
		}
		else if (head->lchild == NULL && head->rchild != NULL) {
			replace_with_inorder_successor();
		}
		else if (head->lchild != NULL && head->rchild == NULL) {
			replace_with_inorder_predecessor();
		}
		else {
			delete head;
			head = NULL;
		}
	}
}


