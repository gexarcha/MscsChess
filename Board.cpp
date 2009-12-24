#include "Board.h"
#include "Piece.h"
#include <vector>
using std::vector;
#include <string>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;

Board::Board() : board(64,(Piece*)0) {srand(0);}

void Board::Init(std::string fenPosition) {
    int iFen = 0;
    int iWhite = 0;
    int iBlack = 0;
    int iSquare = 0;
    
    // make space for the king in the first field
    piece[0].push_back( (Piece*)0 );
    piece[1].push_back( (Piece*)0 );
    while(iSquare < 64) {
        char c = fenPosition[iFen++];
        Piece *p;
        switch (c) {
            case 'r': 
                p = new Rock(Piece::BLACK, iSquare);
                piece[0].push_back(p);
                board[iSquare++] = p;
                break;

            case 'n': 
                p = new Knight(Piece::BLACK, iSquare);
                piece[0].push_back(p);
                board[iSquare++] = p;
                break;

            case 'b':
                p = new Bishop(Piece::BLACK, iSquare);
                piece[0].push_back(p);
                board[iSquare++] = p;
                break;
            case 'q':
                p = new Queen(Piece::BLACK, iSquare);
                piece[0].push_back(p);
                board[iSquare++] = p;
                break;

            case 'k':
                p = new King(Piece::BLACK, iSquare);
                piece[0][0] = p;
                board[iSquare++] = p;
                break;

            case 'p':
                p = new Pawn(Piece::BLACK, iSquare);
                piece[0].push_back(p);
                board[iSquare++] = p;
                break;

            case 'R':
                p = new Rock(Piece::WHITE, iSquare);
                piece[1].push_back(p);
                board[iSquare++] = p;
                break;

            case 'N':
                p = new Knight(Piece::WHITE, iSquare);
                piece[1].push_back(p);
                board[iSquare++] = p;
                break;

            case 'B': 
                p = new Bishop(Piece::WHITE, iSquare);
                piece[1].push_back(p);
                board[iSquare++] = p;
                break;

            case 'Q':
                p = new Queen(Piece::WHITE, iSquare);
                piece[1].push_back(p);
                board[iSquare++] = p;
                break;

            case 'K':
                p = new King(Piece::WHITE, iSquare);
                piece[1][0] = p;
                board[iSquare++] = p;
                break;

            case 'P':
                p = new Pawn(Piece::WHITE, iSquare);
                piece[1].push_back(p);
                board[iSquare++] = p;
                break;

            case '1': iSquare += 1; break;
            case '2': iSquare += 2; break;
            case '3': iSquare += 3; break;
            case '4': iSquare += 4; break;
            case '5': iSquare += 5; break;
            case '6': iSquare += 6; break;
            case '7': iSquare += 7; break;
            case '8': iSquare += 8; break;
            case '/': break;
            default:
                // should not be reached
                throw "invalid char in fenPosition";
        }
    }
    if(fenPosition[iFen+1] == 'w') sideToMove = Piece::WHITE;
    else if(fenPosition[iFen+1] == 'b') sideToMove = Piece::BLACK;
    else throw "invalid char in fenPosition";

}

void Board::Show() {
    int line = 8;
    for(int i = 0; i<64; ++i)  {
        if( (i)%8 == 0 ) cout << "\n   --------------------------------\n" << line-- << " | ";
        if( IsEmpty(i) ) cout << "   |";
        else {
            cout << ' ';
            board[i]->Print();
            cout << " |";
        }
    }
    cout << "\n   --------------------------------\n";
    cout << "     a   b   c   d   e   f   g   h \n\n";
}

void Board::DoMove(std::string move) {

    // a move must have 4 or 5 characters
    if( move.size() < 4 ) throw std::string("Invalid command: ") + move;

    // decode from and to field
    int from = -1;
    int to = -1 ;
    if( move.size() >= 4 ) {
       std::string fromString(move,0,2);
       std::string toString(move,2,2);

       from = string2square(fromString);
       to = string2square(toString);

       if (from == -1 || to == -1) throw std::string("Invalid command: ") + move;
    }
    // now check whether the move is valid
    if( IsEmpty(from) ) throw std::string("Invalid Move: from square empty");
    if( !IsSide(sideToMove, from) ) throw std::string("Invalid Move: wrong color");
    if( !board[from]->CanMoveTo(to, *this) ) throw std::string("Invalid Move ");

    // now we have a legal move, do it
    if(!DoMove(from, to)) throw std::string("Invalid: you are in check");

    // are we in check?
    if( IsInCheck(sideToMove) ) {
        cout << "check";

       // check whether we are checkmate
       Moves moves;
       GeneratePseudoLegalMoves(moves); 
       int n = moves.Size();
       bool mate = true;
       for(int i=0; i<n; ++i) {
           if( TryMove(moves[i]) ) {
               mate = false;
               break;
           }
       }
       if(mate) cout << "mate";
       cout << endl;
    }
}

bool Board::DoMove(int from, int to) {

    Piece* fromP = board[from];
    Piece* toP = board[to];
    if( toP ) {
        // remove the piece on the to square
        // - remove it from piece list
        vector<Piece*>& pieces = piece[toP->GetSide()];
        vector<Piece*>::iterator found = std::find(pieces.begin(), pieces.end(), toP);
        pieces.erase(found);
    }
    fromP->MoveTo(to);
    board[to] = fromP;
    board[from] = 0;
    
    if ( IsInCheck(fromP->GetSide()) ) {
        // if we are in check: 
        // - undo move
        // - throw exeception
        fromP->MoveTo(from);
        board[from] = fromP;
        board[to] = toP;
        if(toP) piece[toP->GetSide()].push_back(toP);
        return false;
    }
    delete toP;
    SwitchSide();
    return true;

}

bool Board::TryMove(Move& move) {
    int from = move.From();
    int to = move.To();
    Piece* fromP = board[from];
    Piece* toP = board[to];
    if( toP ) {
        // remove the piece on the to square
        // - remove it from piece list
        vector<Piece*>& pieces = piece[toP->GetSide()];
        vector<Piece*>::iterator found = std::find(pieces.begin(), pieces.end(), toP);
        pieces.erase(found);
    }
    fromP->MoveTo(to);
    board[to] = fromP;
    board[from] = 0;
    
    bool check = IsInCheck(fromP->GetSide());
    fromP->MoveTo(from);
    board[from] = fromP;
    board[to] = toP;
    if(toP) piece[toP->GetSide()].push_back(toP);
       
    return !check;
}

int Board::string2square(std::string square) {
   int column = square[0] - 'a';
   int line = square[1] - '1';

   if( -1 < column && column < 8 && -1 < line && line < 8)
      return (7 - line) * 8 + column;
   else return -1;
}

void Board::SwitchSide() {
   if (sideToMove == Piece::WHITE ) sideToMove = Piece::BLACK;
   else                             sideToMove = Piece::WHITE;
}

bool Board::IsInCheck(Piece::Side s) {
    // find square of player king
    // for all pieces of opposite side call 
    // bool Piece::Attacks(int destination, Board&)
    // return true if at least one piece attaks the player king
    // int player = (s == Piece::BLACK) ? 0 : 1;
    // int opposite = (s == Piece::BLACK) ? 1 : 0;
    int player;
    int opposite;
    if (s == Piece::WHITE ) {
       player = 1;
       opposite = 0;
    } else {
       player = 0;
       opposite = 1;
    }
    int kingSquare = piece[player][0]->GetSquare();

    int nPieces = piece[opposite].size();
    for(int i=0; i<nPieces; ++i) {
        if( piece[opposite][i]->Attacks(kingSquare, *this) ) return true;
    }

    return false;
}

bool Board::GeneratePseudoLegalMoves(Moves& moves) {

    vector<Piece*>& pieces = piece[sideToMove];
    int nPieces = pieces.size();
    for(int i=0; i<nPieces; ++i) { 
        if( !(pieces[i]->GenerateMoves(moves, *this)) ) return false;
    }

    return true;
}

void Board::RandomMove() {
    Moves moves;
    GeneratePseudoLegalMoves(moves);
    bool done = false;
    while(!done) {
        int i = rand() % moves.Size();      
        // cout << "RandomMove: i = " << i << " out of " << moves.Size() << endl;
        Move m = moves[i];
        if( DoMove(m.From(), m.To()) ) done=true;
    }

    if( IsInCheck(sideToMove) ) {
        cout << "check";

       // check whether we are checkmate
       Moves moves;
       GeneratePseudoLegalMoves(moves); 
       int n = moves.Size();
       bool mate = true;
       for(int i=0; i<n; ++i) {
           if( TryMove(moves[i]) ) {
               mate = false;
               break;
           }
       }
       if(mate) cout << "mate";
       cout << endl;
    }
    
}
