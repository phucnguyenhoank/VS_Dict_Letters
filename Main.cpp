
#include "WordGame.h"

int main() {

	WordGame* wg = new WordGame();

	std::string userCommand = "113";

	while (userCommand.compare("0")) {
		if (userCommand.compare("1") == 0) {
			wg->lookUp();
		}
		else if (userCommand.compare("2") == 0) {
			system("cls");
			std::cout << "WELCOME TO QUIZ GAME\n";
			wg->playWordGame();
			std::cout << "END QUIZ GAME, HOPE TO SEE YOU AGAIN.\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("3") == 0) {
			system("cls");
			std::cout << "WELCOME TO MISSING LETTER GAME\n";
			wg->playWordGame2();
			std::cout << "END MISSING LETTER GAME, HOPE TO SEE YOU AGAIN.\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("113") == 0) {
			std::cout << "-------------------------------------------------------------\n";
			std::cout << "1 -> Look Up a Word\n";
			std::cout << "2 -> Play Quiz Game\n";
			std::cout << "3 -> Play Missing Letter Game\n";
			std::cout << "4 -> Add Word for Practice\n";
			std::cout << "0 -> Quit\n";
			std::cout << "clr -> Flush the Screen\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("clr") == 0) {
			system("cls");
		}
		else {
			std::cout << "INVALID COMMAND\n";
		}

		std::cout << "Your command (113 for help): ";
		std::getline(std::cin, userCommand);
	}

	return 0;
}

