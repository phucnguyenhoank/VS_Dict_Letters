#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>

/*

this class is a feature of the dictionary

*/

class LettersTree {
public:
	Node* root;

	LettersTree() {
		root = new Node();
	}

	LettersTree(std::string wordSouce) {
		root = new Node();
		std::ifstream fin(wordSouce);
		if (fin.fail()) {
			std::cout << "LettersTree, constructor.\n";
			return;
		}

		std::string input;
		while (std::getline(fin, input)) {
			this->addLetter(input);
		}

		fin.close();
	}

	// ------------------------------------ ADD -----------------------------------------

	// WARNING: r phai khac nullptr, tức là r ĐANG trỏ vào một Node cụ thể
	// singleLetter la chu cai thuong
	Node* addLetter(Node* r, char singleLetter) {

		// khong phai luc nao cung them
		// neu khong them thi tro vao nut tiep theo roi tra ve
		// neu co them
		// them vao nut can them roi tra ve dia chi nut vua them
		Node* nextNode = r->getLetterAt(singleLetter - 'a' + 1);
		if (nextNode == nullptr) {
			Node* newNode = new Node();
			newNode->setKey(singleLetter);
			r->setLetterAt(singleLetter - 'a' + 1, newNode);
			return newNode;
		}
		return nextNode;

	}

	void addLetter(std::string word) {
		if (have(word)) return;

		// tu them node dau tien bang tay
		char fir = word[0];
		word.erase(0, 1);

		Node* nextNode = root->getLetterAt(fir - 'a' + 1);

		if (nextNode == nullptr) {
			Node* newNode = new Node();
			root->setLetterAt(fir - 'a' + 1, newNode);
			newNode->setKey(fir);
		}


		Node* tempRoot = root->getLetterAt(fir - 'a' + 1);

		while (!word.empty()) {
			fir = word[0];
			word.erase(0, 1);
			tempRoot = addLetter(tempRoot, fir);
		}

		tempRoot->setSense(true);
	}

	// ---------------------------------- REMOVE ----------------------------------
	void remove(std::string word) {
		if (!have(word)) return;

		char fir;
		Node* nextNode = root;

		while (word.size()) {
			fir = word[0];
			word.erase(0, 1);
			nextNode = nextNode->getLetterAt(fir - 'a' + 1);
		}

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

	// NHƯỢC ĐIỂM:
	// nếu Node hiện tại mà r đang trỏ đến makeSence thì không thể xuất được
	void crushWords(Node* r, std::string& mean) {
		for (int i = 0; i < MAX_LETTERS; i++) {
			if (r->getLetterAt(i)) {
				mean += r->getLetterAt(i)->getKey();
				if (r->getLetterAt(i)->getSense()) {
					std::cout << mean << "\n";
				}
				crushWords(r->getLetterAt(i), mean);
				mean.pop_back();
			}
		}
	}
	void crushWords() {
		std::string mean;
		crushWords(root, mean);
	}

	Node* track(Node* r, std::string letrs) {
		if (letrs.size() == 0 || r == nullptr) return r;

		char fir = letrs[0];
		letrs.erase(0, 1);

		Node* nextNode = r->getLetterAt(fir - 'a' + 1);
		return track(nextNode, letrs);
	}

	void crushWords(std::string missedWord) {
		std::string mean = missedWord;

		Node* beginPoint = track(root, mean);
		if (beginPoint == nullptr) return;

		// khắc mục nhược điểm của crushWords bên dưới
		if (beginPoint->getSense()) std::cout << mean << "\n";
		crushWords(beginPoint, mean);
	}

};

