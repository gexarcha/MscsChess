#include "SearchAgent.h"

#include <iostream>

int SearchAgent::AlphaBeta(int depth, int alpha, int beta) {
    int bestScore = MIN_SCORE;
    int score = MIN_SCORE;

    Moves moves;
    board.GeneratePseudoLegalMoves(moves);

    for(int i = 0; i<moves.Size(); ++i) {
        board.DoMove(moves[i]);

        if(depth == 0) score = evaluator.Score();
        else score = - AlphaBeta(depth-1, -beta, -alpha);

        board.UndoMove();

        if(score > bestScore) bestScore = score;
        if(bestScore > alpha) alpha = bestScore;
        if(alpha >= beta) return alpha;
    }

    return bestScore;
}

Move SearchAgent::GetBestMove() {
    Moves moves;
    board.GeneratePseudoLegalMoves(moves);
    Move bestMove = moves[0];
    int nMoves = moves.Size();
    for(int i = 1; i<nMoves; ++i) {
    	//std::cout <<

    }
    return bestMove;
}
