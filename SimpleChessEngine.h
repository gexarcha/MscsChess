#ifndef SIMPLECHESSENGINE_H
#define SIMPLECHESSENGINE_H

#include "Player.h"
#include "Board.h"
#include "SearchAgent.h"
#include "Evaluator.h"

class SimpleChessEngine: public Player {
public:
    SimpleChessEngine();
    ~SimpleChessEngine();
    void Init(std::string fenString);
    void DoMove(std::string canString);
    std::string NextMove();
    bool IsGameOver();
    std::string Result();
private:
    Board *board;
    SearchAgent *searcher;
};

#endif

