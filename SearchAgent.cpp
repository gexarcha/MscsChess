#include "SearchAgent.h"

#include <iostream>

int SearchAgent::AlphaBeta(int depth, int alpha, int beta) {
    int bestScore = MIN_SCORE;
    int score = MIN_SCORE;

    Moves moves;
    if(!board.GeneratePseudoLegalMoves(moves)) return ILLEGAL;

    int nMoves = moves.Size();
    for(int i = 0; i<nMoves; ++i) {
    	//std::cout << " in AlphaBeta check: " << moves[i] << " depth = " << depth<< std::endl;
        board.ApplyMove(moves[i]);

        if(depth == 0) score = evaluator.Score();
        else score = - AlphaBeta(depth-1, -beta, -alpha);
        if(score == ILLEGAL) continue;

        board.UndoMove();

        if(score > bestScore) bestScore = score;
        if(bestScore > alpha) alpha = bestScore;
        if(alpha >= beta) return alpha;
    }
    if (bestScore == MIN_SCORE) {
    	// no leagal move
    	std::cout << "best score = min\n";
    	if(board.IsInCheck(board.SideToMove())) return bestScore + depth;
    	else return 0;

    }
    return bestScore;
}

Move SearchAgent::GetBestMove() {
	int bestScoreSoFar = MIN_SCORE;
	int alpha = MIN_SCORE;
	int beta = MAX_SCORE;
    Moves moves;
    board.GeneratePseudoLegalMoves(moves);
    Move bestMoveSoFar = moves[0];
    int nMoves = moves.Size();
    for(int i = 0; i < nMoves; ++i) {

    	std::cout << "analyzing "  << moves[i] << std::endl;
    	board.ApplyMove(moves[i]);

    	int score =  -AlphaBeta(3,-beta, -alpha);
    	int nPos = evaluator.GetCheckedPositions();
    	evaluator.Reset();

    	board.UndoMove();

    	if(score > bestScoreSoFar) {
    		bestScoreSoFar = score;
    		bestMoveSoFar = moves[i];
    	}
    	std::cout << "checked positions: " << nPos << ", score = " << score << " best score = " << bestScoreSoFar << " best move so far: " << bestMoveSoFar << std::endl;
    	if (bestScoreSoFar > alpha) alpha = bestScoreSoFar;

    }
    return bestMoveSoFar;
}
