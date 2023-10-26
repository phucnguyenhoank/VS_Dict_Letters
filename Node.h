#pragma once
#include "HardArray.h"

#define MAX_LETTERS 27

class Node {
public:
	// available children nodes
	HardArray<Node*, MAX_LETTERS> letters;
	char key = 0;

	// if went string has a meaning
	bool makeSense = false;

	Node() {
		for (int i = 0; i < MAX_LETTERS; i++) {
			letters.setAt(i, nullptr);
		}
	}
};
