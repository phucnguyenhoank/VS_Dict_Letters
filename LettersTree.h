/*

this class is a feature of the dictionary (EngVieDict.h)

*/

#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>



class LettersTree {
private:
	// the key of the top node is 0
	Node* root;
public:
	LettersTree() {
		root = new Node();
	}

	// create a letter tree from a wordSource file
	// each line in wordSource file must have a word
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
	// return a pointer which is pointing to the child node
	// WARNING
	// r must not be a nullptr, that mean r IS POINTING to a specific, valid Node
	// singleLetter must be lowercase
	Node* addLetter(Node* r, char singleLetter) {
		// don't add a new node at anytime
		// if not add, return that already existed place
		// if add, return a pointer pointing to the newly added place

		// create a node pointing to the next place that the singleLetter is going to be added (if needed)
		Node* nextNode = r->getLetterAt(singleLetter - 'a' + 1);
		// if the needed-to-place have no word yet
		if (nextNode == nullptr) {
			// add a new node to that place and return a pointer pointing to that new place
			Node* newNode = new Node();
			newNode->setKey(singleLetter);
			r->setLetterAt(singleLetter - 'a' + 1, newNode);
			return newNode;
		}
		// just return an already existed place
		return nextNode;

	}

	// press (add) word into this tree
	void pressWord(std::string word) {
		if (have(word)) return;

		// the key of the top node is 0, so the first child nodes (level 1, start from 0) of this tree will be added by ourself
		// get the first letter and remove it from word
		char fir = word[0];
		word.erase(0, 1);
		// the next place that we will put in
		Node* nextNode = root->getLetterAt(fir - 'a' + 1);
		// if it hasn't been placed yet
		if (nextNode == nullptr) {
			Node* newNode = new Node();
			root->setLetterAt(fir - 'a' + 1, newNode);
			newNode->setKey(fir);
		}

		// continue add next letters of the words
		Node* tempRoot = root->getLetterAt(fir - 'a' + 1);
		while (!word.empty()) {
			fir = word[0];
			word.erase(0, 1);
			tempRoot = addLetter(tempRoot, fir);
		}

		// the position of the last node of this word make sense
		tempRoot->setSense(true);
	}

	// ---------------------------------- REMOVE ----------------------------------

	// remove word from the tree
	void remove(std::string word) {
		if (!have(word)) return;
		
		char fir;				
		Node* nextNode = root;	// this pointer is going to point to the node (if presant) represent for the last letter of word

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

	// return true if have word in the tree
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

	// JUST FOR TESTING, MAY CAUSE CONFUSING
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
	// JUST FOR TESTING, MAY CAUSE CONFUSING
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

