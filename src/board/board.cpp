#include "board.hpp"

#include <cassert>
#include <string_view>

namespace tic_tac_toe {

Board::Board()
{
    for (auto& row : squares_)
        row.fill(no_player_id);
}

Board Board::with_data(const std::array<std::array<char, 3>, 3>& data)
{
    Board board{};

    for (int row = 0; row < std::ssize(data); ++row)
        for (int col = 0; col < std::ssize(data[static_cast<std::size_t>(row)]); ++col)
            board.change_owner_of_square(Square{row, col}, data[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] == 'x' ? human_player_id : ai_player_id);

    return board;
}

player_id Board::player_of_square(Square square) const
{
    return squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)];
}

bool Board::empty_square(const Square square) const
{
    return player_of_square(square) == no_player_id;
}

bool Board::has_empty_squares() const
{
    for (int row = 0; row < std::ssize(squares_); ++row)
        for (int col = 0; col < std::ssize(squares_[static_cast<std::size_t>(row)]); ++col)
            if (empty_square({row, col}))
                return true;

    return false;
}

void Board::change_owner_of_square(const Square square, player_id player)
{
    assert(player == human_player_id || player == ai_player_id);

    squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)] = player;
}

}  // namespace tic_tac_toe
