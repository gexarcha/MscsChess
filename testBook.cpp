#include "Book.h"

#include <iostream>
using namespace std;

int main() {
    cout << "Starting test of the opening book" << endl;
    Book book("book.txt");
    cout << book.GetNextMove("") << endl;
    cout << " test with \"e2e4\"" << endl;
    cout << book.GetNextMove("e2e4") << endl;
    cout << " test with \"e2e4 g7g6\"" << endl;
    cout << book.GetNextMove("e2e4 g7g6") << endl;
    cout << endl;
}


