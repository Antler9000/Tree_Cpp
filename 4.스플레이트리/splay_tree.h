#ifndef splay_tree_H
#define splay_tree_H

#include "../2.이진탐색트리(반복문)/BST_using_while.h"

class splay_tree : public BST {

	void LL_rotation();
	void RR_rotation();

public :
	splay_tree() : BST() {
	}

	int retrieve(int target_key);
};

#endif //SPLAY_TREE_H