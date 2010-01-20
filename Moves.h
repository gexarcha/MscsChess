#ifndef MOVES_H
#define MOVES_H

#include "Move.h"
#include <algorithm>
#include <vector>
#include <iostream>


class ScoreSort {
  public:
  	bool operator()(const Move& left, const Move right) { return left.GetScore() > right.GetScore(); }
};

class Moves {
public:
    void Insert(Move m) { moves.push_back(m); }
    void Print() { for(int i=0; i<moves.size(); ++i) std::cout << moves[i] << ' '; std::cout << std::endl; }
    Move& operator[](int i) { return moves[i]; }
    int Size() { return moves.size(); }
    void Sort() { std::sort( moves.begin(), moves.end(), ScoreSort() ); }
    bool Includes(const Move& m) {
        std::vector<Move>::iterator found = std::find(moves.begin(), moves.end(), m);
        if( found != moves.end() ) {
            found->SetScore(5000);
            return true;
        }
        return false;
    }
private:
    std::vector<Move> moves;
};

#endif
