#include "Piece.h"
#include "Board.h"
#include "Moves.h"
#include "Move.h"

#include <iostream>
using namespace std;

int Piece::mailbox[120] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7, -1, 
    -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
    -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
    -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
    -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
    -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
    -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
    -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

int Piece::mailbox2board[64] = {
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98
};

// Piece Square Tables from:
// http://chessprogramming.wikispaces.com/Simplified+evaluation+function

int Piece::whitePawnPositionValue[64] = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

int Piece::blackPawnPositionValue[64] = {   
     0,  0,  0,  0,  0,  0,  0,  0,
     5, 10, 10,-20,-20, 10, 10,  5,
     5, -5,-10,  0,  0,-10, -5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
     0,  0,  0,  0,  0,  0,  0,  0
};


int Piece::whiteKnightPositionValue[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

int Piece::blackKnightPositionValue[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50

};

int Piece::whiteBishopPositionValue[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

int Piece::blackBishopPositionValue[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};


int Piece::whiteRockPositionValue[64] = {
      0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10, 10, 10, 10, 10,  5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      0,  0,  0,  5,  5,  0,  0,  0
};

int Piece::blackRockPositionValue[64] = {
      0,  0,  0,  5,  5,  0,  0,  0,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      5, 10, 10, 10, 10, 10, 10,  5,
      0,  0,  0,  0,  0,  0,  0,  0
};

int Piece::whiteQueenPositionValue[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20

};

int Piece::blackQueenPositionValue[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -10,  5,  5,  5,  5,  5,  0,-10,
      0,  0,  5,  5,  5,  5,  0, -5,
     -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};


int Piece::whiteKingMiddleGamePositionValue[64] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
     20, 20,  0,  0,  0,  0, 20, 20,
     20, 30, 10,  0,  0, 10, 30, 20
};

int Piece::blackKingMiddleGamePositionValue[64] = {
     20, 30, 10,  0,  0, 10, 30, 20,
     20, 20,  0,  0,  0,  0, 20, 20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30

};

int Piece::whiteKingEndGamePositionValue[64] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
};

int Piece::blackKingEndGamePositionValue[64] = {
    -50,-30,-30,-30,-30,-30,-30,-50,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -50,-40,-30,-20,-20,-30,-40,-50
};

Piece::~Piece() {}

bool Piece::CrawlerAttacks(int destination) const {
    for(int i=0; i<nRay; ++i) {
        if( destination == mailbox[ mailbox2board[square] + ray[i] ] ) return true;
    }
    return false;
}

bool Piece::CrawlerCanMoveTo(int destination, Board& board) const {
    // cannot move to a square of same side
    if( board.IsSide(side, destination) ) return false;
    
    return CrawlerAttacks(destination);
}

bool Piece::SliderAttacks(int destination, Board& board) const {
    for(int i=0; i<nRay; ++i) {
        for(int step=1; step<8; ++step) {
            int result = mailbox[ mailbox2board[square] + ray[i]*step ];
            if(result == -1) break;
            if(destination == result) return true;
            if(board.IsOccupied(result)) break;
        }
    }
    return false;
}

bool Piece::SliderCanMoveTo(int destination, Board& board) const {
    // cannot move to a square of same side
    if( board.IsSide(side, destination) ) return false;
    
    return SliderAttacks(destination, board);
}

bool Piece::CrawlerGenerateMoves(Moves& moves, Board& board) const {
    for(int i=0; i<nRay; ++i) {
        int to = mailbox[ mailbox2board[square] + ray[i] ];
        // outside: ignore
        if(to == -1) continue;
        // empty: create move
        else if ( board.IsEmpty(to) ) moves.Insert(Move::CreateNormalMove(square, to, board.GetPiece(square)));
        // own side: ignore
        else if ( board.IsSide(side, to) ) continue;
        // opposite king: position is invalid
        else if ( board.IsKing(to) ) return false;
        // capture: create Move
        else moves.Insert(Move::CreateCaptureMove(square, to, board.GetPiece(square), board.GetPiece(to)));
    }
    return true;
}

bool Piece::SliderGenerateMoves(Moves& moves, Board& board) const {
    for(int i=0; i<nRay; ++i) {
        for(int step=1; step<8; ++step) {
            int to = mailbox[ mailbox2board[square] + ray[i]*step ];
            if(to == -1) {
                break;
            }
            if(board.IsEmpty(to)) {
                moves.Insert(Move::CreateNormalMove(square, to, board.GetPiece(square)));
                continue;
            } else if(board.IsSide(side, to)) {
                break;
            }
            else if(board.IsKing(to)) {
                return false;
            }
            else {
                moves.Insert(Move::CreateCaptureMove(square, to, board.GetPiece(square), board.GetPiece(to)));
                break; 
            }
        }
    }
    return true;
}



King::King(Side s, int square) : Piece(s, square) {
    if(side == WHITE){
    	shortName = 'K';
    	if (square == 60) {
    		castlingMask ^= Board::WHITE_QUEEN_SIDE;
    		castlingMask ^= Board::WHITE_KING_SIDE;
    	}
        positionValue=whiteKingMiddleGamePositionValue; 
    } else {
    	shortName = 'k';
       	if (square == 4) {
        		castlingMask ^= Board::BLACK_QUEEN_SIDE;
        		castlingMask ^= Board::BLACK_KING_SIDE;
        }
        positionValue=blackKingMiddleGamePositionValue; 
    }
    score = KING;

    nRay = 8;
    ray[0] = -11;
    ray[1] = -10;
    ray[2] = -9;
    ray[3] = -1;
    ray[4] = 1;
    ray[5] = 9;
    ray[6] = 10;
    ray[7] = 11;
}


bool King::Attacks(int destination, Board&) const { 
    return CrawlerAttacks(destination); 
}

bool King::CanMoveTo(int destination, Board& board) const { 
	if( destination == square + 2) {
	    if(    board.CastleKingSideAllowed() &&
		       board.IsEmpty(square+1) &&
		       board.IsEmpty(square+2) &&
		       !board.IsInCheck(side) &&
		       !board.IsUnderAttack(square+1, side) &&
		       !board.IsUnderAttack(square+2, side)
	       ) return true;
	}
	if( destination == square - 2) {

	    if(    board.CastleQueenSideAllowed() &&
		       board.IsEmpty(square-1) &&
		       board.IsEmpty(square-2) &&
		       board.IsEmpty(square-3) &&
		       !board.IsInCheck(side) &&
		       !board.IsUnderAttack(square-1, side) &&
		       !board.IsUnderAttack(square-2, side)
	       ) return true;
	}
    return CrawlerCanMoveTo(destination, board); 
}

bool King::GenerateMoves(Moves& moves, Board& board) const {
	if( board.IsCastleKingSidePossible() ) moves.Insert(Move::CreateKingSideCastlingMove(square, board.GetPiece(square), board.GetPiece(square+3)));
	if( board.IsCastleQueenSidePossible() ) moves.Insert(Move::CreateQueenSideCastlingMove(square, board.GetPiece(square), board.GetPiece(square-4)));
    return CrawlerGenerateMoves(moves, board);
}


Queen::Queen(Side s, int square) : Piece(s, square) {
    if(side == WHITE){
    	shortName = 'Q';
        positionValue=whiteQueenPositionValue; 
    } else {
    	shortName = 'q';  
        positionValue=blackQueenPositionValue; 
    }
    score = QUEEN;
    nRay = 8;
    ray[0] = -11;
    ray[1] = -10;
    ray[2] = -9;
    ray[3] = -1;
    ray[4] = 1;
    ray[5] = 9;
    ray[6] = 10;
    ray[7] = 11;
}

bool Queen::Attacks(int destination, Board& board) const { 
    return SliderAttacks(destination, board); 
}

bool Queen::CanMoveTo(int destination, Board& board) const { 
    return SliderCanMoveTo(destination, board); 
}

bool Queen::GenerateMoves(Moves& moves, Board& board) const {
    return SliderGenerateMoves(moves, board);
}


Rock::Rock(Side s, int square) : Piece(s, square) {
    if(side == WHITE){
     	shortName = 'R';
     	if (square == 56) castlingMask ^= Board::WHITE_QUEEN_SIDE;
     	if (square == 63) castlingMask ^= Board::WHITE_KING_SIDE;
        positionValue=whiteRockPositionValue; 
    } else {
     	shortName = 'r';
      	if (square == 0) castlingMask ^= Board::BLACK_QUEEN_SIDE;
        if (square == 7) castlingMask ^= Board::BLACK_KING_SIDE;
        positionValue=blackRockPositionValue; 
    }
    score = ROCK;
    nRay = 4;
    ray[0] = -10;
    ray[1] = -1;
    ray[2] = 1;
    ray[3] = 10;
}

bool Rock::Attacks(int destination, Board& board) const { 
    return SliderAttacks(destination, board); 
}

bool Rock::CanMoveTo(int destination, Board& board) const { 
    return SliderCanMoveTo(destination, board); 
}

bool Rock::GenerateMoves(Moves& moves, Board& board) const {
    return SliderGenerateMoves(moves, board);
}

Bishop::Bishop(Side s, int square) : Piece(s, square) {
    if(side == WHITE){
     	shortName = 'B';   
        positionValue=whiteBishopPositionValue; 
    } else {
     	shortName = 'b';
        positionValue=blackBishopPositionValue; 
    }
    score = BISHOP;
    nRay = 4;
    ray[0] = -11;
    ray[1] = -9;
    ray[2] = 9;
    ray[3] = 11;
}

bool Bishop::Attacks(int destination, Board& board) const { 
    return SliderAttacks(destination, board); 
}

bool Bishop::CanMoveTo(int destination, Board& board) const {
    return SliderCanMoveTo(destination, board); 
}

bool Bishop::GenerateMoves(Moves& moves, Board& board) const {
    return SliderGenerateMoves(moves, board);
}

Knight::Knight(Side s, int square) : Piece(s, square) {
    if(side == WHITE){
     	shortName = 'N';
        positionValue=whiteKnightPositionValue; 
    } else {
     	shortName = 'n'; 
        positionValue=blackKnightPositionValue; 
    }
    score = KNIGHT;
    nRay = 8;
    ray[0] = -21;
    ray[1] = -19;
    ray[2] = -12;
    ray[3] = -8;
    ray[4] = 8;
    ray[5] = 12;
    ray[6] = 19;
    ray[7] = 21;
}

bool Knight::Attacks(int destination, Board& ) const { 
   return CrawlerAttacks(destination); 
}

bool Knight::CanMoveTo(int destination, Board& board) const { 
    return CrawlerCanMoveTo(destination, board); 
}

bool Knight::GenerateMoves(Moves& moves, Board& board) const {
    return CrawlerGenerateMoves(moves, board);
}

Pawn::Pawn(Side s, int square) : Piece(s, square) {
    if(side == WHITE) {
        shortName = 'P';
        positionValue=whitePawnPositionValue; 
        ray[0] = -10; // advance one step, in mailbox coordinates
        ray[1] = -11; // capture right, in mailbox coordinates
        ray[2] = -9;  // capture left, in mailbox coordinates
        // misuse as marker
        ray[4] = 6;   // start row
        ray[5] = 8;   // one row back, in board coordinates
        ray[7] = 0;   // promotion row
    } else {
        shortName = 'p';
        positionValue=blackPawnPositionValue; 
        ray[0] = 10; // advance one step
        ray[1] = 11; // capture right
        ray[2] = 9;  // capture left
        // misuse as marker
        ray[4] = 1;   // start row
        ray[5] = -8;  // one row back, in board coordinates
        ray[7] = 7;   // promotion row
    }
    score = PAWN;

}

bool Pawn::Attacks(int destination, Board &) const {
    if( destination == mailbox[ mailbox2board[square] + ray[1] ] ) return true;
    if( destination == mailbox[ mailbox2board[square] + ray[2] ] ) return true;
    return false;
}

bool Pawn::CanMoveTo(int destination, Board& board) const {
    // cannot move to a square of same side
    if( board.IsSide(side, destination) ) return false;
    
    // capture
    if( destination == mailbox[ mailbox2board[square] + ray[1] ]  && board.IsOccupied(destination) ) return true;
    if( destination == mailbox[ mailbox2board[square] + ray[2] ]  && board.IsOccupied(destination) ) return true;

    // enpassant capture
    if( destination == mailbox[ mailbox2board[square] + ray[1] ]  && board.GetEnPassantSquare() == destination ) return true;
    if( destination == mailbox[ mailbox2board[square] + ray[2] ]  && board.GetEnPassantSquare() == destination ) return true;
    
    //advance one step
    int onestep = mailbox[ mailbox2board[square] + ray[0] ];
    if( board.IsOccupied(onestep) ) return false;
    if( destination == onestep ) return true;
    
    //advance two steps
    if( ray[4] != square/8 || board.IsOccupied(onestep)) return false;
    if( destination == mailbox[ mailbox2board[onestep] + ray[0] ] ) return true;
 
    return false;
}

bool Pawn::GenerateMoves(Moves& moves, Board& board) const {
    //cout << " Pawn::GenerateMoves " << endl;
    //capture 
    int to;
    //cout << " Pawn::GenerateMoves capture" << endl;
    for(int i=1; i<3; ++i) {
        //cout << " Pawn::GenerateMoves capture i:" << i << endl;
        to = mailbox[ mailbox2board[square] + ray[i] ];
        if (to == -1) continue;
        //cout << " Pawn::GenerateMoves capture to:" << to << endl;
        if(board.IsOccupied(to)) {
            if(!board.IsSide(side,to) ) {
                if(board.IsKing(to)) return false;
                else if( ray[7] == square/8 ) {
                    moves.Insert(Move::CreateCapturePromotion2QueenMove(square, to, board.GetPiece(square), board.GetPiece(to)));
                    moves.Insert(Move::CreateCapturePromotion2RockMove(square, to, board.GetPiece(square), board.GetPiece(to)));
                    moves.Insert(Move::CreateCapturePromotion2BishopMove(square, to, board.GetPiece(square), board.GetPiece(to)));
                    moves.Insert(Move::CreateCapturePromotion2KnightMove(square, to, board.GetPiece(square), board.GetPiece(to)));
                }
                else moves.Insert(Move::CreateCaptureMove(square, to, board.GetPiece(square), board.GetPiece(to)));
            }
        } else if (to == board.GetEnPassantSquare()) {
            moves.Insert(Move::CreateEnPassantCaptureMove(square, to, to + ray[5], board.GetPiece(square), board.GetPiece(to + ray[5])));
        }
    }

    //advance one step   
    //cout << " Pawn::GenerateMoves one step" << endl;

    to = mailbox[ mailbox2board[square] + ray[0] ];
    if( board.IsEmpty(to) ) {
        if( ray[7] == square/8 ) {
            moves.Insert(Move::CreateNormalPromotion2QueenMove(square, to, board.GetPiece(square)));
            moves.Insert(Move::CreateNormalPromotion2RockMove(square, to, board.GetPiece(square)));
            moves.Insert(Move::CreateNormalPromotion2BishopMove(square, to, board.GetPiece(square)));
            moves.Insert(Move::CreateNormalPromotion2KnightMove(square, to, board.GetPiece(square)));
        }
    	moves.Insert(Move::CreateNormalMove(square, to, board.GetPiece(square)));

        if( ray[4] == square/8 ) {
            // advance on more step
            int ep = to;
            to = mailbox[ mailbox2board[to] + ray[0] ];
            //std::cout << square/8 << "  " << ray[4] << std::endl;
            if( board.IsEmpty(to) ) moves.Insert(Move::CreateSetEnPassantMove(square, to, ep, board.GetPiece(square)));
        }
    }

    return true;
}

bool operator>(const Piece& left, const Piece& right) {
	std::cout << " in < " << std::endl;
	if(left.GetScore() == right.GetScore()) return left.GetSquare() < right.GetSquare();
	return left.GetScore() < right.GetScore();
}
