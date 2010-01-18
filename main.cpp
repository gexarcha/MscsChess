/**
@mainpage MscsChess

This is the example project of the winter 2009/2010 Software Design and Construction class.

\todo fix init() which does not clear the board

\todo remove test from main

\todo refine Evaluator

\todo introduce Opening Book

\todo introduce time control

\todo better interface to xboard

\todo introduce transposition tables

*/



#include "Board.h"
#include "Piece.h"
#include "Move.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

void printBanner();
string prompt();

void test();

void xboard(Board& board);

int main(int argc, char* argv[]) {
    // initialize random number generator
    srand(time(0));

    Board board;
    printBanner();
    string command;
    while(true) {
        command = prompt();

        if(command == "quit") break;

        if(command == "help") {
            printBanner(); 
            continue;
        }

        if(command == "test") {
            test(); 
            continue;
        }

        if(command == "init") {
            board.Init();
            continue;
        }

        if(command == "show") {
            board.Show(); 
            continue;
        }

        if(command == "rand") {
            board.RandomMove();
            continue;
        }

        if(command == "xboard") {
            xboard(board);
            break;
        }

        if(command == "hint") {
            board.SearchMove(1);
            continue;
        }
        if(command == "move") {
             board.ApplyMove(board.SearchMove(1));
             board.Show();
             continue;
        }

        try {
            board.DoMove(command);
        } catch (string& msg) {
            cout << msg << endl;
        }
    } 

}

void printBanner() {
    cout << "MscsChess version 0.0\n\n";
    cout << "   'help' for help\n";
    cout << "   'quit' to quit\n";
    cout << "   'test' to run the unit tests\n";
    cout << "   'init' to initialize the board\n";
    cout << "   'show' to show the board\n";
    cout << "   'rand' do a random computer move\n";
    cout << "   'hint' propose a computer move\n";
    cout << "   'move' do a computer move\n";
    cout << "   'cndm' with c,d = [a,h], n,m = [1,8] for a move\n";
}

string prompt() {
    cout << " > ";
    string input;
    cin >> input;
    return input;
}


#include <vector>

bool testKingAttacks() {
    string name("testKingAttacks");
    cout << name << endl;
    Board b;
    King p(Piece::BLACK, 30);

    vector<bool> result(64,false);
    const int n = 8;
    int attackedSquares[n] = {21, 22, 23,29, 31, 37, 38, 39};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}

bool testKnightAttacks() {
    string name("testKnightAttacks");
    cout << name << endl;
    Board b;
    Knight p(Piece::BLACK, 28);

    vector<bool> result(64,false);
    const int n = 8;
    int attackedSquares[n] = {11, 13, 18, 22, 34, 38, 43, 45};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}

bool testRockAttacks() {
    string name("testRockAttacks");
    cout << name << endl;
    Board b;
    Rock p(Piece::BLACK, 28);

    vector<bool> result(64,false);
    const int n = 14;
    int attackedSquares[n] = {4, 12, 20, 24, 25, 26, 27, 29, 30, 31, 36, 44, 52, 60};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}

bool testBishopAttacks() {
    string name("testBishopAttacks");
    cout << name << endl;

    Board b;
    Bishop p(Piece::BLACK, 28);

    vector<bool> result(64,false);
    const int n = 13;
    int attackedSquares[n] = {1,10,19,37,46,55,7,14,21,35,42,49,56};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}

bool testQueenAttacks() {
    string name("testQueenAttacks");
    cout << name << endl;

    Board b;
    Queen p(Piece::BLACK, 28);

    vector<bool> result(64,false);
    const int n = 27;
    int attackedSquares[n] = {1, 10, 19, 37, 46, 55, 7, 14, 21, 35, 42, 49, 56, 4, 12, 20, 24, 25, 26, 27, 29, 30, 31, 36, 44, 52, 60};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}
bool testBlockedQueenAttacks() {
    string name("testBlockedQueenAttacks");
    cout << name << endl;

    Board b;
    b.Init("8/4p3/8/1b3b2/8/2N5/8/8 w");
    Queen p(Piece::BLACK, 28);

    vector<bool> result(64,false);
    const int n = 21;
    int attackedSquares[n] = {1,10,19,37,46,55,7,14,21,35,42,12,20,25,26,27,29,36,44,52,60};
    for(int i=0; i<n; ++i) result[ attackedSquares[i] ] = true;

    for(int i=0; i<64; ++i) if( !(p.Attacks(i,b) == result[i]) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << p.Attacks(i,b) << " expected result: " << result[i] << endl;
        return false;
    }

    return true;
}


bool testIsEmpty() {
    string name("testIsEmpty");
    cout << name << endl;

    Board b;
    b.Init(); 
    vector<bool> result(64,true);
    for(int i=0; i<16; ++i) result[i] = false;
    for(int i=48; i<64; ++i) result[i] = false;

    for(int i=0; i<64; ++i) if( result[i] != b.IsEmpty(i) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << b.IsEmpty(i) << " expected result: " << result[i] << endl;
        return false;
    }
    return true;
}

bool testIsOccupied() {
    string name("testIsOccupied");
    cout << name << endl;
    Board b;
    b.Init(); 
    vector<bool> result(64,false);
    for(int i=0; i<16; ++i) result[i] = true;
    for(int i=48; i<64; ++i) result[i] = true;

    for(int i=0; i<64; ++i) if( result[i] != b.IsOccupied(i) ) {
        cout << name + " failed:\n";
        cout << "  field " << i << " result: " << b.IsOccupied(i) << " expected result: " << result[i] << endl;
        return false;
    }
    return true;
}



void test() {	
    cout << "Starting unit tests:" << endl;
    int ok = 0;
    int failed = 0;

    if ( testKingAttacks() ) ok++;
    else failed++;

    if ( testKnightAttacks() ) ok++;
    else failed++;

    if ( testRockAttacks() ) ok++;
    else failed++;	

    if ( testBishopAttacks() ) ok++;
    else failed++;	

    if ( testQueenAttacks() ) ok++;
    else failed++;	

    if ( testIsEmpty() ) ok++;
    else failed++;

    if ( testIsOccupied() ) ok++;
    else failed++;

    if ( testBlockedQueenAttacks() ) ok++;
    else failed++;

    cout << " no of tests: " << ok + failed << endl;
    cout << ok << " passed, " << failed << " failed.\n"; 

}

/**
     Simple interface to xboard: for details  see:
     http://www.gnu.org/software/xboard/     
     the communication protocol is described in
     http://www.gnu.org/software/xboard/engine-intf.html
*/
void xboard(Board& board) {
 
    ofstream logfile("logfile.txt");

    cout << "feature myname=\"MscsCess.v0\"" << endl;
    cout << "feature time=0" << endl;
    cout << "feature usermove=1" << endl;
    cout << "feature sigint=0" << endl;
    cout << "feature sigterm=0" << endl;
    cout << "feature done=1" << endl;

    board.Init();

    while(true) {
         // send data to xboard
         cout.flush();

         string command; 
         getline(cin, command);

         // to learn the protocol we log all commands from xboard 
         logfile << command << endl;

         if(command == "quit") break;

         if(command.find("usermove") == 0) {
             // a move from xboard is of the form
             // "usermove can"  whith can a move in coordinate algebraic notation

             // erase "usermove "
             command.erase(0,9);

             // do the move
             board.DoMove(command);
             if(board.IsOver()) {
                 cout << board.Result() << endl;
                 logfile << "after " << command << " " << board.Result() << endl;
                 continue;
             }

             // get the move from the board
             string move = board.XSearchMove();

             // do it on the board
             board.DoMove(move);

             // send it to xboard and the logfile
             cout << "move " << move << endl;
             logfile << "my move " << move << endl;

             if(board.IsOver()) {
                 cout << board.Result() << endl;
                 logfile << board.Result() << endl;
                 continue;
             }

  
         }
    }
}
