#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack;

template <class T>
class StackNode {
	friend class Stack<T>;
	T data;
	StackNode* child;

	StackNode(T data) {
		this->data = data;
		this->child = NULL;
	}
};

template <class T>
class Stack {
	StackNode<T>* head;

public:
	Stack() {
		head = NULL;
	}

	void push(T data) {
		if (head == NULL) {
			head = new StackNode<T>(data);
		}
		else {
			StackNode<T>* traverse_ptr = head;
			while (traverse_ptr->child) {
				traverse_ptr = traverse_ptr->child;
			}
			traverse_ptr->child = new StackNode<T>(data);
		}
	}

	T pop() {
		if (head == NULL) {
			return NULL;
		}

		if (head->child == NULL) {
			T temp = head->data;
			delete head;
			head = NULL;
			return temp;
		}
		else {
			StackNode<T>* traverse_ptr = head;
			while (traverse_ptr->child->child != NULL) {
				traverse_ptr = traverse_ptr->child;
			}
			T temp = traverse_ptr->child->data;
			delete traverse_ptr->child;
			traverse_ptr->child = NULL;
			return temp;
		}
	}

	T get_top() {
		if (head == NULL) {
			return NULL;
		}

		if (head->child == NULL) {
			return head->data;
		}
		else {
			StackNode<T>* traverse_ptr = head;
			while (traverse_ptr->child->child) {
				traverse_ptr = traverse_ptr->child;
			}
			return traverse_ptr->child->data;
		}
	}

	bool is_empty() {
		if (head == NULL) return true;
		else return false;
	}
};


#endif //STACK_H