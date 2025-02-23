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

	//부모가 가리키는 자식에 대한 정보를 NULL로 바꿔야하므로, 레퍼런스 인자로 받음
	void remove_target(BST*& target_child_variable);

	void replace_with_inorder_predecessor();

	void replace_with_inorder_successor();

public:
	//트리의 헤드노드는 키와 데이터가 모두 -1 값인 더미 노드이다.
	//이는 트리 클래스가 별도의 노드 클래스 없이 재귀적으로 정의되었기에, 헤드노드를 NULL과 같이 표기할 수단이 마땅히 없어서 더미 노드를 두기로 하였다.
	BST() {
		this->key = -1;
		this->data = -1;
		this->lchild = NULL;
		this->rchild = NULL;
	}

	~BST() {
		remove_all();
	}

	//삽입
	void insert(int new_key, int new_data);

	//검색
	int retrieve(int target_key);

	//삭제
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