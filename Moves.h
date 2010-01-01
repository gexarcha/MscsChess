#ifndef MOVES_H
#define MOVES_H

#include "Move.h"

#include <vector>

#include <iostream>

class Moves {
public:
    void Insert(Move m) { moves.push_back(m); }
    void Print() { for(int i=0; i<moves.size(); ++i) std::cout << moves[i] << ' '; std::cout << std::endl; }
    Move& operator[](int i) { return moves[i]; }
    int Size() { return moves.size(); }
    Move GetRandom();
private:
    std::vector<Move> moves;
};

#endif
