#include "Book.h"

#include <iostream>
using namespace std;

void test();

int main() {
    cout << "Starting test of the opening book" << endl;
    for(int i=0; i<10; ++i) test();
}

void test() {
    Book book("book.txt");
    string move = book.GetNextMove("");
    string line = move;
    do {
        cout << line << endl;
        move = book.GetNextMove(line);
        line += ' ' + move;
    } while(move != "");
    

}


