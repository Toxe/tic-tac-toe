#pragma once

#include <cstddef>

#include "../grid/coords.hpp"

namespace tic_tac_toe {

struct Square : public Coords<short> {
    Square() : Coords{} { }
    Square(short col_on_board, short row_on_board);
    Square(int col_on_board, int row_on_board) : Square(static_cast<short>(col_on_board), static_cast<short>(row_on_board)) { }
    Square(std::size_t col_on_board, std::size_t row_on_board) : Square(static_cast<short>(col_on_board), static_cast<short>(row_on_board)) { }
};

}  // namespace tic_tac_toe
