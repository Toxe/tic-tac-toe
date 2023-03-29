#pragma once

#include "../board/square.hpp"

namespace tic_tac_toe {

class Board;
class MinimaxStats;

struct AIMove {
    int score;
    Square square;
    bool is_maximizing;
};

AIMove minimax(int depth, int max_depth, const Board& board, Square square, bool is_maximizing, MinimaxStats& stats);

}  // namespace tic_tac_toe
