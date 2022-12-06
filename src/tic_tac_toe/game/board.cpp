#include "board.hpp"

#include <cassert>

namespace tic_tac_toe {

player_id Board::get_player_of_square(const int row, const int col) const
{
    assert(row >= 0 && row < 3);
    assert(col >= 0 && col < 3);

    return squares_[row][col];
}

bool Board::empty_square(const int row, const int col) const
{
    return get_player_of_square(row, col) == 0;
}

void Board::change_owner_of_square(const int row, const int col, player_id player)
{
    assert(row >= 0 && row < 3);
    assert(col >= 0 && col < 3);
    assert(player == 1 || player == 2);

    squares_[row][col] = player;
}

bool Board::game_over() const
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (empty_square(row, col))
                return false;

    return true;
}

}  // namespace tic_tac_toe
