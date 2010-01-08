#include "Board.h"
#include "Piece.h"

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
	for(int i=0; i<castlingAvailability.size(); ++i) {
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
    else enpassantSquare = string2square(enpassantSquareString);

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

    Move m;
    Piece* fromPiece = board[from];
    Piece* toPiece = board[to];

    if(move == "e1g1" || move == "e8g8") {
    	if(IsCastleKingSidePossible()) m = Move::CreateKingSideCastlingMove(from, fromPiece, GetPiece(from+3));
    	else throw std::string("king side castling not allowed");
    } else if(move == "e1c1" || move == "e8c8") {
    	if(IsCastleQueenSidePossible()) m = Move::CreateQueenSideCastlingMove(from, fromPiece, GetPiece(from-4));
    	else throw std::string("queen side castling not allowed");
    } else if(toPiece) m = Move::CreateCaptureMove(from, to, fromPiece, toPiece);
    else m= Move::CreateNormalMove(from, to, fromPiece);
    // now we have a legal move, do it
    if( !DoMove( m ) ) throw std::string("Invalid: you are in check");

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

    //std::cerr << " try move " << move << " ";
	ApplyMove(move);
    
    bool check = IsInCheck(SideToWait());

    UndoMove();

    return !check;
}

void Board::UndoMove() {

    if(moveStack.size() == 0) return;

    Move move = moveStack.back();
    moveStack.pop_back();

    move.Undo(*this);

	SwitchSide();
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

bool Board::IsUnderAttack(int square, Piece::Side s) {
	std::vector<Piece*>& playerPieces = (s == Piece::WHITE) ? whitePieces : blackPieces;
	std::vector<Piece*>& oppositePieces = (s == Piece::WHITE) ? blackPieces : whitePieces;

	int nPieces = oppositePieces.size();
	for(int i=0; i<nPieces; ++i) {
	    if( oppositePieces[i]->Attacks(square, *this) ) return true;
	}
	return false;
}

bool Board::IsInCheck(Piece::Side s) {
    int kingSquare = ((s == Piece::WHITE) ? whitePieces : blackPieces)[0]->GetSquare();
    return IsUnderAttack(kingSquare, s);
}

bool Board::GeneratePseudoLegalMoves(Moves& moves) {

	std::vector<Piece*>& pieces = (sideToMove == Piece::WHITE) ? whitePieces : blackPieces;

    int nPieces = pieces.size();
    for(int i=0; i<nPieces; ++i) { 
        if(pieces[i]->GetSquare() == -1) continue;
        if( !(pieces[i]->GenerateMoves(moves, *this)) ) return false;
    }

    return true;
}

bool Board::GenerateCaptureMoves(Moves & captures) {
	Moves moves;
    if(!GeneratePseudoLegalMoves(moves)) return false;
    int nMoves = moves.Size();
    for(int i=0; i<nMoves; ++i) if (moves[i].IsCapture()) captures.Insert(moves[i]);
    return  true;
}

void Board::RandomMove() {
    Moves moves;
    GeneratePseudoLegalMoves(moves);
    bool done = false;
    while(!done) {
        int i = rand() % moves.Size();      
        // cout << "RandomMove: i = " << i << " out of " << moves.Size() << endl;
        Move m = moves[i];
        if( DoMove(m) ) {
        	done=true;
        	cout << m;
        }
    }

    if( IsInCheck(sideToMove) ) {
        cout << " check";

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
    }
    cout << endl;
}

int Board::GetMaterialScore() const {
	int score = 0;
    int nPieces = whitePieces.size();
    for(int i=1; i<nPieces; ++i) {
        score += whitePieces[i]->GetScore();
    }
    nPieces = blackPieces.size();
    for(int i=1; i<nPieces; ++i) {
         score -= blackPieces[i]->GetScore();
     }

    return score;
}

std::string square2string(int square) {
   int line = square/8;
   std::string result;
   switch(square%8) {
       case 0: result += 'a'; break;
       case 1: result += 'b'; break;
       case 2: result += 'c'; break;
       case 3: result += 'd'; break;
       case 4: result += 'e'; break;
       case 5: result += 'f'; break;
       case 6: result += 'g'; break;
       case 7: result += 'h'; break;
   }
   switch(square/8) {
        case 0: result += '8'; break;
        case 1: result += '7'; break;
        case 2: result += '6'; break;
        case 3: result += '5'; break;
        case 4: result += '4'; break;
        case 5: result += '3'; break;
        case 6: result += '2'; break;
        case 7: result += '1'; break;
    }
   return result;
}

#include "SearchAgent.h"

Move Board::SearchMove() {
	SearchAgent agent(*this);
	Move move = agent.GetBestMove();
	return move;
}

void Board::PrintPieces() {
	for(int i=0; i<whitePieces.size(); ++i) whitePieces[i]->Print();
	std::cout << std::endl;
	for(int i=0; i<blackPieces.size(); ++i) blackPieces[i]->Print();
	std::cout << std::endl;
}

std::string Board::XRandomMove() {
    Moves moves;
    GeneratePseudoLegalMoves(moves);
    bool done = false;
    Move m;
    while(!done) {
        int i = rand() % moves.Size();      
        // cout << "RandomMove: i = " << i << " out of " << moves.Size() << endl;
        m = moves[i];
        if( DoMove(m) ) done=true;
    }

    std::string result;
    char lines[] = "87654321";
    char columns[] = "abcdefgh"; 

    result += columns[m.From()%8];
    result += lines[m.From()/8];
    result += columns[m.To()%8];
    result += lines[m.To()/8];
    
    return result;
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

