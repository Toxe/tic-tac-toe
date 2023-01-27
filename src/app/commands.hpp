#pragma once

#include "../command/command.hpp"

namespace tic_tac_toe {

class AppController;
class ConsoleWriter;

Command HelpCommand(ConsoleWriter* console_writer);
Command QuitCommand();
Command UndoCommand(AppController* controller);
Command RedoCommand(AppController* controller);

}  // namespace tic_tac_toe
