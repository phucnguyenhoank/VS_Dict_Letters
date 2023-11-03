#pragma once

#include "LettersTree.h"
#include <conio.h>
#include <random>


#define DEFAULT_MAX_VOCAB 101

class Vocab {
public:
	std::string eng, engMean, vieMean;
	void showEngMeaning() {
		std::cout << "English meaning: " << this->engMean << "\n";
	}
	void showVieMeaning() {
		std::cout << "Vietnamese meaning: " << this->vieMean << "\n";
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
	Vocab(std::string eng, std::string engMean, std::string vieMean) {
		this->eng = eng;
		this->engMean = engMean;
		this->vieMean = vieMean;
	}
	
};

// this class contains hash table which map english and its meanings
class EngVieDict {
private:
	DynamicArray<Vocab*> *vocabs;
	LettersTree* lettersTree;

public:
	int hashWord(std::string w) {
		int sum = 0;
		for (int i = 0; i < w.size(); i++) {
			sum += w[i] * (i + 1);
		}
		return sum % DEFAULT_MAX_VOCAB;
	}

	EngVieDict() {
		vocabs = new DynamicArray<Vocab*>();
		vocabs->resize(DEFAULT_MAX_VOCAB);
		lettersTree = new LettersTree();

		std::ifstream fin("wordsmy.txt");
		if (fin.fail()) return;

		std::string temp;
		while (std::getline(fin, temp)) {
			int ind = hashWord(temp);

			Vocab* vcb = new Vocab();
			vcb->eng = temp;
			std::getline(fin, temp);
			vcb->engMean = temp;
			std::getline(fin, temp);
			vcb->vieMean = temp;

			while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->eng.compare(vcb->eng) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs->setAt(ind, vcb);
			lettersTree->addLetter(vcb->eng);

		}
		fin.close();
	}

	// Like read from file
	EngVieDict(std::string fileName) {
		vocabs = new DynamicArray<Vocab*>();
		vocabs->resize(DEFAULT_MAX_VOCAB);
		lettersTree = new LettersTree();

		std::ifstream fin(fileName);
		if (fin.fail()) return;

		std::string temp;
		while (std::getline(fin, temp)) {
			int ind = hashWord(temp);

			Vocab* vcb = new Vocab();
			vcb->eng = temp;
			std::getline(fin, temp);
			vcb->engMean = temp;
			std::getline(fin, temp);
			vcb->vieMean = temp;


			while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->eng.compare(vcb->eng) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs->setAt(ind, vcb);
			lettersTree->addLetter(vcb->eng);

		}
		fin.close();
	}

	~EngVieDict() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			delete vocabs->getAt(i);
		}
		delete lettersTree;
	}

	// --------------------------------------------- EFFECT --------------------------------------------
	std::string suggestWord() {
		
		// ENTER: 13
		// BACKSPACE: 8
		// SPACE: 32
		// '\n': 10
		
		std::string userWord;
		char userChar = 14;

		do {
			system("cls");
			std::cout << "enter a word: " << userWord << "_\n";

			if (userWord.size()) lettersTree->crushWords(userWord);
			userChar = _getch();
			// xu ly cac phim rac
			
			if (userChar == 8) {
				if (userWord.size() == 0) continue;
				userWord.pop_back();
			}
			else if (userChar >= 97 && userChar <= 122) {
				userWord += userChar;
			}
			else if (userChar >= 65 && userChar <= 90) {
				userChar += 32;
				userWord += userChar;
			}

		} while (userChar != 13);
		system("cls");
		return userWord;
	}

	// --------------------------------------------------- CHECKING -----------------------------------------
	bool haveWord(std::string word) {
		for (int i = 0; i < vocabs->getSize(); i++) {
			if (vocabs->getAt(i) != nullptr && vocabs->getAt(i)->eng.compare(word) == 0) {
				return true;
			}
		}
		return false;
	}

	// -------------------------------------------------- DISPLAY --------------------------------------------
	void lookUp() {
		std::string userWord = suggestWord();
		int ind = hashWord(userWord);

		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->eng.compare(userWord) != 0) 
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;

		if (vocabs->getAt(ind) == nullptr) std::cout << "Don\'t have " << userWord << " in the dictionary\n";
		else vocabs->getAt(ind)->showBothMeaning();
	}

	void showHashTable() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			if (vocabs->getAt(i) != nullptr) {
				std::cout << "i=" << i << "; " << vocabs->getAt(i)->eng << "\n";
			}
		}
	}


	// ---------------------------------------------------- SEARCH ---------------------------------------------

	// return referrence pointer is pointing to a Vocab
	Vocab* searchWord(std::string engWord) {
		int ind = hashWord(engWord);
		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->eng.compare(engWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}
		return vocabs->getAt(ind);
	}

	DynamicArray<Vocab*>* getPracticeWords(std::string fileName) {
		DynamicArray<Vocab*>* prw = new DynamicArray<Vocab*>();

		std::ifstream fin(fileName);
		if (fin.fail()) {
			std::cout << "getPracticeWords\n";
			return nullptr;
		}

		std::string word;
		while (std::getline(fin, word)) {
			Vocab* vc = new Vocab();
			vc->eng = word;

			std::getline(fin, word);
			vc->engMean = word;

			std::getline(fin, word);
			vc->vieMean = word;

			prw->add(vc);

		}
		fin.close();
		return prw;
	}

	// -------------------------------------------- ADD -----------------------------------------

	void addWord(std::string engWord, std::string engMeaning, std::string vieMeaning) {
		if (haveWord(engWord)) return;

		int ind = hashWord(engWord);

		Vocab* vcb = new Vocab(engWord, engMeaning, vieMeaning);

		while (vocabs->getAt(ind) != nullptr && vocabs->getAt(ind)->eng.compare(vcb->eng) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}

		vocabs->setAt(ind, vcb);
		lettersTree->addLetter(vcb->eng);

	}

	void addToPracticeList(std::string fileName) {
		EngVieDict* pracList = new EngVieDict(fileName);

		std::string userWord = this->suggestWord();
		Vocab* needToAdd = searchWord(userWord);

		if (needToAdd && !pracList->haveWord(userWord)) {
			pracList->addWord(needToAdd->eng, needToAdd->engMean, needToAdd->vieMean);
		}
		else {
			std::cout << "\'" << userWord << "\'" << " already exist or unavailable.\n";
		}

		pracList->writeToFile(fileName);
		delete pracList;
	}

	// -------------------------------------------- REMOVE ---------------------------------------

	void removeWord(std::string engNeedToDelWord) {
		if (!haveWord(engNeedToDelWord)) return;

		int ind = hashWord(engNeedToDelWord);

		while (this->vocabs->getAt(ind) != nullptr && this->vocabs->getAt(ind)->eng.compare(engNeedToDelWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}
		Vocab* needToDel = vocabs->getAt(ind);
		delete needToDel;
		vocabs->setAt(ind, nullptr);
		lettersTree->remove(engNeedToDelWord);
	}

	void removeFromPracticeList(std::string fileName) {
		EngVieDict* pracList = new EngVieDict(fileName);

		std::string userWord = pracList->suggestWord();
			
		if (pracList->haveWord(userWord)) {
			pracList->removeWord(userWord);
		}
		else {
			std::cout << "\'" << userWord << "\'" << " is not in the practice-word list.\n";
		}

		pracList->writeToFile(fileName);
		delete pracList;
	}

	void writeToFile(std::string fileName) {
		std::ofstream fout(fileName);

		if (fout.fail()) {
			std::cout << "Can\'t open file to Write.\n";
			return;
		}

		for (int i = 0; i < this->vocabs->getSize(); i++) {
			if (this->vocabs->getAt(i) != nullptr) {
				fout << this->vocabs->getAt(i)->eng << "\n";
				fout << this->vocabs->getAt(i)->engMean << "\n";
				fout << this->vocabs->getAt(i)->vieMean << "\n";
			}
		}

		fout.close();
	}

};
