#ifndef SEARCHAGENT_H
#define SEARCHAGENT_H

#include "Board.h"
#include "Evaluator.h"
#include "Move.h"
#include <vector>

class SearchAgent {
public:
	SearchAgent(Board b) : board(b), evaluator(board), checkedNodes(0) {}

	Move GetBestMove();

private:
	Board board;
	Evaluator evaluator;
	std::vector<Move> bestMoves;
	int checkedNodes;

	static const int MIN_SCORE = -10000;
	static const int MAX_SCORE = +10000;
	static const int ILLEGAL = 30000;

	int AlphaBeta(int depth, int alpha, int beta);
	int QuiescenceSearch(int alpha, int beta);
};

#endif /* SEARCHAGENT_H */
