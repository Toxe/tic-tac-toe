#pragma once

#include "../command/command.hpp"
#include "../game/player.hpp"

namespace tic_tac_toe {

class Board;
class ConsoleWriter;
class CommandFactory;

Command receive_player_command(Player player, Board& board, ConsoleWriter& console_writer, CommandFactory& command_factory);

}  // namespace tic_tac_toe
