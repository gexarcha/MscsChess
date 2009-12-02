#ifndef PIECE_H
#define PIECE_H

class Board;

#include <iostream>

class Piece {
public:
    enum Side {WHITE, BLACK };

    virtual ~Piece() {};

    bool IsWhite() const { return side==WHITE; };
    bool IsBlack() const { return side==BLACK; };
    Side GetSide() const { return side; };
    Side GetOppositeSide() const { return (side == WHITE) ? BLACK : WHITE; };

    void Print() const { std::cout << shortName; };

    virtual bool Attacks(int destination, Board& board) const = 0;
    virtual bool CanMoveTo(int destination, Board& board) const  { return false; };
    void MoveTo(int to) { square = to; if(nRay==1) nRay=0;};

protected:
    Piece(Side s, int square) : side(s), square(square) {};

    bool CrawlerAttacks(int destination) const;
    bool SliderAttacks(int destination, Board& board) const;
    
    bool CrawlerCanMoveTo(int destination, Board& board) const;
    bool SliderCanMoveTo(int destination, Board& board) const;

    Side side;
    int square;
    int nRay;
    int ray[8];
    char shortName;

    static int mailbox[120];
    static int mailbox2board[64];

private:
};

class King : public Piece {
public:
    King(Side s, int square);	

    virtual bool Attacks(int destination, Board&) const;

    virtual bool CanMoveTo(int destination, Board& board) const;

};

class Queen : public Piece {	
public:
    Queen(Side s, int square);	
    
    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
};

class Rock : public Piece {
public:
    Rock(Side s, int square);	

    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;
    
};

class Bishop : public Piece {
public:
    Bishop(Side s, int square);	

    virtual bool Attacks(int destination, Board& board) const;
    virtual bool CanMoveTo(int destination, Board& board) const;

};

class Knight : public Piece {
public:
    Knight(Side s, int square);	

    virtual bool Attacks(int destination, Board& ) const;
    virtual bool CanMoveTo(int destination, Board& board) const;

};


class Pawn : public Piece {	
public:
    Pawn(Side s, int square);	

    virtual bool Attacks(int destination, Board&) const;
    virtual bool CanMoveTo(int destination, Board& board) const;

};


#endif
