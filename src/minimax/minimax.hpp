#pragma once

#include <limits>

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

MinimaxMove minimax(Board& board, Square square, int depth, int max_depth, MinimaxStrategy strategy, MinimaxStats& stats, int alpha = std::numeric_limits<int>::min(), int beta = std::numeric_limits<int>::max());

}  // namespace tic_tac_toe
