#pragma once

#include "Node.h"

class LettersTree {
public:
    Node* root;

    LettersTree() {
        root = new Node();
    }

    // WARNING: r phai khac nullptr, tức là r ĐANG trỏ vào một Node cụ thể
    // singleLetter la chu cai thuong
    Node* addLetter(Node* r, char singleLetter) {
        
        // khong phai luc nao cung them
        // neu khong them thi tro vao nut tiep theo roi tra ve
        // neu co them
        // them vao nut can them roi tra ve dia chi nut vua them
        Node* nextNode = r->letters.getAt(singleLetter - 'a' + 1);
        if (nextNode==nullptr) {
            Node* newNode = new Node();
            r->letters.setAt(singleLetter - 'a' + 1, newNode);

            newNode->key = singleLetter;
            return newNode;
        }
        return nextNode;
        
    }

    void addLetter(std::string word) {
        // tu them node dau tien bang tay
        char fir = word[0];
        word.erase(0, 1);

        Node* nextNode = root->letters.getAt(fir - 'a' + 1);
        
        if (nextNode==nullptr) {
            Node* newNode = new Node();
            root->letters.setAt(fir - 'a' + 1, newNode);
            newNode->key = fir;
        }



        Node* tempRoot = root->letters.getAt(fir - 'a' + 1);

        while (!word.empty()) {
            fir = word[0];
            word.erase(0, 1);
            tempRoot = addLetter(tempRoot, fir);
        }

        tempRoot->makeSense = true;
    }

    void show(Node* r) {
        if (r) {
            if (r->makeSense) std::cout << "ms-";
            std::cout << r->key << "\n";
            
            for (int i = 0; i < MAX_LETTERS; i++) {
                if (r->letters.getAt(i)) {
                    show(r->letters.getAt(i));
                }
            }
        }
    }
    void show() {
        this->show(root);
    }
    // NHƯỢC ĐIỂM:
    // nếu Node hiện tại mà r đang trỏ đến makeSence thì không thể xuất được
    void crushWords(Node* r, std::string& mean) {
        for (int i = 0; i < MAX_LETTERS; i++) {
            if (r->letters.getAt(i)) {
                mean += r->letters.getAt(i)->key;
                if (r->letters.getAt(i)->makeSense) {
                    std::cout << mean << "\n";
                }
                crushWords(r->letters.getAt(i), mean);
                mean.pop_back();
            }
        }
    }

    void crushWords() {
        std::string mean;
        crushWords(root, mean);
    }

    Node* track(Node* r, std::string letrs) {
        if (letrs.size()==0 || r == nullptr) return r;

        char fir = letrs[0];
        letrs.erase(0, 1);

        Node* nextNode = r->letters.getAt(fir - 'a' + 1);
        return track(nextNode, letrs);
    }

    void crushWords(std::string missedWord) {
        std::string mean = missedWord;

        Node* beginPoint = track(root, mean);
        if (beginPoint == nullptr) {
            return;
        }
        // khắc mục nhược điểm của crushWords bên dưới
        if (beginPoint->makeSense) std::cout << mean << "\n";
        crushWords(beginPoint, mean);
    }

    

    void test() {
        for (int i = 0; i < MAX_LETTERS; i++) {
            if (root->letters.getAt(i)) {
                std::cout << root->letters.getAt(i)->key << "\n";
            }
        }
    }

};

