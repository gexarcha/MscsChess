#include "SearchAgent.h"

#include <iostream>

int SearchAgent::AlphaBeta(int depth, int alpha, int beta) {
	checkedNodes++;
    int bestScore = MIN_SCORE;
    int score = MIN_SCORE;

    Moves moves;
    if(!board.GeneratePseudoLegalMoves(moves)) return ILLEGAL;

    int nMoves = moves.Size();
    for(int i = 0; i<nMoves; ++i) {
    	//std::cout << " in AlphaBeta check: " << moves[i] << " depth = " << depth<< std::endl;
        board.ApplyMove(moves[i]);

        if(depth == 0) {
        	if(moves[i].IsCapture()) score = -AlphaBeta(depth, -beta, -alpha);
        	else score = evaluator.Score();
        }
        else score = - AlphaBeta(depth-1, -beta, -alpha);

        board.UndoMove();

        if(score == ILLEGAL) continue;

        if(score > bestScore) bestScore = score;
        if(bestScore > alpha) alpha = bestScore;
        if(alpha >= beta) return alpha;
    }
    if (bestScore == MIN_SCORE) {
    	// no legal move

    	if(board.IsInCheck(board.SideToMove())) return MATE_SCORE - depth;
    	else return 0;

    }
    return bestScore;
}



Move SearchAgent::GetBestMove() {
	clock_t start, end;
	double cpuTime;

	int bestScoreSoFar = MIN_SCORE;
	int alpha = MIN_SCORE;
	int beta = MAX_SCORE;
    Moves moves;
    board.GeneratePseudoLegalMoves(moves);
    Move bestMoveSoFar = moves[0];
    int nMoves = moves.Size();
    for(int i = 0; i < nMoves; ++i) {

    	std::cout << "analyzing "  << moves[i] << std::endl;

    	start = std::clock();
    	board.ApplyMove(moves[i]);

    	int score =  -AlphaBeta(2,-beta, -alpha);
    	int nPos = evaluator.GetCheckedPositions();
    	evaluator.Reset();
    	int nNodes = checkedNodes;
    	checkedNodes = 0;

    	board.UndoMove();

    	if(score > bestScoreSoFar) {
    		bestScoreSoFar = score;
    		bestMoveSoFar = moves[i];
    	}

    	end = clock();
    	cpuTime = std::difftime(end, start)/CLOCKS_PER_SEC;

    	std::cout << "checked positions: " << nPos << " in " << cpuTime << " s, or " <<nPos/cpuTime << " positions/s\n";
    	std::cout << "checked nodes: " << nNodes << " in " << cpuTime << " s, or " <<nNodes/cpuTime << " nodes/s\n";
    	std::cout << "score: " << score << " best score = " << bestScoreSoFar << "\n best move so far: " << bestMoveSoFar << std::endl;
    	if (bestScoreSoFar > alpha) alpha = bestScoreSoFar;

    }
    return bestMoveSoFar;
}
