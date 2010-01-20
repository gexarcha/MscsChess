#include "SimpleChessEngine.h"

SimpleChessEngine::SimpleChessEngine() : board(0), searcher(0) {}

SimpleChessEngine::~SimpleChessEngine() {
    delete board;
    delete searcher;
}

void SimpleChessEngine::Init(std::string fenString) {
    delete board;
    delete searcher;

    board = new Board();
    board->Init(fenString);

    searcher = new SearchAgent(*board); 
}

void SimpleChessEngine::DoMove(std::string canString) {
    board->DoMove(canString);
}

std::string SimpleChessEngine::NextMove() {
    Move move = searcher->GetBestMove();
    board->DoMove(move);
    return move.ToCanString();
}

bool SimpleChessEngine::IsGameOver() {
    return board->IsGameOver();
}

std::string SimpleChessEngine::Result() {
    return board->Result();
}

