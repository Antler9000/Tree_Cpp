#include "heap.h"

int main() {
	min_heap test_heap(100);
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
	return 0;
}