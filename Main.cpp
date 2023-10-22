#include <fstream>
#include "LettersTree.h"
#include <conio.h>



int main() {
    
    LettersTree* lt = new LettersTree();

    std::ifstream fin("words1000.txt");
    if (fin.fail()) return 1;
    std::string word;
    while (std::getline(fin, word)) lt->addLetter(word);
    fin.close();

    // PHIÊN BẢN NGƯỜI DÙNG NHẬP Ở CUỐI DANH SÁCH GỢI Ý
    // TRONG TRƯỜNG HỢP LIST TỪ DÀI
    //
    //std::string userWord;

    ///*
    //ENTER: 13
    //BACKSPACE: 8
    //SPACE: 32
    //'\n': 10
    //*/
    //char userChar = 14;

    //do {
    //    userChar = _getch();
    //    if (userChar == 8) {
    //        if (userWord.size() == 0) continue;
    //        userWord.pop_back();
    //    }
    //    else {
    //        userWord += userChar;
    //    }
    //    
    //    system("cls");
    //    if (userWord.size()) lt->crushWords(userWord);
    //    std::cout << "enter a word: " << userWord;
    //} while (userChar != 13);


    /*
    ENTER: 13
    BACKSPACE: 8
    SPACE: 32
    '\n': 10
    */
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

    

    return 0;
}
