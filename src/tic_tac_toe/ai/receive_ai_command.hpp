#pragma once

#include "../game/board.hpp"
#include "../game/command.hpp"

namespace tic_tac_toe {

Command receive_ai_command(const Board& board);

}  // namespace tic_tac_toe
