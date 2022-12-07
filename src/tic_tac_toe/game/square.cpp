#include "square.hpp"

#include <stdexcept>

namespace tic_tac_toe {

Square::Square(const short row_on_board, const short col_on_board)
{
    if (row_on_board < 0 || row_on_board > 2 || col_on_board < 0 || col_on_board > 2)
        throw std::invalid_argument("invalid row or column");

    row = row_on_board;
    col = col_on_board;
}

}  // namespace tic_tac_toe
