#include "minimax.hpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <vector>

#include "../board/board.hpp"
#include "../game/win_conditions.hpp"
#include "stats.hpp"

namespace tic_tac_toe {

std::vector<Square> get_all_empty_squares(const Board& board)
{
    std::vector<Square> all_empty_squares;

    for (int row = 0; row < board.rows(); ++row)
        for (int col = 0; col < board.cols(); ++col)
            if (board.empty_square({col, row}))
                all_empty_squares.emplace_back(col, row);

    return all_empty_squares;
}

AIMove minimax(const int depth, const int max_depth, const Board& board, const Square move_square, const bool is_maximizing, MinimaxStats& stats)
{
    stats.update(depth);

    const auto win_condition = get_win_condition(board);

    if (win_condition == WinCondition::player1_won) {
        assert(max_depth - depth > 0);
        return {max_depth - depth, move_square, is_maximizing};
    } else if (win_condition == WinCondition::player2_won) {
        assert(max_depth - depth > 0);
        return {-(max_depth - depth), move_square, is_maximizing};
    } else if (win_condition == WinCondition::draw) {
        return {0, move_square, is_maximizing};
    }

    if (depth == max_depth) {
        return {0, move_square, is_maximizing};
    }

    const auto all_empty_squares = get_all_empty_squares(board);

    if (all_empty_squares.empty())
        throw std::invalid_argument("error");

    if (is_maximizing) {
        auto max_score = AIMove{std::numeric_limits<int>::min(), move_square, is_maximizing};

        for (const auto& square : all_empty_squares) {
            Board child_board = board;
            child_board.change_owner_of_square(square, player1_id);

            auto res = minimax(depth + 1, max_depth, child_board, square, false, stats);

            if (res.score > max_score.score)
                max_score = AIMove{res.score, square, is_maximizing};
        }

        return max_score;
    } else {
        auto min_score = AIMove{std::numeric_limits<int>::max(), move_square, is_maximizing};

        for (const auto& square : all_empty_squares) {
            Board child_board = board;
            child_board.change_owner_of_square(square, player2_id);

            auto res = minimax(depth + 1, max_depth, child_board, square, true, stats);

            if (res.score < min_score.score)
                min_score = AIMove{res.score, square, is_maximizing};
        }

        return min_score;
    }
}

}  // namespace tic_tac_toe
