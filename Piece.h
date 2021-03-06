#ifndef PIECE_H
#define PIECE_H

class Board;
class Moves;

#include <iostream>

class Piece {
public:
    enum Side {BLACK, WHITE };
    enum Score {PAWN = 100, KNIGHT = 300, BISHOP = 325, ROCK = 500, QUEEN = 900, KING = 5000};

    virtual ~Piece();
    virtual Piece* Clone() = 0;

    bool IsWhite() const { return side==WHITE; }
    bool IsBlack() const { return side==BLACK; }
    bool IsValid() const { return square != -1; }
    Side GetSide() const { return side; };
    Side GetOppositeSide() const { return (side == WHITE) ? BLACK : WHITE; };

    void Print() const { std::cout << shortName; };

    virtual bool Attacks(int destination, Board& board) const = 0;
    virtual bool CanMoveTo(int destination, Board& board) const = 0;
    void MoveTo(int to) { square = to;};
    virtual bool GenerateMoves(Moves& moves, Board& board) const = 0;
    int GetSquare() const  { return square; }
    int GetScore() const { return (square < 0) ? 0 : score + positionValue[square]; }
    //int UpdateCastlingFlags(int flags) const { return flags&castlingMask; }
    int GetCastlingMask() const { return castlingMask; }


protected:
    Piece(Side s, int square) : side(s), square(square), castlingMask(-1) {};

    bool CrawlerAttacks(int destination) const;
    bool SliderAttacks(int destination, Board& board) const;

    bool CrawlerGenerateMoves(Moves& m, Board& board) const;
    bool SliderGenerateMoves(Moves& m, Board& board) const;

    bool CrawlerCanMoveTo(int destination, Board& board) const;
    bool SliderCanMoveTo(int destination, Board& board) const;

    Side side;
    int square;
    int score;
    int castlingMask;
    int nRay;
    int ray[8];
    char shortName;
    int* positionValue;

    static int mailbox[120];
    static int mailbox2board[64];

    static int whitePawnPositionValue[64];
    static int whiteKnightPositionValue[64];
    static int whiteBishopPositionValue[64];
    static int whiteRockPositionValue[64];
    static int whiteQueenPositionValue[64];
    static int whiteKingMiddleGamePositionValue[64];
    static int whiteKingEndGamePositionValue[64];
    static int blackPawnPositionValue[64];
    static int blackKnightPositionValue[64];
    static int blackBishopPositionValue[64];
    static int blackRockPositionValue[64];
    static int blackQueenPositionValue[64];
    static int blackKingMiddleGamePositionValue[64];
    static int blackKingEndGamePositionValue[64];

private:
};

bool operator>(const Piece& left, const Piece& right);


class King : public Piece {
public:
    King(Side s, int square);	

    Piece* Clone() { return new King(*this); } 

    virtual bool Attacks(int destination, Board&) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;

};

class Queen : public Piece {	
public:
    Queen(Side s, int square);	

    Piece* Clone() { return new Queen(*this); } 
    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};

class Rock : public Piece {
public:
    Rock(Side s, int square);	

    Piece* Clone() { return new Rock(*this); } 
    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
    
};

class Bishop : public Piece {
public:
    Bishop(Side s, int square);	

    Piece* Clone() { return new Bishop(*this); } 
    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};

class Knight : public Piece {
public:
    Knight(Side s, int square);	

    Piece* Clone() { return new Knight(*this); } 
    virtual bool Attacks(int destination, Board& ) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};


class Pawn : public Piece {	
public:
    Pawn(Side s, int square);	

    Piece* Clone() { return new Pawn(*this); } 
    virtual bool Attacks(int destination, Board&) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;

};

#endif
