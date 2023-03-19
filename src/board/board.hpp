#pragma once

#include <array>

#include "../game/player.hpp"
#include "../grid/grid.hpp"
#include "square.hpp"

namespace tic_tac_toe {

class Board {
public:
    Board() : squares_{3, 3, no_player_id} { }

    static Board with_data(const std::array<std::array<char, 3>, 3>& data);

    [[nodiscard]] int cols() const { return squares_.width(); }
    [[nodiscard]] int rows() const { return squares_.height(); }

    [[nodiscard]] player_id player_of_square(Square square) const;
    [[nodiscard]] bool empty_square(Square square) const;
    [[nodiscard]] bool has_empty_squares() const;

    [[nodiscard]] bool all_squares_in_col_belong_to(int col, player_id player) const;
    [[nodiscard]] bool all_squares_in_row_belong_to(int row, player_id player) const;

    void change_owner_of_square(Square square, player_id player);
    void clear_owner_of_square(Square square);

private:
    Grid<player_id, Square> squares_;
};

}  // namespace tic_tac_toe
