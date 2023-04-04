#pragma once

#include <initializer_list>
#include <string_view>

#include "../game/player.hpp"
#include "../grid/grid.hpp"
#include "square.hpp"

namespace tic_tac_toe {

class Board {
public:
    Board();
    explicit Board(const std::initializer_list<std::string_view>& data);

    [[nodiscard]] int cols() const { return squares_.width(); }
    [[nodiscard]] int rows() const { return squares_.height(); }

    [[nodiscard]] Player player_of_square(Square square) const;
    [[nodiscard]] bool empty_square(Square square) const;
    [[nodiscard]] bool has_empty_squares() const;

    [[nodiscard]] bool all_squares_in_col_belong_to(int col, Player player) const;
    [[nodiscard]] bool all_squares_in_row_belong_to(int row, Player player) const;

    void change_owner_of_square(Square square, Player player);
    void clear_owner_of_square(Square square);

private:
    Grid<Player, Square> squares_;
};

}  // namespace tic_tac_toe
