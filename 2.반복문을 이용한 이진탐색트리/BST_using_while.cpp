#include"BST_using_while.h"


tree_node* tree::search(int target_key, tree_node* (*to_do_with_target_tree_node)(tree_node*&), tree_node* (*to_do_with_target_hole)(tree_node*&)) {
	if (head == NULL) return (*to_do_with_target_hole)(head);

	tree_node* search_ptr = head;
	while (true) {
		if (target_key < search_ptr->key) {
			if (search_ptr->lchild != NULL) {
				if (search_ptr->lchild->key == target_key) return (*to_do_with_target_tree_node)(search_ptr->lchild);
				else search_ptr = search_ptr->lchild;
			}
			else return (*to_do_with_target_hole)(search_ptr->lchild);
		}
		else if (search_ptr->key < target_key) {
			if (search_ptr->rchild != NULL) {
				if (search_ptr->rchild->key == target_key) return (*to_do_with_target_tree_node)(search_ptr->rchild);
				else search_ptr = search_ptr->rchild;
			}
			else return (*to_do_with_target_hole)(search_ptr->rchild);
		}
		else {
			return (*to_do_with_target_tree_node)(head);
		}
	}
}

void tree::preorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree) {
	if (head == NULL) {
		cout << "can not traverse. there is no tree_node." << endl;
		return;
	}
	stack<tree_node*> head_stack;
	tree_node* traverse_ptr = NULL;
	head_stack.push(this->head);
	while ((traverse_ptr = head_stack.pop())) {
		(*to_do_while_traverse)(traverse_ptr, optional_target_tree);
		if (traverse_ptr->rchild != NULL) head_stack.push(traverse_ptr->rchild);
		if (traverse_ptr->lchild != NULL) head_stack.push(traverse_ptr->lchild);
	}
}

void tree::inorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree) {
	if (head == NULL) {
		cout << "can not traverse. there is no tree_node." << endl;
		return;
	}
	stack<tree_node*> head_stack;
	tree_node* traverse_ptr = NULL;
	head_stack.push(head);
	bool new_left_spine = true;
	while (!head_stack.is_empty()) {
		while (new_left_spine && head_stack.get_top()->lchild) {
			head_stack.push(head_stack.get_top()->lchild);
		}
		traverse_ptr = head_stack.pop();
		(*to_do_while_traverse)(traverse_ptr, optional_target_tree);
		if (traverse_ptr->rchild) {
			new_left_spine = true;
			head_stack.push(traverse_ptr->rchild);
		}
		else new_left_spine = false;
	}
}

void tree::postorder_traverse(void (*to_do_while_traverse)(tree_node*, tree*), tree* optional_target_tree) {
	if (head == NULL) {
		cout << "can not traverse. there is no tree_node." << endl;
		return;
	}
	stack<tree_node*> head_stack;
	tree_node* traverse_ptr = NULL;
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
			(*to_do_while_traverse)(traverse_ptr, optional_target_tree);
			new_left_spine = false;
			tree_node* previous_tree_node = head_stack.pop();
			tree_node* present_tree_node = head_stack.get_top();
			if (present_tree_node && present_tree_node->rchild && present_tree_node->rchild == previous_tree_node) new_right_spine = false;
			else new_right_spine = true;
		}
	}
}



tree_node* tree::remove_target(tree_node*& target_ptr) {
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

void tree::replace_with_inorder_predecessor(tree_node*& target_ptr) {
	tree_node* previous_ptr = NULL;
	tree_node* traverse_ptr = target_ptr->lchild;
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

void tree::replace_with_inorder_successor(tree_node*& target_ptr) {
	tree_node* previous_ptr = NULL;
	tree_node* traverse_ptr = target_ptr->rchild;
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