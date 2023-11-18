#include <iostream>
#include <string>

#define ESC "\x1b"
#define CSI "\x1b["
#define OSC "\x1b]"

class ConsoleEffect {
public:

	// save current cursor to the memory
	static void saveCurrentCursor() {
		std::cout << ESC << "7";
	}

	// move the cursor to the position that 'saveCurrentCursor' saved
	static void loadSavedCursor() {
		std::cout << ESC << "8";
	}

	// move the cursor to straight up n times
	static void moveUp(int times) {
		std::cout << CSI << std::to_string(times) << "A";
	}

	// move the cursor down n times
	static void moveDown(int times) {
		std::cout << CSI << std::to_string(times) << "B";
	}

	// move the cursor to the right n times
	static void moveRight(int times) {
		std::cout << CSI << std::to_string(times) << "C";
	}

	// move the cursor to the left n times
	static void moveLeft(int times) {
		std::cout << CSI << std::to_string(times) << "D";
	}

	// start the cursor blinking
	static void blinkingCursor() {
		std::cout << CSI << "?12h";
	}

	// stop blinking the cursor
	static void noBlinkingCursor() {
		std::cout << CSI << "?12l";
	}

	// show the cursor
	static void showCursor() {
		std::cout << CSI << "?25h";
	}

	// hide the cursor
	static void hideCursor() {
		std::cout << CSI << "?25l";
	}

	// set default cursor shape configured by the user
	static void defaultCursor() {
		std::cout << CSI << "0 q";
	}

	// set blinking block cursor shape
	static void blinkingBlockCursor() {
		std::cout << CSI << "1 q";
	}

	// set steady block cursor shape
	static void steadyBlockCursor() {
		std::cout << CSI << "2 q";
	}

	// set blinking underline cursor shape
	static void blinkingUnderlineCursor() {
		std::cout << CSI << "3 q";
	}

	// set steady underline cursor shape
	static void steadyUnderlineCursor() {
		std::cout << CSI << "4 q";
	}

	// set blinking bar cursor shape
	static void blinkingBarCursor() {
		std::cout << CSI << "5 q";
	}

	// set steady bar cursor shape
	static void steadyBarCursor() {
		std::cout << CSI << "6 q";
	}

	// Insert <numOfSpace> spaces at the current cursor position, shifting all existing text to the right
	// Text exiting the screen to the right is removed
	// No moving the cursor
	static void insertSpace(int numOfSpace) {
		std::cout << CSI << std::to_string(numOfSpace) << "@";
	}

	// Delete <numOfCharacter> characters to the right
	// No moving the cursor
	static void deleteCharacter(int numOfCharacter) {
		std::cout << CSI << std::to_string(numOfCharacter) << "P";
	}

	// Overwrite <numOfCharacter> characters to the right
	// No moving the cursor
	static void eraseCharacter(int numOfCharacter) {
		std::cout << CSI << std::to_string(numOfCharacter) << "X";
	}

	// Returns all attributes to the default state prior to modification
	static void defaultTextFormatting() {
		std::cout << CSI << "0m";
	}

	static void addUnderline() {
		std::cout << CSI << "4m";
	}

	static void removeUnderline() {
		std::cout << CSI << "24m";
	}

	// Swaps foreground and background colors
	static void swapForeBackColor() {
		std::cout << CSI << "7m";
	}

	static void foregroundDefault() {
		std::cout << CSI << "39m";
	}
	static void foregroundExtended() {
		std::cout << CSI << "38";
	}

	// no Bright
	static void foregroundBlack(std::string s) {
		std::cout << CSI << "30m" << s;
		foregroundDefault();
	}

	static void foregroundRed(std::string s) {
		std::cout << CSI << "31m" << s;
		foregroundDefault();
	}

	static void foregroundGreen(std::string s) {
		std::cout << CSI << "32m" << s;
		foregroundDefault();
	}

	static void foregroundYellow(std::string s) {
		std::cout << CSI << "33m" << s;
		foregroundDefault();
	}

	static void foregroundBlue(std::string s) {
		std::cout << CSI << "34m" << s;
		foregroundDefault();
	}

	static void foregroundMagenta(std::string s) {
		std::cout << CSI << "35m" << s;
		foregroundDefault();
	}

	static void foregroundCyan(std::string s) {
		std::cout << CSI << "30m" << s;
		foregroundDefault();
	}

	static void foregroundWhite(std::string s) {
		std::cout << CSI << "37m" << s;
		foregroundDefault();
	}

	// Bright
	static void foregroundBlackB(std::string s) {
		std::cout << CSI << "90m" << s;
		foregroundDefault();
	}

	static void foregroundRedB(std::string s) {
		std::cout << CSI << "91m" << s;
		foregroundDefault();
	}

	static void foregroundGreenB(std::string s) {
		std::cout << CSI << "92m" << s;
		foregroundDefault();
	}

	static void foregroundYellowB(std::string s) {
		std::cout << CSI << "93m" << s;
		foregroundDefault();
	}

	static void foregroundBlueB(std::string s) {
		std::cout << CSI << "94m" << s;
		foregroundDefault();
	}

	static void foregroundMagentaB(std::string s) {
		std::cout << CSI << "95m" << s;
		foregroundDefault();
	}

	static void foregroundCyanB(std::string s) {
		std::cout << CSI << "96m" << s;
		foregroundDefault();
	}

	static void foregroundWhiteB(std::string s) {
		std::cout << CSI << "97m" << s;
		foregroundDefault();
	}

};
