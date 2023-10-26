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
};

// this class contains hash table which map english and its meanings
class DictEng {
public:
	HardArray<Vocab*, DEFAULT_MAX_VOCAB> vocabs;
	LettersTree* lt = new LettersTree();

	DictEng() {
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

			while (vocabs.getAt(ind) != nullptr && vocabs.getAt(ind)->eng.compare(vcb->eng) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs.setAt(ind, vcb);
			lt->addLetter(vcb->eng);

		}
		fin.close();
	}

	int hashWord(std::string w) {
		int sum = 0;
		for (int i = 0; i < w.size(); i++) {
			sum += w[i] * (i + 1);
		}
		return sum % DEFAULT_MAX_VOCAB;
	}

	// three-component file
	DictEng(std::string sourceWords) {
		std::ifstream fin(sourceWords);
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



			while (vocabs.getAt(ind) != nullptr && vocabs.getAt(ind)->eng.compare(vcb->eng) != 0) {
				ind = (ind + 1) % DEFAULT_MAX_VOCAB;
			}

			vocabs.setAt(ind, vcb);
			lt->addLetter(vcb->eng);

		}
		fin.close();
	}

	~DictEng() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			delete vocabs.getAt(i);
		}
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

			if (userWord.size()) lt->crushWords(userWord);
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
		for (int i = 0; i < vocabs.getSize(); i++) {
			if (vocabs.getAt(i) != nullptr && vocabs.getAt(i)->eng.compare(word) == 0) {
				return true;
			}
		}
		return false;
	}

	// -------------------------------------------------- DISPLAY --------------------------------------------
	void lookUp() {
		std::string userWord = suggestWord();
		int ind = hashWord(userWord);

		while (vocabs.getAt(ind) != nullptr && vocabs.getAt(ind)->eng.compare(userWord) != 0) 
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;

		if (vocabs.getAt(ind) == nullptr) std::cout << "Don\'t have " << userWord << " in the dictionary\n";
		else vocabs.getAt(ind)->showBothMeaning();
	}

	void showHashTable() {
		for (int i = 0; i < DEFAULT_MAX_VOCAB; i++) {
			if (vocabs.getAt(i) != nullptr) {
				std::cout << "i=" << i << "; " << vocabs.getAt(i)->eng << "\n";
			}
		}
	}


	// ---------------------------------------------------- SEARCH ---------------------------------------------

	// return referrence pointer is pointing to a Vocab
	Vocab* searchWord(std::string engWord) {
		int ind = hashWord(engWord);
		while (vocabs.getAt(ind) != nullptr && vocabs.getAt(ind)->eng.compare(engWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}
		return vocabs.getAt(ind);
	}


	void getPracticeWords(HardArray<Vocab, 0>* prw) {
		std::ifstream fin("PracticeWords.txt");
		if (fin.fail()) {
			std::cout << "Fail open file, getPracticeWords\n";
			return;
		}

		HardArray<Vocab, 0>* pracWords = new HardArray<Vocab, 0>();

		std::string word;
		while (std::getline(fin, word)) {
			Vocab vc;
			vc.eng = word;

			std::getline(fin, word);
			vc.engMean = word;

			std::getline(fin, word);
			vc.vieMean = word;

			prw->add(vc);

		}

		fin.close();
	}

	// ----------------------------------------------- ADVANCED -------------------------------------------
	void playWordGame() {
		
		HardArray<Vocab, 0>* pracWords = new HardArray<Vocab, 0>();
		getPracticeWords(pracWords);

		// must have at least for word by default
		// 0->3 are default words are always exist in the file
		if (pracWords->getSize() <= 3) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}

		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, pracWords->getSize() - 1);
		std::uniform_int_distribution<int> dis2(0, 3);

		int numRightAnswer = 0;

		for (int i = 3; i < pracWords->getSize(); i++) {

			HardArray<std::string, 4> answers;

			// put randomly user word to answers

			// generate a random position in answers
			int ranPosAnswer = dis2(ge);
			// while the position have already had an answer
			while (answers.getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			// put one answer to the answers array
			answers.setAt(ranPosAnswer, pracWords->getAt(i).engMean);


			int p1, p2, p3;
			
			// chose randomly a sentence from the total list of practice words
			p1 = dis(ge);
			while (p1 == i) p1 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers.getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers.setAt(ranPosAnswer, pracWords->getAt(p1).engMean);


			p2 = dis(ge);
			while (p2 == p1 || p2 == i) p2 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers.getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers.setAt(ranPosAnswer, pracWords->getAt(p2).engMean);

			p3 = dis(ge);
			while (p3 == p1 || p3 == p2 || p3 == i) p3 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers.getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers.setAt(ranPosAnswer, pracWords->getAt(p3).engMean);

			askUser(pracWords->getAt(i), answers, numRightAnswer);

		}
		int numRealQuestions = pracWords->getSize() - 3;
		delete pracWords;
		
		wrapUp(numRightAnswer, numRealQuestions);
		
	}

	// why do we use & here
	void askUser(Vocab askedWord, HardArray<std::string, 4>& answers, int& rightAnswer) {
		std::cout << "What is the meaning of " << askedWord.eng << "?\n";

		char aa = 'A';
		for (int i = 0; i < 4; i++) {
			std::cout << aa << ". " << answers.getAt(i) << ".\n";
			aa += 1;
		}

		std::cout << "Your answer: ";
		std::string userAnswer;
		std::getline(std::cin, userAnswer);
		if (userAnswer[0] < 97) userAnswer[0] += 32;

		while (!(userAnswer[0] >= 97 && userAnswer[0] <= 100) && !(userAnswer[0] >= 65 && userAnswer[0] <= 68)) {
			std::cout << "invalid answer, try again: ";
			std::getline(std::cin, userAnswer);
		}

		if (userAnswer[0] < 97) userAnswer[0] += 32;

		if (answers.getAt(userAnswer[0] - 'a').compare(askedWord.engMean) == 0) {
			std::cout << "RIGHT.\n";
			rightAnswer++;
		}
		else {
			std::cout << "WRONG.\n";
		}
		std::cout << "-----------------------------------\n";
	}

	void wrapUp(int rightAnswer, int totalQuestions) {
		double result = double(rightAnswer) / totalQuestions;
		std::cout << "You was right " << result * 100 << "% of the total questions.\n";

		
		std::cout << "Do you want to remove some words from your practice list?(y/n).\n";
		std::string userCM;
		std::getline(std::cin, userCM);

		if (userCM.compare("y")==0) {
			removeFromPracticeList();
		}

		std::cout << "Do you want to add some words to practice list?(y/n).\n";
		std::getline(std::cin, userCM);

		if (userCM.compare("y") == 0) {
			addToPracticeList();
		}

		delete lt;
	}

	// -------------------------------------------- ADD -----------------------------------------

	// add the same word?
	void addToPracticeList() {
		DictEng* pracList = new DictEng("PracticeWords.txt");

		std::string control = "y";
		while (control.compare("y") == 0) {
			std::string userWord = this->suggestWord();
			Vocab* needToAdd = searchWord(userWord);

			if (needToAdd && !pracList->haveWord(userWord)) {
				pracList->addWord(needToAdd->eng, needToAdd->engMean, needToAdd->vieMean);
			}
			else {
				std::cout << "\'" << userWord << "\'" << " is unavailable.\n";
			}
			std::cout << "Add a different word?(y/n): ";
			std::getline(std::cin, control);
		}

		pracList->writeToFile("PracticeWords.txt");
		delete pracList;

	}

	void addWord(std::string engWord, std::string engMeaning, std::string vieMeaning) {
		if (this->haveWord(engWord)) return;
		
		int ind = hashWord(engWord);

		Vocab* vcb = new Vocab();
		vcb->eng = engWord;
		vcb->engMean = engMeaning;
		vcb->vieMean = vieMeaning;

		while (vocabs.getAt(ind) != nullptr && vocabs.getAt(ind)->eng.compare(vcb->eng) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}

		vocabs.setAt(ind, vcb);
		lt->addLetter(vcb->eng);

	}

	// -------------------------------------------- REMOVE ---------------------------------------
	void removeFromPracticeList() {
		DictEng* pracList = new DictEng("PracticeWords.txt");

		std::string control = "y";
		while (control.compare("y") == 0) {
			std::string userWord = pracList->suggestWord();
			pracList->removeWord(userWord);
			
			std::cout << "Remove a different word?(y/n): ";
			std::getline(std::cin, control);
		}

		pracList->writeToFile("PracticeWords.txt");
		
		delete pracList;

	}

	void removeWord(std::string engNeedToDelWord) {
		if (!haveWord(engNeedToDelWord)) return;

		int ind = hashWord(engNeedToDelWord);

		while (this->vocabs.getAt(ind) != nullptr && this->vocabs.getAt(ind)->eng.compare(engNeedToDelWord) != 0) {
			ind = (ind + 1) % DEFAULT_MAX_VOCAB;
		}
		Vocab* needToDel = vocabs.getAt(ind);
		delete needToDel;
		vocabs.setAt(ind, nullptr);
		this->lt->remove(engNeedToDelWord);
	}

	void writeToFile(std::string fileName) {
		std::ofstream fout(fileName);

		if (fout.fail()) {
			std::cout << "Can\'t open file to Write.\n";
			return;
		}

		for (int i = 0; i < this->vocabs.getSize(); i++) {
			if (this->vocabs.getAt(i) != nullptr) {
				fout << this->vocabs.getAt(i)->eng << "\n";
				fout << this->vocabs.getAt(i)->engMean << "\n";
				fout << this->vocabs.getAt(i)->vieMean << "\n";
			}
		}

		fout.close();
	}

};


/*

VẤN ĐỀ TRÙNG LẶP VÀ HỆ THỐNG HÓA


*/
