
#include "WordGame.h"

int main() {
	ConsoleEffect::foregroundWhiteB("");

	WordGame* wg = new WordGame();
	
	std::string userCommand = "h";

	while (userCommand.compare("q")) {
		if (userCommand.compare("1") == 0) {
			wg->lookUp();
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("2") == 0) {
			system("cls");
			int res = wg->addToPracticeList("PracticeWords.txt");
			if (res == 1) std::cout << "Added completely.\n";
			else if (res == 2) std::cout << "existing word.\n";
			else if (res == 3) std::cout << "NO existing word.\n";
			else std::cout << "Failed adding.\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("3") == 0) {
			system("cls");
			int res = wg->removeFromPracticeList("PracticeWords.txt");
			if (res == 1) std::cout << "Remove completely.\n";
			else if (res == 2) std::cout << "NO existing word.\n";
			else if (res == 0) std::cout << "Empty practice list.\n";
			else std::cout << "Failed removing.\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("4") == 0) {
			system("cls");
			wg->playQuizGame();
		}
		else if (userCommand.compare("5") == 0) {
			system("cls");
			wg->playMissingLetterGame();
		}
		else if (userCommand.compare("6") == 0) {
			system("cls");
			wg->playHidingWordsGame();
		}
		else if (userCommand.compare("h") == 0 || userCommand.compare("?") == 0) {
			std::cout << "1 \t-> Look Up a Word\n";
			std::cout << "2 \t-> Add words for Practice\n";
			std::cout << "3 \t-> Remove words from Practice List\n";
			std::cout << "4 \t-> Play Quiz Game\n";
			std::cout << "5 \t-> Play Missing Letter Game\n";
			std::cout << "6 \t-> Play Hiding Words Game\n";
			std::cout << "q \t-> Quit\n";
			std::cout << "f \t-> Flush the Screen\n";
			std::cout << "h or ? \t-> See the instruction\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("f") == 0) {
			system("cls");
		}
		else {
			ConsoleEffect::foregroundRed("invalid command\n");
			ConsoleEffect::foregroundYellowB("\'h\'");
			std::cout << " or "; 
			ConsoleEffect::foregroundYellowB("\'?\'");
			std::cout << " for help\n";
		}
		ConsoleEffect::foregroundGreenB("\\main_run>");
		std::getline(std::cin, userCommand);
	}

	std::cout << " \n\n~-~ -~- ~-~ -~- ~-~ -~-\n";
	std::cout << "    SEE YA (^-^)=b\n";
	std::cout << "~-~ -~- ~-~ -~- ~-~ -~-\n";
	

	
	return 0;
}

