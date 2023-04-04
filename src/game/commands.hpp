#pragma once

#include "../board/square.hpp"
#include "../command/command.hpp"
#include "../game/player.hpp"

namespace tic_tac_toe {

class Board;
class GamePlayers;
class ConsoleWriter;

Command PlayerMoveCommand(GamePlayers* game_players, Board* board, ConsoleWriter* console_writer, Player player, Square square);

}  // namespace tic_tac_toe
