#include "minimax.hpp"

#include <cassert>
#include <limits>
#include <stdexcept>

#include "../board/board.hpp"
#include "../game/win_conditions.hpp"
#include "stats.hpp"

namespace tic_tac_toe {

bool cmp_move_gt(const MinimaxMove& move, const MinimaxMove& best_move) { return move.score > best_move.score; }
bool cmp_move_lt(const MinimaxMove& move, const MinimaxMove& best_move) { return move.score < best_move.score; }

int calc_score(const int depth, const int max_depth, const WinCondition win_condition)
{
    assert(win_condition != WinCondition::none);

    if (win_condition == WinCondition::draw)
        return 0;

    const int score = max_depth - (depth - 1);
    assert(score > 0);

    return win_condition == WinCondition::player1_won ? score : -score;
}

MinimaxMove minimax(Board& board, const Square square, const int depth, const int max_depth, const MinimaxStrategy strategy, MinimaxStats& stats)
{
    stats.update(depth);

    const auto win_condition = get_win_condition(board);

    if (game_over(win_condition))
        return {square, calc_score(depth, max_depth, win_condition)};

    if (depth == max_depth)
        return {square, 0};

    const auto check_player = strategy == MinimaxStrategy::maximizing ? player1_id : player2_id;
    const auto check_strategy = strategy == MinimaxStrategy::maximizing ? MinimaxStrategy::minimizing : MinimaxStrategy::maximizing;
    const auto is_better = strategy == MinimaxStrategy::maximizing ? cmp_move_gt : cmp_move_lt;

    MinimaxMove best_move{square, strategy == MinimaxStrategy::maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max()};

    for (int row = 0; row < board.rows(); ++row) {
        for (int col = 0; col < board.cols(); ++col) {
            const Square check_square{col, row};

            if (board.empty_square(check_square)) {
                board.change_owner_of_square(check_square, check_player);
                const auto move = minimax(board, check_square, depth + 1, max_depth, check_strategy, stats);

                if (is_better(move, best_move))
                    best_move = MinimaxMove{check_square, move.score};

                board.clear_owner_of_square(check_square);
            }
        }
    }

    return best_move;
}

}  // namespace tic_tac_toe
