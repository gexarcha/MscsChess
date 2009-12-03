#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <vector>
#include <string>

/**

Board is the representation of a chess board the squares are ordered from 0 (a8) to 63 (h1):
<pre>
 0  1  2  3  4  5  6  7
 8  9 10 11 12 13 14 15
 ....
    
</pre>

*/

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
    bool IsInCheck(Piece::Side s);
private:
    /**
    piece[0] are the black pieces, piece[1] are the white pieces, the kings are in the first element p[i][0].
    */
    std::vector<Piece*> piece[2];
    std::vector<Piece*> board;
    Piece::Side sideToMove;

    void Move(int from, int to);
    void SwitchSide();

    static int string2square(std::string square);
};

#endif
