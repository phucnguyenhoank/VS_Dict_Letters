#pragma once

#include "DictEng.h"

class WordQuizGame: public DictEng {
public:
	// ----------------------------------------------- ADVANCED -------------------------------------------
	// 
	
	// CAN SUA LAI
	void playWordGame() {

		DynamicArray<Vocab*>* pracWords = prepare("PracticeWords.txt");

		if (pracWords == nullptr) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}

		int numRightAnswer = play(pracWords);
		int numRealQuestions = pracWords->getSize() - 3;

		delete pracWords;
		wrapUp(numRightAnswer, numRealQuestions);

	}

	DynamicArray<Vocab*>* prepare(std::string fileName) {
		DynamicArray<Vocab*>* pracWords = getPracticeWords("PracticeWords.txt");
		pracWords->add(new Vocab("joy", "a feeling of pleasure", "niem vui"));
		pracWords->add(new Vocab("hope", "a feeling of expectation", "hy vong"));
		pracWords->add(new Vocab("peace", "freedom from disturbance", "hoa binh"));
		if (pracWords->getSize() == 3) return nullptr;
		return pracWords;
	}

	int play(DynamicArray<Vocab*>* pracWords) {
		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, pracWords->getSize() - 1);
		std::uniform_int_distribution<int> dis2(0, 3);

		int numRightAnswer = 0;

		for (int i = 0; i < pracWords->getSize() - 3; i++) {

			DynamicArray<std::string> *answers = new DynamicArray<std::string>();
			answers->resize(4);

			// put randomly user word to answers

			// generate a random position in answers
			int ranPosAnswer = dis2(ge);
			// while the position have already had an answer
			while (answers->getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			// put one answer to the answers array
			answers->setAt(ranPosAnswer, pracWords->getAt(i)->engMean);


			int p1, p2, p3;

			// chose randomly a sentence from the total list of practice words
			p1 = dis(ge);
			while (p1 == i) p1 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers->getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers->setAt(ranPosAnswer, pracWords->getAt(p1)->engMean);

			p2 = dis(ge);
			while (p2 == p1 || p2 == i) p2 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers->getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers->setAt(ranPosAnswer, pracWords->getAt(p2)->engMean);

			p3 = dis(ge);
			while (p3 == p1 || p3 == p2 || p3 == i) p3 = dis(ge);
			ranPosAnswer = dis2(ge);
			while (answers->getAt(ranPosAnswer).compare("")) ranPosAnswer = dis2(ge);
			answers->setAt(ranPosAnswer, pracWords->getAt(p3)->engMean);

			askUser(pracWords->getAt(i), answers, numRightAnswer);

		}
		return numRightAnswer;
	}

	// why do we use & here
	void askUser(Vocab* askedWord, DynamicArray<std::string>* answers, int& rightAnswer) {
		std::cout << "What is the meaning of " << askedWord->eng << "?\n";

		char aa = 'A';
		for (int i = 0; i < 4; i++) {
			std::cout << aa << ". " << answers->getAt(i) << ".\n";
			aa += 1;
		}

		std::cout << "Your answer: ";
		std::string userAnswer;
		std::getline(std::cin, userAnswer);
		
		// chi nhap chu thuong

		if (answers->getAt(userAnswer[0] - 'a').compare(askedWord->engMean) == 0) {
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

		while (userCM.compare("y") == 0) {
			removeFromPracticeList("PracticeWords.txt");

			std::cout << "continue to remove?(y): ";
			std::getline(std::cin, userCM);
		}

		std::cout << "Do you want to add some words to practice list?(y/n).\n";
		std::getline(std::cin, userCM);

		while (userCM.compare("y") == 0) {
			addToPracticeList("PracticeWords.txt");

			std::cout << "continue to add?(y): ";
			std::getline(std::cin, userCM);
		}

	}
};
