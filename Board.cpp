#include "Board.h"
#include "Piece.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

Board::Board() : board(64,0) {}

void Board::Init(std::string fenPosition) {
	int iFen = 0;
	int iWhite = 0;
	int iBlack = 0;
	int iSquare = 0;
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
				piece[0].push_back(p);
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
				piece[1].push_back(p);
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
