#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
public:
    Book(std::string bookFileName);
    std::string GetNextMove(std::string line);
private:
    std::vector<std::string> book;
};

#endif

