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
	enum CastlingFlags {WHITE_KING_SIDE = 1, WHITE_QUEEN_SIDE = 2, BLACK_KING_SIDE = 4, BLACK_QUEEN_SIDE = 8};

    Board();
    Board(const Board& b);
    ~Board();

    void Init(const std::string& fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
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
    void MoveTo(Piece* piece, int from, int to);
    void UndoMove();
    bool IsUnderAttack(int square, Piece::Side s);
    bool IsInCheck(Piece::Side s);
    bool IsGameOver() { return result.size() > 0; }
    std::string Result() { return result; }

    Piece* GetPiece(int square) { return board[square]; }

    int GetMaterialScore() const;

    bool GeneratePseudoLegalMoves(Moves& moves);
    bool GenerateCaptureMoves(Moves& moves);

    bool CastleKingSideAllowed() const { return ( sideToMove == Piece::WHITE ? castlingFlag&WHITE_KING_SIDE : castlingFlag&BLACK_KING_SIDE); }
    bool CastleQueenSideAllowed() const { return ( sideToMove == Piece::WHITE ? castlingFlag&WHITE_QUEEN_SIDE : castlingFlag&BLACK_QUEEN_SIDE); }
    bool IsCastleKingSidePossible();
    bool IsCastleQueenSidePossible();
    Piece::Side SideToMove() const { return sideToMove; }

    Piece::Side SideToWait() const {
       if (sideToMove == Piece::WHITE ) return Piece::BLACK;
       else                             return Piece::WHITE;
    }
    void ApplyMove(Move move);
    int GetCastlingFlag() const { return castlingFlag; }
    void SetCastlingFlag(int status) { castlingFlag = status; }
    void SetEnPassantSquare(int epSquare) { enpassantSquare=epSquare;}
    int GetEnPassantSquare() const { return enpassantSquare; }
    int ExchangeEnPassantSquare(int ep) { int temp = enpassantSquare; enpassantSquare = ep; return temp; }


private:

    std::vector<Piece*> board;
    std::vector<Piece*> whitePieces;
    std::vector<Piece*> blackPieces;
    int castlingFlag;
    int enpassantSquare;
    int fullMoveCounter;
    int fiftyMoveRuleCounter;

    std::vector<Move> moveStack;
    Piece::Side sideToMove;
    std::string result;

    void PrintPieces();

    bool TryMove(Move& move);
    void SwitchSide();


};


#endif
