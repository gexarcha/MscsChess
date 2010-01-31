#ifndef SIMPLECHESSENGINE_H
#define SIMPLECHESSENGINE_H

#include "Player.h"
#include "Board.h"
#include "SearchAgent.h"
#include "Evaluator.h"

class Book;

class SimpleChessEngine: public Player {
public:
    SimpleChessEngine();
    ~SimpleChessEngine();
    void Init(std::string fenString);
    void InitBook(std::string bookFile);
    void DoMove(std::string canString);
    std::string NextMove();
    bool IsGameOver();
    std::string Result();
	void Show();
private:
    Board *board;
    SearchAgent *searcher;
    Book *book;
    std::string line;
};

#endif

