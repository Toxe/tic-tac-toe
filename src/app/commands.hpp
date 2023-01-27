#pragma once

#include "../command/command.hpp"

namespace tic_tac_toe {

class AppController;

Command HelpCommand();
Command QuitCommand();
Command UndoCommand(AppController* controller);
Command RedoCommand(AppController* controller);

}  // namespace tic_tac_toe
