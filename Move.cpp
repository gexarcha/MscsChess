#include "Move.h"
#include "Board.h"
#include <iostream>

std::ostream& operator<<(std::ostream& o, const Move& m) {
	return (o << square2string(m.From()) << square2string(m.To()) /*<<"=" << m.GetScore() << " "*/ );
}

void Move::Do(Board& board) {

    castlingStatusBackup = board.GetCastlingFlag();
    board.SetCastlingFlag(castlingStatusBackup & piece1->GetCastlingMask());

    board.MoveTo(piece2, from2, to2);
    board.MoveTo(piece1, from1, to1);

}

void Move::Undo(Board& board) {
	board.SetCastlingFlag(castlingStatusBackup);

    board.MoveTo(piece1, to1, from1);
    board.MoveTo(piece2, to2, from2);
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
