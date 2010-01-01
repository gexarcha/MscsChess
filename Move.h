#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>

class Piece;

class Move {
public:
	enum Type { UNKNOWN, NORMAL, CAPTURE };
    Move(int from = -1 , int to = -1, Type type = UNKNOWN, Piece* capt=0) : from(from), to(to), type(type), captured(capt) {}
    int From() const { return from; }
    int To() const { return to; }
    bool IsCapture() { return type == CAPTURE; }
    void SetCapturedPiece(Piece* piece) { captured = piece; }
    Piece* GetCapturedPiece() const { return captured; }
private:
    int from;
    int to;
    Type type;
    Piece* captured;
    
};

std::ostream& operator<<(std::ostream& o, const Move& m);

#endif

