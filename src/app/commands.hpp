#pragma once

#include "../command/command.hpp"

namespace tic_tac_toe {

class AppController;
class ConsoleWriter;
class GameState;

Command HelpCommand(ConsoleWriter* console_writer);
Command QuitCommand();
Command UndoCommand(AppController* controller, const GameState* game_state);
Command RedoCommand(AppController* controller, const GameState* game_state);

}  // namespace tic_tac_toe
