#include "Book.h"

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

Book::Book(std::string bookFileName) {
    std::ifstream input(bookFileName.c_str());
    std::string  line;
    while(std::getline(input, line)) book.push_back(line);

    //for(int i=0; i<book.size(); ++i) std::cout<< book[i] << std::endl;
}

std::string Book::GetNextMove(std::string line) {
    std::string move;
    if(line == "") {
        int n = book.size();
        int i = rand() % n;
        move = book[i].substr(0,4);
        return move;
    }
    for(int i=0; i<book.size(); ++i) {
        if(book[i].find(line) == 0 && book[i].size() > line.size()) {
           move = book[i];
           move.erase(0,line.size()+1);
           move = move.substr(0,4);
        }
    }
    return move;
}