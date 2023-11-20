#pragma once

#include "LettersTree.h"
#include "ConsoleEffect.h"
#include <conio.h>
#include <random>

// a prime number
#define DEFAULT_MAX_VOCAB 401

class Vocab {
private:
	std::string eng, engMeaning, vieMeaning;
public:
	std::string getEng() const {
		return eng;
	}
	std::string getEngMeaning() const {
		return engMeaning;
	}
	std::string getVieMeaning() const {
		return vieMeaning;
	}

	void setEng(std::string eng) {
		this->eng = eng;
	}
	void setEngMeaning(std::string engMeaning) {
		this->engMeaning = engMeaning;
	}
	void setVieMeaning(std::string vieMeaning) {
		this->vieMeaning = vieMeaning;
	}

	void showEngMeaning() {
		std::cout << "eng-meaning: " << engMeaning << "\n";
	}
	void showVieMeaning() {
		std::cout << "viet-meaning: " << vieMeaning << "\n";
	}
	void showBothMeaning() {
		showEngMeaning();
		showVieMeaning();
	}

	int getLen() {
		return eng.size();
	}

	void showMissingWord(int missingPos) {
		for (int i = 0; i < eng.size(); i++) {
			if (i == missingPos) {
				std::cout << "_";
			}
			else {
				std::cout << eng[i];
			}
		}
	}

	Vocab() {

	}

	Vocab(std::string eng, std::string engMeaning, std::string vieMeaning) {
		this->eng = eng;
		this->engMeaning = engMeaning;
		this->vieMeaning = vieMeaning;
	}
	
};

// this class contains hash table which map english and its meanings
class EngVieDict {
private:
	DynamicArray<Vocab*> *vocabs;
	LettersTree* lettersTree;

protected:
	// ---------------------------------------------------- SEARCH ---------------------------------------------

	// return a reference pointer pointing to a Vocab
	// return null if it does not exist
	const Vocab* searchWord(std::string engWord) {
		int ind = hashWord(engWord);
		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->getEng().compare(engWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}
		return vocabs->getAt(ind);
	}

	// read the list of words from "fileName"
	// uses dynamic allocating
	// return a pointer pointing to a DynamicArray<Vocab*>
	// this function doesn't return a null pointer
	DynamicArray<Vocab*>* getPracticeWords(std::string fileName) {
		DynamicArray<Vocab*>* prw = new DynamicArray<Vocab*>();

		std::ifstream fin(fileName);
		if (fin.fail()) {
			std::cout << "getPracticeWords: failed in open file\n";
			return prw;
		}

		std::string word;
		while (std::getline(fin, word)) {
			Vocab* vc = new Vocab();
			vc->setEng(word);

			std::getline(fin, word);
			vc->setEngMeaning(word);

			std::getline(fin, word);
			vc->setVieMeaning(word);

			prw->add(vc);

		}
		fin.close();
		return prw;
	}


public:
	
	// --------------------------------------------- INITIALIZING --------------------------------------------

	// read words from default source-word file: Words.txt
	EngVieDict() {
		vocabs = new DynamicArray<Vocab*>();
		vocabs->resize(DEFAULT_MAX_VOCAB);
		lettersTree = new LettersTree();

		std::ifstream fin("Words.txt");
		if (fin.fail()) return;

		std::string temp;
		while (std::getline(fin, temp)) {
			int ind = hashWord(temp);

			Vocab* vcb = new Vocab();
			vcb->setEng(temp);
			std::getline(fin, temp);
			vcb->setEngMeaning(temp);
			std::getline(fin, temp);
			vcb->setVieMeaning(temp);

			while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->getEng().compare(vcb->getEng()) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs->setAt(ind, vcb);
			lettersTree->pressWord(vcb->getEng());
		}
		fin.close();
	}

	// read words from a specific file
	// warning: file must has a appropriate structure
	EngVieDict(std::string fileName) {
		vocabs = new DynamicArray<Vocab*>(DEFAULT_MAX_VOCAB);
		// vocabs->resize(DEFAULT_MAX_VOCAB);
		lettersTree = new LettersTree();

		std::ifstream fin(fileName);
		if (fin.fail()) return;

		std::string temp;
		while (std::getline(fin, temp)) {
			int ind = hashWord(temp);

			Vocab* vcb = new Vocab();
			vcb->setEng(temp);
			std::getline(fin, temp);
			vcb->setEngMeaning(temp);
			std::getline(fin, temp);
			vcb->setVieMeaning(temp);


			while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->getEng().compare(vcb->getEng()) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs->setAt(ind, vcb);
			lettersTree->pressWord(vcb->getEng());
		}
		fin.close();
	}

	~EngVieDict() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) delete vocabs->getAt(i);
		delete vocabs;
		delete lettersTree;
	}

	// --------------------------------------------- EFFECT --------------------------------------------

	// get user string concurrently with suggesting the words of the dictionary
	std::string suggestWord() {
		// ENTER: 13
		// BACKSPACE: 8
		// SPACE: 32
		// '\n': 10
		
		std::string userWord;
		char userChar = 14; // just a valid num

		do {
			system("cls");
			std::cout << "your word: " << userWord;
			ConsoleEffect::saveCurrentCursor();
			
			std::cout << "\n";
			std::cout << "---------------\n";
			std::cout << "valid words:\n";
			if (userWord.size()) lettersTree->sweepWords(userWord);
			ConsoleEffect::loadSavedCursor();
			
			userChar = _getch();
			if (userChar < 8 || userChar>122) continue;
			else if (userChar == 8) {
				if (userWord.size() == 0) continue;
				userWord.pop_back();
			}
			else if (userChar >= 97 && userChar <= 122) userWord += userChar;
			else if (userChar >= 65 && userChar <= 90) {
				userChar += 32;
				userWord += userChar;
			}

		} while (userChar != 13);
		
		system("cls");
		return userWord;
	}


	// --------------------------------------------------- CHECKING and GETTING -----------------------------------------

	// return true if the word is in the dictionary
	bool haveWord(std::string word) {
		for (int i = 0; i < vocabs->getSize(); i++) {
			if (vocabs->getAt(i) != nullptr && vocabs->getAt(i)->getEng().compare(word) == 0) {
				return true;
			}
		}
		return false;
	}

	// QUESTION: why do we use DEFAULT_MAX_VOCAB?
	// return the current num of existing words in the dictionary
	int getNumOfWord() {
		int num = 0;
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			if (vocabs->getAt(i) != nullptr) {
				num++;
			}
		}
		return num;
	}

	// return a hash key of a string
	int hashWord(std::string w) {
		int sum = 0;
		for (int i = 0; i < w.size(); i++) {
			sum += w[i] * (i + 1);
		}
		return sum % DEFAULT_MAX_VOCAB;
	}


	// -------------------------------------------------- DISPLAY --------------------------------------------

	// get user string and show the meaning of that word if possible
	void lookUp() {
		std::string userWord = suggestWord();
		int ind = hashWord(userWord);

		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->getEng().compare(userWord) != 0)
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;

		if (vocabs->getAt(ind) == nullptr) std::cout << "Don\'t have " << userWord << " in the dictionary\n";
		else vocabs->getAt(ind)->showBothMeaning();
	}

	// show the whole keys and values of the dictionary, which really is just a hash table
	void showHashTable() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			if (vocabs->getAt(i) != nullptr) {
				std::cout << "i=" << i << "; " << vocabs->getAt(i)->getEng() << "\n";
			}
		}
	}


	// -------------------------------------------- ADD -----------------------------------------

	// 1: complete
	// 2: the wanted-word already exists in the list
	int addWord(std::string engWord, std::string engMeaning, std::string vieMeaning) {
		if (haveWord(engWord)) return 2;

		int ind = hashWord(engWord);

		Vocab* vcb = new Vocab(engWord, engMeaning, vieMeaning);
		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->getEng().compare(vcb->getEng()) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}

		vocabs->setAt(ind, vcb);
		lettersTree->pressWord(vcb->getEng());
		return 1;
	}

	// 1: complete
	// 2: the wanted-word already exists in the list
	// 3: don't have the wanted-word in the list
	int addToPracticeList(std::string fileName) {
		EngVieDict* practiceList = new EngVieDict(fileName);

		std::string userWord = suggestWord();
		const Vocab* needToAdd = searchWord(userWord);

		if (practiceList->haveWord(userWord)) return 2;
		if (needToAdd) {
			practiceList->addWord(needToAdd->getEng(), needToAdd->getEngMeaning(), needToAdd->getVieMeaning());
			practiceList->writeToFile(fileName);
			delete practiceList; // wrong here
			return 1;
		}
		else {
			practiceList->writeToFile(fileName);
			delete practiceList;
			return 3;
		}
	}


	// -------------------------------------------- REMOVE ---------------------------------------
	
	// (no happen): 0: list is empty 
	// 1: complete
	// 2: don't have the wanted-word in the list
	int removeWord(std::string engNeedToDelWord) {
		if (!haveWord(engNeedToDelWord)) return 2;

		int ind = hashWord(engNeedToDelWord);
		while (this->vocabs->getAt(ind) != nullptr && this->vocabs->getAt(ind)->getEng().compare(engNeedToDelWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}

		Vocab* needToDel = vocabs->getAt(ind);
		delete needToDel;
		vocabs->setAt(ind, nullptr);
		lettersTree->remove(engNeedToDelWord);

		return 1;
	}

	// 0: list is empty
	// 1: complete
	// 2: don't have the wanted-word in the list
	int removeFromPracticeList(std::string fileName) {
		EngVieDict* practiceList = new EngVieDict(fileName);

		if (practiceList->getNumOfWord()==0) return 0;

		std::string userWord = practiceList->suggestWord();
		
		if (practiceList->haveWord(userWord)) practiceList->removeWord(userWord);
		else return 2;

		practiceList->writeToFile(fileName);
		delete practiceList;

		return 1;
	}

	// write all the information to a file
	// 1: complete
	// 0: something went wrong
	int writeToFile(std::string fileName) {
		std::ofstream fout(fileName);
		if (fout.fail()) return 0;

		for (int i = 0; i < this->vocabs->getSize(); i++) {
			if (this->vocabs->getAt(i) != nullptr) {
				fout << this->vocabs->getAt(i)->getEng() << "\n";
				fout << this->vocabs->getAt(i)->getEngMeaning() << "\n";
				fout << this->vocabs->getAt(i)->getVieMeaning() << "\n";
			}
		}

		fout.close();
		return 1;
	}

};
