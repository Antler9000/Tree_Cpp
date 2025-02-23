#include"BST_using_while.h"


BST_node* BST::search(int target_key, BST_node* (BST::* to_do_with_target_ptr)(BST_node*&)) {
	if (head == NULL) return (this->*to_do_with_target_ptr)(head);

	BST_node* search_ptr = head;
	while (true) {
		if (target_key < search_ptr->key) {
			if (search_ptr->lchild != NULL) {
				if (search_ptr->lchild->key == target_key) return (this->*to_do_with_target_ptr)(search_ptr->lchild);
				else search_ptr = search_ptr->lchild;
			}
			else return (this->*to_do_with_target_ptr)(search_ptr->lchild);
		}
		else if (search_ptr->key < target_key) {
			if (search_ptr->rchild != NULL) {
				if (search_ptr->rchild->key == target_key) return (this->*to_do_with_target_ptr)(search_ptr->rchild);
				else search_ptr = search_ptr->rchild;
			}
			else return (this->*to_do_with_target_ptr)(search_ptr->rchild);
		}
		else {
			return (this->*to_do_with_target_ptr)(head);
		}
	}
}

void BST::preorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST) {
	if (head == NULL) {
		cout << "can not traverse. there is no BST_node." << endl;
		return;
	}

	stack<BST_node*> head_stack;
	BST_node* traverse_ptr = NULL;
	head_stack.push(this->head);
	while ((traverse_ptr = head_stack.pop())) {
		(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
		if (traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
		if (traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
	}
}

void BST::inorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST) {
	if (head == NULL) {
		cout << "can not traverse. there is no BST_node." << endl;
		return;
	}

	stack<BST_node*> head_stack;
	BST_node* traverse_ptr = NULL;
	head_stack.push(head);
	bool new_left_spine = true;
	while (!head_stack.is_empty()) {
		while (new_left_spine && head_stack.get_top()->lchild) {
			head_stack.push(head_stack.get_top()->lchild);
		}
		traverse_ptr = head_stack.pop();
		(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
		if (traverse_ptr->rchild != NULL) {
			new_left_spine = true;
			head_stack.push(traverse_ptr->rchild);
		}
		else new_left_spine = false;
	}
}

void BST::postorder_traverse(void (*to_do_while_traverse)(BST_node*, BST*), BST* optional_target_BST) {
	if (head == NULL) {
		cout << "can not traverse. there is no BST_node." << endl;
		return;
	}

	stack<BST_node*> head_stack;
	BST_node* traverse_ptr = NULL;
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
			(*to_do_while_traverse)(traverse_ptr, optional_target_BST);
			new_left_spine = false;
			BST_node* previous_BST_node = head_stack.pop();
			BST_node* present_BST_node = head_stack.get_top();
			if (present_BST_node && present_BST_node->rchild && present_BST_node->rchild == previous_BST_node) new_right_spine = false;
			else new_right_spine = true;
		}
	}
}



BST_node* BST::remove_target(BST_node*& target_ptr) {
	if (target_ptr->lchild != NULL && target_ptr->rchild != NULL) {				//두 자식 모두 있는 경우엔, 중위선행자와 중위후속자 중에서 그냥 중위후속자(오른쪽 자식 트리에서 제일 작은 키 값의 노드)를 없애기로함
		replace_with_inorder_successor(target_ptr);
	}
	else if (target_ptr->lchild == NULL && target_ptr->rchild != NULL) {
		replace_with_inorder_successor(target_ptr);
	}
	else if (target_ptr->lchild != NULL && target_ptr->rchild == NULL) {
		replace_with_inorder_predecessor(target_ptr);
	}
	else {
		delete target_ptr;
		target_ptr = NULL;
		return target_ptr;
	}
}

void BST::replace_with_inorder_predecessor(BST_node*& target_ptr) {
	BST_node* previous_ptr = NULL;
	BST_node* traverse_ptr = target_ptr->lchild;
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

void BST::replace_with_inorder_successor(BST_node*& target_ptr) {
	BST_node* previous_ptr = NULL;
	BST_node* traverse_ptr = target_ptr->rchild;
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