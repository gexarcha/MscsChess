#include "Utilities.h"

int StringToSquare(std::string square) {
   int column = square[0] - 'a';
   int line = square[1] - '1';

   if( -1 < column && column < 8 && -1 < line && line < 8) return (7 - line) * 8 + column;
   else return -1;
}

std::string SquareToString(int square) {
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
