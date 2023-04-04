#pragma once

#include "../board/square.hpp"
#include "../game/player.hpp"
#include "command.hpp"

namespace tic_tac_toe {

class Board;
class GamePlayers;
class AppController;
class ConsoleWriter;

class CommandFactory {
public:
    CommandFactory(Board& board, GamePlayers& game_players, AppController& controller, ConsoleWriter& console_writer)
        : board_{&board}, game_players_{&game_players}, controller_{&controller}, console_writer_{&console_writer} { }

    Command create_player_move_command(Player player, Square square);
    Command create_help_command();
    Command create_quit_command();
    Command create_undo_command();
    Command create_redo_command();

private:
    Board* board_;
    GamePlayers* game_players_;
    AppController* controller_;
    ConsoleWriter* console_writer_;
};

}  // namespace tic_tac_toe
