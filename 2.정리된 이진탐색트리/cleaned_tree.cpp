#include<iostream>
using namespace std;

class node {
	friend class tree;
	int key;
	int data;
	node* lchild;
	node* rchild;


public:
	node(int key, int data) {
		this->key = key;
		this->data = data;
		this->lchild = NULL;
		this->rchild = NULL;
	}
};

//일단 스택이 가지는 아이템의 타입은 node*이고, 최대 개수는 100개라고 가정하고 어레이 구현을 사용함.
//아이템 개수에 상관없이 적절한 메모리 크기를 사용하도록, 추후에 연결된 노드 구조로 개선할 예정
class stack {
	node* head_data[100];
	int item_num;

public:
	stack() {
		for (int i = 0; i < 100; i++) {
			head_data[i] = NULL;
		}
		item_num = 0;
	}

	void push(node* new_head) {
		if (item_num >= 99) {
			cout << "cannot push to stack. it is full!" << endl;
			return;
		}
		head_data[item_num] = new_head;
		item_num++;
	}

	node* pop() {
		if (item_num <= 0) {
			cout << "cannot pop from stack. it is emptied!" << endl;
			return NULL;
		}

		return head_data[--item_num];
	}
};

class tree {
	node* head;

public:
	tree() {
		cout << "tree is made!" << endl;
	}

	~tree() {

	}

	void traverse_print() {
		if (head == NULL) {
			cout << "cannot traverse.head is NULL." << endl;
			return;
		}

		stack head_stack;
		node* traverse_ptr = NULL;
		head_stack.push(this->head);
		while ((traverse_ptr = head_stack.pop())) {
			cout << "node key : " << traverse_ptr->key << " / node data : " << traverse_ptr->data << endl;
			if(traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
			if(traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
		}
	}


	int search(int target_key) {
		if (head == NULL) {
			cout << "can not search. there is no such key." << endl;
			return -1;
		}

		node* search_ptr = head;
		while (search_ptr->key != target_key) {
			if (target_key < search_ptr->key) {
				if (search_ptr->lchild != NULL) search_ptr = search_ptr->lchild;
				else  cout << "there is no such key in searching." << endl;
			}
			else if (search_ptr->key < target_key) {
				if (search_ptr->rchild != NULL) search_ptr = search_ptr->rchild;
				else  cout << "there is no such key in searching." << endl;
			}
			else {
				return search_ptr->data;
			}
		}
	}


	void insert(int new_key, int new_data) {
		if (head == NULL) {
			head = new node(new_key, new_data);
		}
		else {
			node* search_ptr = head;
			while (true) {
				if (new_key < search_ptr->key) {
					if (search_ptr->lchild != NULL) search_ptr = search_ptr->lchild;
					else {
						search_ptr->lchild = new node(new_key, new_data);
						return;
					}
				}
				else if (search_ptr->key < new_key) {
					if (search_ptr->rchild != NULL) search_ptr = search_ptr->rchild;
					else {
						search_ptr->rchild = new node(new_key, new_data);
						return;
					}
				}
			}
		}
	}

	void remove_all() {

	}

	void remove(int target_key) {

	}

	void replace_with_inorder_predecessor() {

	}

	void replace_with_inorder_successor() {

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
	test_tree.traverse_print();


	return 0;
}