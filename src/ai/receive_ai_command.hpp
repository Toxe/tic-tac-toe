#pragma once

#include "../command/command.hpp"

namespace tic_tac_toe {

class Board;
class CommandFactory;

Command receive_ai_command(const Board& board, CommandFactory& command_factory);

}  // namespace tic_tac_toe
