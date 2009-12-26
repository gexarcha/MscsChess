#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Board.h"

class Evaluator {
public:
	Evaluator(Board& b) : board(b) {}
	int Score();
private:
	Board& board;
};

#endif /* EVALUATOR_H */
