#include"tree_using_while.h"


	node* tree::search(int target_key, node* (*to_do_with_target_node)(node*&), node* (*to_do_with_target_hole)(node*&)) {
		if (head == NULL) return (*to_do_with_target_hole)(head);

		node* search_ptr = head;
		while (true) {
			if (target_key < search_ptr->key) {
				if (search_ptr->lchild != NULL) {
					if (search_ptr->lchild->key == target_key) return (*to_do_with_target_node)(search_ptr->lchild);
					else search_ptr = search_ptr->lchild;
				}
				else return (*to_do_with_target_hole)(search_ptr->lchild);
			}
			else if (search_ptr->key < target_key) {
				if (search_ptr->rchild != NULL) {
					if (search_ptr->rchild->key == target_key) return (*to_do_with_target_node)(search_ptr->rchild);
					else search_ptr = search_ptr->rchild;
				}
				else return (*to_do_with_target_hole)(search_ptr->rchild);
			}
			else {
				return (*to_do_with_target_node)(head);
			}
		}
	}

	void tree::preorder_traverse(void (*to_do)(node*)) {
		if (head == NULL) {
			cout << "can not traverse. there is no node." << endl;
			return;
		}
		stack head_stack;
		node* traverse_ptr = NULL;
		head_stack.push(this->head);
		while ((traverse_ptr = head_stack.pop())) {
			(*to_do)(traverse_ptr);
			if (traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
			if (traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
		}
	}

	void tree::inorder_traverse(void (*to_do)(node*)) {
		if (head == NULL) {
			cout << "can not traverse. there is no node." << endl;
			return;
		}
		stack head_stack;
		node* traverse_ptr = NULL;
		head_stack.push(head);
		bool new_left_spine = true;
		while (!head_stack.is_empty()) {
			while (new_left_spine && head_stack.get_top()->lchild) {
				head_stack.push(head_stack.get_top()->lchild);
			}
			traverse_ptr = head_stack.pop();
			(*to_do)(traverse_ptr);
			if (traverse_ptr->rchild) {
				new_left_spine = true;
				head_stack.push(traverse_ptr->rchild);
			}
			else new_left_spine = false;
		}
	}

	void tree::postorder_traverse(void (*to_do)(node*)) {
		if (head == NULL) {
			cout << "can not traverse. there is no node." << endl;
			return;
		}
		stack head_stack;
		node* traverse_ptr = NULL;
		head_stack.push(head);
		bool new_left_spine = true;
		bool new_right_spine = true;
		while (!head_stack.is_empty()) {
			while (new_left_spine && head_stack.get_top()->lchild) {
				head_stack.push(head_stack.get_top()->lchild);
			}
			traverse_ptr = head_stack.get_top();
			if (new_right_spine && traverse_ptr->rchild) {
				new_left_spine = true;
				head_stack.push(traverse_ptr->rchild);
			}
			else {
				(*to_do)(traverse_ptr);
				new_left_spine = false;
				node* previous_node = head_stack.pop();
				node* present_node = head_stack.get_top();
				if (present_node && present_node->rchild && present_node->rchild == previous_node) new_right_spine = false;
				else new_right_spine = true;
			}
		}
	}

	void tree::replace_with_inorder_predecessor(node*& target_ptr) {
		node* previous_ptr = NULL;
		node* traverse_ptr = target_ptr->lchild;
		while (traverse_ptr->rchild != NULL) {
			previous_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->rchild;
		}
		if (previous_ptr != NULL) previous_ptr->rchild = traverse_ptr->lchild;
		else target_ptr->lchild = traverse_ptr->lchild;
		target_ptr->key = traverse_ptr->key;
		target_ptr->data = traverse_ptr->data;
		delete traverse_ptr;
	}

	void tree::replace_with_inorder_successor(node*& target_ptr) {
		node* previous_ptr = NULL;
		node* traverse_ptr = target_ptr->rchild;
		while (traverse_ptr->lchild != NULL) {
			previous_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->lchild;
		}
		if (previous_ptr != NULL) previous_ptr->lchild = traverse_ptr->rchild;
		else target_ptr->rchild = traverse_ptr->rchild;
		target_ptr->key = traverse_ptr->key;
		target_ptr->data = traverse_ptr->data;
		delete traverse_ptr;
	}