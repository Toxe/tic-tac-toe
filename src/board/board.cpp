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

    for (std::size_t row = 0; row < data.size(); ++row)
        for (std::size_t col = 0; col < data[row].size(); ++col)
            if (const auto c = data[row][col]; c != '-')
                board.change_owner_of_square(Square{row, col}, c == 'X' ? human_player_id : ai_player_id);

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
    for (std::size_t row = 0; row < squares_.size(); ++row)
        for (std::size_t col = 0; col < squares_[row].size(); ++col)
            if (empty_square({row, col}))
                return true;

    return false;
}

void Board::change_owner_of_square(const Square square, player_id player)
{
    assert(player == human_player_id || player == ai_player_id);

    squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)] = player;
}

void Board::clear_owner_of_square(const Square square)
{
    squares_[static_cast<std::size_t>(square.row)][static_cast<std::size_t>(square.col)] = no_player_id;
}

}  // namespace tic_tac_toe
