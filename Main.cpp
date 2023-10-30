
#include "WordGame.h"

int main() {

	WordQuizGame* wg = new WordQuizGame();

	wg->playWordGame();

	return 0;
}


/*
 PHIÊN BẢN NGƯỜI DÙNG NHẬP Ở CUỐI DANH SÁCH GỢI Ý
	 TRONG TRƯỜNG HỢP LIST TỪ DÀI

	std::string userWord;

	// ENTER: 13
	// BACKSPACE: 8
	// SPACE: 32
	// '\n': 10

	char userChar = 14;

	do {
		userChar = _getch();
		if (userChar == 8) {
			if (userWord.size() == 0) continue;
			userWord.pop_back();
		}
		else {
			userWord += userChar;
		}

		system("cls");
		if (userWord.size()) lt->crushWords(userWord);
		std::cout << "enter a word: " << userWord;
	} while (userChar != 13);





	std::string userWord;

	char userChar = 14;

	do {
		system("cls");
		std::cout << "enter a word: " << userWord << "_\n";

		if (userWord.size()) lt->crushWords(userWord);
		userChar = _getch();
		if (userChar == 8) {
			if (userWord.size() == 0) continue;
			userWord.pop_back();
		}
		else {
			userWord += userChar;
		}

	} while (userChar != 13);

*/
