
#include "WordGame.h"

int main() {

	WordGame* wg = new WordGame();

	std::string userCommand = "help";

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
		else if (userCommand.compare("4") == 0) {
			system("cls");
			wg->addToPracticeList("PracticeWords.txt");
			std::cout << "Add to PracticeWords Completely!!\n";
		}
		else if (userCommand.compare("5") == 0) {
			system("cls");
			wg->removeFromPracticeList("PracticeWords.txt");
			std::cout << "Remove from PracticeWords Completely!!\n";
		}
		else if (userCommand.compare("help") == 0 || userCommand.compare("?") == 0) {
			std::cout << "-------------------------------------------------------------\n";
			std::cout << "1 -> Look Up a Word\n";
			std::cout << "2 -> Play Quiz Game\n";
			std::cout << "3 -> Play Missing Letter Game\n";
			std::cout << "4 -> Add words for Practice\n";
			std::cout << "5 -> Remove words from Practice List\n";
			std::cout << "0 -> Quit\n";
			std::cout << "c -> Flush the Screen\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("c") == 0) {
			
			system("cls");
		}
		else {
			std::cout << "wrong: INVALID command\n";
			std::cout << "\'help\' or \'?\' for help\n";
		}

		std::cout << "your command: ";
		std::getline(std::cin, userCommand);
	}
	std::cout << "BYE BYE :((\n";

	return 0;
}

