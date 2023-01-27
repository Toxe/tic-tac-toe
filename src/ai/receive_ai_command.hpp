#pragma once

#include "../board/board.hpp"
#include "../command/command.hpp"
#include "../game/game_state.hpp"

namespace tic_tac_toe {

Command receive_ai_command(GameState& game_state, Board& board);

}  // namespace tic_tac_toe
