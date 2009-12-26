#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>

class Piece;

class Move {
public:
    Move(int from, int to, Piece* capt=0) : from(from), to(to), captured(capt) {}
    int From() const { return from; }
    int To() const { return to; }
    void SetCapturedPiece(Piece* piece) { captured = piece; }
    Piece* GetCapturedPiece() const { return captured; }
private:
    int from;
    int to;
    Piece* captured;
    
};

std::ostream& operator<<(std::ostream& o, const Move& m);

#endif

