/**
@mainpage MscsChess

This is the example project of the winter 2009/2010 Software Design and Construction class.

\todo refine Evaluator

\todo introduce time control

\todo better interface to xboard

\todo introduce transposition tables

*/

#include "Player.h"
#include "SimpleChessEngine.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

/**
     Simple interface to xboard: for details  see:
     http://www.gnu.org/software/xboard/     
     the communication protocol is described in
     http://www.gnu.org/software/xboard/engine-intf.html
*/

int main() {
 
    Player *player = new SimpleChessEngine();

    ofstream logfile("logfile.txt");

    cout << "feature myname=\"MscsChess.v1\"" << endl;
    cout << "feature time=0" << endl;
    cout << "feature usermove=1" << endl;
    cout << "feature setboard=1" << endl;
    cout << "feature sigint=0" << endl;
    cout << "feature sigterm=0" << endl;
    cout << "feature done=1" << endl;

    while(true) {
         // send data to xboard
         cout.flush();

         string command; 
         getline(cin, command);

         // to learn the protocol we log all commands from xboard 
         logfile << command << endl;

         if(command == "quit") break;

         if(command == "new") {
             player->Init("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			 player->InitBook("book.txt");
             continue;
         }
        
         if(command == "setboard") {
              command.erase(0,9);
              player->Init(command);
              continue;
         }

         if(command.find("usermove") == 0) {

             // a move from xboard is of the form
             // "usermove can"  whith "can" = a move in coordinate algebraic notation

             // erase "usermove "
             command.erase(0,9);

             // do the move
             player->DoMove(command);

             if(player->IsGameOver()) {
                 cout << player->Result() << endl;
                 logfile << player->Result() << endl;
                 continue;
             }

             // now we have to do a move, that is also done after th go command, so just reuse it
             
             command = "go";

         }

         if(command == "go") {
             // get the move from the board
             string move = player->NextMove();

             // send it to xboard and the logfile
             cout << "move " << move << endl;
             logfile << "my move " << move << endl;

             if(player->IsGameOver()) {
                 cout << player->Result() << endl;
                 logfile << player->Result() << endl;
                 continue;
             }
         }

          
		 // show an ascii representation of the current board
		 // used without xboard
		 if(command == "show") player->Show();
    }

    delete player;
}
