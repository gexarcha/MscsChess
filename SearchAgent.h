#ifndef SEARCHAGENT_H
#define SEARCHAGENT_H

#include "Board.h"
#include "Evaluator.h"
#include "Move.h"
#include <vector>
#include <fstream>

class SearchAgent {
public:
	SearchAgent(Board &b) : board(b), evaluator(board), checkedNodes(0), ply(0) { }

	Move GetBestMove();

private:
	Board &board;
	Evaluator evaluator;
	std::vector<Move> bestMoves;
	int checkedNodes;
	size_t ply;

        bool followPV;

	static const int MAX_PLY = 50;
	static const int MIN_SCORE = -30000;
	static const int MATE_SCORE = -10000;
	static const int MAX_SCORE = +30000;
	static const int ILLEGAL = 30000;

	int AlphaBeta(int depth, int alpha, int beta, std::vector<Move>& principleVariation);
};

#endif /* SEARCHAGENT_H */

