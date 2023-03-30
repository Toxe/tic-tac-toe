#pragma once

#include "../board/square.hpp"

namespace tic_tac_toe {

class Board;
class MinimaxStats;

enum class MinimaxStrategy {
    maximizing,
    minimizing
};

struct MinimaxMove {
    Square square;
    int score;
};

MinimaxMove minimax(Board& board, Square square, int depth, int max_depth, MinimaxStrategy strategy, MinimaxStats& stats);

}  // namespace tic_tac_toe
