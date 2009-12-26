# The name of the project is CHESS
# root source dir ${CHESS_SOURCE_DIR}
# root bin dir ${CHESS_BINARY_DIR}
cmake_minimum_required (VERSION 2.4.5)
project (CHESS)
add_executable(MscsChess main.cpp Board.cpp Piece.cpp Evaluator.cpp SearchAgent.cpp Move.cpp)
