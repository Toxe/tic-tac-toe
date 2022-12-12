#pragma once

#include "../game/board.hpp"
#include "../game/command.hpp"

namespace tic_tac_toe {

void execute_command(Board& board, Command command);

}  // namespace tic_tac_toe
