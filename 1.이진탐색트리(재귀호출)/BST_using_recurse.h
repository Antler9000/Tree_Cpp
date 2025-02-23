#ifndef BST_USING_RECURSE_H
#define BST_USING_RECURSE_H

#include <iostream>
using namespace std;


class BST {
	int data;
	int key;
	BST* lchild;
	BST* rchild;

	BST(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	//�θ� ����Ű�� �ڽĿ� ���� ������ NULL�� �ٲ���ϹǷ�, ���۷��� ���ڷ� ����
	void remove_target(BST*& target_child_variable);

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();

public:
	//Ʈ���� ������ Ű�� �����Ͱ� ��� -1 ���� ���� ����̴�.
	//�̴� Ʈ�� Ŭ������ ������ ��� Ŭ���� ���� ��������� ���ǵǾ��⿡, ����带 NULL�� ���� ǥ���� ������ ������ ��� ���� ��带 �α�� �Ͽ���.
	BST() {
		this->key = -1;
		this->data = -1;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	~BST() {
		remove_all();
	}

	//����
	void insert(int new_key, int new_data);

	//�˻�
	int retrieve(int target_key);

	//����
	void remove(int target_key);

	void copy_from(BST* target_BST) {		
		if (target_BST == NULL) return;

		insert(target_BST->key, target_BST->data);
		copy_from(target_BST->lchild);
		copy_from(target_BST->rchild);
	}

	void remove_all() {
		if (lchild != NULL) lchild->remove_all();
		if (rchild != NULL) rchild->remove_all();

		if (lchild != NULL) delete lchild;
		if (rchild != NULL) delete rchild;
	}

	void preorder_print() {
		if (key == -1 && data == -1) cout << "traverse..." << endl;

		cout << "node key : " << key << " / node data : " << data << endl;
		if (lchild != NULL) lchild->preorder_print();
		if (rchild != NULL) rchild->preorder_print();
	}

	void inorder_print() {
		if (key == -1 && data == -1) cout << "traverse..." << endl;

		if (lchild != NULL) lchild->preorder_print();
		cout << "node key : " << key << " / node data : " << data << endl;
		if (rchild != NULL) rchild->preorder_print();
	}

	void postorder_print() {
		if (key == -1 && data == -1) cout << "traverse...." << endl;

		if (lchild != NULL) lchild->preorder_print();
		if (rchild != NULL) rchild->preorder_print();
		cout << "node key : " << key << " / node data : " << data << endl;
	}

};

#endif //BST_USING_RECURSE_H