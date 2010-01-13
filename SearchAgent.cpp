#include "SearchAgent.h"

#include <iostream>
#include <vector>
using std::vector;

int SearchAgent::AlphaBeta(int depth, int alpha, int beta, vector<Move> & principleVariation) {
    checkedNodes++;

    int bestScore = MIN_SCORE;
    int score = MIN_SCORE;

  

    Moves moves;
    if(!board.GeneratePseudoLegalMoves(moves)) return ILLEGAL;
    moves.Sort();

    int nMoves = moves.Size();
    for(int i = 0; i<nMoves; ++i) {
        board.ApplyMove(moves[i]);

        vector<Move> line;
        if(depth == 0) {
        	if(moves[i].IsCapture()) score = -AlphaBeta(depth, -beta, -alpha, line);
        	else score = evaluator.Score();
        }
        else score = - AlphaBeta(depth-1, -beta, -alpha, line);

        board.UndoMove(); 

        if(score == ILLEGAL) continue;

        if(score > bestScore) bestScore = score;

        if(bestScore > alpha) {
            alpha = bestScore;

            if(alpha >= beta) return alpha;

            // we have a new best move: update the principle variation
            // - remove old moves
            principleVariation.clear();
            // - put the current move at the first place
            principleVariation.push_back(moves[i]);
            // - copy the moves from the child nodes to the principle variation
            std::copy (line.begin(), line.end(), std::back_inserter (principleVariation));

        }

    }
    if (bestScore == MIN_SCORE) {
    	// no legal move

    	if(board.IsInCheck(board.SideToMove())) return MATE_SCORE - depth;
    	else return 0;

    }
    return bestScore;
}

Move SearchAgent::GetBestMove(int outputIndicator) {
        int maxDepth = 5;

	clock_t start, end;
	double cpuTime;
        start = std::clock();

        for(int depth = 0; depth < maxDepth; ++depth) {
           start = std::clock();

	   int score = AlphaBeta(depth, MIN_SCORE, MAX_SCORE, bestMoves);

  	   end = clock();
    	   cpuTime = std::difftime(end, start)/CLOCKS_PER_SEC;

           evaluator.Reset();
    	   int nNodes = checkedNodes;
    	   checkedNodes = 0;

           if(outputIndicator > 0) {
	       std::cout << "depth = " << depth << " move: " << bestMoves[0] << " score = " << score << std::endl;
               std::cout << "checked " << nNodes << " nodes in " << cpuTime << " s " << nNodes/cpuTime << " nodes/s \n";
               if(score == -MATE_SCORE + depth -1) std::cout << "checkmate" << std::endl;
	       for(int i=0; i<bestMoves.size(); ++i) std::cout << bestMoves[i] << ", ";
               std::cout << std::endl;
           }
           if(outputIndicator == 0) {
               std::cout << depth << ' ' << score << ' ' << (int) (cpuTime*100) << ' ' << nNodes << ' ';
               for(int i=0; i<bestMoves.size(); ++i) std::cout << bestMoves[i] << ", ";
               std::cout << std::endl;
           }
        }
	return bestMoves[0];
}

/*
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
    	for(int i=0; i<MAX_PLY; ++i) std::cout << bestMoves[i] << ", ";
    	std::cout << std::endl;
    	if (bestScoreSoFar > alpha) alpha = bestScoreSoFar;

    }
    return bestMoveSoFar;
}
*/
