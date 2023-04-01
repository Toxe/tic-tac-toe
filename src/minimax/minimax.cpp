#include "minimax.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include "../board/board.hpp"
#include "../game/win_conditions.hpp"
#include "stats.hpp"

namespace tic_tac_toe {

struct WithOwnerOfSquare {
    WithOwnerOfSquare(Board& board, Square& square, const player_id player) : board_{board}, square_{square} { board_.change_owner_of_square(square_, player); }
    ~WithOwnerOfSquare() { board_.clear_owner_of_square(square_); }

private:
    Board& board_;
    Square& square_;
};

int calc_score(const int depth, const int max_depth, const WinCondition win_condition)
{
    assert(win_condition != WinCondition::none);

    if (win_condition == WinCondition::draw)
        return 0;

    const int score = max_depth - (depth - 1);
    assert(score > 0);

    return win_condition == WinCondition::player1_won ? score : -score;
}

MinimaxMove minimax(Board& board, const Square square, const int depth, const int max_depth, const MinimaxStrategy strategy, MinimaxStats& stats, int alpha, int beta)
{
    stats.update(depth);

    const auto win_condition = get_win_condition(board);

    if (game_over(win_condition))
        return {square, calc_score(depth, max_depth, win_condition)};

    if (depth == max_depth)
        return {square, 0};

    MinimaxMove best_move{square, strategy == MinimaxStrategy::maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max()};
    Square check_square{0, 0};
    bool done = false;

    while (check_square.y < board.rows() && !done) {
        check_square.x = 0;

        while (check_square.x < board.cols() && !done) {
            if (board.empty_square(check_square)) {
                if (strategy == MinimaxStrategy::maximizing) {
                    const WithOwnerOfSquare with_owner_of_square{board, check_square, player1_id};
                    const auto move = minimax(board, check_square, depth + 1, max_depth, MinimaxStrategy::minimizing, stats, alpha, beta);

                    if (move.score > best_move.score) {
                        best_move = MinimaxMove{check_square, move.score};
                        alpha = std::max(alpha, best_move.score);

                        if (best_move.score >= beta)
                            done = true;
                    }
                } else {
                    const WithOwnerOfSquare with_owner_of_square{board, check_square, player2_id};
                    const auto move = minimax(board, check_square, depth + 1, max_depth, MinimaxStrategy::maximizing, stats, alpha, beta);

                    if (move.score < best_move.score) {
                        best_move = MinimaxMove{check_square, move.score};
                        beta = std::min(beta, best_move.score);

                        if (best_move.score <= alpha)
                            done = true;
                    }
                }
            }

            ++check_square.x;
        }

        ++check_square.y;
    }

    return best_move;
}

}  // namespace tic_tac_toe
