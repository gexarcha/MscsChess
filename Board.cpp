#include "Board.h"
#include "Piece.h"
#include "Utilities.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::sort;

#include <sstream>
using std::istringstream;

class Compare {
  public:
  	bool operator()(Piece* left, Piece* right) { return left->GetScore() > right->GetScore(); }
  };

Board::Board() : board(64,(Piece*)0) {}

Board::Board(const Board &oldBoard) : board(64,(Piece*)0) {
    for(size_t i=0; i<oldBoard.whitePieces.size(); ++i) {
        if(oldBoard.whitePieces[i]->IsValid()) {
            Piece *p = oldBoard.whitePieces[i]->Clone();
            board[p->GetSquare()] = p;
            whitePieces.push_back(p);
        }
    } 
    for(size_t i=0; i<oldBoard.blackPieces.size(); ++i) {
        if(oldBoard.blackPieces[i]->IsValid()) {
            Piece *p = oldBoard.blackPieces[i]->Clone();
            board[p->GetSquare()] = p;
            blackPieces.push_back(p);
        }
    } 
    castlingFlag = oldBoard.castlingFlag;
    enpassantSquare = oldBoard.enpassantSquare;
    fullMoveCounter = oldBoard.fullMoveCounter;
    fiftyMoveRuleCounter = oldBoard.fiftyMoveRuleCounter;

}

Board::~Board() {
    for(size_t i=0; i<whitePieces.size(); ++i) delete whitePieces[i];
    for(size_t i=0; i<whitePieces.size(); ++i) delete blackPieces[i];
}

void Board::Init(const std::string& fenPosition) {
    istringstream in(fenPosition);

    string piecePlacement;
    in >> piecePlacement;

    int iFen = 0;
    int iSquare = 0;
    
    while(iSquare < 64) {
        char c = fenPosition[iFen++];
        Piece *p;
        switch (c) {
            case 'r': 
                p = new Rock(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'n': 
                p = new Knight(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'b':
                p = new Bishop(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;
            case 'q':
                p = new Queen(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'k':
                p = new King(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'p':
                p = new Pawn(Piece::BLACK, iSquare);
                blackPieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'R':
                p = new Rock(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'N':
                p = new Knight(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'B': 
                p = new Bishop(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'Q':
                p = new Queen(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'K':
                p = new King(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
                board[iSquare++] = p;
                break;

            case 'P':
                p = new Pawn(Piece::WHITE, iSquare);
                whitePieces.push_back(p);
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

    sort( whitePieces.begin(), whitePieces.end(), Compare() );
    sort( blackPieces.begin(), blackPieces.end(), Compare() );

    char activeColor;
    in >> activeColor;

    if(activeColor == 'w') sideToMove = Piece::WHITE;
    else if(activeColor == 'b') sideToMove = Piece::BLACK;
    else throw "invalid char in fenPosition";

    string castlingAvailability;
    in >> castlingAvailability;

    castlingFlag = 0;
    for(size_t i=0; i<castlingAvailability.size(); ++i) {
	switch(castlingAvailability[i]) {
	case 'K':
	    castlingFlag |= WHITE_KING_SIDE;
	    break;
	case 'k':
	    castlingFlag |= BLACK_KING_SIDE;
	    break;
	case 'Q':
	    castlingFlag |= WHITE_QUEEN_SIDE;
	    break;
	case 'q':
	    castlingFlag |= BLACK_QUEEN_SIDE;
	    break;
	case '-':
	    break;
	default:
	    throw "invalid char in fenPosition";
	}
    }

    string enpassantSquareString;
    in >> enpassantSquareString;

    if(enpassantSquareString == "-") enpassantSquare = 0;
    else enpassantSquare = StringToSquare(enpassantSquareString);

    in >> fiftyMoveRuleCounter >> fullMoveCounter;

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

    Move m;
    Moves moves;
    GeneratePseudoLegalMoves(moves); 
    for(size_t i=0; i<moves.Size(); ++i) {
        if(move == moves[i].ToCanString()) {
            m = moves[i];
            break;
        }
    }
    if( m.GetType() == Move::UNKNOWN ) throw std::string("invalid move: ") + move;
    //if( !DoMove( m ) ); //throw std::string("Invalid: you are in check");
    DoMove(m);
    // are we in check?
    if( IsInCheck(sideToMove) ) {
        // cout << "check";

       // check whether we are checkmate
       Moves moves;
       GeneratePseudoLegalMoves(moves); 
       size_t n = moves.Size();
       bool mate = true;
       for(size_t i=0; i<n; ++i) {
           if( TryMove(moves[i]) ) {
               mate = false;
               break;
           }
       }
       if(mate) {
           if(sideToMove == Piece::WHITE) result = "0:1";
           else                           result = "1:0"; 
       }
    }
}


void Board::ApplyMove(Move move) {

    move.Do(*this);
    moveStack.push_back(move);
    SwitchSide();
}

void Board::MoveTo(Piece* piece, int from, int to) {
	if(piece) piece->MoveTo(to);
	if(to > -1) board[to] = piece;
	if(from > -1) board[from] = 0;
}

bool Board::DoMove(Move move) {
    ApplyMove(move);

    if ( IsInCheck(SideToWait()) ) {
        UndoMove();
        return false;
    }
    return true;
}

bool Board::TryMove(Move& move) {

    ApplyMove(move);

    bool check = IsInCheck(SideToWait());

    UndoMove();

    return !check;
}

void Board::UndoMove() {

    // if there is nothing to undo return
    if(moveStack.size() == 0) return;

    // get the last move from the moveStack
    Move move = moveStack.back();
    moveStack.pop_back();

    move.Undo(*this);

    SwitchSide();
}


void Board::SwitchSide() {
   if (sideToMove == Piece::WHITE ) sideToMove = Piece::BLACK;
   else                             sideToMove = Piece::WHITE;
}

bool Board::IsUnderAttack(int square, Piece::Side s) {
	std::vector<Piece*>& playerPieces = (s == Piece::WHITE) ? whitePieces : blackPieces;
	std::vector<Piece*>& oppositePieces = (s == Piece::WHITE) ? blackPieces : whitePieces;

	size_t nPieces = oppositePieces.size();
	for(size_t i=0; i<nPieces; ++i) {
            if( oppositePieces[i]->GetSquare() == -1) continue;
	    if( oppositePieces[i]->Attacks(square, *this) ) return true;
	}
	return false;
}

bool Board::IsInCheck(Piece::Side s) {
    //std::cout << "Board::IsInCheck " << s << std::endl;
    int kingSquare = ((s == Piece::WHITE) ? whitePieces : blackPieces)[0]->GetSquare();
    return IsUnderAttack(kingSquare, s);
}

bool Board::GeneratePseudoLegalMoves(Moves& moves) {

	std::vector<Piece*>& pieces = (sideToMove == Piece::WHITE) ? whitePieces : blackPieces;

    size_t nPieces = pieces.size();
    for(size_t i=0; i<nPieces; ++i) { 
        if(pieces[i]->GetSquare() == -1) continue;
        if( !(pieces[i]->GenerateMoves(moves, *this)) ) return false;
    }

    return true;
}

bool Board::GenerateCaptureMoves(Moves & captures) {
	Moves moves;
    if(!GeneratePseudoLegalMoves(moves)) return false;
    size_t nMoves = moves.Size();
    for(size_t i=0; i<nMoves; ++i) if (moves[i].IsCapture()) captures.Insert(moves[i]);
    return  true;
}

int Board::GetMaterialScore() const {
	int score = 0;
    size_t nPieces = whitePieces.size();
    for(size_t i=0; i<nPieces; ++i) {
        score += whitePieces[i]->GetScore();
    }
    nPieces = blackPieces.size();
    for(size_t i=0; i<nPieces; ++i) {
         score -= blackPieces[i]->GetScore();
     }

    return score;
}


bool Board::IsCastleKingSidePossible()  {
    int square = (sideToMove == Piece::WHITE) ? 60 : 4;
	return  CastleKingSideAllowed() && IsEmpty(square+1) && IsEmpty(square+2) && !IsInCheck(sideToMove)
			&& !IsUnderAttack(square+1, sideToMove) && !IsUnderAttack(square+2, sideToMove);
}

bool Board::IsCastleQueenSidePossible() {
    int square = (sideToMove == Piece::WHITE) ? 60 : 4;
	return  CastleQueenSideAllowed() && IsEmpty(square-1) && IsEmpty(square-2) && IsEmpty(square-3)
			&& !IsInCheck(sideToMove) && !IsUnderAttack(square-1, sideToMove) && !IsUnderAttack(square-2, sideToMove);
}

