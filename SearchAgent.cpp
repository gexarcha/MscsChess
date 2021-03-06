#include "SearchAgent.h"

#include <iostream>
#include <vector>
using std::vector;
#include <ctime>

int SearchAgent::AlphaBeta(int depth, int alpha, int beta, vector<Move> & principleVariation) {
    checkedNodes++;

    int bestScore = MIN_SCORE;
    int score = MIN_SCORE;

    Moves moves;
    if(!board.GeneratePseudoLegalMoves(moves)) return ILLEGAL;
	if(bestMoves.size() > ply) followPV = false;
    if( !(followPV && moves.Includes(bestMoves[ply]) ) ) followPV = false;
    moves.Sort();
    size_t nMoves = moves.Size();
    for(size_t i = 0; i<nMoves; ++i) {
        board.ApplyMove(moves[i]); ply++;

        vector<Move> line;
        if(depth == 0) {
        	if(moves[i].IsCapture()) score = -AlphaBeta(depth, -beta, -alpha, line);
        	else score = evaluator.Score();
        }
        else score = - AlphaBeta(depth-1, -beta, -alpha, line);

        board.UndoMove(); ply--;

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

Move SearchAgent::GetBestMove() {
        int maxDepth = 5;
        followPV = false;

        for(int depth = 0; depth < maxDepth; ++depth) {

           clock_t start = std::clock();

           if(depth > 0) followPV = true;
	       int score = AlphaBeta(depth, MIN_SCORE, MAX_SCORE, bestMoves);

     	   clock_t end = clock();
    	   double cpuTime = std::difftime(end, start)/CLOCKS_PER_SEC;

           evaluator.Reset();
    	   int nNodes = checkedNodes;
    	   checkedNodes = 0;

		   // thinking output in xboard format:
		   // "depth score time nodes pv" with
		   // - depth (current depth of the search)
		   // - score (in centipawns)
		   // - time (in centiseconds)
		   // - nodes searched
		   // - pv (principle variation in free form text)
		   // for details see:  http://www.gnu.org/software/xboard/engine-intf.html#10
		   std::cout << depth << ' ' << score << ' ' << (int) cpuTime*100 << ' ' << nNodes << ' ';
           for(size_t i=0; i<bestMoves.size(); ++i) std::cout << bestMoves[i] << ", ";
           std::cout << std::endl;    
	}
	return bestMoves[0];
}


