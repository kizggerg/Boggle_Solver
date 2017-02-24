//
// Created by Gregory Gzik on 2017-02-19.
//

#ifndef BOGGLE_SOLVER_WORDS_H
#define BOGGLE_SOLVER_WORDS_H

#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct Node {
    string letter;
    set<Node*> nexts;

    bool operator== (const Node& rhs) {
        return letter == rhs.letter;
    }

    bool hasNexts() {
        return !nexts.empty();
    }

    ~Node() {
        for (Node* next : nexts) {
            delete next;
        }
    }

};

class Words {
    Node letters[26];

private:
    int  goTo(string letter);
    void addLetters();
    void addLetter(string letter, int place);
    void addWord(string word);
    void insertPaths(Node* letter, string word, unsigned long position);
    void parseWords();
    void printAllWords(Node* letter);
    void numberOfWords();



public:
    Words();
    ~Words();
    bool isWord(string word);
    bool isFruitful(string word);
    void printWords();
    void countWords();


};


#endif //BOGGLE_SOLVER_WORDS_H
