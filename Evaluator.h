#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Board.h"

class Evaluator {
public:
	Evaluator(Board& b) : board(b), checkedPositions(0) {}
	int Score();
	int GetCheckedPositions() const { return checkedPositions; }
	void Reset() { checkedPositions = 0; }
private:
	Board& board;
	int checkedPositions;
};

#endif /* EVALUATOR_H */
