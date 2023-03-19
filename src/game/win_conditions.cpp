#include "win_conditions.hpp"

namespace tic_tac_toe {

bool game_over(const Board& board)
{
    return get_win_condition(board) != WinCondition::none;
}

WinCondition get_win_condition(const Board& board)
{
    if (check_player_victory(board, human_player_id))
        return WinCondition::human_player_won;

    if (check_player_victory(board, ai_player_id))
        return WinCondition::ai_player_won;

    if (!board.has_empty_squares())
        return WinCondition::draw;

    return WinCondition::none;
}

bool has_winning_row(const Board& board, const player_id player)
{
    for (int row = 0; row < board.rows(); ++row)
        if (board.all_squares_in_row_belong_to(row, player))
            return true;

    return false;
}

bool has_winning_column(const Board& board, const player_id player)
{
    for (int col = 0; col < board.cols(); ++col)
        if (board.all_squares_in_col_belong_to(col, player))
            return true;

    return false;
}

bool has_winning_diagonal(const Board& board, const player_id player)
{
    if (board.player_of_square(Square{0, 0}) == player && board.player_of_square(Square{1, 1}) == player && board.player_of_square(Square{2, 2}) == player)
        return true;

    if (board.player_of_square(Square{0, 2}) == player && board.player_of_square(Square{1, 1}) == player && board.player_of_square(Square{2, 0}) == player)
        return true;

    return false;
}

bool check_player_victory(const Board& board, const player_id player)
{
    return has_winning_row(board, player) || has_winning_column(board, player) || has_winning_diagonal(board, player);
}

}  // namespace tic_tac_toe
