#include "show_output.hpp"

#include "fmt/core.h"

#include "generate_output.hpp"

namespace tic_tac_toe {

void show_output(const GameState& game_state)
{
    fmt::print("{}", detail::generate_output(game_state));
}

}  // namespace tic_tac_toe
