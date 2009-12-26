#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Piece.h"
#include "Moves.h"

#include <vector>
#include <string>

/**

Board is the representation of a chess board the squares are ordered from 0 (a8) to 63 (h1):
<pre>
8 |  0  1  2  3  4  5  6  7
7 |  8  9 10 11 12 13 14 15
6 | 16 17 18 19 20 21 22 23
5 | 24 25 26 27 28 29 30 31
4 | 31 33 34 35 36 37 38 39
3 | 40 41 42 43 44 45 46 47
2 | 48 49 50 51 52 53 54 55
1 | 56 57 58 59 60 61 62 63
   ------------------------
    a  b  c  d  e  f  g  h
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

    bool IsKing(int square) const { 
        return dynamic_cast<King*>(board[square]); 
    }

    void Show();
    void DoMove(std::string move);
    bool DoMove(Move move);
    void UndoMove();
    void RandomMove();
    bool IsInCheck(Piece::Side s);

    int GetMaterialScore() const;

    bool GeneratePseudoLegalMoves(Moves& moves);

    Piece::Side SideToMove() const { return sideToMove; }

    Piece::Side SideToWait() const {
       if (sideToMove == Piece::WHITE ) return Piece::BLACK;
       else                             return Piece::WHITE;
    }


private:
    /**
    piece[0] are the black pieces, piece[1] are the white pieces, the kings are in the first element p[i][0].
    */
    std::vector<Piece*> piece[2];
    std::vector<Piece*> board;
    std::vector<Move> moveStack;
    Piece::Side sideToMove;

    void ApplyMove(Move move);

    bool TryMove(Move& move);
    void SwitchSide();


    static int string2square(std::string square);

};

std::string square2string(int square);

#endif
