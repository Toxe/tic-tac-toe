#pragma once

#include "../command/command.hpp"

namespace tic_tac_toe {

class AppController;
class ConsoleWriter;
class GamePlayers;

Command HelpCommand(ConsoleWriter* console_writer);
Command QuitCommand();
Command UndoCommand(AppController* controller, const GamePlayers* game_players);
Command RedoCommand(AppController* controller, const GamePlayers* game_players);

}  // namespace tic_tac_toe
