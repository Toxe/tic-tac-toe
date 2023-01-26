#pragma once

#include <cstddef>

namespace tic_tac_toe {

struct Square {
    Square() = default;
    Square(short row_on_board, short col_on_board);
    Square(int row_on_board, int col_on_board) : Square(static_cast<short>(row_on_board), static_cast<short>(col_on_board)) { }
    Square(std::size_t row_on_board, std::size_t col_on_board) : Square(static_cast<short>(row_on_board), static_cast<short>(col_on_board)) { }

    short row = 0;
    short col = 0;
};

inline bool operator==(const Square& lhs, const Square& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; }
inline bool operator!=(const Square& lhs, const Square& rhs) { return !(lhs == rhs); }

}  // namespace tic_tac_toe
