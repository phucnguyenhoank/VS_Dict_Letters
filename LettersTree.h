#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>

/*

this class is a feature of the dictionary

*/

class LettersTree {
	// the key of the highest node if 0
public:
	Node* root;

	LettersTree() {
		root = new Node();
	}

	// create a letter tree from a wordSource file
	// each line in wordSource file must have one word
	LettersTree(std::string wordSource) {
		root = new Node();
		std::ifstream fin(wordSource);
		if (fin.fail()) {
			std::cout << "LettersTree, constructor.\n";
			return;
		}

		std::string input;
		while (std::getline(fin, input)) {
			this->pressWord(input);
		}

		fin.close();
	}

	~LettersTree() {
		delete root;
	}

	// ------------------------------------ ADD -----------------------------------------

	// add the singleLetter to a reasonable place in the array of father node,
	// this array contains its father's valid child nodes (DynamicArray<Node*> *letters, a field of Node)
	// father node is the node which r is pointing to
	// return a pointer which is pointing to child node
	// WARNING
	// r must be different from nullptr, tha mean r IS POINTING to a specific, valid Node
	// singleLetter must be lower case
	Node* addLetter(Node* r, char singleLetter) {
		// do not add a new node anytime
		// if not add, just return that place which don't need to be added to
		// if so, add to the place need to be placed and return a pointer is pointing to

		// create a node which is pointing to the next place we are going to add a new node (if need)
		Node* nextNode = r->getLetterAt(singleLetter - 'a' + 1);
		// if the need-ed to place haven't any word yet
		if (nextNode == nullptr) {
			// add a new node to that place and return a pointer which is pointing to that new place
			Node* newNode = new Node();
			newNode->setKey(singleLetter);
			r->setLetterAt(singleLetter - 'a' + 1, newNode);
			return newNode;
		}
		// just return already existed place
		return nextNode;

	}

	void pressWord(std::string word) {
		if (have(word)) return;

		// the key of the highest node if 0, so first child nodes (level 1, count from 0) of this tree we will add by ourself
		// get the first letter and remove it from word
		char fir = word[0];
		word.erase(0, 1);
		// the next place we will place to
		Node* nextNode = root->getLetterAt(fir - 'a' + 1);
		// if it hasn't placed yet
		if (nextNode == nullptr) {
			Node* newNode = new Node();
			root->setLetterAt(fir - 'a' + 1, newNode);
			newNode->setKey(fir);
		}

		// continue add next letters of words
		Node* tempRoot = root->getLetterAt(fir - 'a' + 1);
		while (!word.empty()) {
			fir = word[0];
			word.erase(0, 1);
			tempRoot = addLetter(tempRoot, fir);
		}

		// the postion of the last node of this word make sense
		tempRoot->setSense(true);
	}

	// ---------------------------------- REMOVE ----------------------------------
	void remove(std::string word) {
		if (!have(word)) return;
		
		char fir;				
		Node* nextNode = root;	// this pointer is going to point to the node (if have) represent for the last letter of word

		// find the place
		while (word.size()) {
			fir = word[0];
			word.erase(0, 1);
			// point to the next node contains letter 'fir'
			nextNode = nextNode->getLetterAt(fir - 'a' + 1);
		}

		// just set 'makeSense' to false
		nextNode->setSense(false);	
	}

	// ---------------------------------- CHECKING ----------------------------------
	bool have(std::string word) {
		char fir;
		Node* nextNode = root;

		while (word.size()) {
			fir = word[0];
			word.erase(0, 1);

			nextNode = nextNode->getLetterAt(fir - 'a' + 1);
			if (nextNode == nullptr) return false;
		}

		if (!nextNode->getSense()) return false;
		return true;

	}

	// --------------------------------- DISPLAY -----------------------------------------

	// JUST FOR TESTING, MAY CAUSE COFUSING
	void show(Node* r) {
		if (r) {
			if (r->getSense()) std::cout << "ms-";
			std::cout << r->getKey() << "\n";

			for (int i = 0; i < MAX_LETTERS; i++) {
				if (r->getLetterAt(i)) {
					show(r->getLetterAt(i));
				}
			}
		}
	}
	void show() {
		this->show(root);
	}

	// show all words begin at the node of that last letter of the 'mean' word of the letter tree
	// NOTE:
	// cannot display the letter of node which r is pointing to whether makeSense is true or not
	void sweepWords(Node* r, std::string& mean) {
		for (int i = 0; i < MAX_LETTERS; i++) {
			if (r->getLetterAt(i)) {
				mean += r->getLetterAt(i)->getKey();
				if (r->getLetterAt(i)->getSense()) {
					std::cout << mean << "\n";
				}
				sweepWords(r->getLetterAt(i), mean);
				mean.pop_back();
			}
		}
	}

	// show all words of the letter tree
	void sweepWords() {
		std::string mean;
		sweepWords(root, mean);
	}

	// return a node is pointing to the node of the last letter of the 'mean' word of the letter tree
	// if mean doesn't have in the list, return null
	Node* track(Node* r, std::string mean) {
		if (mean.size() == 0 || r == nullptr) return r;

		char fir = mean[0];
		mean.erase(0, 1);

		Node* nextNode = r->getLetterAt(fir - 'a' + 1);
		return track(nextNode, mean);
	}

	// show all words begin at the node of the last letter of the 'mean' word of the letter tree
	void sweepWords(std::string missedWord) {
		std::string mean = missedWord;

		// find the begining node
		Node* beginPoint = track(root, mean);
		if (beginPoint == nullptr) return;
		
		// display if beginPoint make sense, because if it has, sweepWords function will not can display that word
		if (beginPoint->getSense()) std::cout << mean << "\n";
		sweepWords(beginPoint, mean);
	}

};

