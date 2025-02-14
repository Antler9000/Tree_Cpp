#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class stack;

template <class T>
class stack_node {
	friend class stack<T>;
	T data;
	stack_node* child;

	stack_node(T data) {
		this->data = data;
		this->child = NULL;
	}
};

template <class T>
class stack {
	stack_node<T>* head;

public:
	stack() {
		head = NULL;
	}

	void push(T data) {
		if (!head) {
			head = new stack_node<T>(data);
		}
		else {
			stack_node<T>* traverse_ptr = head;
			while (traverse_ptr->child) {
				traverse_ptr = traverse_ptr->child;
			}
			traverse_ptr->child = new stack_node<T>(data);
		}
	}

	T pop() {
		if (!head) {
			cout << "cannot pop from stack. it is emptied!" << endl;
			return NULL;
		}

		if (!head->child) {
			T temp = head->data;
			delete head;
			head = NULL;
			return temp;
		}
		else {
			stack_node<T>* traverse_ptr = head;
			while (traverse_ptr->child->child) {
				traverse_ptr = traverse_ptr->child;
			}
			T temp = traverse_ptr->child->data;
			delete traverse_ptr->child;
			traverse_ptr->child = NULL;
			return temp;
		}
	}

	T get_top() {
		if (!head) {
			cout << "cannot get top from stack. it is emptied!" << endl;
			return NULL;
		}

		if (!head->child) {
			return head->data;
		}
		else {
			stack_node<T>* traverse_ptr = head;
			while (traverse_ptr->child->child) {
				traverse_ptr = traverse_ptr->child;
			}
			return traverse_ptr->child->data;
		}
	}

	bool is_empty() {
		if (!head) return true;
		else return false;
	}
};


#endif //STACK_H