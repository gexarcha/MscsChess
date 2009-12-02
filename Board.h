#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <vector>
#include <string>

class Board {
public:
    Board();
    void Init(std::string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    bool IsEmpty(int square) const { return board[square] == 0; };
    bool IsOccupied(int square) const { return !IsEmpty(square); };
    bool IsSide(Piece::Side s, int square) const { 
        if(IsEmpty(square)) return false;
        return board[square]->GetSide() == s;
    }
    void Show();
    void Move(std::string move);
private:
    std::vector<Piece*> piece[2];
    std::vector<Piece*> board;
    Piece::Side sideToMove;

    void Move(int from, int to);
    void SwitchSide();

    static int string2square(std::string square);
};

#endif
