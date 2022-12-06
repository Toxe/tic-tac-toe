#include "show_output.hpp"

#include "fmt/core.h"

#include "generate_output.hpp"

namespace tic_tac_toe {

void show_output(const Board& board)
{
    fmt::print("{}", generate_output(board));
}

}  // namespace tic_tac_toe
