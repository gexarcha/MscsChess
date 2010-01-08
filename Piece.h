#ifndef PIECE_H
#define PIECE_H

class Board;
class Moves;

#include <iostream>

class Piece {
public:
    enum Side {BLACK, WHITE };
    enum Score {PAWN = 100, KNIGHT = 300, BISHOP = 325, ROCK = 500, QUEEN = 900, KING = 10000};

    virtual ~Piece();

    bool IsWhite() const { return side==WHITE; };
    bool IsBlack() const { return side==BLACK; };
    Side GetSide() const { return side; };
    Side GetOppositeSide() const { return (side == WHITE) ? BLACK : WHITE; };

    void Print() const { std::cout << shortName; };

    virtual bool Attacks(int destination, Board& board) const = 0;
    virtual bool CanMoveTo(int destination, Board& board) const = 0;
    void MoveTo(int to) { square = to;};
    virtual bool GenerateMoves(Moves& moves, Board& board) const = 0;
    int GetSquare() const  { return square; }
    int GetScore() const { return (square < 0) ? 0 : score; }
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

    static int mailbox[120];
    static int mailbox2board[64];

private:
};

bool operator>(const Piece& left, const Piece& right);


class King : public Piece {
public:
    King(Side s, int square);	

    virtual bool Attacks(int destination, Board&) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;

};

class Queen : public Piece {	
public:
    Queen(Side s, int square);	
    
    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};

class Rock : public Piece {
public:
    Rock(Side s, int square);	

    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
    
};

class Bishop : public Piece {
public:
    Bishop(Side s, int square);	

    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};

class Knight : public Piece {
public:
    Knight(Side s, int square);	

    virtual bool Attacks(int destination, Board& ) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;
};


class Pawn : public Piece {	
public:
    Pawn(Side s, int square);	

    virtual bool Attacks(int destination, Board&) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    virtual bool GenerateMoves(Moves& moves, Board& board) const;

};


#endif
