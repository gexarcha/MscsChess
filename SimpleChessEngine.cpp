#include "SimpleChessEngine.h"

#include "Book.h"

SimpleChessEngine::SimpleChessEngine() : board(0), searcher(0), book(0) {}

SimpleChessEngine::~SimpleChessEngine() {
    delete board;
    delete searcher;
    delete book;
}

void SimpleChessEngine::Init(std::string fenString) {
    delete board;
    board = new Board();
    board->Init(fenString);

    delete searcher;
    searcher = new SearchAgent(*board); 

	delete book;
    book = 0;
}

void SimpleChessEngine::InitBook(std::string bookFile) {
	delete book;
	book = new Book(bookFile);
}

void SimpleChessEngine::DoMove(std::string canString) {
    line += canString + ' ';
    board->DoMove(canString);
}

std::string SimpleChessEngine::NextMove() {
    if(book) {
         std::string moveString;
         if( line == "" ) moveString = book->GetNextMove(line);
         else moveString = book->GetNextMove(line.substr(0,line.size()-1) );
         if(moveString =="") {
             delete book;
             book = 0;
         } else {
             board->DoMove(moveString);
             line += moveString + ' ';
             return moveString;
         }
    }
    Move move = searcher->GetBestMove();

    board->DoMove(move);
    line += move.ToCanString() + ' ';
    return move.ToCanString();
}

bool SimpleChessEngine::IsGameOver() {
    return board->IsGameOver();
}

std::string SimpleChessEngine::Result() {
    return board->Result();
}

void SimpleChessEngine::Show() {
	board->Show();
}

