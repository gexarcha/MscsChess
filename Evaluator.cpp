#include "Evaluator.h"

int Evaluator::Score() {
	checkedPositions++;
	if(board.SideToMove()==Piece::WHITE) return -board.GetMaterialScore();
	else                                 return  board.GetMaterialScore();
}
