
#include "WordGame.h"

int main() {

	/*EngVieDict* d = new EngVieDict();
	d->showHashTable();
	std::cout << "NUM:" << d->getNumOfWord() << "\n";*/
	
	WordGame* wg = new WordGame();

	std::string userCommand = "h";

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
			int res = wg->addToPracticeList("PracticeWords.txt");
			if (res == 1) std::cout << "Added completely.\n";
			else if (res == 2) std::cout << "existing word.\n";
			else if (res == 3) std::cout << "NO existing word.\n";
			else std::cout << "Failed adding.\n";
		}
		else if (userCommand.compare("5") == 0) {
			system("cls");
			int res = wg->removeFromPracticeList("PracticeWords.txt");
			if (res == 1) std::cout << "Remove completely.\n";
			else if (res == 2) std::cout << "NO existing word.\n";
			else if (res == 0) std::cout << "Empty practice list.\n";
			else std::cout << "Failed removing.\n";
		}
		else if (userCommand.compare("h") == 0 || userCommand.compare("?") == 0) {
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
			std::cout << "\'h\' or \'?\' for help\n";
		}

		std::cout << "your command: ";
		std::getline(std::cin, userCommand);
	}

	std::cout << " -------------\n";
	std::cout << "  BYE BYE :(( \n";
	std::cout << " -------------\n";
	

	return 0;
}

