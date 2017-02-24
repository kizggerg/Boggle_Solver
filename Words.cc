//
// Created by Gregory Gzik on 2017-02-19.
// TODO: Implement "qu" case

#include "Words.h"

Words::Words() {
    addLetters();
    parseWords();
}

Words::~Words() {
    for (Node letter : letters) {
        letter.~Node();
    }
}

void Words::addLetters() {
    addLetter("a", 0);
    addLetter("b", 1);
    addLetter("c", 2);
    addLetter("d", 3);
    addLetter("e", 4);
    addLetter("f", 5);
    addLetter("g", 6);
    addLetter("h", 7);
    addLetter("i", 8);
    addLetter("j", 9);
    addLetter("k", 10);
    addLetter("l", 11);
    addLetter("m", 12);
    addLetter("n", 13);
    addLetter("o", 14);
    addLetter("p", 15);
    addLetter("q", 16);
    addLetter("r", 17);
    addLetter("s", 18);
    addLetter("t", 19);
    addLetter("u", 20);
    addLetter("v", 21);
    addLetter("w", 22);
    addLetter("x", 23);
    addLetter("y", 24);
    addLetter("z", 25);
}

void Words::addLetter(string letter, int place) {
    Node* newLetter = new Node;
    newLetter->letter = letter;
    letters[place] = *newLetter;
}

int Words::goTo(string letter) {
    if (letter == "a") return 0;
    else if (letter == "b") return 1;
    else if (letter == "c") return 2;
    else if (letter == "d") return 3;
    else if (letter == "e") return 4;
    else if (letter == "f") return 5;
    else if (letter == "g") return 6;
    else if (letter == "h") return 7;
    else if (letter == "i") return 8;
    else if (letter == "j") return 9;
    else if (letter == "k") return 10;
    else if (letter == "l") return 11;
    else if (letter == "m") return 12;
    else if (letter == "n") return 13;
    else if (letter == "o") return 14;
    else if (letter == "p") return 15;
    else if (letter == "q") return 16;
    else if (letter == "r") return 17;
    else if (letter == "s") return 18;
    else if (letter == "t") return 19;
    else if (letter == "u") return 20;
    else if (letter == "v") return 22;
    else if (letter == "w") return 22;
    else if (letter == "x") return 23;
    else if (letter == "y") return 24;
    else if (letter == "z") return 25;
    else return -1;
}

void Words::addWord(string word) {
    Node* letter = &letters[goTo(word.substr(0, 1))];
    insertPaths(letter, word, 2);
}

void Words::insertPaths(Node* letter, string word, unsigned long position) {
    if (position > word.length()) return;

    Node* next = new Node;
    next->letter = word.substr(0, position);
    letter->nexts.insert(next);
    insertPaths(next, word, ++position);
}

void Words::parseWords() {
    // Syntax Retreived from http://www.cplusplus.com/forum/beginner/8388/
    string input;
    ifstream infile;
    infile.open ("../words.txt");
    while(infile.peek() != EOF) // To get you all the lines.
    {
        getline(infile, input); // Saves the line in STRING.
        addWord(input);
        input = "";
    }

    infile.close();
}

void Words::printWords() {
    for (int i = 0; i < 26; i++) {
        printAllWords(&letters[i]);
    }
}

void Words::printAllWords(Node* letter) {
    if (letter->nexts.empty()) {
        cout << letter->letter << endl;
        return;
    }

    for (Node* next : letter->nexts) {
        printAllWords(next);
    }
}

void Words::countWords() {
    int counter = 0;

    for (int i = 0; i < 26; i++) {
        for (Node* next : letters[i].nexts) {
            counter++;
        }
    }

    cout << "There are " + to_string(counter) + " words recorded." << endl;
    numberOfWords();
}

void Words::numberOfWords() {
    int counter = 0;

    string ignore;
    ifstream infile;
    infile.open ("../words.txt");
    while(infile.peek() != EOF) // To get you all the lines.
    {
        getline(infile, ignore);
        counter++;
    }

    infile.close();
    cout << "There should be " + to_string(counter) + " words recorded." << endl;
}

bool isWordRecursive(string word, Node* part) {
    if (part->letter == word) {
        return !part->hasNexts();
    }
    else {
        for (Node* next : part->nexts) {
            if (isWordRecursive(word, next)) return true;
        }
    }

    return false;
}

bool Words::isWord(string word) {
    if (word.length() < 3) return false;
    Node* part = &letters[goTo(word.substr(0, 1))];
    if (!part->hasNexts()) return false;
    else return isWordRecursive(word, part);
}

bool isFruitfulRecursive(string word, Node* part) {
    if (part->letter == word) {
        return part->hasNexts();
    } else {
        if (part->hasNexts()) {
            for (Node *next : part->nexts) {
                if (isFruitfulRecursive(word, next)) return true;
            }
        }

        return false;
    }
}


bool Words::isFruitful(string word) {
    Node* part = &letters[goTo(word.substr(0, 1))];
    if (!part->hasNexts()) return false;
    else return isFruitfulRecursive(word, part);
}