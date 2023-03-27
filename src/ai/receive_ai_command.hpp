#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace tic_tac_toe {

class Board;
class CommandFactory;

Command receive_ai_command(player_id player, const Board& board, CommandFactory& command_factory);

}  // namespace tic_tac_toe
