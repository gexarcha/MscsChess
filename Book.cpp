#include "Book.h"

#include <fstream>
#include <string>
#include <list>
#include <algorithm>

#include <cmath>

#include <iostream>

using namespace std;

Book::Book(string bookFileName) {
    
    ifstream input(bookFileName.c_str());
    string  line;
    while(getline(input, line)) book.push_back(line);
    srand(time(0));
}

struct NotLine {
    NotLine(string line) : line(line) {}
    bool operator()(string bookLine) { return bookLine.find(line) != 0; }
    string line;
};


std::string Book::GetNextMove(string line) {

    // first remove all not matching lines from the book
    list<string>::iterator notInLine = remove_if(book.begin(), book.end(), NotLine(line) );
    book.erase(notInLine, book.end());

    // if no line is in the book, return
    if(book.size() == 0) return "";

    // find a random line
    int i = rand() % book.size();
    list<string>::iterator it = book.begin();
    while(i--) ++it;
    string move = *it;

    // extract the move and return it
    i = line.size() ? line.size() + 1 : 0;
    move = move.substr(i,4);
    return move;
}

