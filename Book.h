#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <list>


class Book {
public:
    Book(std::string bookFileName);
    std::string GetNextMove(std::string line);
private:
    std::list<std::string> book;
};

#endif

