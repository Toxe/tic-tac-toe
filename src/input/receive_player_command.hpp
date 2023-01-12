#pragma once

#include "../board/board.hpp"
#include "../game/command.hpp"

namespace tic_tac_toe {

Command receive_player_command(const Board& board);

}  // namespace tic_tac_toe
