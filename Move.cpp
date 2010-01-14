#include "Move.h"
#include "Board.h"
#include <iostream>

std::ostream& operator<<(std::ostream& o, const Move& m) {
        return ( o << m.Move2Can() );
}

bool operator==(const Move& left, const Move& right) {
    return left.GetType()==right.GetType() &&
           left.From() == right.From() &&
           left.To() == right.To();
}

void Move::Do(Board& board) {

    castlingStatusBackup = board.GetCastlingFlag();
    board.SetCastlingFlag(castlingStatusBackup & piece1->GetCastlingMask());
    epSquare = board.ExchangeEnPassantSquare(epSquare);
    

    board.MoveTo(piece2, from2, to2);
    board.MoveTo(piece1, from1, to1);

    if(IsPromotion()) {
        switch(type) {
            case NORMAL_PROMOTION2QUEEN:
            case CAPTURE_PROMOTION2QUEEN:
                piece1 = new(piece1) Queen(piece1->GetSide(), piece1->GetSquare());
                break;
            case NORMAL_PROMOTION2ROCK:
            case CAPTURE_PROMOTION2ROCK:
                piece1 = new(piece1) Rock(piece1->GetSide(), piece1->GetSquare());
                break;
            case NORMAL_PROMOTION2BISHOP:
            case CAPTURE_PROMOTION2BISHOP:
                piece1 = new(piece1) Bishop(piece1->GetSide(), piece1->GetSquare());
                break;
            case NORMAL_PROMOTION2KNIGHT:
            case CAPTURE_PROMOTION2KNIGHT: 
                piece1 = new(piece1) Knight(piece1->GetSide(), piece1->GetSquare());
                break;
        }
    }
}

void Move::Undo(Board& board) {
    board.SetCastlingFlag(castlingStatusBackup);
    epSquare = board.ExchangeEnPassantSquare(epSquare);

    board.MoveTo(piece1, to1, from1);
    board.MoveTo(piece2, to2, from2);
    if(IsPromotion()) piece1 = new(piece1) Pawn(piece1->GetSide(), piece1->GetSquare());
    
}

void Move::Print() {
    std::cout << "from1 " << from1;
    std::cout<< " to1 " << to1;
    std::cout << " piece1 " << piece1;
    std::cout << "   from2 " << from2;
    std::cout << " to2 " << to2;

    std::cout << " piece2 " << piece2;
    std::cout << " type " << type << std::endl;
}

std::string Move::Move2Can() const {
    std::string result = square2string(from1);
    result += square2string(to1);
    if(IsPromotion()) {
        char c[] = "qqrrbbnn";
        result += c[type-NORMAL_PROMOTION2QUEEN];
    }
    return result;
}
