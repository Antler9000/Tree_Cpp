#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

class heap {
protected:
	int* data;
	int item_num;
	int max_num;

	int get_left_child_index(int data_index) {
		return (data_index * 2 + 1);
	}

	int get_right_child_index(int data_index) {
		return (data_index * 2 + 2);
	}

	int get_parent_index(int data_index) {
		return ((data_index - 1) / 2);
	}

	void swap(int& data_A, int& data_B) {
		int temp = data_A;
		data_A = data_B;
		data_B = temp;
	}

	virtual bool is_not_ordered(int parent_index, int child_index) = 0;

	virtual bool is_left_child_target(int left_child_index, int right_child_index) = 0;

	void reorder_by_promoting();

	void reorder_by_demoting();

public:
	heap(int max_item_number) {
		cout << "heap is being made" << endl;
		data = new int[max_item_number];
		item_num = 0;
		max_num = max_item_number;
	}

	~heap() {
		cout << "heap is being removed" << endl;
		delete data;
		data = NULL;
	}

	void push(int new_data) {
		if (item_num >= max_num) {
			cout << "cannot push item into heap. heap is fulled." << endl;
			return;
		}

		data[item_num] = new_data;
		item_num++;
		reorder_by_promoting();
	}

	int get_top() {
		if (item_num <= 0) {
			cout << "cannot get_top item from heap. heap is emptied." << endl;
			return 0;
		}

		return data[0];
	}

	int pop() {
		if (item_num <= 0) {
			cout << "cannot get_top item from heap. heap is emptied." << endl;
			return 0;
		}

		item_num--;
		int popped_data = data[0];
		data[0] = data[item_num];
		reorder_by_demoting();
		return popped_data;
	}

	void remove_all() {
		item_num = 0;
	}
};

class min_heap : public heap {
	bool is_not_ordered(int parent_index, int child_index) {
		if (data[parent_index] > data[child_index]) return true;
		else return false;
	}

	bool is_left_child_target(int left_child_index, int right_child_index) {
		if (data[left_child_index] < data[right_child_index]) return true;
		else return false;
	}

public :
	min_heap(int max_item_number) : heap(max_item_number) {}
};


class max_heap : public heap {
	bool is_not_ordered(int parent_index, int child_index) {
		if (data[parent_index] < data[child_index]) return true;
		else return false;
	}

	bool is_left_child_target(int left_child_index, int right_child_index) {
		if (data[left_child_index] > data[right_child_index]) return true;
		else return false;
	}

public :
	max_heap(int max_item_number) : heap(max_item_number) {}
};


#endif //HEAP_H