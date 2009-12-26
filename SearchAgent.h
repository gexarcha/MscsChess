#ifndef SEARCHAGENT_H
#define SEARCHAGENT_H

#include "Board.h"
#include "Evaluator.h"

class SearchAgent {
public:
	SearchAgent(Board b) : board(b), evaluator(board) {}

	Move GetBestMove();

private:
	Board board;
	Evaluator evaluator;

	static const int MIN_SCORE = -10000;
	static const int MAX_SCORE = +10000;

	int AlphaBeta(int depth, int alpha, int beta);
};

#endif /* SEARCHAGENT_H */
