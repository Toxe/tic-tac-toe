#pragma once

#include "../app/app_controller.hpp"
#include "../board/board.hpp"
#include "../command/command.hpp"
#include "../game/game_state.hpp"
#include "../output/console_writer.hpp"

namespace tic_tac_toe {

Command receive_player_command(GameState& game_state, Board& board, AppController& app_controller, ConsoleWriter& console_writer);

}  // namespace tic_tac_toe
