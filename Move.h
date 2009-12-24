#ifndef MOVE_H
#define MOVE_H

class Piece;

class Move {
public:
    Move(int from, int to, Piece* capt=0) : from(from), to(to), captured(capt) {}
    int From() const { return from; }
    int To() const { return to; }
    Piece* GetCapturedPiece() const { return captured; }
private:
    int from;
    int to;
    Piece* captured;
    
};

#endif

