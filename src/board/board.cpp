#include "board.hpp"

#include <algorithm>
#include <cassert>

namespace tic_tac_toe {

Board Board::with_data(const std::array<std::array<char, 3>, 3>& data)
{
    Board board;

    for (int row = 0; row < board.rows(); ++row)
        for (int col = 0; col < board.cols(); ++col)
            if (const auto c = data[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]; c != '-')
                board.change_owner_of_square(Square{col, row}, c == 'X' ? player1_id : player2_id);

    return board;
}

player_id Board::player_of_square(Square square) const
{
    return squares_.at(square);
}

bool Board::empty_square(const Square square) const
{
    return player_of_square(square) == no_player_id;
}

bool Board::has_empty_squares() const
{
    return std::any_of(squares_.begin(), squares_.end(), [](auto player) { return player == no_player_id; });
}

bool Board::all_squares_in_col_belong_to(const int col, const player_id player) const
{
    return std::all_of(squares_.col(col).begin(), squares_.col(col).end(), [&](auto player_in_col) { return player_in_col == player; });
}

bool Board::all_squares_in_row_belong_to(const int row, const player_id player) const
{
    return std::all_of(squares_.row(row).begin(), squares_.row(row).end(), [&](auto player_in_row) { return player_in_row == player; });
}

void Board::change_owner_of_square(const Square square, const player_id player)
{
    assert(player_id_is_valid(player));

    squares_.at(square) = player;
}

void Board::clear_owner_of_square(const Square square)
{
    squares_.at(square) = no_player_id;
}

}  // namespace tic_tac_toe
