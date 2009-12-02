#include "Piece.h"
#include "Board.h"

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
    81, 82, 83, 84, 85, 86, 77, 78,
    91, 92, 93, 94, 95, 96, 97, 98
};

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

King::King(Side s, int square) : Piece(s, square) {
    shortName = (side == WHITE) ? 'K' : 'k';
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

Queen::Queen(Side s, int square) : Piece(s, square) {
    shortName = (side == WHITE) ? 'Q' : 'q';
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

Rock::Rock(Side s, int square) : Piece(s, square) {
    shortName = (side == WHITE) ? 'R' : 'r';
    nRay = 4;
    ray[0] = -10;
    ray[1] = -1;
    ray[2] = 1;
    ray[3] = 10;
}

Bishop::Bishop(Side s, int square) : Piece(s, square) {
    shortName = (side == WHITE) ? 'B' : 'b';
    nRay = 4;
    ray[0] = -11;
    ray[1] = -9;
    ray[2] = 9;
    ray[3] = 11;
}

Knight::Knight(Side s, int square) : Piece(s, square) {
    shortName = (side == WHITE) ? 'N' : 'n';
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



Pawn::Pawn(Side s, int square) : Piece(s, square) {
    if(side == WHITE) {
        shortName = 'P';
        ray[0] = -10;
        ray[1] = -11;
        ray[2] = -9;

        // misuse of nRay to signal pawn on starting position
        if(47 < square && square < 56) nRay = 1;
        else                           nRay = 0;
    } else {
        shortName = 'p';
        ray[0] = 10;
        ray[1] = 11;
        ray[2] = 9;
        
        // misuse of nRay to signal pawn on starting position
        if(7 < square && square < 16) nRay = 1;
        else                           nRay = 0;
    }

}

bool Pawn::Attacks(int destination, Board &) const {
    if( destination == mailbox[ mailbox2board[square] + ray[1] ] ) return true;
    if( destination == mailbox[ mailbox2board[square] + ray[2] ] ) return true;
    return false;
}

bool Pawn::CanMoveTo(int destination, Board& board) const {
    cout << "Pawn::CanMoveTo" << endl;
    // cannot move to a square of same side
    if( board.IsSide(side, destination) ) return false;
    
    // capture
    if( destination == mailbox[ mailbox2board[square] + ray[1] ]  && board.IsOccupied(destination) ) return true;
    if( destination == mailbox[ mailbox2board[square] + ray[2] ]  && board.IsOccupied(destination) ) return true;
    
    //advance one step
    int onestep = mailbox[ mailbox2board[square] + ray[0] ];
    if( board.IsOccupied(onestep) ) return false;
    if( destination == onestep ) return true;
    
    //advance two steps
    if( nRay == 0 || board.IsOccupied(onestep)) return false;
    if( destination == mailbox[ mailbox2board[onestep] + ray[0] ] ) return true;
 
    return false;
}
