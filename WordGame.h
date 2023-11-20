/*

This class is a dictionary with games

*/

#pragma once

#include "EngVieDict.h"
class WordGame: public EngVieDict {
private:
	//											-------------- QUIZ GAME ---------------

	bool isInteger(int& n, std::string s) {
		try {
			n = std::stoi(s);
			return true;
		}
		catch (...) {
			return false;
		}
	}

	// read the list of words
	// return a pointer which has DynamicArray<Vocab*>* type
	// return null if the list is empty
	DynamicArray<Vocab*>* preparePractice(std::string fileName) {
		DynamicArray<Vocab*>* practiceWords = getPracticeWords("PracticeWords.txt");
		if (practiceWords->getSize() == 0) {
			delete practiceWords;
			return nullptr;
		}
		return practiceWords;
	}

	// always contains these default words, so that the list won't be empty
	void addDefaultVocabs(DynamicArray<Vocab*>* listVocabs) {
		listVocabs->add(new Vocab("joy", "delight, gladness, pleasure", "niem vui"));
		listVocabs->add(new Vocab("hope", "aim, dream, goal", "hy vong"));
		listVocabs->add(new Vocab("peace", "accord, truce, agreement", "hoa binh"));
	}

	// Games will only take in words in practicWords list (other than default ones), and return num (the amount of correct answers given by the player)
	// numPlayedWords is the the total of questions the user has played, that mean the game can end at anytime the user wants
	int getStartedQuizzes(DynamicArray<Vocab*>* practiceWords, int& numPlayedWords) {
		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, practiceWords->getSize() - 1);
		std::uniform_int_distribution<int> dis2(0, 3);

		int numRightAnswer = numPlayedWords = 0;

		// get words from practiceWords list in order
		for (int i = 0; i < practiceWords->getSize() - 3; i++) {

			// create an array in which will store 4 sentences, these 4 sentences are options for the user to choose from
			DynamicArray<std::string>* answers = new DynamicArray<std::string>(4);

			// randomly put user word to answers
			// generate a random position in answers
			int randomAnswerPos = dis2(ge);
			// while the position have already had an answer
			while (answers->getAt(randomAnswerPos).compare("")) randomAnswerPos = dis2(ge);
			// put one answer to the answers array
			answers->setAt(randomAnswerPos, practiceWords->getAt(i)->getEngMeaning());

			// there random position will get in the list 
			int p1, p2, p3;

			// randomly choose three sentences from the father list of practice words
			p1 = dis(ge);
			while (p1 == i) p1 = dis(ge);
			randomAnswerPos = dis2(ge);
			while (answers->getAt(randomAnswerPos).compare("")) randomAnswerPos = dis2(ge);
			answers->setAt(randomAnswerPos, practiceWords->getAt(p1)->getEngMeaning());

			p2 = dis(ge);
			while (p2 == p1 || p2 == i) p2 = dis(ge);
			randomAnswerPos = dis2(ge);
			while (answers->getAt(randomAnswerPos).compare("")) randomAnswerPos = dis2(ge);
			answers->setAt(randomAnswerPos, practiceWords->getAt(p2)->getEngMeaning());

			p3 = dis(ge);
			while (p3 == p1 || p3 == p2 || p3 == i) p3 = dis(ge);
			randomAnswerPos = dis2(ge);
			while (answers->getAt(randomAnswerPos).compare("")) randomAnswerPos = dis2(ge);
			answers->setAt(randomAnswerPos, practiceWords->getAt(p3)->getEngMeaning());

			if (!askUserABCD(practiceWords->getAt(i), answers, numRightAnswer)) {
				return numRightAnswer;
			}
			else {
				numPlayedWords++;
			}
		}
		return numRightAnswer;
	}

	bool askUserABCD_CheckInput(std::string userAnswer) {
		if (userAnswer.length() != 1) return false;

		if ((userAnswer[0] >= 'A' && userAnswer[0] <= 'D') || (userAnswer[0] >= 'a' && userAnswer[0] <= 'd') || !userAnswer.compare("g")) {
			return true;
		}
		else return false;
	}

	// NOTE: this function is only used for "getStartedQuizzes"
	// askedWord: the word you want to ask
	// answers: contain 4 sentences, one of which is the correct answer of the askedWord
	// rightAnswer increases by 1 if user answered correctly
	// return 1 if ending normally
	// return 0 if user want to exit
	int askUserABCD(Vocab* askedWord, DynamicArray<std::string>* answers, int& rightAnswer) {
		std::cout << "What is the meaning of "; ConsoleEffect::foregroundGreenB(askedWord->getEng()); std::cout << "?\n";

		char aa = 'A';
		for (int i = 0; i < 4; i++) {
			std::cout << aa << ". " << answers->getAt(i) << ".\n";
			aa += 1;
		}

		std::cout << "Your answer: ";
		std::string userAnswer;
		std::getline(std::cin, userAnswer);

		while (!askUserABCD_CheckInput(userAnswer)) {
			ConsoleEffect::foregroundRed("confusing answer, try again: ");
			std::getline(std::cin, userAnswer);
		}

		// decapitalize A,B,C,D from userAnswer
		if (userAnswer[0] >= 'A' && userAnswer[0] <= 'D') userAnswer[0] += 32;
		if (userAnswer[0] == 'g') {
			std::cout << "----------------exited----------------\n";
			return 0;
		}
		if (answers->getAt(userAnswer[0] - 'a').compare(askedWord->getEngMeaning()) == 0) {
			ConsoleEffect::foregroundGreen("correct\n");
			rightAnswer++;
		}
		else {
			ConsoleEffect::foregroundRed("incorrect\n");
		}
		std::cout << "-----------------------------------\n";
		return 1;
	}


	//											-------------- MISSING WORDS GAME ---------------

	bool isLetterOrQuitCommand(std::string s) {
		if (s.length() != 1) return false;
		char c = s[0];
		if (c >= 'a' && c <= 'z' || c == '0') return true;
		return false;
	}

	int getStartedMissingLetters(DynamicArray<Vocab*>* practiceWords, int& numPlayedWords) {
		std::random_device rd;
		std::mt19937 ge(rd());

		int numRightAnswer = numPlayedWords = 0;

		for (int i = 0; i < practiceWords->getSize(); i++) {
			std::uniform_int_distribution<int> dis(0, practiceWords->getAt(i)->getLen() - 1);
			int missingPosInTheWord = dis(ge);
			practiceWords->getAt(i)->showMissingWord(missingPosInTheWord);
			std::cout << "\n";

			std::cout << "the missing letter is?: ";
			std::string s;
			std::getline(std::cin, s);


			while (!isLetterOrQuitCommand(s)) {
				std::cout << "invalid command, try again: ";
				std::getline(std::cin, s);
			}

			char missingLetter = s[0];

			if (missingLetter == '0') {
				std::cout << "---------------exited--------------\n";
				return numRightAnswer;
			}

			if (missingLetter == practiceWords->getAt(i)->getEng()[missingPosInTheWord]) {
				std::cout << "correct w(^o^)W\n";
				numRightAnswer++;
			}
			else {
				std::cout << "incorrect (T^T) but keep it up\n";
			}
			numPlayedWords++;
			std::cout << "------------------------\n";

		}

		return numRightAnswer;
	}


	//                                          -------------- HIDING WORDS GAME ---------------
	
	// dir (directions):
	// 1: left to right
	// 2: top to bottom
	// 3: top-left to bottom-right
	struct BoardGameAnswer {
		int row, col, dir;
		std::string word;
		BoardGameAnswer() {
			row = col = dir = 0;
		}
		BoardGameAnswer(int row, int col, int dir, std::string word) {
			this->row = row;
			this->col = col;
			this->dir = dir;
			this->word = word;
		}

		bool equals(BoardGameAnswer other) {
			if (row == other.row && col == other.col && dir == other.dir && (word.compare(other.word) == 0)) {
				return true;
			}
			return false;
		}

		bool onlyCompareWord(BoardGameAnswer other) {
			if (word.compare(other.word) == 0) return true;
			return false;
		}

	};

	// BECAREFUL, only take in valid arguments
	bool belongAnswerArea(BoardGameAnswer answer, int row, int col) {
		switch (answer.dir) {
		case 1:
			// left to right
			if (row != answer.row || !(col >= answer.col && col < answer.col + answer.word.length())) return false;
			break;
		case 2:
			// top to bottom
			if (col != answer.col || !(row >= answer.row && row < answer.row + answer.word.length())) return false;
			break;
		case 3:
			// top-left to bottom-right
			int i = answer.row;
			int j = answer.col;
			int l = answer.word.length();
			while (i < answer.row + l && j < answer.col + l) {
				if (i == row && j == col) return true;
				i++;
				j++;
			}
			return false;
		}
		return true;
	}

	// visual effects (print colors for words in ans array)
	void printBoard(char** board, int n, DynamicArray<BoardGameAnswer>* ans) {
		if (ans->getSize() == 0) {
			printBoard(board, n);
			return;
		}
		std::cout << "\t";
		for (int i = 0; i < n; i++) std::cout << i << "  ";
		std::cout << "\n\n\n";
		for (int i = 0; i < n; i++) {
			std::cout << i << "\t";
			for (int j = 0; j < n; j++) {
				bool havePrinted = false;
				for (int k = 0; k < ans->getSize(); k++) {
					if (belongAnswerArea(ans->getAt(k), i, j)) {
						std::string redText = "\x1b[91m";
						std::string greenText = "\x1b[92m";
						std::string defaultText = "\x1b[0m";
						if (i == ans->getAt(k).row && j == ans->getAt(k).col)
							std::cout << redText << board[i][j] << defaultText << "  ";
						else
							std::cout << greenText << board[i][j] << defaultText << "  ";

						havePrinted = true;
						break;
					}
				}
				if (!havePrinted) std::cout << board[i][j] << "  ";
			}
			std::cout << "\n\n";
		}
	}

	// white-black colors
	void printBoard(char** board, int n) {
		std::cout << "\t";
		for (int i = 0; i < n; i++) std::cout << i << "  ";
		std::cout << "\n\n\n";

		for (int i = 0; i < n; i++) {
			std::cout << i << "\t";
			for (int j = 0; j < n; j++) {
				std::cout << board[i][j] << "  ";
			}
			std::cout << "\n\n";
		}
	}

	// dir (directions):
	// 1: left to right
	// 2: top to bottpm
	// 3: left-top to right-bottom
	// WARING: Input must be valid
	bool canPlaceWord(char** board, int n, int row, int col, int direction, std::string word) {
		if (row + word.length() >= n || col + word.length() >= n) return false;
		int i = row;
		int j = col;
		for (char letter : word) {
			// if the position hasn't been placed or has been placed but has the same letter 
			if (board[i][j] == '0' || board[i][j] == letter) {
				switch (direction) {
				case 1: j++; break;
				case 2: i++; break;
				case 3: i++; j++; break;
				}
			}
			else return false;
		}
		return true;

	}

	// WARING: Inputs must be CHECKED and CAN be placed in the board
	void placeWord(char** board, int n, int row, int col, int direction, std::string word) {
		int i = row;
		int j = col;
		for (char letter : word) {
			board[i][j] = letter - ' ';
			switch (direction) {
			case 1: j++; break;
			case 2: i++; break;
			case 3: i++; j++; break;
			}
		}
	}

	// WARING: Inputs must be CHECKED
	void putMissingLettersForTheBoard(char** board, int n) {
		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis('A', 'Z');
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == '0') {
					board[i][j] = dis(ge);
				}
			}
		}
	}

	// WARNING: Might not work if n is too big or is allocated falsely
	// return a 2D-Array
	// n must be sufficient
	char** initialBoard(int n, char defValue = '0') {
		char** board = new char* [n];
		for (int i = 0; i < n; i++) board[i] = new char[n];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = defValue;
			}
		}

		return board;
	}

	void clearBoard(char** board, int n) {
		for (int i = 0; i < n; i++) delete[] board[i];
		delete[] board;
	}

	// return a 2D-Array, each cell of this array contains a letter
	// some rows, columns, or diagonals is arranged with meaning of words (is parameter) list
	// answers is going to be allocated, its contents depend on words (is parameter) contents
	char** createWordLetterBoard(int n, DynamicArray<std::string>* words, DynamicArray<BoardGameAnswer>*& answers) {
		char** board = initialBoard(n, '0');

		answers = new DynamicArray<BoardGameAnswer>();

		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, n - 1);
		std::uniform_int_distribution<int> dis2(1, 3);

		for (int i = 0; i < words->getSize(); i++) {
			std::string word = words->getAt(i);
			int row = dis(ge);
			int col = dis(ge);
			int dir = dis2(ge);

			// warning, haven't fixed yet
			// can be an infinite loop if there's no available spot to place
			while (!canPlaceWord(board, n, row, col, dir, word)) {
				row = dis(ge);
				col = dis(ge);
				dir = dis2(ge);
			}

			placeWord(board, n, row, col, dir, word);
			answers->add(BoardGameAnswer(row, col, dir, word));
		}

		putMissingLettersForTheBoard(board, n);

		return board;
	}

	// only compare word-field
	int haveAnswerIn(DynamicArray<BoardGameAnswer>* answers, BoardGameAnswer aAnswer) {
		for (int i = 0; i < answers->getSize(); i++) {
			if (answers->getAt(i).onlyCompareWord(aAnswer)) return i;
		}
		return -1;
	}

	void getStartedHidingWordGame(char** board, int n, DynamicArray<BoardGameAnswer>* answers) {
		DynamicArray<BoardGameAnswer>* userCorrectedAnswers = new DynamicArray<BoardGameAnswer>(0);

		while (userCorrectedAnswers->getSize() < answers->getSize()) {
			system("cls");
			printBoard(board, n, userCorrectedAnswers);
			ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
			std::cout << "You have found: " << userCorrectedAnswers->getSize() << "/" << answers->getSize() << " words\n";
			std::cout << "Press\n";
			std::cout << "ENTER -> answer\n";
			std::cout << "2 -> see answers\n";
			std::cout << "q -> quit\n";

			char userCommand;
			userCommand = _getch();

			BoardGameAnswer userAnswer;
			if (userCommand == 13) {
				std::cout << "The word you\'ve found is: ";
				std::getline(std::cin, userAnswer.word);
			}
			else if (userCommand == '2') {
				ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
				ConsoleEffect::foregroundYellowB("\t\tDirections\n");
				std::cout << "1: left to right\n";
				std::cout << "2: top to bottom\n";
				std::cout << "3: top-left to bottom-right\n";
				ConsoleEffect::foregroundYellowB("\t\tAnswers\n");
				for (int i = 0; i < answers->getSize(); i++) {
					std::cout << "(row:" << answers->getAt(i).row << ", col:" <<
						answers->getAt(i).col << ", dir:" << answers->getAt(i).dir << "): " <<
						answers->getAt(i).word << "\n";
				}
				ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
				system("pause");
			}
			else if (userCommand == 'q') {
				std::cout << "Do you want to quit?(y): ";
				std::cin >> userCommand;
				std::cin.ignore();
				if (userCommand == 'y') break;
			}

			int indexRightAnswer = haveAnswerIn(answers, userAnswer);
			if (indexRightAnswer != -1) {
				userAnswer.row = answers->getAt(indexRightAnswer).row;
				userAnswer.col = answers->getAt(indexRightAnswer).col;
				userAnswer.dir = answers->getAt(indexRightAnswer).dir;
				userCorrectedAnswers->add(userAnswer);
			}

		}
		ConsoleEffect::foregroundBlueB("Your achievements!!!\n");
		std::cout << "You have found: " << userCorrectedAnswers->getSize() << "/" << answers->getSize() << " words\n";
		printBoard(board, n, userCorrectedAnswers);
	}


public:

	void playQuizGame() {
		ConsoleEffect::foregroundYellow("WELCOME TO QUIZ GAME\n");
		std::cout << "Enter ";
		ConsoleEffect::foregroundYellow("A, B, C or D"); std::cout << " to answer, ";
		ConsoleEffect::foregroundYellow("g"); std::cout << " to give up!\n";

		// read the whole words from the file
		DynamicArray<Vocab*>* mainPracticeWords = preparePractice("PracticeWords.txt");

		int numOfWordsUserWantToPlay;

		if (mainPracticeWords == nullptr) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}
		else {
			std::cout << "--------------------------\n";
			std::cout << "Let's GET STARTED\n";
			std::cout << "--------------------------\n";
			std::string s;
			std::cout << "How many words do you want to play?";
			std::cout << " (must be <= " << mainPracticeWords->getSize() << "): ";
			std::getline(std::cin, s);
			while (!isInteger(numOfWordsUserWantToPlay, s) || std::stoi(s) > mainPracticeWords->getSize()) {
				ConsoleEffect::foregroundRed("wrong input, try again: ");
				std::getline(std::cin, s);
			}
		}

		// get some (or the whole) words from that list (haven't gotten randomly yet)
		DynamicArray<Vocab*> *practiceWords = new DynamicArray<Vocab*>();
		for (int i = 0; i < numOfWordsUserWantToPlay; i++) {
			practiceWords->add(mainPracticeWords->getAt(i)); // WARNING: just add a pointer, there is only one Vocab object here
		}

		// in case there is only one word
		addDefaultVocabs(practiceWords);

		// play and calculate the result
		int numPlayedWords;
		int numRightAnswer = getStartedQuizzes(practiceWords, numPlayedWords);
		if (numPlayedWords != 0) {
			double result = double(numRightAnswer) / numPlayedWords;
			std::cout << "You was right " << result * 100 << "% of the total questions.\n";
		}
		else {
			std::cout << "You was right 0% of the total questions.\n";
		}

		// cleaning services
		delete practiceWords;
		delete mainPracticeWords;

		ConsoleEffect::foregroundYellow("END QUIZ GAME, HOPE TO SEE YOU AGAIN.\n");
		std::cout << "-------------------------------------------------------------\n";
	}

	void playMissingLetterGame() {
		ConsoleEffect::foregroundYellowB("WELCOME TO MISSING LETTER GAME\n");
		std::cout << "Find one missing letter of words\n";
		std::cout << "Enter "; ConsoleEffect::foregroundYellowB("\'0\'"); std::cout << " to quit the game!\n";

		// read the whole words from the file
		DynamicArray<Vocab*>* mainPracticeWords = preparePractice("PracticeWords.txt");
		int numOfWordsUserWantToPlay;
		if (mainPracticeWords == nullptr) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}
		else {
			std::string s;
			std::cout << "How many words do you want to play?";
			std::cout << " (must be <= " << mainPracticeWords->getSize() << "): ";
			std::getline(std::cin, s);
			while (!isInteger(numOfWordsUserWantToPlay, s) || std::stoi(s) > mainPracticeWords->getSize()) {
				ConsoleEffect::foregroundRed("wrong input, try again: ");
				std::getline(std::cin, s);
			}
		}

		// get some (or the whole) words from that list (haven't gotten randomly yet)
		DynamicArray<Vocab*>* practiceWords = new DynamicArray<Vocab*>();
		for (int i = 0; i < numOfWordsUserWantToPlay; i++) {
			practiceWords->add(mainPracticeWords->getAt(i)); // NOTE: just add a pointer, there is only one Vocab object here
		}


		// play and calculate the result
		ConsoleEffect::foregroundYellowB("GOooo!\n");
		int numPlayedWords;
		int numRightAnswer = getStartedMissingLetters(practiceWords, numPlayedWords);
		if (numPlayedWords != 0) {
			double result = double(numRightAnswer) / numPlayedWords;
			std::cout << "You was right " << result * 100 << "% of the total questions.\n";
		}
		else {
			std::cout << "You was right 0% of the total questions.\n";
		}
		
		// clean
		delete practiceWords;
		delete mainPracticeWords;
		ConsoleEffect::foregroundYellowB("END MISSING LETTER GAME, HOPE TO SEE YOU AGAIN.\n");
		std::cout << "-------------------------------------------------------------\n";
	}

	void playHidingWordsGame() {
		ConsoleEffect::foregroundYellowB("WELCOME TO HIDING LETTER GAME\n");
		// read the whole words from the file
		DynamicArray<Vocab*>* practiceWords = preparePractice("PracticeWords.txt");
		if (practiceWords == nullptr) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}

		// get practice english meaning words
		DynamicArray<std::string>* words = new DynamicArray<std::string>();
		for (int i = 0; i < practiceWords->getSize(); i++) words->add(practiceWords->getAt(i)->getEng());
		
		// create a play list which contains words wants to play
		std::cout << "Select the difficulty!\n";
		std::cout << "1 --> Easy, One Word\n";
		std::cout << "2 --> Normal, 5 Words\n";
		std::cout << "3 --> Hard, 10 Words\n";
		std::cout << "Chose one: ";
		std::string userCommand;
		std::getline(std::cin, userCommand);

		while (!(userCommand[0] >= '1' && userCommand[0] <= '3')) {
			std::cout << "chose from 1 to 3: ";
			std::getline(std::cin, userCommand);
		}

		DynamicArray<std::string>* playWordList = new DynamicArray<std::string>();
		switch (userCommand[0]) {
		case '1':
			playWordList = new DynamicArray<std::string>(1);
			break;
		case '2':
			playWordList = new DynamicArray<std::string>(5);
			break;
		default:
			playWordList = new DynamicArray<std::string>(10);
		}

		if (playWordList->getSize() > words->getSize()) {
			std::cout << "Don\'t have enough too much words in the practice list.\n";
			return;
		}


		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, words->getSize()-1);
		
		bool* haveTaken = new bool[words->getSize()];
		// since all positions haven't been taken
		std::memset(haveTaken, false, words->getSize());
		
		for (int i = 0; i < playWordList->getSize(); i++) {
			int gettingPosition = dis(ge);
			while (haveTaken[gettingPosition]) gettingPosition = dis(ge);

			playWordList->setAt(i, words->getAt(gettingPosition));
			haveTaken[gettingPosition] = true;
		}

		delete[] haveTaken;
		delete words;

		// max rows and columns of the table depends on the max length of the words
		int maxLengthPlayWords = playWordList->getAt(0).length();
		for (int i = 1; i < playWordList->getSize(); i++) {
			if (playWordList->getAt(i).length() > maxLengthPlayWords) {
				maxLengthPlayWords = playWordList->getAt(i).length();
			}
		}

		DynamicArray<BoardGameAnswer>* answers = new DynamicArray<BoardGameAnswer>();
		char** board = createWordLetterBoard(maxLengthPlayWords + 4, playWordList, answers);
		delete playWordList;
		getStartedHidingWordGame(board, maxLengthPlayWords + 4, answers);

		// clean
		clearBoard(board, maxLengthPlayWords + 4);
		delete answers;
		ConsoleEffect::foregroundYellowB("END HIDING LETTER GAME, HOPE TO SEE YOU AGAIN.\n");
		std::cout << "-------------------------------------------------------------\n";
	}

};
