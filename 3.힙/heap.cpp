#include "heap.h"

void heap::reorder_by_promoting() {
	int target_index = item_num - 1;
	int parent_index = get_parent_index(target_index);

	while ((target_index > 0) && is_not_ordered(parent_index, target_index)) {
		swap(data[target_index], data[parent_index]);
		target_index = parent_index;
		parent_index = get_parent_index(target_index);
	}
}

void heap::reorder_by_demoting() {
	int target_index = 0;
	int left_child_index = get_left_child_index(target_index);
	int right_child_index = get_right_child_index(target_index);
	int target_child_index;

	while (left_child_index <= item_num) {
		if (right_child_index <= item_num) {
			if (is_left_child_target(left_child_index, right_child_index)) target_child_index = left_child_index;
			else target_child_index = right_child_index;
		}
		else {
			target_child_index = left_child_index;
		}

		if (is_not_ordered(target_index, target_child_index)) {
			swap(data[target_index], data[target_child_index]);
			target_index = target_child_index;
			left_child_index = get_left_child_index(target_index);
			right_child_index = get_right_child_index(target_index);
		}
		else {
			break;
		}
	}
}