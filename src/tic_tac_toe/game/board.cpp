#include "board.hpp"

#include <cassert>

namespace tic_tac_toe {

player_id Board::get_player_of_square(const Square square) const
{
    return squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)];
}

bool Board::empty_square(const Square square) const
{
    return get_player_of_square(square) == 0;
}

void Board::change_owner_of_square(const Square square, player_id player)
{
    assert(player == human_player_id || player == ai_player_id);

    squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)] = player;
}

bool Board::game_over() const
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (empty_square({row, col}))
                return false;

    return true;
}

}  // namespace tic_tac_toe
