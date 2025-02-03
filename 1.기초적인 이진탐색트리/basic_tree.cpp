#include <iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	tree* lchild;
	tree* rchild;


public :
	node(int key, int data) {
		cout << "node is made!" << endl;
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

class tree {
	node* head;

public:
	tree() {
		cout << "tree is made!" << endl;
	}

	~tree() {
		traverse_remove();
	}

	void traverse() {
		if (head == NULL) {
			cout << "cannot traverse. head is NULL." << endl;
			return;
		}
		cout << "node key : " << head->key << " / node data : " << head->data << endl;
		if (head->lchild != NULL) head->lchild->traverse();
		if (head->rchild != NULL) head->rchild->traverse();
	}

	void traverse_remove() {
		if (head != NULL) {
			if (head->lchild != NULL) head->lchild->traverse_remove();
			if (head->rchild != NULL) head->rchild->traverse_remove();
			delete head;
			head = NULL;
		}
	}

	int search(int target_key) {
		if (head == NULL) {
			cout << "can not search. there is no such key." << endl;
		}

		if (target_key < head->key) {
			if (head->lchild != NULL) return head->lchild->search(target_key);
		} 
		else if (head->key < target_key) {
			if (head->rchild != NULL) return head->rchild->search(target_key);
		}
		else {
			return head->data;
		}
	}

	void insert(int new_key, int new_data) {
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
			}
		}
	}

	int remove(int target_key) {
		if (head == NULL) {
			cout << "cannot remove! tree is emptied!" << endl;
			return -1;
		}
		else {
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
				if (head->lchild != NULL && head->rchild != NULL) {			//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 중위후속자를 없앰(오른쪽 자식 트리에서 가장 왼쪽 노드)
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
				else if (head->lchild == NULL && head->rchild != NULL) {
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
				else if (head->lchild != NULL && head->rchild == NULL) {
					tree* previous_ptr = NULL;
					tree* traverse_ptr = head->lchild;
					while (traverse_ptr->head->rchild != NULL) {				//중위후속자 노드를 제거하면서 생기는 빈자리로, 해당 중위후속자의 우측 자식을 당겨 놓기 위함(더러운 표현은 나중에 곤치기로) 
						previous_ptr = traverse_ptr;
						traverse_ptr = traverse_ptr->head->rchild;
					}
					if (previous_ptr != NULL) previous_ptr->head->rchild = traverse_ptr->head->lchild;
					else this->head->lchild = traverse_ptr->head->lchild;
					head->key = traverse_ptr->head->key;
					head->data = traverse_ptr->head->data;
					delete traverse_ptr;
				}
				else {
					delete head;
					head = NULL;
				}
			}
		}
	}
};
int main() {
	tree& test_tree = *(new tree());
	test_tree.insert(5, 1515);
	test_tree.insert(7, 2727);
	test_tree.insert(3, 1313);
	test_tree.insert(4, 2424);
	test_tree.insert(6, 3636);
	cout << "traverse" << endl;
	test_tree.traverse();

	
	test_tree.remove(7);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(5);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(6);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(4);
	cout << "traverse" << endl;
	test_tree.traverse();

	test_tree.remove(3);
	cout << "traverse" << endl;
	test_tree.traverse();
	

	
	test_tree.traverse_remove();
	cout << "traverse" << endl;
	test_tree.traverse();
	

	return 0;
}