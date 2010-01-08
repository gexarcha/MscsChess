#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>

class Piece;
class Board;

class Move {
public:
	enum Type { UNKNOWN, NORMAL, CAPTURE, ENPASSANT, CASTLING, NORMAL_PROMOTION2QUEEN=16, CAPTURE_PROMOTION2QUEEN };

    Move() : from1(-1), to1(-1), from2(-1), to2(-1), piece1(0), piece2(0), type(UNKNOWN) {}


    inline static Move CreateNormalMove(int from, int to, Piece* piece);
    inline static Move CreateCaptureMove(int from, int to, Piece* piece, Piece* captured);
    inline static Move CreateEnPassantMove(int from, int to, int ep, Piece* pawn, Piece* captured);
    inline static Move CreateKingSideCastlingMove(int from, Piece* king, Piece* rock);
    inline static Move CreateQueenSideCastlingMove(int from, Piece* king, Piece* rock);
    inline static Move CreateNormalPromotion2QueenMove(int from, int to, Piece* pawn);
    inline static Move CreateCapturePromotion2QueenMove(int from, int to, Piece* pawn, Piece* captured);

    bool IsPromotion() const { return type > 15; }

    void Do(Board& board);
    void Undo(Board& board);

    int From() const { return from1; }
    int To() const { return to1; }
    //int From2() const { return from2; }
    //int To2() const { return to; }
    //Piece* Piece1() const { return piece1; }
    //Piece* Piece2() const { return piece2; }
    bool IsCapture() { return type == CAPTURE; }
    //void SetCapturedPiece(Piece* piece) { captured = piece; }
    //Piece* GetCapturedPiece() const { return captured; }
    void Print();
private:
    Move(Type t, int from1, int to1, Piece* p1 = 0, Piece* p2 = 0, int from2 = -1, int to2 = -1)
    : from1(from1), to1(to1), from2(from2), to2(to2), piece1(p1), piece2(p2), type(t) {}
    int from1;
    int to1;
    int from2;
    int to2;
    Piece* piece1;
    Piece* piece2;
    Type type;
    int castlingStatusBackup;
};

Move Move::CreateNormalMove(int from, int to, Piece* piece) {
    return Move(NORMAL, from, to, piece, (Piece*) 0, -1, -1);
}

Move Move::CreateCaptureMove(int from, int to, Piece* piece, Piece* captured) {
    return Move(CAPTURE, from, to, piece, captured, to, -1);
}

Move Move::CreateEnPassantMove(int from, int to, int ep, Piece* pawn, Piece* captured) {
    return Move(ENPASSANT, from, to, pawn, captured, ep, -1);
}

Move Move::CreateKingSideCastlingMove(int fromKing, Piece* king, Piece* rock) {
	std::cout << "CreateKingSindCastlingMove\n";
	return Move(CASTLING, fromKing, fromKing+2, king, rock, fromKing+3, fromKing+1);
}

Move Move::CreateQueenSideCastlingMove(int fromKing, Piece* king, Piece* rock) {
	return Move(CASTLING, fromKing, fromKing-2, king, rock, fromKing-4, fromKing-1);
}

Move Move::CreateNormalPromotion2QueenMove(int from, int to, Piece* piece) {
    return Move(NORMAL_PROMOTION2QUEEN, from, to, piece, (Piece*) 0, from, -1);
}

Move Move::CreateCapturePromotion2QueenMove(int from, int to, Piece* piece, Piece* captured) {
    return Move(CAPTURE_PROMOTION2QUEEN, from, to, piece, captured, from, -1);
}

std::ostream& operator<<(std::ostream& o, const Move& m);

#endif

