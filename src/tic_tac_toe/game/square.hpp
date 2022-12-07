#pragma once

namespace tic_tac_toe {

struct Square {
    Square(short row_on_board, short col_on_board);
    Square(int row_on_board, int col_on_board) : Square(static_cast<short>(row_on_board), static_cast<short>(col_on_board)) { }

    short row;
    short col;
};

}  // namespace tic_tac_toe
