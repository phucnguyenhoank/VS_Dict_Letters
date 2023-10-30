#pragma once
#include "DynamicArray.h"

#define MAX_LETTERS 27

class Node {
private:
	// available children nodes
	DynamicArray<Node*> *letters;
	char key;

	// if went string has a meaning
	bool makeSense;

public:

	Node() {
		letters = new DynamicArray<Node*>();
		key = 0;
		makeSense = false;
		letters->resize(MAX_LETTERS);

		for (int i = 0; i < MAX_LETTERS; i++) letters->setAt(i, nullptr);
	}

	~Node() {
		delete[] letters;
	}

	Node* getLetterAt(int ind) {
		return letters->getAt(ind);
	}

	void setLetterAt(int ind, Node* pointToLetter) {
		letters->setAt(ind, pointToLetter);
	}

	void setKey(char key) {
		this->key = key;
	}

	void setSense(bool sense) {
		this->makeSense = sense;
	}

	char getKey() {
		return this->key;
	}

	bool getSense() {
		return this->makeSense;
	}

};
