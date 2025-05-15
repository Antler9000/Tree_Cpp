#include "heap.h"

int main() {
	MinHeap test_heap;
	test_heap.push(345);
	test_heap.push(234);
	test_heap.push(123);
	cout << test_heap.pop() << endl;
	cout << test_heap.pop() << endl;
	cout << test_heap.pop() << endl;
	test_heap.push(500);
	test_heap.push(600);
	test_heap.push(400);
	cout << test_heap.pop() << endl;
	cout << test_heap.pop() << endl;
	cout << test_heap.pop() << endl;
	test_heap.push(500);
	test_heap.push(600);
	test_heap.push(400);
	test_heap.push(500);
	test_heap.push(600);
	test_heap.push(400);
	test_heap.push(500);
	test_heap.push(600);
	test_heap.push(400);
	test_heap.push(500);
	test_heap.push(600);
	test_heap.push(400);
	return 0;
}