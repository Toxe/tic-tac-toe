#include "show_output.hpp"

#include "fmt/core.h"

#include "show_board.hpp"

namespace tic_tac_toe {

void show_output(const Board& board)
{
    fmt::print("{}", show_board(board));
}

}  // namespace tic_tac_toe
